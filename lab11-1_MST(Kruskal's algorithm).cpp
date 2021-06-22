///////////////////////////////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab11-1
////////////////////////////////////////////////////////////////////////////////
#include <iostream>
using namespace std;

#define max 10

char DataList[max][3] = {
	{'A', '6', 'B'},
	{'B', '7', 'C'},
	{'A', '1', 'C'},
	{'A', '5', 'D'},
	{'C', '5', 'D'},
	{'B', '3', 'E'},
	{'C', '8', 'E'},
	{'C', '4', 'F'},
	{'D', '2', 'F'},
	{'E', '9', 'F'}
};

class Node {
	char data;
	int cost;
	char data2;
	Node* next;
	friend class Graph;
};

Node graph[max];

class Graph {
private:
	int visited[max] = { 0 };
	int total = 0;
	int edge;
	Node* head;
public:
	Graph(int);
	~Graph() { ; }
	void InsertData();
	void SortedData();
	bool CheckCycle();
	void KruskalAlgorithm();
	void PrintTotalCost();
	void PrintData();
};

Graph::Graph(int num) {
	head = NULL;
	edge = num;
}

void Graph::InsertData() {
	for (int i = 0; i < max; i++) {
		graph[i].data = DataList[i][0];
		graph[i].cost = DataList[i][1] - '0';
		graph[i].data2 = DataList[i][2];
	}
}

void Graph::SortedData() {
	for (int i = 0; i < max - 1; i++) {
		for (int j = 0; j < max - 1; j++) {
			if (graph[j].cost > graph[j + 1].cost) {
				Node tmp = graph[j];
				graph[j] = graph[j + 1];
				graph[j + 1] = tmp;
			}
		}
	}
}
bool Graph::CheckCycle() {
	int i = 0;

	Node* p = head;
	int count = 0;
	while (p) {
		p = p->next;
		count++;
	}
	if (count == edge - 1) return true;
	else return false;
}

void Graph::KruskalAlgorithm() {
	SortedData();
	int index = 0;
	Node* temp;
	int i = 0;

	while (i < 5) {
		if (!CheckCycle()) {
			cout << "Edge " << i + 1 << ":	";
			cout << graph[i].data << " " << graph[i].cost << " "<< graph[i].data2 << endl;
			total = total + graph[i].cost;
			i++;
		}

	}
}

void Graph::PrintTotalCost() {
	cout << total << endl;
}

void Graph::PrintData() {
	for (int i = 0; i < max; i++) {
		cout << graph[i].data << " " << graph[i].cost << " " << graph[i].data2 << "\t";
		if (i % 5 == 4) cout << endl;
	}
}

int main() {
	Graph G(6);

	cout << "<< MST by Kruscal's >> " << endl << endl;
	cout << "1. Input Data : " << endl;
	G.InsertData();
	G.PrintData();
	cout << endl;

	cout << "2. Sorted Data : " << endl;
	G.SortedData();
	G.PrintData();
	cout << endl;

	cout << "3. Minimum Spanning Tree : " << endl;
	G.KruskalAlgorithm();
	cout << "\n4. Total Cost : ";
	G.PrintTotalCost();
	return 0;
}