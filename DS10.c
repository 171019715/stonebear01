#include <stdio.h>
#include <stdlib.h>

#define INF 1000000 // 用一个较大的数表示无穷大

// 打印路径的函数
void printPath(int **next, int start, int end) {
    if (next[start][end] == -1) {
        printf("无路径\n");
        return;
    }
    printf("%d", start);
    while (start != end) {
        start = next[start][end];
        printf(" -> %d", start);
    }
    printf("\n");
}

// Floyd-Warshall 算法
void floydWarshallWithPath(int **graph, int n) {
    int **dist = (int **)malloc(n * sizeof(int *));
    int **next = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dist[i] = (int *)malloc(n * sizeof(int));
        next[i] = (int *)malloc(n * sizeof(int));
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dist[i][j] = 0;
            } else if (graph[i][j] != 0) {
                dist[i][j] = graph[i][j];
                next[i][j] = j;
            } else {
                dist[i][j] = INF;
                next[i][j] = -1;
            }
        }
    }

    // 迭代更新
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    // 打印距离和路径
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i != j) {
                printf("从 %d 到 %d 的最短路径距离: ", i, j);
                if (dist[i][j] == INF) {
                    printf("无路径\n");
                } else {
                    printf("%d\n", dist[i][j]);
                    printf("路径: ");
                    printPath(next, i, j);
                }
            }
        }
    }

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(dist[i]);
        free(next[i]);
    }
    free(dist);
    free(next);
}

int main() {
    int n = 5;
    int **graph = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        graph[i] = (int *)malloc(n * sizeof(int));
    }

    // 初始化图（邻接矩阵表示）
    int adjacencyMatrix[5][5] = {
        {0, 3, 0, 0, 6},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 7, 0},
        {2, 0, 0, 0, 1},
        {0, 0, 0, 0, 0}
    };

    // 复制邻接矩阵到动态分配的 graph 中
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = adjacencyMatrix[i][j];
        }
    }

    // 运行算法
    floydWarshallWithPath(graph, n);

    // 释放内存
    for (int i = 0; i < n; i++) {
        free(graph[i]);
    }
    free(graph);

    return 0;
}
