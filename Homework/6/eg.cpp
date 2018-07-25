#include<iostream>
#include<string>
#include<cstdio>

using namespace std;

class node{
	public:
		int indegree;
		bool isInGraph;
};

int num;
string names[100], result, final_result;
bool adj_mat[27][27];
node indegree[27];

void readin(){
	int i, j;
	scanf("%d\n", &num);

	for (i = 1; i <= 26; i++){
		for (j = 1; j <= 26; j++) adj_mat[i][j] = false;
	}

	for (i = 0; i < num; i++){

		string temp;
		getline(cin, temp);

		for (j = 0; j < temp.length(); j++){
			if (temp[j] >= 'A' && temp[j] <= 'Z') temp[j] += 32;
		}
	
		int begin = 0;

		begin = temp.find(" ", begin);

		while (begin != -1){
			temp.replace(begin, 1, "");
			begin = temp.find(" ", begin);
		}

		names[i] = temp;
	}

	for (i = 0; i < num - 1; i++){

		int pos = 0;
		bool islink = false;
		string pre = names[i];
		string post = names[i + 1];

		while (pos < pre.length() && pos < post.length()){

			if (pre[pos] == post[pos]){

				pos++;
				continue;
			}else{

				adj_mat[pre[pos] - 96][post[pos] - 96] = true;
				pos++;
				islink = true;
				break;
			}
		}
		if (!islink){

			if (pre.length() > post.length()){
				cout << "另请高明吧";
				exit(0);
			}
		}
	}
}

void degreed(){

	for (int i = 1; i <= 26; i++){
		
		indegree[i].indegree = 0;
		indegree[i].isInGraph = true;

		for (int j = 1; j <= 26; j++){	
			if (adj_mat[j][i]) indegree[i].indegree++;
		}

		if (indegree[i].indegree == 0){

			bool isIsolate = true;

			for (int k = 1; k <= 26; k++){
				if (adj_mat[i][k]) isIsolate = false;
			}

			if (isIsolate) indegree[i].isInGraph = false;
		}
	}
}

void select(){
	int i, j, left_num, selected_num = 0;
	int selected[27];

	for (i = 1; i <= 26; i++) selected[i] = -1;

	for (i = 1; i <= 26; i++){

		if (!indegree[i].isInGraph) continue;
		else{

			selected[i] = indegree[i].indegree;
			selected_num++;
		}
	}

	left_num = selected_num;
	result = "";

	for (i = 0; i < selected_num; i++){

		for (j = 1; j <= 26; j++){
			
			if (selected[j] == 0){

				char temp = j + 96;
				result += temp;

				for (int k = 1; k <= 26; k++){
					if (adj_mat[j][k]) selected[k]--;
				}
				selected[j] = -1;
				break;
			}
		}

		if (j == 27){
			bool isCircle = true;

			if (i == selected_num - 1) isCircle = false;

			for (int k = 1; k <= 26; k++){
				if (selected[k] == 0) isCircle = false;
				break;
			}

			if (isCircle){
				
				cout << "另请高明吧";
				exit(0);
			}
		}
	}
}

void print(){

	int i, j, pos = 0;
	string not_selected = "";
	final_result = "";

	for (i = int('a'); i <= int('z'); i++){
		char letter = i;
		if (result.find(letter) == -1) not_selected += letter;
	}
	for (i = 0; i < 26; i++){

		if (not_selected == ""){
			final_result += result;
			break;
		}else if (result == ""){
			final_result += not_selected;
			break;
		}else if (not_selected[0] > result[0]){
			final_result += result[0];
			result = result.substr(1);
		}else if (not_selected[0] < result[0]){
			final_result += not_selected[0];
			not_selected = not_selected.substr(1);
		}
	}
	cout << final_result;
}

int main(){
	readin();
	degreed();
	select();
	print();

	return 0;
}