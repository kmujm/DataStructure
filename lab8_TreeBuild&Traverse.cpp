////////////////////////////////////////////////////////////////////////////////
// Name : ¹ÚÁ¤¹Î
// Student ID : 20203074
// Program ID : Lab8
////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <string>
using namespace std;

char tablePriority[4][2] = { '*', 2, '/', 2, '+', 1, '-', 1 };
int level = 0;

class Node {
private:
	char data;
	Node* left;
	Node* right;
	int priority;
	Node(char value) { data = value; left = 0; right = 0; priority = 4; }
	friend class Tree;
};

class Tree {
public:
	Node* root;
	Tree() { this->root = 0; }
	~Tree() { ; }
	void buildTree(string);
	void insert(char);
	void insertAsOperand(Node*);
	void insertAsOperator(Node*);
	void inOrder(Node*);
	void postOrder(Node*);
	void preOrder(Node*);
	int evaluationPostOrder(Node*);
	void printTree(Node*, int);
};

void Tree::buildTree(string expression) {
	int i = 0;
	while (expression[i] != NULL) {
		insert(expression[i]); i++;
	}
	level = i;
}

void Tree::insert(char data) {
	int i = 0;
	Node* node = new Node(data);

	for (i = 0; i < 4; ++i) {
		if (node->data == tablePriority[i][0]) {
			node->priority = tablePriority[i][1];
			break;
		}
	}
	if (i == 4) insertAsOperand(node);
	else insertAsOperator(node);
}

void Tree::insertAsOperand(Node* node) {
	if (this->root == NULL) { root = node; return; }

	Node* p = root;
	while (p->right != NULL) { p = p->right; }
	p->right = node;
}

void Tree::insertAsOperator(Node* node) {
	if (root->priority >= node->priority) {
		node->left = root;
		root = node;
	}
	else {
		node->left = root->right;
		root->right = node;
	}
}

void Tree::inOrder(Node* node) {
	if (node->left != NULL) inOrder(node->left);
	cout << node->data << " ";
	if (node->right != NULL) inOrder(node->right);
}

void Tree::postOrder(Node* node) {
	if (node->left != NULL) postOrder(node->left);
	if (node->right != NULL) postOrder(node->right);
	cout << node->data << " ";
}

void Tree::preOrder(Node* node) {
	cout << node->data << " ";
	if (node->left != NULL) preOrder(node->left);
	if (node->right != NULL) preOrder(node->right);
}

int Tree::evaluationPostOrder(Node* node) {
	int value = 0;
	int left = 0;
	int right = 0;

	if (node != NULL) {
		if (node->data >= '0' && node->data <= '9') {
			value = node->data - '0';
		}
		else {
			left = evaluationPostOrder(node->left);
			right = evaluationPostOrder(node->right);
			switch (node->data) {
			case '+':
				value = left + right;
				break;
			case '-':
				value = left - right;
				break;
			case '*':
				value = left * right;
				break;
			case '/':
				value = left / right;
				break;
			}
		}
	}
	return value;
}

void Tree::printTree(Node* node, int level) {
	int j = 1;

	if (node != NULL) {
		printTree(node->right, level + 1);
		while (j++ < level) cout << "	";
		cout << node->data << " ";

		if (node->left != 0 && node->right != 0) cout << "<";
		else if (node->right != 0) cout << "/";
		else if (node->left != 0) cout << "\\";
		cout << endl;

		printTree(node->left, level + 1);
	}
}


int main() {
	Tree myTree;
	string exp1 = "8+9-2*3"; 
	string exp2 = "A/B*C*D+E";

	cout << endl << "1. Infix Expression1 : " << exp1 << endl;
	myTree.buildTree(exp1);
	cout << endl << "InOrder : ";
	myTree.inOrder(myTree.root);
	cout << endl << "PostOrder : ";
	myTree.postOrder(myTree.root);
	cout << endl << "PreOrder : ";
	myTree.preOrder(myTree.root);
	cout << endl << "Evaluation : ";
	cout << myTree.evaluationPostOrder(myTree.root) << endl;
	myTree.printTree(myTree.root, level);
	cout << endl << endl;

	Tree myTree2;
	cout << endl << endl << "2. Infix Expression2 : " << exp2 << endl;
	myTree2.buildTree(exp2);
	cout << endl << "InOrder : ";
	myTree2.inOrder(myTree2.root);
	cout << endl << "PostOrder : ";
	myTree2.postOrder(myTree2.root);
	cout << endl << "PreOrder : ";
	myTree2.preOrder(myTree2.root);
	cout << endl;
	myTree2.printTree(myTree2.root, level);
	cout << endl << endl;

	return 0;
}