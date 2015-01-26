#include "callbacks.h"

void on_window1_destroy (GtkWindow* window, DataInfo *di) {
	gtk_main_quit ();
}

gboolean on_window1_window_state_event (GtkWidget *window, GdkEventWindowState *event, DataInfo *di) {
	if (event->new_window_state == GDK_WINDOW_STATE_ICONIFIED) gtk_widget_set_visible (window, FALSE);
	return FALSE;
}

gboolean on_window1_delete_event (GtkWindow *window, GdkEvent *event, DataInfo *di) {
	return test_timer_running (window, di->object[CENTERCHILD]);
}

void on_imagemenuitem1_activate (GtkMenuItem *menu_item, DataInfo *di) {
	gboolean state = start_or_stop_timer_now (di);
	toggle_ui (di->object[CENTERCHILD], G_OBJECT (menu_item), di->object[PREF_MENU_ITEM], state);
}

void on_imagemenuitem2_activate (GtkMenuItem *menu_item, DataInfo *di) {
	show_preferences_dialog (di);
}

void on_imagemenuitem3_activate (GtkMenuItem *menu_item, DataInfo *di) {
	gboolean retVal;
	g_signal_emit_by_name (di->object[TOPLEVEL], "delete-event", di, &retVal, NULL);
	if (!retVal) gtk_widget_destroy (GTK_WIDGET (di->object[TOPLEVEL]));
}

void on_imagemenuitem4_activate (GtkMenuItem *menu_item, DataInfo *di) {
	show_about_dialog (di);
}

void on_checkbutton1_toggled (GtkToggleButton *button, DataInfo *di) {
	di->haveSound = gtk_toggle_button_get_active (button);
}

void on_checkbutton2_toggled (GtkToggleButton *button, DataInfo *di) {
	di->haveNotify = gtk_toggle_button_get_active (button);
}

void on_checkbutton3_toggled (GtkToggleButton *button, DataInfo *di) {
	di->haveReset = gtk_toggle_button_get_active (button);
}

void on_spinbutton1_value_changed (GtkSpinButton *spin_button, DataInfo *di) {
	di->max = gtk_spin_button_get_value_as_int (spin_button);
	set_timer_time (di->object[TIMER_LABEL], di->sec, di->min, di->max);
}

void on_status_icon_activate (GtkStatusIcon *status_icon, GtkWindow *window) {
	toggle_window (window);
}

void on_status_icon_popup_menu (GtkStatusIcon *status_icon, guint button, guint activate_time, GtkMenu *menu) {
	show_popup_menu (menu, button, activate_time);
}
