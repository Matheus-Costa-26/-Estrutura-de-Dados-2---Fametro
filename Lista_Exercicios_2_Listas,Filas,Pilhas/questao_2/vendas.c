#include "vendas.h"

// 1. Inicializar Fila
// O(1)
void inicializar(Fila* f) {
    f->ini = NULL;
    f->fim = NULL;
}

// Função auxiliar para criar um novo nó de Cliente
// O(1)
static Cliente* criar_novo_cliente(Cliente c) {
    Cliente *novo = (Cliente *)malloc(sizeof(Cliente));
    if (novo == NULL) {
        perror("Erro ao alocar memória para novo cliente");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->id, c.id, 24);
    novo->qtd = c.qtd;
    novo->prox = NULL;
    return novo;
}

// 2. Enfileirar (Enqueue)
// O(1)
void enfileirar(Fila* f, Cliente c) {
    Cliente *novo = criar_novo_cliente(c);

    if (vazia(f)) {
        f->ini = novo;
    } else {
        f->fim->prox = novo;
    }
    f->fim = novo;
}

// 3. Desenfileirar (Dequeue)
// O(1)
bool desenfileirar(Fila* f, Cliente *out) {
    if (vazia(f)) {
        return false;
    }

    Cliente *temp = f->ini;

    // Copia os dados do cliente para a estrutura de saída
    strncpy(out->id, temp->id, 24);
    out->qtd = temp->qtd;

    f->ini = f->ini->prox;

    // Se o último elemento foi removido, a fila fica vazia
    if (f->ini == NULL) {
        f->fim = NULL;
    }

    free(temp);
    return true;
}

// 4. Fila Vazia
// O(1)
bool vazia(Fila* f) {
    return f->ini == NULL;
}

// 5. Limpar Fila
// O(N)
void limpar(Fila* f) {
    Cliente *atual = f->ini;
    Cliente *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    f->ini = NULL;
    f->fim = NULL;
}

// --- Funções Auxiliares para a Aplicação e Relatório ---

// Adiciona um cliente à lista de não atendidos (Lista Simplesmente Encadeada)
// O(1) (Adição no início é mais simples)
NaoAtendido* adicionar_nao_atendido(NaoAtendido *L, Cliente c) {
    NaoAtendido *novo = (NaoAtendido *)malloc(sizeof(NaoAtendido));
    if (novo == NULL) {
        perror("Erro ao alocar memória para não atendido");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->id, c.id, 24);
    novo->qtd_solicitada = c.qtd;
    novo->prox = L;
    return novo;
}

// Limpa a lista de não atendidos
// O(N)
NaoAtendido* limpar_nao_atendidos(NaoAtendido *L) {
    NaoAtendido *atual = L;
    NaoAtendido *proximo;
    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    return NULL;
}

// Atualiza a lista Top-3 Compras
// O(1) - O array tem tamanho fixo (3), então a busca e inserção é constante.
void atualizar_top_compras(Relatorio* rel, const char* id, int qtd_comprada) {
    // 1. Encontra a posição correta (inserção ordenada)
    int pos = -1;
    for (int i = 0; i < 3; i++) {
        if (qtd_comprada > rel->top_compras[i].qtd_comprada) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        // 2. Move os elementos para baixo (Shift down)
        for (int i = 2; i > pos; i--) {
            rel->top_compras[i] = rel->top_compras[i-1];
        }
        
        // 3. Insere o novo
        strncpy(rel->top_compras[pos].id, id, 24);
        rel->top_compras[pos].qtd_comprada = qtd_comprada;
    }
}

// Processamento da Fila de Vendas
// O(N) - N é o número de clientes na fila
void processar_vendas(Fila* f, Relatorio* rel, int* estoque) {
    if (vazia(f)) {
        printf("ERRO: A fila de espera está vazia. Nenhuma venda iniciada.\n");
        return;
    }

    if (*estoque <= 0) {
        printf("ERRO: O estoque está zerado. Nenhuma venda pode ser iniciada.\n");
        return;
    }

    printf("\n--- INÍCIO DO PROCESSAMENTO DE VENDAS ---\n");
    printf("Estoque inicial para a venda: %d ingressos.\n", *estoque);
    
    Cliente c_atendido;
    char confirmacao[8];
    int qtd_vendida;

    while (desenfileirar(f, &c_atendido)) {
        
        printf("\nAtendendo cliente %s (solicitou %d ingressos). Estoque atual: %d.\n", 
               c_atendido.id, c_atendido.qtd, *estoque);

        if (*estoque <= 0) {
            // Se esgotou no processamento do cliente anterior
            printf("ESTOQUE ZERADO. O cliente %s não pode ser atendido.\n", c_atendido.id);
            // Adiciona o cliente à lista de não atendidos
            rel->lista_nao_atendidos = adicionar_nao_atendido(rel->lista_nao_atendidos, c_atendido);
            break; // Sai do loop principal de vendas
        }

        if (c_atendido.qtd <= *estoque) {
            // Caso 1: Quantidade solicitada <= Estoque (Venda completa)
            qtd_vendida = c_atendido.qtd;
            *estoque -= qtd_vendida;
            rel->total_vendido += qtd_vendida;
            rel->clientes_atendidos++;
            
            printf("  Venda CONFIRMADA: %d ingressos. Novo estoque: %d.\n", qtd_vendida, *estoque);
            atualizar_top_compras(rel, c_atendido.id, qtd_vendida);

        } else {
            // Caso 2: Quantidade solicitada > Estoque (Oferta parcial)
            qtd_vendida = *estoque;

            printf("  Estoque insuficiente. Podemos oferecer %d ingressos. Aceita (S/N)? ", qtd_vendida);
            
            // Lê a resposta do usuário
            if (fgets(confirmacao, sizeof(confirmacao), stdin) == NULL) {
                // Caso de erro na leitura, trata como não
                printf("\n  Erro na leitura. Cliente %s registrado como não atendido.\n", c_atendido.id);
                rel->lista_nao_atendidos = adicionar_nao_atendido(rel->lista_nao_atendidos, c_atendido);
                continue;
            }
            
            // Limpa a string de confirmação
            confirmacao[strcspn(confirmacao, "\n")] = 0; 

            if (strlen(confirmacao) > 0 && (tolower(confirmacao[0]) == 's')) {
                // Confirmação: Vende o restante do estoque
                *estoque -= qtd_vendida; // *estoque fica zero
                rel->total_vendido += qtd_vendida;
                rel->clientes_atendidos++;

                printf("  Oferta aceita. Venda PARCIAL de %d ingressos. Estoque zerado.\n", qtd_vendida);
                atualizar_top_compras(rel, c_atendido.id, qtd_vendida);
                
                // Vendas zeram o estoque, então para.
                break; 
            } else {
                // Não aceitou a oferta parcial
                printf("  Oferta recusada. Cliente %s registrado como não atendido.\n", c_atendido.id);
                rel->lista_nao_atendidos = adicionar_nao_atendido(rel->lista_nao_atendidos, c_atendido);
            }
        }
    } // Fim do while

    if (vazia(f) && *estoque > 0) {
        printf("\nTODOS OS CLIENTES FORAM ATENDIDOS. Restam %d ingressos no estoque.\n", *estoque);
    } else if (*estoque <= 0) {
        printf("\nPROCESSO DE VENDA FINALIZADO. ESTOQUE ZERADO.\n");
    } else if (!vazia(f) && *estoque > 0) {
        printf("\nPROCESSAMENTO INTERROMPIDO. A fila ainda contém clientes e o estoque não está zerado.\n");
    }
}

// Exibição do Relatório
// O(N) - N é o número de clientes não atendidos
void exibir_relatorio(Relatorio* rel, int estoque_restante) {
    printf("\n======================================================\n");
    printf("                  RELATÓRIO DE VENDAS\n");
    printf("======================================================\n");
    printf("Estoque Restante: %d ingressos\n", estoque_restante);
    printf("Total de Ingressos Vendidos: %d\n", rel->total_vendido);
    printf("Clientes Atendidos (Total ou Parcialmente): %d\n", rel->clientes_atendidos);

    printf("\n--- Top 3 Maiores Compras ---\n");
    for (int i = 0; i < 3; i++) {
        if (rel->top_compras[i].qtd_comprada > 0) {
            printf("  #%d: %s - %d ingressos\n", 
                   i + 1, rel->top_compras[i].id, rel->top_compras[i].qtd_comprada);
        } else {
            printf("  #%d: N/A\n", i + 1);
        }
    }

    printf("\n--- Clientes NÃO Atendidos ---\n");
    if (rel->lista_nao_atendidos == NULL) {
        printf("  Nenhum cliente registrado como não atendido.\n");
    } else {
        NaoAtendido *atual = rel->lista_nao_atendidos;
        while (atual != NULL) {
            printf("  ID: %s - Solicitado: %d ingressos\n", atual->id, atual->qtd_solicitada);
            atual = atual->prox;
        }
    }
    printf("======================================================\n");
}