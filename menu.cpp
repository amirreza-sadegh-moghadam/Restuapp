#include "menu.h" 
using namespace std;

menu::menu()
{
}
menu::~menu()
{
    for (int i = 0; i < items.size(); i++)
    {
        delete items[i];
    }
}
void menu::add_item(item* newone)
{
	items.push_back(newone);
}
void menu::delete_item(int id)
{
	for ( int i=0; i<items.size();i++)
	{
		if ( items[i]->get_id()== id)
		{
			cout<< items[i]->get_name() << " deleted from menu!";
			delete items[i];
			items.erase(items.begin() + i );
			return;
		}
	}
}
void menu::show_menu()
{
	cout<<"\n";
	for ( int i=0;i<items.size();i++)
	{
		items[i]->get_information();
	}
}

item* menu::find_id(int id)
{
	int i;
	for (  i=0; i<items.size();i++)
	{
		if ( items[i]->get_id()== id)
		{
			return items[i];
		}
	}
	return nullptr;
}