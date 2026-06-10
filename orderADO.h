#ifndef ORDERDAO_H
#define ORDERDAO_H

#include "sqlite3.h"
#include "customer.h"
#include <vector>

class orderDAO
{
	
private:
    sqlite3* db;
    
public:
    orderDAO(sqlite3*);
    void addOrder(orders*);
    orders* getOrder(int);
    vector<orders*> getCustomerOrders(int);
    void delete_order(int);
    vector<orders*> getCustomerOrdersR(int ,int);
    vector<orders*> getrestaurantOrders(int );
};

#endif