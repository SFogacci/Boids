#include "TApplication.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TRootCanvas.h"
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
    std::cout << "Valid commands: \n"
              << "- provide data [p]\n"
              << "- provide the number of boids and use sample parameters [r "
                 "FILE_NAME n_NUMBER]\n"
              << "- quit [q]\n"
              << "Once started, press Escape Key to pause/resume the simulation. \n";

    char cmd;
    int n;
    bd::Parameters parameters;
    std::string filename;
    // std::runtime_error e{"Invalid input."};

    std::cin >> cmd;
    if (cmd == 'p') {
      std::cout << "Insert flock's parameters in the following order: \n"
                << "Cohesion intensity [0,0.1], \n"
                << "Alignment intensity [0,1], \n"
                << "Separation intensity [0,1], \n"
                << "Interaction distance [20, 100], \n"
                << "Separation distance [5, 20], \n"
                << "Number of boids [3, 300]. \n";

      if (!(std::cin >> parameters.c >> parameters.a >> parameters.s >> parameters.d >> parameters.ds >> parameters.n)) {
        throw std::runtime_error("Invalid input type.");
      }
    }

    else if (cmd == 'r' && std::cin >> filename && std::cin >> n) {
      std::ifstream infile{filename};
      if (!infile) {
        throw std::runtime_error{"Impossible to open file."};
      }
      float x;
      std::vector<float> par;
      while (infile >> x) {
        par.push_back(x);
      }
      // if (par.size() != 5) {
      //   throw std::runtime_error{"Incorrect file content."};
      // }
      // std::cout << "Input file read successfully" << '\n';
      bd::Parameters read_parameters(par, n);
      parameters = read_parameters;
    }

    else if (cmd == 'q') {
      return EXIT_SUCCESS;
    } else {
      throw std::runtime_error{"Invalid command.\n"};
      // std::cout << "Bad format, insert a new command\n";
      // std::cin.clear();
    }

    // checks if input type is valid
    if (parameters.c < 0 || parameters.c > 1 || parameters.a < 0 || parameters.a > 1 || parameters.s < 0 || parameters.s > 1 || parameters.d < 0 || parameters.d > 100
        || parameters.ds < 0 || parameters.ds > 20 || parameters.n < 0 || parameters.n > 300) {
      throw std::runtime_error{"Input not in range.\n"}; // if input not in range
    }

    //     break;
    //   }
    // }

    // std::cout << "Remember to press the Escape Key to pause the simulation. \n";
    std::vector<bd::Boid> birds = bd::createPreys(parameters.n);
    bd::Boid predator           = bd::createBird(true);
    bd::Flock flock{birds, parameters};
    bd::gameLoop(flock, predator);

    // drawing graphs of distance and speed over time
    TApplication app("app", 0, nullptr);
    const auto dim{static_cast<Int_t>(bd::windowDimensions.y)};
    TCanvas canvas("Statistics", "Statistics", 0, 0, dim, dim);
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
    TRootCanvas* rc{static_cast<TRootCanvas*>(canvas.GetCanvasImp())};
    rc->Connect("CloseWindow()", "TApplication", gApplication, "Terminate()");
    app.Run();

    // Serve qualcosa per chiudere la simulazione
  } catch (std::exception const& e) {
    std::cerr << e.what() << "\n";
    return EXIT_FAILURE;
  } catch (...) {
    std::cerr << "Caught unknown exception\n";
    return EXIT_FAILURE;
  }
}
