#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <set>
#include "forward.h"
#include "tools.h"
#include "rental.h"
#include "store.h"

class Customer {
public:
	Customer();
	virtual ~Customer();
	void setName(std::string n);
	std::string getName();
	virtual bool canGoToStore(Store* s) = 0; //determine if this customer can go to the specified store
	bool willGoToStore(Store* s); //randomly select if they will go to the store
	virtual void rentTools(Store* s) = 0; //randomly rent tools in accordance with customer type
	void returnTools(); //if any rentals are due, return them
protected:
	std::string name;
	std::set<Rental*> rentals;
	int toolsRented = 0;
};

class CasualCustomer : public Customer {
public:
	CasualCustomer();
	CasualCustomer(std::string n);
	~CasualCustomer();
	bool canGoToStore(Store* s);
	void rentTools(Store* s);
};

class RegularCustomer : public Customer {
public:
	RegularCustomer();
	RegularCustomer(std::string n);
	~RegularCustomer();
	bool canGoToStore(Store* s);
	void rentTools(Store* s);
};

class BusinessCustomer : public Customer {
public:
	BusinessCustomer();
	BusinessCustomer(std::string n);
	~BusinessCustomer();
	bool canGoToStore(Store* s);
	void rentTools(Store* s);
};

class CustomerFactory { //essentially the same as ToolFactory, but for Customers
public:
	static Customer* randomCustomer();
	template <typename T> static T* makeCustomer();
private:
	static int numCasual;
	static int numRegular;
	static int numBusiness;
};

#endif
