#include <iostream>
#include <string>
#include "Simulation.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    // Create Simulation object and start the simulation
    Simulation simulation(argv[1]);
    simulation.runSimulation();

    return 0;
}
