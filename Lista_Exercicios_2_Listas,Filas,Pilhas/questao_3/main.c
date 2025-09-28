#include "pilha_processos.h"

// Variável global/simulada para controlar o Stack Pointer para dar exemplos reais
int sp_base = 0x8000;
const int SP_STEP = 0x0100; // Incremento de 256 bytes

// Função para exibir o menu
void exibir_menu() {
    printf("\n--- Menu de Simulação do Stack Frame ---\n");
    printf("Comandos:\n");
    printf("CALL <nome_funcao>                 - Chama e empilha um novo frame.\n");
    printf("RET                                - Retorna e desempilha o frame do topo.\n");
    printf("PEEK                               - Mostra o frame do topo sem remover.\n");
    printf("TRACE                              - Imprime a pilha completa (topo -> fundo).\n");
    printf("EXIT                               - Limpa e sai do programa.\n");
    printf("----------------------------------------\n");
}

// Função para simular o CALL e calcular o SP
void executar_call(Pilha *p, const char *func) {
    int novo_sp = sp_base;
    sp_base += SP_STEP; // Simula a alocação de espaço no stack

    if (push(p, func, novo_sp)) {
        printf("CALL: Frame '%s' empilhado. SP simulado: 0x%04X.\n", func, novo_sp);
    } else {
        printf("ERRO: Falha ao empilhar o frame.\n");
        sp_base -= SP_STEP; // Desfaz o incremento se falhar
    }
}

// Função para processar a entrada do usuário
void processar_comando(Pilha *p, const char *comando, char *resto) {
    char cmd_lower[10];
    strncpy(cmd_lower, comando, 9);
    cmd_lower[9] = '\0';
    for (int i = 0; cmd_lower[i]; i++) {
        cmd_lower[i] = tolower(cmd_lower[i]);
    }

    if (strcmp(cmd_lower, "call") == 0) {
        char func_name[48];
        if (sscanf(resto, "%47s", func_name) == 1) {
            executar_call(p, func_name);
        } else {
            printf("ERRO: Sintaxe inválida para CALL. Esperado: CALL <nome_funcao>\n");
        }
    } else if (strcmp(cmd_lower, "ret") == 0) {
        Frame out;
        if (pop(p, &out)) {
            // O retorno deve reverter o SP, voltando ao estado anterior
            sp_base -= SP_STEP;
            printf("RET: Função '%s' desempilhada. SP anterior: 0x%04X.\n", out.func, out.sp);
        } else {
            printf("ERRO: A Pilha de Processos (Stack Frame) está vazia. Não há função para retornar.\n");
        }
    } else if (strcmp(cmd_lower, "peek") == 0) {
        Frame out;
        if (peek(p, &out)) {
            printf("PEEK: Topo da Pilha (Função Atual):\n");
            printf("  Função: %s\n", out.func);
            printf("  SP (Endereço): 0x%04X\n", out.sp);
        } else {
            printf("ERRO: A Pilha está vazia.\n");
        }
    } else if (strcmp(cmd_lower, "trace") == 0) {
        trace(p);
    } else {
        printf("ERRO: Comando desconhecido. Digite TRACE para ver o estado atual ou EXIT para sair.\n");
    }
}

int main() {
    Pilha stack;
    pilha_init(&stack);
    
    char linha[128];
    char comando[10];
    char resto[118];

    printf("--- Simulação de Stack Frame (Process Stack) ---\n");
    printf("Endereço de Stack Base Simulado: 0x%04X\n", sp_base);
    exibir_menu();

    // Simulação inicial de um processo principal
    executar_call(&stack, "main");

    while (1) {
        printf("\nProcess Stack > ");
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break; 
        }
        
        // Remove a nova linha
        linha[strcspn(linha, "\n")] = 0; 

        if (strlen(linha) == 0) {
            continue;
        }

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
            printf("Saindo do simulador. Limpando o Stack Frame...\n");
            limpar(&stack);
            break;
        }

        processar_comando(&stack, comando, resto);
    }

    return 0;
}