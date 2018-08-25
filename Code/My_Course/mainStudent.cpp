#include "mainStudent.h"
#include "my_course.h"
#include "my_message.h"

extern Student *current_student;
extern vector<Course>courses; 		//全部课程 
extern vector<Student>students;	//全部学生
extern char buf[100];

Students::Students(QWidget *parent) : QMainWindow(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	resize(570, 600);
	uis.setupUi(this);
	/* Signals */
	connect(uis.pushButton_return, SIGNAL(clicked()), this, SLOT(pushButton_return_clicked()));
	connect(uis.pushButton_select, SIGNAL(clicked()), this, SLOT(pushButton_select_clicked()));
	connect(uis.pushButton_withdraw, SIGNAL(clicked()), this, SLOT(pushButton_withdraw_clicked()));
	connect(uis.tableWidget_all_courses, SIGNAL(itemPressed(QTableWidgetItem*)), uis.tableWidget_selected_courses, SLOT(clearSelection()));
	connect(uis.tableWidget_selected_courses, SIGNAL(itemPressed(QTableWidgetItem*)), uis.tableWidget_all_courses, SLOT(clearSelection()));
}

void Students::set_inf() //显示学生信息
{
	uis.label_std_name->setText(current_student->student_name);
	itoa(current_student->student_num, buf, 10);
	uis.label_std_num->setText(buf);
	uis.label_std_college->setText(current_student->college);
}

void Students::pushButton_return_clicked()
{
	save();
	parentWindow->show();
	this->close();
}

int Students::get_row(int flag)
{
	if (flag)
	{
		QList<QTableWidgetSelectionRange>ranges = uis.tableWidget_all_courses->selectedRanges();
		int count = ranges.count();
		if (count == 0)
		{
			myMessageBox(u8"请选中右边的课程");
			return -1;
		}
		int top = ranges.at(0).topRow();
		int botton = ranges.at(0).bottomRow();
		int left = ranges.at(0).leftColumn();
		int right = ranges.at(0).rightColumn();

		if (count > 1 || botton != top)
		{
			myMessageBox(u8"只能选中一门课程");
			return -1;
		}

		else if ((right == left && left == 2) || (right - left) == 1)
		{
			myMessageBox(u8"请选择课程名或课程号");
			return -1;
		}

		else
			return top;
	}
	else
	{
		QList<QTableWidgetSelectionRange>ranges = uis.tableWidget_selected_courses->selectedRanges();
		int count = ranges.count();
		if (count == 0)
		{
			myMessageBox(u8"请选中左边的课程");
			return -1;
		}
		int top = ranges.at(0).topRow();
		int botton = ranges.at(0).bottomRow();
		if (count > 1 || botton != top)
		{
			myMessageBox(u8"只能选中一门课程");
			return -1;
		}
		else
			return top;
	}
}

void Students::pushButton_select_clicked()
{
	int row = get_row(1);
	if (row < 0)
		return;
	vector<unsigned int>::iterator t = std::find(current_student->select.begin(), current_student->select.end(), courses[row].course_num);
	if (t != current_student->select.end())
	{
		myMessageBox(u8"已选了该课程");
		return;
	}
	//courses[row].student_count++;
	courses[row].students.push_back(current_student->student_num);//
	sort(courses[row].students.begin(), courses[row].students.end());//
	current_student->select.push_back(courses[row].course_num);
	sort(current_student->select.begin(), current_student->select.end());
	save();
	print_all_courses();
	print_selected_courses();
	myMessageBox(u8"选课成功");
}

void Students::pushButton_withdraw_clicked()
{
	if (current_student->select.size() == 0)
	{
		myMessageBox(u8"未选课");
		return;
	}
	int row = get_row(0);
	if (row < 0)
		return;
	//((get_course(current_student->select[row]))->student_count)--;
	vector<unsigned int>* t = &(get_course(current_student->select[row]))->students;//
	t->erase(std::find(t->begin(), t->end(), current_student->student_num));//

	current_student->select.erase(current_student->select.begin() + row);
	sort(current_student->select.begin(), current_student->select.end());
	save();
	print_all_courses();
	print_selected_courses();
	myMessageBox(u8"退课成功");
}

void Students::print_all_courses()
{
	int c_num = courses.size();
	uis.tableWidget_all_courses->setColumnCount(3);
	uis.tableWidget_all_courses->setRowCount(c_num);
	uis.tableWidget_all_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList headers;
	headers << u8"课程号" << u8"课程名" << u8"已选人数";
	uis.tableWidget_all_courses->setHorizontalHeaderLabels(headers);
	for (int i = 0; i < c_num; i++)
	{
		itoa(courses[i].course_num, buf, 10);
		uis.tableWidget_all_courses->setItem(i, 0, new QTableWidgetItem(buf));
		uis.tableWidget_all_courses->setItem(i, 1, new QTableWidgetItem(courses[i].course_name));
		itoa(courses[i].students.size(), buf, 10);
		uis.tableWidget_all_courses->setItem(i, 2, new QTableWidgetItem(buf));
	}
	
	uis.tableWidget_all_courses->show();
}

void Students::print_selected_courses()
{
	int c_num = current_student->select.size();
	uis.tableWidget_selected_courses->setColumnCount(1);
	uis.tableWidget_selected_courses->setRowCount(c_num);
	uis.tableWidget_selected_courses->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList headers;
	headers << u8"课程名";
	uis.tableWidget_selected_courses->setHorizontalHeaderLabels(headers);
	if (c_num == 0)
	{
		uis.tableWidget_selected_courses->setRowCount(1);
		uis.tableWidget_selected_courses->setItem(0, 0, new QTableWidgetItem(u8"未选课"));
	}
	else
		for (int i = 0; i < c_num; i++)
			uis.tableWidget_selected_courses->setItem(i, 0, new QTableWidgetItem(get_course_name(current_student->select[i]).c_str()));
}