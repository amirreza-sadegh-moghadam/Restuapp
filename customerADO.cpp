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
    "(name,Debt,points,level,last_copen,copen) "
    "VALUES(" +
     "'" + c->get_name() + "'," +

    to_string(c->get_Debt()) + "," + to_string(c->get_point())  +",'"+ c->get_level()->get_level() + "'," + to_string(c->get_last_copen())+ "," + to_string(c->get_copen()) +
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
        int points = 
        sqlite3_column_int(stmt,3);
        string names =
        (char*)sqlite3_column_text(stmt,4);
        MembershipLevel* level = nullptr;
        int last_copen =
        sqlite3_column_int(stmt,5);
        int copen = 
        sqlite3_column_int(stmt,6);
        if ( names == "Normal")
        {
        	level = new NormalLevel();
		}
		if ( names == "Silver")
		{
			level = new SilverLevel();
		}
		if ( names == "Gold")
		{
			level = new GoldLevel();
		}
		if ( names == "VIP")
		{
			level = new VIPLevel();
		}
        orderDAO orderado(db);
    	vector<orders*> orders = orderado.getCustomerOrders(id);
        customer* s = new customer(id,name,Debt,points, level,last_copen,copen);
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
        int points = 
        sqlite3_column_int(stmt,3);
        string names =
        (char*)sqlite3_column_text(stmt,4);
        MembershipLevel* level = nullptr;
        int last_copen =
        sqlite3_column_int(stmt,5);
        int copen = 
        sqlite3_column_int(stmt,6);
        if ( names == "Normal")
        {
        	level = new NormalLevel();
		}
		if ( names == "Silver")
		{
			level = new SilverLevel();
		}
		if ( names == "Gold")
		{
			level = new GoldLevel();
		}
		if ( names == "VIP")
		{
			level = new VIPLevel();
		}
		vector<orders*> orders = orderado.getCustomerOrders(id);
        customer* s = new customer(id,name,Debt,points,level,last_copen,copen);
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
void customerADO::update_level(int id,string level)
{
	string sql =
		"UPDATE CUSTOMER SET Level =  '"+ level + "' WHERE id = " + to_string(id);

	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}
void customerADO::update_point(int id,int point )
{
	string sql =
		"UPDATE CUSTOMER SET points =  " + to_string(point) +" WHERE id = " + to_string(id);

	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}
void customerADO::update_copen(int id,int copen )
{
	string sql =
		"UPDATE CUSTOMER SET copen = " + to_string(copen) +" WHERE id = " + to_string(id);

	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}
void customerADO::update_last_copen(int id, int copen)
{
	string sql =
	"UPDATE CUSTOMER SET last_copen = " + to_string(copen) +" WHERE id = " + to_string(id);

	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}

void logado::addlog(int customer_id, string oldlevel, string newlevel, int date)
{
    string sql =
    string("INSERT INTO LEVEL_LOG ") +
    "(customer_id, old, new, date) "
    "VALUES(" +
    to_string(customer_id) + "," +
    "'" + oldlevel + "'," +
    "'" + newlevel + "'," +
    to_string(date) +
    ");";
    sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);

}
// choon serfa mikhastim chop konim taghirat roe , ba yeck tabeh ke chop kone kar roe jameh kardim
void logado::show_log()
{
    string sql =
    "SELECT customer_id, old, new, date "
    "FROM LEVEL_LOG "
    "ORDER BY date DESC;";
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int customer_id =
        sqlite3_column_int(stmt,0);
        string old =
        (char*)sqlite3_column_text(stmt,1);
        string newl =
        (char*)sqlite3_column_text(stmt,2);

        int date =
        sqlite3_column_int(stmt,3);
	
        cout << "Customer ID : " << customer_id
             << " | " << old
             << " -> " << newl
             << " | Date : " << date << endl;
    }
    
    sqlite3_finalize(stmt);
}
logado::logado(sqlite3* db)
{
	this-> db = db;
}