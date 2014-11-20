#include "callbacks.h"

void on_window1_destroy(GtkWidget *object, LPDATAINFO data) {
	gtk_main_quit();
}
