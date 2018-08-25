#include "check_course.h"
#include "my_course.h"

extern vector<Student>students;
extern Course *current_course;
extern char buf[100];

Check_course::Check_course(QWidget *parent) : QDialog(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	setFixedSize(370, 540);
	uik.setupUi(this);
	/* Signals */
	connect(uik.pushButton_return, SIGNAL(clicked()), this, SLOT(pushButton_return_clicked()));
	print_current_course();
}

void Check_course::pushButton_return_clicked()
{
	this->close();
}

void Check_course::print_current_course()
{
	/* Print current course informations */
	uik.label_name->setText(current_course->course_name);
	itoa(current_course->course_num, buf, 10);
	uik.label_num->setText(buf);
	/* Find all students who have chosen the course */
	int s_num = current_course->students.size();
	/* Setup tableWidget */
	uik.tableWidget->setColumnCount(3);
	uik.tableWidget->setRowCount(s_num);
	uik.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	QStringList headers;
	headers << u8"学号" << u8"姓名" << u8"院系";
	uik.tableWidget->setHorizontalHeaderLabels(headers);
	/* Print the number of students who have chosen the course */
	itoa(s_num, buf, 10);
	uik.label_std_count->setText(QString(buf));

	if (s_num == 0) /* No student */
	{
		uik.tableWidget->setRowCount(1);
		uik.tableWidget->setItem(0, 0, new QTableWidgetItem("No student yet"));
	}

	else
	{
		vector<Student>::iterator t;
		for (int i = 0; i < s_num; i++)
		{
			t = get_student(current_course->students[i]);
			itoa(t->student_num, buf, 10);
			uik.tableWidget->setItem(i, 0, new QTableWidgetItem(buf));
			uik.tableWidget->setItem(i, 1, new QTableWidgetItem(t->student_name));
			uik.tableWidget->setItem(i, 2, new QTableWidgetItem(t->college));
		}
	}
}