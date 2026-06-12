#include"itemADO.h"
extern "C"{
#include "sqlite3.h"
}
itemDAO::itemDAO(sqlite3* db)
{
	this->db = db;
}
// id restauran ra migirad va item ra ba tavgoh be oone zakhire mikonad, id restaurant baes mishavad dar zaman sakht restauran  menu darja sokhte shavad
void itemDAO::add_item(item* item, int res_id)
{
	string sql =
    "INSERT INTO ITEM "
    "(res_id,name,description,price,type,value,exist,time) "
    "VALUES(" +

	to_string(res_id) + "," +

	"'" + item->get_name() + "'," +
	"'" + item->get_description() + "'," +
	to_string(item->get_price()) + "," +
	"'" + item->get_type() + "'," +
	to_string(item->get_value()) + "," +
	to_string(item->get_exist()) + "," +
	to_string(item->get_time()) +
	");";

    sqlite3_exec(
        db,
        sql.c_str(),
        nullptr,
        nullptr,
        nullptr
    );
}
// item ra sefa bar asas id khood item midahad
item* itemDAO::get_item(int id)
{
	string sql =
    "SELECT * FROM ITEM WHERE id = " +
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

        int res_id =
        sqlite3_column_int(stmt,1);

        string name =
        (char*)sqlite3_column_text(stmt,2);
        
		string description =
		(char*)sqlite3_column_text(stmt,3);
        double price =
        sqlite3_column_double(stmt,4);

        string type =
        (char*)sqlite3_column_text(stmt,5);

        int value =
        sqlite3_column_int(stmt,6);

        int exist =
        sqlite3_column_int(stmt,7);

        int time = 
        sqlite3_column_int(stmt,8);
        item* i ;
        if ( type  == "food")
        i=
        new food(id, name, type, price, description, time, value, exist);
        else
        i =
        new drink(id, name, type, price, description, time, value, exist);   


        sqlite3_finalize(stmt);
        
        return i;
    }
	//dar sorati ke peyda nakard!
    sqlite3_finalize(stmt);

    return nullptr;
}
// item haye yeck restauran ra be toor komel midahad

vector<item*> itemDAO::getrestaurantitem(int resid)
{
	vector<item*> menu;
	string sql
	= "SELECT * FROM ITEM ";
	sqlite3_stmt* stmt;

    sqlite3_prepare_v2(
        db,
        sql.c_str(),
        -1,
        &stmt,
        nullptr
    );
    while ( sqlite3_step(stmt) == SQLITE_ROW)
    {
    	int res_id =
    	sqlite3_column_int(stmt,1);
    	if ( res_id == resid )
    	{
    	
        	int id =
        	sqlite3_column_int(stmt,0);


	        string name =
    	    (char*)sqlite3_column_text(stmt,2);
        
			string description =
			(char*)sqlite3_column_text(stmt,3);
        	double price =
        	sqlite3_column_double(stmt,4);

       		string type =
        	(char*)sqlite3_column_text(stmt,5);

        	int value =
        	sqlite3_column_int(stmt,6);

        	int exist =
        	sqlite3_column_int(stmt,7);

        	int time = 
        	sqlite3_column_int(stmt,8);
        	item* i;
        	if ( type  == "food")
        		i =
        		new food(id, name, type, price, description, time, value, exist);
        	else
        		i =
        		new drink(id, name, type, price, description, time, value, exist);  
        	menu.push_back(i);
		}
	}
	sqlite3_finalize(stmt);
	return menu;
	
}
void itemDAO::delete_item(int id)
{
	string sql =
	"DELETE FROM ITEM WHERE id = " + to_string(id)+";";
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
	
}
// baghieh tabeh ha baraye update hastand

void itemDAO::update_name(int id,string name)
{
	string sql = 
	"UPDATE ITEM SET name = '" + name +"' WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}
void itemDAO::update_price(int id,double price)
{
	string sql = 
	"UPDATE ITEM SET price = " + to_string(price) +" WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}
void itemDAO::update_description(int id,string description)
{
	string sql = 
	"UPDATE ITEM SET description = '" + description +"' WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}
void itemDAO::update_time(int id,int time)
{
	string sql = 
	"UPDATE ITEM SET time = " + to_string(time) +" WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}
void itemDAO::update_value(int id,int value)
{
	string sql = 
	"UPDATE ITEM SET value = " + to_string(value) +" WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}
void itemDAO::update_exist(int id, bool exist)
{
	string sql = 
	"UPDATE ITEM SET exist = " + to_string(exist) +" WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}