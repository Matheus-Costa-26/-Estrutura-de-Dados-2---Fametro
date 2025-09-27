#ifndef VENDAS_H
#define VENDAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> // Para usar o tipo bool
#include <ctype.h>   // Para tolower/toupper, se necessário

// Definição da estrutura Cliente para o nó da fila
typedef struct Cliente {
    char id[24];
    int qtd; // Quantidade de ingressos solicitada
    struct Cliente *prox;
} Cliente;

// Estrutura para a Fila (simplesmente encadeada)
typedef struct {
    Cliente *ini, *fim; // Ponteiros para o início e o fim da fila
} Fila;

// Estrutura para armazenar clientes não atendidos (usaremos uma lista para isso)
typedef struct NaoAtendido {
    char id[24];
    int qtd_solicitada;
    struct NaoAtendido *prox;
} NaoAtendido;

// Estrutura para os dados do Relatório
typedef struct Relatorio {
    int total_vendido;
    int clientes_atendidos;
    NaoAtendido *lista_nao_atendidos; // Lista de não atendidos

    // Top 3 Compras (usaremos um array simples para gerenciamento)
    struct {
        char id[24];
        int qtd_comprada;
    } top_compras[3];

} Relatorio;


// Protótipos das Funções da Fila
void inicializar(Fila* f);
void enfileirar(Fila* f, Cliente c);
bool desenfileirar(Fila* f, Cliente *out);
bool vazia(Fila* f);
void limpar(Fila* f);

// Protótipo para a Lista de Não Atendidos (função auxiliar)
NaoAtendido* adicionar_nao_atendido(NaoAtendido *L, Cliente c);
NaoAtendido* limpar_nao_atendidos(NaoAtendido *L);

// Protótipos das Funções da Aplicação
void processar_vendas(Fila* f, Relatorio* rel, int* estoque);
void exibir_relatorio(Relatorio* rel, int estoque_restante);
void atualizar_top_compras(Relatorio* rel, const char* id, int qtd_comprada);

#endif // VENDAS_H