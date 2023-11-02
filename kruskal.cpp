#include <stdio.h>
#include <stdlib.h>
int total = 0, parent[40001];
typedef struct node* nodePointer;

struct node
{
	int vertex,weight;
	nodePointer link;
};
nodePointer graph[40001];

struct edge 
{
    int a, b, w;
}e[40001];

int cmp(const void *a, const void *b)
{
    struct edge* ea = (struct edge*)a;
    struct edge* eb = (struct edge*)b; 
    return ea->w - eb->w;
}

int find(int x)
{
    if(x == parent[x]) return x;
    else return parent[x] = find(parent[x]);
}

void merge(int x, int y)
{
    parent[find(x)] = find(y);
}

void kruskal(int vertexnum, int edgesnum)
{
	printf("\nminimum spanning tree:\n");
    for(int i = 0; i < vertexnum; i++) {parent[i] = i;}
	qsort(e, edgesnum, sizeof(e[0]), cmp);
	for(int i = 0, j = 0; i < vertexnum - 1 && j < edgesnum; i++)
	{
		while(find(e[j].a) == find(e[j].b)) j++;
		merge(e[j].a, e[j].b);
		printf("%d: <%d,%d>\n", i + 1, e[j].a, e[j].b);
		total += e[j].w;
		j++;
	}
}

int main()
{
	int a, b, w, vertexnum = -1, edgesnum = 0;
	nodePointer temp, ptr;
	for(int i = 0; i < 40001; i++) 
	{
		graph[i] = (nodePointer)malloc(sizeof(struct node));
		graph[i]->vertex = i;
		graph[i]->weight = -1;
		graph[i]->link = NULL;
	}
	while(scanf("%d %d %d", &a, &b, &w)!= EOF)
	{
		if(a > b && a > vertexnum) vertexnum = a;
		else if(b > a && b > vertexnum) vertexnum = b; 

		e[edgesnum].a = a;
		e[edgesnum].b = b;
		e[edgesnum].w = w;
		edgesnum++;

		temp = (nodePointer)malloc(sizeof(nodePointer));
		temp->vertex = b;
		temp->weight = w;
		temp->link = NULL;

		for (ptr = graph[a]; ptr->link; ptr = ptr->link);
		ptr->link = temp;

		temp = (nodePointer)malloc(sizeof(struct node));
		temp->vertex = a;
		temp->weight = w;
		temp->link = NULL;

		for (ptr = graph[b]; ptr->link; ptr = ptr->link);
		ptr->link = temp;
	}
	printf("Adjacency list:\n");
	for(int i = 0; i <= vertexnum; i++)
	{
		printf("%d: ", i);
		for(ptr = graph[i]->link; ptr != NULL; ptr = ptr->link)
		{
			printf("%d -> ", ptr->vertex);
		}
		printf("end\n");
	}
	kruskal(vertexnum + 1, edgesnum);
	printf("Make it conflict\n");
}