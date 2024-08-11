#include "Simulation.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <queue>

Simulation::Simulation(const std::string& inputFile) : inputFile(inputFile) {
    loadCustomers();
}

void Simulation::loadCustomers() {
    std::ifstream file(inputFile);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << inputFile << std::endl;
        exit(1);
    }

    int numRegisters;
    file >> numRegisters;

    if (file.fail() || numRegisters <= 0) {
        std::cerr << "Invalid number of registers in input file." << std::endl;
        exit(1);
    }

    registers.reserve(numRegisters);
    for (int i = 1; i <= numRegisters; ++i) {
        registers.emplace_back(i, i == numRegisters);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line.find_first_not_of(' ') == std::string::npos) {
            continue;
        }

        std::istringstream iss(line);
        char type;
        int arrivalTime, items;

        if (!(iss >> type >> arrivalTime >> items)) {
            std::cerr << "Invalid format in input file: " << line << std::endl;
            exit(1);
        }

        if (!isalpha(type) || (type != 'A' && type != 'B')) {
            std::cerr << "Invalid customer type in input file: " << type << std::endl;
            exit(1);
        }

        if (arrivalTime < 0 || items <= 0) {
            std::cerr << "Arrival time and items must be positive integers: " << line << std::endl;
            exit(1);
        }

        customerQueue.push(Customer(type, arrivalTime, items));
    }

    file.close();
}

void Simulation::runSimulation() {
    int currentTime = 0;

    while (!customerQueue.empty() || std::any_of(registers.begin(), registers.end(), [](const Register& reg) { return !reg.isEmpty(); })) {
        // Add customers who have arrived by the current time
        while (!customerQueue.empty() && customerQueue.top().getArrivalTime() <= currentTime) {
            Customer customer = customerQueue.top();
            customerQueue.pop();

            Register* chosenRegister = nullptr;
            if (customer.getType() == 'A') {
                chosenRegister = &*std::min_element(registers.begin(), registers.end(), [](const Register& a, const Register& b) {
                    return a.getLineSize() < b.getLineSize();
                });
            } else if (customer.getType() == 'B') {
                chosenRegister = &*std::min_element(registers.begin(), registers.end(), [](const Register& a, const Register& b) {
                    return a.remainingItems() < b.remainingItems();
                });
            }

            chosenRegister->addCustomer(customer);
        }

        // Process a minute of time
        for (auto& reg : registers) {
            reg.processMinute();
        }

        // Increment time
        currentTime++;
    }

    std::cout << "Finished at: t=" << currentTime << " minutes" << std::endl;
}
