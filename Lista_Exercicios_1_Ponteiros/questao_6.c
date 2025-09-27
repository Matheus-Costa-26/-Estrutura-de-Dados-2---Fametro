#include <stdio.h>

void contarVogaisConsoantes(char *s, int *v, int *c) {
    *v = *c = 0;
    
    while (*s) {
        if (*s == 'a' || *s == 'e' || *s == 'i' || *s == 'o' || *s == 'u' ||
            *s == 'A' || *s == 'E' || *s == 'I' || *s == 'O' || *s == 'U') {
            (*v)++;
        } else if ((*s >= 'a' && *s <= 'z') || (*s >= 'A' && *s <= 'Z')) {
            (*c)++;
        }
        s++;
    }
}

int main() {
    char texto[] = "Hello";
    int v, c;
    
    contarVogaisConsoantes(texto, &v, &c);
    printf("Vogais: %d\nConsoantes: %d\n", v, c);
    
    return 0;
}
