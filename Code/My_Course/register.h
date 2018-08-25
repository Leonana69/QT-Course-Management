#pragma once

/*
 * "Register" window
 */

#include <QtWidgets/QMainWindow>
#include "ui_register.h"

class Register : public QDialog
{
	Q_OBJECT

public:
	Register(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;
	void init();

	private slots:
	void pushButton_register1_clicked();
	void pushButton_return1_clicked();
	void lineEdit_std_num_finished();
	
private:
	int empty_flag;
	int already_flag;
	int legal_flag;
	Ui::Register_Dialog uir;
};
