#ifndef REGISTER_H
#define REGISTER_H

#include <queue>
#include "Customer.h"

class Register {
private:
    int id;                     //ID of the register
    bool isTraining;            //whether the register is a training register or not
    int remainingTime;          // Time remaining to process the current customer
    std::queue<Customer> line;  // Queue of customers at the register
    
public:
    /**
     * Constructs a Register object.
     *
     * @param[in] id the ID of the register
     * @param[in] isTraining whether the register is a training register
     */
    Register(int id, bool isTraining);

    /**
     * Checks if the register is empty.
     *
     * @return true if the register has no customers and no remaining time, false otherwise
     */
    bool isEmpty() const;

    /**
     * Gets the remeaning number of items of the customer at the front of the queue
     *
     * @return the number of items of the customer at the front of the queue
     */
    int remainingItems() const;

    /**
     * Gets the size of the line (number of customers) at the register.
     *
     * @return the number of customers in the queue
     */
    int getLineSize() const;

    /**
     * Adds a customer to the register's queue.
     *
     * @param[in] customer the customer to add to the queue
     */
    void addCustomer(const Customer& customer);
    
     /**
     * Processes one minute of time at the register.
     *
     * Decrements the remaining time for the current item. If the item is
     * fully processed, the customer's item count is decremented, and the
     * next item or customer is processed.
     */
    void processMinute();

private:
    int processTime(const Customer& customer) const;

    /**
     * Starts processing the next customer in the queue.
     *
     * Initializes the remaining time based on the number of items the
     * customer has and whether the register is a training register.
     */
    void startProcessing();  // Start processing the next customer
};

#endif
