#pragma once

/*
 * "Modify course" window
 */

#include <QtWidgets/QMainWindow>
#include "ui_modify_course.h"

class Modify : public QDialog
{
	Q_OBJECT

public:
	Modify(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;

	private slots:
	void pushButton_enter_clicked();
	void pushButton_return_clicked();

signals:
	void modify_course_event();

private:
	int equal_flag;
	Ui::modify_Dialog uim;
};
