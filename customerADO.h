#ifndef CUSTOMERADO_H
#define CUSTOMERADO_H

#include <string>
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
		void update_Debt(int id,double price);
		void update_level(int , string);
		void update_point(int,int);
		void update_copen(int,int);
		void update_last_copen(int,int);
	private:
		sqlite3* db;			
};

class logado
{
	public:
		logado(sqlite3*);
		void addlog(int,string,string,int);
		void show_log();
	private:
		sqlite3* db;
};
#endif