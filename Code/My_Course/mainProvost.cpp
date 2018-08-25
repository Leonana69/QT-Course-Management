#include "mainProvost.h"
#include "my_course.h"
#include "my_message.h"

extern vector<Course>courses;
extern vector<Student>students;
extern Course *current_course;
extern char buf[100];

/*
 * UI
 */

Provost::Provost(QWidget *parent) : QMainWindow(parent)
{
	parentWindow = parent;
	cp = NULL;
	ac = NULL;
	md = NULL;
	ck = NULL;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	resize(880, 615);
	uip.setupUi(this);
	/* Signals */
	connect(uip.pushButton_add, SIGNAL(clicked()), this, SLOT(pushButton_add_clicked()));
	connect(uip.pushButton_delete, SIGNAL(clicked()), this, SLOT(pushButton_delete_clicked()));
	connect(uip.pushButton_modify, SIGNAL(clicked()), this, SLOT(pushButton_modify_clicked()));
	connect(uip.pushButton_pw, SIGNAL(clicked()), this, SLOT(pushButton_pw_clicked()));
	connect(uip.pushButton_return0, SIGNAL(clicked()), this, SLOT(pushButton_return0_clicked()));
	connect(uip.pushButton_check, SIGNAL(clicked()), this, SLOT(pushButton_check_clicked()));
}

void Provost::add_course_complete()
{
	print_all_courses();
}

void Provost::modify_course_complete()
{
	print_all_courses();
}

void Provost::pushButton_add_clicked()
{
	ac = new Add_course(this);
	connect(ac, SIGNAL(add_course_event()), this, SLOT(add_course_complete()));
	ac->show();
}

/* 获取当前列号 */
int Provost::get_column()
{
	QList<QTableWidgetSelectionRange>ranges = uip.tableWidget_all_courses->selectedRanges();
	int count = ranges.count();
	if (count == 0)
	{
		myMessageBox(u8"请选中课程");
		return -1;
	}
	int right = ranges.at(0).rightColumn();
	int left = ranges.at(0).leftColumn();
	if (right < 3 || ranges.at(0).topRow() > 0 || ranges.at(0).bottomRow() != students.size() - 1)
	{
		myMessageBox(u8"请选择课程名");
		return -1;
	}
		
	else if (count > 1 || right != left)
	{
		myMessageBox(u8"只能选中一门课程");
		return -1;
	}
		
	else return right - 3; //前三列为学生信息
}

void Provost::pushButton_delete_clicked()
{
	int column = get_column();
	if (column >= 0)
	{
		change_s_course(&courses[column], 1);
		//qDebug("%s\n", (courses.begin() + (right - 3))->course_name);
		courses.erase(courses.begin() + column);
		sort(courses.begin(), courses.end(), cmp_course_num);
		save();
		print_all_courses();
		myMessageBox(u8"删除成功");
	}
}

void Provost::pushButton_modify_clicked()
{
	int column = get_column();
	if (column >= 0)
	{
		/* Set current student */
		current_course = &*(courses.begin() + column);
		md = new Modify(this);
		connect(md, SIGNAL(modify_course_event()), this, SLOT(modify_course_complete()));
		md->show();
	}
}

void Provost::pushButton_check_clicked()
{
	int column = get_column();
	if (column >= 0)
	{
		/* Set current student */
		current_course = &*(courses.begin() + column);
		ck = new Check_course(this);
		ck->show();
	}
}

void Provost::pushButton_pw_clicked()
{
	cp = new Change_pw(this);
	cp->show();
}

void Provost::pushButton_return0_clicked()
{
	save();
	parentWindow->show();
	if (cp != NULL)
		delete cp;
	if (ac != NULL)
		delete ac;
	if (md != NULL)
		delete md;
	if (ck != NULL)
		delete ck;
	cp = NULL;
	ac = NULL;
	md = NULL;
	ck = NULL;
	this->close();
}

void Provost::print_all_courses()
{
	int c_num = courses.size();
	int s_num = students.size();
	uip.tableWidget_all_courses->setColumnCount(3 + c_num);
	uip.tableWidget_all_courses->setRowCount(s_num);
	uip.tableWidget_all_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList headers;
	headers << u8"学号" << u8"姓名" << u8"院系";
	for (int i = 0; i < c_num; i++)
		headers << courses[i].course_name;	
	uip.tableWidget_all_courses->setHorizontalHeaderLabels(headers);

	if (s_num == 0)
	{
		uip.tableWidget_all_courses->setRowCount(1);
		uip.tableWidget_all_courses->setItem(0, 0, new QTableWidgetItem("No student yet"));
	}
		
	else
	{
		vector<unsigned int>::iterator t;
		for (int i = 0; i < s_num; i++)
		{
			/* 打印tableWidget */
			itoa(students[i].student_num, buf, 10);
			uip.tableWidget_all_courses->setItem(i, 0, new QTableWidgetItem(buf));
			uip.tableWidget_all_courses->setItem(i, 1, new QTableWidgetItem(students[i].student_name));
			uip.tableWidget_all_courses->setItem(i, 2, new QTableWidgetItem(students[i].college));
			//qDebug("%s %s %s\n", buf, students[i].student_name, students[i].college);
			for (int j = 0; j < c_num; j++)
			{
				if ((t = std::find(students[i].select.begin(), students[i].select.end(),
					courses[j].course_num)) != students[i].select.end())
					uip.tableWidget_all_courses->setItem(i, j + 3, new QTableWidgetItem("Yes"));
				else
					uip.tableWidget_all_courses->setItem(i, j + 3, new QTableWidgetItem("-"));
			}
		}
	}
	uip.tableWidget_all_courses->show();
}