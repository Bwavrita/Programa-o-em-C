#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MOVIES 1682

typedef struct filmes {
    int indice;
    int directorId;
    int rYear;
    char title[50];
    char url[125];
} F;

typedef struct vetorIndice {
    int idFilme;
    long offset;
} vIndice;

int compararIndices(const void* a, const void* b) {
    vIndice* indiceA = (vIndice*)a;
    vIndice* indiceB = (vIndice*)b;
    return (indiceA->idFilme - indiceB->idFilme);
}

vIndice* fazerVetor(FILE* arq, int* tamanho) {
    vIndice* vetor = (vIndice*) malloc(MAX_MOVIES * sizeof(vIndice));
    F filme;
    long posicao;
    int count = 0;

    rewind(arq);

    while (fread(&filme, sizeof(F), 1, arq) == 1 && count < MAX_MOVIES) {
        posicao = ftell(arq) - sizeof(F);

        vetor[count].idFilme = filme.indice;
        vetor[count].offset = posicao;
        count++;
    }

    *tamanho = count;
    return vetor;
}

void salvarVetorEmArquivoBinario(vIndice* vetor, int tamanhoVetor, const char* nomeArquivo) {
    FILE* arquivo = fopen(nomeArquivo, "wb");
    if (arquivo == NULL) {
        printf("Erro ao criar o arquivo binário de índices.\n");
        return;
    }

    fwrite(vetor, sizeof(vIndice), tamanhoVetor, arquivo);

    fclose(arquivo);
    printf("Índice salvo em %s com sucesso.\n", nomeArquivo);
}

void inserirNovoFilmeNaExtensao(FILE* arq, int id, int directorId, int rYear, const char* title, const char* url) {
    F novoFilme;
    novoFilme.indice = id;
    novoFilme.directorId = directorId;
    novoFilme.rYear = rYear;
    strcpy(novoFilme.title, title);
    strcpy(novoFilme.url, url);

    fseek(arq, 0, SEEK_END);
    fwrite(&novoFilme, sizeof(F), 1, arq);

    printf("Novo filme inserido: %s (ID: %d)\n", novoFilme.title, novoFilme.indice);
}

void reorganizarFilmes(FILE* arq, vIndice** vetor, int* tamanhoVetor) {
    rewind(arq);

    F filme;
    long posicao;
    int count = 0;

    *vetor = (vIndice*) realloc(*vetor, (*tamanhoVetor + MAX_MOVIES) * sizeof(vIndice));//aumentar o tamanho do vetor apos a inserção de novos filmes

    while (fread(&filme, sizeof(F), 1, arq) == 1) { //insere os novos indices e endereço no ARQ de indice
        posicao = ftell(arq) - sizeof(F);

        (*vetor)[count].idFilme = filme.indice;
        (*vetor)[count].offset = posicao;
        count++;
    }

    *tamanhoVetor = count;

    qsort(*vetor, *tamanhoVetor, sizeof(vIndice), compararIndices);
}

int main() {
    FILE* arq = fopen("filmesOrdenados.bin", "rb+");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    int tamanhoVetor = 0;
    vIndice* vetor = fazerVetor(arq, &tamanhoVetor);

    qsort(vetor, tamanhoVetor, sizeof(vIndice), compararIndices);

    for (int i = 0; i < tamanhoVetor; i++) {
        printf("ID do filme: %d, Offset: %ld\n", vetor[i].idFilme, vetor[i].offset);
    }

    inserirNovoFilmeNaExtensao(arq, 1683, 102, 2024, "Novo Filme 1", "http://novo-filme1.com");
    inserirNovoFilmeNaExtensao(arq, 1684, 103, 2025, "Novo Filme 2", "http://novo-filme2.com");

    reorganizarFilmes(arq, &vetor, &tamanhoVetor);
    salvarVetorEmArquivoBinario(vetor, tamanhoVetor, "indiceFilmes.bin");

    free(vetor);
    fclose(arq);
    return 0;
}
