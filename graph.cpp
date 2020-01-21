//
// Created by Carlos Flores on 1/13/20.
//

#include "graph.h"
#include <iostream>
#include <stack>
#include <unistd.h>
#include <cmath>
using namespace std;

graph::graph(const int n, const double d){
    recursive = 0, count = 0, delay = d, size = n;
    visualize = true;
    for (int i = n; i > 0 ; i--){
        s.push(i);
    }
}

stack<int>* graph::find(const string &x) {
    if (x == "start"){
        return &s;
    } else if (x == "aux1"){
        return &a1;
    } else if (x == "aux2"){
        return &a2;
    } else if (x == "aux3"){
        return &a3;
    } else if (x == "aux4"){
        return &a4;
    } else if (x == "dest"){
        return &d;
    } else {
        cout << "Error: can't find " << x << endl;
        return nullptr;
    }
}

// Move one disc from tower i to tower f
void graph::move(const string i, const string f){
    // Placeholder for the value of the disc
    int temp = 0;
    // Get pointers to the two towers
    auto from = find(i), to = find(f);
    // If you successfully returned two pointers to a tower then:
    if( (from != nullptr) && (to != nullptr) ){
        // Store the value of the disc to be moved in the temporary variable
        temp = from->top();
        // Remove the disc from tower i
        from->pop();
        // Add that disc to tower f
        to->push(temp);
    }

    // If some value was stored then a disc was successfully moved
    if (temp){
        // Print the action taken and the current state of the graph
        cout << ++count << ". Move disc " << temp;
        cout << " from " << i << " to " << f  << "."<< endl;

        if (visualize){
            print();
            // Sleep for a while (for the animation display)
            usleep(int(delay*10000));
        }
    }
}

void graph::move(const string i, const string via, const string f){
    move(i,via);
    move(via, f);
}

void graph::move(const string i, const string v1, const string v2, const string f){
    move(i,v1);
    move(v1, v2);
    move(v2, f);
}

void graph::print(){
    // Make an array of pointers to all five towers
    stack<int>* arr[6] = {&s, &a1, &a2, &a3, &a4, &d};
    // Declare 5 empty towers to store the temporary data
    stack<int> clr[6];
    // Unload the data from the towers to the temp stack and print the information
    for (int i = 0; i < size ; i++){
        for (int j = 0; j < 6; j++){
            if(arr[j]->size() == size - i){
                cout << arr[j]->top();
                clr[j].push(arr[j]->top());
                arr[j]->pop();
            } else {
                cout << ".";
            }
            cout << "   ";
        }
        cout << endl;
    }
    cout << "------------------------" << endl;
    cout << "S  " << " A1 " << " A2 " << " A3 " << " A4 " << " D\n" << endl;

    // Reload the data from the temporary stack to the original stack
    for (int i = 0; i < 6; i++){
        while (clr[i].size()){
            arr[i]->push(clr[i].top());
            clr[i].pop();
        }
    }
}

// Increment the number of recursive calls by one
// It is used in the if-statement body of every recursive subroutine
void graph::invoke() {++recursive;}

void graph::showStatus() {
    // Display the performance and expected complexities:
    cout << "The number of recursive calls: " << recursive << endl;
    cout << "O(2^n) is: " << pow(2,size)<< endl;
    cout << "The number of actual moves: " << count << endl;
    cout << "O(3^n) is: " << pow(3, size) << endl;
}

// Disable graph visualization
void graph::turnOffGraphics() {visualize = false;}