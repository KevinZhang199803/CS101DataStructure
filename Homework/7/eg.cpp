#include<iostream>
using namespace std;

int row = 0, col = 0, startrow, startcol, endrow, endcol;
string input_lines[100000];
string origin[100000];

struct coord{
	int row;
	int col;
};

struct trace{
	coord self;
	coord previous;
};

template <class T>
class node{
public:
	T key;
	node* next;
	node(){
		next = nullptr;
	}
};

template <class T>
class Queue{
private:
	node<T> *head, *tail;

public:
	int length;
	Queue(){
		head = nullptr;
		tail = nullptr;
		length = 0;
	}
	void enqueue(T element);
	T dequeue();
	bool isEmpty();
};

template <class T>
void Queue<T>::enqueue(T element){
	if (length == 0){
		node<T>* newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = nullptr;

		head = newnode;
		tail = newnode;
		length = 1;
	}else if (length == 1){
		node<T>* newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = nullptr;

		tail -> next = newnode;
		tail = newnode;
		length = 2;
	}else{
		node<T>* newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = nullptr;

		tail -> next = newnode;
		tail = newnode;
		length++;
	}
}

template <class T>
T Queue<T>::dequeue(){
	if (length == 1){
		node<T>* old = head;
		T temp = head -> key;
		head = nullptr;
		tail = nullptr;
		length = 0;
		delete old;
		return temp;
	}else{
		node<T>* old = head;
		T temp = head -> key;
		head = head -> next;
		length--;
		delete old;
		return temp;
	}
}

template <class T>
bool Queue<T>::isEmpty(){
	return (length == 0);
}

template <class T>
class Stack{
private:
	node<T> *top, *bottom;
	int length;

public:
	Stack(){
		top = nullptr;
		bottom = nullptr;
		length = 0;
	}
	void push(T element);
	T pop();
	T topval();
	bool isEmpty();
};

template <class T>
void Stack<T>::push(T element){
	if (length == 0){
		node<T> *newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = nullptr;

		top = newnode;
		bottom = newnode;
		length = 1;
	}else if (length == 1){
		node<T> *newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = top;

		top = newnode;
		length = 2;
	}else{
		node<T> *newnode = new node<T>;
		newnode -> key = element;
		newnode -> next = top;

		top = newnode;
		length++;
	}
}

template <class T>
T Stack<T>::pop(){
	if (length == 1){
		node<T>* old = top;
		T temp = top -> key;
		top = nullptr;
		bottom = nullptr;
		length = 0;
		delete old;
		return temp;
	}else{
		node<T>* old = top;
		T temp = top -> key;
		top = top -> next;
		length--;
		delete old;
		return temp;
	}
}

template <class T>
bool Stack<T>::isEmpty(){
	return (length == 0);
}

template <class T>
T Stack<T>::topval(){
	return top -> key;
}

/*
Sequence:
Up
Down
Right
Left
*/
struct directions{
	int num;
	coord *result;
};

directions next_step(coord now){
	coord temp[4];
	int result_num = 0;
	if (now.row > 0 && now.row < row-1 && now.col > 0 && now.col < col-1){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}

	}else if (now.row == 0 && now.col > 0 && now.col < col-1){
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}
	}else if (now.row == 0 && now.col == 0){
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
	}else if (now.row == 0 && now.col == col-1){
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}
	}else if (now.row == row-1 && now.col > 0 && now.col < col-1){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}
	}else if (now.row == row-1 && now.col == 0){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
	}else if (now.row == row-1 && now.col == col-1){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}
	}else if (now.row > 0 && now.row < row-1 && now.col == 0){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col+1] == ' '){
			coord next = {now.row, now.col+1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col+1] = 'x';
		}
	}else if (now.row > 0 && now.row < row-1 && now.col == col-1){
		if (input_lines[now.row-1][now.col] == ' '){
			coord next = {now.row-1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row-1][now.col] = 'x';
		}
		if (input_lines[now.row+1][now.col] == ' '){
			coord next = {now.row+1, now.col};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row+1][now.col] = 'x';
		}
		if (input_lines[now.row][now.col-1] == ' '){
			coord next = {now.row, now.col-1};
			temp[result_num] = next;
			result_num++;
			input_lines[now.row][now.col-1] = 'x';
		}
	}

	directions dir;
	if (result_num == 0){	
		dir.num = 0;
		dir.result = nullptr;
		return dir;
	}else{
		dir.result = new coord[result_num];
		for (int i = 0; i < result_num; i++){
			dir.result[i] = temp[i];
		}
		dir.num = result_num;
		return dir;
	}
}

void readin(){
	row = 0;col = 0;
	string temp;

	while (getline(cin, temp)){
		input_lines[row] = temp;
		origin[row] = temp;

		if (temp.find('*') != -1){
			startrow = row;
			startcol = temp.find('*');
			input_lines[startrow][startcol] = ' ';
		}
		if (temp.find('+') != -1){
			endrow = row;
			endcol = temp.find('+');
			input_lines[endrow][endcol] = ' ';
		}
		row++;
	}
	col = input_lines[0].length();
}

void BFS(){
	Queue<trace> queue;
	Stack<trace> stack;

	queue.enqueue({{startrow, startcol}, {-1, -1}});
	while (!queue.isEmpty()){
		trace now = queue.dequeue();
		directions next = next_step(now.self);
		
		if (next.num != 0){
			for (int i = 0; i < next.num; i++){
				queue.enqueue({next.result[i], now.self});
			}
			delete next.result;
		}
		stack.push(now);
	}
	
	while (!stack.isEmpty() && !(stack.topval().self.row == endrow && stack.topval().self.col == endcol)){
		trace temp = stack.pop();
	}

	if (stack.isEmpty()){
		cout << "NO SOLUTION" << endl;
		exit(0);
	}

	int step_counter = 1;
	origin[endrow][endcol] = '.';

	trace now = stack.pop();
	while (!stack.isEmpty()){
		trace temp = stack.pop();
		if (temp.self.row == now.previous.row && temp.self.col == now.previous.col){
			origin[temp.self.row][temp.self.col] = '.';
			step_counter++;
			now = temp;
		}
	}
	
	for (int i = 0; i < row; i++){
		cout << origin[i] << endl;
	}
	cout << (step_counter-1) << endl;
	
}

int main(){
	readin();
	BFS();
	return 0;
}