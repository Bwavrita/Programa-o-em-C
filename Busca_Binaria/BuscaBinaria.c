#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 1682
#define MAX_TITLE 50
#define MAX_URL 125
#define MAX_LINE 1000

typedef struct filmes {
    int id;
    int directorId;
    int rYear;
    char title[MAX_TITLE];
    char url[MAX_URL];
} F;

void trimSpaces(char *str) {
    int len = strlen(str);
    while (len > 0 && str[len - 1] == ' ') {
        str[len - 1] = '\0';
        len--;
    }
}

int carregarFilmes(const char *nomeArquivo, F *filmes) {
    FILE *file = fopen(nomeArquivo, "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return -1;
    }
    int totalFilmes = fread(filmes, sizeof(F), MAX_MOVIES, file);
    fclose(file);
    return totalFilmes;
}

int buscaBinariaMemoria(F *filmes, int totalFilmes, const char *titulo) {
    int inicio = 0;
    int fim = totalFilmes - 1;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        trimSpaces(filmes[meio].title);
        int cmp = strcmp(titulo, filmes[meio].title);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}

int buscaBinariaTitulo(FILE *file, const char *titulo, int totalFilmes) {
    int inicio = 0;
    int fim = totalFilmes - 1;
    F filmeLido;
    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        fseek(file, meio * sizeof(F), SEEK_SET);
        fread(&filmeLido, sizeof(F), 1, file);
        trimSpaces(filmeLido.title);
        int cmp = strcmp(titulo, filmeLido.title);
        if (cmp == 0) {
            return meio;
        } else if (cmp < 0) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
    }
    return -1;
}

int main() {
    FILE *file = fopen("filmesOrdenados.bin", "rb");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int totalFilmes = MAX_MOVIES;
    char tituloBuscado[MAX_TITLE] = "12 Angry Men";

    int posicao = buscaBinariaTitulo(file, tituloBuscado, totalFilmes);
    
    if (posicao != -1) {
        printf("Filme encontrado na posição %d\n", posicao + 1);
    } else {
        printf("Filme não encontrado.\n");
    }

    fclose(file);
    return 0;
}
