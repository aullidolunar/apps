#include "page2.h"

void reset_toggled (GtkToggleButton *togglebutton, LPAPPWIDGETS p) {
	p->_reset = gtk_toggle_button_get_active (togglebutton);
}

void notify_toggled (GtkToggleButton *togglebutton, LPAPPWIDGETS p) {
	p->_notify = gtk_toggle_button_get_active (togglebutton);
}

void sound_toggled (GtkToggleButton *togglebutton, LPAPPWIDGETS p) {
	p->_sound = gtk_toggle_button_get_active (togglebutton);
}

void spinbutton_value_change (GtkSpinButton *spin_button, LPAPPWIDGETS p) {
	p->timer_end = gtk_spin_button_get_value_as_int (spin_button);
}

void set_contents_page2 (LPAPPWIDGETS ptr, const gchar *title) {
	GtkWidget *child;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *spacer1;
	GtkWidget *spinbutton;
	GtkWidget *child1;
	GtkWidget *reset_check;
	GtkWidget *notify_check;
	GtkWidget *sound_check;
	
	label = gtk_label_new (title);
	child = create_box_helper (VERTICAL_BOX);
	
	child1 = create_box_helper (HORIZONTAL_BOX);
	label1 = gtk_label_new (_("Set timer in minutes:"));
	spacer1 = create_box_helper (HORIZONTAL_BOX);
	spinbutton = gtk_spin_button_new_with_range (1, ptr->max, 1);
	gtk_spin_button_set_value (GTK_SPIN_BUTTON (spinbutton), ptr->timer_end);
	
	reset_check = gtk_check_button_new_with_label (_("Reset seconds at alarm startup"));
	notify_check = gtk_check_button_new_with_label (_("Disable notify balloons"));
#ifndef WITH_LIBNOTIFY
	gtk_widget_set_sensitive (notify_check, FALSE);
#endif
	sound_check = gtk_check_button_new_with_label (_("Disable alarm sound"));
	
	g_signal_connect (spinbutton, "value-changed", G_CALLBACK(spinbutton_value_change), ptr);
	g_signal_connect (reset_check, "toggled", G_CALLBACK(reset_toggled), ptr);
	g_signal_connect (notify_check, "toggled", G_CALLBACK(notify_toggled), ptr);
	g_signal_connect (sound_check, "toggled", G_CALLBACK(sound_toggled), ptr);
	
	gtk_box_pack_start (GTK_BOX (child1), label1, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child1), spacer1, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (child1), spinbutton, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), child1, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), reset_check, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), notify_check, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), sound_check, FALSE, FALSE, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (ptr->notebook), child, label);
}
