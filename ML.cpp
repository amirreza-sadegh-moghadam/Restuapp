#include "ML.h"
#include <string>
string NormalLevel::get_level()
{
	return "Normal";
}
string SilverLevel::get_level()
{
	return "Silver";
}
string GoldLevel::get_level()
{
	return "Gold";
}
string VIPLevel::get_level()
{
	return "VIP";
}
int NormalLevel::get_copen()
{
	return 0;
}
int SilverLevel::get_copen()
{
	return 1;
}
int GoldLevel::get_copen()
{
	return 1;
}
int VIPLevel::get_copen()
{
	return 3;
}
double NormalLevel::get_pointx()
{
	return  1.0;
}
double SilverLevel::get_pointx()
{
	return  1.2;
}
double GoldLevel::get_pointx()
{
	return  1.5;
}
double VIPLevel::get_pointx()
{
	return  2.0;
}
int NormalLevel::get_discount()
{
	return  0;
}
int SilverLevel::get_discount()
{
	return  5;
}
int GoldLevel::get_discount()
{
	return  10;
}
int VIPLevel::get_discount()
{
	return  15;
}
int NormalLevel::ersal()
{
	return 0;
}
int SilverLevel::ersal()
{
	return 10;
}
int GoldLevel::ersal()
{
	return 50;
}
int VIPLevel::ersal()
{
	return 100;
}

// in tabeh meghdar emtaiz daryafty dar har kharid ra mohasebeh mikoned , bar asas tedad sefaresh va mablagh va albateh sath
double pointcalculator( int items,int price, int pointx)
{
	return (items* 5 + ( price) * 0.001 ) * pointx;
}