#ifndef VEHICLE_HPP
#define VEHICLE_HPP

class Vehicle {
  private:
    unsigned int speed, distance = 0;
    int x, y;
  public:
    Vehicle(int x, int y, unsigned int speed);

    void getxy(int &x, int &y);
    void speed_inc(int inc);
    void shift_x(int offset);
    void track_distance();

    unsigned int get_speed();
    unsigned int get_distance();
};

#endif // VEHICLE_HPP
