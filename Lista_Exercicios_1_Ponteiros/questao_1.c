#include <stdio.h>

// Função para trocar valores usando ponteiros
void trocarValores(int *ptr1, int *ptr2) {
    int temp = *ptr1;  // Armazena o valor apontado por ptr1
    *ptr1 = *ptr2;     // Atribui o valor de ptr2 para ptr1
    *ptr2 = temp;      // Atribui o valor temporário para ptr2
}

int main() {
    int a, b;
    
    // Leitura dos valores
    printf("Digite o primeiro valor: ");
    scanf("%d", &a);
    
    printf("Digite o segundo valor: ");
    scanf("%d", &b);
    
    // Exibe valores antes da troca
    printf("\nAntes da troca:\n");
    printf("a = %d, b = %d\n", a, b);
    
    // Chama a função de troca passando os endereços das variáveis
    trocarValores(&a, &b);
    
    // Exibe valores depois da troca
    printf("\nDepois da troca:\n");
    printf("a = %d, b = %d\n", a, b);
    
    return 0;
}
