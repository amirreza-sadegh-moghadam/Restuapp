#include"item.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

item::item (int id,string name ,string type, double price,string description,int time,int value,bool exist) : id (id),name(name), type(type), price(price), description(description), time(time), value(value), exist(exist){}
string item::get_name()
{
	return this->name;
}
int item::get_id()
{
	return this->id;
}
string item::get_type()
{
	return this->type;
}
string item::get_description()
{
	return this->description;
}

int item::get_value()
{
	return this->value;
}
int item::get_time()
{
	return this->time;
}
double item::get_price()
{
	return this->price;
}
bool item::get_exist()
{
	return this->exist;
}
void item::set_name(string name)
{
	this->name = name;
}
void item::set_description(string description)
{
	this->description = description;
}
void item::set_value(int value)
{
	this->value = value;
}
void item::set_time(int time)
{
	this->time = time;	
}
void item::set_price(double  price)
{
	this->price = price;
}
void item::set_exist(bool exist)
{
	this->exist = exist;
}
// drink baraye namayesh dorost vishegy motefavetash ba food yany volume ya hakm dorost shode
drink::drink(int id,string name ,string type, double price,string description,int time,int value,bool exist) :
	item(id,name,type,price,description,time,value,exist){}
void drink::get_information()
{
	cout<< "|| name : " <<get_name()<< "| id : " << get_id() << "| price : " << get_price() << "| needed time : "<< get_time() << "| volume : " << get_value() << "| is exist? : ";
	cout<< (get_exist()? " YES " : "NO");
	cout<<"\n"<< "description : "<<"\n"<<get_description()<<"\n";
};
// food baraye namayesh dorost vishegy motefavetash ba drink yany Qauntity tarahy shode
food::food(int id,string name ,string type, double price,string description,int time,int value,bool exist) :
	item(id,name,type,price,description,time,value,exist){}
void food::get_information()
{
	cout<< "|| name : " << get_name()<< "| id : " << get_id() << "| price : " << get_price() << "| needed time : "<< get_time() << "| Quantity: " << get_value() << "| is exist? : ";
	cout<< (get_exist()? " YES " : "NO");
	cout<<"\n"<< "description : "<<"\n"<<get_description()<<"\n";
};