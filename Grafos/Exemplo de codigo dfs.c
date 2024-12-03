void dfs(int v)
{
    visit[v] = 1;
    for(int i=1;i<6;i++)
    if(M[v][i] && visit[i]==0)
    dfs(i);
}
int main(){
    dfs(3);
    return 0;
}
#include <stdio.h>
#include <stdbool.h>

int M[6][6] = {
    {0, 1, 0, 1, 0, 0},
    {1, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 1},
    {1, 1, 0, 0, 1, 0},
    {0, 0, 0, 1, 0, 1},
    {0, 0, 1, 0, 1, 0}
};

int visit[6] = {0};

void dfs(int v) {
    visit[v] = 1;
    printf("%d ", v);
    for (int i = 0; i < 6; i++) {
        if (M[v][i] && visit[i] == 0) {
            dfs(i);
        }
    }
}

int main() {
    dfs(3);
    return 0;
}
