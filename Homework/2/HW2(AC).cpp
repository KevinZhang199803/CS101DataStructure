#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>

using namespace std; 

long int minHeap[100000];
long int maxHeap[100000];
long int input[100000];
int minHeapNum = 1, maxHeapNum = 1;
int input_len = 2, input_current = 2;

void print_result(){
	double median = 0.0;
	median = (double) (minHeap[1] + maxHeap[1]) / 2;
	long int median_int = floor(median);

	if ((maxHeapNum + minHeapNum) % 2 == 0) {
		if (median == median_int) cout << median_int << endl;
		else printf("%.1f\n", median);
	}else{
		if (maxHeapNum > minHeapNum) cout << maxHeap[1] << endl;
		else cout << minHeap[1] << endl;
	}
	

	long int min_layer = log(minHeapNum) / log(2);
	long int max_layer = log(maxHeapNum) / log(2);
	long int count = 1;
	string result = "";

	for (long int i = 0; i <= min_layer; i++) // layer
	{
		for (long int j = 1; j <= (int) pow(2, i); j++){
			if (count <= minHeapNum){
				result += to_string(minHeap[count]);
				result += " ";
				count++;
			}else{
				result += "S ";
				count++;
			}

		}
		result = result.erase(result.rfind(" ")) + "\n";
	}

	count = 1;
	for (long int i = 0; i <= max_layer; i++) // layer
	{
		for (long int j = 1; j <= (int) pow(2, i); j++){
			if (count <= maxHeapNum){
				result += to_string(maxHeap[count]);
				result += " ";
				count++;
			}else{
				result += "S ";
				count++;
			}

		}
		result = result.erase(result.rfind(" ")) + "\n";
	}
	cout << result;
}

void maxHeapPush(long int val){
	maxHeapNum++;
	maxHeap[maxHeapNum] = val;

	int i = maxHeapNum;
	while (i >> 1 != 0 && maxHeap[i] > maxHeap[i >> 1]){
		long int temp = maxHeap[i];
		maxHeap[i] = maxHeap[i >> 1];
		maxHeap[i >> 1] = temp;
		i = i >> 1;
	}
}

void minHeapPush(long int val){
	minHeapNum++;
	minHeap[minHeapNum] = val;
		
	int i = minHeapNum;
	while (i >> 1 != 0 && minHeap[i] < minHeap[i >> 1]){
		long int temp = minHeap[i];
		minHeap[i] = minHeap[i >> 1];
		minHeap[i >> 1] = temp;
		i = i >> 1;
	}
}

long int maxHeapPop(){
	long int val = maxHeap[1];

	maxHeap[1] = maxHeap[maxHeapNum];
	maxHeapNum -= 1;
	long int i = 1;

	while (i << 1 <= maxHeapNum && (maxHeap[i] < maxHeap[i << 1] || maxHeap[i] < maxHeap[((i << 1) + 1)])){
		if (i << 1 == maxHeapNum){
			long int temp = maxHeap[i];
			maxHeap[i] = maxHeap[i << 1];
			maxHeap[i << 1] = temp;
			break;
		}else if (maxHeap[i] < maxHeap[i << 1] && maxHeap[i] < maxHeap[(i << 1) + 1]){
			if (maxHeap[i << 1] >= maxHeap[(i << 1) + 1]){
				long int temp = maxHeap[i];
				maxHeap[i] = maxHeap[i << 1];
				maxHeap[i << 1] = temp;
				i = i << 1;
			}else{
				long int temp = maxHeap[i];
				maxHeap[i] = maxHeap[(i << 1) + 1];
				maxHeap[(i << 1) + 1] = temp;
				i = (i << 1) + 1;
			}
		}else if (maxHeap[i] < maxHeap[i << 1]){
			long int temp = maxHeap[i];
			maxHeap[i] = maxHeap[i << 1];
			maxHeap[i << 1] = temp;
			i = i << 1;
		}else{
			long int temp = maxHeap[i];
			maxHeap[i] = maxHeap[(i << 1) + 1];
			maxHeap[(i << 1) + 1] = temp;
			i = (i << 1) + 1;
		}
	}
	return val;
}

long int minHeapPop(){
	long int val = minHeap[1];

	minHeap[1] = minHeap[minHeapNum];
	minHeapNum -= 1;
	long int i = 1;

	
	while (i << 1 <= minHeapNum && (minHeap[i] > minHeap[i << 1] || minHeap[i] > minHeap[((i << 1) + 1)])){
		if (i << 1 == minHeapNum){
			long int temp = minHeap[i];
			minHeap[i] = minHeap[i << 1];
			minHeap[i << 1] = temp;
			break;
		}else if (minHeap[i] > minHeap[i << 1] && minHeap[i] > minHeap[(i << 1) + 1]){
			if (minHeap[i << 1] <= minHeap[(i << 1) + 1]){
				long int temp = minHeap[i];
				minHeap[i] = minHeap[i << 1];
				minHeap[i << 1] = temp;
				i = i << 1;
			}else{
				long int temp = minHeap[i];
				minHeap[i] = minHeap[(i << 1) + 1];
				minHeap[(i << 1) + 1] = temp;
				i = (i << 1) + 1;
			}
		}else if (minHeap[i] > minHeap[i << 1]){
			long int temp = minHeap[i];
			minHeap[i] = minHeap[i << 1];
			minHeap[i << 1] = temp;
			i = i << 1;
		}else{
			long int temp = minHeap[i];
			minHeap[i] = minHeap[(i << 1) + 1];
			minHeap[(i << 1) + 1] = temp;
			i = (i << 1) + 1;
		}
	}
	return val;
}

void balance(){
	if ((maxHeapNum + minHeapNum) % 2 == 0) {
		if (maxHeapNum > minHeapNum){
			while (maxHeapNum != minHeapNum) {
				long int temp = maxHeapPop();
				minHeapPush(temp);
			}
		}else if (maxHeapNum < minHeapNum) {
			while (maxHeapNum != minHeapNum){
				long int temp = minHeapPop();
				maxHeapPush(temp);
			}
		}else{
			return;
		}
	}else{
		if (maxHeapNum > minHeapNum){
			while (maxHeapNum != minHeapNum + 1) minHeapPush(maxHeapPop());
		}else if (maxHeapNum < minHeapNum){
			while (maxHeapNum + 1 != minHeapNum) maxHeapPush(minHeapPop());
		}else{
			return;
		}
	}
}

int main(){
	string str_input;
	int pos;

	//---------- input part -------------------

	getline(cin, str_input);
	pos = str_input.find(" ");
	input[1] = stoi(str_input.substr(0, pos));
	input[2] = stoi(str_input.substr(pos + 1, str_input.length()));

	while (getline(cin, str_input)){
		input_len++;
		input_current++;
		input[input_current] = stoi(str_input);
	}

	//----------input ends--------------------
	minHeap[1] = max(input[1], input[2]);
	maxHeap[1] = min(input[1], input[2]);
	print_result();

	for (long int j = 3; j <= input_len; j++){
		if (input[j] < maxHeap[1]) maxHeapPush(input[j]);
		else minHeapPush(input[j]);
		balance();
		print_result();
	}

	return 0;
}
