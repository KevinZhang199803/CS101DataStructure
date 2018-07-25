#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

class element{
	public:
		string name;
		uint32_t num;
};

class table{

	public:

		element tbl[1000];
		uint32_t len;

		void init(){
			len = 0;
		}

		void add(string new_name){

			if (len == 0){

				len = 1;
				tbl[0].name = new_name;
				tbl[0].num = 1;
				return;
			}

			for (int i = 0; i < len; i++) {
				if (new_name.compare(tbl[i].name) == 0){
					tbl[i].num++;
					return;
				}
			}

			tbl[len].name = new_name;
			tbl[len].num = 1;
			len++;
		}

		long int search(string name){

			for (int i = 0; i < len; i++){
				if (name.compare(tbl[i].name) == 0) return tbl[i].num;
			}

			return -1;

		}

};

struct Huff_Node {
	long int frequency;
	string name;
	Huff_Node* lchild;
	Huff_Node* rchild;

};

Huff_Node minHeap[2000];
int minHeapNum = 0;

string least_str(Huff_Node node){
	if (node.name != "") return node.name;
	else return min(least_str(*node.lchild), least_str(*node.rchild));
}

int Huff_inputcmp(Huff_Node a, Huff_Node b){
	// a prior to b: 1, b prior to a: -1
	if (a.frequency > b.frequency) return 1;
	else if (a.frequency < b.frequency) return -1;
	else{
		string a_least = least_str(a);
		string b_least = least_str(b);

		if (a_least < b_least) return 1;
		else if (a_least > b_least) return -1;
		else return 0;
	}

}

void minHeapPush(Huff_Node node){
	minHeapNum++;
	minHeap[minHeapNum] = node;
		
	int i = minHeapNum;
	while (i >> 1 != 0 && Huff_inputcmp(minHeap[i], minHeap[i >> 1]) == -1){
		Huff_Node temp = minHeap[i];
		minHeap[i] = minHeap[i >> 1];
		minHeap[i >> 1] = temp;
		i = i >> 1;
	}
}


Huff_Node minHeapPop(){
	Huff_Node val = minHeap[1];

	minHeap[1] = minHeap[minHeapNum];
	minHeapNum -= 1;
	long int i = 1;

	while (i << 1 <= minHeapNum && (Huff_inputcmp(minHeap[i], minHeap[i << 1]) == 1 || Huff_inputcmp(minHeap[i], minHeap[((i << 1) + 1)]) == 1)){
		if (i << 1 == minHeapNum){
			Huff_Node temp = minHeap[i];
			minHeap[i] = minHeap[i << 1];
			minHeap[i << 1] = temp;
			break;
		}else if (Huff_inputcmp(minHeap[i], minHeap[i << 1]) == 1 && Huff_inputcmp(minHeap[i], minHeap[((i << 1) + 1)]) == 1){
			if (Huff_inputcmp(minHeap[i << 1], minHeap[(i << 1) + 1]) != 1){
				Huff_Node temp = minHeap[i];
				minHeap[i] = minHeap[i << 1];
				minHeap[i << 1] = temp;
				i = i << 1;
			}else{
				Huff_Node temp = minHeap[i];
				minHeap[i] = minHeap[(i << 1) + 1];
				minHeap[(i << 1) + 1] = temp;
				i = (i << 1) + 1;
			}
		}else if (Huff_inputcmp(minHeap[i], minHeap[i << 1]) == 1){
			Huff_Node temp = minHeap[i];
			minHeap[i] = minHeap[i << 1];
			minHeap[i << 1] = temp;
			i = i << 1;
		}else{
			Huff_Node temp = minHeap[i];
			minHeap[i] = minHeap[(i << 1) + 1];
			minHeap[(i << 1) + 1] = temp;
			i = (i << 1) + 1;
		}
	}
	return val;
}

void printHeap(Huff_Node node){
	
	if (node.lchild == nullptr && node.rchild == nullptr) cout << node.name << " " << node.frequency << endl;
	else {
		printHeap(*node.lchild);
		printHeap(*node.rchild);
	}

}

struct Code_Node{
	string name;
	string code_str;	
};

Code_Node code[2000];
int code_len = 0;

void Huff_Code(Huff_Node node, string str){

	if (node.lchild == nullptr && node.rchild == nullptr){

		code[code_len].name = node.name;
		code[code_len].code_str = str;
		code_len++;

	}else{
		Huff_Code(*node.lchild, str + "0");
		Huff_Code(*node.rchild, str + "1");
	}
}

void encode_output(string str, table count){

	cout << "HUFFMAN";
	cout << '\0';

	for (int i = 0; i <= 255; i++){

		char temp = i;
		string temp1 = "";
		temp1.push_back(temp);
		int j = 0;
		int isExist = 0;

		while (j < count.len && isExist == 0){
			if (count.tbl[j].name.compare(temp1) == 0){
				fwrite(&count.tbl[j].num, 1, 4, stdout);
				isExist = 1;
			}
			j++;
		}

		if (isExist == 0){
			uint32_t zero = 0;
			fwrite(&zero, 1, 4, stdout);
		}

	}

	string result = "";

	for (int i = 0; i < str.length(); i++){
		int j = 0;
		int isFound = 0;

		while (j < code_len && isFound == 0){
			if (code[j].name.compare(str.substr(i, 1)) == 0){
				result += code[j].code_str;
				isFound = 1;
			}
			j++;
		}

	}

	while (result.length() % 8 != 0) result += "0";

	int j = 0;

	while (j < result.length()){
		uint8_t temp = stoi(result.substr(j, 8), nullptr, 2);
		fwrite(&temp, 1, 1, stdout);
		j += 8;
	}

}

void encode(){

	string str = "";
	char mid;
	while (cin.get(mid)) str.push_back(mid);

	table count;
	count.init();
	
	//cout << 1 << endl;
	for (int i = 0; i < str.length(); i++) count.add(str.substr(i, 1));

	for (int i = 0; i < count.len; i++){
		Huff_Node temp;
		temp.name = count.tbl[i].name;
		temp.frequency = count.tbl[i].num;
		temp.lchild = nullptr;
		temp.rchild = nullptr;

		minHeapPush(temp);
	}

	while (minHeapNum != 1){
		Huff_Node* temp1 = new Huff_Node;
		Huff_Node* temp2 = new Huff_Node;
		Huff_Node new_node;

		*temp1 = minHeapPop();
		*temp2 = minHeapPop();

		new_node.name = "";
		new_node.frequency = temp1 -> frequency + temp2 -> frequency;
		new_node.lchild = temp1;
		new_node.rchild = temp2;

		minHeapPush(new_node);
	}

	Huff_Code(minHeap[1], "");

	for (int i = 0; i < code_len; i++) cout << code[i].name << " " << code[i].code_str << endl;

	//printHeap(minHeap[1]);

	//encode_output(str, count);

	/*
	for (int i = 0; i < count.len; i++){
		cout << tree[i].name << " " << tree[i].weight << " " << tree[i].code << endl;
	}
	*/
	//cout << str.length() << endl;
	//encode_output(tree, str, count);
}

void decode(){
	/*
	char mid = 1;
	long int sum = 0;
	for (int i = 1; i <= 8; i++) cin.get(mid);

	element tbl[2000];
	int tbl_len = 0;

	for (int i = 0; i <= 255; i++){
		uint32_t temp;
		fread(&temp, 1, 4, stdin);

		mid = i;
		string temp1 = "";
		temp1.push_back(mid);

		if (temp != 0){
			tbl[tbl_len].name = temp1;
			tbl[tbl_len].num = temp;
			sum += temp;
			tbl_len++;
		}

	}

	minHeapNum = 0;

	for (int i = 0; i < tbl_len; i++){
		Huff_Node node;
		node.name = tbl[i].name;
		node.frequency = tbl[i].num;
		node.lchild = nullptr;
		node.rchild = nullptr;

		minHeapPush(node);
	}

	while (minHeapNum != 1){
		Huff_Node* temp1 = new Huff_Node;
		Huff_Node* temp2 = new Huff_Node;
		Huff_Node new_node;

		*temp1 = minHeapPop();
		*temp2 = minHeapPop();

		new_node.name = "";
		new_node.frequency = temp1 -> frequency + temp2 -> frequency;
		new_node.lchild = temp1;
		new_node.rchild = temp2;

		minHeapPush(new_node);
	}
	*/

	cout << "";


}

int main(){

	string str = "";

	for (int i = 1; i <= 6; i++) str += cin.get();

	if (str.compare("ENCODE") == 0) encode();
	else if (str.compare("DECODE") == 0) decode();
/*

	Huff_Node node;

	Huff_Node* node1 = new Huff_Node;
	Huff_Node* node2 = new Huff_Node;
	Huff_Node* node3 = new Huff_Node;
	Huff_Node* node4 = new Huff_Node;
	Huff_Node* node5 = new Huff_Node;
	Huff_Node* node6 = new Huff_Node;
	Huff_Node* node7 = new Huff_Node;
	Huff_Node* node8 = new Huff_Node;
	Huff_Node* node9 = new Huff_Node;

	node9 -> name = "e";
	node9 -> lchild = nullptr;
	node9 -> rchild = nullptr;

	node8 -> name = "~";
	node8 -> lchild = nullptr;
	node8 -> rchild = nullptr;

	node7 -> name = "4";
	node7 -> lchild = nullptr;
	node7 -> rchild = nullptr;

	node6 -> name = "2";
	node6 -> lchild = nullptr;
	node6 -> rchild = nullptr;

	node5 -> name = "E";
	node5 -> lchild = nullptr;
	node5 -> rchild = nullptr;

	node4 -> name = "";
	node4 -> lchild = node8;
	node4 -> rchild = node9;

	node3 -> name = "";
	node3 -> lchild = node7;
	node3 -> rchild = node4;

	node2 -> name = "";
	node2 -> lchild = node5;
	node2 -> rchild = node6;

	node1 -> name = "";
	node1 -> lchild = node2;
	node1 -> rchild = node3;

	cout << least_str(*node1) << endl;
*/

	//else encode();


	//cout << str;

	return 0;
}