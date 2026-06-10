#ifndef  RESTMG_h
#define RESTMG_h

#include "rest.h"
#include<string>

using namespace std;

class res_manager
{
	public:
		res_manager(int,string);
		restaurant* choose(int id);
		void show_all();
		string get_name();
		int get_id();
		restaurant* search_restaurant(int id);
	private:
		vector<restaurant*> restaurants;
		int id;
		string name;
		
};
#endif