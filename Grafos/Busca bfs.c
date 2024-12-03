#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define N 6 // Número de vértices

// Função para realizar a busca em largura (BFS)
void bfs(int mat[N][N], int inicio, int destino) {
    int fila[N];
    bool visitado[N];
    int distancia[N];
    int inicio_fila = 0, final_fila = 0;

    // Inicializa as estruturas de dados
    for (int i = 0; i < N; i++) {
        visitado[i] = false;
        distancia[i] = INT_MAX;
    }

    // Inicia a busca a partir do vértice de início
    visitado[inicio] = true;
    distancia[inicio] = 0;
    fila[final_fila++] = inicio;

    // Enquanto houver vértices na fila
    while (inicio_fila != final_fila) {
        int v = fila[inicio_fila++];
        // Para cada vértice adjacente não visitado
        for (int i = 0; i < N; i++) {
            if (mat[v][i] && !visitado[i]) {
                visitado[i] = true;
                distancia[i] = distancia[v] + 1;
                fila[final_fila++] = i;
            }
        }
    }

    // Imprime a distância do vértice de início até o destino
    printf("A menor distância de %d até %d é: %d\n", inicio, destino, distancia[destino]);
}

int main() {
    int mat[N][N] = {
        {0, 1, 1, 0, 0, 0},
        {1, 0, 0, 1, 0, 0},
        {1, 0, 0, 1, 1, 0},
        {0, 1, 1, 0, 1, 1},
        {0, 0, 1, 1, 0, 1},
        {0, 0, 0, 1, 1, 0}
    };

    int inicio = 0; // Vértice de início
    int destino = 5; // Vértice de destino

    bfs(mat, inicio, destino);

    return 0;
}
