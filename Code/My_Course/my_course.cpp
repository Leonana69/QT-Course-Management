#include "my_course.h"

/*
 * Global variable
 */

char pw[PW_N];
vector<Course>courses; 		//全部课程 
vector<Student>students;	//全部学生
Student *current_student;	//当前登录的学生
Course *current_course;		//当前操作的课程
char buf[100];				//读取输入的缓冲区
FILE *fd;					//文件


/*
 * 各种比较函数用于排序
 */

bool cmp_course_num(const Course& ca, const Course& cb)
{
	return ca.course_num < cb.course_num;
}

bool cmp_course_name(const Course& ca, const Course& cb)
{
	return strcmp(ca.course_name, cb.course_name);
}

bool cmp_student_num(const Student& sa, const Student& sb)
{
	return sa.student_num < sb.student_num;
}

bool cmp_student_name(const Student& sa, const Student& sb)
{
	return strcmp(sa.student_name, sb.student_name);
}


/*
 * Functions of IO
 */

void save()
{
	rewind(fd);
	/* Write provost's password */
	fwrite(pw, 1, PW_N, fd);

	/* Write courses' information */
	int num = courses.size();
	fwrite(&num, sizeof(int), 1, fd);
	for (int i = 0; i < num; i++)
	{
		fwrite(&(courses[i].course_num), sizeof(unsigned int), 1, fd);
		fwrite(courses[i].course_name, 1, COURSE_NAME_N, fd);
		int snum = courses[i].students.size();
		fwrite(&snum, sizeof(int), 1, fd);
		for (int j = 0; j < snum; j++)
			fwrite(&(courses[i].students[j]), sizeof(unsigned int), 1, fd);
		//qDebug("Course: %s %d\n", courses[i].course_name, courses[i].course_num);
	}

	/* Write students' informaiton */
	num = students.size();
	fwrite(&num, sizeof(int), 1, fd);
	for (int i = 0; i < num; i++)
	{
		fwrite(&(students[i].student_num), sizeof(unsigned int), 1, fd);
		fwrite(students[i].student_name, 1, NAME_N, fd);
		fwrite(students[i].college, 1, COLLEGE_N, fd);
		fwrite(students[i].pw, 1, PW_N, fd);
		/* Write students' courses information */
		int snum = students[i].select.size();
		fwrite(&snum, sizeof(int), 1, fd);
		for (int j = 0; j < snum; j++)
			fwrite(&(students[i].select[j]), sizeof(unsigned int), 1, fd);

		//qDebug("Student: %s %d\n", students[i].student_name, students[i].student_num);
	}
}

void Quit()
{
	save();
}

//read all information from my_data.mdt
void read_information()
{
	//read provost's password
	fread(pw, 1, PW_N, fd);

	//read courses' information
	int num;
	fread(&num, sizeof(int), 1, fd);

	Course ctmp;
	for (int i = 0; i < num; i++)
	{
		memset(&ctmp, 0, sizeof(struct Course));
		ctmp.students.clear();
		fread(&ctmp.course_num, sizeof(unsigned int), 1, fd);
		fread(ctmp.course_name, 1, COURSE_NAME_N, fd);
		//fread(&ctmp.student_count, sizeof(unsigned), 1, fd);
		int snum;
		unsigned int student_tmp;
		fread(&snum, sizeof(int), 1, fd);
		for (int j = 0; j < snum; j++)
		{
			fread(&student_tmp, sizeof(unsigned int), 1, fd);
			ctmp.students.push_back(student_tmp);
		}
		courses.push_back(ctmp);
		//qDebug("Course: %s %d\n", ctmp.course_name, ctmp.course_num);
	}

	//read students' informaiton
	Student stmp;
	fread(&num, sizeof(int), 1, fd);
	for (int i = 0; i < num; i++)
	{
		memset(&stmp, 0, sizeof(struct Student));
		stmp.select.clear();
		fread(&stmp.student_num, sizeof(unsigned int), 1, fd);
		fread(stmp.student_name, 1, NAME_N, fd);
		fread(stmp.college, 1, COLLEGE_N, fd);
		fread(stmp.pw, 1, PW_N, fd);
		int snum;
		unsigned int course_tmp;
		fread(&snum, sizeof(int), 1, fd);
		for (int j = 0; j < snum; j++)
		{
			fread(&course_tmp, sizeof(unsigned int), 1, fd);
			stmp.select.push_back(course_tmp);
		}
		students.push_back(stmp);
		//qDebug("Student: %s %d\n", stmp.student_name, stmp.student_num);
	}
}

vector<Student>::iterator get_student(string inf)
{
	if (inf[0] > '9')
		return find_if(students.begin(), students.end(), find_name(inf));
	else
		return find_if(students.begin(), students.end(), find_number(atoi(inf.c_str())));
}

vector<Student>::iterator get_student(unsigned int inf)
{
	return find_if(students.begin(), students.end(), find_number(inf));
}

bool isNum(string s)
{
	stringstream sin(s);
	double t;
	char p;
	if (!(sin >> t))
		return false;
	if (sin >> p)
		return false;
	else
		return true;
}


string get_course_name(unsigned int tnum)
{
	vector<Course>::iterator t = find_if(courses.begin(), courses.end(), find_number(tnum));
	if (t != courses.end())
		return t->course_name;
	else return NULL;
}


unsigned int get_course_num(string tname)
{
	vector<Course>::iterator t = find_if(courses.begin(), courses.end(), find_name(tname));
	if (t != courses.end())
		return t->course_num;
	else return 0;
}

vector<Course>::iterator get_course(string inf)
{
	if (inf[0] > '9')
		return find_if(courses.begin(), courses.end(), find_name(inf));
	else
		return find_if(courses.begin(), courses.end(), find_number(atoi(inf.c_str())));
}

vector<Course>::iterator get_course(unsigned int cnum)
{
	return find_if(courses.begin(), courses.end(), find_number(cnum));
}

int error_count = 0;

void change_s_course(Course *c, int flag, unsigned int course_num)
{
	int c_s_num = c->students.size();
	int c_num = c->course_num;
	vector<unsigned int>::iterator t;
	for (int i = 0; i < c_s_num; i++)
	{
		Student *stmp = &*get_student(c->students[i]);
		if ((t = find(stmp->select.begin(), stmp->select.end(), c_num)) != stmp->select.end())
		{
			if (flag == 1)
				stmp->select.erase(t);
			else
				*t = course_num;
		}
		else error_count++;
	}
	//qDebug("ERROR: %d", error_count);
}


/*
 * 生成数据
 */

char gbuf[100];
char spw[] = "123456";
void generate_data()
{
	Student stmp;
	Course ctmp;
	srand((unsigned)time(NULL));
	char cname[15] = "cs";

	for (int i = 0; i < 5; i++) //课程
	{
		cname[2] = '\0';
		int tmp = i + 15213 + rand();
		itoa(tmp, buf, 10);
		strcat(cname, buf);
		ctmp.set_name(cname);
		ctmp.set_num(tmp);
		ctmp.students.clear();
		courses.push_back(ctmp);
	}
	sort(courses.begin(), courses.end(), cmp_course_num);

	for (int i = 0; i < 5000; i++) //学生
	{
		int std_num = 140000000;
		int name = 100000 + i;
		int college = rand();
		itoa(name, buf, 10);
		stmp.set_name(buf);
		itoa(college, buf, 10);
		stmp.set_college(buf);
		stmp.set_num(std_num + name);
		stmp.set_pw(spw);
		stmp.select.clear();
		students.push_back(stmp);
	}
	sort(students.begin(), students.end(), cmp_student_num);

	for (int i = 0; i < 5000; i++)
	{
		for (int t = 0; t < courses.size(); t++)
		{
			if (rand()%20 < 4)
			{
				students[i].select.push_back(courses[t].course_num);
				courses[t].students.push_back(students[i].student_num);
				/*qDebug("Course: %d Student: %d", courses[t].course_num, students[i].student_num);
				if (students[i].select.size())
					qDebug("1   Student: %d Number: %d", students[i].student_num, students[i].select.size());*/
			}
		}
	}

	for (int t = 0; t < courses.size(); t++)
		sort(courses[t].students.begin(), courses[t].students.end());
	
	save();
}