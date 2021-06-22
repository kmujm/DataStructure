/////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab11
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
using namespace std;

#define max 100
#define maxn 7

int cost1[maxn][maxn] = {
	{0, 0, 0, 0, 0, 0, 0},
	{0, max, 6, 1, 5, max, max},
	{0, 6, max, 4, max, 3, max},
	{0, 1, 4, max, 5, 6, 5 },
	{0, 5, max, 5, max, max, 2},
	{0, max, 3, 6, max, max, 6},
	{0, max, max, 5, 2, 6, max}
};


class Graph {
private:
	int total = 0;
	int closet;
	int lowcost[maxn] = { 0 };
public:
	Graph() { ; }
	~Graph() { ; }
	void display();
	void PrimeMST(int);
};

void Graph::display() {
	cout << "    ";
	for (int i = 1; i < maxn; i++)
		cout << setw(4) << "v" << i;
	cout << endl;
	for (int i = 1; i < maxn; ++i) {
		cout << setw(5) << "v" << i;
		for (int j = 1; j < maxn; ++j)
			cout << setw(5) << cost1[i][j];
		cout << endl;;
	}
}

void Graph::PrimeMST(int v) {
	for (int i = 1; i < maxn; i++) {
		lowcost[i] = cost1[v][i];
	}
	closet = v;

	for (int i = 1; i < maxn - 1; i++) { // MST will have maxn vertices 
		int min = lowcost[i];
		int k = i;
		for (int j = 1; j < maxn; j++) {
			if (lowcost[j] < min) {
				min = lowcost[j];
				k = j;
			}
		}

		cout << closet << " , " << k << endl;
		total = total + lowcost[k];
		lowcost[k] = max;
		cost1[k][closet] = max;
		cost1[closet][k] = max;

		for (int j = 1; j < maxn; j++) {
			if (cost1[k][j] < lowcost[j] && lowcost[j] <= max) {
				lowcost[j] = cost1[k][j];
				closet = k;
			}
		}
	}
	cout << "Total = " << total << endl;
}

int main() {
	Graph G;
	cout << "**** Weighted Graph ****" << endl;
	G.display();
	cout << endl << "**** Minimal Spanning Tree ****" << endl;
	G.PrimeMST(1);
	return 0;
}