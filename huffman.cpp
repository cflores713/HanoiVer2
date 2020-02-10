#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

struct Node {
    string symbol;
    int counter, height;
    Node *left, *right;

    // Explicit Constructor (no children are passed)
    Node(string a, int b): symbol(a), counter(b), height(1), left(nullptr), right(nullptr) {}
    // Explicit Constructor w/children nodes passed as well as height.
    Node(string a, int b, Node* l, Node* r, int h): symbol(a), counter(b), height(h), left(l), right(r) {}
};

// Comparison Classes for the Priority Queue
struct CompareCount {
    bool operator()(Node* t1, Node* t2) {
        return (t1->counter > t2->counter);
    }
};

bool prioritizeByValue( pair<string, double> i, pair<string, double> k) { return i.second > k.second ;}
void print(priority_queue<Node*, vector<Node*>, CompareCount> pq);
Node* combine(Node* a, Node* b, int i);
Node* combineHuffmanNodes(priority_queue<Node*, vector<Node*>, CompareCount> &pq);
void printSideways(Node* cu, string indent="");
void makeEncoderMap(Node* tree, unordered_map<string, string> &myMap, string path, unordered_map<string, int> eTable, int passNum);

int main() {

    // Create a Hash Map of {letters : occurrences}
    //TODO fill in the vectors with the information given in the exam.
    vector<string> letters  = {"a", "b", "c", "d", "e", "f", "g", "h"};
    vector<int> frequencies = { 1,   2,   3,   4,   5,   6,   8,   11};

    priority_queue<Node*, vector<Node*>, CompareCount> pqCount;
    unordered_map<string, int> examMap;

    for (int i = 0 ; i < letters.size() ; i++){
        examMap[letters[i]] = frequencies[i];
        Node* temp = new Node( letters[i], frequencies[i]);
        pqCount.push(temp);
    }

    // Get the sum of all of the letters in the string.
    int sum = 0;
    for (const auto &i : frequencies) sum += i;
    cout << "Total number of letters: " << sum << endl;

    cout << "\nConstructing the Tree:" << endl;
    Node* huffmanTree = combineHuffmanNodes(pqCount);
    cout << "\nHuffman Tree:" << endl;
    printSideways(huffmanTree);
    unordered_map<string, string> encoder;
    cout << "\nMaking the Encoding Map:" << endl;
    makeEncoderMap(huffmanTree, encoder, "", examMap, sum);
    return 0;
}

void print(priority_queue<Node*, vector<Node*>, CompareCount> pq){
    int i = 1;
    string numFormat;
    priority_queue<Node*, vector<Node*>, CompareCount> c;
    Node* placeholder = nullptr;
    while (!pq.empty()){
        placeholder = new Node(pq.top()->symbol, pq.top()->counter, pq.top()->left, pq.top()->right, pq.top()->height);
        c.push(placeholder);
        pq.pop();
    }
    // Print the queue in order and push onto the original pq.
    while (!c.empty()){
        i < 10 ? numFormat = " " : numFormat = "";
        cout << numFormat << i << ". ";
        cout << c.top()->symbol << " : " << c.top()->counter << endl;
        placeholder = new Node(c.top()->symbol, c.top()->counter, c.top()->left, c.top()->right, pq.top()->height);
        pq.push(placeholder);
        c.pop();
        i++;
    }

}

Node* combine(Node* a, Node* b, int i){
    cout << "The nodes \"" << a->symbol << "\" and \"" << b->symbol << "\" will combine to form \"X" << i  << ".\""<< endl;
    Node* c = new Node("X"+ to_string(i), a->counter+b->counter);
    c->left = a, c->right = b;
    if (a->height > b->height) {
        c->height = a->height+1;
    } else {
        c->height = b->height+1;
    }
    return c;
}

Node* combineHuffmanNodes(priority_queue<Node*, vector<Node*>, CompareCount> &pq){
    int i = 1;
    string numFormat;
    Node *temp1, *temp2, *temp3;
    while (pq.size()>1){
        temp1 = new Node(pq.top()->symbol, pq.top()->counter, pq.top()->left, pq.top()->right, pq.top()->height);
        pq.pop();
        temp2 = new Node(pq.top()->symbol, pq.top()->counter,pq.top()->left, pq.top()->right, pq.top()->height);
        pq.pop();
        temp3 = combine(temp1, temp2, i);
        i++;
        pq.push(temp3);
    }
    return new Node(pq.top()->symbol, pq.top()->counter, pq.top()->left, pq.top()->right, pq.top()->height);
};

void printSideways(Node* cu, string indent){
    if (cu != nullptr) {
        printSideways(cu->left, indent + " \t ");
        cout << indent;
        cout << cu->symbol << " : " << cu->counter << endl;
        printSideways(cu->right, indent + " \t ");
    }
}

void fillEncoderMap(Node* tree, unordered_map<string, string> &myMap, string path){
    if (tree){
        if ( !(tree->left) && !(tree->right) ) {
            myMap[tree->symbol] = path;
        } else {
            fillEncoderMap(tree->left, myMap, path+"0");
            fillEncoderMap(tree->right, myMap, path+"1");
        }
    }
}

void makeEncoderMap(Node* tree, unordered_map<string, string> &myMap, string path, unordered_map<string, int> eTable, int passNum){
    fillEncoderMap(tree, myMap, path);
    int runningSum =0;
    for (const auto& x : myMap){
        cout << x.first << " : " << x.second << endl;
    }
    bool flag = false;
    string plus = "+";
    cout << "\nThe Expected Bit Length is: " << endl;
    for (const auto& x : myMap){
        runningSum += eTable[x.first]*x.second.length();
        if (flag){
            cout << plus << " ";
        } else {
            flag = true;
        }
        cout << "(" << eTable[x.first] << "*" << x.second.length() << ") ";
    }
    cout << "\nThe expected  length is "<< runningSum <<"/" << passNum;
    double tempPassNum;
    tempPassNum = runningSum/double(passNum);
    cout << " = " << tempPassNum;
}
