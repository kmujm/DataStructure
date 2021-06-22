////////////////////////////////////////////////////////////////////////////////
// Name : 박정민
// Student ID : 20203074
// Program ID : Lab9
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
using namespace std;

class Heap {
private:
	int* heap;
	int idx;
	int MaxSize;
public:
	Heap(int size) {
		MaxSize = size;
		idx = -1;
		heap = new int[MaxSize + 1];
	}
	void createH(int);
	int HEAP_FULL() { return (idx == MaxSize); }
	int HEAP_EMPTY() { return (idx == -1); }
	void insertHEAP(int);
	void deleteHEAP();
	void searchHEAP(int);
	void printHEAP();
	int levelTest();
	void makeHEAP(int);
	void heapSort(int);
	void adjust(int*, int, int);
};

void Heap::createH(int item) {
	int i = ++idx;
	heap[i] = item;
}

void Heap::insertHEAP(int item) {
	int i;
	if (HEAP_FULL()) {
		cout << "Heap is full...";
		return;
	}
	i = ++idx;
	while ((i != 1) && (item > heap[i / 2])) {
		heap[i] = heap[i / 2];
		i = i / 2;
	}
	heap[i] = item;
}

void Heap::deleteHEAP() {
	int parent, child;
	int item, temp;

	item = heap[1];
	temp = heap[idx--];
	parent = 1;
	child = 2;

	while (child <= idx) {
		if ((child < idx) && (heap[child] < heap[child + 1])) child++;
		if (temp >= heap[child]) break;
		heap[parent] = heap[child];
		parent = child;
		child = child * 2;
	}
	heap[parent] = temp;
}

void Heap::printHEAP() {
	cout << "Heap : ";
	for (int i = 1; i < idx + 1; i++)cout << heap[i] << " ";
	cout << endl << endl;
}

void Heap::searchHEAP(int item) {
	int n;
	if (HEAP_EMPTY()) cout << "Heap is Empty !" << endl;
	else {
		n = 1;
		while (n != idx + 1 && heap[n] != item) ++n;
		if (n != idx + 1) cout << item << " is Found" << endl;
		else cout << "Not Found" << endl;
	}
}

int Heap::levelTest() {
	int level = 0;
	while (MaxSize != 0) {
		MaxSize = MaxSize / 2;
		level++;
	}
	return level;
}

void Heap::makeHEAP(int n) {
	int i;

	for (i = n / 2; i > 0; i--) {
		adjust(heap, i, n);
	}
}
void Heap::heapSort(int n) {
	int temp;
	int cnt = 1;
	while (cnt++ <= idx) {
		for (int i = 0; i < idx; i++) {
			if (heap[i] > heap[i + 1]) {
				temp = heap[i];
				heap[i] = heap[i + 1];
				heap[i + 1] = temp;
			}
		}
	}
}

void Heap::adjust(int* heap, int i, int n) {
	int child;
	child = 2 * i;
	int temp = heap[i];

	while (n >= child) {
		if ((n > child) && (heap[child] < heap[child + 1])) child = child + 1;
		if (temp >= heap[child]) break;
		heap[child / 2] = heap[child];
		child = 2 * child;
	}
	heap[child / 2] = temp;
	return;
}

int main() {
	int sizeH = 11;
	int num, choice;
	int data[11] = { 0, 26, 5, 77, 1, 61, 11, 59, 15, 48, 19 };

	Heap arrH(sizeH);
	for (int i = 0; i < sizeH; i++) {
		arrH.createH(data[i]);
	}	

	while (true) {
		cout << "MENU : 1)Print 2)Search 3)LevelTest 4)MakeHeap 5)Heapsort 6)Delete 7)Insert 8)Quit" << endl;
		cout << "Choice : ";
		cin >> choice;
		switch (choice) {
		case 1:
			arrH.printHEAP();
			break;
		case 2:
			cout << "Enter a number to Search : ";
			cin >> num;
			arrH.searchHEAP(num);
			break;
		case 3:
			cout << "Level of Heap is ";
			cout << arrH.levelTest();
			cout << endl;
			break;
		case 4:
			cout << "Heap 변환 : ";
			arrH.makeHEAP(sizeH);
			arrH.printHEAP();
			break;
		case 5:
			cout << "Sort 결과 : ";
			arrH.heapSort(sizeH);
			arrH.printHEAP();
			break;
		
		case 6:
			arrH.deleteHEAP();
			arrH.printHEAP();
			break;
		case 7:
			cout << "Enter a number to insert : ";
			cin >> num;
			arrH.insertHEAP(num);
			arrH.printHEAP();
			break;
		case 8:
			return 0;

		}
	}
}