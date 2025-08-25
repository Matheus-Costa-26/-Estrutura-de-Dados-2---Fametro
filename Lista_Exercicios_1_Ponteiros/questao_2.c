#include <stdio.h>

void encontrarMaiorMenor(int *array, int tamanho, int *maior, int *menor) {
    *maior = array[0];
    *menor = array[0];
    
    for(int i = 1; i < tamanho; i++) {
        if(array[i] > *maior) *maior = array[i];
        if(array[i] < *menor) *menor = array[i];
    }
}

int main() {
    int array[] = {8, 3, 12, 5, 7};
    int tamanho = 5;
    int maior, menor;
    
    encontrarMaiorMenor(array, tamanho, &maior, &menor);
    
    printf("Maior: %d\n", maior);
    printf("Menor: %d\n", menor);
    
    return 0;
}
