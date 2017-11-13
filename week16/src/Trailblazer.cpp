// This is the CPP file you will edit and turn in.
// Also remove these comments here and add your own, along with
// comments on every function and on complex code sections.
// TODO: write comment header for this file; remove this comment

#include "Trailblazer.h"
#include <queue>
using namespace std;

static const double SUFFICIENT_DIFFERENCE = 0.2;

double getPathCost(const Vector<RoadEdge*> & path);
Path getPath(vector<RoadNode*> path);
Path getPathFromRoadEdge(Vector<RoadEdge*> roadedge);

/* Struct node is used to overload the operator : < in order to use the min priority_queue */
struct node
{
    friend bool operator< (node n1, node n2)
    {
        return getPathCost(n1.ele) > getPathCost(n2.ele);//"<"为从大到小排列，">"为从小打到排列
    }
    Vector<RoadEdge*> ele;
};


/* The the cost from the start to the end */
double getPathCost(const Vector<RoadEdge*>& path) {
    double cost = 0;
    for (RoadEdge* road_edge : path) {
        cost += road_edge->cost();
    }
    return cost;
}

/* Tranfer the data structure from vector<RoadNode*> to Vector<RoadNode*> (Path) */
Path getPath(vector<RoadNode*> path) {
    Path result;
    for (RoadNode* ele : path)
        result.add(ele);

    return result;
}

/* Get the result form the vector of roadedge */
Path getPathFromRoadEdge(Vector<RoadEdge*> roadedge) {
    if (roadedge.size() == 0)
        return {};

    Path result;
    result.add(roadedge[0]->from());
    for (RoadEdge* ele : roadedge) {
        result.add(ele->to());
    }

    return result;
}


Path dijkstrasAlgorithm(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    Vector<RoadEdge*> path;
    priority_queue<node> min_heap;
    /* Record the least from the start node */
    map<string, double> fixed;

    while (start != end) {
        /* Fist set the color of the start node */
        start->setColor(Color::GREEN);

        /* If the node is not visited */
        if (fixed.find(start->nodeName()) == fixed.end()) {
            fixed[start->nodeName()] = getPathCost(path);
            Set<RoadEdge*> road_edge_set = start->outgoingEdges();

            for (RoadEdge* road_edge : road_edge_set) {
                /* If the node is unvisited */
                if (fixed.find(road_edge->to()->nodeName()) == fixed.end()) {
                    /* Set the color of the node */
                    road_edge->to()->setColor(Color::YELLOW);
                    path.add(road_edge);

                    node ele;
                    ele.ele = path;
                    min_heap.push(ele);
                    path.remove(path.size() - 1);
                }
            }
        }

        if (min_heap.size() == 0) {
            path.clear();
            return {};
        }

        path = min_heap.top().ele;
        min_heap.pop();
        start = path[path.size() - 1]->to();
    }
    path[path.size() - 1]->to()->setColor(Color::GREEN);
    return getPathFromRoadEdge(path);
}


Path breadthFirstSearch(const RoadGraph& graph, RoadNode* start, RoadNode* end) {
    /* TODO: Delete the following lines and implement this function! */
    queue<vector<RoadNode*> > path_queue;
    set<RoadNode*> visited;             /* It marks the points visited */
    start->setColor(Color::YELLOW);
    vector<RoadNode*> path;

    /* If the start point is the same as the end point */
    if (start == end) {
        start->setColor(Color::GREEN);
        return getPath(path);
    }

    /* Push the start point into the queue */
    visited.insert(start);
    path.push_back(start);
    path_queue.push(path);
    while (!path_queue.empty()) {
        /* Get the path at the front of the queue */
        vector<RoadNode*> ele = path_queue.front();
        path_queue.pop();

        /* Get the last node of the path */
        RoadNode* last_node = ele[ele.size() - 1];
        /* Set the color because it is poped from the queue */
        last_node->setColor(Color::GREEN);

        /* Get the set of neightbor node of the node */
        Set<RoadEdge*> edge_set = last_node->outgoingEdges();

        for (RoadEdge* edge : edge_set) {
            RoadNode* next_node = edge->to();

            /* If the neighbor node is not visited */
            if (visited.find(next_node) == visited.end()) {
                vector<RoadNode*> ele_copy = ele;
                ele_copy.push_back(next_node);
                visited.insert(next_node);
                next_node->setColor(Color::YELLOW);

                /* If the node is the end node */
                if (next_node == end) {
                    next_node->setColor(Color::GREEN);
                    return getPath(ele_copy);
                }

                /* Else push it into queue */
                path_queue.push(ele_copy);
            }
        }
    }

    /* If no path found, return empty path */
    return {};
}



