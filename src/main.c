//-- Ajout de la librairie pebble  
#include <pebble.h>  
//-- Déclaration des objets Fenêtre et texte   
Window *window;  
TextLayer *text_layer_haut;  
TextLayer *text_layer_bas;
InverterLayer *inv_layer;
char buffer_haut[] = "Sun";
char buffer_bas[] = "00:00";

void tick_handler(struct tm *tick_time, TimeUnits units_changed)
{//Format the buffer string using tick_time as the time source
 strftime(buffer_haut, sizeof("Sun"), "%a", tick_time);
 strftime(buffer_bas, sizeof("00:00"), "%H:%M", tick_time);
 //Change the TextLayer text to show the new time!
 text_layer_set_text(text_layer_haut, buffer_haut);
 text_layer_set_text(text_layer_bas, buffer_bas);
}

//-- Définition des actions à effectuer au lancement de l'application  
void window_load(Window *window)   
{ //text_layer = text_layer_create(GRect(0, 53, 132, 168));
  //GRect means (x, y, width, height)
  //layer_set_frame(layer, (x, y, 144 - x, 168 - y));
  text_layer_haut = text_layer_create(GRect(0, 0, 144, 84));
  text_layer_set_background_color(text_layer_haut, GColorClear);
  text_layer_set_text_color(text_layer_haut, GColorBlack);
  text_layer_set_text_alignment(text_layer_haut, GTextAlignmentCenter);
  text_layer_set_font(text_layer_haut, fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD));
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer_haut); 
  //////////////
    text_layer_bas = text_layer_create(GRect(0, 85, 144, 168));
  text_layer_set_background_color(text_layer_bas, GColorClear);
  text_layer_set_text_color(text_layer_bas, GColorBlack);
  text_layer_set_text_alignment(text_layer_bas, GTextAlignmentCenter);
  text_layer_set_font(text_layer_bas, fonts_get_system_font(FONT_KEY_BITHAM_42_LIGHT));
  layer_add_child(window_get_root_layer(window), (Layer*) text_layer_bas); 
  
  //Get a time structure so that the face doesn't start blank
  struct tm *t;
  time_t temp;
  temp = time(NULL);
  t = localtime(&temp); 
  //Manually call the tick handler when the window is loading
  tick_handler(t, MINUTE_UNIT);
}  
 //-- actions à la fermeture de l'application   
void window_unload(Window *window)  
{//We will safely destroy the Window's elements here!
  text_layer_destroy(text_layer_haut);
 text_layer_destroy(text_layer_bas);
}  
 //-- Initialisation  
void init()  
{tick_timer_service_subscribe(MINUTE_UNIT, (TickHandler) tick_handler);  
 window = window_create();  
 window_set_window_handlers(window, (WindowHandlers) {  
   .load = window_load,  
   .unload = window_unload,  
  });  
  window_stack_push(window, true);  
}  
//-- Déinitialisation   
void deinit()  
{tick_timer_service_unsubscribe();   
 window_destroy(window);  
 }  
//-- Fonction principale  
int main(void)  
 {  
  init();  
  app_event_loop();  
  deinit();  
 }  