#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void ler_arquivo(FILE *f, FILE *d) {
    char linhaFilme[100];
    char linhaDiretor[100];
    char *tokenFilme;
    char *tokenDiretor;
    char delimitador[] = ";";

    while (fgets(linhaFilme, sizeof(linhaFilme), f)) {
        tokenFilme = strtok(linhaFilme, delimitador);
        int campo = 0;
        char movieID[10], title[50], releaseYear[10], url[50], directorID[20] = "sem informação";

        while (tokenFilme != NULL) {
            switch (campo) {
                case 0: strcpy(movieID, tokenFilme); break;
                case 1: strcpy(title, tokenFilme); break;
                case 2: strcpy(releaseYear, tokenFilme); break;
                case 3: strcpy(url, tokenFilme); break;
                case 4: 
                    if (strcmp(tokenFilme, "") != 0) {
                        strcpy(directorID, tokenFilme);
                    }
                    break;
            }
            campo++;
            tokenFilme = strtok(NULL, delimitador);
        }
        if (strcmp(directorID, "sem informação") == 0) {
            rewind(d);
            while (fgets(linhaDiretor, sizeof(linhaDiretor), d)) {
                tokenDiretor = strtok(linhaDiretor, delimitador);
                char diretorMovieID[10];
                char diretorNome[50];

                strcpy(diretorMovieID, tokenDiretor);
                tokenDiretor = strtok(NULL, delimitador);
                strcpy(diretorNome, tokenDiretor);
                if (strcmp(movieID, diretorMovieID) == 0) {
                    strcpy(directorID, diretorNome);
                    break;
                }
            }
        }
        if (strcmp(directorID, "sem informação") == 0) {
            printf("Id: %s\ntitle: %s\nyear: %s\nurl: %s\ndirector: sem informação\n\n", movieID, title, releaseYear, url);
        } else {
            printf("Id: %s\ntitle: %s\nyear: %s\nurl: %s\ndirector: %s\n\n", movieID, title, releaseYear, url, directorID);
        }
    }
}

int main() {
    FILE *arquivoFilmes = fopen("filmes.txt", "r");
    FILE *arquivoDiretores = fopen("diretores.txt", "r");

    if (arquivoFilmes == NULL || arquivoDiretores == NULL) {
        perror("Erro ao abrir os arquivos");
        return 1;
    }

    ler_arquivo(arquivoFilmes, arquivoDiretores);

    fclose(arquivoFilmes);
    fclose(arquivoDiretores);

    return 0;
}
