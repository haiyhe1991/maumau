#ifndef __TIME_TOOLS_H__
#define __TIME_TOOLS_H__

#include <string>

//ʱ�����

struct TimeStruct
{
	int				year;
	int				month;
	int				day;
	int				hour;
	int				minute;
	int				secend;
	int				cur_time;			//1970�굽���ڵ�����
	long long		cur_mtime;			//1970�굽���ڵĺ�����
};

class TimeTools
{
public:
	static TimeTools*		getInstance();								//ȡ��ʱ������Ψһʵ��
	static void				destoryInstance();							//���ٵ�ǰʵ��
	void					setSystemTime(int time);

	TimeStruct				getCurTime();
	int						getSecendFormat(std::string timeFormat);			//����ʱ���ַ�����ȡ��1970���ַ�������ʱ�������  format��2013.11.17
private:
	TimeTools();
	static TimeTools *_instance;

	//���������µ�ʱ���ֵ    1970-01-01  ������
	int _time;
};

#endif
