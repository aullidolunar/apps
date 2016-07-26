#ifndef FORM_HXX_INC
#define FORM_HXX_INC

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <QSystemTrayIcon>
#include <QTimer>
#include <Phonon/MediaObject>
#include <Phonon/MediaSource>
#include <QDesktopWidget>
#include <QMessageBox>
#include <QFile>
#include "ui_Alarm.h"

enum TIP_MESSAGES {
	ALARM_ON, ALARM_OFF
};

class MySubClassedTrayIcon : public QSystemTrayIcon
{
private:
	Q_OBJECT
	QMenu *m_menuAlarm;
	QMainWindow *m_toplevel;
	QTimer m_timeBlink;
	bool isBlinking;
	bool blinkMotion;
public:
	MySubClassedTrayIcon (QWidget * parent = 0);
	void setAlarmMenu (QMenu *);
	void setToplevel (QMainWindow *);
	void sendNotifications (bool checked = false, bool actionStart = true);
	void sendBlink (bool checked = false);
protected:
	void startBlinking (bool start = true);
protected slots:
	void cb_trayiconActivated (QSystemTrayIcon::ActivationReason);
	void cb_blink ();
signals:
	void trayClicked();
};

class MyForm : public QMainWindow
{
private:
	Q_OBJECT
	Ui::MainWindow ui;
	MySubClassedTrayIcon m_ticon;
	Phonon::MediaObject *m_mobj;
	QTimer m_timer;
	int seconds;
	int minutes;
	int maximum;
public:
	MyForm (QWidget *parent = 0);
	virtual ~MyForm ();
protected:
	virtual void changeEvent (QEvent *);
	virtual void closeEvent (QCloseEvent *);
	void sendSoundAlarm (bool checked = false);
protected slots:
	void cb_start_activate ();
	void cb_exit_activate ();
	void cb_about_activate ();
	void cb_aboutqt_activate ();
	void cb_tick ();
	void cb_traptrayClicked ();
};

#endif
