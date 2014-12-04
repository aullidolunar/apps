#ifndef HELPER_H_INCLUDED
#define HELPER_H_INCLUDED

#include "main.h"

GtkWidget * create_button_helper (int);
GtkWidget * create_box_helper (const int);
void update_button_helper (GtkWidget *, const gint);
void toggle_ui (GtkWindow *);
gboolean message_box_helper (GtkWindow *);

enum {
	HORIZONTAL_BOX,
	VERTICAL_BOX
};

enum {
	BUTTON_PLAY,
	BUTTON_ABOUT,
	BUTTON_QUIT
};

enum {
	STOP,
	PLAY
};

enum {
	YES_BUTTON,
	NO_BUTTON
};

#endif
