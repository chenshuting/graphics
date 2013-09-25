/*
 * =====================================================================================
 *
 *       Filename:  TOPOLOGICAL.cpp
 *
 *    Description: Build topological sequence through graphics
 *
 *        Version:  1.0
 *        Created:  2013/09/24 11时43分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Shuting (cst), cicy0125@gmail.com
 *        Company:  gucas.ict.bwstor
 *
 * =====================================================================================
 */

#include <iostream>
#include <list>
using namespace std;

typedef enum color{white=0,gray, black}color_t;
const int NIL = -1;
const int begin = 0;
const int finish = 1;
typedef list<int> LISTNODE;

string actions_array[] = {"undershorts", "pants", "belt", "shirt", "tie", "jacket","socks", "shoes", "watch"};
enum actions {undershorts = 0, pants, belt, shirt, tie, jacket,socks, shoes, watch, actions_length};
LISTNODE adj[actions_length];

int ancestors[actions_length] = {0};
color color[actions_length];
int timeCnt = 0;
int timestamp[2][actions_length] = {0};

void init_adj()
{
	adj[undershorts].push_back(pants);
	adj[undershorts].push_back(shoes);
	adj[pants].push_back(shoes);
	adj[pants].push_back(belt);
	adj[belt].push_back(jacket);
	adj[shirt].push_back(belt);
	adj[shirt].push_back(tie);
	adj[tie].push_back(jacket);
	adj[socks].push_back(shoes);
}
void init_data()
{
	for (int i = 0; i < actions_length; i++) {
		color[i] = white;
		ancestors[i] = NIL;
	}
	init_adj();
}

void dfs_visit(int node)
{
	color[node] = gray;
	timestamp[begin][node] = ++timeCnt;
	for (LISTNODE::iterator iter = adj[node].begin();
			iter != adj[node].end(); iter++) {
		if(color[*iter] == white){
			ancestors[*iter] = node;
			dfs_visit(*iter);
		}
	}
	color[node] = black;
	timestamp[finish][node] = ++timeCnt;
}

void print_info()
{
	for (int i = 0; i < actions_length; i++) {
		cout << "Node[" << i << "]: timestamp<" << timestamp[begin][i] << "," 
			<< timestamp[finish][i] << ">, ancestors node <" << ancestors[i] << ">" << endl;
	}
}

void printTopological(LISTNODE& head)
{
	for (LISTNODE::iterator iter = head.begin(); iter != head.end(); iter++) {
		cout << actions_array[*iter] << " ";
	}
	cout << endl;
}

void topological()
{
	int BOUNDARY = 2 * actions_length + 1;
	int prev_max = BOUNDARY;
	int max = 0;
	int pos = 0;
	LISTNODE head;

	for (int i = 0; i < actions_length; i++) {
		for (int i = 0; i < actions_length; i++) {
			if (timestamp[finish][i] < prev_max&& timestamp[finish][i] > max) {
				pos = i;
				max = timestamp[finish][i];
			}
		}
		prev_max = max;
		max = 0;
		head.push_back(pos);	
	}

	printTopological(head);
}

int main()
{
	init_data();

	for (int i = 0; i < actions_length; i++) {
		if (color[i] == white)
			dfs_visit(i);
	}

//	print_info();

	topological();

	return 0;
}



