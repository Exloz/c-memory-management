
#include <stdio.h>
#include <stdint.h>
#include <math.h>

// Funci¢n para imprimir los bits de un entero de 32 bits
void print_bits(uint32_t num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i == 31 || i == 23) printf(" "); // separador para signo y exponente
    }
    printf("\n");
}

int main() {
    float f;
    printf("Ingresa un n£mero float: ");
    scanf("%f", &f);

    // Interpretar los bits del float como uint32_t
    uint32_t bits = *(uint32_t*)&f;

    printf("\nValor float: %f\n", f);
    printf("Bits (IEEE 754): ");
    print_bits(bits);

    // Extraer partes
    int sign     = (bits >> 31) & 0x1;
    int exponent = (bits >> 23) & 0xFF;
    int mantissa = bits & 0x7FFFFF;

    // Mostrar partes
    printf("\nSigno:     %d (%s)\n", sign, sign ? "negativo" : "positivo");
    printf("Exponente: %d (sin bias: %d)\n", exponent, exponent - 127);
    printf("Mantisa:   0x%06X\n", mantissa);

    // Reconstrucci¢n
    float real_mantissa = 1.0f;
    for (int i = 0; i < 23; i++) {
        if ((mantissa >> (22 - i)) & 1)
            real_mantissa += powf(2, -(i + 1));
    }

    float final_value = powf(2, exponent - 127) * real_mantissa;
    if (sign) final_value = -final_value;

    printf("\nReconstruido paso a paso:\n");
    printf("  = %s1.%s x 2^%d\n",
        sign ? "-" : "",
        "mantisa_binaria",
        exponent - 127);
    printf("  = %f\n", final_value);

    return 0;
}
