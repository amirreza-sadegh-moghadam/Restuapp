#ifndef MENU_H
#define MENU_H


#include<vector>
#include"item.h"
class menu
{
	public:
		menu();
		~menu();
		void add_item(item*);
		void delete_item(int id);
		void show_menu();
		item* find_id(int);
	private:
		vector<item*> items;	
};
#endif