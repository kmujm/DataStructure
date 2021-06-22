/////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab12
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define MaxSize 7

int HASH(int key) { return (key % MaxSize); }

class Node {
	int data;
	Node* link;
	friend class Htable;
};

class Htable {
private :
	Node* HashTable[MaxSize];
public:
	Htable() {
		for (int i = 0; i < MaxSize; i++) HashTable[i] = NULL;
	}
	int findKey(int);
	int insertKey(int);
	int deleteKey(int);
	void printTable();
};

int Htable::findKey(int key) {
	int index = HASH(key);
	Node* p = HashTable[index];
	Node* q = NULL;

	if (p == NULL) return false;
	else {
		q = p;
		while ((q != NULL) && (q->data != key)) {
			q = q->link;
		}
		if (q == NULL) return false;
		else return true;
	}
}

int Htable::insertKey(int key) {
	int index = HASH(key);
	int check = findKey(key);

	if (check) return false;
	else {
		Node* q = new Node();
		q->data = key;
		Node* p;
		Node* r;
		
		if (HashTable[index] == NULL) HashTable[index] = q;
		else {
			r = HashTable[index];
			p = r;
			while (p->link != NULL) p = p->link;
			p->link = q;

		}
	}
}

int Htable::deleteKey(int key) {
	int check = findKey(key);
	if (!check) {
		cout << " key is not found" << endl;
		return false;
	}
	else {
		int index = HASH(key);


		Node* p = NULL;
		Node* q = NULL;

		if (HashTable[index]->data == key) {
			p = HashTable[index];
			HashTable[index] = HashTable[index]->link;
			delete p;
		}
		else {
			p = HashTable[index];
			q = HashTable[index];
			while (p != NULL && p->data != key) {
				q = p;
				p = p->link;
			}
			if (p != NULL) {
				q->link = p->link;
				delete p;
			}
		}
	}
}

void Htable::printTable() {
	Node* p;
	for (int i = 0; i < MaxSize; i++) {
		cout << "HashT[" << i << "] -> ";
		p = HashTable[i];
		for (p; p != NULL; p = p->link) {
			cout << p->data << "   ";
		}
		cout << endl;
	}
}

int main() {
	Htable H;
	char choice;
	int key;
	while (1) {
		cout << "Enter command (i, f, d, q)";
		cin >> choice;		
		switch (choice) {
		case 'i':
			cout << "Enter key ";
			cin >> key;
			cout << "Hash value " << HASH(key) << endl;
			H.insertKey(key);
			H.printTable();
			break;
		case 'f':
			cout << "Enter key ";
			cin >> key;
			cout << "Hash value " << HASH(key) << "  ";
			if (H.findKey(key)) cout << "Key is Found\n";
			else cout << "Key Not Found\n";
			H.printTable();
			break;
		case 'd':
			cout << "Enter key ";
			cin >> key;
			cout << "Hash value " << HASH(key) << endl;
			H.deleteKey(key);
			H.printTable();
			break;
		case 'q':
			return 0;
		}
	}
	
}