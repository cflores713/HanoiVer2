//
// Created by Carlos Flores on 1/13/20.
//

#include "graph.h"

graph::graph(const int n, const double d): recursive(0), count(0), delay(d), size(n), visualize(true){
    convert["start"] = &s, convert["aux1"] = &a1, convert["aux2"] = &a2;
    convert["aux3"] = &a3, convert["aux4"] = &a4, convert["dest"] = &dest;
    for (int i = n; i > 0 ; i--)
        s.push(i);
}

stack<int>* graph::find(const string &x) {
    if ( convert.find(x) != convert.end() ) return convert[x];
    else {
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
    if( (from) && (to) ){
        // Store the value of the disc to be moved in the temporary variable
        temp = from->top();
        // Remove the disc from tower i
        from->pop();
        // Add that disc to tower f
        to->push(temp);
    }
    // If some value was stored then a disc was successfully moved
    if (temp){
        ++count;
        if (visualize){
            // Print the action taken and the current state of the graph
            cout << count << ". Move disc " << temp << " from " << i << " to " << f  << "."<< endl;
            print();
            // Sleep for a while (for the animation display)
            usleep(int(delay*10000));
        } else {
            if (first100.size() < 100)
                first100.push(to_string(count) + ". Move disc " + to_string(temp) + " from " + i + " to " + f  + ".");

            if (last100.size() > 100)
                last100.pop();

            last100.push(to_string(count) + ". Move disc " + to_string(temp) + " from " + i + " to " + f  + ".");
        }
    }
}

void graph::move(const string i, const string via, const string f){
    move(i,via), move(via, f);
}

void graph::move(const string i, const string v1, const string v2, const string f){
    move(i,v1), move(v1, v2), move(v2, f);
}

void graph::print(){
    // Make an array of pointers to all five towers
    stack<int>* arr[6] = {&s, &a1, &a2, &a3, &a4, &dest};
    // Declare 5 empty towers to store the temporary data
    stack<int> clr[6];
    // Unload the data from the towers to the temp stack and print the information
    for (int i = 0; i < size ; i++){
        for (int j = 0; j < 6; j++){
            if(arr[j]->size() == size - i){
                cout << arr[j]->top();
                clr[j].push(arr[j]->top());
                arr[j]->pop();
            } else
                cout << ".";

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
    // If the animation is not displayed then show the first 100 moves and last 100 moves
    if (!visualize){
        cout << "The first 100 moves to move a stack of " << size << " discs are: " << endl;
        stack<string> reverse;
        while (!first100.empty()){
            reverse.push(first100.top());
            first100.pop();
        }
        while (!reverse.empty()){
            cout << reverse.top() << endl;
            reverse.pop();
        }
        cout << "\n\nThe last 100 moves to move a stack of " << size << " discs are: " << endl;
        while (!last100.empty()){
            cout << last100.front() << endl;
            last100.pop();
        }
    }
    // Display the performance and expected complexities:
    cout << "The number of recursive calls: " << recursive << endl;
    cout << "O(2^n) is: " << pow(2,size)<< endl;
    cout << "The number of actual moves: " << count << endl;
    cout << "O(3^n) is: " << pow(3, size) << endl;
}

// Disable graph visualization
void graph::turnOffGraphics() {visualize = false;}