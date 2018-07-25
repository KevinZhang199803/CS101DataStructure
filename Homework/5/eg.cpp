#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>

#define MAXINT 1000000

using namespace std;

class edge
{
	public:
		long int city1;
		long int city2;

		long int weight;
};

long int city_num, road_num, region_num, selected_edge_pos;

edge Edge[MAXINT], selected_edge[MAXINT];

long int parent[MAXINT];

int weight_cmp(edge edge1, edge edge2){

	if (edge1.weight > edge2.weight) return 1;
	else if (edge1.weight < edge2.weight) return -1;
	else if (min(edge1.city1, edge1.city2) < min(edge2.city1, edge2.city2)) return -1;
	else if (min(edge1.city1, edge1.city2) == min(edge2.city1, edge2.city2) && max(edge1.city1, edge1.city2) < max(edge2.city1, edge2.city2)) return -1;
	else return 1;

}

void q_sort_edge_inv(edge Edge[], long int start, long int end){

	if (start < end){

		long int left_mark = start, right_mark = end;
		edge mark = Edge[start];

		while (left_mark < right_mark){

			while (left_mark < right_mark && weight_cmp(Edge[right_mark], mark) == -1) right_mark--;

			if (left_mark < right_mark){

				Edge[left_mark] = Edge[right_mark];

				left_mark++;
			}

			while (left_mark < right_mark && weight_cmp(Edge[left_mark], mark) == 1) left_mark++;

			if (left_mark < right_mark){

				Edge[right_mark] = Edge[left_mark];

				right_mark--;
			}

		}

		Edge[left_mark] = mark;
	
		q_sort_edge_inv(Edge, start, right_mark - 1);
		q_sort_edge_inv(Edge, right_mark + 1, end);

	}
}

class maxHeap
{

	public:

		long int element_num;
		long int min_city;
		edge* Heap;

		void init(){

			element_num = 0;
			min_city = city_num;
			Heap = new edge[road_num];

		}

		void push(edge new_edge){

			if (min_city > min(new_edge.city1, new_edge.city2)) min_city = min(new_edge.city1, new_edge.city2);

			Heap[element_num] = new_edge;
			element_num++;

		}

		void sort(){

			//for (long int i = 0; i < element_num; i++) printf("%ld %ld %ld\n", Heap[i].city1, Heap[i].city2, Heap[i].weight);
			q_sort_edge_inv(Heap, 0, element_num - 1);

		}

};

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

int region_cmp(maxHeap region1, maxHeap region2){

	if (region1.element_num > region2.element_num) return 1;
	else if (region1.element_num < region2.element_num) return -1;
	else if (region1.min_city > region2.min_city) return 1;
	else return -1;

}

void q_sort_region(maxHeap region_list[], long int start, long int end){

	if (start < end){

		long int left_mark = start, right_mark = end;
		maxHeap mark = region_list[start];

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
	
	q_sort_region(region_list, start, right_mark - 1);
	q_sort_region(region_list, right_mark + 1, end);	

	}

}

void Read_in(){

	scanf("%ld", &city_num);
	scanf("%ld", &road_num);
	scanf("%ld", &region_num);

	for (long int i = 0; i < road_num; i++){

		scanf("%ld", &Edge[i].city1);
		scanf("%ld", &Edge[i].city2);
		scanf("%ld", &Edge[i].weight);

		if (Edge[i].city1 > Edge[i].city2){

			long int temp = Edge[i].city1;
			Edge[i].city1 = Edge[i].city2;
			Edge[i].city2 = temp;

		}
	}

	//for (long int i = 0; i < road_num; i++) printf("%ld %ld %ld\n", Edge[i].city1, Edge[i].city2, Edge[i].weight);
}

long int find_parent(long int node){

	if (parent[node] == node) {

		return node;

	}else{

		parent[node] = find_parent(parent[node]);

		return parent[node];

	}

}

void set_union(long int a, long int b){

	a = find_parent(a);
	b = find_parent(b);

	if (a != b) parent[b] = a;

}

void Kruskal(){

	for (long int i = 0; i < city_num; i++) parent[i] = i;
	selected_edge_pos = 0;

	for (long int i = 0; i < road_num; i++){

		if (find_parent(Edge[i].city1) != find_parent(Edge[i].city2)){

			set_union(Edge[i].city1, Edge[i].city2);
			selected_edge[selected_edge_pos] = Edge[i];
			selected_edge_pos++;
		}

		if (selected_edge_pos >= city_num - region_num) break;
	}
}

void print_result(){

	maxHeap region_list[city_num];

	for (long int i = 0; i < city_num; i++) region_list[i].init();

	for (long int i = 0; i < selected_edge_pos; i++){

		region_list[find_parent(selected_edge[i].city1)].push(selected_edge[i]);

	}

	q_sort_region(region_list, 0, city_num - 1);

	for (long int i = 0; i < region_num; i++) region_list[i].sort();
	
	printf("[\n");

	for (long int i = 0; i < region_num; i++){

		printf("[\n");

		for (long int j = 0; j < region_list[i].element_num; j++){

			printf("[%ld,%ld,%ld]", region_list[i].Heap[j].city1, region_list[i].Heap[j].city2, region_list[i].Heap[j].weight);

			if (j != region_list[i].element_num - 1) printf(",");

			printf("\n");

		}

		printf("]");

		if (i != region_num - 1) printf(",");

		printf("\n");

	}

	printf("]\n");

}

int main(){

	Read_in();

	q_sort_edge(Edge, 0, road_num - 1);

	//for (long int i = 0; i < road_num; i++) printf("%ld %ld %ld\n", Edge[i].city1, Edge[i].city2, Edge[i].weight);

	Kruskal();

	print_result();

	return 0;

}
