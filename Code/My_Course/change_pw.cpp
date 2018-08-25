#include "change_pw.h"
#include "my_course.h"
#include "my_message.h"

extern char pw[PW_N];

Change_pw::Change_pw(QWidget *parent) : QDialog(parent)
{
	parentWindow = parent;
	setWindowIcon(QIcon(":/Resources/windows.png"));
	setFixedSize(180, 145);
	uic.setupUi(this);
	/* Set lineEdit mode */
	uic.lineEdit_pw1->setEchoMode(QLineEdit::Password);
	uic.lineEdit_pw2->setEchoMode(QLineEdit::Password);
	/* Signals */
	connect(uic.pushButton_enter, SIGNAL(clicked()), this, SLOT(pushButton_enter_clicked()));
	connect(uic.pushButton_return, SIGNAL(clicked()), this, SLOT(pushButton_return_clicked()));
}

void Change_pw::pushButton_enter_clicked()
{
	if (uic.lineEdit_pw1->text().compare(uic.lineEdit_pw2->text()) != 0)
	{
		myMessageBox("Two passwords are not same.");
		uic.lineEdit_pw2->clear();
	}

	else if (uic.lineEdit_pw1->text().length() == 0)
		myMessageBox("Empty input.");

	else
	{
		strncpy(pw, uic.lineEdit_pw1->text().toStdString().c_str(), PW_N);
		myMessageBox("Changin password success.");
		save();
		this->close();
	}
}

void Change_pw::pushButton_return_clicked()
{
	this->close();
}