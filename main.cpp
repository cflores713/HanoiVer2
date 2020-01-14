#include <iostream>
#include "graph.h"
using namespace std;

// Function Prototypes:
// They are declared beforehand since they will be used before being defined.
void H2(int n, string a, string b, string c, string d, string e, string f, graph &g);
void H4s(int n, string a, string b, string c, string d, string e, string f, graph &g);
void H3mid(int n, string a, string b, string c, string d, string e, string f, graph &g);
void H4d(int n, string a, string b, string c, string d, string e, string f, graph &g);

// Move a stack of N discs 2 spaces within the cycle
void H2(int n, string a, string b, string c, string d, string e,  string f, graph &g){
    if (n){
        g.invoke();
        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, a, b, c, d, e, f, g);

        // Move 1 disc two spaces.
        g.move(a, b);
        g.move(b, c);

        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, d, e, b, c, a, f, g);
    }
}

// Move a stack of N discs 3 spaces within the cycle
void H3mid(int n, string a, string b, string c, string d, string e, string f, graph &g){
    if (n){
        // Move N-1 discs 2 spaces within the cycle.
        H2(n-1, a, b, c, d, e, f, g);

        // Move one disc one space.
        g.move(a, b);

        // Move N-1 discs two spaces within the cycle.
        H2(n-1, c, d, a, b, e, f, g);

        // Move one disc two spaces.
        g.move(b, c);
        g.move(c, d);

        // Move N-1 discs 3 spaces within the cycle.
        H3mid(n-1, a, b, c, d, e, f, g);
    }
}

// Move a stack of n discs 3 spaces from the start to inside the cycle:
void H3s(int n, string a, string b, string c, string d, string e, string f, graph& g){
    if (n){
        g.invoke();
        // Move N-1 discs 4 spaces from the start to inside the cycle.
        H4s(n-1, a, b, c, d, e, f, g);

        // Move 1 disc from start to aux3.
        g.move(a, b);
        g.move(b, c);
        g.move(c, d);

        // Move N-1 discs 3 spaces inside the cycle.
        H3mid(n-1, e, b, c, d, a, f, g);
    }
}

// Move a stack of n discs 3 spaces from inside to outside the cycle.
void H3d(int n, string a, string b, string c, string d, string e, string f, graph& g){
    if (n){
        g.invoke();

        // Move a stack of N-1 discs 3 spaces inside the cycle
        H3mid(n-1, d, e, b, c, a, f, g);

        // Move 1 disc 3 spaces inside the cycle.
        g.move(d, e);
        g.move(e, b);
        g.move(b, f);

        // Move N-1 discs 4 spaces from inside to outside the cycle.
        H4d(n-1, a, b, c, d, e, f, g);
    }
}

// Move N-1 discs 4 spaces from inside to outside the cycle.
void H4s(int n, string a, string b, string c, string d, string e, string f, graph &g){
    if (n){
        // Move N-1 discs from Start to Aux3
        H4s(n-1, a, b, c, d, e, f, g);

        // Move one disc from Start to Aux2
        g.move(a, b);
        g.move(b, c);
        g.move(c, d);

        // Move N-1 discs from Aux2 to Aux4
        H2(n-1, e, b, c, d, a, f, g);

        // Move one disc from Aux2 to Dest
        g.move(d, e);

        // Move N-1 discs from Aux1 to Dest
        H2(n-1, c, d, e, b, a, f, g);
    }
}

void H4d(int n, string a, string b, string c, string d, string e, string f, graph &g){
    if (n){

        // Move N-1 discs from Start to Aux3
        H2(n-1, c, d, e, b, a, f, g);

        // Move one disc from Start to Aux2
        g.move(c, d);

        // Move N-1 discs from Aux3 to Aux1
        H2(n-1, e, b, c, d, a, f, g);

        // Move one disc from Aux2 to Dest
        g.move(d, e);
        g.move(e, b);
        g.move(b, f);

        // Move N-1 discs from Aux1 to Dest
        H4d(n-1, a, b, c, d, e, f, g);
    }
}

// Solve the problem with the helper functions
void Hanoi(int n, string a, string b, string c, string d, string e, string f, graph &g){
    if (n){
        // Move N-1 discs from Start to Aux3
        H3s(n-1, a, b, c, d, e, f, g);

        // Move one disc from Start to Dest
        g.move(a, b);
        g.move(b, f);

        // Move N-1 discs from Aux1 to Dest
        H3d(n-1, a, b, c, d, e, f, g);
    }
}

int main() {
    int num = 6;
    double animation = 7;
    cout << "Enter the number of disks: " << endl;
    //cin >> num;
    cout << "Enter the speed in the animation: " << endl;
    cout << "    (1 is slow and 10 is fast)    " << endl;
    //cin >> animation;
    graph test(num, 10-animation);

    Hanoi(num, "start", "aux1", "aux2","aux3", "aux4","dest", test);
    test.showStatus();

    return 0;
}
