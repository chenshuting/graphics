/*
 * =====================================================================================
 *
 *       Filename:  BFS.cpp
 *
 *    Description: Build breadth first tree through graphics
 *
 *        Version:  1.0
 *        Created:  2013/09/23 15时40分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Shuting (cst), cicy0125@gmail.com
 *        Company:  gucas.ict.bwstor
 *
 * =====================================================================================
 */

#include <iostream>
#include <deque>
using namespace std;

const int infinity = ((int)(~0U >> 1));
const int vertex_num = 8;
typedef enum color{white=0,gray, black}color_t;
const int root = 0;
const int NIL = -1;

int adj[vertex_num][vertex_num] = {0};
int ancestors[vertex_num] = {0};
int distances[vertex_num] = {0};//the distance between root and current node
color color[vertex_num];

void init_adj()
{
	adj[0][1] = 1;
	adj[1][0] = 1;
	adj[0][3] = 1;
	adj[3][0] = 1;
	adj[1][2] = 1;
	adj[2][1] = 1;
	adj[3][7] = 1;
	adj[7][3] = 1;
	adj[3][4] = 1;
	adj[4][3] = 1;
	adj[4][7] = 1;
	adj[7][4] = 1;
	adj[4][5] = 1;
	adj[5][4] = 1;
	adj[4][6] = 1;
	adj[6][4] = 1;
	adj[5][6] = 1;
}
void init_data()
{
	for (int i = 0; i < vertex_num; i++) {
		color[i] = white;
		ancestors[i] = NIL;
		distances[i] = infinity;
	}
	init_adj();
	color[root] = gray;
	distances[root] = 0;
}

void print_info()
{
	for (int i = 0; i < vertex_num; i++) {
		cout << "Node[" << i << "]: distances to root<" << distances[i] << ">, ancestors node <" << ancestors[i] << ">" << endl;
	}
}

int main()
{
	init_data();
	deque<int> queue;
	
	queue.push_back(root);
	while (queue.size() > 0) {
		int pos = queue.front();
		queue.pop_front();
		for (int i = 0; i < vertex_num; i++) {
			if (adj[pos][i] == 1 && color[i] == white) {
				color[i] = gray;
				distances[i] = distances[pos] + 1;
				ancestors[i] = pos;
				queue.push_back(i);
			}
		}
		color[pos] = black;
	}

	print_info();

	return 0;
}



