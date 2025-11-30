#include "info.hpp"

Info::Info() {}

void Info::show_info(WINDOW *win, unsigned int speed, unsigned int distance, int direction, unsigned int turns) {
    wchar_t direction_symbol;

    switch (direction) {
        case -1:
            direction_symbol = WCHAR_ARROW_LEFT;
            break;

        case 0:
        default:
            direction_symbol = WCHAR_ARROW_UP;
            break;

        case 1:
            direction_symbol = WCHAR_ARROW_RIGHT;
            break;
    }

    mvwprintw(win, 1, 1, "Speed: %d km/h", speed * 10);
    mvwprintw(win, 2, 1, "Direction: %lc", direction_symbol);
    mvwprintw(win, 3, 1, "Turns: %d", turns);
    mvwprintw(win, 4, 1, "Distance: %d", distance);

    mvwprintw(win, 6, 1, "Use %lc, %lc, %lc", WCHAR_ARROW_LEFT, WCHAR_ARROW_UP, WCHAR_ARROW_RIGHT);
    mvwprintw(win, 7, 1, "to change direction");
    mvwprintw(win, 8, 1, "-, = to change speed");

    mvwprintw(win, 10, 1, "ENTER to make a turn");
    mvwprintw(win, 11, 1, "q to quit");
}

void Info::game_over(WINDOW *win) {
    mvwaddstr(win, 3, 1, "GAME OVER");
    mvwaddstr(win, 5, 1, "Press any key to exit...");
}
