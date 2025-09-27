#include "estoque.h"

// Função para exibir o menu
void exibir_menu() {
    printf("\n--- Menu de Controle de Estoque ---\n");
    printf("Comandos:\n");
    printf("ADD <codigo> <nome> <qtd> <preco>  - Adicionar/Atualizar Produto (Inserção Ordenada)\n");
    printf("UPD <codigo> <delta_qtd>           - Ajustar quantidade (+/- delta_qtd)\n");
    printf("DEL <codigo>                       - Remover Produto\n");
    printf("FIND <codigo>                      - Buscar e exibir Produto\n");
    printf("LIST                               - Listar todos os Produtos\n");
    printf("REL                                - Gerar Relatório de Estoque\n");
    printf("CLEAN                              - Limpar/Esvaziar todo o estoque\n");
    printf("EXIT                               - Sair do programa\n");
    printf("-----------------------------------\n");
}

// Função para processar a entrada do usuário
void processar_comando(Produto **L, const char *comando, char *resto) {
    // Conversão do comando para minúsculas para facilitar a comparação
    char cmd_lower[10];
    strncpy(cmd_lower, comando, 9);
    cmd_lower[9] = '\0';
    for (int i = 0; cmd_lower[i]; i++) {
        cmd_lower[i] = tolower(cmd_lower[i]);
    }

    if (strcmp(cmd_lower, "add") == 0) {
        Produto p = {"", "", 0, 0.0, NULL};
        
        // Tenta ler o resto da linha com sscanf
        if (sscanf(resto, "%15s \"%63[^\"]\" %d %f", 
                   p.codigo, p.nome, &p.qtd, &p.preco) == 4) {
            
            // Verifica se a quantidade e o preço são válidos
            if (p.qtd < 0) {
                 printf("ERRO: Quantidade inicial não pode ser negativa.\n");
                 return;
            }
            if (p.preco < 0.0) {
                printf("ERRO: Preço não pode ser negativo.\n");
                return;
            }

            // A função inserir_ordenado_por_codigo já lida com a atualização
            *L = inserir_ordenado_por_codigo(*L, p);
            
        } else {
            printf("ERRO: Sintaxe inválida para ADD. Esperado: ADD <code> \"<nome>\" <qtd> <preco>\n");
        }
    } else if (strcmp(cmd_lower, "upd") == 0) {
        char codigo[16];
        int delta_qtd;
        
        if (sscanf(resto, "%15s %d", codigo, &delta_qtd) == 2) {
            *L = ajustar_quantidade(*L, codigo, delta_qtd);
        } else {
            printf("ERRO: Sintaxe inválida para UPD. Esperado: UPD <code> <delta_qtd>\n");
        }
    } else if (strcmp(cmd_lower, "del") == 0) {
        char codigo[16];
        if (sscanf(resto, "%15s", codigo) == 1) {
            *L = remover_por_codigo(*L, codigo);
        } else {
            printf("ERRO: Sintaxe inválida para DEL. Esperado: DEL <code>\n");
        }
    } else if (strcmp(cmd_lower, "find") == 0) {
        char codigo[16];
        if (sscanf(resto, "%15s", codigo) == 1) {
            Produto *p = buscar(*L, codigo);
            if (p != NULL) {
                printf("Produto encontrado:\n");
                printf("  Código: %s\n", p->codigo);
                printf("  Nome: %s\n", p->nome);
                printf("  Qtd: %d\n", p->qtd);
                printf("  Preço: R$ %.2f\n", p->preco);
                printf("  Valor Imobilizado: R$ %.2f\n", p->qtd * p->preco);
            } else {
                printf("Produto com código %s NÃO encontrado.\n", codigo);
            }
        } else {
            printf("ERRO: Sintaxe inválida para FIND. Esperado: FIND <code>\n");
        }
    } else if (strcmp(cmd_lower, "list") == 0) {
        listar(*L);
    } else if (strcmp(cmd_lower, "rel") == 0) {
        Relatorio rel = gerar_relatorio(*L);

        printf("\n--- Relatório de Estoque ---\n");
        printf("Total de itens distintos: %d\n", rel.total_distintos);
        printf("Valor total do estoque (R$): %.2f\n", rel.valor_total_estoque);
        
        if (rel.total_distintos > 0) {
            printf("\n--- Produto com MAIOR valor imobilizado ---\n");
            printf("  Código: %s\n", rel.produto_maior_valor.codigo);
            printf("  Nome: %s\n", rel.produto_maior_valor.nome);
            printf("  Qtd: %d\n", rel.produto_maior_valor.qtd);
            printf("  Preço: R$ %.2f\n", rel.produto_maior_valor.preco);
            printf("  Valor Imobilizado: R$ %.2f\n", rel.produto_maior_valor.qtd * rel.produto_maior_valor.preco);
            printf("-------------------------------------------\n");
        }
    } else if (strcmp(cmd_lower, "clean") == 0) {
        *L = limpar(*L);
    } else {
        printf("ERRO: Comando desconhecido ou sintaxe inválida. Digite LIST para ver os produtos ou EXIT para sair.\n");
    }
}

int main() {
    Produto *estoque = NULL;
    char linha[256];
    char comando[10];
    char resto[246]; // Tamanho total - tamanho do comando - espaço

    printf("--- Sistema de Controle de Estoque (Lista Encadeada) ---\n");
    exibir_menu();

    while (1) {
        printf("\n> ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break; // Erro ou EOF
        }
        
        // Remove a nova linha se existir
        linha[strcspn(linha, "\n")] = 0; 

        // Se a linha estiver vazia, continua
        if (strlen(linha) == 0) {
            continue;
        }

        // Tenta ler o comando e o resto da linha
        if (sscanf(linha, "%9s%*[ \t]%[^\n]", comando, resto) < 1) {
            printf("ERRO: Comando não reconhecido.\n");
            continue;
        }

        // Verifica o comando de saída
        char cmd_lower[10];
        strncpy(cmd_lower, comando, 9);
        cmd_lower[9] = '\0';
        for (int i = 0; cmd_lower[i]; i++) {
            cmd_lower[i] = tolower(cmd_lower[i]);
        }

        if (strcmp(cmd_lower, "exit") == 0) {
            printf("Saindo do sistema. Limpando a memória...\n");
            estoque = limpar(estoque);
            break;
        }

        // Processa o comando
        processar_comando(&estoque, comando, resto);
    }

    return 0;
}