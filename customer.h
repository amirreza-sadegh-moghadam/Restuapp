#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <vector>
#include <iostream>
#include "item.h"
#include "menu.h"
#include <string>
#include "ML.h"
using namespace std;
class orders
{
	public:
		orders(int,int,int,string,int,double);
		void add_item(item*);
		void del_item(int id);
		void show_order();
		void set_customer_id(int );
		int get_customer_id();
		void set_id(int);
		int get_id();
		int get_date();
		string get_status();
		vector<item*>& get_items();
		double total_price();
		void set_rest_id(int);
		int get_rest_id();
		double get_total();
		void set_total(double);


	private:
		int id;
		int customer_id;
		vector<item*> list;
		int date;
		string status;
		int restaurant_id;
		double total;

};
class customer{
	public:
		customer(int,string,double,int,MembershipLevel*,int,int);
		~customer();
		void set_Debt(double );
		double get_Debt();
		string get_name();
		int get_id();
		void set_id(int);
		void add_order(orders* );
		double total_price();
		int get_point();
		MembershipLevel* get_level();
		void set_level(MembershipLevel* );
		void set_point(int);
		void add_point(int);
		void del_point(int);
		void change_level();
		int get_last_copen();
		void set_last_copen(int);
		void set_copen(int);
		int get_copen();
		bool copen_calculator(int );
		string return_name();
		

	private:
		double Debt;
		int id;
		string name;
		vector<orders*> corders;
		int points;
		MembershipLevel* level;
		int last_copen; 
		int copen;

};



#endif