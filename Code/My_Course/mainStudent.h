#pragma once

/*
 * Student functions
 */

#include <QtWidgets/QMainWindow>
#include "ui_mainStudent.h"

class Students : public QMainWindow
{
	Q_OBJECT

public:
	Students(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;
	void set_inf();
	void print_selected_courses();
	void print_all_courses();
	int get_row(int);

	private slots:
	void pushButton_return_clicked();
	void pushButton_select_clicked();
	void pushButton_withdraw_clicked();

private:
	Ui::Students_MainWindow uis;
};
