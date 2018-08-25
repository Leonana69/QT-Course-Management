#include "register.h"
#include "enterWidget.h"
#include "my_course.h"
#include "my_message.h"

extern vector<Student>students;

Register::Register(QWidget *parent) : QDialog(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	setFixedSize(180, 290);
	uir.setupUi(this);
	/* Set lineEdit mode */
	uir.lineEdit_pw->setEchoMode(QLineEdit::Password);
	/* Signals */
	connect(uir.pushButton_register1, SIGNAL(clicked()), this, SLOT(pushButton_register1_clicked()));
	connect(uir.pushButton_return1, SIGNAL(clicked()), this, SLOT(pushButton_return1_clicked()));
	connect(uir.lineEdit_std_num, SIGNAL(editingFinished()), this, SLOT(lineEdit_std_num_finished()));	
}

void Register::init()
{
	/* Clear all lineEdit */
	uir.label_inf->clear();
	uir.lineEdit_pw->clear();
	uir.lineEdit_std_college->clear();
	uir.lineEdit_std_name->clear();
	uir.lineEdit_std_num->clear();
}

void Register::pushButton_register1_clicked()
{
	Student stmp;
	if (empty_flag)
		QMessageBox::warning(NULL, "Message", "Empty student number.", QMessageBox::Ok, QMessageBox::Ok);
	else if (already_flag)
		QMessageBox::warning(NULL, "Message", "Number already registed.", QMessageBox::Ok, QMessageBox::Ok);
	else if (legal_flag)
		QMessageBox::warning(NULL, "Message", "Illegal number.", QMessageBox::Ok, QMessageBox::Ok);
	else
	{
		/* Set temp variable informations */
		stmp.set_num(atoi(uir.lineEdit_std_num->text().toStdString().c_str()));
		stmp.set_name(uir.lineEdit_std_name->text().toStdString().c_str());
		stmp.set_college(uir.lineEdit_std_college->text().toStdString().c_str());
		stmp.set_pw(uir.lineEdit_pw->text().toStdString().c_str());
		stmp.select.clear();
		/* Add to student list */
		students.push_back(stmp);
		QMessageBox::warning(NULL, "Message", "Register success.", QMessageBox::Ok, QMessageBox::Ok);
		/* Re-sort and save */
		sort(students.begin(), students.end(), cmp_student_num);
		save();
		close();
	}
	return;
}

void Register::pushButton_return1_clicked()
{
	this->close();
}

/* Judge if the student number is legal */
void Register::lineEdit_std_num_finished()
{
	int len = uir.lineEdit_std_num->text().length();
	if (len == 0) /* Empty input */
	{
		uir.label_inf->setText(u8"学号不能为空!");
		empty_flag = 1;
		already_flag = 0;
	}

	else
	{
		unsigned int snum;
		if (!isNum(uir.lineEdit_std_num->text().toStdString()))
		{
			uir.label_inf->setText(u8"学号必须是纯数字");
			legal_flag = 1;
		}

		else
		{
			snum = atoi(uir.lineEdit_std_num->text().toStdString().c_str());
			empty_flag = 0;
			legal_flag = 0;
			vector<Student>::iterator t;
			if ((t = get_student(snum)) != students.end()) /* Find in student list */
			{
				uir.label_inf->setText(u8"学号已被注册");
				already_flag = 1;
				uir.lineEdit_std_num->clear();
			}
			else
			{
				uir.label_inf->clear();
				already_flag = 0;
			}
		}	
	}
}