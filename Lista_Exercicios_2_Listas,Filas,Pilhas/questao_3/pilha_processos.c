#include "pilha_processos.h"

// 1. Inicializa a Pilha
// O(1)
void pilha_init(Pilha* p) {
    p->topo = NULL;
}

// 5. Verifica se a Pilha está vazia
// O(1)
bool vazia(Pilha* p) {
    return p->topo == NULL;
}

// Função auxiliar para criar um novo Frame
// O(1)
static Frame* criar_novo_frame(const char *func, int sp) {
    Frame *novo = (Frame *)malloc(sizeof(Frame));
    if (novo == NULL) {
        perror("Erro ao alocar memória para o Frame");
        exit(EXIT_FAILURE);
    }
    strncpy(novo->func, func, 48);
    novo->func[47] = '\0'; // Garantir terminação
    novo->sp = sp;
    novo->baixo = NULL;
    return novo;
}

// 2. Push (Empilhar)
// O(1) - Adiciona o Frame no topo
bool push(Pilha* p, const char *func, int sp) {
    Frame *novo = criar_novo_frame(func, sp);
    
    // O novo frame aponta para o antigo topo
    novo->baixo = p->topo;
    
    // O novo frame se torna o topo
    p->topo = novo;
    
    return true; // Sucesso
}

// 3. Pop (Desempilhar)
// O(1) - Remove o Frame do topo
bool pop(Pilha* p, Frame *out) {
    if (vazia(p)) {
        return false;
    }

    Frame *temp = p->topo;
    
    // Copia os dados do topo para a estrutura de saída
    strncpy(out->func, temp->func, 48);
    out->sp = temp->sp;
    
    // Move o topo para o próximo Frame abaixo
    p->topo = p->topo->baixo;
    
    free(temp); // Libera a memória do Frame removido
    return true;
}

// 4. Peek (Consultar o topo)
// O(1) - Consulta o Frame do topo sem removê-lo
bool peek(Pilha* p, Frame *out) {
    if (vazia(p)) {
        return false;
    }

    // Copia os dados do topo para a estrutura de saída
    strncpy(out->func, p->topo->func, 48);
    out->sp = p->topo->sp;
    
    // Note: out->baixo não é relevante
    return true;
}

// 6. Limpar (Esvaziar toda a Pilha)
// O(N)
void limpar(Pilha* p) {
    Frame *atual = p->topo;
    Frame *proximo;

    while (atual != NULL) {
        proximo = atual->baixo;
        free(atual);
        atual = proximo;
    }
    p->topo = NULL;
}

// Funções de Aplicação

// Trace (Imprimir a Pilha do Topo ao Fundo)
// O(N)
void trace(Pilha* p) {
    if (vazia(p)) {
        printf("\nO Stack Frame está vazio. Nenhum processo em execução.\n");
        return;
    }
    
    printf("\n--- Stack Trace (Topo ao Fundo) ---\n");
    
    // Precisamos percorrer a pilha, mas numerar de forma decrescente para simular profundidade,
    // ou apenas numerar do topo (nível 0) para o fundo.

    Frame *atual = p->topo;
    int nivel = 0;
    
    // Primeiro, conta o número total de frames para simular um "nível" mais lógico
    int count = 0;
    Frame *temp = p->topo;
    while(temp != NULL) {
        count++;
        temp = temp->baixo;
    }

    int nivel_simulado = count - 1;

    while (atual != NULL) {
        printf("[Nível %d] | Função: %-40s | SP (Endereço): 0x%04X\n", 
               nivel_simulado, atual->func, atual->sp);
        atual = atual->baixo;
        nivel_simulado--;
    }
    printf("-----------------------------------\n");
}