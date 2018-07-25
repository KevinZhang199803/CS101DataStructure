#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

string str = "";

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

class Huff_Node{
	public:
		long int weight;
		string name, code;
		int lchild, rchild, parent;

		void init(){
			weight = 0;
			parent = -1;
			lchild = -1;
			rchild = -1;
			name = "";
			code = "";
		}

};


string find_smallest(Huff_Node tree[], int pos){
	string temp1, temp2;
	int isLeft, isRight;
	temp1 = "";
	temp2 = "";
	isLeft = 0;
	isRight = 0;

	if (tree[pos].lchild != -1){
		temp1 = find_smallest(tree, tree[pos].lchild);
		isLeft = 1;
	}

	if (tree[pos].rchild != -1){
		temp2 = find_smallest(tree, tree[pos].rchild);
		isRight = 1;
	}

	//cout << "L == R: " << (isLeft == isRight) << endl;

	if (isLeft == 1 && isRight == 1) return min(temp1, temp2);
	else return tree[pos].name;

}

void Huff_merge(Huff_Node tree[], int* node1, int* node2, int new_node){

	int i;

	long int weight = 0;

	for (i = 0; i < new_node; i++){

		if (tree[i].parent != -1) continue;

		if (weight == 0){
			weight = tree[i].weight;
			*node1 = i;
		}else if (tree[i].weight < weight){
			weight = tree[i].weight;
			*node1 = i;
		}
	}

	weight = 0; // find the second one

	for (i = 0; i < new_node; i++){
		if (tree[i].parent != -1 || i == *node1) continue;
		else if (weight == 0){
			weight = tree[i].weight;
			*node2 = i;
		}else if (tree[i].weight == weight){
			/*S and T have the same weight, and the smallest character (in ASCII value)
			  in any of S's leaves is smaller than that in any of T's leaves.
			  Under this definition, the delete operation should remove 
			  the subtree with the highest priority from the min-heap. 
			  Also when merging two subtrees, set the subtree with the lower 
			  priority as the left subtree (whose code is 0), 
			  and the subtree with the higher priority as the right subtree 
			  (whose code is 1).
			*/
			string temp1 = find_smallest(tree, i);
			string temp2 = find_smallest(tree, *node1);

			//cout << "temp1 = " << temp1 << " " << "temp2 = " << temp2 << std::endl;

			if (temp1 < temp2){
				//node i smaller than any node in node node1
				*node2 = *node1;
				*node1 = i;
				continue;
			}else{
				*node2 = i;
				continue;
			}


		}else if (tree[i].weight < weight){
			weight = tree[i].weight;
			*node2 = i;
		}
	}

	if (tree[*node1].lchild < tree[*node2].lchild){
		int temp;
		temp = *node1;
		*node1 = *node2;
		*node2 = temp;
	}
}


void Huff_Tree(Huff_Node tree[], long int weight[], string label[], uint32_t len){
	for (int i = 0; i < 2 * len - 1; i++) tree[i].init();
	
	for (int i = 0; i < len; i++){
		tree[i].name = label[i];
		tree[i].weight = weight[i];
	}

	for (int i = len; i < 2 * len - 1; i++){
		int node1 = 0;
		int node2 = 0;

		Huff_merge(tree, &node1, &node2, i); // merge node1 and node2 to node i

		tree[node1].parent = i;
		tree[node2].parent = i;
		tree[i].weight = tree[node1].weight + tree[node2].weight;
		tree[i].lchild = node1;
		tree[i].rchild = node2;
	}
}

/*S and T have the same weight, and the smallest character (in ASCII value)
  in any of S's leaves is smaller than that in any of T's leaves.
  Under this definition, the delete operation should remove 
  the subtree with the highest priority from the min-heap. 
  Also when merging two subtrees, set the subtree with the lower 
  priority as the left subtree (whose code is 0), 
  and the subtree with the higher priority as the right subtree 
  (whose code is 1).
*/


void Huff_Code(Huff_Node tree[], int len){

	for (int i = 0; i < len; i++){
		string temp = "";
		int j = i;

		// find the parent root from leave nodes
		while (tree[j].parent != -1){
			int parent = tree[j].parent;

			if (j == tree[parent].lchild) temp = "0" + temp;
			else temp = "1" + temp;

			j = tree[j].parent;
		}

		tree[i].code = temp;
	}
}

void encode_output(Huff_Node tree[], string str, table count){
	cout << "HUFFMAN" << '\0';

	int mark = 0;

	for (int i = 0; i <= 255; i++){
		char mid = i;
		string temp = "";
		temp.push_back(mid);
		int isEq = 0;
		int j = 0;

		while (isEq == 0 && j < count.len){
			if (count.tbl[j].name.compare(temp) == 0){
				//cout << count.tbl[j].num << endl;
				fwrite(&count.tbl[j].num, 1, 4, stdout);
				isEq = 1;
			}

			j++;
		}
		
		if (isEq == 0){
			uint32_t zero = 0;
			fwrite(&zero, 1, 4, stdout);
			//cout << 0 << endl;
		}
	}

	//------------------------ compressed data --------------------------

	string compressed = "";
	for (int i = 0; i < str.length(); i++){
		string temp = str.substr(i, 1);
		for (int j = 0; j < count.len; j++){
			if (tree[j].name.compare(temp) == 0) compressed = tree[j].code + compressed;
		}
	}

	long int pos = 0;

	while (pos < compressed.length()){
		uint8_t temp;
		temp = stoi(compressed.substr(pos,8), nullptr, 2);
		fwrite(&temp, 1, 1, stdout);
		pos += 8;
	}


}

void encode(){

	str = "";
	char mid;
	while (cin.get(mid)) str.push_back(mid);

	table count;
	count.init();
	
	//cout << 1 << endl;
	for (int i = 0; i < str.length(); i++) count.add(str.substr(i, 1));
	
	Huff_Node tree[2000];
	string label[2000];
	long int weight[2000];


	for (int i = 0; i < count.len; i++){
		label[i] = count.tbl[i].name;
		weight[i] = count.tbl[i].num;
	}

	Huff_Tree(tree, weight, label, count.len);

	Huff_Code(tree, count.len);

	/*
	for (int i = 0; i < count.len; i++){
		cout << tree[i].name << " " << tree[i].weight << " " << tree[i].code << endl;
	}
	*/
	//cout << str.length() << endl;
	encode_output(tree, str, count);



}

void decode(){
	
}

int main(){

	for (int i = 1; i <= 6; i++) str += cin.get();

	if (str.compare("ENCODE") == 0) encode();
	else if (str.compare("DECODE") == 0) decode();

	//else encode();


	//cout << str;

	return 0;
}