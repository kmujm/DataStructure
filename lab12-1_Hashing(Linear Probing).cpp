/////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab12-1
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

#define MaxSize 7

int HASH(int key) { return (key % MaxSize); }

struct Node {
	int data = NULL;
	bool empty = true;
	friend class Htable;
} HashTable[MaxSize];


int findKey(int key) {
	int index = HASH(key);
	int start = 0;
	int found = false;
	int loop = false;

	while ((HashTable[index].empty == false) && (found == false) && (loop == false)) {
		if (HashTable[index].data == key)
			found = true;
		else {
			index = (index + 1) % MaxSize;
			if (index == start) loop = true;
		}
	}
	return found;
}

int insertKey(int key) {
	int index = HASH(key);
	int check = findKey(key);

	if (check) return false;
	else {
		while (!HashTable[index].empty) {
			index = (index + 1) % MaxSize;
		}
		HashTable[index].data = key;
		HashTable[index].empty = false;
	}
	return true;
}

int deleteKey(int key) {
	int check = findKey(key);
	if (!check) {
		cout << " key is not found" << endl;
		return false;
	}
	else {
		int index = HASH(key);
		while (HashTable[index].data != key) {
			index = (index + 1) % MaxSize;
		}
		HashTable[index].data = NULL;
		HashTable[index].empty = true;
		return true;
	}
}

void printTable() {
	for (int i = 0; i < MaxSize; i++) {
		cout << "HashT[" << i << "] : ";
		if (HashTable[i].data == NULL) cout << "-" << endl;
		else cout << HashTable[i].data << endl;
	}
}

int main() {
	char choice;
	int key;
	
	while (1) {
		cout << "Enter command (i, f, d, q)";
		cin >> choice;
		switch (choice) {
		case 'i':
			cout << "Enter key ";
			cin >> key;
			insertKey(key);
			printTable();
			break;
		case 'f':
			cout << "Enter key ";
			cin >> key;
			if (findKey(key)) cout << "Key is Found\n";
			else cout << "Key Not Found\n";
			printTable();
			break;
		case 'd':
			cout << "Enter key ";
			cin >> key;
			deleteKey(key);
			printTable();
			break;
		case 'q':
			return 0;
		}
	}

}