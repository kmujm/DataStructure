////////////////////////////////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab6
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>

using namespace std;


class Node {
private : 
    int data;
    Node* next;
    //Node(int value) { data = value; next = 0; }
    friend class List;
};

class List {
private:
    Node* head;
public:
    List() { head = 0; }
    ~List();
    void insertNode(int);
    void deleteNode(int);
    void search(int);
    void displayList();
    void findMax();
};

List::~List() {
    Node* p = NULL;

    while (head != 0) {
        p = head;
        head = head->next;
        delete p;
    }
}

void List::insertNode(int data) {
    Node* temp = new Node;
    temp->data = data;
    temp->next = 0;

    Node* p = NULL;
    Node *q = NULL;

    if (head == NULL) head = temp;
    else if (temp->data < head->data) {
        temp->next = head;
        head = temp;
    }
    else {
        p = head;
        q = head;
        while ((p != 0) && (p->data < temp->data)) {
            q = p;
            p = p->next;
        }
        if (p != 0) {
            temp->next = p;
            q->next = temp;
        }
        else q->next = temp;
    }
}
void List::deleteNode(int num) {
    Node* p = NULL;
    Node *q = NULL;
    if (head->data == num) {
        p = head;
        head = head->next;
        delete p;
    }
    else {
        p = head;
        while (p != NULL && p->data != num) {
            q = p;
            p = p->next;
        }if (p != NULL) {
            q->next = p->next;
            delete p;
        }
        else cout << num << "is not found" << endl;
    }
}

void List::search(int num) {
    Node* p;

    if (head != 0) {
        p = head;
        while (p != 0 && p->data != num)
            p = p->next;
        if (p) cout << p->data << " is found" << endl;
        else cout << num << " is not found" << endl;
    }
    else cout << "List Empty" << endl;
}

void List::findMax() {
    Node* p = NULL;
    Node* max = NULL;
    
    p = head;
    max = head;

    while (p->next != NULL) {
        if (max->data < p->data) max = p;
        p = p->next;
    }
    max = p;

    cout << "Max num is : " << max->data << endl;
}
void List::displayList() {
    Node* p = NULL;

    if (head == NULL) cout << "List is Empty!" << endl;
    else {
        p = head;
        cout << "--- List ---" << endl;
        for (int i = 1; p != 0; i++) {
            cout << setw(5) << i << " : " << p->data << endl;
                p = p->next;
        }
    }
}

int main() {
    List lst;

    int choice, n;
    
    while (true) {
        cout << "Command : 1).insert  2).delete 3).search 4).displayList 5).findMax 6).Quit => ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Input a number : ";
            cin >> n;
            lst.insertNode(n);
            lst.displayList();
            break;
        case 2:
            cout << "Input a number : ";
            cin >> n;
            lst.deleteNode(n);
            lst.displayList();
            break;
        case 3:
            cout << "Input a number : ";
            cin >> n;
            lst.search(n);
            lst.displayList();
            break;
        case 4:
            lst.displayList();
            break;
        case 5:
            lst.findMax();
            lst.displayList();
            break;
        case 6:
            return 0;
            break;
        }
    }
}