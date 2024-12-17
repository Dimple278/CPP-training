#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

template <typename T>
class LinkedList {
public:
    ~LinkedList() {
        clear();
    }

    void insert(const T& value) {
        Node<T>* newNode = new Node<T>;
        newNode->data = value;
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
    }

    void clear() {
        Node<T>* current = head;
        while (current != nullptr) {
            Node<T>* next = current->next;
            cout << "Deleting: " << current->data << endl;
            delete current;
            current = next;
        }
        head = tail = nullptr;
    }

    template <typename U>
    friend ostream& operator<<(ostream& os, const LinkedList<U>& list);

private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
};

template <typename T>
ostream& operator<<(ostream& os, const LinkedList<T>& list) {
    Node<T>* current = list.head;
    while (current != nullptr) {
        os << current->data;
        if (current->next != nullptr) os << " -> ";
        current = current->next;
    }
    os << endl;
    return os;
}

int main() {
    LinkedList<string> list;
    list.insert("a");
    list.insert("b");
    list.insert("c");
    list.insert("d");
    list.insert("e");
    list.insert("f");

    cout << list;

    return 0;
}
