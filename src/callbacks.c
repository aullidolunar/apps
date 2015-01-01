#include "main.h"

void on_window1_destroy (GtkWindow *window, LPAPPINFO ai) {
	gtk_main_quit ();
}

gboolean IsNumberCool (const gchar *s) {
	GRegex *regex;
	gboolean retval;
	regex = g_regex_new ("^-?\\d*(\\.\\d+)?$", G_REGEX_CASELESS, 0, NULL);
	retval = g_regex_match (regex, s, 0, NULL);
	g_regex_unref (regex);
	return retval;
}

gboolean test_key_event (guint keyval) {
	gboolean retVal = TRUE;
	switch (keyval) {
		case GDK_KEY_Tab:
		case GDK_KEY_BackSpace:
		case GDK_KEY_KP_0:
		case GDK_KEY_KP_1:
		case GDK_KEY_KP_2:
		case GDK_KEY_KP_3:
		case GDK_KEY_KP_4:
		case GDK_KEY_KP_5:
		case GDK_KEY_KP_6:
		case GDK_KEY_KP_7:
		case GDK_KEY_KP_8:
		case GDK_KEY_KP_9:
		case GDK_KEY_0:
		case GDK_KEY_1:
		case GDK_KEY_2:
		case GDK_KEY_3:
		case GDK_KEY_4:
		case GDK_KEY_5:
		case GDK_KEY_6:
		case GDK_KEY_7:
		case GDK_KEY_8:
		case GDK_KEY_9:
		case GDK_KEY_period:
		case GDK_KEY_KP_Decimal:
		case GDK_KEY_KP_Subtract:
		case GDK_KEY_minus:
		{ 
			retVal = FALSE; 
		}
	}
	return retVal;
}

void msg_error (GtkWindow *window, const gchar *b) {
	GtkWidget *dialog;
	dialog = gtk_message_dialog_new_with_markup (window, GTK_DIALOG_DESTROY_WITH_PARENT, GTK_MESSAGE_ERROR, GTK_BUTTONS_CLOSE, "<b>%s</b>", _("Error calculating the operation"));
	gtk_window_set_title (GTK_WINDOW (dialog), PACKAGE_STRING);
	gtk_message_dialog_format_secondary_text (GTK_MESSAGE_DIALOG (dialog), "%s:\n%s", _("Detected the following errors"), b);
	gtk_dialog_run (GTK_DIALOG (dialog));
	gtk_widget_destroy (dialog);
}

gchar * get_the_goodie (gint i, const gchar *a, const gchar *b) {
	double r = 0.0;
	double v1 = g_strtod (a, NULL);
	double v2 = g_strtod (b, NULL);
	double k = 0.0;
	k = ((v1*v2)/100);
	switch (i)
	{
		case INCREMENT:
		{
			r = v1 + k;
			break;
		}
		case DECREMENT:
		{
			r = v1 - k;
			break;
		}
		case PERCENTAGE:
		{
			if (v1 < v2) {
				r = (100*(v2-v1))/v1;
			} else {
				r = (100*(v2+v1))/v1;
			}
			break;
		}
	}
	return g_strdup_printf ("%0.2f", r);
}

gboolean on_entry1_key_press_event (GtkWidget *widget, GdkEventKey *event, LPAPPINFO ai) {
	return test_key_event (event->keyval);
}

gboolean on_entry2_key_press_event (GtkWidget *widget, GdkEventKey *event, LPAPPINFO ai) {
	return test_key_event (event->keyval);
}

void on_button1_clicked (GtkButton *b, LPAPPINFO ai) {
	GString *_error;
	gint index;
	gint pos;
	gint e; // error counter
	_error = g_string_new (NULL);
	e = 0;
	index = gtk_combo_box_get_active (GTK_COMBO_BOX (ai->combo));
	if (!index) {
		g_string_append_printf (_error, "* %s = 0\n", _("Combo index"));
		e++;
	} else {
		pos = index;
	}
	index = gtk_entry_get_text_length (GTK_ENTRY (ai->val1));
	if (!index) {
		g_string_append_printf (_error, "* %s = %s\n", _("Value1"), _("empty"));
		e++;
	}
	index = gtk_entry_get_text_length (GTK_ENTRY (ai->val2));
	if (!index) {
		g_string_append_printf (_error, "* %s = %s\n", _("Value2"), _("empty"));
		e++;
	}
	if (e) {
		msg_error (GTK_WINDOW (ai->window), _error->str);
	} else {
		g_string_free (_error, TRUE);
		e = 0;
		_error = g_string_new (NULL);
		const gchar * val1 = gtk_entry_get_text (GTK_ENTRY (ai->val1));
		if (!IsNumberCool (val1)) {
			e++;
			g_string_append_printf (_error, "* Odd number in %s: %s\n", _("Value2"), val1);
		}
		const gchar * val2 = gtk_entry_get_text (GTK_ENTRY (ai->val2));
		if (!IsNumberCool (val2)) {
			e++;
			g_string_append_printf (_error, "* Odd number in %s: %s\n", _("Value2"), val2);
		}
		if (e) {
			msg_error (GTK_WINDOW (ai->window), _error->str);
		} else {
			// seems legit :p
			gchar *response = get_the_goodie (pos, val1, val2);
			gtk_entry_set_text (GTK_ENTRY (ai->resp), response);
			g_free (response);
		}
	}
	g_string_free (_error, TRUE);
	g_print ("Shit freed, man\n");
}

void on_button2_clicked (GtkButton *b, LPAPPINFO ai) {
	gtk_widget_destroy (ai->window);
}
