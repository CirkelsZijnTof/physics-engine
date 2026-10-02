#ifndef PHYS_1_HPP
#define PHYS_1_HPP

// a method for determining various variables around a fall (with(out) air resistance), outputs either time to fall or distance fallen. Dimensions are in flattened 2d.

#include <iostream>
#include <array>
#include <cmath>

class Phys_Object_v1
{
private:

    void getVariable(auto& variable)
    {   
        std::cin >> variable;
    };

public:

    // container for physics
    double mass = 1.0; // kg, mass of the object

    double drag_coefficient = 0.47; // dimensionless, drag coefficient for a sphere
    double cross_sectional_area = 0.1; // m^2, cross-sectional area of the object, remove const later

    double time_fallen = 0.0;

    double height = 0.0;

    std::array<double, 2> current_position = {0.0, 0.0}; // m, initial position of the object (x, y)
    std::array<double, 2> future_position = {0.0, 0.0}; // for handling object-ground collision
    std::array<double, 2> velocity = {0.0, 0.0}; // m/s, amount of distance the position should be updated with (x, y)

    // temporary physics object flags
    bool has_landed = false;

    // a few setters for convenience sorry
    void setPosition(std::array<double, 2> position)
    {
        current_position = position;
    };

    void setPosition(double value, int index)
    {
        current_position[index] = value;
    };

    void applyStartUpLogic()
    {
        setPosition(height, 1);
    };

    void setEnvironmentVariables() 
    {  

        std::cout << "\nContinuing to Object setup.\n";

        std::cout << "How heavy is the object? (default = " << mass << "kg)\n";
        getVariable(mass);

        std::cout << "What is the object's drag coefficient? (default = " << drag_coefficient << ")\n";
        getVariable(drag_coefficient);

        std::cout << "What is the cross-sectional area of the object? (default = " << cross_sectional_area << " m^2)\n";
        getVariable(cross_sectional_area);

        std::cout << "What is the height at which the object starts? (default = " << height << "m)\n";
        getVariable(height);

        applyStartUpLogic();

    };

    // start of the real deal
    void applyForces(double force_x, double force_y, double delta_time)
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

            has_landed = true;

        }

    };

};

class Phys_Framework
{
private:

    // sequence handler
    // function caller
    // physics constants
    bool do_medium_resistance = false;

    double g = 9.81; // m/s^2, acceleration due to gravity
    double medium_density = 1.225; // kg/m^3, density of the medium. Based on air at sea level

    void getVariable(auto& variable)
    {   

        std::cin >> variable;
        std::cout << "\n";
    };

public:

    int steps = 1000; // N, remove const later
    double step_time = 0.01; // s, amount of time that passes after each step, remove const later
    bool do_infinite_run = false;

    void applyStartUpLogic()
    {
        if(steps == 0)
        {
            do_infinite_run = true;
            steps = 1;
        };
    };

    void setEnvironmentVariables() 
    {  

        std::cout << "There's no user input validation. Please re-enter the default value exactly.\n";
        std::cout << "If you mis-enter, the program will crash, so beware.\n\n";

        std::cout << "How many steps should the program run for? (set to 0 to run until ground collision)";
        getVariable(steps);

        std::cout << "How long should each step take to complete? (default = 0.01)";
        getVariable(step_time);

        std::cout << "What should be the gravitational force? (default = 9.81 m/s^2)";
        getVariable(g);

        std::cout << "What should be the density of the medium through which the object is moving? (default = 1.225 kg/m^3)";
        getVariable(medium_density);

        applyStartUpLogic();

    };

    void updateStepCounter()
    {
        if(!do_infinite_run)
        {
            steps--;
        }
    };

    double MediumResistanceForce(double density, double drag, double area, double velocity) {

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
        double object_m = object.mass;
        double friction_y = 0;

        // y-acting forces that work on a falling object: Fgrav, Ffric
        if (do_air_resistance) 
        {   
            friction_y = MediumResistanceForce(medium_density, object.drag_coefficient, object.cross_sectional_area, object.velocity[1]);
        }

        return -GravitationalForce(object_m) + friction_y;
    };

    void move(Phys_Object_v1& object) 
    {

        double force_x = getForceX(object, do_medium_resistance);
        double force_y = getForceY(object, do_medium_resistance);

        object.applyForces(force_x, force_y, step_time);

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