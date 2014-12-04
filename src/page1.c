#include "page1.h"

GtkWidget *create_text_view () {
	GtkWidget *tmp;
	GtkWidget *s;
	s = gtk_scrolled_window_new (NULL, NULL);
	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (s), GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
	gtk_scrolled_window_set_shadow_type (GTK_SCROLLED_WINDOW (s), GTK_SHADOW_ETCHED_OUT);
	tmp = gtk_text_view_new ();
	gtk_container_add (GTK_CONTAINER (s), tmp);
	gtk_widget_set_tooltip_text (tmp, _("Things to remember"));
	return s; // not actually the text view, but ...
}

void set_contents_page1 (LPAPPWIDGETS ptr, const gchar *title) {
	GtkWidget *time_box;
	GtkWidget *scrolled;
	GtkWidget *child;
	GtkWidget *label;
	GtkWidget *label1;
	GtkWidget *spacer1;
	
	label = gtk_label_new (title);
	child = create_box_helper (VERTICAL_BOX);
	scrolled = create_text_view ();
	time_box = create_box_helper (HORIZONTAL_BOX);
	label1 = gtk_label_new (_("Time elapsed"));
	spacer1 = create_box_helper (HORIZONTAL_BOX);
	ptr->time_label = gtk_label_new ("00:00");
	
	gtk_box_pack_start (GTK_BOX (time_box), label1, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (time_box), spacer1, TRUE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (time_box), ptr->time_label, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), time_box, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX (child), scrolled, TRUE, TRUE, 0);
	gtk_notebook_append_page (GTK_NOTEBOOK (ptr->notebook), child, label);
}
