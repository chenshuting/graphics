/*
 * =====================================================================================
 *
 *       Filename:  kruskal.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013/09/25 10时39分18秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Shuting (cst), cicy0125@gmail.com
 *        Company:  gucas.ict.bwstor
 *
 * =====================================================================================
 */

#include <iostream>
#include <vector>
using namespace std;

struct edge{
	int pointA;
	int pointB;
	int weight;
};

const int infinity = (int)(~0UL) >> 1;
const int vertex_num = 9;
const int edge_num = 14;
string vertexs[vertex_num] = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};
enum vertex_name{a = 0, b, c, d, e, f, g, h, i};
enum state{signal, group}; 
typedef vector<int> TREE_NODE;
const int root_parent = -1;
const int max_child = vertex_num - 1;

struct edge edges[edge_num];
int ancestors[vertex_num];
int child_nums[vertex_num];
vector<TREE_NODE *> forest;

void make_set()
{
	for (int index = a; index <=i; index++){
		TREE_NODE* node = new TREE_NODE();
		node->push_back(index);
		forest.push_back(node);
	}
}

TREE_NODE *find_set(int node)
{
	bool find = false;
	TREE_NODE *tree; 

	for (vector<TREE_NODE *>::iterator iter = forest.begin();
			iter != forest.end(); iter++)
	{
		tree = *iter;
		for (vector<int>::iterator iterB = tree->begin();
				iterB != tree->end(); iterB++) {
			if (node == *iterB) {
				find = true;
				break;
			}
		}
		if (find) {
			forest.erase(iter);
			return tree;
		}
	}
	return NULL;
}

void init_edges()
{
	edges[0].pointA = a;
	edges[0].pointB = b;
	edges[0].weight = 4;

	edges[1].pointA = b;
	edges[1].pointB = c;
	edges[1].weight = 8;

	edges[2].pointA = a;
	edges[2].pointB = h;
	edges[2].weight = 8;

	edges[3].pointA = b;
	edges[3].pointB = h;
	edges[3].weight = 11; 

	edges[4].pointA = h;
	edges[4].pointB = i;
	edges[4].weight = 7;

	edges[5].pointA = h;
	edges[5].pointB = g;
	edges[5].weight = 1;

	edges[6].pointA = c;
	edges[6].pointB = i;
	edges[6].weight = 2;

	edges[7].pointA = c;
	edges[7].pointB = f;
	edges[7].weight = 4;

	edges[8].pointA = g;
	edges[8].pointB = f;
	edges[8].weight = 2;

	edges[9].pointA = c;
	edges[9].pointB = d;
	edges[9].weight = 7;

	edges[10].pointA = d;
	edges[10].pointB = f;
	edges[10].weight = 14;

	edges[11].pointA = d;
	edges[11].pointB = e;
	edges[11].weight = 9;

	edges[12].pointA = e;
	edges[12].pointB = f;
	edges[12].weight = 10;

	edges[13].pointA = i;
	edges[13].pointB = g;
	edges[13].weight = 6;
}

void init_data()
{
	for (int index = a; index <= i; index++) {
		ancestors[index] = root_parent;
		child_nums[index] = 0;
	}

	init_edges();
}

void swap(struct edge &edge1, struct edge &edge2) 
{
	int tmp;
	tmp = edge1.pointA;
	edge1.pointA = edge2.pointA;
	edge2.pointA = tmp;

	tmp = edge1.pointB;
	edge1.pointB = edge2.pointB;
	edge2.pointB = tmp;

	tmp = edge1.weight;
	edge1.weight = edge2.weight;
	edge2.weight = tmp;
}

void print_edges()
{
	for (int pos = 0; pos < edge_num; pos++) {
		cout << edges[pos].weight << " ";
	}
	cout << endl;
}

void sort_edges()
{
	for (int pos1 = 0; pos1 < edge_num - 1; pos1++) {
		for (int pos2 = 0; pos2 < edge_num - pos1 - 1; pos2++) {
			if (edges[pos2+1].weight < edges[pos2].weight) {
				swap(edges[pos2+1], edges[pos2]);
			}
		}
	}
	cout << "After sort:>"; 
	print_edges();
}

//combine two sepearted trees
void combine_trees(TREE_NODE* node1, TREE_NODE* node2)
{
	for (TREE_NODE::iterator iter = node2->begin();
			iter != node2->end(); iter++) {
		node1->push_back(*iter);
	}
	node2->clear();
	forest.push_back(node1);
}

void print_forest()
{
	for (vector<TREE_NODE *>::iterator iter = forest.begin(); 
			iter != forest.end(); iter++) {
		TREE_NODE *node = *iter;
		cout << "{" ;
		for (TREE_NODE::iterator iterN = node->begin();
				iterN != node->end(); iterN++) {
			cout << vertexs[*iterN] << " ";
		}
		cout << "}, ";
	}
	cout << endl;
}

/* *
 * Adjust node to the root of the tree
 * */
void adjust_to_root(int node)
{
	if (ancestors[node] != root_parent) {
		int parent = ancestors[node];
		if (ancestors[parent] != root_parent) {
			adjust_to_root(parent);
		}
		ancestors[parent] = node;
		ancestors[node] = root_parent;

		child_nums[node] +=1;
		child_nums[parent] -= 1;
		cout << "parent " << vertexs[parent] << " to child, child "<< vertexs[node] << " to parent" << endl; 
	}
}

/* *
 * adjust tree structure, and combine tree1 and tree2 which contains
 * node1 and node2 seperately
 * */
void adjust_tree_structure(int node1, int node2)
{
	adjust_to_root(node2);

	ancestors[node2] = node1;
	child_nums[node1] += 1;
}

TREE_NODE *kruskal()
{
	int index = 0;
	//generate forest 
	make_set();
	//sort edges by weight
	sort_edges();

	//generate min weight tree
	while(forest.size() > 1 && index < edge_num){
		TREE_NODE *set1 = find_set(edges[index].pointA);
		TREE_NODE *set2 = find_set(edges[index].pointB);
		
		if (set1 != NULL && set2!= NULL) {
			adjust_tree_structure(edges[index].pointA, edges[index].pointB);
			combine_trees(set1, set2);
		} else if (set1 != NULL)
			forest.push_back(set1);
		else if (set2 != NULL)
			forest.push_back(set2);

		print_forest();
		index++;
	}
	
	return forest[0];
}

void print_tree()
{
	for (int i = 0; i < vertex_num; i++) {
		int parent = ancestors[i];
		if (parent == root_parent)
			cout << "node[" << vertexs[i] << "] is root!" << endl; 
		else
			cout << "node[" << vertexs[i] << "]'s parent is " << vertexs[parent] << endl; 
	}
}

bool check_if_valid()
{
	bool flag = true;
	int edge_num_array[vertex_num] = {0};

	for (int index = 0; index < edge_num; index++) {
		edge_num_array[edges[index].pointA]++;
		edge_num_array[edges[index].pointB]++;
	}

	for (int index = 0; index < vertex_num; index++) {
		if (edge_num_array[index] == 0){
			flag = false;
			break;
		}
	}
	return flag;
}

int main()
{
	init_data();

	if (check_if_valid()) {
		kruskal();
		print_tree();
	} else {
		cout << "Not all the nodes are connected!" << endl;
	}
	return 0;
}
