#ifndef PHYS_1_HPP
#define PHYS_1_HPP

// a method for determining various variables around a fall (with(out) air resistance), outputs either time to fall or distance fallen. Dimensions are in flattened 2d.

#include <iostream>
#include <array>
#include <cmath>

class Phys_Object_v1
{
private:

    // container for physics
    const double mass = 1.0; // kg, mass of the object
    const double initial_height = 100.0; // m, initial height of the object

    double time_fallen = 0.0;

    std::array<double, 2> current_position = {0.0, initial_height}; // m, initial position of the object (x, y)
    std::array<double, 2> future_position = {0.0, 0.0}; // for handling object-ground collision
    std::array<double, 2> velocity = {0.0, 0.0}; // m/s, amount of distance the position should be updated with (x, y)

public:

    // some getter functions sorry
    const double getMass()
    {
        return mass;
    };

    std::array<double, 2> getCurrentPosition()
    {
        return current_position;
    };

    double getCurrentPosition(int index)
    {
        return current_position[index];
    };

    std::array<double, 2> getFuturePosition() 
    {
        return future_position;
    };

    double getFuturePosition(int index)
    {
        return future_position[index];
    };

    std::array<double, 2> getVelocity() 
    {
        return velocity;
    };

    double getVelocity(int index) 
    {
        return velocity[index];
    };

    // start of the real deal
    void move(double force_x, double force_y, double delta_time)
    {

        velocity[0] += force_x * delta_time;
        velocity[1] += force_y * delta_time;

        future_position[0] = current_position[0] + velocity[0] * delta_time;
        future_position[1] = current_position[1] + velocity[1] * delta_time;

        if(future_position[1] >= 0)
        {

            current_position[0] = future_position[0];
            current_position[1] = future_position[1];

            time_fallen += delta_time;

        } else {

            time_fallen += current_position[1] / velocity[1];

            std::cout << "program finished!\n";
            std::cout << time_fallen << "s\n";
            std::cin.get();

        }

    };

};

class Phys_Framework
{
private:

    // sequence handler
    // function caller
    // physics constants
    const double g = 9.81; // m/s^2, acceleration due to gravity, remove const later
    const double air_density = 1.225; // kg/m^3, density of air at sea level, remove const later
    const double drag_coefficient = 0.47; // dimensionless, drag coefficient for a sphere, remove const later
    const double cross_sectional_area = 0.1; // m^2, cross-sectional area of the object, remove const later

    const int steps = 1000; // N, remove const later
    const double step_length = 0.05; // s, amount of time that passes after each step, remove const later

public:

    double AirResistanceForce(double density, double drag, double area, double velocity) {

        return 0.5 * density * velocity * velocity * drag * area;
    };

    double GravitationalForce(double mass) 
    {
        return mass * g;
    };

    double getForceX(Phys_Object_v1& object, bool do_air_resistance)
    {
        return 0.0;
    };

    double getForceY(Phys_Object_v1& object, bool do_air_resistance) 
    {   
        
        // set object vars
        double o_mass = object.getMass();
        double friction_y = 0;

        // y-acting forces that work on a falling object: Fgrav, Ffric
        if (do_air_resistance) 
        {   
            friction_y = AirResistanceForce(air_density, drag_coefficient, cross_sectional_area, object.getVelocity(1));
        }

        return -GravitationalForce(o_mass) + friction_y;
    };

    void update(Phys_Object_v1& object, double delta_time, bool do_air_resistance) 
    {

        double force_x = getForceX(object, do_air_resistance);
        double force_y = getForceY(object, do_air_resistance);

        object.move(force_x, force_y, delta_time);

    };


    // presumptions: earth's gravity.
    // print set up parameters

    // step length, amount of steps

    // calculate time to fall or distance fallen?

    // get initial variables: height, mass, velocity, time/distance

    // do air resistance y/n
    // if yes: air resistance factors: 

    // run correct physics engine

};

#endif