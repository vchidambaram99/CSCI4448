/*
Valliappan Chidambaram
CSCI4448 HW3
2/16/19
*/

#include <iostream>
#include <iomanip>
#include <vector>
#include <cassert>
#include <cstdlib>
#include "store.h"

class StoreSimulator {
public:
	StoreSimulator(int numTools, int numCustomers) : s(numTools) {
		assert(numCustomers>=3 && "Must have 3 or more customers");
		customers = std::vector<Customer*>(numCustomers); //1 customer of each type, rest are random
		customers[0] = CustomerFactory::makeCustomer<CasualCustomer>();
		customers[1] = CustomerFactory::makeCustomer<RegularCustomer>();
		customers[2] = CustomerFactory::makeCustomer<BusinessCustomer>();
		for(int i = 3;i<customers.size();++i) customers[i] = CustomerFactory::randomCustomer();
	}
	~StoreSimulator(){
		//customers are dynamically allocated and must be deleted
		for(int i = 0;i<customers.size();++i) delete customers[i];
	}
	void simulate(int numDays){
		for(int i = 0;i<numDays;++i){
			s.updateRentals(); //update the days left on each rental
			for(int j = 0;j<customers.size();++j){
				customers[j]->returnTools(); //have customers return rentals that are over
				if(customers[j]->willGoToStore(&s))customers[j]->rentTools(&s); //rent more tools randomly
			}
		}
		std::cout<<"The store made $"<<std::fixed<<std::setprecision(2)<<s.profit<<".\n";
		std::cout<<"The store currently has the following tools: \n";
		for(int i = 0;i<s.numAvailable;++i){
			std::cout<<s.tools[i]->getName()<<"\n";
		}
		std::cout<<"\nThe store completed the following rentals: \n";
		for(int i = 0;i<s.completedRentals.size();++i){
			std::cout<<"Completed Rental #"<<i<<":\n"<<*s.completedRentals[i]<<"\n";
		}
		std::cout<<"The following rentals are currently active: \n";
		int count = 0;
		for(auto it = s.activeRentals.begin();it!=s.activeRentals.end();++it){
			std::cout<<"Active Rental #"<<count++<<":\n"<<*(*it)<<"\n";
		}
		std::cout<<std::endl;
	}
private:
	Store s;
	std::vector<Customer*> customers;
};

int main(int argc, char* argv[]){
	srand(time(0)); //seeds the PRNG for all the random stuff later
	StoreSimulator ss(20,10);
	ss.simulate(35);
	return 0;
}
