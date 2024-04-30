#ifndef BOID_HPP
#define BOID_HPP

#include <SFML/Graphics.hpp>
 namespace bd{
struct Position{};
struct Velocity{};
class Boid{
    private:
    Position position;
    Velocity velocity;

    public:
    Boid(Position const& p,Velocity const&v ): position{p}, velocity{v} {}
    Position getPosition() const;
    void setPosition();
    Velocity getVelocity() const;
    void setVelocity();
};
 }
#endif BOIDS_HPP