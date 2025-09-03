#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Item
{
    char nome[30];
    char tipo[20];
    int quantidade;
};

typedef struct Item I;

void inserirItem(I *lista, int *totalItens, const char *nome, const char *tipo, int quantidade);
void removerItem(I *lista, int *totalItens, const char *nome);
void listarItem(I *lista, int *totalItens);
void buscarItem(I *lista, int *totalItens, const char *nome);


int main() {
    
    I inventario[10];

    int totalItens = 0;
    int opcao, quantidade;
    char nome[30], tipo[20];

    do {
        printf("\n--- INVENTÁRIO DE ITENS ---\n");
        printf("1. Inserir Item na mochila\n");
        printf("2. Buscar Item na mochila\n");
        printf("3. Remover Item da mochila\n");
        printf("4. Listar Item na mochila\n");
        printf("0. Sair da mochila\n");
        printf("Escolha uma opção: \n");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
        case 1:
            printf("Digite o nome do Item que deseja coloca na mochila: ");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;

            printf("Digite o tipo do Item: ");
            fgets(tipo, sizeof(tipo), stdin);
            tipo[strcspn(tipo, "\n")] = 0;

            printf("Digite a quantidade do Item: ");
             scanf("%d", &quantidade);
            getchar(); 

            inserirItem(inventario, &totalItens, nome, tipo, quantidade);

            break;
        case 2:
            printf("Digite o Item que busca: \n");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            buscarItem(inventario, &totalItens, nome);
            break;
        case 3:
            printf("Digite o Item que desena remover: \n");
            fgets(nome, sizeof(nome), stdin);
            nome[strcspn(nome, "\n")] = 0;
            removerItem(inventario, &totalItens, nome);
            break;
        case 4:
            listarItem(inventario, &totalItens);
            break;
        case 0:
            printf("Saindo...");
            break;
        default:
            printf("Opção inválida!");
        }
    } while (opcao != 0);

    return 0;
}

void inserirItem(I *lista, int *totalItens, const char *nome, const char *tipo, int quantidade) {
    if(*totalItens >= 10) {
        printf("Atenção! Inventário está cheio!\n");
        return;
    }
    strcpy(lista[*totalItens].nome, nome);
    strcpy(lista[*totalItens].tipo, tipo);
    lista[*totalItens].quantidade = quantidade;
    (*totalItens)++;
    printf("Item \"%s\" adicionado ao inventário.\n", nome);
}

void removerItem(I *lista, int *totalItens, const char *nome) {
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

    for(i = pos; i < *totalItens - 1; i++) {
        lista[i] = lista [i + 1];
    }

    (*totalItens)--;
    printf("Seu item \"%s\" foi removido com sucesso!\n", nome);
}

void listarItem(I *lista, int *totalItens) {
    if(*totalItens == 0) {
        printf("Seu inventário está vazio.\n");
        return;
    }
    printf("Itens no seu inventário: ");
    for(int i = 0; i < *totalItens; i++) {
        printf("\"%s\" (Tipo: %s, Quantidade: %d) \n", lista[i].nome, lista[i].tipo, lista[i].quantidade);
    }
}

void buscarItem(I *lista, int *totalItens, const char *nome) {
    for(int i = 0; i < *totalItens; i++) {
        if(strcmp(lista[i].nome, nome) == 0) {
            printf("O item \"%s\" está na sua mão agora!\n", nome);
            return;
        }
    }
        printf("Esse item \"%s\" não foi encontrado no seu inventário!\n", nome);
        return;
}