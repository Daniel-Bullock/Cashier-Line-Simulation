//File for some unit and integration tests

#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <cstdlib> // For system()
#include "Customer.h"
#include "Simulation.h"
#include "Register.h"

// Global variables to track the number of passed and failed tests
int testsPassed = 0;
int testsFailed = 0;

// A simple assertEqual function to check if two values are equal
template <typename T>
void assertEqual(const T& actual, const T& expected, const std::string& testName) {
    if (actual == expected) {
        std::cout << "[PASS] " << testName << std::endl;
        testsPassed++;
    } else {
        std::cout << "[FAIL] " << testName << " - Expected: " << expected << ", but got: " << actual << std::endl;
        testsFailed++;
    }
}

// Function to print the summary of tests
void printTestSummary() {
    std::cout << "\nTest Summary:\n";
    std::cout << "Passed: " << testsPassed << "\n";
    std::cout << "Failed: " << testsFailed << "\n";
}

// Unit Test: Customer class
void testCustomerInPriorityQueue() {
    std::priority_queue<Customer> pq;
    pq.push(Customer('A', 5, 10));
    pq.push(Customer('B', 5, 10));
    assertEqual(pq.top().getType(), 'A', "Priority Queue Customer Comparison Test");
}

// Unit Test: Register class
void testRegister() {
    Register reg(1, false);
    reg.addCustomer(Customer('A', 0, 10));
    for (int i = 0; i < 5; ++i) {
        reg.processMinute();
    }
    assertEqual(reg.remainingItems(), 5, "Regular Register Remaining Items After 5 Minutes");

    Register regTraining(2, true);  // Training register
    Customer c2('A', 0, 10); // 10 items
    regTraining.addCustomer(c2);
    regTraining.processMinute(); // 1st minute, no items processed yet
    regTraining.processMinute(); // 2nd minute, 1 item processed
    assertEqual(regTraining.remainingItems(), 9, "Training Register: Remaining Items After 2 Minutes");

}

// Integration Test: Running main.exe with test case files
void runTestCase(const std::string& testFilePath, const std::string& expectedOutput) {
    std::string command = "main.exe " + testFilePath + " > testcases/output.txt 2>&1";
    system(command.c_str());

    std::ifstream resultFile("testcases/output.txt");
    std::string actualOutput((std::istreambuf_iterator<char>(resultFile)), std::istreambuf_iterator<char>());
    resultFile.close();

    assertEqual(actualOutput, expectedOutput, "Test case: " + testFilePath);
}

void runAllTestCases() {
    std::vector<std::pair<std::string, std::string>> testCases = {
        {"testcases/test1.txt", "Finished at: t=7 minutes\n"},
        {"testcases/test2.txt", "Finished at: t=13 minutes\n"},
        {"testcases/test3.txt", "Finished at: t=6 minutes\n"},
        {"testcases/test4.txt", "Finished at: t=9 minutes\n"},
        {"testcases/test5.txt", "Finished at: t=11 minutes\n"},
        {"testcases/test6.txt", "Invalid number of registers in input file.\n"}, //blank file
    };

    for (const auto& testCase : testCases) {
        runTestCase(testCase.first, testCase.second);
    }
}

// Main function to run all tests
int main() {
    std::cout << "Running Unit Tests...\n\n";

    testCustomerInPriorityQueue();
    testRegister();

    std::cout << "\nRunning Integration Tests...\n\n";

    runAllTestCases();

    printTestSummary();

    return 0;
}
