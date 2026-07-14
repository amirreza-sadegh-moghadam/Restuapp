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
#include <limits>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;
#include <limits>
#include <iostream>
int show_next_level ( string a)
{
	if ( a == "Normal")
	{
		return 100;
	}
	if ( a == "Silver")
	{
		return 300;
	}
	if ( a == "Gold")
	{
		return 700;
	}
}
using namespace std;
// baraye erorhandeling dar vroody haye gheir adday baraye moteghair haye adady
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
// baraye ijad tavaghof dar menu  , mah nashoedan sarieh etelahat az jolo cheshm mokhatab
void pause()
{
	cout<< " please enter to countinue!";
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	cin.get();
	system("cls");
}
// zaman ra be soart sanieh daryaft mikonad sepas be model taghsim shode( sal, mah, rooz,saat,daghgige,sanie) tabdil mikonad sepas sal mah roozash 
// ra dar yek string zakhire mikonad va dar akhar in string ra be int tabdil mikonad va return mikonad
int get_current_date()
{
    time_t now = time(nullptr);
    tm tm = *localtime(&now);
    ostringstream oss;
    oss << put_time(&tm, "%Y%m%d");
    return stoi(oss.str());
}
// bakhs menu moshtary
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
		MembershipLevel* newcustomers = new NormalLevel();
		customer* newcustomer = new customer(0, name, 0,0,newcustomers,0,0);
		customerado.addcustomer(newcustomer);
		// agar moshtary dar app ozve nabashad ba gereftan esm o, ozvsh mikonad va be oo yeck id midahad ke ba on mitavand vared shavad
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
	// serafa tebgh khaste project amal kardam magarnah benazar man in jaleb nist va bahtar bood ke yeck goozine toye menu mizashtim ta moshtray bere va level 
	//information hash roe bebine
	cout << "welcome back " << moshtary->get_name() <<" the " << moshtary->return_name()<< "!" << endl; 

	cout<< "your level is " <<moshtary->get_level()->get_level()<<endl;
	cout<< " your points" << moshtary->get_point()<< endl;
	string a =  moshtary->get_level()->get_level();
	int date = get_current_date();
	
	if ( moshtary->copen_calculator(date) == true )
	{
		customerado.update_copen(moshtary->get_id(),moshtary->get_copen());
		customerado.update_last_copen(moshtary->get_id(),date);
	}
	if (a!= "VIP" )
	{
		cout <<" you need " << show_next_level(a) << "points";
	}
	int answer2;
	// baraye mohasebeh points
	int itemcount = 0;
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
		orders* newone = new orders(0, moshtary->get_id(), date, "dar hal amade sazi",choose->get_id(),0);
		
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
				itemcount ++;
				cout << found->get_name() << " added to your order bro!" << "Total Price : "<<newone->total_price()<<endl;
				double total = newone->total_price();
				//mohasebeh gheymat takhfif dar
				newone->set_total(total - total*moshtary->get_level()->get_discount()/100);
				
			}
			else if ( answer3 == 2)
			{
				cout << "enter the id's of item who you want to remove: ";
				int itemid;
				itemid = int_eror<int>("this input is invalid , please input number" );
				newone->del_item(itemid);
				double total = newone->total_price();
				//mohasebeh gheymat takhfif dar
				newone->set_total(total - total*moshtary->get_level()->get_discount()/100);
			}   
			else if (answer3 == 3)                                   
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

		system("cls");
		cout<<"do you want delivery ( Y /N)"<<endl;
		string deliveryanswer;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		getline(cin,deliveryanswer);
		double delivery_price =  30 - 0.3*moshtary->get_level()->ersal();
		while ( deliveryanswer != "Y"  && deliveryanswer != "N")
		{
			cout<< " invalide, please input 'Y' or 'N'"<<endl;
			getline(cin,deliveryanswer);
		}
		if ( deliveryanswer == "Y")
		{
			cout<<" you get it and its  orginal price  is : 30 " <<endl  ;
			cout<< "but you are a good customer and we give you a discount "<<endl;
			cout<<" its price :" <<delivery_price<<endl;
			newone->set_total(newone->get_total() + delivery_price);
			
		}
		if ( moshtary->get_copen() > 0)
		{
			cout<< "you have" << moshtary->get_copen()<< "do you want to use it?(Y/N)"<<endl;
			string answercopen;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin,answercopen);
			while ( answercopen != "N" && answercopen != "Y")
			{
				cout<<" please only input N or Y"<<endl;
				getline(cin,answercopen);
			}
			if ( answercopen == "N")
			{
				newone->set_total(newone->get_total() * 0.8);
				cout<<" you get a 20% :)"<<endl;
				cout<< "your price is " << newone->get_total();
				moshtary->set_copen(moshtary->get_copen()-1);
				customerado.update_copen(moshtary->get_id(),moshtary->get_copen());
			}
		}
		pause();
		system("cls");
		orderado.addOrder(newone);
		// chap factory ke matn project behesh takid dosht
		cout<< " Order ID : " << newone->get_id() << " status : " << newone->get_status()<< " price : " << newone->get_total()<<endl;
		string old = moshtary->get_level()->get_level();
		int yourpoints = pointcalculator(itemcount,newone->get_total(),moshtary->get_level()->get_pointx());
		if (deliveryanswer == "Y")
		{
		cout<< "Delivery :" << delivery_price<<endl;
		}
		cout<<"points : "<< yourpoints<<endl;       
		cout<<"level  discount : " <<moshtary->get_level()->get_discount()<<"%"<<endl;
		cout<<"totally price ( with discount)" << newone->get_total()<<endl;
		moshtary->add_point(yourpoints);            
		if( old != moshtary->get_level()->get_level())
		{
			logado logdo(db);
			logdo.addlog(moshtary->get_id(),old,moshtary->get_level()->get_level(),date);
		}                         
		customerado.update_point(moshtary->get_id(),moshtary->get_point());
		customerado.update_level(moshtary->get_id(),moshtary->get_level()->get_level());
		
		pause();
		customerado.update_Debt(moshtary->get_id(),newone->get_total());
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
// choon dar chanidn kaye main kole restauran ha namayesh dadaeh mishodand in tabeh barayesh neveshte shood
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
// bakhsh modiriat restauran
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
	// dar inja eror handling kamel sorat migirad ke yeck vaght id cher o paert tavasot karbar vared nashavad
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
			// dar in paeein kamel baresi mishavad ke vroody chizi jooz food ya drink nabashad
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
			// baraye check addady boodan vroody
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
			// dar paieen motmein mishavim ke chizi jooz 0 ya 1 tavasot karbar vared nashavad
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
			// baraye inke menu restauran dar ja berooz beshavad
			myrest = restdao.getrestaurant(resid);
			delete newitem;
		}
		else if ( answer == 4)
		{
			int itemid;
			myrest->show_menu();
			cout << "enter item id to delete :  ";
			itemid = int_eror<int>("this input is invalid sweety!, please input number" );
			// baresi mikonad ke karabar id chert vared nakardeh bashad
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
			 // bar asas id vroody kool sefaresh haye oon shakhs dar restauran modir ra namayesh midahad 
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
				//dar akhar pointer sefaresh ha ra pack mikonad
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
				// dar payan har if javab dobare myrest adres giri mishavad ta dar ja menu update shavad va in mozooh barkhat sorat girad
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
					// check mikonad chizi jooz  0 ya 1 vared nashavad
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
				// inja ham dar har if khoste va bad taghir myrest dobare odresdehy mishavad ta menu barkhat bashad 
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
					//dobareh check mishavad ke vroody chizy jozeh 0 ya 1 nabashad
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
			customerADO customerado(db);
			//dar inja modir restauran mitavand vazeeiat sefaresh ha ra taghir bedahad
			vector <orders*> orderha = orderado.getrestaurantOrders(rest_id);
			for ( int i = 0; i< orderha.size();i++)
			{
				cout << " id : " << orderha[i]->get_id() << "| date : " << orderha[i]->get_date() << "| status : " << orderha[i]->get_status()<<endl;
			}
			cout <<" choose order : ";
			int order_id;
			int flag = 0;
			int z;
			do
			{
				 order_id = int_eror<int>("this input is invalid sweety!, please input number" );
				for ( int i = 0; i<orderha.size();i++)
				{
					if ( orderha[i]->get_id() == order_id)
					{
					
						flag = 1;
						z = i;
						break;
					}
				}
			}while ( flag == 0 );
			string status;
			cout<< "input new status : "<<endl;
			cout<< " if you want to cancel some order input canceled"<<endl;
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			getline(cin,status);
			if (status == "canceled")
			{
				customer* customerma = customerado.getcustomer(orderha[z]->get_customer_id());
				string old= customerma->get_level()->get_level();
				int itemcount = orderha[z]->get_items().size();
				customerma->del_point(pointcalculator(itemcount,orderha[z]->get_total(),customerma->get_level()->get_pointx()));
				customerado.update_point(customerma->get_id(),customerma->get_point());
				customerado.update_level(customerma->get_id(),customerma->get_level()->get_level());
				if ( old != customerma->get_level()->get_level() )
				{
					logado  logdo(db);
					logdo.addlog(customerma->get_id(),old,customerma->get_level()->get_level(),get_current_date());
				}
				delete customerma;
			}
			
			orderado.update_status(order_id,status);
			for ( int i =0; i<orderha.size();i++)
				delete orderha[i]; 
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
// bakhsh modireyat barnameh
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
	cout<< "6.change  level of user"<<endl;
	cout<<"7.see level log"<<endl;
	cout << "8. exit" << endl;
	 answer = int_eror<int>("this input is invalid sweety!, please input number" );

	while ( answer != 8)
	{
		if ( answer == 1)
		{
			vector<customer*> customerss= customerado.getallcustomer();
			vector<restaurant*> rests = restdao.getallrestaurants();
			//tedad sefaresh hay kol
			int ORs = 0;
			//  mablagh sefaresh haye kol
			int payoutas = 0;
			cout << "we have " << rests.size() << " restaurants in system " << endl;
			// shomaresh level ha!
			int normal = 0,vip = 0,gold = 0,silver = 0;

			for ( int m = 0; m<customerss.size();m++)
				{
					if ( customerss[m]->get_level()->get_level() == "Normal" )
						normal++;
					if ( customerss[m]->get_level()->get_level() == "Silver" )
						silver++;
					if ( customerss[m]->get_level()->get_level() == "Gold" )
						gold++;
					if ( customerss[m]->get_level()->get_level() == "VIP" )
						vip++;	
				}
			for ( int i = 0; i < rests.size(); i++) 
			{
				//tedad sefaresh haye har restauran
				int OR = 0;
				//  mablagh sefaresh haye har restaurant
				int payouta = 0;
					vector <orders*> order_r = orderdao.getrestaurantOrders(rests[i]->get_id());
					for ( int z = 0; z <order_r.size();z++)
					{
						payouta += order_r[z]->get_total();
						OR +=1;
					}
					// dar inja sefaresh ha va mablagh har restauran ra jooda namayesh midihad
				cout<<"Name : " << rests[i]->get_name() << " Count of orders :  " << OR << " all the payouts : " << payouta<<endl;
				payoutas += payouta;
				ORs += OR;
				
				for ( int i=0; i<order_r.size();i++)
				{
					delete order_r[i];
				}
			}
			//dar inja jameh in do vishegy dar koll restauran ha ra namayesh midahad
			cout << "Overall Statistics " <<  endl;
			cout<< "Total orders : " << ORs<<endl;
			cout<< "Total payout : "<<payoutas<<endl;
			cout<<"----level information----"<<endl;
			cout<< " normal user : " <<normal<<endl;
			cout<<" silver user : " << silver<<endl;
			cout<<" gold user : " << gold<<endl;
			cout<<" vip user : "<< vip<<endl;
			for ( int i = 0; i < rests.size(); i++) 
			{
				delete rests[i];
			}
			for(int i=0;i<customerss.size();i++)
			{
				delete customerss[i];
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
			//baraye rooshan kardan yeck restauran
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
			// baraye khamoosh karadan yeck restauran ke sabab mishavad digar baraye moshtray namayesh nayabad
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
			//tamam user hara be modir namayesh midahad
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
		else if (answer == 6)
		{
			//tamam user hara be modir namayesh midahad
			vector<customer*> customers = customerado.getallcustomer();
			cout << "\nall users:" << endl;
			for ( int i = 0; i < customers.size(); i++)
			{
				cout << "id: " << customers[i]->get_id()
					 << " | name: " << customers[i]->get_name()
					 << " | points: " << customers[i]->get_point() << endl
					 <<"| level :" << customers[i]->get_level()->get_level()<<endl;
			}
			cout<< "what user do you want to change?"<<endl;
			int userid;
			int flagg = 0;
			while ( flagg == 0)
			{
				cin >> userid;
				userid = int_eror<int>("please input numbers" );
				for ( int i = 0; i<customers.size();i++)
				{
					if ( userid == customers[i]->get_id())
					{
						// peyda mishe va hala bahash kar mikonim
						userid = i;
						flagg = 1;
						break;
					}
					if ( i == customers.size()-1)
					{
					cout<< " we dont have this user!"<<endl;
					}
				}
				
				
			}
			cout<< " what you whant to change ? "<<endl;
			cout<<"1.point";
			cout<<"2.level"<<endl;
			int manageranswer;
			manageranswer = int_eror<int>("this input is invalid !, please input number" );
			while (manageranswer != 1 && manageranswer != 2)
			{
				int_eror<int>("this input is invalid !, please input number 2 or 1" );
			}
			if (manageranswer == 1)
			{
				cout<< "  points  of this user :"<<customers[userid]->get_point()<<endl;
				cout<< " please input the new point "<<endl;
				int newpoint;
				newpoint = int_eror<int>("this input is invalid !, please input number" );
				string old = customers[userid]->get_level()->get_level();
				customers[userid]->set_point(newpoint);
				customerado.update_point(customers[userid]->get_id(),newpoint);
				customerado.update_level(customers[userid]->get_id(),customers[userid]->get_level()->get_level());
				if (old != customers[userid]->get_level()->get_level())
				{
					logado logdo(db);
					logdo.addlog(customers[userid]->get_id(),old,customers[userid]->get_level()->get_level(),get_current_date());
				}
				cout<< "  done fine!"<<endl;
			}
			if (manageranswer == 2)
			{
				cout<< "level of this user "<<customers[userid]->get_level()->get_level()<<endl;
				cout<< " plese input the new level "<<endl;
				// tebgh matn project modir mitoneh avaz koneh level ro va in motineh khalaf point ha basheh!
				cout<<"just input Normal,Silver,Gold,VIP";
				string levelanswer;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				getline(cin,levelanswer);
				while ( levelanswer != "Normal" && levelanswer !="Silver" && levelanswer != "Gold" && levelanswer != "VIP")
				{
					cout<<" invalid input, just input Normal,Silver,Gold,VIP"<<endl;
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					getline(cin,levelanswer);
				}
				string oldi = customers[userid]->get_level()->get_level();
				MembershipLevel* temp = nullptr;
				if ( levelanswer == "Normal")
					temp = new NormalLevel();
				if ( levelanswer == "Silver")
					temp = new SilverLevel();
				if ( levelanswer == "Gold" )
					temp = new GoldLevel();
				if( levelanswer == "VIP")
					temp = new VIPLevel();
				customers[userid]->set_level(temp);
				if (oldi != customers[userid]->get_level()->get_level())
				{
					logado logdo(db);
					logdo.addlog(customers[userid]->get_id(),oldi,customers[userid]->get_level()->get_level(),get_current_date());
				}
				customerado.update_level(customers[userid]->get_id(),levelanswer);
				cout<< " done fine!";
				
			}
			
		
			
			for ( int i = 0; i < customers.size(); i++) 
			{
			delete customers[i];
			}
		}
		else if (answer == 7)
		{
			logado logdo(db);
			logdo.show_log();
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
		cout<< "6.change level of user"<<endl;
		cout << "7. see level log" << endl;
		cout<< "8.exist"<<endl;
		answer = int_eror<int>("this input is invalid sweety!, please input number" );
	}
}
// va hala main asy va seda zadan in tabeh haye doost dashtany:))
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
	db.create_Log();

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

/*
neveshte shode : Amirreza Sadeghmoghadam

ba arezo moafaghiat baraye tamam khonandegan in code:)
-
*/