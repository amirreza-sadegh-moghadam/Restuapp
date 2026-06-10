#include  "data.h"
#include <iostream>
#include "itemADO.h"

data::data(sqlite3* db)
{
	this->db = nullptr;
}
bool data::connect()
{
	int open = sqlite3_open("data.db", &db);

	if( open != SQLITE_OK)
    {
        std::cout << "Database Error\n";
        return false;
    }

    return true;
}
void data::close()
{
    sqlite3_close(db);
}
sqlite3* data::getDB()
{
    return db;
}
void data::create_restaurant()
{
	const char* res_data = "CREATE TABLE IF NOT EXISTS RESTAURANT("
	"id INTEGER PRIMARY KEY AUTOINCREMENT,"
	"time INTEGER,"
	"status INTEGER,"
	"location TEXT,"
	"phone TEXT,"
	"name TEXT,"
	"description TEXT);";
	sqlite3_exec(db,res_data,nullptr,nullptr,nullptr);
}
void data::create_item()
{
	const char* item_data=
	" CREATE TABLE IF NOT EXISTS ITEM("
	"id INTEGER PRIMARY KEY AUTOINCREMENT,"
	"res_id INTEGER,"
	"name TEXT,"
	"description TEXT,"
	"price REAL,"
	"type TEXT,"
	"value INTEGER,"
	"exist INTEGER,"
	"time INTEGER);";
	sqlite3_exec(db,item_data,nullptr,nullptr,nullptr);
}
void data::create_customer()
{
	const char* customer_data=
	" CREATE TABLE IF NOT EXISTS CUSTOMER("
	"id INTEGER PRIMARY KEY AUTOINCREMENT,"
	"name TEXT,"
	"Debt REAL);";
	sqlite3_exec(db,customer_data,nullptr,nullptr,nullptr);
}
void data::create_order()
{
	const char* order_data=
	" CREATE TABLE IF NOT EXISTS ORDERS("
	"id INTEGER PRIMARY KEY AUTOINCREMENT,"
	"customer_id INTEGER,"
	"date INTEGER,"
	"status TEXT);";
	sqlite3_exec(db,order_data,nullptr,nullptr,nullptr);
}
void data::create_order_item()
{
    const char* order_item_data =
    "CREATE TABLE IF NOT EXISTS order_items("
    "id INTEGER PRIMARY KEY AUTOINCREMENT,"
    "order_id INTEGER,"
    "item_id INTEGER,"
    "quantity INTEGER);";

    sqlite3_exec(db,order_item_data,nullptr,nullptr,nullptr);
}
restaurantDAO::restaurantDAO(sqlite3* db)
{
   this->db = db;
}
void restaurantDAO::addrestaurant(restaurant& r)
{
    string sql =
    "INSERT INTO RESTAURANT "
    "(time,status,location,phone,description,name) "
    "VALUES(" +

    to_string(r.get_time()) + "," +

    to_string(r.get_status()) + "," +

    "'" + r.get_location() + "'," +

    "'" + r.get_phone() + "'," +

    "'" + r.get_description() + "'," +

    "'" + r.get_name() + "'" +

    ");";

    sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        nullptr
    );
    int id = sqlite3_last_insert_rowid(db);
    r.set_id(id);
}
restaurant* restaurantDAO::getrestaurant(int id)
{
    string sql =
    "SELECT * FROM RESTAURANT WHERE id = " +
    to_string(id) + ";";

    sqlite3_stmt* stmt;

    sqlite3_prepare_v2(
        db,
        sql.c_str(),
        -1,
        &stmt,
        nullptr
    );

    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id =
        sqlite3_column_int(stmt,0);

        int time =
        sqlite3_column_int(stmt,1);

        bool status =
        sqlite3_column_int(stmt,2);

        string location =
        (char*)sqlite3_column_text(stmt,3);

        string phone =
        (char*)sqlite3_column_text(stmt,4);

        string description =
        (char*)sqlite3_column_text(stmt,6);

        string name =
        (char*)sqlite3_column_text(stmt,5);

        menu* m = new menu();

        restaurant* r =
        new restaurant(
            *m,
            id,
            time,
            status,
            location,
            phone,
            description,
            name
        );
        itemDAO itemdao(db);
        vector<item*> items = 
        itemdao.getrestaurantitem(id);
        for(int i=0;i<items.size();i++)
		{
	    	r->add_menu(items[i]);
		}
        sqlite3_finalize(stmt);

        return r;
    }
	//dar sorati ke peyda nakard!
    sqlite3_finalize(stmt);

    return nullptr;
}
vector<restaurant*> restaurantDAO::getallrestaurants()
{
	itemDAO itemdao(db);
	vector<restaurant*> restaurants;
	string sql = 
	"SELECT * FROM RESTAURANT;";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(
	db,sql.c_str(),-1,&stmt,nullptr);
	while ( sqlite3_step(stmt) ==SQLITE_ROW)
	{
		int id =
        	sqlite3_column_int(stmt,0);

        	int time =
        	sqlite3_column_int(stmt,1);

        	bool status =
        	sqlite3_column_int(stmt,2);

        	string location =
        	(	char*)sqlite3_column_text(stmt,3);

        	string phone =
        	(char*)sqlite3_column_text(stmt,4);

        	string description =
 	        (char*)sqlite3_column_text(stmt,6);

     	   string name =
        	(char*)sqlite3_column_text(stmt,5);

        	menu* m = new menu();
        	restaurant* r =
        	new restaurant(*m,id,time,status,location,phone,description,name); 
        	vector<item*> items
        	= itemdao.getrestaurantitem(id);
        	for ( int i = 0; i< items.size();i++)
        	{
        		r->add_menu(items[i]);
			}
        	restaurants.push_back(r);
	}
	sqlite3_finalize(stmt);
	return restaurants;
}
void restaurantDAO::delete_rest(int id)
{
	string sql = 
	"DELETE FROM ITEM WHERE res_id = " + to_string(id) + ";";
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
	string sqll = 
	"DELETE FROM RESTAURANT WHERE id = " + to_string(id) + ";";
	sqlite3_exec(db,sqll.c_str(),nullptr,nullptr,nullptr);
}