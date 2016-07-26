#include "form.hxx"

const QString tipMessages[] = {
	QObject::tr("The alarm is running"),
	QObject::tr("The alarm is stopped")
};

MySubClassedTrayIcon::MySubClassedTrayIcon (QWidget *parent) : 
	QSystemTrayIcon (parent),
	m_timeBlink (parent)
{
	isBlinking = false;
	blinkMotion = false;
	setToolTip (QObject::tr(qPrintable(tipMessages[ALARM_OFF])));
	connect (this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(cb_trayiconActivated(QSystemTrayIcon::ActivationReason)));
	connect (&m_timeBlink, SIGNAL(timeout()), this, SLOT(cb_blink()));
}

void MySubClassedTrayIcon::setAlarmMenu (QMenu *am) {
	m_menuAlarm = am;
}

void MySubClassedTrayIcon::setToplevel (QMainWindow *p) {
	m_toplevel = p;
}

void MySubClassedTrayIcon::sendNotifications (bool checked, bool actionStart) {
	setToolTip (actionStart ? QObject::tr(qPrintable(tipMessages[ALARM_ON])) : QObject::tr(qPrintable(tipMessages[ALARM_OFF])));
	if (!checked) {
		showMessage (m_toplevel->windowTitle(), actionStart ? QObject::tr(qPrintable(tipMessages[ALARM_ON])) : QObject::tr(qPrintable(tipMessages[ALARM_OFF])), QSystemTrayIcon::Information);
	}
}

void MySubClassedTrayIcon::sendBlink (bool checked) {
	if (!checked) {
		startBlinking ();
	}
}

void MySubClassedTrayIcon::cb_blink () {
	setIcon (blinkMotion ? QIcon(":blink") : QIcon(":main"));
	blinkMotion = !blinkMotion;
}

void MySubClassedTrayIcon::startBlinking (bool start) {
	if (start) {
		m_timeBlink.start (700);
		isBlinking = true;
	} else {
		m_timeBlink.stop ();
		isBlinking = false;
		blinkMotion = false;
		setIcon (QIcon(":main"));
	}
}

void MySubClassedTrayIcon::cb_trayiconActivated (QSystemTrayIcon::ActivationReason reason) {
	emit trayClicked ();
	if (isBlinking) {
		startBlinking (false);
	}
	switch (reason) {
		case QSystemTrayIcon::Context: {
			m_menuAlarm->popup(QCursor::pos());
			break;
		}
		default: {
			if (m_toplevel->isVisible ()) {
				m_toplevel->hide ();
			} else {
				m_toplevel->showNormal ();
			}
			break;
		}
	}
}

MyForm::MyForm (QWidget *parent) : 
	QMainWindow(parent),
	m_timer (parent),
	m_ticon (parent)
{
	// init class stuff
	seconds = 0;
	minutes = 0;
	maximum = 0;
	// load ui fule	
	ui.setupUi (this);
	// window stuff
	setWindowTitle (PACKAGE_STRING);
	setWindowIcon (QIcon(":main"));
	// tray stuff
	m_ticon.setToplevel (this);
	m_ticon.setAlarmMenu (ui.menuAlarm);
	m_ticon.setIcon (windowIcon ());
	m_ticon.show ();
	
	m_mobj = Phonon::createPlayer(Phonon::MusicCategory);
	QFile *ogg_file = new QFile (":sound", this);
	m_mobj->setCurrentSource (Phonon::MediaSource(ogg_file));
	
	// connections
	connect (ui.action_Start, SIGNAL(triggered()), this, SLOT(cb_start_activate()));
	connect (ui.action_Exit, SIGNAL(triggered()), this, SLOT(cb_exit_activate()));
	connect (ui.action_About, SIGNAL(triggered()), this, SLOT(cb_about_activate()));
	connect (ui.actionAbout_qt, SIGNAL(triggered()), this, SLOT(cb_aboutqt_activate()));
	connect (&m_timer, SIGNAL(timeout()), this, SLOT(cb_tick()));
	connect (&m_ticon, SIGNAL (trayClicked()), this, SLOT (cb_traptrayClicked ()));
}

void MyForm::cb_start_activate () {
	bool state = ui.gb2->isEnabled();
	bool actionStart = false;
	if (state) {
		maximum = ui.time_sb->value ();
		m_timer.start (1000);
		actionStart = true;
		if (ui.reset_check->isChecked()) seconds = 0;
	} else {
		m_timer.stop ();
	}
	ui.gb2->setEnabled (!state);
	ui.action_Start->setText (!state ? tr("&Start") : tr("&Stop"));
	m_ticon.sendNotifications (ui.notify_check->isChecked(), actionStart);
}

void MyForm::cb_exit_activate () {
	close ();
}

void MyForm::cb_about_activate () {
	QString info = QString("%1\n%2 %3\n%4").arg(PACKAGE_STRING).arg(tr("utility alarm coded with qt")).arg(qVersion()).arg(tr("Created by Joel"));
	QMessageBox::about (this, QString("%1 %2").arg(tr("About")).arg(PACKAGE_NAME), info);
}

void MyForm::cb_aboutqt_activate () {
	QMessageBox::aboutQt (this, PACKAGE_STRING);
}

void MyForm::cb_tick () {
	seconds++;
	if (seconds == 60) {
		seconds = 0;
		minutes++;
	}
	if (minutes == maximum) {
		minutes = 0;
		m_timer.stop ();
		ui.gb2->setEnabled (true);
		ui.action_Start->setText (tr("&Start"));
		m_ticon.sendNotifications (ui.notify_check->isChecked(), false);
		m_ticon.sendBlink (ui.blink_check->isChecked());
		sendSoundAlarm (ui.sound_check->isChecked());
	}
	QString output = QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
	ui.time_label->setText (output);
}

void MyForm::closeEvent (QCloseEvent* event) {
	if (m_timer.isActive()) {
		int button_id = QMessageBox::information (this, windowTitle (), tr("The alarm is still active, do you want exit anyway?"), QMessageBox::Yes|QMessageBox::No, QMessageBox::No);
		if (button_id != QMessageBox::Yes) {
			event->ignore ();
		} else {
			event->accept();
		}
	} else {
		event->accept();
	}
}

void MyForm::changeEvent (QEvent *event) {
	switch (event->type()) {
		case QEvent::WindowStateChange: {
			if (isMinimized()) hide();
			break;
		}
		default: {
			QMainWindow::changeEvent (event);
			break;
		}
	}
}

void MyForm::sendSoundAlarm (bool checked) {
	if (!checked) {
		m_mobj->play();
	}
}

void MyForm::cb_traptrayClicked () {
	m_mobj->stop();
}

MyForm::~MyForm () {
	if (m_timer.isActive()) m_timer.stop();
	delete m_mobj;
}
