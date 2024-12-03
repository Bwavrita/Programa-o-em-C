#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


typedef struct bitfields{
    unsigned int bit1 : 4;
    unsigned int bit2 : 4;
}BITS1;

typedef struct bitfield{
    unsigned int bit1 : 6;
    unsigned int bit2 : 6;
    unsigned int campo : 12;
}BITS2;

typedef struct bit{
    unsigned int bit1 : 8;
    unsigned int bit2 : 8;
}BITS3;

typedef struct list {
    int qtd;
    char letra;
    int usado;
    int cod;
    struct list* prox;
    struct list* anterior;
} L;

typedef struct header {
    int qtd;
    struct list* inicio;
    struct list* fim;
} H;

// Função para criar a lista com letras e frequências
void inserir(H** header, char c) {
    c = tolower(c);

    L* temp = (*header)->inicio;
    if (temp != NULL) {
        while (temp != NULL) {
            if (temp->letra == c) {
                (temp->qtd)++;
                return;
            }
            temp = temp->prox;
        }
    }

    L* novo = (L*)malloc(sizeof(L));
    novo->qtd = 1;
    novo->letra = c;
    novo->usado = 0;
    novo->prox = NULL;
    novo->cod = 0;
    novo->anterior = (*header)->fim;


    if ((*header)->fim != NULL) {
        (*header)->fim->prox = novo;
    } else {
        (*header)->inicio = novo;
    }
    (*header)->fim = novo;
}

// Função para ordenar a lista encadeada com base na quantidade (qtd)
void ordenarLista(H* header) {
    if (header->inicio == NULL) return;

    int trocou;
    do {
        trocou = 0;
        L* atual = header->inicio;

        while (atual->prox != NULL) {
            if (atual->qtd < atual->prox->qtd) {
                // Troca os valores de 'qtd' e 'letra'
                int tempQtd = atual->qtd;
                char tempLetra = atual->letra;
                atual->qtd = atual->prox->qtd;
                atual->letra = atual->prox->letra;
                atual->prox->qtd = tempQtd;
                atual->prox->letra = tempLetra;
                
                trocou = 1;
            }
            atual = atual->prox;
        }
    } while (trocou);
}
void contarQtd(H* header){
    L* temp = header->inicio;
    while(temp != NULL){
        (header->qtd)++;
        temp = temp->prox;
    }
}

void printar(H* header) {
    L* temp = header->inicio;
    while (temp != NULL) {
        printf("%c -> quantidade: %d \t codigo-> %d \n", temp->letra, temp->qtd,temp->cod);
        temp = temp->prox;
    }
}

void fazerCodigo(H* header){
    L* temp = header->inicio;
    int aux = 0;
    for(int i = 0;i<header->qtd;temp = temp->prox,i++,aux++){
        temp->cod = aux;
    }
}

void escreverCodigo(H* header, FILE* saidaTxt,FILE* saidaBin){
    L* temp = header->inicio;
    for(int i = 0;i<header->qtd;temp = temp->prox->prox,i+=2){
        if(header->qtd <=15){
            BITS1 b;
            unsigned char byte = 0;
            b.bit1 = temp->cod;
            b.bit2 = temp->prox->cod;
            byte |= (b.bit1 << 4);
            byte |= b.bit2;
            fprintf(saidaTxt,"%c",byte);
            fwrite(&byte,sizeof(unsigned char ),1,saidaBin);
        }else if(header->qtd <= 63){
            BITS2 b;
            b.bit1 = temp->cod;
            b.bit2 = temp->prox->cod;
            b.campo |= (b.bit1 << 6);
            b.campo |= b.bit2;
            fprintf(saidaTxt,"%d",b.campo);
            unsigned int campo = b.campo;
            fwrite(&campo,sizeof(unsigned int),1,saidaBin);
        }else{
            BITS3 b;
            unsigned int aux;
            b.bit1 = temp->cod;
            b.bit2 = temp->prox->cod;
            aux |= (b.bit1 << 6);
            aux |= b.bit2;
            fprintf(saidaTxt,"%d",aux);
            fwrite(&aux,sizeof(unsigned int),1,saidaBin);
        }
    }
}

int main() {
    H* header = (H*)malloc(sizeof(H));
    header->qtd = 0;
    header->inicio = NULL;
    header->fim = NULL;
    FILE* entrada = fopen("entrada.txt","r");
    if(entrada == NULL){
        printf("erro entrada");
        exit(0);
    }
    FILE* saidaTXT = fopen("saidaTXT.txt","w");
        if(saidaTXT == NULL){
        printf("erro saidaTXT");
        exit(0);
    }
    FILE* saidaBIN = fopen("saidaBIN.bin","wb");
        if(saidaBIN == NULL){
        printf("erro saidaBIN");
        exit(0);
    }
    char f[1000];
    fgets(f,sizeof(f),entrada);

    for (int i = 0; f[i] != '\0'; i++) {
        inserir(&header, f[i]);
    }
    ordenarLista(header);
    printar(header);
    contarQtd(header);
    fazerCodigo(header);
    escreverCodigo(header,saidaTXT,saidaBIN);
    printf("dps\n");
    printar(header);

    fclose(entrada);
    fclose(saidaTXT);
    fclose(saidaBIN);
    L* temp = header->inicio;
    while (temp != NULL) {
        L* prox = temp->prox;
        free(temp);
        temp = prox;
    }
    free(header);

    return 0;
}
