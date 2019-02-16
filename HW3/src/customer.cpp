#include <sstream>
#include <type_traits>
#include "customer.h"

Customer::Customer(){}
Customer::~Customer(){}
void Customer::setName(std::string n){ name = n; }
std::string Customer::getName(){ return name; }
bool Customer::willGoToStore(Store* s){ return canGoToStore(s)&&(std::rand()&1); }
void Customer::returnTools(){
	for(auto it = rentals.begin();it!=rentals.end();){
		if((*it)->getDays()<=0){ //if rental due
			(*it)->returnTools();
			toolsRented -= (*it)->tools.size();
			it = rentals.erase(it); //remove from customer's rentals
		}else ++it;
	}
}

CasualCustomer::CasualCustomer(){}
CasualCustomer::CasualCustomer(std::string n){ name = n; }
CasualCustomer::~CasualCustomer(){}
bool CasualCustomer::canGoToStore(Store* s){
	return toolsRented<3 && s->getNumAvailable()>0;
}
void CasualCustomer::rentTools(Store* s){
	int rentable = std::min(std::min(3-toolsRented,s->getNumAvailable()),2);
	int toRent = std::rand()%rentable+1; //determine num tools to rent
	toolsRented += toRent;
	rentals.insert(s->rentTools(this,toRent,std::rand()%2+1)); //rent and add rental to set
}

RegularCustomer::RegularCustomer(){}
RegularCustomer::RegularCustomer(std::string n){ name = n; }
RegularCustomer::~RegularCustomer(){}
bool RegularCustomer::canGoToStore(Store* s){
	return toolsRented<3 && s->getNumAvailable()>0;
}
void RegularCustomer::rentTools(Store* s){
	int rentable = std::min(3-toolsRented,s->getNumAvailable());
	int toRent = std::rand()%rentable+1; //determine num tools to rent
	toolsRented += toRent;
	rentals.insert(s->rentTools(this,toRent,std::rand()%3+3)); //rent and add rental to set
}

BusinessCustomer::BusinessCustomer(){}
BusinessCustomer::BusinessCustomer(std::string n){ name = n; }
BusinessCustomer::~BusinessCustomer(){}
bool BusinessCustomer::canGoToStore(Store* s){
	return toolsRented==0 && s->getNumAvailable()>=3;
}
void BusinessCustomer::rentTools(Store* s){
	toolsRented += 3;
	rentals.insert(s->rentTools(this,3,7)); //rent and add rental to set
}

Customer* CustomerFactory::randomCustomer(){
	switch(rand()%3){
	case 0:
		return makeCustomer<CasualCustomer>();
	case 1:
		return makeCustomer<RegularCustomer>();
	case 2:
		return makeCustomer<BusinessCustomer>();
	}
	return 0;
}
template <typename T> T* CustomerFactory::makeCustomer(){
	std::stringstream ss;
	//determine type with compile time if, and set name appropriately
	if(std::is_same<T,CasualCustomer>::value){
		ss<<"Casual "<<numCasual++;
	}else if(std::is_same<T,RegularCustomer>::value){
		ss<<"Regular "<<numRegular++;
	}else if(std::is_same<T,BusinessCustomer>::value){
		ss<<"Business "<<numBusiness++;
	}
	return new T(ss.str());
}
int CustomerFactory::numCasual = 0;
int CustomerFactory::numRegular = 0;
int CustomerFactory::numBusiness = 0;
