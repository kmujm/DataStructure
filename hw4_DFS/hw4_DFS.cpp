////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  박정민
// Student ID : 20203074
// Program ID : HW#4
// Description : 인접 리스트로 구성된 그래프의 DFS Graph Search
// Algorithm : 각 정점에 대해 1개의 연결 리스트가 존재하고 깊이 우선 탐색을 한다.
// Variables :
// class    - Node : data와 link
//			- AdjList : 
//				function - print_node() : node를 프린트해주는 함수
//						 - buildList() : buffer에서 읽어온 데이터로 연결 리스트를 만들어주는 함수
//						 - dfs() : 깊이 우선탐색 함수
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
	int visited[10]; // 초기값은 0, 방문 시 1
public :
	AdjList() {
		for (int i = 0; i < 10; i++) { //초기화
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
// description : 인접 리스트로 구성된 그래프를 출력해준다.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::print_node() {
	for (int i = 0; i < 10; i++) {
		if (graph[i] != NULL) { //정점이 존재할때
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
// description : buffer에서 읽어온 값으로 연결 리스트를 생성한다.
// variables : - temp : buffer의 값을 할당
//			   - head : head Node / t : next Node
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::buildList(char* buffer, int line) {
	int i = 0;
	int temp = buffer[i] - '0'; // bufer가 char type이므로 int타입으로 변환하여 temp에 할당한다.
	Node* head = new Node(temp); // head Node 생성
	graph[line] = head; // 

	Node* q;
	q = head;
	while (buffer[++i] != '\0') { //인접한 모든 노드들을 single list로 생성
		temp = buffer[i] - '0'; // bufer가 char type이므로 int타입으로 변환하여 temp에 할당한다.
		Node* t = new Node(temp); // next Node 생성
		q->link = t; // 이전 노드에 next Node연결
		q = q->link; // 다음 노드를 현재 노드로 변경
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : dfs()
// description : 깊이 우선탐색 함수 : 루트 노드에서 시작해서 다음 분기로 넘어가기 전에 해당 분기를 완벽하게 탐색하는 방법
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AdjList::dfs(int v) {
	Node* w;
	visited[v] = 1; //정점v 방문 표시
	cout << v << " -> ";
	for (w = graph[v]; w != NULL; w = w->link) { //w와 인접한 노드들을 차례로 순회하고 인접한 노드가 없으면 종료한다.
		if (!visited[w->data]) dfs(w->data); //정점 w를 방문하지 않았으면 dfs(w)를 호출
	}
}

int main() {
	AdjList G1;
	int line = 0;

	char buffer[80]; //데이터를 읽어올 버퍼
	ifstream infile;
	infile.open("graph1.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile.getline(buffer, 80)) { //graph1.txt 데이터를 한줄씩 읽어서 List를 생성
		G1.buildList(buffer, line);
		line++;
	}
	cout << "<<	Graph data 1	>>" << endl << endl;
	G1.print_node(); 
	cout << endl << "depth first search result:" << endl;
	G1.dfs(0);

	AdjList G2;
	line = 0;

	char buffer2[80]; //데이터를 읽어올 버퍼
	ifstream infile2;
	infile2.open("graph2.txt", ios::in);
	if (infile2.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile2.getline(buffer2, 80)) { //graph2.txt 데이터를 한줄씩 읽어서 List를 생성
		G2.buildList(buffer2, line);
		line++;
	}
	cout << endl << endl << "<<	Graph data 2	>>" << endl << endl;
	G2.print_node();
	cout << endl << "depth first search result:" << endl;
	G2.dfs(0);


	return 0;
}