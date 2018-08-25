#pragma once

/*
 * Main data structures and searching functions
 */

#include "enterWidget.h"
#include <iostream>
#include <cstdio>
#include <vector> 
#include <cstdio>
#include <cstdlib>
#include <set>
#include <cstring>
#include <unistd.h>
#include <algorithm>
#include <sstream>
#include <ctime>

#define NAME_N 20
#define PW_N 24
#define COLLEGE_N 24
#define COURSE_NAME_N 28

using namespace std;

/*
 * ѧ���Ϳγ̽ṹ
 */

struct Course
{
	unsigned int course_num;			//�γ̺� 
	char course_name[COURSE_NAME_N];	//�γ�����
	vector<unsigned int>students;		//ѡ�˸ÿγ̵�ѧ��ѧ��
	void set_name(const char *tname) { strncpy(course_name, tname, COURSE_NAME_N); }
	void set_num(const unsigned tnum) { course_num = tnum; }
};

struct Student
{
	unsigned int student_num; 	//ѧ��
	char student_name[NAME_N];	//����
	char college[COLLEGE_N];	//ѧԺ
	char pw[PW_N];				//����
	vector<unsigned int>select;		//��ѡ�γ̵Ŀγ̺�
	void set_num(unsigned tnum) { student_num = tnum; }
	void set_name(const char *tname) { strncpy(student_name, tname, NAME_N); }
	void set_college(const char *tcollege) { strncpy(college, tcollege, COLLEGE_N); }
	void set_pw(const char *tpw) { strncpy(pw, tpw, PW_N); }
};


/*
 * ����find�����Ľṹ�壬����ָ��vector����������
 */

typedef struct find_name		//�����������ĵ�����
{
	find_name(string sname)
	{
		fname = sname;
	}
	bool operator()(const Student& s) //����ѧ��
	{
		if (fname.compare(s.student_name) == 0)
			return true;
		else return false;
	}
	bool operator()(const Course& c) //�����γ�
	{
		if (fname.compare(c.course_name) == 0)
			return true;
		else return false;
	}
	string fname;
}find_name;

typedef struct find_number		//��ѧ�������ĵ�����
{
	find_number(unsigned int snumber)
	{
		fnumber = snumber;
	}
	bool operator()(const Student& s) //����ѧ��
	{
		return s.student_num == fnumber;
	}

	bool operator()(const Course& c) //�����γ�
	{
		return c.course_num == fnumber;
	}
	unsigned int fnumber;
}find_number;


/*
 * Functions of IO
 */

void save();				//������Ϣ
void Quit();				//�˳�
void read_information();	//��ȡ��Ϣ


/*
 * ���ֱȽϺ�����������
 */

bool cmp_course_num(const Course& ca, const Course& cb);
bool cmp_course_name(const Course& ca, const Course& cb);
bool cmp_student_num(const Student& sa, const Student& sb);
bool cmp_student_name(const Student& sa, const Student& sb);

/*
 * ������������
 */

/* Get a student by std_num or name */
vector<Student>::iterator get_student(string inf);
vector<Student>::iterator get_student(unsigned int inf);
/* Judge a string is num or have illegal characters */
bool isNum(string);
/* Get a course by course_num or name */
unsigned int get_course_num(string tname);
string get_course_name(unsigned int tnum);
vector<Course>::iterator get_course(string inf);
vector<Course>::iterator get_course(unsigned int cnum);


/* Change course informations */
void change_s_course(Course *c, int flag, unsigned course_num = 0);
/* Auto generate plenty of data */
void generate_data();