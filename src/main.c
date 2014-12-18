//-- Affichage et utilisation de Pebble Graphic UI
//-- Ici on a défini un écran dénommé testwindow
#include <pebble.h>
#include "testwindow.h" //-- Contient la fenêtre définie

int main() {
  show_testwindow(); //-- Fonction définie dans testwindow.c
  app_event_loop();
  hide_testwindow(); //-- Fonction définie dans testwindow.c
  return 0;
}

