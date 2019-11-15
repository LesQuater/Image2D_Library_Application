#include <iostream>
#include <cstdio>
#include <gtkmm.h>
#include "Image2D.h"
#include "Fenetre.hpp"
using namespace std;

int main(int argc, char* argv[])
{
  Gtk::Main app(argc, argv);
  Fenetre fenetre;
  Gtk::Main::run(fenetre);
  return 0;
}
