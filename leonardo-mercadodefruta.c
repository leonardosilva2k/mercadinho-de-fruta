#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para armazenar as informações de uma fruta
typedef struct {
    int codigo;
    char nome[50];
    int quantidade;
    float preco;
} Fruta;

// Funções para gerenciar o mercadinho de frutas
void cadastrarFruta(Fruta **frutas, int *quantidadeFrutas);
void listarFrutas(Fruta **frutas, int quantidadeFrutas);
Fruta *buscarFruta(Fruta **frutas, int quantidadeFrutas, int codigo);
void alterarFruta(Fruta **frutas, int quantidadeFrutas);
void excluirFruta(Fruta **frutas, int *quantidadeFrutas);
void venderFruta(Fruta **frutas, int quantidadeFrutas);
void registrarVenda(int codigo, char *nome, int quantidade, float preco);

int main() {
    Fruta *frutas[100]; // Array de ponteiros para frutas
    int quantidadeFrutas = 0;
    int opcao;

    do {
        printf("\n=== Menu do Mercadinho ===\n");
        printf("1. Cadastrar Fruta\n");
        printf("2. Listar Frutas\n");
        printf("3. Buscar Fruta\n");
        printf("4. Alterar Fruta\n");
        printf("5. Excluir Fruta\n");
        printf("6. Vender Fruta\n");
        printf("7. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrarFruta(frutas, &quantidadeFrutas);
                break;
            case 2:
                listarFrutas(frutas, quantidadeFrutas);
                break;
            case 3: {
                int codigo;
                printf("Digite o código da fruta: ");
                scanf("%d", &codigo);
                Fruta *fruta = buscarFruta(frutas, quantidadeFrutas, codigo);
                if (fruta != NULL) {
                    printf("Fruta encontrada: %s, Quantidade: %d, Preço: %.2f\n",
                           fruta->nome, fruta->quantidade, fruta->preco);
                } else {
                    printf("Fruta não encontrada.\n");
                }
                break;
            }
            case 4:
                alterarFruta(frutas, quantidadeFrutas);
                break;
            case 5:
                excluirFruta(frutas, &quantidadeFrutas);
                break;
            case 6:
                venderFruta(frutas, quantidadeFrutas);
                break;
            case 7:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 7);

    // Liberar a memória alocada para as frutas
    for (int i = 0; i < quantidadeFrutas; i++) {
        free(frutas[i]);
    }

    return 0;
}

// Implementações das funções

void cadastrarFruta(Fruta **frutas, int *quantidadeFrutas) {
    Fruta *novaFruta = (Fruta *)malloc(sizeof(Fruta));
    printf("Digite o código da fruta: ");
    scanf("%d", &novaFruta->codigo);

    // Verificar se o código é único
    for (int i = 0; i < *quantidadeFrutas; i++) {
        if (frutas[i]->codigo == novaFruta->codigo) {
            printf("Código já existente. Cadastro não realizado.\n");
            free(novaFruta);
            return;
        }
    }

    printf("Digite o nome da fruta: ");
    scanf("%s", novaFruta->nome);
    printf("Digite a quantidade em estoque: ");
    scanf("%d", &novaFruta->quantidade);
    printf("Digite o preço da fruta: ");
    scanf("%f", &novaFruta->preco);

    frutas[*quantidadeFrutas] = novaFruta;
    (*quantidadeFrutas)++;
    printf("Fruta cadastrada com sucesso!\n");
}

void listarFrutas(Fruta **frutas, int quantidadeFrutas) {
    printf("\n=== Lista de Frutas ===\n");
    for (int i = 0; i < quantidadeFrutas; i++) {
        printf("Código: %d, Nome: %s, Quantidade: %d, Preço: %.2f\n",
               frutas[i]->codigo, frutas[i]->nome, frutas[i]->quantidade, frutas[i]->preco);
    }
}

Fruta *buscarFruta(Fruta **frutas, int quantidadeFrutas, int codigo) {
    for (int i = 0; i < quantidadeFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            return frutas[i];
        }
    }
    return NULL;
}

void alterarFruta(Fruta **frutas, int quantidadeFrutas) {
    int codigo;
    printf("Digite o código da fruta a ser alterada: ");
    scanf("%d", &codigo);
    Fruta *fruta = buscarFruta(frutas, quantidadeFrutas, codigo);

    if (fruta != NULL) {
        printf("Digite o novo nome da fruta: ");
        scanf("%s", fruta->nome);
        printf("Digite a nova quantidade em estoque: ");
        scanf("%d", &fruta->quantidade);
        printf("Digite o novo preço da fruta: ");
        scanf("%f", &fruta->preco);
        printf("Fruta alterada com sucesso!\n");
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void excluirFruta(Fruta **frutas, int *quantidadeFrutas) {
    int codigo;
    printf("Digite o código da fruta a ser excluída: ");
    scanf("%d", &codigo);
    for (int i = 0; i < *quantidadeFrutas; i++) {
        if (frutas[i]->codigo == codigo) {
            if (frutas[i]->quantidade == 0) {
                free(frutas[i]);
                frutas[i] = frutas[*quantidadeFrutas - 1];
                (*quantidadeFrutas)--;
                printf("Fruta excluída com sucesso!\n");
                return;
            } else {
                printf("Não é possível excluir uma fruta com estoque.\n");
                return;
            }
        }
    }
    printf("Fruta não encontrada.\n");
}

void venderFruta(Fruta **frutas, int quantidadeFrutas) {
    int codigo, qtd;
    printf("Digite o código da fruta a ser vendida: ");
    scanf("%d", &codigo);
    Fruta *fruta = buscarFruta(frutas, quantidadeFrutas, codigo);

    if (fruta != NULL) {
        printf("Digite a quantidade a ser vendida: ");
        scanf("%d", &qtd);
        if (qtd > fruta->quantidade) {
            printf("Quantidade insuficiente no estoque.\n");
        } else {
            fruta->quantidade -= qtd;
            registrarVenda(fruta->codigo, fruta->nome, qtd, fruta->preco * qtd);
            printf("Venda realizada com sucesso!\n");
        }
    } else {
        printf("Fruta não encontrada.\n");
    }
}

void registrarVenda(int codigo, char *nome, int quantidade, float preco) {
    FILE *file = fopen("vendas.txt", "a");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de vendas.\n");
        return;
    }
    fprintf(file, "Código: %d, Nome: %s, Quantidade: %d, Total: %.2f\n", codigo, nome, quantidade, preco);
    fclose(file);
}
