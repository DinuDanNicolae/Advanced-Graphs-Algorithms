#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define inf 9000000

typedef struct graphAdjMat 
{
    size_t numNodes;       
    double **matrix;             
} graphAdjMat;

typedef struct graphEdge {
    size_t u;       /**< Nodul sursa */ 
    size_t v;       /**< Nodul destinatie */ 
    int w;       /**< Costul muchiei */
} graphEdge;

graphAdjMat *initGraph(size_t numNodes) 
{
    if (numNodes <= 0) {
        printf("initGraph: numarul de noduri trebuie sa fie un numar pozitiv nenul\n");
        return NULL;
    }

    graphAdjMat *g = malloc(sizeof(graphAdjMat));

    g->numNodes = numNodes;
    g->matrix = malloc(numNodes * sizeof(double *));

    int i;
    for (i = 0; i < numNodes; i++) {
        g->matrix[i] = calloc(numNodes, sizeof(double));
    }
    return g;
}

void freeGraph(graphAdjMat **g) 
{
    if (*g == NULL) {
        return;
    }

    /* Eliberez matricea de adiacenta */
    for (size_t u = 0; u < (*g)->numNodes; u++) {
        free((*g)->matrix[u]);
    }
    free((*g)->matrix);

    /* Eliberez structura */
    free(*g);
    *g = NULL;
}

void printPath(int parent[], int j, int orig)
{
    // Base Case : If j is source
    if (parent[j] == -1)
        return;

    printPath(parent, parent[j],orig);
    printf("%d", j);
    
    if(j != orig)
        printf(" ");
}

double Dijkstra(graphAdjMat *mat, int source, int target, int *prev)
{
    int i,start;
    int m,min;
    double d;
    int *visited = calloc(mat->numNodes+1, sizeof(int)); 
    double *dist = calloc(mat->numNodes+1, sizeof(double)); 
    
    for(i=0; i<mat->numNodes; i++)
        {
            dist[i] = inf;
            prev[i] = -1;
        }
    start = source;
    dist[start] = 0;
    visited[start] = 1;
     
    while(visited[target] == 0)
        {
            min = inf;
            m = 0;
            for(i=0; i<mat->numNodes; i++)
                {
                    d = dist[start] + mat->matrix[start][i];

                    if(d < dist[i] && visited[i] == 0)
                        {
                            dist[i] = d;
                            prev[i] = start;
                        } 

                    if(min > dist[i] && visited[i] == 0)
                        {
                            min = dist[i];
                            m = i;
                        }
                }
            start = m;
            visited[start] = 1;    
        }
    double rez = dist[target];
    free(dist);
    free(visited);
    return rez;
    
}

int main()
{
    int n;
    int m;
    int d;
    int i,j;
    int ID_Node1, ID_Node2;
    int nr_of_tasks;
    double cost;
    int *ID_depo;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &d);

    graphAdjMat *mat = initGraph(n); //init the graph matrix

    for(i=0; i<n; i++)
        for(j=0; j<n; j++)
            mat->matrix[i][j] = inf;

    for(i=0; i<m; i++) //punem costul in masina de adiacenta
            {
                scanf("%d",&ID_Node1);
                scanf("%d",&ID_Node2);
                scanf("%lf",&cost);
                mat->matrix[ID_Node1][ID_Node2] = cost;
            }

    ID_depo = calloc(mat->numNodes+1, sizeof(int));
    for(i=0; i<d; i++)
        scanf("%d",&ID_depo[i]);

    scanf("%d",&nr_of_tasks);

    double cost_total = 0;
    while(nr_of_tasks > 0)
    {
        char *ID_task;
        ID_task = malloc(256*sizeof(char));
        scanf("%s",ID_task);

        if(strcmp(ID_task,"e1") == 0)
            {
                    int source;
                    int nr_of_targets;
                    scanf("%d",&source);
                    scanf("%d",&nr_of_targets);
                    while(nr_of_targets > 0)
                        {
                            double rez1,rez2;
                            int target;
                            int *prev1 = calloc(mat->numNodes, sizeof(int));
                            int *prev2 = calloc(mat->numNodes, sizeof(int));

                            scanf("%d",&target);
                            printf("%d\n",target);

                            rez1 = Dijkstra(mat,source,target,prev1); //apelare dijkstra dus
                            rez2 = Dijkstra(mat,target,source,prev2); //apelare dijkstra intros
            
                            printf("%.1lf %.1lf\n",rez1,rez2);
                            printf("%d ",source);

                            printPath(prev1,target,target);
                            printf(" ");
                            printPath(prev2,source,source);
                            printf("\n");

                            cost_total += rez1 + rez2;
                            nr_of_targets--;
                            free(prev1);
                            free(prev2);
                        }
                    printf("%.1lf", cost_total);
            }
        free(ID_task);
        nr_of_tasks--;
        if(nr_of_tasks != 0)
            printf("\n");
        cost_total = 0;
    }
    free(ID_depo);
    freeGraph(&mat);
    return 0;
}