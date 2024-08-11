#include "Register.h"

Register::Register(int id, bool isTraining) : id(id), isTraining(isTraining), remainingTime(0) {}

bool Register::isEmpty() const {
    return line.empty() && remainingTime == 0;
}

int Register::remainingItems() const {
    if (line.empty()) return 0;
    return line.front().getItems();
}

int Register::getLineSize() const {
    return line.size();
}

void Register::addCustomer(const Customer& customer) {
    line.push(customer);
    if (remainingTime == 0) {
        startProcessing();
    }
}

void Register::processMinute() {
    if (remainingTime > 0) {
        remainingTime--;
        
        // If enough time has passed to process an item, decrement the item count
        if (remainingTime % (isTraining ? 2 : 1) == 0) {
            Customer& currentCustomer = line.front();
            currentCustomer.processItem();
        }

        if (remainingTime == 0 && !line.empty()) {
            line.pop();
            if (!line.empty()) {
                startProcessing();
            }
        }
    }
}

int Register::processTime(const Customer& customer) const {
    return isTraining ? customer.getItems() * 2 : customer.getItems();
}

void Register::startProcessing() {
    if (!line.empty()) {
        remainingTime = processTime(line.front());
    }
}
