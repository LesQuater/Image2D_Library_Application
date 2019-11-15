#ifndef DEF_FENETRE
#define DEF_FENETRE

#include <fstream>
#include <vector>
#include <gtkmm.h>
#include "Image2D.h"
class Fenetre : public Gtk::Window {
    public :
        Fenetre();
        void dialogueOuvrirFichier();
        void dialogueNouveau();
        void SaltAndPepper();
        void RealSandP();
        void Convolution();
        void RealConv();
        void RGB2Grey();
        void Grey2RGB();
        void SeuilGrey();
        void RealSeuilGrey();
        void SeuilR();
        void RealSeuilR();
        void SeuilG();
        void RealSeuilG();
        void SeuilB();
        void RealSeuilB();
        void Translate();
        void RealTranslate();
        void Rotate();
        void RealRotate();
        void Mask();
        void RealMask();
        void FiltrageAuto();
        void RealFiltrageAuto();
        void Histo();
        void Info();
        void Autor();

    private :
        Gtk::ScrolledWindow barresDeDefilement;
        Gtk::HButtonBox boiteH;
        Gtk::VBox boiteV;
        //Gtk::Image image;
        Gtk::MenuBar barreMenu;
        Gtk::MenuItem menuItemFichier;
        Gtk::Menu menuFichier;
        Gtk::ImageMenuItem menuNouveau;
        Gtk::ImageMenuItem menuOuvrir;
        Gtk::ImageMenuItem menuQuitter;

        Gtk::MenuItem menuItemTransformation;
        Gtk::Menu menuTransformation;
        Gtk::ImageMenuItem menuRotate;
        Gtk::ImageMenuItem menuTranslate;

        Gtk::MenuItem menuItemConversion;
        Gtk::Menu menuConversion;
        Gtk::ImageMenuItem menuRGB2Grey;
        Gtk::ImageMenuItem menuGrey2RGB;

        Gtk::MenuItem menuItemSeuillage;
        Gtk::Menu menuSeuillage;
        Gtk::ImageMenuItem menuSeuilGrey;
        Gtk::ImageMenuItem menuSeuilR;
        Gtk::ImageMenuItem menuSeuilG;
        Gtk::ImageMenuItem menuSeuilB;

        Gtk::MenuItem menuItemFiltrage;
        Gtk::Menu menuFiltrage;
        Gtk::ImageMenuItem menuSaltAndPepper;
        Gtk::ImageMenuItem menuConv;
        Gtk::ImageMenuItem menuMask;
        Gtk::ImageMenuItem menuFiltrageAuto;

        Gtk::MenuItem menuItemInfo;
        Gtk::Menu menuInfo;
        Gtk::ImageMenuItem menuHisto;
        Gtk::ImageMenuItem menuInfoImage;
        Gtk::ImageMenuItem menuAutor;


        Gtk::Dialog DialogueGrey;
        Gtk::HBox Hbox;
        Gtk::Label txt;
        Gtk::Button bouton;
        Gtk::Entry entry;

        Gtk::Image image;
        Image2D A;
        Image2D B;
};

#endif
