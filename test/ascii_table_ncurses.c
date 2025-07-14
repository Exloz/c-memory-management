
#include <ncurses.h>

void init_colors() {
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);    // Control
    init_pair(2, COLOR_GREEN, COLOR_BLACK);  // ASCII est ndar
    init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Extendidos
}

int main() {
    initscr();              // Inicia ncurses
    noecho();               // No mostrar teclas
    cbreak();               // Input inmediato
    curs_set(0);            // Oculta cursor

    init_colors();

    for (int i = 0; i < 256; i++) {
        int row = i / 16;
        int col = i % 16;

        int x = col * 15 + 2;
        int y = row + 1;

        if (i <= 31 || i == 127)
            attron(COLOR_PAIR(1));
        else if (i >= 128)
            attron(COLOR_PAIR(3));
        else
            attron(COLOR_PAIR(2));

        mvprintw(y, x, "D:%3d H:%02X ", i, i);
        if (i < 32 || i == 127)
            printw(".");
        else
            printw("%c", i);

        attroff(COLOR_PAIR(1));
        attroff(COLOR_PAIR(2));
        attroff(COLOR_PAIR(3));
    }

    mvprintw(18, 0, "Presiona cualquier tecla para salir...");
    refresh();
    getch();    // Espera input

    endwin();   // Termina ncurses
    return 0;
}
