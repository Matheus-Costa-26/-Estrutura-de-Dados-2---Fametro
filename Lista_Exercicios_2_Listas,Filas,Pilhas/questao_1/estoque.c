#include "estoque.h"

// Função auxiliar para criar um novo nó
// O(1) - Tempo constante
Produto* criar_novo_no(Produto p) {
    Produto *novo = (Produto *)malloc(sizeof(Produto));
    if (novo == NULL) {
        perror("Erro ao alocar memória para novo produto");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->codigo, p.codigo, 16);
    strncpy(novo->nome, p.nome, 64);
    novo->qtd = p.qtd;
    novo->preco = p.preco;
    novo->prox = NULL;
    return novo;
}

// 1. Inserir no início
// O(1) - Tempo constante
Produto* inserir_inicio(Produto *L, Produto p) {
    Produto *novo = criar_novo_no(p);
    novo->prox = L;
    return novo;
}

// 2. Inserir ordenado por código (e atualizar se existir)
// O(N) - Linear no número de elementos
Produto* inserir_ordenado_por_codigo(Produto *L, Produto p) {
    Produto *atual = L;
    Produto *anterior = NULL;

    // 1. Busca: Verifica se o código já existe
    while (atual != NULL) {
        int comparacao = strcmp(atual->codigo, p.codigo);
        if (comparacao == 0) {
            // Código encontrado: Atualiza qtd e preco
            atual->qtd = p.qtd;
            atual->preco = p.preco;
            // O nome também pode ser atualizado: strncpy(atual->nome, p.nome, 64);
            printf("Produto %s atualizado (qtd: %d, preco: %.2f).\n", p.codigo, p.qtd, p.preco);
            return L; // Retorna a cabeça da lista inalterada
        } else if (comparacao > 0) {
            // Posição de inserção encontrada (mantendo a ordem)
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }

    // 2. Inserção: O código não existe, insere um novo nó ordenadamente
    Produto *novo = criar_novo_no(p);
    
    if (anterior == NULL) {
        // Inserir no início (ou lista vazia)
        novo->prox = L;
        return novo; // Nova cabeça
    } else {
        // Inserir no meio ou no fim
        novo->prox = atual;
        anterior->prox = novo;
        return L; // Cabeça inalterada
    }
}

// 3. Remover por código
// O(N) - Linear no número de elementos
Produto* remover_por_codigo(Produto *L, const char *codigo) {
    Produto *atual = L;
    Produto *anterior = NULL;

    // Percorre a lista até encontrar o código
    while (atual != NULL && strcmp(atual->codigo, codigo) != 0) {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL) {
        // Produto não encontrado
        printf("ERRO: Produto com código %s não encontrado para remoção.\n", codigo);
        return L;
    }

    // Produto encontrado (atual aponta para o nó a ser removido)
    if (anterior == NULL) {
        // Remover o primeiro nó
        L = atual->prox;
    } else {
        // Remover um nó no meio ou no fim
        anterior->prox = atual->prox;
    }

    printf("Produto %s (%s) removido com sucesso.\n", atual->codigo, atual->nome);
    free(atual); // Libera a memória
    return L;
}

// 4. Ajustar quantidade
// O(N) - Linear no número de elementos
Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd) {
    Produto *p = buscar(L, codigo);

    if (p == NULL) {
        printf("ERRO: Produto com código %s não encontrado para ajuste de quantidade.\n", codigo);
        return L;
    }

    int nova_qtd = p->qtd + delta_qtd;

    if (nova_qtd < 0) {
        printf("ERRO: O ajuste de %d resultaria em quantidade negativa (%d). Operação cancelada.\n", delta_qtd, nova_qtd);
        return L;
    }

    p->qtd = nova_qtd;
    printf("Quantidade de %s (%s) ajustada. Nova Qtd: %d.\n", p->codigo, p->nome, p->qtd);

    // Se a quantidade se tornar 0, pode-se optar por remover o produto.
    // O requisito não exige, mas seria uma boa prática.
    /*
    if (p->qtd == 0) {
        printf("Produto com Qtd 0 será removido.\n");
        return remover_por_codigo(L, codigo);
    }
    */
   
    return L;
}


// 5. Buscar por código
// O(N) - Linear no número de elementos
Produto* buscar(Produto *L, const char *codigo) {
    Produto *atual = L;
    while (atual != NULL) {
        if (strcmp(atual->codigo, codigo) == 0) {
            return atual; // Encontrado
        }
        atual = atual->prox;
    }
    return NULL; // Não encontrado
}

// 6. Listar todos os produtos
// O(N) - Linear no número de elementos
void listar(Produto *L) {
    if (L == NULL) {
        printf("\nO estoque está vazio.\n");
        return;
    }
    printf("\n--- Catálogo de Estoque ---\n");
    printf("| %-15s | %-60s | %-5s | %-10s |\n", "CÓDIGO", "NOME", "QTD", "PREÇO (R$)");
    printf("|-----------------|--------------------------------------------------------------|-------|------------|\n");
    
    Produto *atual = L;
    while (atual != NULL) {
        printf("| %-15s | %-60s | %5d | %10.2f |\n", 
               atual->codigo, atual->nome, atual->qtd, atual->preco);
        atual = atual->prox;
    }
    printf("--------------------------------------------------------------------------------------------------\n");
}

// 7. Limpar a lista (liberar toda a memória)
// O(N) - Linear no número de elementos
Produto* limpar(Produto *L) {
    Produto *atual = L;
    Produto *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    printf("Estoque completamente limpo. Memória liberada.\n");
    return NULL; // A lista está vazia
}

// Geração do Relatório (REL)
// O(N) - Linear no número de elementos
Relatorio gerar_relatorio(Produto *L) {
    Relatorio rel = {0, 0.0, {"", "", 0, 0.0, NULL}}; // Inicializa o relatório
    float maior_valor_imobilizado = -1.0;
    
    Produto *atual = L;
    while (atual != NULL) {
        // 1. Total de itens distintos
        rel.total_distintos++;

        // 2. Valor total do estoque
        float valor_produto = atual->qtd * atual->preco;
        rel.valor_total_estoque += valor_produto;

        // 3. Produto com maior valor imobilizado (qtd * preco)
        if (valor_produto > maior_valor_imobilizado) {
            maior_valor_imobilizado = valor_produto;
            // Copia o produto (evita problemas se o original for desalocado)
            strncpy(rel.produto_maior_valor.codigo, atual->codigo, 16);
            strncpy(rel.produto_maior_valor.nome, atual->nome, 64);
            rel.produto_maior_valor.qtd = atual->qtd;
            rel.produto_maior_valor.preco = atual->preco;
            // O campo 'prox' do produto de relatório é irrelevante, mantido como NULL ou copiado, mas não usado.
        }

        atual = atual->prox;
    }

    return rel;
}