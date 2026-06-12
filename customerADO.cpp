#include "customerADO.h"
#include <iostream>
#include <vector>
#include "sqlite3.h"
#include "orderADO.h"
#include <string>
using namespace std;
customerADO::customerADO(sqlite3* db)
{
	this->db = db;
}
void customerADO::addcustomer(customer* c)
{
	string sql =
	string("INSERT INTO CUSTOMER ")+
    "(name,Debt) "
    "VALUES(" +
     "'" + c->get_name() + "'," +

    to_string(c->get_Debt()) + 
    ");";
	char* errMsg = nullptr;
    int rc = sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        nullptr
    );
    int id = sqlite3_last_insert_rowid(db);
    c->set_id(id);
}
// ba gereftan id customer ra tahvil mi dahad
customer* customerADO::getcustomer(int id)
{
	string sql =
	"SELECT * FROM CUSTOMER WHERE id = " + to_string(id )+";";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr);
	if(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id =
        sqlite3_column_int(stmt,0);
        string name =
        (char*)sqlite3_column_text(stmt,1);
        double Debt = 
        sqlite3_column_double(stmt,2);
        orderDAO orderado(db);
    	vector<orders*> orders = orderado.getCustomerOrders(id);
        customer* s = new customer(id,name,Debt);
        for ( int i = 0; i< orders.size();i++)
        {
        	s->add_order(orders[i]);
		}
        sqlite3_finalize(stmt);
        return s;
	}
	sqlite3_finalize(stmt);
	return nullptr;
}
// tamam customer haye barnameh ra tahvil midahad
vector<customer*> customerADO::getallcustomer()
{
	vector<customer*> customers;
	string sql =
	"SELECT * FROM CUSTOMER";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr);
	orderDAO orderado(db);
	while(sqlite3_step(stmt) == SQLITE_ROW)
	{
		int id =
        sqlite3_column_int(stmt,0);
        string name =
        (char*)sqlite3_column_text(stmt,1);
        double Debt = 
        sqlite3_column_double(stmt,2);
        vector<orders*> orders = orderado.getCustomerOrders(id);
        customer* s = new customer(id,name,Debt);
        for (int i = 0; i<orders.size();i++)
        {
        	s->add_order(orders[i]);
		}
		customers.push_back(s);	
	}
	sqlite3_finalize(stmt);
	return customers;
}
void customerADO::delete_customer(int id)
{
	orderDAO orderado(db);
	vector<orders*> os =
	orderado.getCustomerOrders(id);
	for(int i=0;i<os.size();i++)
	{
    	orderado.delete_order(os[i]->get_id());
    	delete os[i];
	}
	string sqll=
	"DELETE FROM CUSTOMER WHERE id = " +  to_string(id) + ";";
	sqlite3_exec(db,sqll.c_str(),nullptr,nullptr,nullptr);
}
// meghdar bedehy ra taghir midahad
void customerADO::update_Debt(int id,double price )
{
	string sql =
		"UPDATE CUSTOMER SET Debt = Debt + " + to_string(price) +" WHERE id = " + to_string(id);

	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}