#include <stdexcept>
#include <vector>
using namespace std;

template <typename T>
LinkedListStack<T>::LinkedListStack()
{
    top = nullptr;
    this->length = 0;
}

template <typename T>
LinkedListStack<T>::LinkedListStack(const LinkedListStack<T>& copyObj) {
    top = nullptr;
    this->length = 0;
    copy(copyObj);
}

template <typename T>
LinkedListStack<T>& LinkedListStack<T>::operator=(const LinkedListStack<T>& rightObj) {
    if (this != &rightObj) {
        clear();
        copy(rightObj);
    }
    return *this;
}

template <typename T>
LinkedListStack<T>::~LinkedListStack() {
    clear();
}

template <typename T>
void LinkedListStack<T>::clear() {
    // TO DO: Delete all the elements in the stack
    Node<T>* curr = top;
    while (curr != nullptr) {
        Node<T>* nxt = curr->next;
        delete curr;
        curr = nxt;
    }
    top = nullptr;
    this->length = 0;
}

template <typename T>
void LinkedListStack<T>::copy(const LinkedListStack<T>& copyObj) {
    // TO DO: Implement copy 
    std::vector<T> vals;
    Node<T>* curr = copyObj.top;
    while (curr != nullptr) {
        vals.push_back(curr->data);
        curr = curr->next;
    }
    for (int i = static_cast<int>(vals.size()) - 1; i >= 0; --i) {
        push(vals[i]);
    }
}

template <typename T>
int LinkedListStack<T>::getLength() const {
    return this->length;
}

template <typename T>
bool LinkedListStack<T>::isEmpty() const {
    return this->length == 0;
}

template <typename T>
T LinkedListStack<T>::peek() const {
    // TO DO: implement peek
    if (isEmpty()) throw underflow_error("peek on empty stack");
    return top->data;
}

template <typename T>
void LinkedListStack<T>::pop() {
    // TO DO: Implement pop
    if (isEmpty()) throw underflow_error("pop on empty stack");
    Node<T>* oldTop = top;
    top = top->next;
    delete oldTop;
    --this->length;
}

template <typename T>
void LinkedListStack<T>::push(const T& elem) {
    // TO DO: Implement push
    Node<T>* n = new Node<T>(elem);
    n->next = top;
    top = n;
    ++this->length;
}

template <typename T>
void LinkedListStack<T>::rotate(typename Stack<T>::Direction dir) {
    // TO DO: Implement rotate
    if (this->length <= 1) return;

    if (dir == Stack<T>::LEFT) {
        Node<T>* first = top;
        top = top->next;
        first->next = nullptr;
        Node<T>* tail = top;
        while (tail->next != nullptr) tail = tail->next;
        tail->next = first;
    } else if (dir == Stack<T>::RIGHT) {
        Node<T>* prev = nullptr;
        Node<T>* curr = top;
        while (curr->next != nullptr) {
            prev = curr;
            curr = curr->next;
        }
        if (prev != nullptr) {
            prev->next = nullptr;
            curr->next = top;
            top = curr;
        }
    } else {
        throw string("rotate: error, unknown direction");
    }
}

template <typename T>
void LinkedListStack<T>::print() {
    cout << "LinkedListStack contents: ";
    if (isEmpty()) {
        cout << "Stack is empty, no elements to display.\n";
    }
    else {
        Node<T> *curr = top;
        while (curr != nullptr){
            cout <<  curr->data  << "\t";
            curr = curr->next;
        }
    }
    cout << endl;
}

