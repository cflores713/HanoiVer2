//
// Created by Carlos Flores on 1/13/20.
//

#ifndef HANOI_GRAPH_H
#define HANOI_GRAPH_H

#include <iostream>
#include <fstream>
#include <stack>
using namespace std;

class graph {
private:
    stack<int> s, a1, a2, a3, a4, d;
    int size, count, recursive;
    double delay;

public:
    // Initialize the graph with N number of discs on the start tower
    graph(int n, double d);

    // Given a name of a tower return a pointer to that stack
    stack<int>* find(const string &x);

    // Take the top disc from i and move it to f
    void move(string i, string f);

    // Show the contents of the graph
    void print();

    // Increment the number of recursive invocations
    void invoke();

    // Give a summary of the algorithm's complexities
    void showStatus();

};

#endif //HANOI_GRAPH_H
