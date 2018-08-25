#pragma once

/*
 * Change provost's password window
 */

#include "ui_change_pw.h"
#include <QtWidgets/QMainWindow>

class Change_pw : public QDialog
{
	Q_OBJECT

public:
	Change_pw(QWidget *parent = Q_NULLPTR);
	QWidget *parentWindow;

	private slots:
	void pushButton_enter_clicked();
	void pushButton_return_clicked();

private:
	int equal_flag;
	Ui::Change_Dialog uic;
};
