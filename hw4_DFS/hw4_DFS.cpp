////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  ������
// Student ID : 20203074
// Program ID : HW#4
// Description : ���� ����Ʈ�� ������ �׷����� DFS Graph Search
// Algorithm : �� ������ ���� 1���� ���� ����Ʈ�� �����ϰ� ���� �켱 Ž���� �Ѵ�.
// Variables :
// class    - Node : data�� link
//			- AdjList : 
//				function - print_node() : node�� ����Ʈ���ִ� �Լ�
//						 - buildList() : buffer���� �о�� �����ͷ� ���� ����Ʈ�� ������ִ� �Լ�
//						 - dfs() : ���� �켱Ž�� �Լ�
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
using namespace std;

class Node {
private:
	int data;
	Node* link;
	Node(int value) { data = value; link = 0; }
friend class AdjList;
};

class AdjList {
private :
	Node* graph[10];
	int visited[10]; // �ʱⰪ�� 0, �湮 �� 1
public :
	AdjList() {
		for (int i = 0; i < 10; i++) { //�ʱ�ȭ
			graph[i] = NULL;
			visited[i] = 0;
		}
	};
	void print_node();
	void buildList(char*, int);
	void dfs(int);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : print_node()
// description : ���� ����Ʈ�� ������ �׷����� ������ش�.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::print_node() {
	for (int i = 0; i < 10; i++) {
		if (graph[i] != NULL) { //������ �����Ҷ�
			Node* p = graph[i];
			cout << "  graph[" << i << "] -> ";
			p = p->link;
			for (p; p != NULL; p = p->link) cout << p->data << " ";
			cout << endl;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : buildList()
// description : buffer���� �о�� ������ ���� ����Ʈ�� �����Ѵ�.
// variables : - temp : buffer�� ���� �Ҵ�
//			   - head : head Node / t : next Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::buildList(char* buffer, int line) {
	int i = 0;
	int temp = buffer[i] - '0'; // bufer�� char type�̹Ƿ� intŸ������ ��ȯ�Ͽ� temp�� �Ҵ��Ѵ�.
	Node* head = new Node(temp); // head Node ����
	graph[line] = head; // 

	Node* q;
	q = head;
	while (buffer[++i] != '\0') { //������ ��� ������ single list�� ����
		temp = buffer[i] - '0'; // bufer�� char type�̹Ƿ� intŸ������ ��ȯ�Ͽ� temp�� �Ҵ��Ѵ�.
		Node* t = new Node(temp); // next Node ����
		q->link = t; // ���� ��忡 next Node����
		q = q->link; // ���� ��带 ���� ���� ����
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : dfs()
// description : ���� �켱Ž�� �Լ� : ��Ʈ ��忡�� �����ؼ� ���� �б�� �Ѿ�� ���� �ش� �б⸦ �Ϻ��ϰ� Ž���ϴ� ���
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::dfs(int v) {
	Node* w;
	visited[v] = 1; //����v �湮 ǥ��
	cout << v << " -> ";
	for (w = graph[v]; w != NULL; w = w->link) { //w�� ������ ������ ���ʷ� ��ȸ�ϰ� ������ ��尡 ������ �����Ѵ�.
		if (!visited[w->data]) dfs(w->data); //���� w�� �湮���� �ʾ����� dfs(w)�� ȣ��
	}
}

int main() {
	AdjList G1;
	int line = 0;

	char buffer[80]; //�����͸� �о�� ����
	ifstream infile;
	infile.open("graph1.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile.getline(buffer, 80)) { //graph1.txt �����͸� ���پ� �о List�� ����
		G1.buildList(buffer, line);
		line++;
	}
	cout << "<<	Graph data 1	>>" << endl << endl;
	G1.print_node(); 
	cout << endl << "depth first search result:" << endl;
	G1.dfs(0);

	AdjList G2;
	line = 0;

	char buffer2[80]; //�����͸� �о�� ����
	ifstream infile2;
	infile2.open("graph2.txt", ios::in);
	if (infile2.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile2.getline(buffer2, 80)) { //graph2.txt �����͸� ���پ� �о List�� ����
		G2.buildList(buffer2, line);
		line++;
	}
	cout << endl << endl << "<<	Graph data 2	>>" << endl << endl;
	G2.print_node();
	cout << endl << "depth first search result:" << endl;
	G2.dfs(0);


	return 0;
}