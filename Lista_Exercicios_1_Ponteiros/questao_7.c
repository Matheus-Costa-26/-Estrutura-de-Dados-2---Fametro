#include <stdio.h>

void inverterString(char *s) {
    char *fim = s;
    
    while (*fim) fim++;
    fim--;
    
    while (s < fim) {
        char temp = *s;
        *s = *fim;
        *fim = temp;
        s++;
        fim--;
    }
}

int main() {
    char texto[] = "brasil";
    
    printf("Original: %s\n", texto);
    inverterString(texto);
    printf("Invertida: %s\n", texto);
    
    return 0;
}
