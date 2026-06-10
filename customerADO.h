#ifndef CUSTOMERADO_H
#define CUSTOMERADO_H

#include "customer.h"
#include <vector>
extern "C"{
#include "sqlite3.h"
}
using namespace std;
class customerADO
{
	public:
		customerADO(sqlite3*);
		void addcustomer(customer*);
		customer* getcustomer(int );
		vector<customer*> getallcustomer();
		void delete_customer(int id);
	private:
		sqlite3* db;			
};

#endif