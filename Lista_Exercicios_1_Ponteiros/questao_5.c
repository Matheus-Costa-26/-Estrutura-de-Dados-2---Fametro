#include <stdio.h>

void copiarString(char *o, char *d) {
    while (*d++ = *o++);
}

int main() {
    char o[] = "Hello";
    char d[50];
    
    copiarString(o, d);
    printf("Original: %s\nCópia: %s\n", o, d);
    
    return 0;
}
