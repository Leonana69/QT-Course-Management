#include "modify_course.h"
#include "my_course.h"
#include "my_message.h"

extern vector<Course>courses;
extern Course *current_course;
extern char buf[100];

Modify::Modify(QWidget *parent) : QDialog(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	setFixedSize(180, 145);
	uim.setupUi(this);
	/* Print some informations */
	uim.label_name->setText(QString(u8"当前课程：") + (QString)current_course->course_name);
	QString qs = u8"当前课程号：";
	itoa(current_course->course_num, buf, 10);
	qs += QString(buf);
	uim.label_num->setText(qs);
	/* Signals */
	connect(uim.pushButton_enter, SIGNAL(clicked()), this, SLOT(pushButton_enter_clicked()));
	connect(uim.pushButton_return, SIGNAL(clicked()), this, SLOT(pushButton_return_clicked()));
}

void Modify::pushButton_enter_clicked()
{
	if (uim.lineEdit_name->text().length() == 0 && uim.lineEdit_num->text().length() == 0)
	/* No input */
	{
		myMessageBox(u8"未做修改");
		close();
	}
	
	if (get_course(uim.lineEdit_name->text().toStdString()) != courses.end()
		|| get_course(uim.lineEdit_num->text().toStdString()) != courses.end())
	/* Already existed */
		myMessageBox(u8"课程号或课程名重复");

	else
	{
		if (uim.lineEdit_name->text().length() != 0) /* Set course name */
			current_course->set_name(uim.lineEdit_name->text().toStdString().c_str());
		if (uim.lineEdit_num->text().length() != 0) /* Modify course number and change the course number of every student who has chosen the course */
		{
			change_s_course(current_course, 2, atoi(uim.lineEdit_num->text().toStdString().c_str()));
			current_course->set_num(atoi(uim.lineEdit_num->text().toStdString().c_str()));
		}
		/* Re-sort and save */
		sort(courses.begin(), courses.end(), cmp_course_num);
		save();
		myMessageBox(u8"修改成功");
		/* Inform provost window of the change */
		emit modify_course_event();
		close();
	}
}

void Modify::pushButton_return_clicked()
{
	this->close();
}