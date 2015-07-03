#include "reguser.hpp"

RegUser::RegUser (QWidget *parent) :
	QMainWindow (parent), ui (new Ui::MainWindow),
	RegEdit1 ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", QSettings::NativeFormat, this),
	RegEdit2 ("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Advanced", QSettings::NativeFormat, this)
{
	ui->setupUi (this);
	setWindowTitle (PACKAGE_STRING_LONG);
#ifndef WIN32
	setEnabled (false);
	setToolTip (tr("This is app must build in Win32 environments"));
#else
	QString username = RegEdit1.value ("RegisteredOwner").toString();
	QString organization = RegEdit1.value ("RegisteredOrganization").toString();
	ui->_username->setText (username);
	ui->_organization->setText (organization);
	bool enabled = RegEdit2.value ("EnableBalloonTips").toBool();
	ui->balloon_check->setChecked (enabled);
	connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(onSave()));
	connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onAbout()));
#endif
	Centre();
}

RegUser::~RegUser () {
	delete ui;
}

void RegUser::onSave () {
	RegEdit1.setValue ("RegisteredOwner", ui->_username->text());
	RegEdit1.setValue ("RegisteredOrganization", ui->_organization->text());
	RegEdit2.setValue ("EnableBalloonTips", ui->balloon_check->isChecked ());
	QString msg = QString("%1\n\n%2").arg(tr("Data has been saved")).arg(tr("You need to reboot your PC to apply the additional preferences"));
	QMessageBox::information (this, PACKAGE_STRING_LONG, msg);
}

void RegUser::onAbout () {
#ifdef WIN32
	HWND hwnd = winId();
	QPixmap hIcon (":/main");
	QString title (PACKAGE_NAME);
	QString desc(tr("Change registered owner and organization"));
	const wchar_t *_title = reinterpret_cast<const wchar_t*>(title.utf16());
	const wchar_t *_desc = reinterpret_cast<const wchar_t*>(desc.utf16());
	::ShellAbout (hwnd, _title, _desc, hIcon.toWinHICON());
#endif
}

void RegUser::Centre () {
	QDesktopWidget *desktop = QApplication::desktop();
	int screenWidth = desktop->width();
	int screenHeight = desktop->height(); 
	int frameWidth = width();
	int frameHeight = height ();
	int x = (screenWidth - frameWidth) / 2;
	int y = (screenHeight - frameHeight) / 2;
	move (x, y);
}

