#pragma once

/*
 * For emitting a message box
 */

#include <QMessageBox>
#include <cstring>
#include <QApplication>

static void myMessageBox(QString s)
{
	QApplication::setQuitOnLastWindowClosed(false);
	QMessageBox::warning(NULL, "Message", s, QMessageBox::Ok, QMessageBox::Ok);
	QApplication::setQuitOnLastWindowClosed(true);
}