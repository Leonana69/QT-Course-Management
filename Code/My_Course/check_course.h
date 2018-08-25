#pragma once

/*
 * "Check course" window
 */

#include "ui_check_course.h"
#include <QtWidgets/QMainWindow>

class Check_course : public QDialog
{
	Q_OBJECT

public:
	Check_course(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;
	void print_current_course();

	private slots:
	void pushButton_return_clicked();

private:
	int equal_flag;
	Ui::check_Dialog uik;
};
