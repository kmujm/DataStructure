////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  박정민
// Student ID : 20203074
// Program ID : HW#3
// Description : Doubly Linked List의 여러 함수들을 구현한다.
// Algorithm : Node에 rlink와 llink 주소를 저장하여 Node끼리 연결시켜 새로운 Node를 추가, 삭제하고 현재 노드를 삭제하고 currnet의 위치를 변경하거나 current의 data를 변경한다. 
// Variables :
// class    - Node : data와 rlink(next)와 llink(prev)의 주솟값을 담을 수 있는 Node
//			- List : 
//				function - insertAfter() : 새로운 Node를 current뒤에 추가해주는 함수
//						 - insertBefore() : 새로운 Node를 current앞에 추가해주는 함수
//						 - insertFirst() : 새로운 Node를 list의 제일 앞에 추가해주는 함수
//						 - insertLast() : 새로운 Node를 list의 제일 뒤에 추가해주는 함수
//						 - deleteCurrent() : current Node를 삭제해주는 함수
//						 - locateCurrent() : current의 위치를 변경해주는 함수
//						 - updateCurrent() : current의 data를 갱신해주는 함수
//						 - displayList() : list를 출력해주는 함수
//						 - listLength() : Node의 개수(list의 길이)를 반환해주는 함수
//                       - isEmpty() : list가 비어있는지 확인해주는 함수
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
// description : 새로운 Node(temp)를 current의 Node뒤에 추가해 줌
// variables =>  temp : 새로운 노드 / current : 가장 최근에 수정한 Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertAfter(int data) {
	Node* temp = new Node(data); // 새로운 노드를 생성하고 data값을 넣어준다.

	if (head == NULL) head = temp; // list에 아직 아무 Node가 추가되어 있지 않을 때
	else if (current->next != 0) { // current Node가 제일 마지막 Node가 아닐 때 (current의 rlink가 NULL이 아닐 때)
		temp->next = current->next; //current rlink를 temp의 rlink에 할당 => temp -> current next Node 1)
		temp->prev = current; // temp의 llink에 current를 할당 => current <- temp 2)
		current->next->prev = temp; //current의 다음 Node의 llink에 temp를 할당 => temp <- current next Node 3)
		current->next = temp; // current의 rlink에 temp를 할당 => current -> temp 4)
	} // ==> current <->(2,4) temp(new current) <->(1,3) current next Node
	else { // current Node가 마지막 Node일 때 (current의 rlink가 NULL)
		current->next = temp; // current의 rlink에 temp를 할당 => current -> temp
		temp->prev = current; // temp의 llink에 current 할당 => current <- temp
	} // current <-> temp(new current)
	current = temp; // current를 temp로 변경
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertBefore()
// description : 새로운 Node(temp)를 current의 Node앞에 추가해 줌
// variables =>  temp : 새로운 노드 / current : 가장 최근에 수정한 Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertBefore(int data) {
	Node* temp = new Node(data); // 새로운 노드를 생성하고 data값을 넣어준다.

	if (head == NULL) head = temp; // list에 아직 아무 Node가 추가되어 있지 않을 때
	else if (current == head) {  // current Node가 제일 첫 Node일 때
		temp->next = head; // temp의 rlink에 head Node를 할당 => temp -> head
		head->prev = temp; // head의 link에 temp를 할당 => temp <- head
		head = temp; // head를 temp로 변경
	} // temp(new head, current) <-> head
	else { // current Node가 제일 첫 Node가 아닐 때
		temp->next = current; // temp의 rlink에 current를 할당 => temp -> current 1)
		temp->prev = current->prev; // temp의 llink에 current의 전 Node를 할당 => current prev Node <- temp 2)
		current->prev->next = temp; // current의 전 Node의 rlink에 temp를 할당 => current prev Node -> temp 3)
		current->prev = temp; // current의 llink에 temp를 할당 => temp <- current 4)
	} // current prev Node <->(2,3) temp(new current) <->(1,4) current
	current = temp; // curent를 temp로 변경
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertFirst()
// description : 새로운 Node(temp)를 list의 제일 처음에 추가해 줌
// variables =>  temp : 새로운 노드 / current : 가장 최근에 수정한 Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertFirst(int data) {
	Node* temp = new Node(data);  // 새로운 노드를 생성하고 data값을 넣어준다.

	if (head == NULL) head = temp; // list에 아직 아무 Node가 추가되어 있지 않을 때
	else { // list에 다른 Node가 추가되어 있을 때
		temp->next = head; // temp의 rlink에 head Node를 할당 => temp -> head
		head->prev = temp; // head의 llinkn에 temp를 할당 => temp <- head
		head = temp; // head를 temp로 변경 => temp(new head, new current) <-> head
	}
	current = temp; // current를 temp(new head)로 변경
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : insertLast()
// description : 새로운 Node(temp)를 list의 제일 마지막에 추가해 줌
// variables =>  temp : 새로운 노드 / current : 가장 최근에 수정한 Node 
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::insertLast(int data) {
	Node* temp = new Node(data); // 새로운 노드를 생성하고 data값을 넣어준다.
	Node* p; // 임시 포인터

	if (head == NULL) head = temp; // list에 아직 아무 Node가 추가되어 있지 않을 때
	else { // list에 다른 Node가 추가되어 있을 때
		p = head; // 임시 포인터 p에 head를 할당
		while (p->next != 0) p = p->next; //p가 가르키는 Node의 다음 Node가 존재할 때 p에 p의 다음 Node를 할당해준다. 
		p->next = temp; // 마지막 Node까지 p가 움직여온 뒤 p의 rlink에 temp를 할당 => p(last Node) -> temp
		temp->prev = p; // temp의 llink에 p를 할당 => p(last Node) <- temp
	} // p(last Node) <-> temp(new last Node, new current)
	current = temp; // current를 temp(new last)로 변경
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : deleteCurrent()
// description : currnet Node를 삭제해 줌
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::deleteCurrent() {
	Node* p;

	if (head == NULL) cout << "List is empty!" << endl; // List가 비어있을 때
	else { // List가 비어있지 않을 때
		p = current; // 임시 포인터 p에 current를 할당
		if (head == current) { // current가 제일 처음 Node일 때
			head = head->next; // head에 head의 다음 Node를 할당 => head next Node(new head)
			current = current->next; // current(head)에 current의 다음 Node(head의 다음 Node)를 할당 => head next Node(new head, new current)
			current->prev = 0; // currnet의 llink에 NULL을 할당 
		}
		else if (current->next == 0){ // current가 제일 마지막 Node일 때
			current->prev->next = 0; // current의 이전 노드의 rlink에 NULL을 할당 => current prev Node(new last)
			current = head; // current를 제일 첫 노드로 변경 => head(new current)
		}
		else { // 이외의 경우
			current->next->prev = current->prev; // current 다음 노드의 llink에 current 이전 노드를 할당 => current prev Node <- current next Node
			current->prev->next = current->next; // currnet 이전 노드의 rlink에 current 다음 노드를 할당 => current prev Node -> current next Node
			current = current->next; // current를 curent의 다음 노드로 변경 current next Node(new current)
		} // current prev Node <-> current next Node(new current)
		delete p; // p Node(current Node)삭제
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : locateCurrent()
// description : current의 위치를 변경해 줌
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::locateCurrent(int Nth) {
	Node* p;
	int pos = 1;

	if (head == NULL) cout << "List is empty!" << endl;
	else if (listLength() >= Nth) { // 바꾸고 싶은 위치 값 Nth을 받아 이 값이 list의 길이보다 작은 값인지 확인
		p = head; // Nth번 째 Node까지 p노드로 찾아감
		while (pos != Nth) {
			p = p->next;
			pos++;
		}
		current = p; // current 노드를 p 노드(Nth)번째 노드로 변경
		cout << pos << "*";
		cout << setw(8) << current->val << endl;
	}
	else cout << "No such a line" << endl; // Nth 값이 list 길이보다 큰 값일 때
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : updateCurrent()
// description : current의 data값을 변경해 줌
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void List::updateCurrent(int data) {
	current->val = data;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : displayList()
// description : List를 출력해 줌
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
// description : List의 길이를 구해줌(List 안의 Node의 갯수)
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