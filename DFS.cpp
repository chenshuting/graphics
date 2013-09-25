/*
 * =====================================================================================
 *
 *       Filename:  DFS.cpp
 *
 *    Description: Build deapth first tree through graphics
 *
 *        Version:  1.0
 *        Created:  2013/09/24 10时43分37秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Chen Shuting (cst), cicy0125@gmail.com
 *        Company:  gucas.ict.bwstor
 *
 * =====================================================================================
 */

#include <iostream>
using namespace std;

const int vertex_num = 8;
typedef enum color{white=0,gray, black}color_t;
const int NIL = -1;
const int begin = 0;
const int finish = 1;

int adj[vertex_num][vertex_num] = {0};
int ancestors[vertex_num] = {0};
color color[vertex_num];
int timeCnt = 0;
int timestamp[2][vertex_num] = {0};

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
	}
	init_adj();
}

void dfs_visit(int node)
{
	color[node] = gray;
	timestamp[begin][node] = ++timeCnt;
	for (int i = 0; i < vertex_num; i++) {
		if (adj[node][i] == 1 && color[i] == white) {
			ancestors[i] = node;
			dfs_visit(i);
		}
	}
	color[node] = black;
	timestamp[finish][node] = ++timeCnt;
}

void print_info()
{
	for (int i = 0; i < vertex_num; i++) {
		cout << "Node[" << i << "]: timestamp<" << timestamp[begin][i] << "," 
			<< timestamp[finish][i] << ">, ancestors node <" << ancestors[i] << ">" << endl;
	}
}

int main()
{
	init_data();

	for (int i = 0; i < vertex_num; i++) {
		if (color[i] == white)
			dfs_visit(i);
	}

	print_info();

	return 0;
}



