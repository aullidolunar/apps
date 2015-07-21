#ifndef PREF_HH_INCLUDED
#define PREF_HH_INCLUDED

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

#include "ui_pref.h"
#include <QDialog>

namespace Ui {
	class Dialog;
};

class PrefDialog : public QDialog
{
	private:
		Q_OBJECT
		Ui::Dialog *ui;
	public:
		PrefDialog (QWidget *parent = 0);
		void loadValues (int, bool, bool, bool);
		int get_timeout () const;
		bool get_notify () const;
		bool get_sound () const;
		bool get_reset () const;
		QVariant get_lang_data () const;
		virtual ~PrefDialog ();
};

#endif
