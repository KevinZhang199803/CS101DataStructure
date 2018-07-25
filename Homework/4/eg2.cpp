#include<iostream>
#include<string>
#include<cstdio>
#include<ctype.h>
#include<sstream>
#include<cmath>

using namespace std;

long int load_factor, length, hash_table_size;

int isReadinFinish = 0;

class node{

	public:
		string value;
		long int key;
		node *next, *pre;

};

class single_linked_list{

	public:
		single_linked_list(){
			
			head = nullptr;

		}

		void init(){

			head = nullptr;

		}

		bool isEmpty();

		long int length();

		void insert(string value);

		void del(string value);

		//void print_list();

		void change(string value, long int key);

		node* search(string value);

		node *head;

};

node* single_linked_list::search(string value){

	for (node *i = head; i != nullptr; i = i -> next){

		if (i -> value == value) return i;

	}

	return nullptr;

}

long int single_linked_list::length(){

	node *p = head;

	long int len = 0;

	while (p != nullptr){

		len++;
		p = p -> next;

	}

	return len;
}

bool single_linked_list::isEmpty(){

	return (head == nullptr);

}

void single_linked_list::insert(string value){

	node *isFound = search(value);

	node *p = head, *temp;

	temp = new node;
	temp -> value = value;
	temp -> next = nullptr;
	temp -> pre = nullptr;
	temp -> key = 1;

	if (isEmpty()){

		head = temp;

	}else{

		if (isFound == nullptr){

			head -> pre = temp;
			temp -> next = head;
			head = temp;

		}else{

			isFound -> key += 1;

		}

	}

}

void single_linked_list::change(string value, long int key){

	node *p = head, *temp;

	temp = new node;
	temp -> value = value;
	temp -> next = nullptr;
	temp -> pre = nullptr;
	temp -> key = key;

	if (isEmpty()){

		head = temp;

	}else{

		head -> pre = temp;
		temp -> next = head;
		head = temp;

	}

}

void single_linked_list::del(string value){

	if (isEmpty()) return;
	else if (length() == 1){

		if (head -> value == value) head = nullptr;
		else return;

	}else{

		for (node *i = head; i != nullptr; i = i -> next){

			if (i -> value == value){

				i -> pre -> next = i -> next;
				i -> next -> pre = i -> pre;

			}

		}

	}

}



single_linked_list Hash_Table[100000], Hash_Table_temp[100000];

bool isNum(string str_input){

	stringstream str_in_buff(str_input);

	char temp_c;
	double temp_d;

	if (!(str_in_buff >> temp_d)) return false;

	if (str_in_buff >> temp_c) return false;

	return true;

}

long int hash_code(string value){

	if (isNum(value)){

		return stoi(value) % length;

	}else{

		long int sum = 0, factor = 0;
		
		for (int i = value.length() - 1; i >= 0; i--){

			long int temp, temp2;

			unsigned char temp_c = value[i];

			temp2 = pow(256 % length, factor);

			temp2 = temp2 % length;

			temp = ((temp_c % length) * temp2) % length;

			//uint64_t temp = value[i] * pow(256, factor);
			//cout << "temp = " << temp << endl;

			//cout << temp << endl;

			sum += temp;
			factor++;

		}
		//cout << value << " sum:" << sum << endl;

		return sum % length;

	}

}


void print_table(){

	cout << "[\n";

	for (int i = 0; i < length; i++){

		cout << "{";

		for (node *j = Hash_Table[i].head; j != nullptr; j = j -> next){

			cout << "\"" << j -> value << "\"" << ":" << j -> key;

			if (j -> next != nullptr) cout << ",";

		}

		cout << "}";

		if (i + 1 != length) cout << ",";

		cout << "\n";

	}

	cout << "]";

}

void hash_table_resize(){

	//print_table();

	long int length_temp = length;

	length = 2 * length + 1;

	for (int i = 0; i <= length_temp; i++){
		for (node *j = Hash_Table[i].head; j != nullptr; j = j -> next){

			long int code = hash_code(j -> value);

			Hash_Table_temp[code].change(j -> value, j -> key);

		}
	}

	for (int i = 0; i <= length; i++){

		Hash_Table[i].init();

		Hash_Table[i] = Hash_Table_temp[i];

		Hash_Table_temp[i].init();

	}

}


int main(){

	scanf("%ld %ld", &load_factor, &length);

	string str_in;

	hash_table_size = 0;

	while (cin >> str_in){

		cout << "str_in = " << str_in << " isReadinFinish = " << isReadinFinish << endl;

		if (isReadinFinish == 0){

			if (str_in == "************************"){

				isReadinFinish = 1;

				continue;


			}else{

				long int code = hash_code(str_in);

				//cout << str_in << " " << code << endl;

				Hash_Table[code].insert(str_in);

				hash_table_size++;

				if (hash_table_size * 100 > length * load_factor) hash_table_resize();

				//cout << "length = " << length << endl;

				//print_table();


			}

		}else{

			if (str_in == "************************") {

				print_table();

				return 0;

			}else {

				long int code = hash_code(str_in);
				
				Hash_Table[code].del(str_in);			

				//print_table();
			}

		}

	}

	print_table();

	return 0;
}
