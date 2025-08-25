#include <stdio.h>

int main() {
    int numero = 42;
    int *ponteiro = &numero;
    
    printf("Valor da variável: %d\n", numero);
    printf("Endereço da variável: %p\n", &numero);
    printf("Valor do ponteiro: %p\n", ponteiro);
    printf("Valor apontado pelo ponteiro: %d\n", *ponteiro);
    
    return 0;
}
