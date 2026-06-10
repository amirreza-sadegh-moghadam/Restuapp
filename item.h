#ifndef ITEM_H
#define ITEM_H

#include<iostream>
#include<string> 
using namespace std;
class item
{
	public:
		item (int,string,string,double,string,int,int,bool);
		int get_id();
		string get_name();
		string get_type();
		string get_description();
		virtual void get_information() = 0;
		int get_value();
		int get_time();
		bool get_exist();
		double get_price();
		void set_name(string);
		void set_description(string);
		void set_value(int);
		void set_time(int);
		void set_price(double);
		void set_exist(bool);
	private:
		int id;
		string name;
		string description;
		double price;
		string type;
		int value;
		bool exist;
		int time; // toye tozih project neveshte shode bood in mitavand tanha baraye ghaza bashad ama noshidany ha ham mitavanand zaman tolid dashte bashand  pass koly kardanesh  behtar ast    
		// har chand hanoozam va betoore koly bedoone chand rikhty mitavan class ra peyade kard ama khobe choon gofte shode estefade mikonim
};
class drink : public item
{
	public:
		drink( int,string, string,double,string,int,int,bool);
		void get_information()override;
};
class food:public item
{
	public:
		food( int,string, string,double,string,int,int,bool);
		void get_information()override;
};


#endif