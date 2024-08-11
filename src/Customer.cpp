#include "Customer.h"

Customer::Customer(char type, int arrivalTime, int items) : type(type), arrivalTime(arrivalTime), items(items) {}

char Customer::getType() const {
    return type;
}

int Customer::getArrivalTime() const {
    return arrivalTime;
}

int Customer::getItems() const {
    return items;
}

void Customer::processItem() {
    if (items > 0) {
        --items;
    }
}

bool Customer::operator<(const Customer& other) const {
    if (arrivalTime != other.arrivalTime)
        return arrivalTime > other.arrivalTime;
    if (items != other.items)
        return items > other.items;
    return type > other.type; // 'A' should come before 'B'
}
