#ifndef REGUSER_HPP_INCLUDED
#define REGUSER_HPP_INCLUDED

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include "ui_reguser.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLocale>
#include <QTranslator>
#include <QTextCodec>
#include <QMessageBox>
#include <QCloseEvent>
#include <QProcess>
#include <QDesktopServices>
#include <QSettings>
#ifdef ENABLE_DEBUG
	#include <QDebug>
#endif
#ifdef WIN32
	#include <windows.h>
#endif

namespace Ui {
	class MainWindow;
};


class RegUser : public QMainWindow {
Q_OBJECT
	private:
		Ui::MainWindow *ui;
		QSettings RegEdit;
	public:
		RegUser (QWidget *parent = 0);
		virtual ~RegUser ();
	protected:
		void Centre ();
	protected slots:
		void onSave();
		void onAbout ();
};

#endif
