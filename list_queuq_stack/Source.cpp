#include<iostream>
#include<exception>
#include<string>
#include<cmath>
using namespace std;
template<class T>
struct node {
	T data;
	node<T>* pnext;
};
template<class T>
class mylist {
	node<T>* phead;
	node<T>* ptail;
public:
	mylist() {
		phead = ptail = NULL;
	}
	~mylist() {
		if (ptail != NULL) {
			while (phead != NULL)
			{
				node<T>* temp = phead;
				phead = phead->pnext;
				if (temp != NULL)delete temp;
			}
			phead = NULL;
			ptail = NULL;
		}
	}
	void addHead(node<T>* u) {
		if (u != NULL) {
			if (phead == NULL) {
				phead = ptail = u;
			}
			else {
				u->pnext = phead;
				phead = u;
			}
		}
	}
	bool isempty() {
		return phead == NULL;
	}
	void addTail(node<T>*u) {
		if (u != NULL) {
			if (phead == NULL) {
				phead = ptail = u;
			}
			else {
				ptail->pnext = u;
				ptail = u;
			}
		}
	}
	void delTail() {
		if (ptail != NULL) {
			node<T>* u = NULL;
			if (phead->pnext == NULL) {
				delete phead;
				phead = ptail = NULL;
			}
			else {
				for (u = phead; u->pnext != ptail; u = u->pnext);
				swap(u, ptail);
				delete u;
				ptail->pnext = NULL;
			}
		}
	}
	void delHead() {
		if (ptail != NULL) {
			node<T>* u = NULL;
			if (phead->pnext == NULL) {
				delete phead;
				phead = ptail = NULL;
			}
			else {
				u = phead;
				phead = phead->pnext;
				delete u;
			}
		}
	}
	node<T>* find(T data) {
		for (node<T>* u = phead; u !=NULL; u=u->pnext) {
			if (data == u->data)return u;
		}
		return NULL;
	}
	void deldata(T data) {
		if (phead->data == data)delHead();
		else if (ptail->data == data)delTail();
		else {
			node<T>* u = phead;
			node<T>*u1 = phead->pnext;
			while (u1 != ptail) {
				if (u1->data == data) break;
				u = u->pnext;
				u1 = u1->pnext;
			}
			u->pnext = u1->pnext;
			u1->pnext = NULL;
			delete u1;
		}
	}
	void print() {
		if (phead != NULL) {
			for (node<T>* u = phead; u != NULL; u = u->pnext) {
				cout << u->data << '\t';
			}
		}
	}
	node<T>* head() {
		return phead;
	}
	node<T>* tail() {
		return ptail;
	}
};
template<class T>
node<T>* creatNODE(T data) {
	node<T>*a = new node<T>;
	a->data = data;
	a->pnext = NULL;
	return a;
}
template<class T>
class myStack {
	mylist<T> myl;
public:
	void push(T data) {
		myl.addTail(creatNODE(data));
	}
	T top() {
		if (!myl.isempty())return myl.tail()->data;
		else throw out_of_range("the list is empty");
	}
	void pop() {
		myl.delTail();
	}
	bool isempty() {
		return myl.isempty();
	}
};
template<class T>
class myQueue {
	mylist<T> myl;
public:
	void enqueue(T data) {
		myl.addTail(creatNODE(data));
	}
	void dequeue() {
		myl.delHead();
	}
	bool isempty() {
		return myl.isempty();
	}
	T top() {
		if (!myl.isempty())return myl.head()->data;
		else throw out_of_range("the list is empty");
	}
};
int setuutien(char c){
	if (c == '-'|| c=='+')return 1;
	else if (c == '*' || c == '/') return 2;
	else if (c == '(')return 0;
	else return 3;
}
void infixToPostfix(string source,string& result) {
	result = "";
	myStack<char> a;
	for (int i = 0; i < source.size(); i++) {
		if (source[i] == '+' || source[i] == '-' || source[i] == '*' || source[i] == '/' || source[i] == '(' || source[i] == ')'||source[i]=='^') {
			if (a.isempty())a.push(source[i]);
			else {
				if (source[i] == '(')a.push(source[i]);
				else if (source[i] == ')') {
					while (a.top() != '(') {
						result += a.top();
						a.pop();
					}
					a.pop();
				}
				else {
					char k = a.top();
					if (setuutien(source[i]) > setuutien(a.top()))
					{
						a.push(source[i]);
						int o = 5;
					}
					else {
						if (a.top() != '(') {
							while (!a.isempty()&&setuutien(source[i]) <= setuutien(a.top()) ) {
								result += a.top();
								a.pop();
								
							}
							a.push(source[i]);
						}
					}
				}
			}
		}
		else {
			result += source[i];
		}
	}
	while (!a.isempty()) {
		result += a.top();
		a.pop();
	}
}
int thenum(string & result){
	result += ' ';
	int pos = 0;
	if (result[0] == ' ') {
		pos = result.find_first_not_of(' ', 0);
	}
	myStack<int> a;
	for (int i = pos; i < result.size(); i++) {
		if (result[i] == '+' || result[i] == '-' || result[i] == '*' || result[i] == '/' || result[i] == '^') {
			int temp1 = a.top();
			a.pop();
			int temp2 = a.top();
			a.pop();
			int sum = 0;
			switch (result[i])
			{
			case '+': {sum = temp1 + temp2; break; }
			case'-': {sum = temp2 - temp1; break; }
			case'*': {sum = temp2 * temp1; break; }
			case'/': {sum = temp2 / temp1; break; }
			case'^': {sum = pow(temp2, temp1); break; }
			}
			a.push(sum);
		}
		else {
			int dem = i;
			string op;
			char test = result[dem];
			while (result[dem] != ' ') {
				if (result[dem] == '+' || result[dem] == '-' || result[dem] == '*' || result[dem] == '/' || result[dem] == '^') {
					dem--; break;
				}
				op += result[dem];
				dem++;
			}
			i = dem;
			if (!op.empty())
			{
				a.push(atoi(op.c_str()));
			}
		}
	}

	return a.top();
}
void main() {
	string source;
	string result;
	getline(cin, source);
	infixToPostfix(source, result);
	cout << result << endl;
	cout << thenum(result) << endl;
}