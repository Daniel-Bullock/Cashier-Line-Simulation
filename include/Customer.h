#ifndef CUSTOMER_H
#define CUSTOMER_H

/**
 * Represents a customer in the cashier line simulation.
 */
class Customer {
private:
    char type;       // The type of customer ('A' or 'B')
    int arrivalTime; // The arrival time of the customer in minutes
    int items;       // The number of items the customer currently has

public:
    /**
     * Constructs a Customer object.
     *
     * @param[in] type the type of customer ('A' or 'B')
     * @param[in] arrivalTime the time the customer arrives at the register
     * @param[in] items the number of items the customer has
     */
    Customer(char type, int arrivalTime, int items);

    /**
     * Gets the type of the customer.
     *
     * @return the type of customer ('A' or 'B')
     */
    char getType() const;

    /**
     * Gets the arrival time of the customer.
     *
     * @return the arrival time of the customer in minutes
     */
    int getArrivalTime() const;

    /**
     * Gets the number of items the customer has.
     *
     * @return the number of items the customer currently has
     */
    int getItems() const;

    /**
     * Decrements the number of items the customer has by one.
     */
    void processItem();

    /**
     * Compares two customers based on their priority in a queue.
     *
     * Customers are compared first by arrival time, then by the number
     * of items, and finally by customer type (with 'A' taking precedence).
     *
     * @param[in] other the other customer to compare against
     * @return true if this customer has lower priority than the other, false otherwise
     */
    bool operator<(const Customer& other) const;
};

#endif // CUSTOMER_H
