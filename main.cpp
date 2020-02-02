#include <iostream>
#include "graph.h"
using namespace std;

// Function Prototypes: (they are declared beforehand since they will be used before being defined)
void H2(int n, string a, string b, string c, string d, graph &g);
void H4s(int n, string a, string b, string c, string d, string e, string f, graph &g);
void H3mid(int n, string a, string b, string c, string d, graph &g);
void H4d(int n, string a, string b, string c, string d, string e, string f, graph &g);
void H3s(int n, string a, string b, string c, string d, string e, string f, graph& g);
void H3d(int n, string a, string b, string c, string d, string e, string f, graph& g);


// Solve the problem with the helper functions
void Hanoi(const int n, const string a, const string b, const string c, const string d, const string e, const string f, graph &g){
    if (n){
        // Move N-1 discs from Start to Aux3
        H3s(n-1, a, b, c, d, e, f, g);
        // Move one disc from Start to Dest
        g.move(a, b, f);
        // Move N-1 discs from Aux3 to Dest
        H3d(n-1, a, b, c, d, e, f, g);
    }
}

// Move a stack of N discs 3 spaces from the start to inside the cycle:
void H3s(const int n, const string a, const string b, const string c, const string d, const string e, const string f, graph &g){
    if (n){
        g.invoke();
        // Move N-1 discs 4 spaces from the start to inside the cycle.
        H4s(n-1, a, b, c, d, e, f, g);
        // Move 1 disc from start to aux3.
        g.move(a, b, c, d);
        // Move N-1 discs 3 spaces inside the cycle.
        H3mid(n-1, e, b, c, d, g);
    }
}

// Move a stack of N discs 3 spaces from inside the cycle to dest.
void H3d(const int n, const string a, const string b, const string c, const string d, const string e, const string f, graph &g){
    if (n){
        g.invoke();
        // Move a stack of N-1 discs 3 spaces inside the cycle
        H3mid(n-1, d, e, b, c, g);
        // Move 1 disc 3 spaces inside the cycle.
        g.move(d, e, b, f);
        // Move N-1 discs 4 spaces from inside to outside the cycle.
        H4d(n-1, a, b, c, d, e, f, g);
    }
}

int main() {
    int num = 3;
    double animation = 10;
    string response = "Y";
    cout << "Enter the number of disks: " << endl;
    cin >> num;
    cout << "Enter the speed in the animation:\n    (1 is slow and 10 is fast)    " << endl;
    cin >> animation;
    graph demo(num, 10-animation);
    cout << "Do you wish to see the animtation?:\n    (Y for YES and N for NO)    " << endl;
    cin >> response;
    if (response != "Y") demo.turnOffGraphics();
    Hanoi(num, "start", "aux1", "aux2","aux3", "aux4","dest", demo);
    demo.showStatus();
    return 0;
}

// Move a stack of N discs 4 spaces from start to inside the cycle.
void H4s(const int n, const string a, const string b, const string c, const string d, const string e, const string f, graph &g){
    if (n){
        // Move N-1 discs from Start to Aux3
        H4s(n-1, a, b, c, d, e, f, g);
        // Move one disc from Start to Aux2
        g.move(a, b, c, d);
        // Move N-1 discs from Aux2 to Aux4
        H2(n-1, e, b, c, d, g);
        // Move one disc from Aux2 to Dest
        g.move(d, e);
        // Move N-1 discs from Aux1 to Dest
        H2(n-1, c, d, e, b, g);
    }
}

// Move a stack of N discs 4 spaces from inside the cycle to dest.
void H4d(const int n, const string a, const string b, const string c, const string d, const string e, const string f, graph &g){
    if (n){
        // Move N-1 discs from Start to Aux3
        H2(n-1, c, d, e, b, g);
        // Move one disc from Start to Aux2
        g.move(c, d);
        // Move N-1 discs from Aux3 to Aux1
        H2(n-1, e, b, c, d, g);
        // Move one disc from Aux2 to Dest
        g.move(d, e, b, f);
        // Move N-1 discs from Aux1 to Dest
        H4d(n-1, a, b, c, d, e, f, g);
    }
}

// Move a stack of N discs 3 spaces within the cycle
void H3mid(const int n, const string a, const string b, const string c, const string d, graph &g){
    if (n){
        // Move N-1 discs 2 spaces within the cycle.
        H2(n-1, a, b, c, d, g);
        // Move one disc one space.
        g.move(a, b);
        // Move N-1 discs two spaces within the cycle.
        H2(n-1, c, d, a, b, g);
        // Move one disc two spaces.
        g.move(b, c, d);
        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, a, b, c, d, g);
    }
}
// Move a stack of N discs 2 spaces within the cycle
void H2(const int n, const string a, const string b, const string c, const string d, graph &g){
    if (n){
        g.invoke();
        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, a, b, c, d, g);
        // Move 1 disc two spaces.
        g.move(a, b, c);
        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, d, a, b, c, g);
    }
}