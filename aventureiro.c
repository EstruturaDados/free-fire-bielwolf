
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 30
#define MAX_TIPO 20
#define MAX_INV 10

// Structs
struct Item {
    char nome[MAX_STRING];
    char tipo[MAX_TIPO];
    int quantidade;
};
typedef struct Item I;

typedef struct No {
    I *dados;
    struct No *proximo;
} No;
typedef No* IED;

// Protótipos
void inserirItemVetor(I *lista, int *totalItens, const char *nome, const char *tipo, int quantidade);
void removerItemVetor(I *lista, int *totalItens, const char *nome);
void listarItem(I *lista, int *totalItens);
int buscarSequencialVetor(I *lista, int *totalItens, const char *nome, int *comparacoes);
void ordenarVetor(I *lista, int totalItens);
int buscarBinariaVetor(I *lista, int totalItens, const char *nome, int *comparacoes);

void inserirItemVetorENC(IED *lista, const char *nome, const char *tipo, int quantidade);
void removerItemVetorENC(IED *lista, const char *nome);
void listarItemENC(IED lista);
int buscarSequencialVetorENC(IED lista, const char *nome, int *comparacoes);
void ordenarListaENC(IED *lista);

int main() {
    I inventario[MAX_INV];
    int totalItens = 0;

    IED listaEnc = NULL;

    int opcao, quantidade, comparacoes;
    char nome[MAX_STRING], tipo[MAX_TIPO];

    do {
        printf("\n--- INVENTÁRIO DE ITENS ---\n");
        printf("1. Inserir Item na mochila (vetor)\n");
        printf("2. Buscar Item na mochila (vetor)\n");
        printf("3. Remover Item da mochila (vetor)\n");
        printf("4. Listar Item na mochila (vetor)\n");
        printf("5. Ordenar itens do vetor por nome\n");
        printf("6. Buscar item no vetor com busca binária\n");
        printf("7. Inserir Item na mochila (lista encadeada)\n");
        printf("8. Buscar Item na mochila (lista encadeada)\n");
        printf("9. Remover Item da mochila (lista encadeada)\n");
        printf("10. Listar Item na mochila (lista encadeada)\n");
        printf("0. Sair da mochila\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            printf("Digite o nome do Item que deseja colocar na mochila: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite o tipo do Item: ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Digite a quantidade do Item: ");
            scanf("%d", &quantidade);
            getchar(); 

            inserirItemVetor(inventario, &totalItens, nome, tipo, quantidade);
            break;

        case 2:
            printf("Digite o Item que deseja buscar: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            comparacoes = 0;
            if(buscarSequencialVetor(inventario, &totalItens, nome, &comparacoes) == 1)
                printf("Item \"%s\" encontrado! Comparações: %d\n", nome, comparacoes);
            else
                printf("Item \"%s\" não encontrado! Comparações: %d\n", nome, comparacoes);
            break;

        case 3:
            printf("Digite o Item que deseja remover: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            removerItemVetor(inventario, &totalItens, nome);
            break;

        case 4:
            listarItem(inventario, &totalItens);
            break;

        case 5:
            ordenarVetor(inventario, totalItens);
            printf("Itens ordenados por nome com sucesso!\n");
            break;

        case 6:
            printf("Digite o Item que deseja buscar (busca binária): ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            comparacoes = 0;
            int pos = buscarBinariaVetor(inventario, totalItens, nome, &comparacoes);
            if(pos != -1)
                printf("Item \"%s\" encontrado na posição %d! Comparações: %d\n", nome, pos, comparacoes);
            else
                printf("Item \"%s\" não encontrado! Comparações: %d\n", nome, comparacoes);
            break;

        case 7:
            printf("Digite o nome do Item que deseja colocar na mochila (lista): ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite o tipo do Item: ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Digite a quantidade do Item: ");
            scanf("%d", &quantidade);
            getchar(); 

            inserirItemVetorENC(&listaEnc, nome, tipo, quantidade);
            break;

        case 8:
            printf("Digite o Item que deseja buscar (lista): ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            comparacoes = 0;
            if(buscarSequencialVetorENC(listaEnc, nome, &comparacoes) == 1)
                printf("Item \"%s\" encontrado na lista encadeada! Comparações: %d\n", nome, comparacoes);
            else
                printf("Item \"%s\" não encontrado na lista encadeada! Comparações: %d\n", nome, comparacoes);
            break;

        case 9:
            printf("Digite o Item que deseja remover (lista): ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            removerItemVetorENC(&listaEnc, nome);
            break;

        case 10:
            listarItemENC(listaEnc);
            break;

        case 0:
            printf("Saindo...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Funções do vetor ---
void inserirItemVetor(I *lista, int *totalItens, const char *nome, const char *tipo, int quantidade) {
    if(*totalItens >= MAX_INV) {
        printf("Atenção! Inventário está cheio!\n");
        return;
    }
    strcpy(lista[*totalItens].nome, nome);
    strcpy(lista[*totalItens].tipo, tipo);
    lista[*totalItens].quantidade = quantidade;
    (*totalItens)++;
    printf("Item \"%s\" adicionado ao inventário.\n", nome);
}

void removerItemVetor(I *lista, int *totalItens, const char *nome) {
    int i, pos = -1;
    for(i = 0; i < *totalItens; i++) {
        if(strcmp(lista[i].nome, nome) == 0) {
            pos = i;
            break;
        }
    }
    if(pos == -1) {
        printf("Esse item \"%s\" não foi encontrado no seu inventário!\n", nome);
        return;
    }
    for(i = pos; i < *totalItens - 1; i++)
        lista[i] = lista[i + 1];
    (*totalItens)--;
    printf("Seu item \"%s\" foi removido com sucesso!\n", nome);
}

void listarItem(I *lista, int *totalItens) {
    if(*totalItens == 0) {
        printf("Seu inventário está vazio.\n");
        return;
    }
    printf("Itens no seu inventário: \n");
    for(int i = 0; i < *totalItens; i++)
        printf("\"%s\" (Tipo: %s, Quantidade: %d)\n", lista[i].nome, lista[i].tipo, lista[i].quantidade);
}

int buscarSequencialVetor(I *lista, int *totalItens, const char *nome, int *comparacoes) {
    for(int i = 0; i < *totalItens; i++) {
        (*comparacoes)++;
        if(strcmp(lista[i].nome, nome) == 0)
            return 1;
    }
    return -1;
}

void ordenarVetor(I *lista, int totalItens) {
    for(int i = 0; i < totalItens - 1; i++) {
        for(int j = 0; j < totalItens - i - 1; j++) {
            if(strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                I temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(I *lista, int totalItens, const char *nome, int *comparacoes) {
    int inicio = 0, fim = totalItens - 1;
    while(inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        (*comparacoes)++;
        int cmp = strcmp(lista[meio].nome, nome);
        if(cmp == 0) return meio;
        else if(cmp > 0) fim = meio - 1;
        else inicio = meio + 1;
    }
    return -1;
}

// --- Funções da lista encadeada ---
void inserirItemVetorENC(IED *lista, const char *nome, const char *tipo, int quantidade) {
    No *novoNo = malloc(sizeof(No));
    if(!novoNo) { printf("Inventário está cheio!\n"); return; }

    novoNo->dados = malloc(sizeof(I));
    if(!novoNo->dados) { free(novoNo); printf("Não foi possível adicionar item!\n"); return; }

    strcpy(novoNo->dados->nome, nome);
    strcpy(novoNo->dados->tipo, tipo);
    novoNo->dados->quantidade = quantidade;

    novoNo->proximo = *lista;
    *lista = novoNo;

    printf("Item \"%s\" (Tipo: %s, Quantidade: %d) adicionado à lista encadeada.\n",
           novoNo->dados->nome, novoNo->dados->tipo, novoNo->dados->quantidade);
}

void removerItemVetorENC(IED *lista, const char *nome) {
    No *atual = *lista, *anterior = NULL;
    while(atual != NULL && strcmp(atual->dados->nome, nome) != 0) {
        anterior = atual;
        atual = atual->proximo;
    }
    if(atual == NULL) { printf("Esse item \"%s\" não foi encontrado!\n", nome); return; }
    if(anterior == NULL) *lista = atual->proximo;
    else anterior->proximo = atual->proximo;
    free(atual->dados);
    free(atual);
    printf("Item \"%s\" removido da lista encadeada com sucesso.\n", nome);
}

void listarItemENC(IED lista) {
    if(lista == NULL) { printf("Lista encadeada vazia.\n"); return; }
    printf("Itens na lista encadeada:\n");
    No *atual = lista;
    while(atual != NULL) {
        printf("\"%s\" (Tipo: %s, Quantidade: %d)\n", atual->dados->nome, atual->dados->tipo, atual->dados->quantidade);
        atual = atual->proximo;
    }
}

int buscarSequencialVetorENC(IED lista, const char *nome, int *comparacoes) {
    No *atual = lista;
    while(atual != NULL) {
        (*comparacoes)++;
        if(strcmp(atual->dados->nome, nome) == 0) return 1;
        atual = atual->proximo;
    }
    return -1;
}

void ordenarListaENC(IED *lista) {
    if(*lista == NULL || (*lista)->proximo == NULL) return;
    int houveTroca;
    do {
        houveTroca = 0;
        No *atual = *lista;
        while(atual->proximo != NULL) {
            if(strcmp(atual->dados->nome, atual->proximo->dados->nome) > 0) {
                I temp = *(atual->dados);
                *(atual->dados) = *(atual->proximo->dados);
                *(atual->proximo->dados) = temp;
                houveTroca = 1;
            }
            atual = atual->proximo;
        }
    } while(houveTroca);
}
