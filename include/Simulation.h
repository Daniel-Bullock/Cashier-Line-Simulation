#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include <queue>
#include <string>
#include "Customer.h"
#include "Register.h"

class Simulation {
private:
    std::string inputFile; // The input file containing the simulation data
    std::vector<Register> registers; // A vector of registers used in the simulation, each representing a checkout line.

    /**
     * A priority queue of customers waiting to be processed in the simulation.
     * 
     * The queue prioritizes customers based on their arrival time, the number
     * of items they have, and their customer type (type 'A' taking precedence).
     * This ensures that customers are processed in the correct order as the simulation progresses.
     */
    std::priority_queue<Customer, std::vector<Customer>, std::less<>> customerQueue;

    /**
     * Loads customers and registers from the input file.
     *
     * Reads the input file to initialize the registers and customers
     * for the simulation.
     */
    void loadCustomers();

public:
    /**
     * Constructs a Simulation object.
     *
     * @param[in] inputFile the path to the input file containing simulation data
     */
    Simulation(const std::string& inputFile);

    /**
     * Runs the simulation of the cashier line.
     *
     * Processes each customer in the order they arrive, simulating
     * their checkout process based on the type of register they use.
     */
    void runSimulation();
};

#endif
