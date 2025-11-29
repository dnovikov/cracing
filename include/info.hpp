#ifndef INFO_HPP
#define INFO_HPP

#define INFO_WIN_WIDTH 30

#define WCHAR_ARROW_LEFT L'\x2190'
#define WCHAR_ARROW_UP L'\x2191'
#define WCHAR_ARROW_RIGHT L'\x2192'

#include <ncursesw/ncurses.h>

class Info {
  public:
    Info();

    void show_info(WINDOW *win, unsigned int speed, unsigned int distance, int direction);
    void game_over(WINDOW *win);
};

#endif // INFO_HPP
