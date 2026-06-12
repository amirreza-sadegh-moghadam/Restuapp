#include "customer.h"
#include <iostream>

using namespace std;
customer::customer(int id,string name,double d) : Debt (d), id(id), name(name){}
customer::~customer()
{
	for ( int i = 0; i<corders.size();i++)
	{
		delete corders[i];
	}
}
// baraye hazf item ha 
void orders::del_item(int id)
{
	for ( int i =0 ; i < list.size();i++)
	{
		if ( list[i]->get_id() == id)
		{
			cout<< " this item deleted bro!"<<endl;
			list.erase(list.begin()+i);
			return;
		}
	}
	cout<< " you already dont have this in your order bro!"<<endl;
}
// etelat item haye sefaresh ra namayesh midahad va sepas mablagh oon ro elam mikonad
void orders::show_order()
{
	cout<< "\n";
	for ( int i = 0; i < list.size();i++)
	{
		list[i]->get_information();
	}
	cout<<"\n"<< "payout : " << total_price()<<endl;
}
void customer::set_Debt(double debt)
{
	this->Debt = debt;
}
string customer::get_name()
{
	return this->name;
}
double customer::get_Debt()
{
	return this->Debt;
}
int customer::get_id()
{
	return this->id;
}
void orders::set_customer_id(int id)
{
	this->customer_id = id;
}
int orders::get_customer_id()
{
	return this->customer_id;
}
void orders::add_item(item* newone)
{
	list.push_back(newone);
}
int orders::get_id()
{
	return this->id;
}
int orders::get_date()
{
	return this->date;
}
string orders::get_status()
{
	return this->status;
}
vector<item*>& orders::get_items()
{
	return this->list;
}
void customer::add_order(orders* o)
{
	this->corders.push_back(o);
}
orders::orders(int id,int customer_id,int date,string status,int restaurant_id) : id(id), customer_id(customer_id),date(date), status(status),restaurant_id(restaurant_id){}
// mablegh koly ke tamam sefaresh hara mohasebeh mikonad
double customer::total_price()
{
	double price = 0;
	for ( int i = 0; i<corders.size();i++)
	{
		price += corders[i]->total_price();
	}
	this->Debt = price;
	return price;
} 
// mablagh yeck sefaresh ro ba jameh mablagh item hash be dast myard
double orders::total_price()
{
	double price = 0;
	for ( int i = 0; i <list.size();i++)
	{
		price += list[i]->get_price();
	}
	return price;
}
void customer::set_id(int id)
{
	this->id = id;
}
void orders::set_id(int id)
{
	this->id = id; 
}
void orders::set_rest_id(int id)
{
	this->restaurant_id = id;
}
int orders::get_rest_id()
{
	return restaurant_id;
}