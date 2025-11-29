#include "track.hpp"


Track::Track(int max_win_row, int max_win_col) {
    this->max_row = max_win_row;
    this->max_col = max_win_col;
    this->width = INITIAL_TRACK_WIDTH;
    this->x_buf_offset = (this->max_col - this->width - 2) / 2;

    this->buffer = new char*[this->max_row];
    for (int i = 0; i < this->max_row; i++) {
        this->buffer[i] = new char[this->max_col];
    }
}

Track::~Track() {
    for (int i = 0; i < this->max_row; i++) {
        delete[] this->buffer[i];
    }
    delete[] this->buffer;
}

void Track::detect_collision() {
    int vx, vy;
    this->vehicle->getxy(vx, vy);
    this->is_collision = (bool) (this->buffer[vy][vx] == SYMBOL_BORDER);
}

void Track::draw_vehicle() {
    int vx, vy;
    this->vehicle->getxy(vx, vy);
    this->buffer[vy][vx] = SYMBOL_VEHICLE;
}

void Track::calculate_new_offsets() {
    int new_x_offset = this->x_offset, new_width = this->width, offset_delta, width_delta;

    do {
        // new_width += (rand() % 3) - 1;
        new_width = INITIAL_TRACK_WIDTH;
        width_delta = this->width - new_width;

        if (this->preserve_x_offset_lines == 0) {
            new_x_offset = (rand() % 3) - 1;
        }

        offset_delta = this->x_offset - new_x_offset;
    } while (abs(offset_delta) > 1 || (abs(width_delta) > 1) || (abs(offset_delta) == 1 && abs(width_delta) == 1) || new_width > 7 || new_width < 2);

    this->width = new_width;
    this->x_offset = new_x_offset;

    if (this->preserve_x_offset_lines > 0) {
        this->preserve_x_offset_lines--;
    } else {
        if (this->x_offset <= 0) {
            this->preserve_x_offset_lines = rand() % (this->x_buf_offset / 2);
        } else {
            this->preserve_x_offset_lines = rand() % ((this->max_col - this->x_buf_offset - this->width) / 2);
        }
    }
}

void Track::assign_vehicle(Vehicle *vehicle) {
    this->vehicle = vehicle;
}

void Track::shift_y(int lines_num) {
    int i, j;

    for (i = this->max_row - 1; i >= lines_num; i--) {
        for (j = 0; j < this->max_col; j++) {
            this->buffer[i][j] = this->buffer[i - lines_num][j];
        }
    }

    for (i = lines_num - 1; i >= 0; i--) {
        this->x_buf_offset += this->x_offset;

        for (j = 0; j < this->x_buf_offset; j++) {
            this->buffer[i][j] = SYMBOL_EMPTY;
        }

        this->buffer[i][j] = SYMBOL_BORDER;

        for (j++; j <= this->x_buf_offset + this->width; j++) {
            this->buffer[i][j] = SYMBOL_TRACK;
        }

        this->buffer[i][j] = SYMBOL_BORDER;

        for (j++; j < this->max_col; j++) {
            this->buffer[i][j] = SYMBOL_EMPTY;
        }

        this->calculate_new_offsets();
    }
}

void Track::draw(WINDOW *win) {
    int i, j;

    this->detect_collision();
    this->draw_vehicle();

    char *str = new char[this->max_col + 1];
    for (i = 0; i < this->max_row; i++) {
        for (j = 0; j < this->max_col; j++) {
            str[j] = this->buffer[i][j];
        }
        str[this->max_col] = '\0';
        mvwaddstr(win, i, 0, str);
    }

    delete str;
}

bool Track::collision() {
    return this->is_collision;
}
