/*! GTK+3 APPLICATON - PRINTS OUT 2 INPUTS
 *
 * \description A simple Input / Output Program made with gtk+3
 *
 * \author Sebastian Dichler <el16b032@technikum-wien.at> <sedi343@gmail.com>
 *
 * \version Rev.: 01, 25.04.2017 - Used lectors code example
 *          Rev.: 02, 25.04.2017 - Changing code for 2 inputs (Forename, Surname)
 *          Rev.: 03, 25.04.2017 - Reduced everything to one function each button action
 *          Rev.: 04, 25.04.2017 - Removed ENTER signal from forename
 *          Rev.: 05, 25.04.2017 - Removed Useless comments due to old functions
 *
 *
 */

#include <gtk/gtk.h>
#include <string.h>

/* ---- struct that collects all widgets we will use in various callbacks ---- */

struct my_widgets
{
	GtkWidget *label_output_forename;
	GtkWidget *input_entry_forename;
	GtkWidget *label_output_surname;
	GtkWidget *input_entry_surname;
};

/*------------------------------------------------------------------*/
/*
 * callback executed when the "Okay" button is clicked,
 * or "Enter" is hit in the entry box
*/
/*------------------------------------------------------------------*/

/* INPUT FUNCTION */
static void ok_clicked (GtkWidget *widget, gpointer data)
{
	gchar *buffer1, *buffer2, *buffer3, *buffer4;
	
/* ----- obtain references to the widgets passed as generic data pointer ---- */
	
	struct my_widgets *wid = (struct my_widgets*) data;
	
/* ----- obtain text from the entry box ----- */
	
	buffer1 = (gchar*) gtk_entry_get_text (GTK_ENTRY (wid->input_entry_forename));
	buffer2 = g_malloc (sizeof (gchar) * (strlen (buffer1) + 7));	
	sprintf (buffer2, "Hello, %s", buffer1);
	
	buffer3 = (gchar*) gtk_entry_get_text (GTK_ENTRY (wid->input_entry_surname));
	buffer4 = g_malloc (sizeof (gchar) * (strlen (buffer3) + 2));
	sprintf (buffer4, " %s!", buffer3);
	
/* ---- write the final text to the label on top ---- */

	gtk_label_set_text (GTK_LABEL (wid->label_output_forename), buffer2);
	
	gtk_widget_set_name(wid->label_output_surname, "style_output_bold");
	gtk_label_set_text (GTK_LABEL (wid->label_output_surname), buffer4);
	
	g_free (buffer2);
	g_free (buffer4);
}

/* CLEAR BUTTON USED FUNCTION */
static void clr_clicked (GtkWidget *widget, gpointer data)
{
	
/* ----- obtain references to the widgets passed as generic data pointer ---- */
	
	struct my_widgets *wid = (struct my_widgets*) data;
	
/* ---- clear the entry box ----- */
	
	gtk_entry_set_text (GTK_ENTRY (wid->input_entry_forename), "");
	gtk_entry_set_text (GTK_ENTRY (wid->input_entry_surname), "");
	
/* ---- put the placeholder text into the entry box ---- */
	
	gtk_entry_set_placeholder_text (GTK_ENTRY (wid->input_entry_forename), "e.g. Maximilian");
	gtk_entry_set_placeholder_text (GTK_ENTRY (wid->input_entry_surname), "e.g. Mustermann");
	
/* ---- clear the label ----- */
	
	gtk_label_set_text (GTK_LABEL (wid->label_output_forename), "Hello?");
	gtk_widget_set_name(wid->label_output_surname, "style_output");
	gtk_label_set_text (GTK_LABEL (wid->label_output_surname), "What's Your name?");
}

/* FUNCTION TO APPLY BACKGROUND (NOT WORKING) */
static void apply_css (GtkWidget *widget, GtkStyleProvider *provider)
{
	gtk_style_context_add_provider (gtk_widget_get_style_context (widget), provider, G_MAXUINT);
	if (GTK_IS_CONTAINER (widget))
	{
		gtk_container_forall (GTK_CONTAINER (widget), (GtkCallback) apply_css, provider);
	}
}

/* APP ACTIVATE CALLBACK - CREATES THE WINDOW */
static void activate (GtkApplication* app, gpointer user_data)
{
	
/* ----- WIDGETS ---- */
	
	GtkWidget *window;
	GtkWidget *grid;
	GtkWidget *label_name_forename;
	GtkWidget *label_name_surname;
	GtkWidget *clr_button, *ok_button;
	GtkWidget *headerbar;
	GtkStyleContext *context;
	GtkStyleProvider *provider;
	GtkWidget *box;
	GtkWidget *backgroundimage;
	GtkWidget *layout;
	
	
/* ----- obtain references to the widgets passed as generic data pointer ---- */
	
	struct my_widgets *wid = (struct my_widgets*) user_data;

/* ---- create the window and associate an icon ---- */
	
	window = gtk_application_window_new (app);
	gtk_window_set_resizable (GTK_WINDOW (window), FALSE);
	gtk_window_set_default_icon_from_file ("icon.png", NULL);
	gtk_window_set_position (GTK_WINDOW (window), GTK_WIN_POS_MOUSE);

/* ---- create a grid to be used as layout container ---- */
	
	grid = gtk_grid_new();
	gtk_grid_set_column_homogeneous (GTK_GRID (grid), FALSE);
	gtk_container_add (GTK_CONTAINER (window), grid);
	gtk_container_set_border_width (GTK_CONTAINER(window), 20);
	
/*------------------------------------------------------------------*/
/*
 * output label using a fancy font from "Google Font Dir"
 * NOTE - the box is only used to make the label more
 *        convenient selectable using the CSS - see below
 *
 * Marck Script:  style_google
 * April-Flowers: style_output
*/
/*------------------------------------------------------------------*/
	
	box = gtk_box_new (GTK_ORIENTATION_HORIZONTAL, 0);
	wid->label_output_forename = gtk_label_new ("Hello?");
	wid->label_output_surname = gtk_label_new("What's Your name?");
	
/* ---- name the label so that we can reference it from the CSS file ---- */
	
	gtk_widget_set_name(wid->label_output_forename, "style_output");
	gtk_widget_set_name(wid->label_output_surname, "style_output");
	gtk_box_pack_start (GTK_BOX (box), wid->label_output_forename, TRUE, TRUE, 0);
	gtk_box_pack_start (GTK_BOX (box), wid->label_output_surname, TRUE, TRUE, 0);
	gtk_widget_set_size_request (wid->label_output_forename, 150, 50);
	gtk_widget_set_size_request (wid->label_output_surname, 100, 50);
	gtk_grid_attach (GTK_GRID (grid), box, 0, 0, 2, 1);

/* ---- name label - label text horizontally aligned at towards the end ---- */
	
	label_name_forename = gtk_label_new ("Forename: ");
	label_name_surname = gtk_label_new ("Surname: ");
	gtk_widget_set_halign (label_name_forename, GTK_ALIGN_END);
	gtk_widget_set_halign (label_name_surname, GTK_ALIGN_END);
	gtk_widget_set_size_request (label_name_forename, 60, 40);
	gtk_widget_set_size_request (label_name_surname, 60, 40);
	gtk_grid_attach (GTK_GRID (grid), label_name_forename, 0, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), label_name_surname, 0, 2, 1, 1);
	
/* ---- text entry with a placeholder text ---- */
	
	wid->input_entry_forename = gtk_entry_new();
	wid->input_entry_surname = gtk_entry_new();
	gtk_grid_attach (GTK_GRID (grid), wid->input_entry_forename, 1, 1, 1, 1);
	gtk_grid_attach (GTK_GRID (grid), wid->input_entry_surname, 1, 2, 1, 1);
	gtk_entry_set_placeholder_text (GTK_ENTRY (wid->input_entry_forename), "e.g. Maximilian");
	gtk_entry_set_placeholder_text (GTK_ENTRY (wid->input_entry_surname), "e.g. Mustermann");
	
/* ---- connect a signal when ENTER is hit within the entry box ---- */
	
	//g_signal_connect (wid->input_entry_forename, "activate", G_CALLBACK (ok_clicked), (gpointer) wid);
	g_signal_connect (wid->input_entry_surname, "activate", G_CALLBACK (ok_clicked), (gpointer) wid);
	
/* ---- create a headerbar ---- */
	
	headerbar = gtk_header_bar_new ();
	gtk_widget_show (headerbar);
	gtk_header_bar_set_title (GTK_HEADER_BAR (headerbar), "Name Printer");
	gtk_header_bar_set_subtitle (GTK_HEADER_BAR (headerbar), "Simple I/O GUI Program");
	gtk_header_bar_set_show_close_button (GTK_HEADER_BAR (headerbar), TRUE);
	gtk_window_set_titlebar (GTK_WINDOW (window), headerbar);
	
/* ---- put a red clear button to the left side of the header bar ---- */
	
	clr_button = gtk_button_new_with_mnemonic ("_Clear");
	context = gtk_widget_get_style_context (clr_button);
	gtk_style_context_add_class (context, "text-button");
	gtk_style_context_add_class (context, "destructive-action");
	gtk_header_bar_pack_start (GTK_HEADER_BAR (headerbar), clr_button);
	
/* ---- connect a signal when the CLEAR button is clicked ---- */
	
	g_signal_connect (clr_button, "clicked", G_CALLBACK (clr_clicked), (gpointer) wid);
	
/* ---- put a blue okay button to the left side of the header bar ---- */
	
	ok_button = gtk_button_new_with_mnemonic ("_Okay");
	context = gtk_widget_get_style_context (ok_button);
	gtk_style_context_add_class (context, "text-button");
	gtk_style_context_add_class (context, "suggested-action");
	gtk_header_bar_pack_end (GTK_HEADER_BAR (headerbar), ok_button);
	
/* ---- connect a signal when the OKAY button is clicked ---- */
	
	g_signal_connect (ok_button, "clicked", G_CALLBACK (ok_clicked), (gpointer) wid);
	
/* ---- add a fancy background image ---- */
	
	provider = GTK_STYLE_PROVIDER (gtk_css_provider_new ());
	gtk_css_provider_load_from_resource (GTK_CSS_PROVIDER (provider), "/css_greeter/css_greeter.css");
	apply_css (window, provider);
	
/* ---- cant find the reason why background is not loading ---- */
	
	layout = gtk_layout_new(NULL, NULL);
	gtk_container_add(GTK_CONTAINER(window), layout);
	gtk_widget_show(layout);
	
	backgroundimage = gtk_image_new_from_file("background.jpg");
	gtk_layout_put(GTK_LAYOUT(layout), backgroundimage, 0, 0);
	
/* ----- end of background image ----- */

	gtk_widget_show_all (window);
}

int main (int argc, char **argv)
{
	GtkApplication *app;
	int status;
	
/* ---- we need some memory for the widgets struct ---- */
	
	struct my_widgets *wid = g_malloc (sizeof (struct my_widgets));
	
/* ---- create a threaded application ---- */
	
	app = gtk_application_new (NULL, G_APPLICATION_FLAGS_NONE);
	g_signal_connect (app, "activate", G_CALLBACK (activate), (gpointer) wid);
	
/* ---- run the application -> emits an "activate" signal ---- */
	
	status = g_application_run (G_APPLICATION (app), argc, argv);
	g_object_unref (app);
	
/* ---- free the memory for the widgets struct ---- */
	
	g_free (wid);
	wid = NULL;

	return status;
}
