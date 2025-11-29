#include "vehicle.hpp"


Vehicle::Vehicle(int x, int y, unsigned int speed): x(x), y(y), speed(speed) {}

void Vehicle::getxy(int &x, int &y) {
    x = this->x;
    y = this->y;
}

unsigned int Vehicle::get_speed() {
    return this->speed;
}

unsigned int Vehicle::get_distance() {
    return this->distance;
}

void Vehicle::speed_inc(int inc) {
    this->speed += inc;
}

void Vehicle::shift_x(int offset) {
    this->x += offset;
}

void Vehicle::track_distance() {
    this->distance += this->get_speed();
}
