
#ifndef CPERSON_H_
#define CPERSON_H_

/*
��Person�ཫע�뵽Lua�У�����Lua��ʹ�ø�Person��Ķ���
*/
#include<iostream>
#include<string>

using namespace std;

class CPerson
{
public:
	CPerson();
	virtual ~CPerson();

	string get_name();
	void set_name(string name);

	short get_age();
	void  set_age(short age);

	short get_sex();
	void  set_sex(short sex);

	string get_bornDay();
	void   set_bornDay(string bornDay);

	long  get_id();
	void  set_id(long id);

private:
	string _name;  
	short _age;
	short _sex;
	string _bornDay;
	long _id;
};

#endif // !CPERSON_H_

