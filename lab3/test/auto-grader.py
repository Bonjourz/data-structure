import subprocess
import threading

from os import getcwd, listdir


def compile_ladder(source_file, report_file):
    try:
        process = subprocess.Popen(["g++", "-std=c++11", "-O2", source_file, "-o", "ladder"])
        process.communicate()
    except:
        report_file.write("cannot compile {}\n".format(source_file))


def grade_ladder(report_file):
    trace_passed = 0
    threads = []

    for trace in listdir(getcwd() + "/traces"):
        if not trace.startswith("trace"):
            continue

        print("running {}".format(trace))

        # run ladder
        trace_file = open("traces/" + trace, "r")
        ladder_process = subprocess.Popen(["./ladder"], stdin=subprocess.PIPE, stdout=subprocess.PIPE)
        while True:
            s = trace_file.readline()
            if s.startswith("----"):
                break

            ladder_process.stdin.write(s.encode())
            ladder_process.stdin.flush()

        # get standard result
        ladder_length = 0
        standard_output = trace_file.readline().strip()
        if standard_output.startswith("A ladder from"):
            ladder_length = int(trace_file.readline())

        # check ladder result
        try:
            out, err = ladder_process.communicate(timeout=10)
            output = out.decode()
        except subprocess.TimeoutExpired:
            report_file.write("{}: ladder time out\n".format(trace))
            continue

        # find occurrence of standard result
        if output.find(standard_output) == -1:
            report_file.write("{}: unexpected result\n".format(trace))
            continue

        # if ladder should be found
        if ladder_length > 0:
            ladder = output[output.find(standard_output):].splitlines()[1].split()
            if len(ladder) != ladder_length:
                report_file.write("{}: ladder length dose not match!\n".format(trace))
                continue

            for pre_word, suc_word in zip(ladder[:-1], ladder[1:]):
                diff_count = 0
                for pre_letter, suc_letter in zip(pre_word, suc_word):
                    if pre_letter != suc_letter:
                        diff_count += 1

                if diff_count != 1:
                    report_file.write("{}: invalid ladder {} -> {}\n".format(trace, pre_word, suc_word))
                    continue

        report_file.write("{}: trace passed\n".format(trace))
        trace_passed += 1

    report_file.write("your program passed {} trace(s)".format(trace_passed))
    return trace_passed


def main():
    for cpp in listdir(getcwd() + "/submits"):
        if not cpp.endswith(".cpp"):
            continue

        try:
            _, student_id, student_name = cpp.split("+")
            student_name = student_name[:student_name.find(".")]
            report_name = student_id + " " + student_name + ".txt"
        except:
            report_name = cpp.split(".")[0] + ".txt"

        report = open("reports/" + report_name, "w")
        compile_ladder("submits/" + cpp, report)
        trace_passed = grade_ladder(report)
        print("{}\t{}".format(report_name, trace_passed))


if __name__ == '__main__':
    main()
