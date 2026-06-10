#include <iostream>
#include "item.h"
#include "menu.h"
#include "customer.h"
#include "rest.h"
#include "sqlite3.h"
#include "customerADO.h"
#include "itemADO.h"
#include "data.h"
#include "orderADO.h"
#include "restmg.h"
#include <limits>

using namespace std;

void customer_panel(sqlite3* db)
{
	customerADO customerado(db);
	restaurantDAO restdao(db);
	orderDAO orderado(db);

	cout << "\n1. im a old user" << endl;
	cout << "2. im a new one" << endl;
	int answer;
	cin >> answer;
	while ( answer != 1 && answer != 2)
	{
		cout << "this input is invalid sweety!, please input 1 or 2" << endl;
		cin >> answer;
	}

	customer* moshtary = nullptr;

	if ( answer == 2)
	{
		cout << "enter your name bro: ";
		string name;
		cin >> name;
		
		customer* newcustomer = new customer(0, name, 0);
		customerado.addcustomer(newcustomer);
		cout << "welcome here! now you can login with your id:" << endl;
		cout<<"BTW this is your id : " << newcustomer->get_id();
		delete newcustomer;
	}

	cout << "enter your id: ";
	int id;
	cin >> id;
	moshtary = customerado.getcustomer(id);
	while ( moshtary == nullptr )
	{
		cout << "we dont have this id bro!, try it again: ";
		cin >> id;
		moshtary = customerado.getcustomer(id);
	}
	cout << "welcome back " << moshtary->get_name() << "!" << endl;
	int answer2;
	cout << "\nwhat you gonna do now?" << endl;
	cout << "1. New order" << endl;
	cout << "2. show me old orders!" << endl;
	cout << "3. exit" << endl;
	cin >> answer2;
	while ( answer2 != 1 && answer2 != 2 && answer2 != 3)
	{
		cout << "this input is invalid sweety!, please input 1 or 2 or 3" << endl;
		cin >> answer2;
	}

	if ( answer2 == 1)
	{
		vector<restaurant*> rests = restdao.getallrestaurants();
		cout << "\nplease choose your restaurant :" << endl;
		for ( int i = 0; i < rests.size(); i++)
		{
			rests[i]->show_information();
			cout << "\n";
		}
		cout << "enter restaurant id: ";
		int resid;
		cin >> resid;

		restaurant* choose = nullptr;
		for ( int i = 0; i < rests.size(); i++)
		{
			if ( rests[i]->get_id() == resid)
			{
				choose = rests[i];
			}
		}
		while ( choose == nullptr || choose->get_status() == false)
		{
			cout << "we dont have this  restaurant bro!, try it again: ";
			cin >> resid;
			for ( int i = 0; i < rests.size(); i++)
			{
				if ( rests[i]->get_id() == resid)
				{
					choose = rests[i];
				}
			}
		}

		cout << "\n MENU:" << endl;
		choose->show_menu();

		orders* newone = new orders(0, moshtary->get_id(), 14040506, "dar hal amade sazi");

		int answer3;
		cout << "\n1. add item" << endl;
		cout << "2. remove item" << endl;
		cout << "3. show my order" << endl;
		cout << "4. confirm order!" << endl;
		cin >> answer3;

		while ( answer3 != 4)
		{
			if ( answer3 == 1)
			{
				cout << "choose the item with input the id: ";
				int itemid;
				cin >> itemid;
				item* found = choose->find_id(itemid);
				while ( found == nullptr)
				{
					cout << "we dont have this bro, try again: ";
					cin >> itemid;
					found = choose->find_id(itemid);
				}
				newone->add_item(found);
				cout << found->get_name() << " added to your order bro!" << "Total Price : "<<newone->total_price()<<endl;
				
			}
			else if ( answer3 == 2)
			{
				cout << "enter the id's of item who you want to remove: ";
				int itemid;
				cin >> itemid;
				newone->del_item(itemid);
				cout<<"Deleted succsfuelly total price : "<< newone->total_price();
			}
			else if ( answer3 == 3)
			{
				cout << "\nyour order : " << endl;
				newone->show_order();
			}
			else
			{
				cout << "this input is invalid sweety!, please input 1 or 2 or 3 or 4" << endl;
			}

			cout << "\n1. add item" << endl;
			cout << "2. remove item" << endl;
			cout << "3. show my order" << endl;
			cout << "4. confirm order!" << endl;
			cin >> answer3;
		}

		orderado.addOrder(newone);
		cout << "order confirmed! we are preparing your food\n just wait now!" << endl;

		delete newone;
		for ( int i = 0; i < rests.size(); i++) 
		{
			delete rests[i];
		};
	}

	if ( answer2 == 2)
	{
		vector<orders*> m_orders = orderado.getCustomerOrders(moshtary->get_id());
		cout << "\n your orders:" << endl;
		for ( int i = 0; i < m_orders.size(); i++)
		{
			cout << "order id: " << m_orders[i]->get_id()
				 << " | date: " << m_orders[i]->get_date()
				 << " | status: " << m_orders[i]->get_status() << endl;
			m_orders[i]->show_order();
			cout << "----------------------------" << endl;
		}
		for ( int i = 0; i < m_orders.size(); i++) 
		{
			delete m_orders[i];
		}
	}

	delete moshtary;
}
void show_rs(sqlite3 * db)
{
	restaurantDAO restdao(db);
	vector<restaurant*> rests = restdao.getallrestaurants();
	for ( int i = 0; i < rests.size(); i++)
	{
		cout <<rests[i]->get_name() << " id : "<<rests[i]->get_id();
		cout << "\n";
	}
	for ( int i = 0; i < rests.size(); i++) 
	{
			delete rests[i];
	}
}

void restaurant_manager_panel(sqlite3* db)
{
	restaurantDAO restdao(db);
	itemDAO itemdao(db);
	orderDAO orderado(db);
	customerADO customerado(db);

	cout << "enter your restaurant id: ";
	
	int resid;
	vector<restaurant*> rests = restdao.getallrestaurants();
	show_rs(db);
	cin >> resid;
	restaurant* myrest = restdao.getrestaurant(resid);
	while ( myrest == nullptr)
	{
		cout << "we dont have this id, i guess you should try it again: ";
		cin >> resid;
		myrest = restdao.getrestaurant(resid);
	}
	cout << "welcome " << myrest->get_name() << " manager!" << endl;

	int answer;
	cout << "\nwhat you want to do?" << endl;
	cout << "1. show restaurant info" << endl;
	cout << "2. show menu" << endl;
	cout << "3. add item to menu" << endl;
	cout << "4. delete item from menu" << endl;
	cout << "5. show orders" << endl;
	cout << "6. exit" << endl;
	cin >> answer;

	while ( answer != 6)
	{
		if ( answer == 1)
		{
			myrest->show_information();
			cout << "\n";
		}
		else if ( answer == 2)
		{
			myrest->show_menu();
		}
		else if ( answer == 3)
		{
			cout << "enter name: ";
			cin.ignore();
			string name;
			getline(cin,name);
			cout << "enter type (food/drink): ";
			string type;
			cin.ignore();
			getline(cin,type);
			while ( type != "food" && type !="drink")
			{
				cout<<" invalid input, please just input word 'food' or 'drink'";
				getline(cin,type);
			}
			cout << "enter price: ";
			double price;
			cin >> price;
			while ( cin.fail())
			{
					cout<<"please input numbers!";
					cin.clear();
  					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> price;
			}
			cout << "enter description: ";
			string description;
			getline(cin,description);
			getline(cin,description);
			cout << "enter time ( minute prefer): ";
			int time;
			cin >> time;
			while ( cin.fail())
			{
					cout<<"please input numbers!";
					cin.clear();
  					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> time;
					
			}
			cout << "enter value: ";
			int value;
			cin >> value;
				while ( cin.fail())
				{
					cout<<"please input numbers!";
					cin.clear();
  					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> value;
					
				}
			cout << "is exist? (1/0): 1.YES 2.NO ";
			int exist;
			while (true)
			{
    			cin >> exist;

    			if (cin.fail())
    			{
        			cout << "invalid input (only 1 or 2)\n";
       				cin.clear();
        			cin.ignore(numeric_limits<streamsize>::max(), '\n');
        			continue;
    			}

		   if (exist == 1 || exist == 2)
       		break;
			cout << "invalid input (only 1 or 2)\n";
			}

			item* newitem = nullptr;
			if ( type == "food")
				newitem = new food( 0,name, type, price, description, time, value, exist);
			else
				newitem = new drink(0,name, type, price, description, time, value, exist);

			itemdao.add_item(newitem, resid);
			cout << name << " added to menu bro!" << endl;
			myrest = restdao.getrestaurant(resid);
			delete newitem;
		}
		else if ( answer == 4)
		{
			int itemid;
			myrest->show_menu();
			cout << "enter item id to delete :  "<<;
			cin >> itemid;
			itemdao.delete_item(itemid);
			myrest = restdao.getrestaurant(resid);
			cout << "item deleted bro!" << endl;
			
		}
		else if ( answer == 5)
		{
			cout << "enter customer id to see their orders (or 0 for all): "<<endl;
			vector<customer*> customers = customerado.getallcustomer();
			for ( int i =0; i <customers.size();i++)
			{
				cout<< customers[i]->get_name() << " id : " << customers[i]->get_id()<<endl;
			}
			int c_id;
			cin >> c_id;
			if ( c_id != 0)
			{
				vector<orders*> orders = orderado.getCustomerOrders(c_id);
				for ( int i = 0; i < orders.size(); i++)
				{
					cout << "order id: " << orders[i]->get_id()
						 << " | status: " << orders[i]->get_status() << endl;
					orders[i]->show_order();
					cout << "---------------------" << endl;
				}
				for ( int i = 0; i < orders.size(); i++) 
				{
					delete orders[i];
				}
			}
		}
		else
		{
			cout << "this input is invalid " << endl;
		}

		cout << "\n1. show restaurant info" << endl;
		cout << "2. show menu" << endl;
		cout << "3. add item to menu" << endl;
		cout << "4. delete item from menu" << endl;
		cout << "5. show orders" << endl;
		cout << "6. exit" << endl;
		cin >> answer;
	}

	delete myrest;
}

void program_manager_panel(sqlite3* db)
{
	restaurantDAO restdao(db);
	customerADO customerado(db);

	int answer;
	cout << "\nWhat you want now?" << endl;
	cout << "1. amount of sell (all orders count)" << endl;
	cout << "2. add new restaurant" << endl;
	cout << "3. turning on the restaurant" << endl;
	cout << "4. turning off the restaurant" << endl;
	cout << "5. show all users" << endl;
	cout << "6. exit" << endl;
	cin >> answer;

	while ( answer != 6)
	{
		if ( answer == 1)
		{
			vector<restaurant*> rests = restdao.getallrestaurants();
			cout << "we have " << rests.size() << " restaurants in system " << endl;
			for ( int i = 0; i < rests.size(); i++) 
			{
				rests[i]->show_information();
			}
			for ( int i = 0; i < rests.size(); i++) 
			{
				delete rests[i];
			}
		}
		else if ( answer == 2)
		{
			cout << "enter name: ";
			string name;
			cin >> name;
			cout << "enter location: ";
			string loc;
			cin >> loc;
			cout << "enter phone: ";
			string phone;
			cin >> phone;
			cout << "enter description: ";
			string description;
			cin >> description;
			cout << "enter prepare time (minutes): ";
			int time;
			cin >> time;

			menu* m = new menu();
			restaurant* new_r = new restaurant(*m, 0, time, true, loc, phone, description, name);
			restdao.addrestaurant(*new_r);
			cout << name << " added to system :)" << endl;
			delete new_r;
		}
		else if ( answer == 3)
		{
			cout << "enter restaurant id to turn on: "<<endl;
			show_rs(db);
			int id;
			cin >> id;
			restaurant* r = restdao.getrestaurant(id);
			if ( r == nullptr)
			{
				cout << "we dont have this id bro!" << endl;
			}
			else
			{
				r->set_status(true);
				cout << r->get_name() << " is now on bro!" << endl;
			}
			delete r;
		}
		else if ( answer == 4)
		{
			cout << "enter restaurant id to turn off: "<<endl;
			show_rs(db);
			int id;
			cin >> id;
			restaurant* r = restdao.getrestaurant(id);
			if ( r == nullptr)
			{
				cout << "we dont have this id bro!" << endl;
			}
			else
			{
				r->set_status(false);
				cout << r->get_name() << " is now OFF bro!" << endl;
			}
			delete r;
		}
		else if ( answer == 5)
		{
			vector<customer*> customers = customerado.getallcustomer();
			cout << "\nall users:" << endl;
			for ( int i = 0; i < customers.size(); i++)
			{
				cout << "id: " << customers[i]->get_id()
					 << " | name: " << customers[i]->get_name()
					 << " | debt: " << customers[i]->get_Debt() << endl;
			}
			for ( int i = 0; i < customers.size(); i++) 
			{
			delete customers[i];
			}
		}
		else
		{
			cout << "this input is invalid sweety!" << endl;
		}

		cout << "\n1. amount of sell (all orders count)" << endl;
		cout << "2. add new restaurant" << endl;
		cout << "3. turning on the restaurant" << endl;
		cout << "4. turning off the restaurant" << endl;
		cout << "5. show all users" << endl;
		cout << "6. exit" << endl;
		cin >> answer;
	}
}

int main()
{
	sqlite3* mydb;
	data db(mydb);
	db.connect();
	mydb = db.getDB();
	db.create_restaurant();
	db.create_item();
	db.create_customer();
	db.create_order();
	db.create_order_item();

	cout << "welcome to restuapp!" << "\n";
	cout << "Who you are?" << endl;
	cout << "1.Customer" << endl;
	cout << "2.Restaurant Manager" << endl;
	cout << "3.Program Manager" << endl;

	int answer;
	cin >> answer;
	while ( answer != 1 && answer != 2 && answer != 3)
	{
		cout << "this input is invalid , please input 1 or 2 or 3 ;)" << endl;
		cin >> answer;
	}

	if ( answer == 1)
	{
		customer_panel(mydb);
	}
	if ( answer == 2)
	{
		restaurant_manager_panel(mydb);
	}
	if ( answer == 3)
	{
		program_manager_panel(mydb);
	}

	db.close();
	return 0;
}