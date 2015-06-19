#include "pref.hh"

PrefDialog::PrefDialog (QWidget *parent) : QDialog (parent), ui (new Ui::Dialog)
{
	ui->setupUi (this);
}

void PrefDialog::loadValues (int _t, bool _n, bool _s, bool _r) {
	ui->spinBox->setValue (_t);
	ui->checkNotify->setChecked (_n);
	ui->checkSound->setChecked (_s);
	ui->checkReset->setChecked (_r);
}

int PrefDialog::get_timeout() const {
	return ui->spinBox->value();
}

bool PrefDialog::get_notify() const {
	return ui->checkNotify->isChecked();
}

bool PrefDialog::get_sound () const {
	return ui->checkSound->isChecked();
}

bool PrefDialog::get_reset () const {
	return ui->checkReset->isChecked();
}

PrefDialog::~PrefDialog () {
	delete ui;
}
