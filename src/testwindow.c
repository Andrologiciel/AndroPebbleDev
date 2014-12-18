#include "testwindow.h"
#include <pebble.h>

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_bitham_42_bold;
static GFont s_res_gothic_24_bold;
static GFont s_res_gothic_18;
static TextLayer *time_layer;
static TextLayer *fete_layer;
static TextLayer *date_layer;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, GColorBlack);
  window_set_fullscreen(s_window, 1);
  
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_gothic_18 = fonts_get_system_font(FONT_KEY_GOTHIC_18);
  // time_layer
  time_layer = text_layer_create(GRect(8, 9, 124, 48));
  text_layer_set_background_color(time_layer, GColorBlack);
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_text(time_layer, "20:30");
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  text_layer_set_font(time_layer, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)time_layer);
  
  // fete_layer
  fete_layer = text_layer_create(GRect(4, 61, 135, 77));
  text_layer_set_text(fete_layer, "Véronique, annie");
  text_layer_set_text_alignment(fete_layer, GTextAlignmentCenter);
  text_layer_set_font(fete_layer, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)fete_layer);
  
  // date_layer
  date_layer = text_layer_create(GRect(4, 145, 135, 19));
  text_layer_set_background_color(date_layer, GColorBlack);
  text_layer_set_text_color(date_layer, GColorWhite);
  text_layer_set_text(date_layer, "3 septembre 2014");
  text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
  text_layer_set_font(date_layer, s_res_gothic_18);
  layer_add_child(window_get_root_layer(s_window), (Layer *)date_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  text_layer_destroy(time_layer);
  text_layer_destroy(fete_layer);
  text_layer_destroy(date_layer);
}
// END AUTO-GENERATED UI CODE


//-- Code spécifique montre
//--
static const char* STR_SPACE = " "; 
char buffer_haut[] = "00:00";
static char daynum[] = "xx";
static int day;
static char buffer_bas[20];
static const char* MONTHS[] = {
    "Janvier",
    "Février",
    "Mars",
    "Avril",
    "Mai",
    "Juin",
    "Juillet",
    "Août",
    "Septembre",
    "Octobre",
    "Novembre",
    "Décembre",
};
static const char* WEEKDAYS[] = {
    "Dimanche",
    "Lundi",
    "Mardi",
    "Mercredi",
    "Jeudi",
    "Vendredi",
    "Samedi",
};
//-- Code spécifique montre

void itoa(int num, char* buffer) {
	snprintf(buffer, sizeof(buffer), "%i", num);
}

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{//Format the buffer string using tick_time as the time source
 strftime(buffer_haut, sizeof("00:00"), "%H:%M", tick_time);
 //formatage de la date http://www.cplusplus.com/reference/ctime/strftime/
 //strftime(buffer_bas, sizeof("Wednesday 31 September"), "%A %d %B", tick_time);
 //-- Formatage de la date en français
 day=tick_time->tm_mday;
 itoa(day,daynum);
 memset(buffer_bas,0,20); //-- remise à 0 du buffer date
 strcat(buffer_bas, WEEKDAYS[tick_time->tm_wday]);
 strcat(buffer_bas, STR_SPACE);
 strcat(buffer_bas, daynum);
 strcat(buffer_bas, STR_SPACE);
 strcat(buffer_bas, MONTHS[tick_time->tm_mon]);
 //Change the TextLayer text to show the new time!
 text_layer_set_text(date_layer, buffer_bas);
 text_layer_set_text(time_layer, buffer_haut);
}

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_testwindow(void) {
  //-- Code spécifique montre
  tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler); 
  //--
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
    struct tm *t;
  //-- Code spécifique montre  
  time_t temp;
  temp = time(NULL);
  t = localtime(&temp); 
  tick_handler(t, MINUTE_UNIT);
  //--
}

void hide_testwindow(void) {
  //-- Code spécifique montre  
  tick_timer_service_unsubscribe(); 
  //--
  window_stack_remove(s_window, true);
}
