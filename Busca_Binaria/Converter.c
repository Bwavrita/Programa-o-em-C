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

int compare(const void *a, const void *b) {
    F *filmA = (F *)a;
    F *filmB = (F *)b;
    return strcmp(filmA->title, filmB->title);
}

void completar(char filmes[MAX_URL], char title[MAX_TITLE]) {
    int i;
    int len_url = strlen(filmes);
    for (i = len_url; i < MAX_URL - 1; i++) {
        filmes[i] = ' ';
    }
    filmes[MAX_URL - 1] = '\0';

    int len_title = strlen(title);
    for (i = len_title; i < MAX_TITLE - 1; i++) {
        title[i] = ' ';
    }
    title[MAX_TITLE - 1] = '\0';
}

int main() {
    FILE *inputFile = fopen("filmes.txt", "r");
    if (inputFile == NULL) {
        printf("Erro ao abrir o arquivo .txt.\n");
        return 1;
    }

    F filmes[MAX_MOVIES];
    int count = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), inputFile)) {
        char *token;

        token = strtok(line, ";");
        if (token != NULL) {
            filmes[count].id = atoi(token);
        } else {
            filmes[count].id = -1;
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            strncpy(filmes[count].title, token, MAX_TITLE - 1);
            filmes[count].title[MAX_TITLE - 1] = '\0';
        } else {
            strncpy(filmes[count].title, "Título Desconhecido", MAX_TITLE - 1);
            filmes[count].title[MAX_TITLE - 1] = '\0';
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            filmes[count].rYear = atoi(token);
        } else {
            filmes[count].rYear = -1;
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            strncpy(filmes[count].url, token, MAX_URL - 1);
            filmes[count].url[MAX_URL - 1] = '\0';
        } else {
            strncpy(filmes[count].url, "URL Desconhecida", MAX_URL - 1);
            filmes[count].url[MAX_URL - 1] = '\0';
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            filmes[count].directorId = atoi(token);
        } else {
            filmes[count].directorId = -1;
        }

        count++;
        if (count >= MAX_MOVIES) break;
    }
    fclose(inputFile);

    qsort(filmes, count, sizeof(F), compare);

    for (int i = 0; i < count; i++) {
        completar(filmes[i].url, filmes[i].title);
    }

    FILE *outputFile = fopen("filmesOrdenados.bin", "wb");
    if (outputFile == NULL) {
        printf("Erro ao abrir o arquivo binário.\n");
        return 1;
    }

    fwrite(filmes, sizeof(F), count, outputFile);
    fclose(outputFile);

    printf("Arquivo binário 'filmesOrdenados.bin' gerado com sucesso.\n");

    return 0;
}
