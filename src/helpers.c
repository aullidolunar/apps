#include "helpers.h"

GdkPixbuf * make_pixbuf_from_my_file (const gchar* filename, gint w, gint h) {
	GdkPixbuf *p;
	gchar *f;
	f = g_build_filename (RES_DIR, filename, NULL);
	p = gdk_pixbuf_new_from_file_at_size (f, w, h, NULL);
	g_free (f);
	return p;
}

gboolean IsMyMediaFile (const gchar *filepath) {
	GRegex *regex;
	gboolean retval;
	regex = g_regex_new ("\\.(mp3|ogg|wma|flv|mp4|wav)", G_REGEX_CASELESS, 0, NULL);
	retval = g_regex_match (regex, filepath, 0, NULL);
	g_regex_unref (regex);
	return retval;
}

gint read_files (const gchar *directory, GList **list) {
	gint items;
	items = 0;
	if (g_file_test (directory, G_FILE_TEST_IS_DIR)) {
		const gchar *entry;
		GDir *dh;
		dh = g_dir_open (directory, 0, NULL);
		while ((entry = g_dir_read_name (dh))) {
			gchar *item = g_build_filename (directory, entry, NULL);
			if ((g_file_test (item, G_FILE_TEST_IS_REGULAR)) && (IsMyMediaFile (item))) {
#ifdef ENABLE_DEBUG
				g_print ("FILE: %s\n", item);
#endif
				*list = g_list_append (*list, item);
				items++;
			} else {
				g_free (item);
			}
		}
		g_dir_close (dh);
	}
#ifdef ENABLE_DEBUG
	g_print ("Total: %i\n", items);
#endif
	return items;
}

GtkWidget * create_button_helper (GtkDialog *dialog) {
	const button_data b[] = {
		{ "yes.png", GTK_RESPONSE_YES, _("Yes")},
		{ "no.png", GTK_RESPONSE_NO, _("No") },
		{ NULL, 0, NULL }
	};
	gint index;
	for (index = 0; b[index].icon_name != NULL; index++) {
		GdkPixbuf *p;
		GtkWidget *tmp;
		GtkWidget *i;
		tmp = gtk_button_new_with_label (b[index].label);
		p = make_pixbuf_from_my_file (b[index].icon_name, 16, 16);
		i = gtk_image_new_from_pixbuf (p);
		gtk_button_set_image (GTK_BUTTON (tmp), i);
		gtk_dialog_add_action_widget (GTK_DIALOG (dialog), tmp, b[index].response);
		g_object_unref (p);
	}
}

gboolean notify_bye_bye (GtkWindow* parent, const gchar *body) {
	gboolean ret;
	GtkWidget *dialog;
	GtkWidget *container;
	GtkWidget *content;
	GtkWidget *vertical;
	GtkWidget *i;
	GtkWidget *h;
	GtkWidget *b;
	GtkWidget *spacer;
	GdkPixbuf *p;
	gchar *_b;
	ret = FALSE;
	dialog = gtk_dialog_new ();
	gtk_window_set_transient_for (GTK_WINDOW (dialog), parent);
	gtk_window_set_resizable (GTK_WINDOW (dialog), FALSE);
	gtk_window_set_title (GTK_WINDOW (dialog), PACKAGE_STRING);
	content = gtk_dialog_get_content_area (GTK_DIALOG (dialog));
	container = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	vertical = gtk_box_new (GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_set_border_width (GTK_CONTAINER (container), 10);
	gtk_container_set_border_width (GTK_CONTAINER (vertical), 10);
	p = make_pixbuf_from_my_file ("warning.png", 64, 64);
	i = gtk_image_new_from_pixbuf (p);
	h = gtk_label_new ("");
	gtk_label_set_markup (GTK_LABEL (h), _("<b>ffmpeg is still running</b>"));
	g_object_set (h, "xalign", 0.0, NULL);
	spacer = gtk_box_new (GTK_ORIENTATION_VERTICAL, 10);
	_b = g_strdup_printf ("%s:\n%s", _("Aborting the operation can cause a corrupted file"), body);
	b = gtk_label_new (_b);
	g_free (_b);
	gtk_box_pack_start (GTK_BOX(vertical), h, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(vertical), spacer, TRUE, TRUE, 10);
	gtk_box_pack_start (GTK_BOX(vertical), b, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(container), i, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(container), vertical, FALSE, FALSE, 0);
	gtk_box_pack_start (GTK_BOX(content), container, FALSE, FALSE, 0);
	create_button_helper (GTK_DIALOG (dialog));
	gtk_widget_show_all (dialog);
	if (gtk_dialog_run (GTK_DIALOG (dialog)) == GTK_RESPONSE_YES) {
		ret = TRUE;
	} else {
		ret = FALSE;
	}
	g_object_unref (p);
	gtk_widget_destroy (dialog);
	return ret;
}

void toggle_tool_button (GtkToolButton *b, int state) {
	const tool_button_data t[] = {
		{ "media-playback-start", _("Starts the convertion") },
		{ "media-playback-stop", _("Stops the convertion") },
		{ NULL, NULL }
	};
	gtk_tool_button_set_icon_name (b, t[state].icon_name);
	gtk_widget_set_tooltip_text (GTK_WIDGET (b), t[state].tip_text);
}

void combo_dir_load (GtkComboBox* cb, gint pos) {
	GtkListStore *model;
	GdkPixbuf *p_all;
	gint index;
	p_all = make_pixbuf_from_my_file ("folder.png", 16, 16);
	model = GTK_LIST_STORE (gtk_combo_box_get_model (cb));
	for (index = -1; index != G_USER_N_DIRECTORIES; index++) {
		GtkTreeIter iter;
		gtk_list_store_append (model, &iter);
		if (index == -1) {
			GdkPixbuf *p_down = make_pixbuf_from_my_file ("down.png", 16, 16);
			gtk_list_store_set (model, &iter, 0, p_down, 1, _("Choose a directory"), 2, NULL, -1);
			g_object_unref (p_down);
		} else {
			const gchar *directory = g_get_user_special_dir (index);
			gchar *base_name = g_path_get_basename (directory);
			gtk_list_store_set (model, &iter, 0, p_all, 1, base_name, 2, directory, -1);
			g_free (base_name);
		}
	}
	g_object_unref (p_all);
	gtk_combo_box_set_active (cb, pos);
}

void combo_bitrate_load (GtkComboBox* cb, gint pos) {
	gint bitrates[] = {
		96, 112, 128, 160, 192, 224, 256, 320, -1
	};
	GtkListStore *model;
	GdkPixbuf *p;
	gint index;
	p = make_pixbuf_from_my_file ("speaker.png", 16, 16);
	model = GTK_LIST_STORE (gtk_combo_box_get_model (cb));
	for (index = -1; bitrates[index] != -1; index++) {
		GtkTreeIter iter;
		gtk_list_store_append (model, &iter);
		if (index == -1) {
			GdkPixbuf *p_down = make_pixbuf_from_my_file ("down.png", 16, 16);
			gtk_list_store_set (model, &iter, 0, p_down, 1, _("Choose a bitrate"), 2, NULL, -1);
			g_object_unref (p_down);
		} else {
			gchar *num = g_strdup_printf ("%i kb", bitrates[index]);
			gtk_list_store_set (model, &iter, 0, p, 1, num, 2, bitrates[index], -1);
			g_free (num);
		}
	}
	g_object_unref (p);
	gtk_combo_box_set_active (cb, pos);
}

void init_status_bar (GtkImage *i) {
	GdkPixbuf *p;
	p = make_pixbuf_from_my_file ("off.png", 16, 16);
	gtk_image_set_from_pixbuf (i, p);
	g_object_unref (p);
}

void set_status_msg (GtkLabel *l, GtkImage *i, const gchar* msg, gboolean good) {
	const gchar *icon_set[] = {
		"off.png", "on.png"
	};
	GdkPixbuf *p;
	p = make_pixbuf_from_my_file (icon_set[good], 16, 16);
	gtk_image_set_from_pixbuf (i, p);
	g_object_unref (p);
	gtk_label_set_text (l, msg);
}

void init_toolbar_icons (LPAPPINFO ai) {
	const gchar *tool_button_icons[] = {
		"run.png", "unsed", "about.png", "quit.png", NULL
	};
	gint pos = 0;
	while (tool_button_icons[pos] != NULL) {
		if (pos != 1) {
			GdkPixbuf *p;
			GtkWidget *i;
			GtkToolItem *t;
			t = gtk_toolbar_get_nth_item (GTK_TOOLBAR (ai->toolbar), pos);
			p = make_pixbuf_from_my_file (tool_button_icons[pos], 32, 32);
			i = gtk_image_new_from_pixbuf (p);
			gtk_tool_button_set_icon_widget (GTK_TOOL_BUTTON (t), i);
			g_object_unref (p);
		}
		pos++;
	}
}

gchar * get_combo_dir (GtkComboBox *c) {
	gchar *d;
	gint pos;
	GtkTreeModel *m;
	GtkTreeIter i;
	pos = gtk_combo_box_get_active (c);
	m = gtk_combo_box_get_model (c);
	gtk_tree_model_iter_nth_child (m, &i, NULL, pos);
	gtk_tree_model_get (m, &i, 2, &d, -1);
	return d;
}

gint get_combo_bitrate (GtkComboBox *c) {
	gint d;
	gint pos;
	GtkTreeModel *m;
	GtkTreeIter i;
	pos = gtk_combo_box_get_active (c);
	m = gtk_combo_box_get_model (c);
	gtk_tree_model_iter_nth_child (m, &i, NULL, pos);
	gtk_tree_model_get (m, &i, 2, &d, -1);
	return d;
}

void watcher (GPid pid, gint status, gpointer d) {
	LPAPPINFO ai = (LPAPPINFO)d;
	ai->current++;
	g_spawn_close_pid (pid);
	ai->pid = 0;
	if (ai->deleteMe && g_file_test (ai->outfile, G_FILE_TEST_IS_REGULAR)) {
		g_unlink (ai->infile);
#ifdef ENABLE_DEBUG
		g_print ("Deleted: %s\n", ai->infile);
#endif
	}
	if (ai->current < ai->total) {
		g_free (ai->outfile);
		ai->outfile = NULL;
		preprocess_runner (ai);
	} else {
		if (ai->list != NULL) {
			g_list_free_full (ai->list, g_free);
			ai->list = NULL;
#ifdef ENABLE_DEBUG
			g_print ("We're done here.\n");
#endif
		}
		gtk_widget_set_sensitive (ai->centerWidget, TRUE);
		set_status_msg (GTK_LABEL (ai->status_text), GTK_IMAGE (ai->status_icon), _("Ready"), FALSE);
	}
}

gchar* makemyOutFile (const gchar *out_dir, const gchar *s) {
	gchar *file_basename;
	gchar *tmp;
	file_basename = g_path_get_basename (s);
	gchar *str = g_strrstr (file_basename, ".");
	g_strlcpy (str+1, "mp3", 4);
	tmp = g_build_filename (out_dir, file_basename, NULL);
	g_free (file_basename);
	return tmp;
}

gboolean preprocess_runner (LPAPPINFO ai) {
	gboolean ret;
	gchar *out_dir;
	ai->infile = g_list_nth_data (ai->list, ai->current);
#ifdef ENABLE_DEBUG
	g_print ("Got a file: %s\n", ai->infile);
#endif
	out_dir = get_combo_dir (GTK_COMBO_BOX (ai->combo2));
	ai->outfile = makemyOutFile (out_dir, ai->infile);
#ifdef ENABLE_DEBUG
	g_print ("Testing outfile: %s\n", ai->outfile);
#endif
	/* test if file target exists? */
	if (g_file_test (ai->outfile, G_FILE_TEST_IS_REGULAR)) {
#ifdef ENABLE_DEBUG
		g_print ("ok, you have a same filename in outdir: %s\n", out_dir);
		g_free (ai->outfile);
		ai->current++;
		preprocess_runner (ai);
#endif
	} else {
		GError *error = NULL;
		gint bitrate;
		GPid pid;
		gchar **cmd_to_spawn;
		gchar *cmd;
		bitrate = get_combo_bitrate (GTK_COMBO_BOX (ai->combo3));
		cmd = g_strdup_printf ("%s -i \"%s\" -f mp3 -ab %i \"%s\"", FFMPEG_PATH, ai->infile, bitrate, ai->outfile);
#ifdef ENABLE_DEBUG
		g_print ("CMD: %s\n", cmd);
#endif
		g_shell_parse_argv (cmd, NULL, &cmd_to_spawn, NULL);
		ret = g_spawn_async (out_dir, cmd_to_spawn, NULL, G_SPAWN_SEARCH_PATH|G_SPAWN_DO_NOT_REAP_CHILD|G_SPAWN_STDOUT_TO_DEV_NULL|G_SPAWN_STDERR_TO_DEV_NULL, NULL, NULL, &pid, &error);
		if (ret) {
			gchar *msg;
			ai->pid = pid;
			msg = g_strdup_printf ("%s [%i/%i]: %s", _("Converting"), ai->current+1, ai->total, ai->infile);
			set_status_msg (GTK_LABEL (ai->status_text), GTK_IMAGE (ai->status_icon), msg, TRUE);
			g_free (msg);
			g_child_watch_add (pid, watcher, ai);
		} else {
#ifdef ENABLE_DEBUG
			g_print ("ERROR: %s\n", error->message);
#endif
			g_error_free (error);
		}
		g_strfreev (cmd_to_spawn);
		g_free (cmd);
	}
	g_free (out_dir);
#ifdef ENABLE_DEBUG
	g_print ("Running async we can see this line while extracting\n");
#endif
	return ret;
		
}
	
void init_ui (LPAPPINFO ai) {
	init_toolbar_icons (ai);
	combo_dir_load (GTK_COMBO_BOX (ai->combo1), 8);
	combo_dir_load (GTK_COMBO_BOX (ai->combo2), 4);
	combo_bitrate_load (GTK_COMBO_BOX (ai->combo3), 3);
	init_status_bar (GTK_IMAGE (ai->status_icon));
}

