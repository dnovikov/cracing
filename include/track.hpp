#ifndef TRACK_HPP
#define TRACK_HPP

#include <ncursesw/ncurses.h>
#include <cstdlib>

#include "vehicle.hpp"

#define INITIAL_TRACK_WIDTH 4

#define SYMBOL_EMPTY ' '
#define SYMBOL_BORDER '#'
#define SYMBOL_TRACK '.'
#define SYMBOL_VEHICLE '@'

class Track {
  private:
    int max_row, max_col, x_buf_offset, width = INITIAL_TRACK_WIDTH, x_offset = 0, preserve_x_offset_lines = 0;
    char **buffer;
    Vehicle *vehicle;
    bool is_collision = false;

    void detect_collision();
    void draw_vehicle();
    void calculate_new_offsets();

  public:
    Track(int max_win_row, int max_win_col);
    ~Track();

    void assign_vehicle(Vehicle *vehicle);
    void shift_y(int lines_num);
    void draw(WINDOW *win);
    bool collision();
};

#endif // TRACK_HPP
