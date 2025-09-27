void calcular(float a, float b, float *soma, float *sub, float *mult, float *div) {
    *soma = a + b;
    *sub = a - b;
    *mult = a * b;
    *div = (b != 0) ? a / b : 0; // Evita divisão por zero
}
