#include "Person.h"

CPerson::CPerson():
	_name("zhangshan"),
	_age(25),
	_sex(0),
	_bornDay("1992-04-11"),
	_id(123456789)
{
}


CPerson::~CPerson()
{
	cout << "Person »ØÊÕ" << endl;
}

string CPerson::get_name()
{
	return _name;
}

void CPerson::set_name(string name)
{
	_name = name;
}

short CPerson::get_age()
{
	return _age;
}

void CPerson::set_age(short age)
{
	_age = age;
}

short CPerson::get_sex()
{
	return _sex;
}

void CPerson::set_sex(short sex)
{
	_sex = sex;
}

string CPerson::get_bornDay()
{
	return _bornDay;
}

void CPerson::set_bornDay(string bornDay)
{
	_bornDay = bornDay;
}

long CPerson::get_id()
{
	return _id;
}

void CPerson::set_id(long id)
{
	_id = id;
}
