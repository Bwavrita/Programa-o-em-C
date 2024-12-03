#include <stdio.h>

int M[6][6] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 1, 0, 0, 0},
    {1, 1, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 1},
    {0, 0, 0, 0, 1, 0}
};

int visit[6] = {0};

void dfs(int v) {
    visit[v] = 1;
    for (int i = 0; i < 6; i++) {
        if (M[v][i] && !visit[i]) {
            dfs(i);
        }
    }
}

int main() {
    for (int i = 0; i < 6; i++) {
        if (!visit[i]) {
            printf("%d ", i + 1); // Os índices começam em 0, mas os vértices são numerados a partir de 1
            dfs(i);
        }
    }

    return 0;
}
