////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  ������
// Student ID : 20203074
// Program ID : HW#2
// Description : ������ ���Ͽ��� ��ȣ�� ���Ե� ǥ������ �о� ��ȣ�� ������ �� ���߾����ִ��� ������ ����Ͽ� �׽�Ʈ�Ѵ�.
// Algorithm : �����͸� �� �پ� �о�ͼ� �°�ȣ, �� '(' �Ǵ� '{' �Ǵ� '['�� ���ÿ� push�ϰ�
//			   ���ȣ, �� ')' �Ǵ� '}' �Ǵ� ']'�� ������ ������ Ȯ���ϰ� match() �Լ��� ���� ��ȣ�� ������ �´��� Ȯ���Ѵ�. 
// Variables :
// function - match() : ���ȣ, �� ')' �Ǵ� '}' �Ǵ� ']'�� ������ �� ������ ������� ���� �����̸� (���ÿ��� �°�ȣ,�� '(' �Ǵ� '{' �Ǵ� '['�� 
//						�����Ǿ� ����) pop�ؼ� Ȯ���Ͽ� ���� ������ ������( '('�� ')'�� ��Ī�Ǿ�� �ϰ� '{'�� '}'�� ��Ī�Ǿ�� �ϰ� '['�� ']'��	
//						��Ī�Ǿ�� ��) if���ǹ��� ���� Ȯ���ϰ� ������ true �ƴϸ� false �� ��ȯ
//			- check_paren() : ��ȣ�� ���� ������ �ε��� ����(��, ��ȣ�� �ƴ� �ٸ� ���� A, B, C ���� ������ ���� �ε����� �Ѿ)�Ѵ�.	
//							  �°�ȣ, �� '(' �Ǵ� '{' �Ǵ� '['�� ������ stack�� push�� ���´�.
//							  ���ȣ, �� ')' �Ǵ� '}' �Ǵ� ']'�� ������ �� stack�� ��������� ��ȣ�� ���� ���� �ʴ� ���̹Ƿ� unbalanced + 1�� �ϰ� false ��ȯ	
//							  stack�� ������� ������ stack���� pop�� �°�ȣ�� ������ ���ȣ�� match()�Լ��� �Ѱ��־� ������ ��ġ�ϴ��� Ȯ���Ѵ�. 
//							  �߰��� return�� ������ �ʰ� �������� �� ���� �� ������ ������(for���� ������ ������) stack�� ������� ������ 
//							  ��ȣ�� ���� ���� �ʴ� ���̹Ƿ� unbalanced + 1�ϰ� fasle��ȯ, ����ִٸ� ��ȣ�� ������ �� �´� ���̹Ƿ� true ��ȯ
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

class Stack { // Stack class
private :
	int* stack;
	int top;
	const int size;
public :
	Stack(int size);
	void push(char exp);
	char pop();
	bool isEmpty() { return top == -1; }
	bool isFull() { return top == (size - 1); }
};

Stack::Stack(int size) :size(size) {
	stack = new int[size];
	top = -1;
}

void Stack::push(char exp) { // stack�� push�ϴ� �Լ�
	if (isFull()) cout << "Stack is full" << endl;
	else stack[++top] = exp;
}

char Stack::pop() { // stack���� ���Ҹ� pop�ϴ� �Լ�
	if (!isEmpty()) return stack[top--];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : match()
// description : ���ȣ�� ������ �� ������ ������� ���� �����̸� ȣ���. ���ȣ�� ���ÿ� ����ִ� �°�ȣ�� ������ �´��� Ȯ�����ְ� ����� ��ȯ��.
// variables : ���ÿ��� ���� char a(�°�ȣ),
//			   buffer���� �о�� i��° exp[i]�� char b(���ȣ)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int match(char a, char b) { 
	if (a == '[' && b == ']') return true;
	else if (a == '{' && b == '}') return true;
	else if (a == '(' && b == ')') return true;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : check_paren()
// description : hw2.txt�� �� �پ� �о�ͼ� ���޹޾� ��ȣ�� ������ ��ȣ�� ������ �´��� �˻����ְ� ��ȣ�� �ƴ� ���ڸ� ������ ���� �ε����� �Ѿ.
//				 �����ʹ� �տ������� �˻��ϰ� �˻��� false ���� return ������ �� ���� �����ʹ� �� �ڷ� �� �˻����� �ʰ� ���� ���� �����ͷ� �Ѿ.
// variables : buffer���� �о�� ���� ���޹��� char* exp,	
//			   unbalanced�� mismatched�� ������ ���ִ� ����, 
//			   ���ÿ��� pop�� �� ���� �����ϴ� ���� temp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int check_paren(char* exp, int *unbalanced, int *mismatched) {
	Stack stack(100);

	char temp;

	for (int i = 0; i < strlen(exp); i++) { // ������ �� ���� ���̸�ŭ �ݺ����� ����
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') stack.push(exp[i]); //�°�ȣ�� ������ ���ÿ� push
		else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') { // ���ȣ�� ������ ��
			if (stack.isEmpty()) { //������ ��������� ��ȣ�� ���� ���� �ʴ� �����̹Ƿ� unbalanced + 1
				cout << "The Expression has unbalanced parentheses" << endl;
				*unbalanced = *unbalanced + 1;
				return false; // false�� ��ȯ
			}
			else { // ������ ������� ������
				temp = stack.pop(); // ���ÿ� ����ִ� ��(�°�ȣ)�� pop
				if (!match(temp, exp[i])) { // ���ÿ��� pop�� �Ͱ� ������ exp[i]�� ������ ��ġ�ϴ��� match()�Լ��� �˻�
					cout << "The Mismatched Parenthes in the Expression are " << temp << " and " << exp[i] << endl; // ��Ī���� ������ ��µ�
					*mismatched = *mismatched + 1; // mismatched + 1
					return false; // false�� ��ȯ
				}
			}
		}
	}
	if (stack.isEmpty()) return true; // �� ���� ������ �� �а� �� ������ ��������� ��ȣ�� ������ �� �´� �����̹Ƿ� true ��ȯ
	else { // �� ���� ������ �� �а� �� �� ������ ������� ������ �°�ȣ�� �����ִ� �����̹Ƿ� ��ȣ�� ���� ���� �����Ƿ� unbalanced + 1
		cout << "The Expression has unbalanced parentheses" << endl; 
		*unbalanced = *unbalanced + 1; 
		return false; // false ��ȯ
	}
}

int main() {
	char buffer[80]; // ������ ������ �о�ͼ� ����
	int validity; // ������ ������ ��ȣ�� ������ �´����� ���� ����
	ifstream infile;
	int i = 0; // ����� �� �� ��° ���������� �˷��ֱ� ���� ���� 
	int balanced = 0; int unbalanced = 0; int mismatched = 0; // balanced, unbalanced, mismatched ������ ���� ���� ���� ����

	infile.open("hw2.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile.getline(buffer, 80)) { // hw2.txt�� �����͸� �� �پ� �о��
		cout << "Input Data " << ++i << ".	" << buffer << endl; //�о�� �����͸� �״�� ���
		validity = check_paren(buffer,&unbalanced, &mismatched); // buffer���� �о�� �����͸� check_paren()�Լ��� ���� �˻��ϰ� ����� validity�� ��ȯ
		if (validity) { // �˻� ����� true�� �� balanced + 1
			cout << "The Expression is Valid";
			balanced++;  
		}
		else cout << "The Expression is Invalid"; // �˻� ����� false�� ��

		cout << endl << endl;				
	}
	cout << "Total :	Balanced : " << balanced << " Unbalanced : " << unbalanced << " Mismatched : " << mismatched;

	return 0;
}

