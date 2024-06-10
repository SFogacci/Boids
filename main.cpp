
#include "graphics.hpp"
#include "input.hpp"

int main()
{
  bd::Parameters parameters = bd::getParameters();
  std::vector<bd::Boid> birds = bd::createBirds(bd::getSize());
  bd::Flock flock{birds, parameters};
  bd::gameLoop(flock);
  return 0;
}
