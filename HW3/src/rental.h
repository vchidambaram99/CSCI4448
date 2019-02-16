#ifndef RENTAL_H
#define RENTAL_H

#include <vector>
#include <iostream>
#include "forward.h"
#include "tools.h"
#include "store.h"

class Rental {
	friend class Customer; //Customer should have access to all tools
	friend class Store; //Store should have access to cost, and other info
	Rental(Store* s, Customer* c, std::vector<Tool*> t, int d, double co);
	void decrementDays(); //update daysRemaining
	int getDays(); //get daysRemaining
	void returnTools(); //return tools to store
	friend std::ostream& operator<<(std::ostream& out, Rental r); //prints rental (used in StoreSimulator)
private:
	Store* store;
	Customer* customer;
	std::vector<Tool*> tools;
	int daysRemaining; //days remaining until tools need to be returned
	int daysTotal; //total days for rental, not updated
	double cost;
};

#endif
