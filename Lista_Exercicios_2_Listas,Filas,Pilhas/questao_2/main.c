#include "vendas.h"

// Função para exibir o menu
void exibir_menu() {
    printf("\n--- Menu de Venda de Ingressos ---\n");
    printf("Comandos:\n");
    printf("ADD <id_cliente> <qtd_solicitada>  - Adicionar cliente à fila\n");
    printf("START                              - Iniciar processamento de vendas\n");
    printf("REL                                - Exibir Relatório\n");
    printf("EXIT                               - Sair do programa\n");
    printf("-----------------------------------\n");
}

int main() {
    Fila fila_espera;
    inicializar(&fila_espera);
    
    // Inicializa o Relatório
    Relatorio rel = {0, 0, NULL, {{"", 0}, {"", 0}, {"", 0}}};

    int estoque_inicial = -1;
    int estoque_atual = -1;
    char linha[256];
    char comando[10];
    char resto[246];

    printf("--- Sistema de Fila de Espera para Vendas ---\n");
    
    // 1. Leitura do Estoque Inicial
    while (estoque_inicial < 0) {
        printf("Informe a quantidade inicial de ingressos (Estoque > 0): ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) continue;
        linha[strcspn(linha, "\n")] = 0;
        if (sscanf(linha, "%d", &estoque_inicial) == 1 && estoque_inicial >= 0) {
            estoque_atual = estoque_inicial;
            printf("Estoque inicial definido: %d ingressos.\n", estoque_inicial);
            break;
        } else {
            printf("Entrada inválida. Por favor, digite um número inteiro não negativo.\n");
            estoque_inicial = -1;
        }
    }

    exibir_menu();

    while (1) {
        printf("\n> ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) break;
        
        linha[strcspn(linha, "\n")] = 0; 
        if (strlen(linha) == 0) continue;

        if (sscanf(linha, "%9s%*[ \t]%[^\n]", comando, resto) < 1) {
            continue;
        }

        char cmd_lower[10];
        strncpy(cmd_lower, comando, 9);
        cmd_lower[9] = '\0';
        for (int i = 0; cmd_lower[i]; i++) {
            cmd_lower[i] = tolower(cmd_lower[i]);
        }

        if (strcmp(cmd_lower, "exit") == 0) {
            printf("Saindo do sistema. Limpando a memória...\n");
            limpar(&fila_espera);
            rel.lista_nao_atendidos = limpar_nao_atendidos(rel.lista_nao_atendidos);
            break;
        } else if (strcmp(cmd_lower, "add") == 0) {
            Cliente c = {"", 0, NULL};
            if (sscanf(resto, "%23s %d", c.id, &c.qtd) == 2) {
                if (c.qtd <= 0) {
                    printf("ERRO: Quantidade solicitada deve ser positiva.\n");
                    continue;
                }
                enfileirar(&fila_espera, c);
                printf("Cliente %s com solicitação de %d ingressos adicionado à fila.\n", c.id, c.qtd);
            } else {
                printf("ERRO: Sintaxe inválida para ADD. Esperado: ADD <id_cliente> <qtd_solicitada>\n");
            }
        } else if (strcmp(cmd_lower, "start") == 0) {
            // Verifica se a fila já está limpa e o estoque está zerado
            if (vazia(&fila_espera) && estoque_atual == 0) {
                printf("As vendas já foram processadas, a fila está vazia e o estoque zerou.\n");
            } else {
                processar_vendas(&fila_espera, &rel, &estoque_atual);
            }
        } else if (strcmp(cmd_lower, "rel") == 0) {
            exibir_relatorio(&rel, estoque_atual);
            if (!vazia(&fila_espera)) {
                printf("\nA FILA DE ESPERA AINDA NÃO FOI VAZIA! Clientes restantes na fila.\n");
            }
        } else {
            printf("ERRO: Comando desconhecido. Digite EXIT para sair.\n");
        }
    }

    return 0;
}