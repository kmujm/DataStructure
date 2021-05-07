////////////////////////////////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab7
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
using namespace std;

class Node {
private:
	int data;
	Node* next;
	Node(int value) { data = value; next = 0; }
	friend class linkedStack;
	friend class linkedQueue;
	friend class linkedList;
};

class linkedStack {
private:
	Node* top;
public:
	linkedStack() { top = 0; }
	~linkedStack();
	void createStack() { top = 0; }
	void push(int);
	char pop();
	int isEmptyS() { return (top == 0); }
	void displayStack();
};

linkedStack::~linkedStack() {
	Node* p;

	while (top != 0) {
		p = top;
		top = top->next;
		delete p;
	}
}

void linkedStack::push(int data) {
	Node* temp = new Node(data);

	if (top == 0) top = temp;
	else {
		temp->next = top;
		top = temp;
	}
}

char linkedStack::pop() {
	Node* p;
	int num;

	num = top->data;
	p = top;
	top = top->next;
	delete p;
	return num;
}

void linkedStack::displayStack() {
	Node* p;

	if (!isEmptyS()) {
		cout << "Stack : " << endl;
		p = top;
		while (p) {
			cout << p->data << "	";
			p = p->next;
		}
		cout << endl;
	}
	else cout << "Stack is empty!" << endl;
}


class linkedQueue {
private:
	Node* front;
	Node* rear;
public:
	linkedQueue() { front = 0; rear = 0; }
	~linkedQueue() {};
	void createQueue() { front = 0; rear = 0; };
	void enqueue(int);
	char dequeue();
	int isEmptyQ() { return (front == 0); }
	void displayQueue();
};

void linkedQueue::enqueue(int data) {
	Node* temp = new Node(data);

	if (front == 0) {
		front = temp;
		rear = temp;
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}

char linkedQueue::dequeue() {
	Node* p;
	int num;

	num = front->data;
	p = front;

	if (front == rear) { front = 0; rear = 0; }
	else front = front->next;

	delete p;
	return num;
}

void linkedQueue::displayQueue() {
	Node* p;
	if (!isEmptyQ()) {
		p = front;
		while (p) {
			cout << setw(8) << p->data;
			p = p->next;
		}
		cout << endl;
	}
	else cout << "Que is empty!" << endl;
}

class linkedList {
private:
	Node* head;
public:
	linkedList() { head = 0; }
	~linkedList() {};
	int isEmpty() { return head == 0; }
	void insert(int);
	void display();
};

void linkedList::insert(int data) {
	Node* temp = new Node(data);
	Node* p, * q;

	if (head == NULL) head = temp;
	else if (temp->data < head->data) {
		temp->next = head;
		head = temp;
	}
	else {
		p = head; q = head;
		while (p != NULL && p->data < temp->data) {
			q = p;
			p = p->next;
		}if (p != NULL) {
			temp->next = p;
			q->next = temp;
		}
		else q->next = temp;
	}
}

void linkedList::display() {
	Node* p;

	if (head != NULL) {
		cout << "List : ";
		p = head;
		while (p != NULL) {
			cout << setw(8) << p->data;
			p = p->next;
		}
		cout << endl;
	}
	else cout << "List is Empty!" << endl;
}
void main() {
	linkedStack s1;
	linkedQueue Q1;
	linkedList L1;

	int num, choice;
	int stopflag = 1;

	while (stopflag) {
		cout << "MENU : (1.push	2. pop	3.enqueue	4. dequeue	5. Makelist	6.quit) : ";
		cin >> choice;

		switch (choice) {
		case 1: cout << "Input an integer to push => "; cin >> num; s1.push(num); s1.displayStack(); break;
		case 2:
			if (!s1.isEmptyS()) {
				num = s1.pop();
				cout << num << "  ==> is popped!" << endl;
				s1.displayStack();
			}
			else cout << "Stack is empty!" << endl;
		    break;
		case 3:
			cout << "Enter an integer to enque => : ";
			cin >> num;
			Q1.enqueue(num);
			Q1.displayQueue();
			break;
		case 4:
			if (!Q1.isEmptyQ()) {
				num = Q1.dequeue();
				cout << num << "  ==> is dequed." << endl;
				Q1.displayQueue();
			}
			else cout << "Que is empty!" << endl;
			break;
		case 5:
			while (!s1.isEmptyS()) { L1.insert(s1.pop()); }
			while (!Q1.isEmptyQ()) { L1.insert(Q1.dequeue()); }
			L1.display();
			break;
		case 6: stopflag = 0; exit(1); break;
		default: cout << "Bad command" << endl; break;
		}
	}
}