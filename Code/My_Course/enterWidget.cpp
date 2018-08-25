#include "enterWidget.h"
#include "my_course.h"
#include "my_message.h"

extern char pw[PW_N];
extern vector<Student>students;	//全部学生
extern vector<Course>courses;
extern Student *current_student;

/*
 * UI
 */

My_Course::My_Course(QWidget *parent) : QMainWindow(parent)
{
	provost = new Provost(this);
	student = new Students(this);
	rg = new Register(this);
	setWindowIcon(QIcon(":/Resources/windows.png"));
	uie.setupUi(this);
	uie.lineEdit_pw->setEchoMode(QLineEdit::Password);
	setFixedSize(180, 260);
	/* Signals */
	connect(uie.pushButton_enter0, SIGNAL(clicked()), this, SLOT(pushButton_enter0_clicked()));
	connect(uie.pushButton_quit0, SIGNAL(clicked()), this, SLOT(pushButton_quit0_clicked()));
	connect(uie.pushButton_register, SIGNAL(clicked()), this, SLOT(pushButton_register_clicked()));
	connect(uie.radioButton_student, SIGNAL(clicked()), this, SLOT(radioButton_student_clicked()));
	connect(uie.radioButton_provost, SIGNAL(clicked()), this, SLOT(radioButton_provost_clicked()));
}

/*
 * SLOT Functions
 */

void My_Course::pushButton_enter0_clicked()
{
	//provost->show();
	sign_in();
}

void My_Course::pushButton_quit0_clicked()
{
	save();
	students.clear();
	courses.clear();
	if (provost)
		delete provost;	
	if (rg)
		delete rg;
	if (student)
		delete student;
	provost = NULL;
	rg = NULL;
	student = NULL;
	this->close();
}

void My_Course::pushButton_register_clicked()
{
	rg->init();
	rg->show();
}

void My_Course::radioButton_provost_clicked()
{
	uie.label_3->setText(u8"教务登录：");
	uie.lineEdit_std_num->setText(u8"输入密码即可");
	uie.lineEdit_std_num->setEnabled(false);
}

void My_Course::radioButton_student_clicked()
{
	uie.lineEdit_std_num->setEnabled(true);
	uie.lineEdit_std_num->clear();
	uie.label_3->setText(u8"学号：");
}


/*
 * 登录
 */

void My_Course::sign_in()
{
	if (uie.radioButton_provost->isChecked() == 1)
	/* Provost */
	{
		if (uie.lineEdit_pw->text().length() == 0)
			myMessageBox("Empty password.");

		else if (uie.lineEdit_pw->text().compare(pw) != 0)
		{
			myMessageBox("Wrong password.");
			this->uie.lineEdit_pw->clear();
		}

		else
		{
			this->uie.lineEdit_pw->clear();
			this->uie.lineEdit_std_num->clear();
			provost->print_all_courses();
			provost->show();
			//this->hide();
		}
	}
	else
	/* Student */
	{
		vector<Student>::iterator t;
		if ((t = get_student(uie.lineEdit_std_num->text().toStdString())) == students.end())
		{
			myMessageBox("No such student.");
			this->uie.lineEdit_std_num->clear();
			this->uie.lineEdit_pw->clear();
		}

		else
		{
			if (uie.lineEdit_pw->text().length() == 0)
				myMessageBox("Empty password.");

			else if (uie.lineEdit_pw->text().compare(t->pw) == 0)
			{
				this->uie.lineEdit_pw->clear();
				//this->hide();
				/* Set current student */
				current_student = &(*t);
				student->set_inf();
				student->print_all_courses();
				student->print_selected_courses();
				student->show();
			}

			else
			{
				myMessageBox("Wrong password.");
				this->uie.lineEdit_pw->clear();
			}
		}
	}
}