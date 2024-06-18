#include "graphics.hpp"
#include "input.hpp"
#include <stdlib.h>
#include <iostream>
#include <random>
#include <stdexcept>

int main()
{
  try {
    float a, c, d, ds, s;
    size_t n;

    std::cout << "Insert flock's parameters in the following order: \n"
              << "Cohesion intensity [0,1], \n"
              << "Alignment intensity [0,1], \n"
              << "Separation intensity [0,1], \n"
              << "Interaction distance [0, 100], \n"
              << "Separation distance [0, 20], \n"
              << "Number of boids [0, 300]. \n";

    std::runtime_error e{"Invalid input. \n"};

    if (std::cin >> c >> a >> s >> d >> ds
        >> n) { // checks if input type is valid
      if (c < 0 || c > 1 || a < 0 || a > 1 || s < 0 || s > 1 || d < 0 || d > 100
          || ds < 0 || ds > 20 || n > 300) {  // checks range of input (size_t is by def >0).
        throw e; // if input not in range
      }

    } else
      throw e; // if input type not valid

    bd::Parameters parameters{a, c, d, ds, s, n};

    std::vector<bd::Boid> birds = bd::createBirds(parameters.n);
    bd::Flock flock{birds, parameters};
    bd::gameLoop(flock);
  }

  catch (std::runtime_error const& e) {
    std::cerr << e.what() << '\n';
    return EXIT_FAILURE;
  }
}
