#pragma once

/*
 * "Add course" window
 */

#include "ui_add_course.h"
#include <QtWidgets/QMainWindow>

class Add_course : public QDialog
{
	Q_OBJECT

public:
	Add_course(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;

	private slots:
	void pushButton_enter_clicked();
	void pushButton_return_clicked();

signals:
	void add_course_event();

private:
	int equal_flag;
	Ui::add_course_Dialog uia;
};
