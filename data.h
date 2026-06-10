#ifndef DATA_H
#define DATA_H

#include "sqlite3.h"
#include "rest.h"
#include <vector>
#include <string>
extern "C"{
#include "sqlite3.h"
}
using namespace std;
class data
{
	public:
		data(sqlite3*);
		bool connect();
		void close();
		sqlite3* getDB();
		void create_restaurant();
		void create_customer();
		void create_order();
		void create_item();
		void create_order_item();
		
	private:
		sqlite3* db;
};
class restaurantDAO
{

	public:

    	restaurantDAO(sqlite3* );
   		void addrestaurant(restaurant& );
   		void delete_rest(int id);
    	restaurant* getrestaurant(int );
    	vector<restaurant*> getallrestaurants();
    	void update_name(int id, string name);
		void update_phone(int id, string phone);
		void update_status(int id, bool status);
		void update_description(int id, string description);
		void update_location(int id, string location);
    private:
    
    	sqlite3* db;
};



#endif