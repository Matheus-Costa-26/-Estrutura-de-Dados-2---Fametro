#ifndef ESTOQUE_H
#define ESTOQUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower/toupper, se necessário

// Definição da estrutura Produto
typedef struct Produto {
    char codigo[16];
    char nome[64];
    int qtd;
    float preco;
    struct Produto *prox;
} Produto;

// Protótipos das funções de gerência da lista
Produto* inserir_inicio(Produto *L, Produto p);
Produto* inserir_ordenado_por_codigo(Produto *L, Produto p);
Produto* remover_por_codigo(Produto *L, const char *codigo);
Produto* ajustar_quantidade(Produto *L, const char *codigo, int delta_qtd);
Produto* buscar(Produto *L, const char *codigo);
void listar(Produto *L);
Produto* limpar(Produto *L);

// Estrutura para os dados do relatório
typedef struct Relatorio {
    int total_distintos;
    float valor_total_estoque;
    Produto produto_maior_valor;
} Relatorio;

Relatorio gerar_relatorio(Produto *L);

// Função auxiliar para criar um novo nó (para uso interno)
Produto* criar_novo_no(Produto p);

#endif // ESTOQUE_H