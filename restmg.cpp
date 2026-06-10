#include"restmg.h"
#include"rest.h"
#include "string.h"
using namespace std;
res_manager::res_manager(int id,string name) : id(id),name(name){}
string res_manager::get_name()
{
	return this->name;
}
restaurant* res_manager::search_restaurant(int id)
{
	for ( int i = 0 ; i  < restaurants.size();i++)
	{
		if ( restaurants[i]->get_id() == id)
		{
			return restaurants[i];
		}
	}
	return nullptr;
}
restaurant* res_manager::choose(int id)
{
	cout<< " please enter the restaurant you want to work with it";
	this->show_all();
	int answer;
	cin >> answer;
	while ( search_restaurant(id) == nullptr)
	{
		cout<<"you dont have the restaurant with this id, please check the id and resend it!"<< endl;
		cin >> answer;
	}
	return search_restaurant(answer);
}

void res_manager::show_all()
{
	for ( int i = 0 ; i < restaurants.size();i++)
	{
		restaurants[i]->show_information();
	}
}
int res_manager::get_id()
{
	return this->id;
}