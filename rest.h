#ifndef REST_H
#define REST_H
#include "menu.h"
#include <string>
using namespace std;
class restaurant
{
	public:
		restaurant(menu&,int ,int ,bool,string,string,string,string);
		// setters
		void set_id(int);
		void set_time(int);
		void set_status(bool);
		void set_location(string);
		void set_phone(string);
		void set_description(string);
		void set_name(string);
		//getters
		int get_id();
		int get_time();
		string get_name();
		bool get_status();
		string get_location();
		string get_phone();
		string get_description();
		void show_menu();
		item* find_id(int id);
		void add_menu(item*);
		void del_menu(item*);
		void show_information();
	private:
		menu& list;
		int id;
		int time;
		bool status;
		string location;
		string phone;
		string description;
		string name;
		
};

#endif 