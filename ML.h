#ifndef ML_H
#define ML_H
#include <iostream>
#include<string>
using namespace std;
class  MembershipLevel 
{
	public:
	virtual string get_level() = 0;
	virtual int get_copen() = 0;
	virtual double get_pointx() = 0;
	virtual int get_discount() = 0;	
	virtual int ersal() = 0;
	
};
class NormalLevel : public MembershipLevel 
{
	public:
	
	string get_level();
	int get_copen();
	double get_pointx();
	int get_discount();	
	int ersal();	 
};
class SilverLevel : public MembershipLevel 
{
	public:
		
	string get_level();
	int get_copen();
	double get_pointx();
	int get_discount();
	int ersal();		
};
class GoldLevel: public MembershipLevel 
{
	public:
		
	string get_level();
	int get_copen();
	double get_pointx();
	int get_discount();	
	int ersal();	
};
class VIPLevel: public MembershipLevel 
{
	public:
		
	string get_level();
	int get_copen();
	double get_pointx();
	int get_discount();
	int ersal ();				
};
double pointcalculator( int items,int price, int pointx);
#endif
