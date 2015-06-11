#include "reguser.hpp"

RegUser::RegUser (QWidget *parent) :
	QMainWindow (parent), ui (new Ui::MainWindow),
	RegEdit ("HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", QSettings::NativeFormat, this)
{
	ui->setupUi (this);
	setWindowTitle (PACKAGE_STRING_LONG);
#ifndef WIN32
	setEnabled (false);
	setToolTip (tr("This is app must build in Win32 environments"));
#else
	QString username = RegEdit.value ("RegisteredOwner").toString();
	QString organization = RegEdit.value ("RegisteredOrganization").toString();
	ui->_username->setText (username);
	ui->_organization->setText (organization);
	connect (ui->pushButton, SIGNAL(clicked()), this, SLOT(onSave()));
	connect (ui->pushButton_3, SIGNAL(clicked()), this, SLOT(onAbout()));
#endif
	Centre();
}

RegUser::~RegUser () {
	delete ui;
}

void RegUser::onSave () {
	RegEdit.setValue ("RegisteredOwner", ui->_username->text());
	RegEdit.setValue ("RegisteredOrganization", ui->_organization->text());
	QMessageBox::information (this, PACKAGE_STRING_LONG, tr("Data has been saved"));
}

void RegUser::onAbout () {
#ifdef WIN32
	HWND hwnd = winId();
	QPixmap Icon(":/main");
	LPCWSTR _title = reinterpret_cast<LPCWSTR>(QString(PACKAGE_NAME).utf16());
	LPCWSTR _desc = reinterpret_cast<LPCWSTR>(QString(tr("Change registered owner and organization")).utf16());
	::ShellAbout (hwnd, _title, _desc, Icon.toWinHICON ());
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

