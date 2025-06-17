
#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {}

    void insertionAtHead(int val) {
        Node* newNode = new Node(val);
        newNode->next = head;
        head = newNode;
    }

    void deletionAtHead() {
        if (head == nullptr) return;
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    void insertionAtLast(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr)
            temp = temp->next;
        temp->next = newNode;
    }

    void deletionAtLast() {
        if (head == nullptr) return;
        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            return;
        }
        Node* temp = head;
        while (temp->next->next != nullptr)
            temp = temp->next;
        delete temp->next;
        temp->next = nullptr;
    }

    void insertAfter(int key, int val) {
        Node* temp = head;
        while (temp != nullptr && temp->data != key)
            temp = temp->next;
        if (temp == nullptr) return;
        Node* newNode = new Node(val);
        newNode->next = temp->next;
        temp->next = newNode;
    }

    void traverse() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    bool search(int key) {
        Node* temp = head;
        while (temp != nullptr) {
            if (temp->data == key) return true;
            temp = temp->next;
        }
        return false;
    }

    void deleteByKey(int key) {
        if (head == nullptr) return;
        if (head->data == key) {
            Node* temp = head;
            head = head->next;
            delete temp;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr && temp->next->data != key)
            temp = temp->next;
        if (temp->next == nullptr) return;
        Node* delNode = temp->next;
        temp->next = delNode->next;
        delete delNode;
    }
};

int main() {
    LinkedList list;
    int choice, val, key;

    do {
        cout << "\nMenu:\n1. Insert at Head\n2. Delete at Head\n3. Insert at Last\n4. Delete at Last\n5. Insert After Key\n6. Traverse\n7. Search\n8. Delete by Key\n9. Exit\nEnter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value: ";
            cin >> val;
            list.insertionAtHead(val);
            break;
        case 2:
            list.deletionAtHead();
            break;
        case 3:
            cout << "Enter value: ";
            cin >> val;
            list.insertionAtLast(val);
            break;
        case 4:
            list.deletionAtLast();
            break;
        case 5:
            cout << "Enter key after which to insert: ";
            cin >> key;
            cout << "Enter value: ";
            cin >> val;
            list.insertAfter(key, val);
            break;
        case 6:
            list.traverse();
            break;
        case 7:
            cout << "Enter key to search: ";
            cin >> key;
            cout << (list.search(key) ? "Found\n" : "Not Found\n");
            break;
        case 8:
            cout << "Enter key to delete: ";
            cin >> key;
            list.deleteByKey(key);
            break;
        case 9:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice" << endl;
        }
    } while (choice != 9);

    return 0;
}
