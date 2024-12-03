#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define N 6 // N�mero de v�rtices

// Fun��o para realizar a busca em largura (BFS)
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

    // Inicia a busca a partir do v�rtice de in�cio
    visitado[inicio] = true;
    distancia[inicio] = 0;
    fila[final_fila++] = inicio;

    // Enquanto houver v�rtices na fila
    while (inicio_fila != final_fila) {
        int v = fila[inicio_fila++];
        // Para cada v�rtice adjacente n�o visitado
        for (int i = 0; i < N; i++) {
            if (mat[v][i] && !visitado[i]) {
                visitado[i] = true;
                distancia[i] = distancia[v] + 1;
                fila[final_fila++] = i;
            }
        }
    }

    // Imprime a dist�ncia do v�rtice de in�cio at� o destino
    printf("A menor dist�ncia de %d at� %d �: %d\n", inicio, destino, distancia[destino]);
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

    int inicio = 0; // V�rtice de in�cio
    int destino = 5; // V�rtice de destino

    bfs(mat, inicio, destino);

    return 0;
}
