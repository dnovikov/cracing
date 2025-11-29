#include "info.hpp"

Info::Info() {}

void Info::show_info(WINDOW *win, unsigned int speed, unsigned int distance, int direction) {
    char direction_symbol;

    switch (direction) {
        case -1:
            direction_symbol = '<';
            break;

        case 0:
        default:
            direction_symbol = '^';
            break;

        case 1:
            direction_symbol = '>';
            break;
    }

    mvwprintw(win, 1, 1, "Speed: %d0 km/h", speed);
    mvwprintw(win, 2, 1, "Direction: %c", direction_symbol);
    mvwprintw(win, 3, 1, "Distance: %d", distance);

    mvwprintw(win, 5, 1, "Use %lc, %lc, %lc", WCHAR_ARROW_LEFT, WCHAR_ARROW_UP, WCHAR_ARROW_RIGHT);
    mvwprintw(win, 6, 1, "to change direction");
    mvwprintw(win, 7, 1, "-, = to change speed");

    mvwprintw(win, 9, 1, "ENTER to make a turn");
    mvwprintw(win, 10, 1, "q to quit");
}

void Info::game_over(WINDOW *win) {
    mvwaddstr(win, 3, 1, "GAME OVER");
    mvwaddstr(win, 5, 1, "Press any key to exit...");
}
