#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

struct site {
    char nome[100];
    char link[100];
 	site* proximo;
};

void insereSite( site** lista, const char* nome, const char* link) {
    struct site* novo = (struct site*)malloc(sizeof(struct site));
    strcpy(novo->nome, nome);
    strcpy(novo->link, link);
    novo->proximo = *lista;
    *lista = novo;
}

void buscaNome(struct site* lista, const char* nome,  site** site_encontrado) {
    while (lista != NULL) {
        if (strcmp(lista->nome, nome) == 0) {
            *site_encontrado = lista;
            return;
        }
        lista = lista->proximo;
    }
    printf("\nSite nao encontrado.\n");
}

void buscaLink(struct site* lista, const char* link,  site** site_encontrado) {
    while (lista != NULL) {
        if (strcmp(lista->link, link) == 0) {
            *site_encontrado = lista;
            return;
        }
        lista = lista->proximo;
    }
    printf("\nSite nao encontrado.\n");
}

void buscaGeral(struct site* lista) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,  FOREGROUND_BLUE);
    printf("===================\n");
	printf("   BUSCA GLOBAL \n");
	printf("===================\n");
    while (lista != NULL) {
    	SetConsoleTextAttribute(hConsole,  FOREGROUND_GREEN);
        printf("\nNome: %s\n", lista->nome);
        printf("Link: %s\n", lista->link);
        lista = lista->proximo;
    }
}

void mover_para_primeira_posicao(struct site** lista, struct site* site_encontrado) {
    if (*lista == site_encontrado) {
        return;
    }

    struct site* anterior = NULL;
    struct site* atual = *lista;

    while (atual != NULL && atual != site_encontrado) {
        anterior = atual;
        atual = atual->proximo;
    }

    if (atual == NULL) {
        return;
    }

    anterior->proximo = atual->proximo;
    site_encontrado->proximo = *lista;
    *lista = site_encontrado;
}

int main() {
    int op;
    struct site* lista = NULL;

    insereSite(&lista, "Facebook", "www.facebook.com");
    insereSite(&lista, "Google", "www.google.com");
    insereSite(&lista, "YouTube", "www.youtube.com");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    printf("OPCOES:\n1 para busca pelo nome.\n2 para busca por link.\n3 para fazer uma busca geral.\n0 para sair do navegador.\n");
    scanf("%d", &op);

    while (op != 0) {

        if (op == 1) {
        	system("cls");
            char nome[100];
            printf("Digite o nome do site: ");
            scanf("%s", nome);
            struct site* site_encontrado = NULL;
            buscaNome(lista, nome, &site_encontrado);
            if (site_encontrado != NULL) {
                mover_para_primeira_posicao(&lista, site_encontrado);
                SetConsoleTextAttribute(hConsole,  FOREGROUND_GREEN);
                printf("Site encontrado:\n");
                printf("Nome: %s\n", site_encontrado->nome);
                printf("Link: %s\n", site_encontrado->link);
            }
        }
        else if (op == 2) {
        	system("cls");
            char link[100];
            printf("Digite o link do site: ");
            scanf("%s", link);
            struct site* site_encontrado = NULL;
            buscaLink(lista, link, &site_encontrado);
            if (site_encontrado != NULL) {
                mover_para_primeira_posicao(&lista, site_encontrado);
                SetConsoleTextAttribute(hConsole,  FOREGROUND_GREEN);
                printf("Site encontrado:\n");
                printf("Nome: %s\n", site_encontrado->nome);
                printf("Link: %s\n", site_encontrado->link);
            }
        }
        else if (op == 3) {
        	system("cls");
            buscaGeral(lista);
        }
        else {
        	system("cls");
        	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
            printf("Opcao invalida. Tente novamente.\n");
        }
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
        printf("\nOPCOES:\n1 para busca pelo nome.\n2 para busca por link.\n3 para fazer uma busca geral.\n0 para sair do navegador.\n");
        scanf("%d", &op);
    }

    return 0;
}
