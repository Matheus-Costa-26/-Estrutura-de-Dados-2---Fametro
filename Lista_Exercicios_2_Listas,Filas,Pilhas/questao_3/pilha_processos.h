#ifndef PILHA_PROCESSOS_H
#define PILHA_PROCESSOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Definição da estrutura Frame (o nó da pilha)
typedef struct Frame {
    char func[48];
    int sp; // stack pointer lógico/simulado
    struct Frame *baixo; // próximo elemento em direção ao fundo
} Frame;

// Definição da estrutura Pilha (o gerenciador da pilha)
typedef struct {
    Frame *topo; // O topo da pilha (head)
} Pilha;

// Protótipos das Funções da Pilha
void pilha_init(Pilha* p);
bool push(Pilha* p, const char *func, int sp);
bool pop(Pilha* p, Frame *out);
bool peek(Pilha* p, Frame *out);
bool vazia(Pilha* p);
void limpar(Pilha* p);
void trace(Pilha* p);

#endif // PILHA_PROCESSOS_H