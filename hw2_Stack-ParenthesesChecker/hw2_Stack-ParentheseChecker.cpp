////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Name :  박정민
// Student ID : 20203074
// Program ID : HW#2
// Description : 데이터 파일에서 괄호가 포함된 표현식을 읽어 괄호의 균형이 잘 맞추어져있는지 스택을 사용하여 테스트한다.
// Algorithm : 데이터를 한 줄씩 읽어와서 좌괄호, 즉 '(' 또는 '{' 또는 '['만 스택에 push하고
//			   우괄호, 즉 ')' 또는 '}' 또는 ']'를 만나면 스택을 확인하고 match() 함수를 통해 괄호의 균형이 맞는지 확인한다. 
// Variables :
// function - match() : 우괄호, 즉 ')' 또는 '}' 또는 ']'를 만났을 때 스택이 비어있지 않은 상태이면 (스택에는 좌괄호,즉 '(' 또는 '{' 또는 '['만 
//						보관되어 있음) pop해서 확인하여 같은 종류의 것인지( '('는 ')'과 매칭되어야 하고 '{'는 '}'와 매칭되어야 하고 '['는 ']'와	
//						매칭되어야 함) if조건문을 통해 확인하고 맞으면 true 아니면 false 를 반환
//			- check_paren() : 괄호를 만날 때까지 인덱스 증가(즉, 괄호가 아닌 다른 문자 A, B, C 등을 만나면 다음 인덱스로 넘어감)한다.	
//							  좌괄호, 즉 '(' 또는 '{' 또는 '['를 만나면 stack에 push해 놓는다.
//							  우괄호, 즉 ')' 또는 '}' 또는 ']'를 만났을 때 stack이 비어있으면 괄호의 쌍이 맞지 않는 것이므로 unbalanced + 1를 하고 false 반환	
//							  stack이 비어있지 않으면 stack에서 pop한 좌괄호와 현재의 우괄호를 match()함수에 넘겨주어 종류가 일치하는지 확인한다. 
//							  중간에 return을 만나지 않고 데이터의 한 줄이 다 끝나고 나서도(for문이 끝나고 나서도) stack이 비어있지 않으면 
//							  괄호의 쌍이 맞지 않는 것이므로 unbalanced + 1하고 fasle반환, 비어있다면 괄호의 균형이 잘 맞는 것이므로 true 반환
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

void Stack::push(char exp) { // stack에 push하는 함수
	if (isFull()) cout << "Stack is full" << endl;
	else stack[++top] = exp;
}

char Stack::pop() { // stack에서 원소를 pop하는 함수
	if (!isEmpty()) return stack[top--];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : match()
// description : 우괄호를 만났을 때 스택이 비어있지 않은 상태이면 호출됨. 우괄호와 스택에 들어있는 좌괄호의 종류가 맞는지 확인해주고 결과를 반환함.
// variables : 스택에서 꺼낸 char a(좌괄호),
//			   buffer에서 읽어온 i번째 exp[i]인 char b(우괄호)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int match(char a, char b) { 
	if (a == '[' && b == ']') return true;
	else if (a == '{' && b == '}') return true;
	else if (a == '(' && b == ')') return true;
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// function : check_paren()
// description : hw2.txt를 한 줄씩 읽어와서 전달받아 괄호를 만나면 괄호의 균형이 맞는지 검사해주고 괄호가 아닌 문자를 만나면 다음 인덱스로 넘어감.
//				 데이터는 앞에서부터 검사하고 검사중 false 값을 return 받으면 그 줄의 데이터는 그 뒤로 더 검사하지 않고 다음 줄의 데이터로 넘어감.
// variables : buffer에서 읽어온 것을 전달받은 char* exp,	
//			   unbalanced와 mismatched의 갯수를 세주는 변수, 
//			   스택에서 pop해 온 것을 저장하는 변수 temp
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int check_paren(char* exp, int *unbalanced, int *mismatched) {
	Stack stack(100);

	char temp;

	for (int i = 0; i < strlen(exp); i++) { // 데이터 한 줄의 길이만큼 반복문을 돌림
		if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[') stack.push(exp[i]); //좌괄호를 만나면 스택에 push
		else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') { // 우괄호를 만났을 때
			if (stack.isEmpty()) { //스택이 비어있으면 괄호의 쌍이 맞지 않는 상태이므로 unbalanced + 1
				cout << "The Expression has unbalanced parentheses" << endl;
				*unbalanced = *unbalanced + 1;
				return false; // false를 반환
			}
			else { // 스택이 비어있지 않으면
				temp = stack.pop(); // 스택에 들어있는 것(좌괄호)를 pop
				if (!match(temp, exp[i])) { // 스택에서 pop한 것과 현재의 exp[i]의 종류가 일치하는지 match()함수로 검사
					cout << "The Mismatched Parenthes in the Expression are " << temp << " and " << exp[i] << endl; // 매칭되지 않으면 출력됨
					*mismatched = *mismatched + 1; // mismatched + 1
					return false; // false를 반환
				}
			}
		}
	}
	if (stack.isEmpty()) return true; // 한 줄을 끝까지 다 읽고난 후 스택이 비어있으면 괄호의 균형이 잘 맞는 상태이므로 true 반환
	else { // 한 줄을 끝까지 다 읽고 난 후 스택이 비어있지 않으면 좌괄호가 남아있는 상태이므로 괄호의 쌍이 맞지 않으므로 unbalanced + 1
		cout << "The Expression has unbalanced parentheses" << endl; 
		*unbalanced = *unbalanced + 1; 
		return false; // false 반환
	}
}

int main() {
	char buffer[80]; // 데이터 파일을 읽어와서 저장
	int validity; // 데이터 내에서 괄호의 균형이 맞는지에 대한 정보
	ifstream infile;
	int i = 0; // 출력할 때 몇 번째 데이터인지 알려주기 위한 변수 
	int balanced = 0; int unbalanced = 0; int mismatched = 0; // balanced, unbalanced, mismatched 데이터 수를 세기 위한 변수

	infile.open("hw2.txt", ios::in);
	if (infile.fail()) { cout << "can't open the input file" << endl; exit(1); }

	while (infile.getline(buffer, 80)) { // hw2.txt의 데이터를 한 줄씩 읽어옴
		cout << "Input Data " << ++i << ".	" << buffer << endl; //읽어온 데이터를 그대로 출력
		validity = check_paren(buffer,&unbalanced, &mismatched); // buffer에서 읽어온 데이터를 check_paren()함수를 통해 검사하고 결과를 validity에 반환
		if (validity) { // 검사 결과가 true일 때 balanced + 1
			cout << "The Expression is Valid";
			balanced++;  
		}
		else cout << "The Expression is Invalid"; // 검사 결과가 false일 때

		cout << endl << endl;				
	}
	cout << "Total :	Balanced : " << balanced << " Unbalanced : " << unbalanced << " Mismatched : " << mismatched;

	return 0;
}

