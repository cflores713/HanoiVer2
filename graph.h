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
    // Create six towers of integers to hold the discs
    stack<int> s, a1, a2, a3, a4, d;
    // Keep track of the number of moves
    int size, count, recursive;
    // The higher the number the faster the animation will run
    double delay;
    bool visualize;

public:
    // Initialize the graph with N number of discs on the start tower
    graph(int n, double d);

    // Given a name of a tower return a pointer to that stack
    stack<int>* find(const string &x);

    // Take the top disc from i and move it to f.
    void move(string i, string f);
    // Take the top disc from i, move it to via and then to f.
    void move(string i, string via, string f);
    // Take the top disc from i, move it to v1, then v2, and finally f.
    void move(string i, string v1, string v2, string f);

    // Show the contents of the graph
    void print();

    // Increment the number of recursive invocations
    void invoke();

    // Give a summary of the algorithm's complexities
    void showStatus();

    void turnOffGraphics();

    // Create a txt file of the first 100 moves and the last 100 moves.
    void generateAnalysisReport();

};

#endif //HANOI_GRAPH_H
