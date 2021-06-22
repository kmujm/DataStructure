/////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab10
////////////////////////////////////////////////////////////////////////////////

#include<iostream>
using namespace std;

class Node {
private:
	int data;
	Node* next;
public:
	Node(int value) { data = value; next = 0; }
	friend class Graph;
};

class Graph {
private:
	int size;
	int* visited;
	Node* front;
	Node* rear;
	int visited1[8] = { 0 };
	int visited2[6] = { 0 };

	int ADM1[8][8] = {
		0, 1, 1, 0, 0, 0, 0, 0,
		1, 0, 0, 1, 1, 0, 0, 0,
		1, 0, 0, 0, 0, 1, 1, 0,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 1, 0, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 1, 0, 0, 0, 0, 1,
		0, 0, 0, 1, 1 ,1 ,1 ,0 };

	int ADM2[6][6] = {
		0, 1, 1, 0, 0, 0,
		1, 0, 1, 1, 0, 0,
		1, 1, 0, 0, 0, 1,
		0, 1, 0, 0, 1, 1,
		0, 0, 0, 1, 0, 1,
		0, 0, 1, 1, 1, 0 };
public:
	Graph() { front = 0; rear = 0; }
	~Graph() { ; }
	void printMatrix(int);
	bool isEmpty() { return front == 0; }
	void enQue(int item);
	int deQue();
	void bfs(int, int);
};


void Graph::printMatrix(int size) {
	cout << "    ";
	for (int i = 0; i < size; i++)
		cout << "v" << i << "  ";
	cout << endl;
	if (size == 8) {
		for (int i = 0; i < size; ++i) {
			cout << "v" << i << "   ";
			for (int j = 0; j < size; ++j)
				cout << ADM1[i][j] << "   ";
			cout << endl;;
		}
	}
	else if(size == 6) {
		for (int i = 0; i < size; ++i) {
			cout << "v" << i << "   ";
			for (int j = 0; j < size; ++j)
				cout << ADM2[i][j] << "   ";
			cout << endl;;
		}
	}
}

void Graph::enQue(int item) {
	Node* temp = new Node(item);

	if (isEmpty()) {
		front = temp;
		rear = temp;
	}
	else {
		rear->next = temp;
		rear = temp;
	}
}

int Graph::deQue() {
	Node* p;
	int num;

	if (!isEmpty()) {
		num = front->data;
		p = front;

		if (front == rear) { front = 0; rear = 0; }
		else {
			front = front->next;
		}
		delete p;
		return num;
	}
}

void Graph::bfs(int v, int size) {
	enQue(v);

	while (!isEmpty()) {
		int v = deQue();
		cout << v << "	";
		if (size == 8) {
			visited1[v] = 1;
			for (int i = 0; i < size; i++) {
				if (ADM1[v][i] && !visited1[i]) {
					visited1[i] = 1;
					enQue(i);
				}
			}
		}
		else if(size == 6) {
			visited2[v] = 1;
			for (int i = 0; i < size; i++) {
				if (ADM2[v][i] && !visited2[i]) {
					visited2[i] = 1;
					enQue(i);
				}
			}
		}
	}
}

int main() {
	cout << "************ Adjacency Matrix ************" << endl;
	Graph G;
	G.printMatrix(8);
	cout << "Breadth First Search -> ";
	G.bfs(0, 8);
	cout << endl << "************ Adjacency Matrix ************" << endl;
	Graph G2;
	G2.printMatrix(6);
	cout << "Breadth First Search -> ";
	G2.bfs(0, 6);
}