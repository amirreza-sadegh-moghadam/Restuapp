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
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
#include <limits>
#include <iostream>
using namespace std;

template <typename T>
T int_eror(const string& errorMsg) {
    T value;
    cin >> value;
    while (cin.fail())
	{
        cout << errorMsg << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> value;
    }
    return value;
}
void pause()
{
	cout<< " please enter to countinue!";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}

int get_current_date()
{
    time_t now = time(nullptr);
    tm tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y%m%d");
    return stoi(oss.str());
}
void customer_panel(sqlite3* db)
{
	 system("cls");
	customerADO customerado(db);
	restaurantDAO restdao(db);
	orderDAO orderado(db);

	cout << "\n1. im a old user" << endl;
	cout << "2. im a new one" << endl;
	int answer;
	answer = int_eror<int>("this input is invalid sweety!, please input 1 or 2" );
	while ( answer != 1 && answer != 2)
	{
		cout << "this input is invalid !, please input 1 or 2" << endl;
		answer = int_eror<int>("this input is invalid , please input 1 or 2" );
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
		cout<<"BTW this is your id : " << newcustomer->get_id()<<endl;
		delete newcustomer;
	}

	cout << "enter your id: ";
	int id;
	id = int_eror<int>("this input is invalid , please input number" );
	moshtary = customerado.getcustomer(id);
	while ( moshtary == nullptr )
	{
		cout << "we dont have this id bro!, try it again: ";
		id = int_eror<int>("this input is invalid , please input numbers" );
		moshtary = customerado.getcustomer(id);
	}
	while (true) 
	{
	system("cls");
	cout << "welcome back " << moshtary->get_name() << "!" << endl;
	int answer2;
	cout << "\nwhat you gonna do now?" << endl;
	cout << "1. New order" << endl;
	cout << "2. show me old orders!" << endl;
	cout << "3. exit" << endl;
	answer2 = int_eror<int>("this input is invalid , please input 1 or 2 or 3" );
	while ( answer2 != 1 && answer2 != 2 && answer2 != 3)
	{
		answer2 = int_eror<int>("this input is invalid , please input 1 or 2 or 3" );
	}

	if ( answer2 == 1)
	{
		vector<restaurant*> rests = restdao.getallrestaurants();
		system("cls");
		cout << "\nplease choose your restaurant : " << endl;
		for ( int i = 0; i < rests.size(); i++)
		{
			if(rests[i]->get_status() == true )
			{
				rests[i]->show_information();
				cout << "\n";
			}
		}
		cout << "enter restaurant id: ";
		int resid;
		resid = int_eror<int>("this input is invalid , please input number" );
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
			resid = int_eror<int>("this input is invalid , please input number" );
			for ( int i = 0; i < rests.size(); i++)
			{
				if ( rests[i]->get_id() == resid)
				{
					choose = rests[i];
				}
			}
		}
		system("cls");
		// tarikh bar asas tarikh dasgah karbar tanzim misheh!
		int date = get_current_date();
		orders* newone = new orders(0, moshtary->get_id(), date, "dar hal amade sazi",choose->get_id());

		int answer3;
		cout << "\n MENU:" << endl;
		choose->show_menu();
		cout << "\n1. add item" << endl;
		cout << "2. remove item" << endl;
		cout << "3. show my order" << endl;
		cout << "4. confirm order!" << endl;
		answer3 = int_eror<int>("this input is invalid , please input 1 or 2 or 3 or 4" );

		while ( answer3 != 4)
		{
			if ( answer3 == 1)
			{
				cout << "choose the item with input the id: ";
				int itemid;
				itemid = int_eror<int>("this input is invalid , please input number" );
				item* found = choose->find_id(itemid);
				while ( found == nullptr)
				{
					cout << "we dont have this bro, try again: ";
					itemid = int_eror<int>("this input is invalid , please input number" );
					found = choose->find_id(itemid);
				}
				newone->add_item(found);
				cout << found->get_name() << " added to your order bro!" << "Total Price : "<<newone->total_price()<<endl;
				
			}
			else if ( answer3 == 2)
			{
				cout << "enter the id's of item who you want to remove: ";
				int itemid;
				itemid = int_eror<int>("this input is invalid , please input number" );
				newone->del_item(itemid);
				cout<<" total price : "<< newone->total_price();
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
			pause();
			cout << "\n MENU:" << endl;
			choose->show_menu();
			cout << "\n1. add item" << endl;
			cout << "2. remove item" << endl;
			cout << "3. show my order" << endl;
			cout << "4. confirm order!" << endl;
			answer3 = int_eror<int>("this input is invalid , please input 1 or 2 or 3 or 4" );
		}

		orderado.addOrder(newone);
		system("cls");
		cout<< " Order ID : " << newone->get_id() << " status : " << newone->get_status();
		pause();
		customerado.update_Debt(moshtary->get_id(),newone->total_price());
		delete newone;
		for ( int i = 0; i < rests.size(); i++) 
		{
			delete rests[i];
		}
	}

	else if ( answer2 == 2)
	{
		vector<orders*> m_orders = orderado.getCustomerOrders(moshtary->get_id());
		 system("cls");
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
	else if( answer2 == 3)
	{
		break;
	}
	else
	{
		cout<<"invalid input";
	}
	pause();
}
	delete moshtary;
}
void show_rs(sqlite3 * db)
{
	restaurantDAO restdao(db);
	vector<restaurant*> rests = restdao.getallrestaurants();
	for ( int i = 0; i < rests.size(); i++)
	{
		cout <<rests[i]->get_name() << "| id : "<<rests[i]->get_id();
		cout << "\n";
	}
	for ( int i = 0; i < rests.size(); i++) 
	{
			delete rests[i];
	}
}

void restaurant_manager_panel(sqlite3* db)
{
	 system("cls");
	restaurantDAO restdao(db);
	itemDAO itemdao(db);
	orderDAO orderado(db);
	customerADO customerado(db);
	
	int resid;
	vector<restaurant*> rests = restdao.getallrestaurants();
	show_rs(db);
	cout << "enter your restaurant id: "<<endl;
	resid = int_eror<int>("this input is invalid sweety!, please input number" );
	restaurant* myrest = restdao.getrestaurant(resid);
	while ( myrest == nullptr)
	{
		cout << "we dont have this id, i guess you should try it again: ";
		resid = int_eror<int>("this input is invalid sweety!, please input number" );
		myrest = restdao.getrestaurant(resid);
	}
	int rest_id = myrest->get_id();
	cout << "welcome " << myrest->get_name() << " manager!" << endl;

	int answer;
	cout << "\nwhat you want to do?" << endl;
	cout << "1. show restaurant info" << endl;
	cout << "2. show menu" << endl;
	cout << "3. add item to menu" << endl;
	cout << "4. delete item from menu" << endl;
	cout << "5. show orders" << endl;
	cout<< "6.change restaurant info"<<endl;
	cout<<"7.change menu items"<<endl;
	cout<<"8.change the status of orders"<<endl;
	cout << "9. exit" << endl;
	answer = int_eror<int>("this input is invalid !, please input number" );

	while ( answer != 9)
	{
		if ( answer == 1)
		{
			system("cls");
			myrest->show_information();
			cout << "\n";
		}
		else if ( answer == 2)
		{
			system("cls");
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
			getline(cin,type);
			while ( type != "food" && type !="drink")
			{
				cout<<" invalid input, please just input word 'food' or 'drink' : "<<endl;
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
			cin.ignore();
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
			cout << "is exist? (1/0): 1.YES 0.NO ";
			int exist;
			while (true)
			{
    			cin >> exist;

    			if (cin.fail())
    			{
        			cout << "invalid input (only 1 or 0)\n"<<endl;
       				cin.clear();
        			cin.ignore(numeric_limits<streamsize>::max(), '\n');
        			continue;
    			}
		   if (exist == 1 || exist == 0)
       		break;
			cout << "invalid input (only 1 or 0)\n";
	
			}
			
		 	item* newitem = nullptr;
			if ( type == "food")
				newitem = new food( 0,name, type, price, description, time, value, exist);
			else
				newitem = new drink(0,name, type, price, description, time, value, exist);

			itemdao.add_item(newitem, resid);
			cout << name << " added to menu bro!" << endl;
			delete myrest;
			myrest = restdao.getrestaurant(resid);
			delete newitem;
		}
		else if ( answer == 4)
		{
			int itemid;
			myrest->show_menu();
			cout << "enter item id to delete :  ";
			itemid = int_eror<int>("this input is invalid sweety!, please input number" );
			while ( myrest->find_id(itemid) == nullptr)
			{
				itemid = int_eror<int>("this input is invalid sweety!, please input number" );
			}
			itemdao.delete_item(itemid);
			delete myrest;
			myrest = restdao.getrestaurant(resid);
			cout << "item deleted bro!" << endl;
		}
		else if ( answer == 5)
		{
			system("cls");	
			vector<customer*> customers = customerado.getallcustomer();
			for ( int i =0; i <customers.size();i++)
			{
				cout<< customers[i]->get_name() << " id : " << customers[i]->get_id()<<endl;
			}
			cout<<" input the id : ";
			int c_id;
			 c_id =	int_eror<int>("this input is invalid sweety!, please input number" );
			if ( c_id != 0)
			{
				vector<orders*> orders = orderado.getCustomerOrdersR(c_id,myrest->get_id());
				for ( int i = 0; i < orders.size(); i++)
				{
					cout << "order id: " << orders[i]->get_id()
						 << "|order date:" << orders[i]->get_date()
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
		else if ( answer == 6)
		{
			system("cls");
			int javab;
			while ( true)
			{
				myrest->show_information();
				cout<< "What would you like to change?"<<endl;
				cout<< "1.name"<<endl;
				cout<<"2.phone"<<endl;
				cout<<"3.status"<<endl;
				cout<<"4.description"<<endl;
				cout<<"5.location"<<endl;
				cout<<"6.exist"<<endl;
				javab = int_eror<int>("this input is invalid sweety!, please input number" );
				if ( javab == 1)
				{
					string name;
					cout << " input new name : "<< endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,name);
					restdao.update_name(rest_id,name);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( javab == 2)
				{
					string phone;
					cout << "input new phone number : "<< endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,phone);
					restdao.update_phone(rest_id,phone);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( javab == 3)
				{
					bool status;
					cout << " input new status of restaurant ( 1.ON / 0.OFF)"<<endl;
					while (true)
					{
    					cin >> status;

    				if (cin.fail())
    				{
        				cout << "invalid input (only 1 or 0)\n"<<endl;
       					cin.clear();
        				cin.ignore(numeric_limits<streamsize>::max(), '\n');
        				continue;
    				}

		   			if (status == 1 || status == 0)
       					break;
					cout << "invalid input (only 1 or 0)\n";
					}
					restdao.update_status(rest_id,status);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
					
				}
				else if ( javab == 4)
				{
					string description;
					cout << "input new description"<<endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,description);
					restdao.update_description(rest_id,description);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( javab == 5)
				{
					string location;
					cout<< "input new location "<<endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,location);
					restdao.update_location(rest_id,location);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				
				else if ( javab == 6)
					break;
				else
				{
					cout << " invalid input!";
				}
				pause();
			
			}
		}
		else if (answer == 7)
		{
			while ( true)
			{
				int khoste;
				myrest->show_menu();
				cout<< "0. exit"<<endl;
				cout<< "choose the item by id : ";
				int item_id;
				 item_id = int_eror<int>("this input is invalid sweety!, please input number" );
				while ( myrest->find_id(item_id) == nullptr && item_id != 0)
				{
					cout<< " we dont have this item!, try again"<<endl;
					 item_id = int_eror<int>("this input is invalid sweety!, please input number" );
				}
				if (item_id !=0)
				{
				cout<< "what would you like to change? "<<endl;
				cout<<"1.name"<<endl;
				cout<<"2.price"<<endl;
				cout<<"3.description"<<endl;
				cout<<"4.time"<<endl;
				cout<<"5.value"<<endl;
				cout<<"6.exist"<<endl;
				cout<<"7.exit"<<endl;
				khoste = int_eror<int>("this input is invalid sweety!, please input number" );
				}
				if ( item_id ==0)
				{
					khoste = 7;
				}
				if ( khoste == 1)
				{
					
					string name2;
					cout<<" input the new name : ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,name2);
					itemdao.update_name(item_id,name2);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( khoste == 2)
				{
					double price2;
					cout<< "input the new price : ";
					cin >> price2;
					while ( cin.fail())
					{
						cout<<"please input numbers!";
						cin.clear();
  						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin >> price2;
					}
					itemdao.update_price(item_id,price2);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( khoste == 3)
				{
					string description2;
					cout<<" input the new description : ";
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,description2);
					itemdao.update_description(item_id,description2);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( khoste == 4)
				{
					int time2;
					cout<< "input the new time  : ";
					cin >> time2;
					while ( cin.fail())
					{
						cout<<"please input numbers!";
						cin.clear();
  						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin >> time2;
					}
					itemdao.update_time(item_id,time2);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( khoste == 5)
				{
					double value2;
					cout<< "input the new value : ";
					cin >> value2;
					while ( cin.fail())
					{
						cout<<"please input numbers!";
						cin.clear();
  						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cin >> value2;
					}
					itemdao.update_value(item_id,value2);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
				}
				else if ( khoste == 6)
				{
					bool exist;
					cout << " input new exist of item ( 1.YES / 0.OFF)"<<endl;
					while (true)
					{
    					cin >> exist;

    				if (cin.fail())
    				{
        				cout << "invalid input (only 1 or 0)\n"<<endl;
       					cin.clear();
        				cin.ignore(numeric_limits<streamsize>::max(), '\n');
        				continue;
    				}

		   			if (exist == 1 || exist == 0)
       					break;
					cout << "invalid input (only 1 or 0)\n";
					}
					itemdao.update_exist(item_id,exist);
					delete myrest;
					myrest = restdao.getrestaurant(rest_id);
					
				}
				else if ( khoste == 7 || item_id == 0)
					break;
				else
				{
					cout<< "this input is invalid"<<endl;
				}
				pause();
			}
		}
		else if ( answer == 8)
		{
			vector <orders*> orderha = orderado.getrestaurantOrders(rest_id);
			for ( int i = 0; i< orderha.size();i++)
			{
				cout << " id : " << orderha[i]->get_id() << "| date : " << orderha[i]->get_date() << "| status : " << orderha[i]->get_status()<<endl;
			}
			cout <<" choose order : ";
			int order_id;
			int flag = 0;
			do
			{
				 order_id = int_eror<int>("this input is invalid sweety!, please input number" );
				for ( int i = 0; i<orderha.size();i++)
				{
					if ( orderha[i]->get_id() == order_id)
						flag = 1;
				}
			}while ( flag == 0 );
			string status;
			cout<< "input new status : "<<endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin,status);
			orderado.update_status(order_id,status);
			for ( int i =0; i<orderha.size();i++)
				delete orderha[i]; 
			orderha = orderado.getrestaurantOrders(rest_id);
		}
			
		else
		{
			cout << "this input is invalid " << endl;
		} 
		pause();
		cout << "\n1. show restaurant info" << endl;
		cout << "2. show menu" << endl;
		cout << "3. add item to menu" << endl;
		cout << "4. delete item from menu" << endl;
		cout << "5. show orders" << endl;
		cout<<"6.change restaurant info"<<endl;
		cout<<"7.change menu items"<<endl;
		cout<<"8.change the status of orders"<<endl;
		cout << "9. exit" << endl;
		 answer = int_eror<int>("this input is invalid sweety!, please input number" );
	}
	for ( int i = 0; i < rests.size();i++)
		delete rests[i];
	delete myrest;
}

void program_manager_panel(sqlite3* db)
{
	system("cls");
	restaurantDAO restdao(db);
	customerADO customerado(db);	
	orderDAO orderdao(db);
	int answer;
	cout << "\nWhat you want now?" << endl;
	cout << "1. amount of sell (all orders count)" << endl;
	cout << "2. add new restaurant" << endl;
	cout << "3. turning on the restaurant" << endl;
	cout << "4. turning off the restaurant" << endl;
	cout << "5. show all users" << endl;
	cout << "6. exit" << endl;
	 answer = int_eror<int>("this input is invalid sweety!, please input number" );

	while ( answer != 6)
	{
		if ( answer == 1)
		{
			vector<restaurant*> rests = restdao.getallrestaurants();
			//tedad sefaresh hay kol
			int ORs = 0;
			//  mablagh sefaresh haye kol
			int payoutas = 0;
			cout << "we have " << rests.size() << " restaurants in system " << endl;
			for ( int i = 0; i < rests.size(); i++) 
			{
				//tedad sefaresh haye har restauran
				int OR = 0;
				//  mablagh sefaresh haye har restaurant
				int payouta = 0;
					vector <orders*> order_r = orderdao.getrestaurantOrders(rests[i]->get_id());
					for ( int z = 0; z <order_r.size();z++)
					{
						payouta += order_r[z]->total_price();
						OR +=1;
					}
				cout<<"Name : " << rests[i]->get_name() << " Count of orders :  " << OR << " all the payouts : " << payouta<<endl;
				payoutas += payouta;
				ORs += OR;
				for ( int i=0; i<order_r.size();i++)
				{
					delete order_r[i];
				}
			}
			cout << "Overall Statistics " <<  endl;
			cout<< "Total orders : " << ORs<<endl;
			cout<< "Total payout : "<<payoutas<<endl;
			for ( int i = 0; i < rests.size(); i++) 
			{
				delete rests[i];
			}
		}
		else if ( answer == 2)
		{
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "enter name: ";
			string name;
			getline(cin,name);
			cout << "enter location: ";
			string loc;
			getline(cin,loc);
			cout << "enter phone: ";
			string phone;
			getline(cin,phone);
			cout << "enter description: ";
			string description;
			getline(cin,description);
			cout << "enter prepare time (minutes): ";
			int time;
			cin >> time;
			while ( cin.fail())
			{
					cout<<"please input numbers!";
					cin.clear();
  					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cin >> time;
					
			}
			menu* m = new menu();
			restaurant* new_r = new restaurant(*m, 0, time, true, loc, phone, description, name);
			restdao.addrestaurant(*new_r);
			cout << name << " added to system :)" << endl;
			delete new_r;
			delete m;
		}
		else if ( answer == 3)
		{
			cout << "enter restaurant id to turn on: "<<endl;
			show_rs(db);
			int id;
			 id = int_eror<int>("this input is invalid sweety!, please input number" );
			restaurant* r = restdao.getrestaurant(id);
			if ( r == nullptr)
			{
				cout << "we dont have this id bro!" << endl;
			}
			else
			{
				r->set_status(true);
				restdao.update_status(id,true);
				cout << r->get_name() << " is now on bro!" << endl;
			}
			delete r;
		}
		else if ( answer == 4)
		{
			cout << "enter restaurant id to turn off: "<<endl;
			show_rs(db);
			int id;
		 	id = int_eror<int>("this input is invalid sweety!, please input number" );
			restaurant* r = restdao.getrestaurant(id);
			if ( r == nullptr)
			{
				cout << "we dont have this id bro!" << endl;
			}
			else
			{
				r->set_status(false);
				restdao.update_status(id,false);
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
		pause();
		cout << "\n1. amount of sell (all orders count)" << endl;
		cout << "2. add new restaurant" << endl;
		cout << "3. turning on the restaurant" << endl;
		cout << "4. turning off the restaurant" << endl;
		cout << "5. show all users" << endl;
		cout << "6. exit" << endl;
		answer = int_eror<int>("this input is invalid sweety!, please input number" );
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
	while (true)
	{
    cin >> answer;

    if (cin.fail())
    {
        cout << "Invalid input! Please enter 1, 2 or 3" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if (answer == 1 || answer == 2 || answer == 3)
        break;

    cout << "Invalid choice! Please enter 1, 2 or 3" << endl;
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