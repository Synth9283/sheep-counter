#include <gtk/gtk.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>

// global vars
uint8_t *sheep_count = 0;
typedef struct {
  Mix_Chunk *say1;
  Mix_Chunk *say2;
  Mix_Chunk *say3;
  Mix_Chunk *click;
} Audio;
typedef struct {
    GtkWidget *sheep_label;
} app_widgets;
Audio audio;

int main(int *argc, char **argv) {
    gtk_init(&argc, &argv);
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "glade/window_main.glade", NULL);
    GtkWidget *window = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    app_widgets *widgets = g_slice_new(app_widgets);
    widgets->sheep_label = GTK_WIDGET(gtk_builder_get_object(builder, "sheep_label"));
    gtk_builder_connect_signals(builder, widgets);
    g_object_unref(builder);
    gtk_widget_show(window);

    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    audio.say1 = Mix_LoadWAV("source/sounds/say1.wav");
    audio.say2 = Mix_LoadWAV("source/sounds/say2.wav");
    audio.say3 = Mix_LoadWAV("source/sounds/say3.wav");
    audio.click = Mix_LoadWAV("source/sounds/pop.wav");

    gtk_main();
    g_slice_free(app_widgets, widgets);
    Mix_FreeChunk(audio.say1);
    Mix_FreeChunk(audio.say2);
    Mix_FreeChunk(audio.say3);
    Mix_FreeChunk(audio.click);
    SDL_Quit();
    return 0;
}

void on_window_main_destroy() {
    gtk_main_quit();
}

void on_sheep_button_clicked(GtkButton *sheep_button, app_widgets *widgets) {
    uint8_t sheep_say = rand()%3+1;
    Mix_PlayChannel(-1, audio.click, 0);
    switch (sheep_say) {
      case 1: Mix_PlayChannel(-1, audio.say1, 0);
      case 2: Mix_PlayChannel(-1, audio.say2, 0);
      case 3: Mix_PlayChannel(-1, audio.say3, 0);
    }

    static guint sheep_count = 0;
    sheep_count++;
    gchar *sheep_count_str = g_strdup_printf("%d Sheep", sheep_count);
    gtk_label_set_text(GTK_LABEL(widgets->sheep_label), sheep_count_str);
    g_free(sheep_count_str);
}

