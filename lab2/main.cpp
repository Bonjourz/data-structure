// ConsoleApplication2.cpp : ¶¨Òå¿ØÖÆÌ¨Ó¦ÓÃ³ÌÐòµÄÈë¿Úµã¡£
//

#include "Lines_window.h"

int main()
{
	using namespace Graph_lib;
	try {
			/* Initialize the calculator */
		Lines_window win(Point(100, 100), 600, 600, "lines");
		return gui_main();
	}

	/* Determine whether there is eception */
	catch (exception& e) {
		cerr << "exception: " << e.what() << "\n";
		return 1;
	}

	catch (...) {
		cerr << "Some exception.\n";
		return 2;
	}

	
	return 0;
}

