#ifndef ALARM_HH_INCLUDED
#define ALARM_HH_INCLUDED

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include "ui_alarm.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLocale>
#include <QLibraryInfo>
#include <QTranslator>
#include <QTextCodec>
#include <QMessageBox>
#include <QCloseEvent>
#include <QProcess>
#include <QDesktopServices>
#include <QSystemTrayIcon>
#include <Phonon/MediaObject>
#include <Phonon/MediaSource>
#include <QTimer>
#include <QUrl>
#include "pref.hh"

#ifdef WIN32
#include <windows.h>
#endif

#ifdef ENABLE_DEBUG
	#include <QDebug>
#endif

namespace Ui {
	class MainWindow;
};

class AlarmUI : public QMainWindow {
Q_OBJECT
	private:
		Ui::MainWindow *ui;
		QSystemTrayIcon *tray_icon;
		Phonon::MediaObject *m_sound;
		PrefDialog *pref;
		QTimer *m_timer;
		int timeout;
		bool use_notify;
		bool use_sound;
		bool use_reset;
		int sec;
		int min;
		int m_lang_index;
		QTranslator *m_qt_trans;
		QTranslator *m_pro_trans;
	public:
		AlarmUI (QTranslator *, QTranslator *, QWidget *parent = 0);
		virtual ~AlarmUI ();
	protected:
		void Centre ();
		void toggleui (bool);
		void updateTimeLabel ();
		void localeMe ();
		virtual void changeEvent (QEvent *);
		virtual void closeEvent (QCloseEvent *);
	protected slots:
		void trayiconActivated (QSystemTrayIcon::ActivationReason);
		void onStart ();
		void onAboutQt ();
		void onProject ();
		void onPref ();
		void onAbout ();
		void tick ();
		void onFinishedSound ();
};

#endif
