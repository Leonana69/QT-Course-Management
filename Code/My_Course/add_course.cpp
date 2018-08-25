#include "add_course.h"
#include "enterWidget.h"
#include "my_course.h"
#include "my_message.h"
#include <qdebug.h>

/* Extern variables */
extern vector<Course>courses;

/* Add_course init function */
Add_course::Add_course(QWidget *parent) : QDialog(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	setFixedSize(180, 145);
	uia.setupUi(this);
	/* Signals */
	connect(uia.pushButton_enter, SIGNAL(clicked()), this, SLOT(pushButton_enter_clicked()));
	connect(uia.pushButton_return, SIGNAL(clicked()), this, SLOT(pushButton_return_clicked()));
}

void Add_course::pushButton_enter_clicked()
{
	if (uia.lineEdit_name->text().length() == 0 || uia.lineEdit_num->text().length() == 0)
		myMessageBox(u8"信息不准为空");

	else if (get_course(uia.lineEdit_name->text().toStdString()) != courses.end()
		|| get_course(uia.lineEdit_num->text().toStdString()) != courses.end())
		myMessageBox(u8"课程号或课程名重复");

	else if (!isNum(uia.lineEdit_num->text().toStdString()))
		myMessageBox(u8"课程号必须为数字");

	else
	{
		Course *ctmp = new Course;
		ctmp->set_name(uia.lineEdit_name->text().toStdString().c_str());
		ctmp->set_num(atoi(uia.lineEdit_num->text().toStdString().c_str()));
		ctmp->students.clear();
		courses.push_back(*ctmp);
		//qDebug("Name: %s, Number: %d\n", ctmp->course_name, ctmp->course_num);
		/* Re-sort and save */
		sort(courses.begin(), courses.end(), cmp_course_num);
		save();
		/* Inform provost window of the change */
		emit add_course_event();
		this->close();
		myMessageBox(u8"添加成功");
	}
}

void Add_course::pushButton_return_clicked()
{
	this->close();
}