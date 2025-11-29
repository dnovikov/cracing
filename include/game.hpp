#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <locale>
#include <ncursesw/ncurses.h>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

#include "info.hpp"
#include "track.hpp"
#include "vehicle.hpp"

#define MIN_COLS (INITIAL_TRACK_WIDTH + INFO_WIN_WIDTH + 2)

class Game {
    private:
        int max_row, max_col, direction_offset = 0, speed_inc = 0;
        bool game_over = false;
        WINDOW *track_win, *info_win;
        Info *info;
        Track *track;
        Vehicle *vehicle;

        void setup(unsigned int seed);
        void cleanup();

    public:
        void run(unsigned int seed);
};

#endif // GAME_HPP
