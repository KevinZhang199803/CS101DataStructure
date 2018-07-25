#include<iostream>
#include<string>
#include<cctype>

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
int main()
{
	string s = "1.";
	cout << stod(s) << endl;

	return 0;
}