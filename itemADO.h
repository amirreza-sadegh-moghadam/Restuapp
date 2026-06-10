#ifndef ITEMDAO_H
#define ITEMDAO_H

#include "sqlite3.h"
#include "item.h"
#include <vector>

using namespace std;

class itemDAO
{
	public:
		itemDAO(sqlite3*);
		void add_item(item*,int);
		item* get_item(int);
		vector<item*> getrestaurantitem(int);
		void delete_item(int);
		void update_name(int,string);
		void update_price(int,double);
		void update_description(int,string);
		void update_time(int,int);
		void update_value(int,int);
		void update_exist(int,bool);
	private:
		sqlite3* db;
};

#endif