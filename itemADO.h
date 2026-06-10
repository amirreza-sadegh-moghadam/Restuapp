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
	private:
		sqlite3* db;
};

#endif