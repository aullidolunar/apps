#include "pref.hh"

PrefDialog::PrefDialog (QWidget *parent) : QDialog (parent), ui (new Ui::Dialog)
{
	ui->setupUi (this);
	setWindowTitle (QString("%1 %2").arg(tr("Preferences dialog for")).arg(PACKAGE_STRING_LONG));
	const char *labels[][2] = {
		{QT_TR_NOOP("Select language"), "0"},
		{QT_TR_NOOP("English"), "en"},
		{QT_TR_NOOP("Spanish"), "es_MX"},
		NULL
	};
	for (int index = 0; labels[index][0] != NULL; index++) {
		ui->comboLang->addItem (labels[index][0], labels[index][1]);
	}
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

QVariant PrefDialog::get_lang_data() const {
	return ui->comboLang->itemData(ui->comboLang->currentIndex());
}

PrefDialog::~PrefDialog () {
	delete ui;
}
