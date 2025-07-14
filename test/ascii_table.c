
#include <stdio.h>

void print_colored_ascii(unsigned char c) {
    if (c <= 31 || c == 127) {
        // Rojo: control
        printf("\033[31m"); // rojo
    } else if (c >= 128) {
        // Azul: extendido
        printf("\033[34m"); // azul
    } else {
        // Verde: imprimible
        printf("\033[32m"); // verde
    }

    printf("Dec:%3d Hex:%02X Char:", c, c);
    if (c < 32 || c == 127) {
        printf(" ."); // No imprimibles
    } else {
        printf(" %c", c); // Imprimible
    }

    printf("\033[0m\n"); // reset color
}

int main() {
    for (int i = 0; i < 256; i++) {
        print_colored_ascii((unsigned char)i);
    }
    return 0;
}
