#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "graphics.hpp"
#include "input.hpp"
#include "statistics.hpp"
#include <stdlib.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>

int main()
{
  try {
    char cmd;
    std::size_t n;
    bd::Parameters parameters;
    std::string filename;

    std::cout << "Valid commands: \n"
              << "- provide data [p]\n"
              << "- provide the number of boids and use sample parameters [r "
                 "FILE_NAME n_NUMBER]\n"
              << "- quit [q]\n";

    std::runtime_error e{"Invalid input. \n"};

    while (std::cin >> cmd) {
      if (cmd == 'p') {
        std::cout << "Insert flock's parameters in the following order: \n"
                  << "- Cohesion intensity [0,1], \n"
                  << "- Alignment intensity [0,1], \n"
                  << "- Separation intensity [0,1], \n"
                  << "- Interaction distance [0, 100], \n"
                  << "- Separation distance [0, 20], \n"
                  << "- Number of boids [0, 300]. \n";

        if (std::cin >> parameters.c >> parameters.a >> parameters.s
            >> parameters.d >> parameters.ds >> parameters.n) {
        } else
          throw e; // if input type not valid
      }

      else if (cmd == 'r' && std::cin >> filename && std::cin >> n) {
        std::ifstream infile{filename};
        if (!infile) {
          throw std::runtime_error{"Impossible to open file!"};
        }
        float x;
        std::vector<float> par;
        while (infile >> x) {
          par.push_back(x);
        }
        if (par.size() != 5) {
          throw std::runtime_error{"Incorrect file content!"};
        }
        std::cout << "Input file read successfully" << '\n';
        bd::Parameters read_parameters(par, n);
        parameters = read_parameters;
      }

      else if (cmd == 'q') {
        return EXIT_SUCCESS;
      } else {
        std::cout << "Bad format, insert a new command\n";
        std::cin.clear();
      }

      // checks if input type is valid
      if (parameters.c < 0 || parameters.c > 1 || parameters.a < 0
          || parameters.a > 1 || parameters.s < 0 || parameters.s > 1
          || parameters.d < 0 || parameters.d > 100 || parameters.ds < 0
          || parameters.ds > 20
          || parameters.n > 300) { // checks range of input (std::size_t is
                                   // by def >0).
        throw e;                   // if input not in range
      }

      break;
    }

    std::vector<bd::Boid> birds = bd::createBirds(parameters.n);
    bd::Boid predator           = bd::createPredator();
    bd::Flock flock{birds, parameters};
    bd::gameLoop(flock, predator);

    // drawing graphs of distance and speed over time
    TApplication app("app", 0, nullptr);
    TCanvas canvas("Statistics", "Statistics", 0, 0, 800, 600);
    canvas.Divide(2, 2);

    canvas.cd(1);
    TGraph meanSpeeds("statistics.txt", "%lg %lg");
    bd::drawGraph(meanSpeeds, "Mean speed");

    canvas.cd(2);
    TGraph sigmaSpeeds("statistics.txt", "%lg %*lg %lg");
    bd::drawGraph(sigmaSpeeds, "Std deviation for speed");

    canvas.cd(3);
    TGraph meanDistances("statistics.txt", "%lg %*lg %*lg %lg");
    bd::drawGraph(meanDistances, "Mean distance");

    canvas.cd(4);
    TGraph sigmaDistances("statistics.txt", "%lg %*lg %*lg %*lg %lg");
    bd::drawGraph(sigmaDistances, "Std deviation for distance");
    
    canvas.Modified();
    canvas.Update();
    canvas.Print(bd::fileName().c_str());
    app.Run();

  } catch (std::exception const& e) {
    std::cerr << e.what() << "'\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
