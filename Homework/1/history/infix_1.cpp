#include<iostream>
#include<string>
#include<malloc.h>
#include<sstream>

using namespace std;

class Node
{
	public:
		string value;
		Node *pre;
		Node *post;
};

class Node_cal
{
	public:
		long double value;
		Node_cal *pre;
		Node_cal *post;
};

class Stack
{
	public:
		void init() // Initialize a stack, create a empty top and bottom node
		{
			bottom.value = "";
			bottom.pre = NULL;
			bottom.post = NULL;
			top.value = "";
			top.pre = NULL;
			top.post = NULL;
			count = 0;
		}

		bool isEmpty() // Judge whether the stack is empty
		{
			return (count == 0);
		}

		string peak() // return the top element of the stack
		{
			return top.value;
		}

		void push(string str_in) // push an element into the stack
		{
			if (count == 0)
			{
				top.value = str_in;
				top.pre = &bottom;
				top.post = NULL;
				bottom.value = str_in;
				bottom.pre = NULL;
				bottom.post = &top;
				count++;
			}else if (count == 1) {
				top.value = str_in;
				count++;
			}else{
				Node *pre_node = (Node*) malloc(sizeof(Node));
				// Copy "top" node to pre_node
				pre_node -> value = top.value;
				pre_node -> pre = top.pre;
				pre_node -> post = &top;
				// Modify the previous node's pointer to pre_node
				top.pre -> post = pre_node;
				// Point current "top" node to pre_node
				// and give the "top" node the new value
				top.pre = pre_node;
				top.value = str_in;
				// point the pre_node to the top node
				count++;
			}
		}

		string pop()
		{
			if (count == 1)
			{
				string back = top.value;

				bottom.value = "";
				top.value = "";
				bottom.post = NULL;
				top.pre = NULL;
				count--;

				return back;
			}else if (count == 2) {
				string back = top.value;
				top.value = bottom.value;
				count--;

				return back;
			}else{
				string back = top.value;
				// move the pre_node to the "top" node
				top.value = top.pre -> value;
				top.pre -> pre -> post = &top;
				// if (top.pre != &bottom) free((Node*) top.pre);
				top.pre = top.pre -> pre;
				// move the previous node of pre_node's post ptr to top
				// if (desserted != &bottom) free(deserted);
				// free the memory used by pre_node
				count--;

				return back;
			}
		}
	private:
		Node bottom, top;
		long long int count;

};

class Stack_cal
{
	public:
		void init() // Initialize a stack, create a empty top and bottom node
		{
			bottom.value = 0;
			bottom.pre = NULL;
			bottom.post = NULL;
			top.value = 0;
			top.pre = NULL;
			top.post = NULL;
			count = 0;
		}

		bool isEmpty() // Judge whether the stack is empty
		{
			return (count == 0);
		}

		long double peak() // return the top element of the stack
		{
			return top.value;
		}

		void push(long double str_in) // push an element into the stack
		{
			if (count == 0)
			{
				top.value = str_in;
				top.pre = &bottom;
				top.post = NULL;
				bottom.value = str_in;
				bottom.pre = NULL;
				bottom.post = &top;
				count++;
			}else if (count == 1) {
				top.value = str_in;
				count++;
			}else{
				Node_cal *pre_node = (Node_cal*) malloc(sizeof(Node_cal));
				// Copy "top" node to pre_node
				pre_node -> value = top.value;
				pre_node -> pre = top.pre;
				pre_node -> post = &top;
				// Modify the previous node's pointer to pre_node
				top.pre -> post = pre_node;
				// Point current "top" node to pre_node
				// and give the "top" node the new value
				top.pre = pre_node;
				top.value = str_in;
				// point the pre_node to the top node
				count++;
			}
		}

		long double pop()
		{
			if (count == 1)
			{
				long double back = top.value;

				bottom.value = 0;
				top.value = 0;
				bottom.post = NULL;
				top.pre = NULL;
				count--;

				return back;
			}else if (count == 2) {
				long double back = top.value;
				top.value = bottom.value;
				count--;

				return back;
			}else{
				long double back = top.value;
				// move the pre_node to the "top" node
				top.value = top.pre -> value;
				top.pre -> pre -> post = &top;
				// if (top.pre != &bottom) free((Node*) top.pre);
				top.pre = top.pre -> pre;
				// move the previous node of pre_node's post ptr to top
				// if (desserted != &bottom) free(deserted);
				// free the memory used by pre_node
				count--;

				return back;
			}
		}
	private:
		Node_cal bottom, top;
		long long int count;

};

class Queue_str
{
	public:
		void init() // Initialize a stack, create a empty top and bottom node
		{
			head.value = "";
			head.pre = NULL;
			head.post = NULL;
			tail.value = "";
			tail.pre = NULL;
			tail.post = NULL;
			count = 0;
		}

		bool isEmpty()
		{
			return (count == 0);
		}

		void enqueue(string str_in)
		{
			if (count == 0)
			{
				head.value = str_in;
				tail.value = str_in;
				tail.pre = &head;
				head.post = &tail;
				count++;
			}else if (count == 1) {
				tail.value = str_in;
				count++;
			}else{
				Node *pre_node = (Node*) malloc(sizeof(Node));

				pre_node -> value = tail.value;
				pre_node -> pre = tail.pre;
				pre_node -> post = &tail;
				tail.pre -> post = pre_node;
				tail.value = str_in;
				tail.pre = pre_node;
				count++;

			}
		}

		string dequeue()
		{
			if (count == 1)
			{
				string back = head.value;
				head.value = "";
				tail.value = "";
				tail.pre = NULL;
				head.post = NULL;
				count--;
				return back;
			}else if (count == 2){
				string back = head.value;
				head.value = tail.value;
				count--;
				return back;
			}else{
				string back = head.value;
				head.value = head.post -> value;
				head.post -> post -> pre = &head;
				head.post = head.post -> post;
				count--;
				return back;
			}
		}

	private:
		Node head, tail;
		long long int count;

}; 

int rankme(string s)
{
	if (s == "+" || s == "-"){
		return 1;
	}else if (s == "*" || s == "/"){
		return 2;
	}else if (s == "("){
		return 0;
	}
}




int main()
{
	string str_input,temp;
	long long int pos_s = 0, pos_e;

	getline(cin, str_input);

	//******** split the input string by whitespace*********
	Queue_str queue;
	queue.init();
	// get the first element
	pos_e = str_input.find(" ", 1);
	queue.enqueue(str_input.substr(0, pos_e-pos_s));
	pos_s = pos_e;
	// first element gotten

	while (str_input.find(" ", pos_s+1) != -1)
	{
		pos_e = str_input.find(" ", pos_s+1);
		queue.enqueue(str_input.substr(pos_s+1, pos_e-pos_s-1));
		cout << "1" << endl;
		pos_s = pos_e;
	}

	// get the last element
	queue.enqueue(str_input.substr(pos_s+1));
	cout << "2" << endl;

	//*************** split part ends ***********************

	//*************** infix to postfix **********************
	/*

	1.遇到操作数：直接输出（添加到后缀表达式中）
	2.栈为空时，遇到运算符，直接入栈
	3.遇到左括号：将其入栈 f
	4.遇到右括号：执行出栈操作，并将出栈的元素输出，直到弹出栈的是左括号，括号不输出。f
	5.遇到其他运算符：加减乘除：弹出所有优先级大于或者等于该运算符的栈顶元素，然后将该运算符入栈 f
	6.最终将栈中的元素依次出栈，输出。

	*/
	Queue_str postfix;
	postfix.init();
	// infix is used to store the infix 
	Stack stack;
	stack.init();
	// stack is used to store operators and parenthesis
	while (! queue.isEmpty())
	{
		temp = queue.dequeue();
		if (temp == "(")
		{
			stack.push("(");
		}else if (temp == ")") {
			string mid;
			while (stack.peak() != "(")
			{
				mid = stack.pop();
				postfix.enqueue(mid);
			}
			mid = stack.pop();
		}else if (temp == "+" || temp == "-" || temp == "*" || temp == "/") {
			string mid;
			while (! stack.isEmpty() && rankme(stack.peak()) >= rankme(temp))
			{
				mid = stack.pop();
				postfix.enqueue(mid);
			}
			stack.push(temp);
		}else{
			postfix.enqueue(temp);
		}
	}
	while (! stack.isEmpty())
	{
		string mid;
		mid = stack.pop();
		postfix.enqueue(mid);
	}
	cout << "1" << endl;


	//*************** infix to postfix ends *****************

	//*************** Calculation starts ********************
	/*
	从左到右遍历表达式的每个数字和符号，遇到是数字就进栈，遇到是符号，就将处于栈顶两个数字出栈，进行运算，运算结果进栈，一直到最终获得结果。
	*/
	Stack_cal cal;
	cal.init();

	while (! postfix.isEmpty())
	{
		string now = postfix.dequeue();
		if (now == "+")
		{
			long double num2 = cal.pop();
			long double num1 = cal.pop();
			long double result = num1 + num2;
			cal.push(result);
		}else if (now == "-")
		{
			long double num2 = cal.pop();
			long double num1 = cal.pop();
			long double result = num1 - num2;
			cal.push(result);
		}else if (now == "*")
		{
			long double num2 = cal.pop();
			long double num1 = cal.pop();
			long double result = num1 * num2;
			cal.push(result);
		}else if (now == "/")
		{
			long double num2 = cal.pop();
			long double num1 = cal.pop();
			long double result = num1 / num2;
			cal.push(result);
		}else{
			cal.push(stold(now));
		}
	}

	long double output = cal.pop();

	//*************** Calculation ends **********************
	
	cout << output << endl;

	return 0;
}