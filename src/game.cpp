#include "game.hpp"


void Game::setup(unsigned int seed) {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    cbreak();
    nonl();

    getmaxyx(stdscr, this->max_row, this->max_col);

    if (this->max_row < 10) {
        throw std::runtime_error("The game requires min 10 rows to run.");
    }

    if (this->max_col < MIN_COLS) {
        std::ostringstream oss;

        oss << "The game requires min " << MIN_COLS << " columns to run.";

        throw std::runtime_error(oss.str());
    }

    if (!(this->info_win = newwin(this->max_row, INFO_WIN_WIDTH, 0, 0))) {
        throw std::runtime_error("Error creating info window.");
    }

    if (!(this->track_win = newwin(this->max_row, this->max_col - INFO_WIN_WIDTH - 2, 0, INFO_WIN_WIDTH))) {
        throw std::runtime_error("Error creating track window.");
    }

    box(this->info_win, 0, 0);
    box(this->track_win, 0, 0);

    keypad(this->track_win, true);
    srand(seed);

    this->track = new Track(this->max_row, this->max_col - INFO_WIN_WIDTH);
    this->vehicle = new Vehicle(((this->max_col - INFO_WIN_WIDTH) / 2), this->max_row - 1, 3);

    this->track->shift_y(this->max_row);
    this->track->assign_vehicle(this->vehicle);
}

void Game::run(unsigned int seed) {
    int key;

    this->setup(seed);

    do {
        this->track->draw(this->track_win);
        this->info->show_info(this->info_win, this->vehicle->get_speed(), this->vehicle->get_distance(), this->direction_offset);

        wrefresh(this->track_win);
        wrefresh(this->info_win);

        key = wgetch(this->track_win);

        switch (key) {
            case KEY_ENTER:
            case 13:
                // Actually do the turn.
                this->vehicle->shift_x(this->direction_offset);

                if (this->game_over = this->track->collision()) {
                    this->track->draw(this->track_win);
                    wrefresh(this->track_win);
                    break;
                }

                for (int i = 1; i <= this->vehicle->get_speed(); i++){
                    usleep(500000);
                    this->track->shift_y(1);
                    this->track->draw(this->track_win);
                    wrefresh(this->track_win);

                    if (this->game_over = this->track->collision()) {
                        break;
                    }
                }

                this->direction_offset = 0;
                this->speed_inc = 0;

                this->vehicle->track_distance();

                break;

            case KEY_UP:
                this->direction_offset = 0;
                break;

            case KEY_LEFT:
                this->direction_offset = -1;
                break;

            case KEY_RIGHT:
                this->direction_offset = 1;
                break;

            case '-':
                if (this->speed_inc > -1 && this->vehicle->get_speed() > 1) {
                    this->vehicle->speed_inc(-1);
                    this->speed_inc--;
                }
                break;

            case '+':
            case '=':
                if (this->speed_inc < 1) {
                    this->vehicle->speed_inc(1);
                    this->speed_inc++;
                }
                break;

            default:
                break;
        }
    } while (key != 'q' && key != 'Q' && !this->game_over);

    if (this->game_over) {
        werase(this->info_win);
        box(this->info_win, 0, 0);

        this->info->game_over(this->info_win);

        wrefresh(this->info_win);

        wgetch(this->track_win);
    }

    this->cleanup();
}

void Game::cleanup() {
    delwin(this->info_win);
    delwin(this->track_win);
    endwin();
}
