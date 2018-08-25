#pragma once

/*
 * First window for sign in
 */

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_enterWidget.h"
#include "mainProvost.h"
#include "mainStudent.h"
#include "register.h"

class My_Course : public QMainWindow
{
	Q_OBJECT

public:
	My_Course(QWidget *parent = Q_NULLPTR);
	void sign_in();

	private slots:
	void pushButton_enter0_clicked();
	void pushButton_quit0_clicked();
	void pushButton_register_clicked();
	void radioButton_student_clicked();
	void radioButton_provost_clicked();

private:
	Students *student;
	Provost *provost;
	Register *rg;
	Ui::MainWindow uie;
};
