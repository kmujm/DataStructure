////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  ������
// Student ID : 20203074
// Program ID : HW#3
// Description : Doubly Linked List�� ���� �Լ����� �����Ѵ�.
// Algorithm : Node�� rlink�� llink �ּҸ� �����Ͽ� Node���� ������� ���ο� Node�� �߰�, �����ϰ� ���� ��带 �����ϰ� currnet�� ��ġ�� �����ϰų� current�� data�� �����Ѵ�. 
// Variables :
// class    - Node : data�� rlink(next)�� llink(prev)�� �ּڰ��� ���� �� �ִ� Node
//			- List : 
//				function - insertAfter() : ���ο� Node�� current�ڿ� �߰����ִ� �Լ�
//						 - insertBefore() : ���ο� Node�� current�տ� �߰����ִ� �Լ�
//						 - insertFirst() : ���ο� Node�� list�� ���� �տ� �߰����ִ� �Լ�
//						 - insertLast() : ���ο� Node�� list�� ���� �ڿ� �߰����ִ� �Լ�
//						 - deleteCurrent() : current Node�� �������ִ� �Լ�
//						 - locateCurrent() : current�� ��ġ�� �������ִ� �Լ�
//						 - updateCurrent() : current�� data�� �������ִ� �Լ�
//						 - displayList() : list�� ������ִ� �Լ�
//						 - listLength() : Node�� ����(list�� ����)�� ��ȯ���ִ� �Լ�
//                       - isEmpty() : list�� ����ִ��� Ȯ�����ִ� �Լ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
using namespace std;

class Node {
private : 
	int val;
	Node* next;
	Node* prev;
	Node(int data) { val = data; next = 0; prev = 0; }
	friend class List;
};

class List {
private : 
	Node* head;
	Node* current;
public:
	List() {};
	~List() {};
	void insertAfter(int);
	void insertBefore(int);
	void insertFirst(int);
	void insertLast(int);
	void deleteCurrent();
	void locateCurrent(int);
	void updateCurrent(int);
	void displayList();
	int listLength();
	int isEmpty() { return (head == 0); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertAfter()
// description : ���ο� Node(temp)�� current�� Node�ڿ� �߰��� ��
// variables =>  temp : ���ο� ��� / current : ���� �ֱٿ� ������ Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertAfter(int data) {
	Node* temp = new Node(data); // ���ο� ��带 �����ϰ� data���� �־��ش�.

	if (head == NULL) head = temp; // list�� ���� �ƹ� Node�� �߰��Ǿ� ���� ���� ��
	else if (current->next != 0) { // current Node�� ���� ������ Node�� �ƴ� �� (current�� rlink�� NULL�� �ƴ� ��)
		temp->next = current->next; //current rlink�� temp�� rlink�� �Ҵ� => temp -> current next Node 1)
		temp->prev = current; // temp�� llink�� current�� �Ҵ� => current <- temp 2)
		current->next->prev = temp; //current�� ���� Node�� llink�� temp�� �Ҵ� => temp <- current next Node 3)
		current->next = temp; // current�� rlink�� temp�� �Ҵ� => current -> temp 4)
	} // ==> current <->(2,4) temp(new current) <->(1,3) current next Node
	else { // current Node�� ������ Node�� �� (current�� rlink�� NULL)
		current->next = temp; // current�� rlink�� temp�� �Ҵ� => current -> temp
		temp->prev = current; // temp�� llink�� current �Ҵ� => current <- temp
	} // current <-> temp(new current)
	current = temp; // current�� temp�� ����
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertBefore()
// description : ���ο� Node(temp)�� current�� Node�տ� �߰��� ��
// variables =>  temp : ���ο� ��� / current : ���� �ֱٿ� ������ Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertBefore(int data) {
	Node* temp = new Node(data); // ���ο� ��带 �����ϰ� data���� �־��ش�.

	if (head == NULL) head = temp; // list�� ���� �ƹ� Node�� �߰��Ǿ� ���� ���� ��
	else if (current == head) {  // current Node�� ���� ù Node�� ��
		temp->next = head; // temp�� rlink�� head Node�� �Ҵ� => temp -> head
		head->prev = temp; // head�� link�� temp�� �Ҵ� => temp <- head
		head = temp; // head�� temp�� ����
	} // temp(new head, current) <-> head
	else { // current Node�� ���� ù Node�� �ƴ� ��
		temp->next = current; // temp�� rlink�� current�� �Ҵ� => temp -> current 1)
		temp->prev = current->prev; // temp�� llink�� current�� �� Node�� �Ҵ� => current prev Node <- temp 2)
		current->prev->next = temp; // current�� �� Node�� rlink�� temp�� �Ҵ� => current prev Node -> temp 3)
		current->prev = temp; // current�� llink�� temp�� �Ҵ� => temp <- current 4)
	} // current prev Node <->(2,3) temp(new current) <->(1,4) current
	current = temp; // curent�� temp�� ����
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertFirst()
// description : ���ο� Node(temp)�� list�� ���� ó���� �߰��� ��
// variables =>  temp : ���ο� ��� / current : ���� �ֱٿ� ������ Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertFirst(int data) {
	Node* temp = new Node(data);  // ���ο� ��带 �����ϰ� data���� �־��ش�.

	if (head == NULL) head = temp; // list�� ���� �ƹ� Node�� �߰��Ǿ� ���� ���� ��
	else { // list�� �ٸ� Node�� �߰��Ǿ� ���� ��
		temp->next = head; // temp�� rlink�� head Node�� �Ҵ� => temp -> head
		head->prev = temp; // head�� llinkn�� temp�� �Ҵ� => temp <- head
		head = temp; // head�� temp�� ���� => temp(new head, new current) <-> head
	}
	current = temp; // current�� temp(new head)�� ����
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertLast()
// description : ���ο� Node(temp)�� list�� ���� �������� �߰��� ��
// variables =>  temp : ���ο� ��� / current : ���� �ֱٿ� ������ Node 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertLast(int data) {
	Node* temp = new Node(data); // ���ο� ��带 �����ϰ� data���� �־��ش�.
	Node* p; // �ӽ� ������

	if (head == NULL) head = temp; // list�� ���� �ƹ� Node�� �߰��Ǿ� ���� ���� ��
	else { // list�� �ٸ� Node�� �߰��Ǿ� ���� ��
		p = head; // �ӽ� ������ p�� head�� �Ҵ�
		while (p->next != 0) p = p->next; //p�� ����Ű�� Node�� ���� Node�� ������ �� p�� p�� ���� Node�� �Ҵ����ش�. 
		p->next = temp; // ������ Node���� p�� �������� �� p�� rlink�� temp�� �Ҵ� => p(last Node) -> temp
		temp->prev = p; // temp�� llink�� p�� �Ҵ� => p(last Node) <- temp
	} // p(last Node) <-> temp(new last Node, new current)
	current = temp; // current�� temp(new last)�� ����
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : deleteCurrent()
// description : currnet Node�� ������ ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::deleteCurrent() {
	Node* p;

	if (head == NULL) cout << "List is empty!" << endl; // List�� ������� ��
	else { // List�� ������� ���� ��
		p = current; // �ӽ� ������ p�� current�� �Ҵ�
		if (head == current) { // current�� ���� ó�� Node�� ��
			head = head->next; // head�� head�� ���� Node�� �Ҵ� => head next Node(new head)
			current = current->next; // current(head)�� current�� ���� Node(head�� ���� Node)�� �Ҵ� => head next Node(new head, new current)
			current->prev = 0; // currnet�� llink�� NULL�� �Ҵ� 
		}
		else if (current->next == 0){ // current�� ���� ������ Node�� ��
			current->prev->next = 0; // current�� ���� ����� rlink�� NULL�� �Ҵ� => current prev Node(new last)
			current = head; // current�� ���� ù ���� ���� => head(new current)
		}
		else { // �̿��� ���
			current->next->prev = current->prev; // current ���� ����� llink�� current ���� ��带 �Ҵ� => current prev Node <- current next Node
			current->prev->next = current->next; // currnet ���� ����� rlink�� current ���� ��带 �Ҵ� => current prev Node -> current next Node
			current = current->next; // current�� curent�� ���� ���� ���� current next Node(new current)
		} // current prev Node <-> current next Node(new current)
		delete p; // p Node(current Node)����
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : locateCurrent()
// description : current�� ��ġ�� ������ ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::locateCurrent(int Nth) {
	Node* p;
	int pos = 1;

	if (head == NULL) cout << "List is empty!" << endl;
	else if (listLength() >= Nth) { // �ٲٰ� ���� ��ġ �� Nth�� �޾� �� ���� list�� ���̺��� ���� ������ Ȯ��
		p = head; // Nth�� ° Node���� p���� ã�ư�
		while (pos != Nth) {
			p = p->next;
			pos++;
		}
		current = p; // current ��带 p ���(Nth)��° ���� ����
		cout << pos << "*";
		cout << setw(8) << current->val << endl;
	}
	else cout << "No such a line" << endl; // Nth ���� list ���̺��� ū ���� ��
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : updateCurrent()
// description : current�� data���� ������ ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::updateCurrent(int data) {
	current->val = data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : displayList()
// description : List�� ����� ��
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::displayList() {
	Node* p;

	if (head == NULL) cout << "List is empty!" << endl;
	else{
		p = head;
		int pos = 1;
		cout << "---List---" << endl;
		while (p != 0) {
			if (p == current)
				cout << setw(5) << pos << " * " << p->val << endl;
			else 
				cout << setw(5) << pos << " : " << p->val << endl;
			p = p->next;
			pos++;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : listLength()
// description : List�� ���̸� ������(List ���� Node�� ����)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int List::listLength() {
	Node* p = head;
	int len = 0;

	while (p) {
		++len;
		p = p->next;
	}
	return len;
}

void main() {
	List l1;
	int choice, num;

	while (1) {
		cout << "Command : (1)insertAfter	(2)insertBefore		(3)insertFirst	(4)insertLast	(5)deleteCurrent" << endl;
		cout << "          (6)locateCurrent	(7)updateCurrent	(8)displayList	(9)quit" << endl;
		cout << "==> ";
		cin >> choice;
		switch (choice) {
		case 1: cout << "Enter a data to insert => ";
			cin >> num;
			l1.insertAfter(num); l1.displayList(); break;
		case 2: cout << "Enter a data to insert => ";
			cin >> num;
			l1.insertBefore(num); l1.displayList(); break;
		case 3: cout << "Enter a data to insert => ";
			cin >> num;
			l1.insertFirst(num); l1.displayList(); break;
		case 4: cout << "Enter a data to insert => ";
			cin >> num;
			l1.insertLast(num); l1.displayList(); break;
		case 5: l1.deleteCurrent(); l1.displayList(); break;
		case 6: 
			if (!l1.isEmpty()) {
			cout << "Enter a position to locate => ";
			cin >> num;
			l1.locateCurrent(num);
			}
			 else cout << "List is empty!" << endl;
			 break;
		case 7:
			if (!l1.isEmpty()) {
				cout << "Enter a data to update => ";
				cin >> num;
				l1.updateCurrent(num);
				l1.displayList();
			}
			else cout << "List is empty!" << endl;
			break;
		case 8: l1.displayList(); break;
		case 9: exit(1);
		default: cout << "Bad Command" << endl;
		}
	}
}