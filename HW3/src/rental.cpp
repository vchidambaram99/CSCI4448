#include <iomanip>
#include "rental.h"

Rental::Rental(Store* s, Customer* c, std::vector<Tool*> t, int d, double co){
	store = s;
	customer = c;
	tools = t;
	daysRemaining = d;
	daysTotal = d;
	cost = co;
}
void Rental::decrementDays(){ daysRemaining--; }
int Rental::getDays(){ return daysRemaining; }
void Rental::returnTools(){ store->returnTools(this); }

std::ostream& operator<<(std::ostream& out, Rental r){
	out<<"Customer: "<<r.customer->getName()<<"\n";
	out<<"Days: "<<r.daysTotal<<", Cost: $"<<std::fixed<<std::setprecision(2)<<r.cost<<"\n";
	out<<"Tools: ";
	for(int i = 0;i<r.tools.size();++i){
		out<<r.tools[i]->getName();
		if(i!=r.tools.size()-1)out<<", ";
	}
	out<<std::endl;
	return out;
}
