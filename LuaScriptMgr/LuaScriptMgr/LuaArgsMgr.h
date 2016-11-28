#ifndef CLUAARGSMGR_H_
#define CLUAARGSMGR_H_

#include<iostream>
#include<string>
#include<list>

/*
Lua������������ʹ�ø�������Lua��ջ����������ռ�lua��ջ���ص�����
C�п��ܴ��뵽Lua��ջ�е��������ͣ�bool,int,short,string,long,etc
*/
enum C_TYPE
{
	C_TYPE_BOOL,
	C_TYPE_INT,
	C_TYPE_LONG,
	C_TYPE_DOUBLE,
	C_TYPE_STRING,
	C_TYPE_ALL,
};

typedef struct CValue
{
	bool bValue;
	int  iValue;
	long lValue;
	double dValue;
	std::string strValue;
	CValue()
	{
		bValue = false;
		iValue = 0;
		lValue = 0l;
		dValue = 0.0;
	}
} CValue;

class CValueType
{
public:
	CValueType();
	virtual ~CValueType();
public:
	// get��set����
	void SetBool(bool bValue);
	bool GetBool() const { return _value.bValue; } 

	void SetInt(int iValue);
	int  GetInt() const { return _value.iValue; }

	void SetLong(long lValue);
	long GetLong() const { return _value.lValue; }

	void SetDouble(double dValue);
	double GetDouble() const { return _value.dValue; }

	void SetString(std::string str);
	std::string GetString() const { return _value.strValue; }

	C_TYPE GetType() const { return _type; }

private:
	CValue _value;
	C_TYPE _type;
};


class CLuaArgsMgr
{
public:
	CLuaArgsMgr();
	virtual ~CLuaArgsMgr();
public:
	std::list<CValueType>& GetLuaArgsList() { return m_LuaArgsList; }
	void Add(bool bValue);
	void Add(int  iValue);
	void Add(long lValue);
	void Add(double dValue);
	void Add(std::string str);
public:
	void Clear();
public:
	// ���Դ�ӡ����
	void PrintDebug();
private:
	std::list<CValueType> m_LuaArgsList; // Lua��������
};


#endif // !CLUAARGSMGR_H_