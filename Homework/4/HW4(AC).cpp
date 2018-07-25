#include<iostream>
#include<string>
#include<cstring>
#include<cstdio>
#include<cstdlib>
#include<ctype.h>

using namespace std;

long int load_factor, length, hash_table_size;

int isReadinFinish = 0;

class node{

	public:
		string value;
		long int key;
		node *next;

};

class single_linked_list{

	public:
		void init();

		bool insert(string value);

		void insert_full(string value, long int key);

		void del(string value);

		node* search(string value);

		long int list_length;
		node *head;

};

void single_linked_list::init(){

	list_length = 0;
	head = nullptr;

}

node* single_linked_list::search(string value){
	if (list_length  == 0) return nullptr;
	else{

		for (node *i = head; i != nullptr; i = i -> next){
			if (i -> value == value) return i;
		}

		return nullptr;

	}

}

bool single_linked_list::insert(string value){
	if (list_length == 0){

		node *new_node = new node;

		new_node -> value = value;
		new_node -> key = 1;
		new_node -> next = nullptr;
		head = new_node;

		list_length = 1;

		return true;

	}else{
		
		node *isExist = search(value);

		if (isExist == nullptr){

			node *new_node = new node;

			new_node -> value = value;
			new_node -> key = 1;
			new_node -> next = head;
			head = new_node;

			list_length++;
			return true;

		}else{

			isExist -> key += 1;
			return false;

		}

	}
}

void single_linked_list::insert_full(string value, long int key){

	if (list_length == 0){

		node *new_node = new node;

		new_node -> value = value;
		new_node -> key = key;
		new_node -> next = nullptr;
		head = new_node;

		list_length = 1;

	}else{
			
		node *new_node = new node;

		new_node -> value = value;
		new_node -> key = key;
		new_node -> next = head;
		head = new_node;

		list_length++;
	}
}

void single_linked_list::del(string value){

	if (list_length == 0) return;
	else if (list_length == 1){

		if (head -> value == value){

			head = nullptr;
			list_length = 0;

		}
		return;

	}
	else if (list_length == 2){

		if (head -> value == value){

			head = head -> next;
			list_length = 1;

		}
		else if (head -> next -> value == value){

			head -> next = nullptr;
			list_length = 1;

		}
		return;

	}else{

		node *current, *pre;

		if (head -> value == value){

			head = head -> next;
			list_length--;

			return;

		}else{

			current = head -> next;
			pre = head;

			while (current != nullptr){

				if (current -> value == value){

					pre -> next = current -> next;
					list_length--;
					break;

				}else{

					current = current -> next;
					pre = pre -> next;

				}

			}

			return;

		}

	}

}

single_linked_list Hash_Table[10000000], Hash_Table_temp[10000000];


unsigned long int hash_code(string value){

	char *ptr;

	long int num = strtol(value.c_str(), &ptr, 10);
	
	if (num >= 0 && *ptr == '\0'){

		return num % length;

	}else{

		unsigned long int sum = 0;

		if (value.length() == 1){

			unsigned char temp1 = value[0];

			unsigned int temp2 = temp1;

			return temp2 % length;

		}else if (value.length() == 2){

			unsigned char temp1 = value[0];

			unsigned char temp2 = value[1];

			unsigned int temp3 = temp1;

			unsigned int temp4 = temp2;

			sum = (temp3 * 256 + temp4) % length;

			return sum;


		}else{

			unsigned char temp1 = value[0];

			unsigned char temp2 = value[1];

			unsigned int temp3 = temp1;

			//cout << "temp3 = " << temp3 << endl;

			unsigned int temp4 = temp2;

			//cout << "temp4 = " << temp4 << endl;

			sum = (temp3 * 256 + temp4) % length;

			for (int i = 2; i < value.length(); i++){

				temp1 = value[i];

				temp3 = temp1;

				sum = (sum * 256 + temp3) % length;

			}

			return sum % length;

		}
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

		cout << endl;

	}

	cout << "]\n";

}

void hash_table_resize(){

	long int length_temp = length;

	length = 2 * length + 1;

	for (int i = 0; i <= length_temp; i++){
		for (node *j = Hash_Table[i].head; j != nullptr; j = j -> next){

			long int code = hash_code(j -> value);
			Hash_Table_temp[code].insert_full(j -> value, j -> key);

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

		if (isReadinFinish == 0){

			if (str_in == "************************"){

				isReadinFinish = 1;

				continue;


			}else{

				long int code = hash_code(str_in);

				bool isExist = Hash_Table[code].insert(str_in);

				if (isExist) hash_table_size++;

				while (hash_table_size * 100 > length * load_factor) hash_table_resize();

			}

		}else{

			if (str_in == "************************") {

				print_table();

				return 0;

			}else {

				long int code = hash_code(str_in);
				
				Hash_Table[code].del(str_in);			

			}
		}
	}
}
