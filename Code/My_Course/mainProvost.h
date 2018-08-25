#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_mainProvost.h"
#include "change_pw.h"
#include "add_course.h"
#include "modify_course.h"
#include "check_course.h"

/*
 * Provost functions
 */

class Provost : public QMainWindow
{
	Q_OBJECT

public:
	Provost(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;
	void print_all_courses();
	int get_column();

	private slots:
	void pushButton_add_clicked();
	void pushButton_delete_clicked();
	void pushButton_modify_clicked();
	void pushButton_return0_clicked();
	void pushButton_pw_clicked();
	void add_course_complete();
	void modify_course_complete();
	void pushButton_check_clicked();

private:
	Change_pw *cp;
	Add_course *ac;
	Modify *md;
	Check_course *ck;
	Ui::Provost_MainWindow uip;
};
