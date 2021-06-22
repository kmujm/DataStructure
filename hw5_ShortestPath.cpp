////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  박정민
// Student ID : 20203074
// Program ID : HW#5
// Description : v0에서 Graph의 다른 모든 정점까지의 최소비용경로
// Algorithm : Graph를 비용 인접 행렬로 표현하여 v0에서 다른 모든 정점까지의 최소비용경로를 구한다.
// Variables :
// class    - Graph : 
//				function - printMatrix() : 비용 인접 행렬(costMatrix)를 출력해주는 함수
//						 - choose() : 최소비용 노드(정점)을 찾아주는 함수 (거쳐가지 않은 정점들 중에 가장 비용이 적은 정점을 찾아줌)
//						 - shortestPath() : 
//						 - printDist() : dist[]를 출력 // v0에서 각 정점까지의 최소비용를 출력
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <iostream>
#include <iomanip>
using namespace std;

#define max 999
#define maxn 6

int costMatrix1[maxn][maxn] = {
	{0, 50, 10, max, 45, max},
	{max, 0, 15, max, 10, max},
	{20, max, 0, 15, max, max},
	{max, 20, max, 0, 35, max},
	{max, max, max, 30, 0, max},
	{max, max, max, 3, max, 0}
};

int costMatrix2[maxn][maxn] = {
	{0, 3, 5, 9, max, max},
	{3, 0, 3, 4, 7, max},
	{5, 3, 0, 2, 6, 8},
	{9, 4, 2, 0, 2, 2},
	{max, 7, 6, 2, 0, 5},
	{max, max, 8, 2, 5, 0}
};

class Graph {
private :
	int found[maxn] = { 0 }; //노드(정점)의 방문 여부를 표기 
	int dist[maxn] = { 0 }; // v0에서 각 노드(정점)까지의 비용를 표기
	int minnode;
public:
	Graph() { ; }
	void printMatrix(int matrix[][maxn]); // 비용 인접 행렬을 출력해주는 함수
	int choose();
	void shortestPath(int v, int matrix[][maxn]);
	void printDist();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : printMatrix()
// description : 인자로 넘겨 받은 matrix(costMatrix)를 출력해주는 함수
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::printMatrix(int matrix[][maxn]) {
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++) {
			cout << setw(8) << matrix[i][j];
		}
		cout << endl;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : choose()
// description : 최소비용 노드(정점)을 찾아주는 함수 (거쳐가지 않은 정점들 중에 가장 비용이 적은 정점을 찾아줌)
// variables : - minnode : 찾은 노드(정점)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Graph::choose(){
	int min = 999;

	for (int i = 0; i < maxn; i++) {
		if (dist[i] <= min && !found[i]) { // 거쳐가지 않은 정점들 중에 가장 비용이 적은 정점을 찾아준다.
			minnode = i;
			min = dist[i];
		}
	}
	return minnode;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : shortestPath()
// description : v0(시작점)에서 각 정점까지의 최소비용을 구해주는 함수 // dist[]에서 최소비용인 정점u를 찾아서(choose함수) 정점u를 거쳐 가는 최소비용을 dist[]에 갱신해준다. 
//				 이 과정을 반복하면 v0(시작점)에서 각 정점까지의 최소비용을 찾을 수 있다.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::shortestPath(int v, int matrix[][maxn]) {
	cout << "Beginning Dist:" << setw(8);
	for (int i = 0; i < maxn; i++) {
		dist[i] = matrix[v][i];
	}

	printDist(); // 최초 상태 출력, costMatrix의 0행 // v0(시작점)에서의 직접 연결 정점들
	cout << endl;

	found[v] = 1; //v0(시작점) mark
	dist[v] = 0; //v0(시작점)에서 v0(시작점)까지의 최소비용 0
	
	for(int i = 0; i < maxn - 1; i ++){ 
		int u = choose(); // 최소 비용인 정점을 찾아서 u에 할당
		found[u] = 1; //정점u 방문 mark


		for (int w = 0; w < maxn; w++) {
			if (found[w] == 0) { // mark하지 않은 정점이라면 // 아직 방문하지 않은 정점이라면
				if (dist[u] + matrix[u][w] < dist[w]) //"v0(시작점)에서 찾은 정점u까지의 비용 + u에서 w정점까지의 비용" 과 "v0(시작점)에서 정점w까지의 비용" 비교
					dist[w] = dist[u] + matrix[u][w]; // u정점을 거쳐 오는 것이 더 비용이 적으면 v0(시작점)에서 정점w까지의 최소비용 값을 변경
			}
		}
		cout << "Select :  (" << u << ")  dist:"; //v0에서 정점u를 거쳐오는 것이 비용이 더 적음을 도출하였으므로 출력
		printDist();
	}

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function :printDist()
// description : dist[]를 출력 // v0에서 각 정점까지의 최소비용을 출력
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Graph::printDist() {
	for (int i = 0; i < maxn; i++) {
		cout << setw(5) << dist[i];
	}
	cout << endl;
}

int main() {
	Graph G, G2;
	cout << "***** Adjacency matrix *****" << endl << endl;
	G.printMatrix(costMatrix1);
	cout << endl << endl << "***** Shortest Path *****" << endl << endl;
	G.shortestPath(0, costMatrix1);

	cout << endl << endl << "***** Adjacency matrix *****" << endl << endl;
	G2.printMatrix(costMatrix2);
	cout << endl << endl << "***** Shortest Path *****" << endl << endl;
	G2.shortestPath(0, costMatrix2);
}