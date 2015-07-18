#include "alarm.hh"

AlarmUI::AlarmUI (QWidget *parent) :
	QMainWindow (parent), ui (new Ui::MainWindow), pref (new PrefDialog (this)),
	m_timer (new QTimer(this))
{
	/* init values */
	timeout = 1;
	sec = 0;
	min = 0;
	use_notify = true;
	use_sound = true;
	use_reset = false;
	/* init phonon */
	m_sound = Phonon::createPlayer(Phonon::MusicCategory);
	/* begin ui */
	ui->setupUi (this);
	setWindowTitle (PACKAGE_STRING_LONG);
	tray_icon = new QSystemTrayIcon (QIcon(":/main"), this);
	tray_icon->show ();
	tray_icon->setToolTip (PACKAGE_STRING);

    connect (m_timer, SIGNAL(timeout()), this, SLOT(tick()));
	connect (tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayiconActivated(QSystemTrayIcon::ActivationReason)));
	connect (ui->itemStart, SIGNAL(triggered()), this, SLOT(onStart()));
	connect (ui->itemAboutQt, SIGNAL(triggered()), this, SLOT(onAboutQt()));
	connect (ui->itemPref, SIGNAL(triggered()), this, SLOT(onPref()));
	connect (ui->itemAbout, SIGNAL(triggered()), this, SLOT(onAbout()));
	connect (ui->itemProject, SIGNAL(triggered()), this, SLOT(onProject()));
	connect (m_sound, SIGNAL(finished()), this, SLOT(onFinishedSound()));
	Centre();
}

AlarmUI::~AlarmUI () {
	if (m_timer->isActive ()) m_timer->stop();
	m_sound->clear();
	delete m_sound;
	delete m_timer;
	delete pref;
	delete ui;
}

void AlarmUI::tick() {
	sec++;
	if (sec == 60) {
		sec = 0;
		min++;
	}
	if (min == timeout) {
		min = 0;
		m_timer->stop ();
		showNormal ();
		if (use_sound) {
			qDebug() << "playing";
			m_sound->enqueue (QUrl::fromLocalFile(PACKAGE_SOUND));
			m_sound->play();
		}
	}
	updateTimeLabel ();
}

void AlarmUI::onFinishedSound () {
	toggleui (false);
	m_sound->clear ();
}

void AlarmUI::updateTimeLabel () {
	ui->timeLabel->setText (QString("%1:%2/%3:00").arg(min, 2, 10, QChar('0')).arg(sec, 2, 10, QChar('0')).arg(timeout, 2, 10, QChar('0')));
}

void AlarmUI::onStart () {
	bool state = false;
	if (!m_timer->isActive ()) {
		// start here
		if (use_reset) sec = 0;
		m_timer->start (1000);
		state = true;
	} else {
		// stop here
		m_timer->stop ();
	}
	toggleui (state);
}

void AlarmUI::toggleui (bool _state) {
	ui->itemStart->setText (_state ? tr("&Stop") : tr ("&Start"));
	ui->itemStart->setIcon (QIcon (_state ? ":/stop" : ":/start"));
	ui->itemPref->setEnabled (!_state);
	if (!QSystemTrayIcon::supportsMessages ()) {
		qDebug() << "No suported";
	} else {
		qDebug () << "You must see msg";
	}
	if (use_notify) {
		tray_icon->showMessage (windowTitle(), QString ("%1 %2").arg(tr("A Qt alarm has")).arg(_state ? tr("started") : tr("stopped")), QSystemTrayIcon::Information);
	}
}

void AlarmUI::onPref () {
	pref->loadValues (timeout, use_notify, use_sound, use_reset);
	if (pref->exec()) {
		timeout = pref->get_timeout ();
		use_notify = pref->get_notify ();
		use_sound = pref->get_sound ();
		use_reset = pref->get_reset ();
		updateTimeLabel ();
	}
}

void AlarmUI::onAbout () {
	QMessageBox::about (this, QString("%1 %2").arg(tr("About")).arg(windowTitle()), tr("QT4 alarm utility"));
}

void AlarmUI::Centre () {
	QDesktopWidget *desktop = QApplication::desktop();
	int screenWidth = desktop->width();
	int screenHeight = desktop->height(); 
	int frameWidth = width();
	int frameHeight = height ();
	int x = (screenWidth - frameWidth) / 2;
	int y = (screenHeight - frameHeight) / 2;
	move (x, y);
}

void AlarmUI::trayiconActivated (QSystemTrayIcon::ActivationReason reason) {
	switch (reason) {
		case QSystemTrayIcon::Context: {
			ui->menu_Application->popup(QCursor::pos());
			break;
		}
		default: {
			if (isVisible ()) {
				hide ();
			} else {
				showNormal ();
			}
			break;
		}
	}
	
}

void AlarmUI::closeEvent (QCloseEvent* event) {
	if (m_timer->isActive ()) {
		int ret = QMessageBox::warning (this, windowTitle(), tr("The alarm is still running, do you want to exit anyway?"), QMessageBox::Yes|QMessageBox::No);
		if (ret == QMessageBox::Yes) {
			qDebug() << "Here, right";
			m_timer->stop ();
			event->accept();
		} else {
			event->ignore ();
		}
	} else {
		event->accept();
	}
}

void AlarmUI::changeEvent (QEvent *event) {
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

void AlarmUI::onAboutQt () {
	QApplication::aboutQt ();
}

void AlarmUI::onProject () {
	QDesktopServices::openUrl(QUrl("https://github.com/aullidolunar/apps/tree/qt-alarm"));
}
