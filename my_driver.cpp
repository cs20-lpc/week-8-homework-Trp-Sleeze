#include <iostream>
#include <string>
#include <vector>
#include "StackFactory.hpp"
using namespace std;

template <typename T>
vector<T> drain(Stack<T>& s) {
    vector<T> out;
    while (!s.isEmpty()) {
        out.push_back(s.peek());
        s.pop();
    }
    return out;
}

template <typename T>
void testBoth(const vector<T>& seq) {
    Stack<T>* listS = StackFactory<T>::GetStack();                  // Linked list stack
    Stack<T>* arrayS = StackFactory<T>::GetStack((int)seq.size() + 5); // Array stack

    for (auto x : seq) { listS->push(x); arrayS->push(x); }

    while (!listS->isEmpty()) {
        T a = listS->peek(); listS->pop();
        T b = arrayS->peek(); arrayS->pop();
        if (a != b) cout << "mismatch\n";
    }

    delete listS;
    delete arrayS;
}

int main() {
    // ints
    {
        Stack<int>* s = StackFactory<int>::GetStack();
        for (int i = 1; i <= 5; ++i) s->push(i);
        cout << "Top: " << s->peek() << endl;
        auto popped = drain(*s);
        cout << "Popped: ";
        for (auto n : popped) cout << n << " ";
        cout << endl;
        delete s;
    }

    // strings
    {
        Stack<string>* s = StackFactory<string>::GetStack();
        s->push("alpha");
        s->push("beta");
        s->push("gamma");
        cout << s->peek() << endl; s->pop();
        cout << s->peek() << endl; s->pop();
        cout << s->peek() << endl; s->pop();
        delete s;
    }

    // parity check vs ArrayStack
    testBoth<int>({ 1,2,3,4 });
    testBoth<string>({ "a","bb","ccc" });

    cout << "done\n";
    return 0;
}
