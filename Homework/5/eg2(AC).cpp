#include<iostream>
#include<cstdio>

using namespace std;

class edge
{
	public:
		long int city1;
		long int city2;

		long int weight;
};

class counter
{
	public:
		long int city_num;
		long int times;
};

long int city_num, road_num, region_num, selected;
edge* Edge;
edge* selected_edge;
long int* parent;

int weight_cmp(edge edge1, edge edge2){

	if (edge1.weight > edge2.weight) return 1;
	else if (edge1.weight < edge2.weight) return -1;
	else if (min(edge1.city1, edge1.city2) < min(edge2.city1, edge2.city2)) return -1;
	else if (min(edge1.city1, edge1.city2) == min(edge2.city1, edge2.city2) && max(edge1.city1, edge1.city2) < max(edge2.city1, edge2.city2)) return -1;
	else return 1;
}

class region{

	public:
		long int element_num;
		long int min_city;
		long int road_in_region;
		edge* list;

		void init(long int n);
		void push(edge new_edge);
		void sort();

	private:
		void minHeap_edge(long int start, long int end);
		void Heap_sort_edge_dec(long int length);
};

void region::init(long int n){

	element_num = 0;
	road_in_region = n;
	min_city = city_num;
	list = new edge[n];
}

void region::push(edge new_edge){

	list[element_num] = new_edge;
	element_num++;

	if (min_city > min(new_edge.city1, new_edge.city2)) min_city = min(new_edge.city1, new_edge.city2);
}

void region::minHeap_edge(long int start, long int end){

	long int c = start;
	long int l = 2 * c + 1;
	edge temp = list[c];

	for (; l <= end; c = l, l = 2 * l + 1){

		if (l < end && weight_cmp(list[l], list[l + 1]) == 1) l++;

		if (weight_cmp(temp, list[l]) == -1) break;
		else {
			list[c] = list[l];
			list[l] = temp;
		}

	}
}

void region::Heap_sort_edge_dec(long int length){

	for (long int i = length / 2 - 1; i >= 0; i--) minHeap_edge(i, length - 1);

	for (long int i = length - 1; i > 0; i--){

		edge temp = list[0];
		list[0] = list[i];
		list[i] = temp;

		minHeap_edge(0, i - 1);
	}
}

void region::sort(){

	Heap_sort_edge_dec(element_num);
}

region* region_list;

void maxHeap_edge(edge Edge[], long int start, long int end){

	long int c = start;
	long int l = 2 * c + 1;
	edge temp = Edge[c];

	for (;l <= end; c = l, l = 2 * l + 1){

		if (l < end && weight_cmp(Edge[l], Edge[l + 1]) == -1) l++;
		
		if (weight_cmp(temp, Edge[l]) == 1) break;
		else {

			Edge[c] = Edge[l];
			Edge[l] = temp;
		}
	}
}

void Heap_sort_inc(edge Edge[], long int length){

	for (long int i = length / 2 - 1; i >= 0; i--) maxHeap_edge(Edge, i, length - 1);

	for (long int i = length - 1; i > 0; i--){
		edge temp = Edge[0];
		Edge[0] = Edge[i];
		Edge[i] = temp;

		maxHeap_edge(Edge, 0, i - 1);
	}
}

void q_sort_edge(edge Edge[], long int start, long int end){

	if (start < end){

		long int left_mark = start, right_mark = end;
		edge mark = Edge[start];

		while (left_mark < right_mark){

			while (left_mark < right_mark && weight_cmp(Edge[right_mark], mark) == 1) right_mark--;
			if (left_mark < right_mark){

				Edge[left_mark] = Edge[right_mark];
				left_mark++;
			}

			while (left_mark < right_mark && weight_cmp(Edge[left_mark], mark) == -1) left_mark++;
			if (left_mark < right_mark){

				Edge[right_mark] = Edge[left_mark];
				right_mark--;
			}

		}
		Edge[left_mark] = mark;
	
		q_sort_edge(Edge, start, right_mark - 1);
		q_sort_edge(Edge, right_mark + 1, end);
	}
}

long int find(long int n){

	if (parent[n] == n) return n;
	else {

		parent[n] = find(parent[n]);
		return parent[n];
	}
}

void set_union(long int a, long int b){

	long int a_p = find(a);
	long int b_p = find(b);

	if (a_p != b_p) parent[b_p] = a_p;
}

int region_cmp(region a, region b){

	if (a.element_num > b. element_num) return 1;
	else if (a.element_num < b. element_num) return -1;
	else if (a.min_city > b.min_city) return 1;
	else return -1;
}

void q_sort_region(long int start, long int end){

	if (start < end){

		long int left_mark = start, right_mark = end;
		region mark = region_list[start];

		while (left_mark < right_mark){

			while (left_mark < right_mark && region_cmp(region_list[right_mark], mark) == -1) right_mark--;
			if (left_mark < right_mark){

				region_list[left_mark] = region_list[right_mark];
				left_mark++;
			}

			while (left_mark < right_mark && region_cmp(region_list[left_mark], mark) == 1) left_mark++;
			if (left_mark < right_mark){

				region_list[right_mark] = region_list[left_mark];
				right_mark--;
			}
		}
		region_list[left_mark] = mark;

		q_sort_region(start, right_mark - 1);
		q_sort_region(right_mark + 1, end);
	}

}

void read_in(){

	scanf("%ld", &city_num);
	scanf("%ld", &road_num);
	scanf("%ld", &region_num);

	if (city_num <= region_num){

		printf("[\n");

		for (long int i = 0; i < city_num; i++){
			printf("[\n]");

			if (i != city_num - 1) printf(",");
			printf("\n");
		}

		printf("]");
		exit(0);

	}

	Edge = new edge[road_num];
	parent = new long int[city_num];
	selected_edge = new edge[city_num - region_num];

	for (long int i = 0; i < road_num; i++){

		scanf("%ld %ld %ld", &Edge[i].city1, &Edge[i].city2, &Edge[i].weight);

		if (Edge[i].city1 > Edge[i].city2){

			long int temp = Edge[i].city1;
			Edge[i].city1 = Edge[i].city2;
			Edge[i].city2 = temp;

		}
	}
	q_sort_edge(Edge, 0, road_num - 1);
}

void Kruskal(){

	for (long int i = 0; i < city_num ; i++) parent[i] = i;
	long int edge_now = 0;
	selected = 0;

	while (selected < city_num - region_num && edge_now < road_num){

		if (find(Edge[edge_now].city1) != find(Edge[edge_now].city2)){

			set_union(Edge[edge_now].city1, Edge[edge_now].city2);
			selected_edge[selected] = Edge[edge_now];

			selected++;
			edge_now++;

		}else edge_now++;
	}
}

void region_set(){

	region_list = new region[city_num - selected];
	counter region_num[city_num];
	long int region_num_pos = 0;

	for (long int i = 0; i < selected; i++){
		long int temp = find(selected_edge[i].city1);
		bool isExist = false;

		for (long int j = 0; j < region_num_pos; j++){

			if (region_num[j].city_num == temp) {
				isExist = true;
				region_num[j].times++;
				break;
			}
		}

		if (!isExist){

			region_num[region_num_pos].city_num = temp;
			region_num[region_num_pos].times = 1;
			region_num_pos++;
		}
	}

	for (long int i = 0; i < city_num - selected; i++) region_list[i].init(region_num[i].times);

	for (long int i = 0; i < selected; i++){
		long int temp;

		for (long int j = 0; j < region_num_pos; j++){

			if (region_num[j].city_num == find(selected_edge[i].city1)){
				temp = j;
				break;
			}

		}
		region_list[temp].push(selected_edge[i]);
	}

	for (long int i = 0; i < city_num - selected; i++) {
		if (region_list[i].element_num >= 2) region_list[i].sort();
	}
	q_sort_region(0, city_num - selected - 1);
	
}

void print(){

	printf("[\n");

	for (long int i = 0; i < city_num - selected; i++){
		printf("[\n");

		for (long int j = 0; j < region_list[i].element_num; j++){
			printf("[%ld,%ld,%ld]", region_list[i].list[j].city1, region_list[i].list[j].city2, region_list[i].list[j].weight);
			if (j != region_list[i].element_num - 1) printf(",");
			printf("\n");
		}

		printf("]");
		if (i != city_num - selected - 1) printf(",");
		printf("\n");
	}

	printf("]");
}

int main()
{
	read_in();
	Kruskal();
	region_set();
	print();

	return 0;
}