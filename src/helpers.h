#ifndef HELPERS_H_INCLUDED
#define HELPERS_H_INCLUDED

#include "main.h"

typedef struct  {
	const gchar *icon_name;
	int response;
	const gchar *label;
} button_data;

typedef struct {
	const gchar *icon_name;
	const gchar *tip_text;
} tool_button_data;

void init_ui (LPAPPINFO);
void toggle_tool_button (GtkToolButton *, int);
void set_status_msg (GtkLabel *, GtkImage *, const gchar*, gboolean);
gboolean preprocess_runner (LPAPPINFO);

#endif
