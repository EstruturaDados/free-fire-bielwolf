
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#define MAX_STRING 30
#define MAX_TIPO 20
#define MAX_INV 10
#define MAX_COMP 20

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

struct Componente {
    char nome [MAX_STRING];
    char tipo[MAX_TIPO];
    int prioridade;
};
typedef struct Componente Co;

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

void cadastrarComponentes(Co *lista, int *totalComp, const char *nome, const char *tipo, int prioridade);
void bubbleSort(Co lista[], int n, int *comparacoes);
void insertionSort(Co lista[], int n, int *comparacoes);
void selectionSort(Co lista[], int n, int *comparacoes);

void menuVetor(I *inventario, int *totalItens);
void menuListaEnc(IED *listaEnc);
void menuComponentes(Co *componente, int *totalComp);

int main() {
    Co componente[MAX_COMP];
    I inventario[MAX_INV];
    int totalItens = 0;
    int totalComp = 0;

    IED listaEnc = NULL;

    int opcao, quantidade, comparacoes, prioridade;
    char nome[MAX_STRING], tipo[MAX_TIPO];

    int listaBubble[MAX_COMP];
    int listaInsert[MAX_COMP];
    int listaSelection[MAX_COMP];

    srand(time(NULL));

    do {
        printf("\n--- INVENTÁRIO DE ITENS ---\n");
        printf("1. Operações com vetor\n");
        printf("2. Operações com lista encadeada\n");
        printf("3. Operações com componentes\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {
            case 1:
                menuVetor(inventario, &totalItens);
                break;
            case 2:
                menuListaEnc(&listaEnc);
                break;
            case 3:
                menuComponentes(componente, &totalComp);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// ---------------- Funções do menu ----------------
void menuVetor(I *inventario, int *totalItens) {
    int opcao, quantidade, comparacoes;
    char nome[MAX_STRING], tipo[MAX_TIPO];

    printf("\n--- Operações com vetor ---\n");
    printf("1. Inserir Item\n");
    printf("2. Buscar Item (Sequencial)\n");
    printf("3. Remover Item\n");
    printf("4. Listar Itens\n");
    printf("5. Ordenar Itens por nome\n");
    printf("6. Buscar Item (Binária)\n");
    printf("0. Voltar ao menu principal\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
        case 1:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            printf("Tipo: "); fgets(tipo, sizeof(tipo), stdin); tipo[strcspn(tipo, "\n")] = 0;
            printf("Quantidade: "); scanf("%d", &quantidade); getchar();
            inserirItemVetor(inventario, totalItens, nome, tipo, quantidade);
            break;

        case 2:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            comparacoes = 0;
            if(buscarSequencialVetor(inventario, totalItens, nome, &comparacoes) == 1)
                printf("Item \"%s\" encontrado! Comparações: %d\n", nome, comparacoes);
            else
                printf("Item \"%s\" não encontrado! Comparações: %d\n", nome, comparacoes);
            break;

        case 3:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            removerItemVetor(inventario, totalItens, nome);
            break;

        case 4:
            listarItem(inventario, totalItens);
            break;

        case 5:
            ordenarVetor(inventario, *totalItens);
            printf("Itens ordenados por nome com sucesso!\n");
            break;

        case 6:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            comparacoes = 0;
            int pos = buscarBinariaVetor(inventario, *totalItens, nome, &comparacoes);
            if(pos != -1)
                printf("Item \"%s\" encontrado na posição %d! Comparações: %d\n", nome, pos, comparacoes);
            else
                printf("Item \"%s\" não encontrado! Comparações: %d\n", nome, comparacoes);
            break;
        case 0:
            printf("Voltando ao menu principal...\n");
            break;

        default:
            printf("Opção inválida!\n");
    }
}

void menuListaEnc(IED *listaEnc) {
    int opcao, quantidade, comparacoes;
    char nome[MAX_STRING], tipo[MAX_TIPO];

    printf("\n--- Operações com lista encadeada ---\n");
    printf("1. Inserir Item\n");
    printf("2. Buscar Item\n");
    printf("3. Remover Item\n");
    printf("4. Listar Itens\n");
    printf("0. Voltar ao menu principal...\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
        case 1:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            printf("Tipo: "); fgets(tipo, sizeof(tipo), stdin); tipo[strcspn(tipo, "\n")] = 0;
            printf("Quantidade: "); scanf("%d", &quantidade); getchar();
            inserirItemVetorENC(listaEnc, nome, tipo, quantidade);
            break;

        case 2:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            comparacoes = 0;
            if(buscarSequencialVetorENC(*listaEnc, nome, &comparacoes) == 1)
                printf("Item \"%s\" encontrado! Comparações: %d\n", nome, comparacoes);
            else
                printf("Item \"%s\" não encontrado! Comparações: %d\n", nome, comparacoes);
            break;

        case 3:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            removerItemVetorENC(listaEnc, nome);
            break;

        case 4:
            listarItemENC(*listaEnc);
            break;

        case 0:
            printf("Voltando ao menu principal...\n");
            break;
        default:
            printf("Opção inválida!\n");
    }
}

void menuComponentes(Co *componente, int *totalComp) {
    int opcao, comparacoes, prioridade;
    char nome[MAX_STRING], tipo[MAX_TIPO];

    printf("\n--- Operações com componentes ---\n");
    printf("1. Inserir Componente\n");
    printf("2. Ordenar por nome (Bubble Sort)\n");
    printf("3. Ordenar por tipo (Insertion Sort)\n");
    printf("4. Ordenar por prioridade (Selection Sort)\n");
    printf("0. Voltar ao menu principal...\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    getchar();

    switch(opcao) {
        case 1:
            printf("Nome: "); fgets(nome, sizeof(nome), stdin); nome[strcspn(nome, "\n")] = 0;
            printf("Tipo: "); fgets(tipo, sizeof(tipo), stdin); tipo[strcspn(tipo, "\n")] = 0;
            printf("Prioridade: "); scanf("%d", &prioridade); getchar();
            cadastrarComponentes(componente, totalComp, nome, tipo, prioridade);
            break;

        case 2:
            if(*totalComp == 0) printf("Nenhum componente para ordenar!\n");
            else bubbleSort(componente, *totalComp, &comparacoes);
            break;

        case 3:
            if(*totalComp == 0) printf("Nenhum componente para ordenar!\n");
            else insertionSort(componente, *totalComp, &comparacoes);
            break;

        case 4:
            if(*totalComp == 0) printf("Nenhum componente para ordenar!\n");
            else selectionSort(componente, *totalComp, &comparacoes);
            break;
        case 0:
            printf("Voltando ao menu principal...");
            break;

        default:
            printf("Opção inválida!\n");

    } while (opcao != 0);

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

// //Não acho que seja eficiente, por isso não implementei como opção. 
// int buscaBinariaInterativaENC(IED lista, const char *nome, int *comparacoes) {
//     No *atual = lista;
//     int contador = 0;

//     while (atual != NULL) {
//         contador++;
//         atual = atual->proximo;
//     }

//     int inicio = 0;
//     int fim = contador - 1;
//     int meio;

//     while (inicio <= fim){
//         meio = inicio + (fim - contador) / 2;
//         atual = lista;
//         for (int i = 0; i < meio; i++)
//             atual = atual->proximo;
        
//         (*comparacoes)++;
//         int comparacao = strcmp(atual->dados->nome, nome);

//         if(comparacao == 0) {
//             return meio;
//         } else if(comparacao > 0) {
//             fim = meio - 1;
//         } else {
//             inicio = meio + 1;
//         }
//     }

//     return -1;
// }

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

void cadastrarComponentes(Co *lista, int *totalComp, const char *nome, const char *tipo, int prioridade) {
    if(*totalComp >= MAX_COMP) {
        printf("Atenção! Não é mais possível inserir componentes!\n");
        return;
    }
    strcpy(lista[*totalComp].nome, nome);
    strcpy(lista[*totalComp].tipo, tipo);
    lista[*totalComp].prioridade = prioridade;
    (*totalComp)++;
    printf("O componente\"%s\"  foi adicionado a torre de sobrevivência.\n", nome);
}

void bubbleSort(Co lista[], int n, int *comparacoes) {
    int i, j;
    int trocou;

    *comparacoes = 0;
    clock_t inicio = clock();

    for (i = 0; i < n - 1; i++) {
        trocou = 0;
        for(j = 0; j < n - i - 1; j++) { 
            (*comparacoes)++;
            if(strcmp(lista[j].nome, lista[j + 1].nome) > 0) {
                Co temp = lista[j];
                lista[j] = lista[j + 1];
                lista[j + 1] = temp;
                trocou = 1;
            }
        }

        if (trocou == 0) {
            break;
        }
    }
    clock_t fim = clock();
    double tempo = ((double)(fim - inicio) / CLOCKS_PER_SEC);
    printf("Bubble Sort: Comparações = %d, Tempo = %.6f segundos\n", *comparacoes, tempo);

}

void insertionSort(Co lista[], int n, int *comparacoes) { 
    int i, j;
    *comparacoes = 0;

    clock_t inicio = clock();

    for (i = 1; i < n; i++) {
        Co chave = lista[i];
        j = i - 1;

        while (j >= 0 && strcmp(lista[j].tipo, chave.tipo) > 0) {
            (*comparacoes)++;
            lista[j + 1] = lista[j];
            j = j - 1;
        }

        lista[j + 1] = chave;
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Insertion Sort: Comparações = %d, Tempo = %.6f segundos\n", *comparacoes, tempo);

}

void selectionSort(Co lista[], int n, int *comparacoes) {
    int i, j, indice_min;
    *comparacoes = 0;

    clock_t inicio = clock();

    for(i = 0; i < n - 1; i++) {
        indice_min = i;

        for (j = i + 1; j < n; j++) {
            (*comparacoes)++; 
            if(lista[j].prioridade < lista[indice_min].prioridade) {
                indice_min = j;
            }
        }

        if(indice_min != i) {
            Co temp = lista[i];
            lista[i] = lista[indice_min];
            lista[indice_min] = temp;
        }
    }

    clock_t fim = clock();
    double tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
    printf("Insertion Sort: Comparações = %d, Tempo = %.6f segundos\n", *comparacoes, tempo);

}





