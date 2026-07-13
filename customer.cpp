#include "customer.h"
#include <iostream>

using namespace std;
customer::customer(int id,string name,double d,int point,MembershipLevel* level,int last_copen,int copen) : Debt (d), id(id), name(name), points(point), level(level),last_copen(last_copen),copen(copen)
{}
customer::~customer()
{
	for ( int i = 0; i<corders.size();i++)
	{
		delete corders[i];
	}
	delete level;
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
	cout<< " sum of prices : " << total_price();
	cout<<"\n"<< "payout (discount) : " << total<<endl;
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
orders::orders(int id,int customer_id,int date,string status,int restaurant_id,double total) : id(id), customer_id(customer_id),date(date), status(status),restaurant_id(restaurant_id), total(total){}
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
int customer::get_point()
{
	return this->points;
}

MembershipLevel* customer::get_level()
{
	return this->level;
}
void customer::set_level(MembershipLevel* level)
{
	this->level = level;
}
void customer::set_point(int points)
{
	this->points = points;
	change_level();
}
void customer::add_point(int point)
{
	// Dar matn project oomadahe ke admin bayad betoone dar soorat adam failiat sateh roe beyare paeen, hala man alave bar oone kahat outomatic kardamesh  ke dar sorat faliat mojadad
	// dobare be sateh ghably bargarde!, choon tavabeh add , del roe seda mizanim
	points += point;
	change_level();
}
void customer::del_point(int point)
{
	points -= point ;
	change_level();
}
void customer::change_level()
{
	if (  points < 100  && level->get_level() != "Normal")
	{
		delete level;
		level = new NormalLevel();
		cout << " now your level is Normal";
	}	
	else if (points > 99 && points < 300 && level->get_level() != "Silver")
	{
		delete level;
		level = new SilverLevel();
		cout<< " now your level is Silver";
		
	}
	else if ( points > 299&& points < 700  && level->get_level() != "Gold")
	{
		delete level;
		level = new GoldLevel();
		cout << " now your level is Gold";
	}
	else if ( points > 699&& level->get_level() != "VIP")
	{
		delete level;
		level = new VIPLevel();
		cout << " now your level is VIP";
	}
}
double orders::get_total()
{
	return total;
}
void orders::set_total(double total)
{
	this->total = total;
}
int customer::get_last_copen()
{
	return last_copen;
}
void customer::set_last_copen(int last_copen)
{
	this->last_copen = last_copen;
}
void customer::set_copen(int copen)
{
	this->copen = copen;
}
int customer::get_copen()
{
	return copen;
}
bool customer::copen_calculator(int date)
{

	// baraye moghayese mah ha ke copen ro bedim behesh
	if ( (date/ 100) %100 != (last_copen/100) %100)
	{
		this->copen += level->get_copen(); 
		last_copen = date;
		cout<<"you get " <<level->get_copen()<<"copen"<<endl;
		return true;

	}
	return false;
}
string customer:: return_name()
{
	if ( copen > 3)
		return "Copen Guy";
	else if ( Debt > 500)
		return "Top Debtor";
	else if ( Debt == 0)
		return "Nice guy";
	else if ( name.length() > 40)
	 	return" long name guy!";
	else if ( points > 1000)
		return "Awesome guy!";
	else
		return " normal guy!";
	
}