#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <iostream>
#include "item.h"
#include "menu.h"
#include <string>

using namespace std;
class orders
{
	public:
		orders(int,int,int,string);
		void add_item(item*);
		void del_item(int id);
		void show_order();
		void set_customer_id(int );
		int get_customer_id();
		int get_id();
		int get_date();
		string get_status();
		vector<item*>& get_items();
		double total_price();

	private:
		int id;
		int customer_id;
		vector<item*> list;
		int date;
		string status;

};
class customer{
	public:
		customer(int,string,double);
		~customer();
		void set_Debt(double );
		double get_Debt();
		string get_name();
		int get_id();
		void set_id(int);
		void add_order(orders* );
		double total_price();


	private:
		double Debt;
		int id;
		string name;
		vector<orders*> corders;
};



#endif