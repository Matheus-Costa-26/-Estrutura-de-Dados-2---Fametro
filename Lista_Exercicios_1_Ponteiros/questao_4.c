#include <stdio.h>

void dobrar(int *n) {
    *n *= 2;
}

int main() {
    int num = 5;
    
    printf("Antes: %d\n", num);
    dobrar(&num);
    printf("Depois: %d\n", num);
    
    return 0;
}
