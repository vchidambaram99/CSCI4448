#ifndef STORE_H
#define STORE_H

#include <vector>
#include <set>
#include "forward.h"
#include "tools.h"
#include "rental.h"
#include "customer.h"

class StoreSimulator;

class Store {
public:
	friend class StoreSimulator;
	Store(int numTools);
	~Store();
	int getNumAvailable(); //number of tools available in store
	Rental* rentTools(Customer* customer, int numTools, int numDays); //create a new rental
	void returnTools(Rental* r); //remove rental from active, make tools available
	void updateRentals(); //decrementDays on all active rentals
private:
	void getToolBack(int i); //helper method to maintain partition
	void giveToolAway(int i); //helper method to maintain partition
	std::vector<Tool*> tools;
	int numAvailable; //splits tools vector into partitions, available [0,numAvailable) and rented [numAvailable,end]
	double profit;
	std::set<Rental*> activeRentals;
	std::vector<Rental*> completedRentals;
};

#endif
