#include"rest.h"
#include<iostream>
using namespace std;
restaurant::restaurant(menu& list, int id, int time,bool status ,string location ,string phone ,string description,string name) :
	list(list), id(id), time(time), status(status), location(location), phone(phone), description(description),name (name){}
void restaurant::set_id(int id)
{
	this->id = id;
}
string restaurant::get_name()
{
	return name;
}
void restaurant::set_time(int time )
{
	this->time = time;
}
void restaurant::set_status(bool status)
{
	this->status = status;
}
void restaurant::set_location(string location)
{
	this->location = location;
}
void restaurant::set_phone(string phone)
{
	this->phone = phone;
}
void restaurant::set_description(string description)
{
	this->description = description;
}
int restaurant::get_id()
{
	return this->id;
}
int restaurant::get_time()
{
	return this->time;
}
bool restaurant::get_status()
{
	return this->status;
}
string restaurant::get_location()
{
	return this->location;
}
string restaurant::get_phone()
{
	return this->phone;
}
string restaurant::get_description()
{
	return this->description;
}
void restaurant::show_menu()
{
	list.show_menu();
}
void restaurant::add_menu(item* newone)
{
    this->list.add_item(newone);
}
void restaurant::del_menu(item* newone)
{
	this->list.delete_item(newone->get_id());
}
item* restaurant::find_id(int id)
{
	return list.find_id(id);
}
void restaurant::set_name(string name)
{
	this->name = name;
}
void restaurant::show_information()
{
	cout<< "||" << " name :  " << name << "| id "<< id << "| phone : " << phone << "| description : " << description << "| location : " 
	<< location;
	if ( status == 1)
	{
		cout<< "|status : On ";
	}
	if (status == 0)
	{
		cout <<"|status : Off";
	}
}