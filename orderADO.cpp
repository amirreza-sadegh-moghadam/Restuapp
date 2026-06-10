#include "orderADO.h"
#include <string>
#include <vector>
#include"itemADO.h"
orderDAO::orderDAO(sqlite3* db)
{
	this->db = db;
}
void orderDAO::addOrder(orders* o)
{
	string sql =
	"INSERT INTO ORDERS (customer_id,date,status,restaurant_id) VALUES(" +to_string(o->get_customer_id()) + "," +	to_string(o->get_date()) + ",'" +o->get_status() + "'," +to_string(o->get_rest_id()) +");";
    sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
    int order_id =
    sqlite3_last_insert_rowid(db);
    vector<item*>& items = 
    o->get_items();
    for ( int i =0;i< items.size();i++)
    {
    	string sqll=
    	"INSERT INTO order_items (order_id,item_id,quantity) VALUES(" +
    	to_string(order_id)+"," + to_string(items[i]->get_id()) + ",1);";
    	sqlite3_exec(db,sqll.c_str(),nullptr,nullptr,nullptr);
	}
	o->set_id(order_id);
	
}
orders* orderDAO::getOrder(int id)
{
	string sql =
	"SELECT * FROM ORDERS WHERE id = " + to_string(id)+";";
	sqlite3_stmt* stmt;
    sqlite3_prepare_v2(
        db,
        sql.c_str(),
        -1,
        &stmt,
     nullptr
    );
	orders* o = nullptr;
    if(sqlite3_step(stmt) == SQLITE_ROW)
    {
    	int id =
    	sqlite3_column_int(stmt,0);
    	int customer_id =
    	sqlite3_column_int(stmt,1);
    	int date =
    	sqlite3_column_int(stmt,2);
    	string status = 
    	(char*)sqlite3_column_text(stmt,3);
    	int restaurant_id =
    	sqlite3_column_int(stmt,4);
    	o = new orders(id,customer_id,date,status,restaurant_id);
	}
	if(o == nullptr)
	{
    	sqlite3_finalize(stmt);
    	return nullptr;
	}
	string sqll=
	"SELECT * FROM order_items WHERE order_id = " +to_string(id)+ ";";
    sqlite3_stmt* stmt2;
    sqlite3_prepare_v2(db,sqll.c_str(),-1,&stmt2,nullptr);
    itemDAO itemdao(db);
    while(sqlite3_step(stmt2) == SQLITE_ROW)
    {
    	int item_id = 
    	sqlite3_column_int(stmt2,2);
    	int quantity =
    	sqlite3_column_int(stmt2,3);
    	item * i = itemdao.get_item(item_id);
    	if ( i != nullptr)
    	for ( int j = 0; j < quantity;j++)
    	{
    		o->add_item(i);
		}

	}
	sqlite3_finalize(stmt2);
	sqlite3_finalize(stmt);
	return o;

}
vector<orders*> orderDAO::getCustomerOrders(int customer_id)
{
	vector<orders*> orderha;
	orders* o;
	string sql = 
	"SELECT * FROM ORDERS WHERE customer_id = " + to_string(customer_id)+";";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr);
	while ( sqlite3_step(stmt) == SQLITE_ROW)
	{
		int order_id =
    	sqlite3_column_int(stmt,0);
    	int customer_id =
    	sqlite3_column_int(stmt,1);
    	int date =
    	sqlite3_column_int(stmt,2);
    	string status = 
    	(char*)sqlite3_column_text(stmt,3);
    	int restaurant_id =
    	sqlite3_column_int(stmt,4);
     	o = new orders(order_id,customer_id,date,status,restaurant_id);
     	string sqll = 
     	"SELECT * FROM order_items WHERE order_id = " +to_string(order_id)+ ";";
 		sqlite3_stmt* stmt2;
    	sqlite3_prepare_v2(db,sqll.c_str(),-1,&stmt2,nullptr);
 	    itemDAO itemdao(db);
 	    while(sqlite3_step(stmt2) == SQLITE_ROW)
	    {
   		 	int item_id = 
    		sqlite3_column_int(stmt2,2);
    		int quantity =
    		sqlite3_column_int(stmt2,3);
    		item * i = itemdao.get_item(item_id);
    		if ( i != nullptr)
    		for ( int j = 0; j < quantity;j++)
    		{
    		o->add_item(i);
			}
		}	
    	orderha.push_back(o);
    	sqlite3_finalize(stmt2);

	}
	sqlite3_finalize(stmt);
	return orderha;
}
void orderDAO::delete_order(int id)
{
	string sql = 
	"DELETE FROM order_items WHERE order_id = " + to_string(id) + ";";
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
	string sqll = 
	"DELETE FROM ORDERS WHERE id = " + to_string(id) + ";";
	sqlite3_exec(db,sqll.c_str(),nullptr,nullptr,nullptr);
}

vector<orders*> orderDAO::getrestaurantOrders(int rest_id)
{
	vector<orders*> orderha;
	orders* o;
	string sql = 
	"SELECT * FROM ORDERS WHERE restaurant_id = " + to_string(rest_id)+";";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr);
	while ( sqlite3_step(stmt) == SQLITE_ROW)
	{
		int order_id =
    	sqlite3_column_int(stmt,0);
    	int customer_id =
    	sqlite3_column_int(stmt,1);
    	int date =
    	sqlite3_column_int(stmt,2);
    	string status = 
    	(char*)sqlite3_column_text(stmt,3);
    	int restaurant_id =
    	sqlite3_column_int(stmt,4);
     	o = new orders(order_id,customer_id,date,status,restaurant_id);
     	string sqll = 
     	"SELECT * FROM order_items WHERE order_id = " +to_string(order_id)+ ";";
 		sqlite3_stmt* stmt2;
    	sqlite3_prepare_v2(db,sqll.c_str(),-1,&stmt2,nullptr);
 	    itemDAO itemdao(db);
 	    while(sqlite3_step(stmt2) == SQLITE_ROW)
	    {
   		 	int item_id = 
    		sqlite3_column_int(stmt2,2);
    		int quantity =
    		sqlite3_column_int(stmt2,3);
    		item * i = itemdao.get_item(item_id);
    		if ( i != nullptr)
    		for ( int j = 0; j < quantity;j++)
    		{
    		o->add_item(i);
			}
		}	
    	orderha.push_back(o);
    	sqlite3_finalize(stmt2);

	}
	sqlite3_finalize(stmt);
	return orderha;
}

vector<orders*> orderDAO::getCustomerOrdersR(int customer_id,int restaurant_id)
{
	vector<orders*> orderha;
	orders* o;
	string sql = 
	"SELECT * FROM ORDERS WHERE customer_id = " + to_string(customer_id)+ " AND restaurant_id = " + to_string(restaurant_id)+";";
	sqlite3_stmt* stmt;
	sqlite3_prepare_v2(db,sql.c_str(),-1,&stmt,nullptr);
	while ( sqlite3_step(stmt) == SQLITE_ROW)
	{
		int order_id =
    	sqlite3_column_int(stmt,0);
    	int customer_id =
    	sqlite3_column_int(stmt,1);
    	int date =
    	sqlite3_column_int(stmt,2);
    	string status = 
    	(char*)sqlite3_column_text(stmt,3);
    	int restaurant_id =
    	sqlite3_column_int(stmt,4);
     	o = new orders(order_id,customer_id,date,status,restaurant_id);
     	string sqll = 
     	"SELECT * FROM order_items WHERE order_id = " +to_string(order_id)+ ";";
 		sqlite3_stmt* stmt2;
    	sqlite3_prepare_v2(db,sqll.c_str(),-1,&stmt2,nullptr);
 	    itemDAO itemdao(db);
 	    while(sqlite3_step(stmt2) == SQLITE_ROW)
	    {
   		 	int item_id = 
    		sqlite3_column_int(stmt2,2);
    		int quantity =
    		sqlite3_column_int(stmt2,3);
    		item * i = itemdao.get_item(item_id);
    		if ( i != nullptr)
    		for ( int j = 0; j < quantity;j++)
    		{
    		o->add_item(i);
			}
		}	
    	orderha.push_back(o);
    	sqlite3_finalize(stmt2);

	}
	sqlite3_finalize(stmt);
	return orderha;
}
void orderDAO::update_status(int id,  string status)
{
	string sql = 
	"UPDATE ORDERS SET status = '" +status +"' WHERE id = " + to_string(id);
	sqlite3_exec(db,sql.c_str(),nullptr,nullptr,nullptr);
}