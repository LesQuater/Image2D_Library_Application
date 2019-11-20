#include "Fenetre.hpp"
#include "Image2D.h"

Fenetre::Fenetre() :menuItemSeuillage("Seuillage"),menuItemConversion("Conversion"),menuFiltrageAuto("Filtrage Auto"), menuAutor("Auteur"),menuItemInfo("Information",true),menuHisto("Histogramme"),menuInfoImage("Information Image"), DialogueGrey("Seuillage Gris", *this), menuMask("Masquage"),menuTranslate("Translation"),menuRotate("Rotation"),menuItemFichier("_Fichier",true),menuNouveau(Gtk::Stock::NEW),menuOuvrir(Gtk::Stock::OPEN),menuQuitter(Gtk::Stock::QUIT),menuItemTransformation("Transformation",true),menuRGB2Grey("RGB to Grey"),menuGrey2RGB("Grey to RGB"),menuSeuilGrey("Seuillage Grey"), menuSeuilR("Seuillage Rouge"), menuSeuilG("Seuillage Vert"),menuSeuilB("Seuillage Bleu"),menuItemFiltrage("Filtrage & Bruit",true),menuSaltAndPepper("Salt & Pepper"), menuConv("Convolution"),bouton("Ok"),menuItemDetection("Detection",true),menuHarris("Harris Corner Detection")  {
    //Configurer la fenêtre.
    set_position(Gtk::WIN_POS_CENTER);
    set_default_size(800, 600);
    set_title("Image2D");
    set_icon_from_file("lena.bmp");

    add(boiteV);

    //Configurer les barres de défilement.
    barresDeDefilement.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    barresDeDefilement.add(image);

    //Ajout de widgets dans les boîtes.
    boiteV.pack_start(barreMenu, Gtk::PACK_SHRINK);
    boiteV.pack_start(barresDeDefilement);
    boiteV.pack_start(Hbox, Gtk::PACK_SHRINK);
    Hbox.pack_start(txt,Gtk::PACK_EXPAND_PADDING);
    Hbox.pack_start(entry);
    Hbox.pack_start(bouton,Gtk::PACK_EXPAND_PADDING);
    //txt.set_label("coucou");


    barreMenu.append(menuItemFichier);
    menuItemFichier.set_submenu(menuFichier);
    menuFichier.append(menuOuvrir);
    menuFichier.append(menuNouveau);
    menuFichier.append(menuQuitter);

    barreMenu.append(menuItemConversion);
    menuItemConversion.set_submenu(menuConversion);
    menuConversion.append(menuRGB2Grey);
    menuConversion.append(menuGrey2RGB);

    barreMenu.append(menuItemSeuillage);
    menuItemSeuillage.set_submenu(menuSeuillage);
    menuSeuillage.append(menuSeuilGrey);
    menuSeuillage.append(menuSeuilR);
    menuSeuillage.append(menuSeuilG);
    menuSeuillage.append(menuSeuilB);

    barreMenu.append(menuItemTransformation);
    menuItemTransformation.set_submenu(menuTransformation);
    menuTransformation.append(menuRotate);
    menuTransformation.append(menuTranslate);

    barreMenu.append(menuItemFiltrage);
    menuItemFiltrage.set_submenu(menuFiltrage);
    menuFiltrage.append(menuSaltAndPepper);
    menuFiltrage.append(menuConv);
    menuFiltrage.append(menuMask);
    menuFiltrage.append(menuFiltrageAuto);

    barreMenu.append(menuItemDetection);
    menuItemDetection.set_submenu(menuDetection);
    menuDetection.append(menuHarris);

    barreMenu.append(menuItemInfo);
    menuItemInfo.set_submenu(menuInfo);
    menuInfo.append(menuHisto);
    menuInfo.append(menuInfoImage);
    menuInfo.append(menuAutor);

    //Connexion des signaux aux fonctions de rappel.
    menuOuvrir.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::dialogueOuvrirFichier));
    menuNouveau.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::dialogueNouveau));
    menuSaltAndPepper.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::SaltAndPepper));
    menuConv.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Convolution));
    menuRGB2Grey.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::RGB2Grey));
    menuGrey2RGB.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Grey2RGB));
    menuSeuilGrey.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::SeuilGrey));
    menuSeuilR.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::SeuilR));
    menuSeuilG.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::SeuilG));
    menuSeuilB.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::SeuilB));
    menuRotate.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Rotate));
    menuTranslate.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Translate));
    menuMask.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Mask));
    menuFiltrageAuto.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::FiltrageAuto));
    menuHarris.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Harris));
    menuHisto.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Histo));
    menuInfoImage.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Info));
    menuAutor.signal_activate().connect(sigc::mem_fun(*this, &Fenetre::Autor));


    menuQuitter.signal_activate().connect(sigc::ptr_fun(&Gtk::Main::quit));

    show_all();
}
void Fenetre::Mask(){
  txt.set_label("Masque : image path\n Exemple : mask.bmp");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealMask));
}
void Fenetre::RealMask(){
  char* X;
  std::string Xstr;
  std::string txt = entry.get_text().c_str();
  std::istringstream iss(txt);
  std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                             std::istream_iterator<std::string>());
  Xstr = results[0];
  X = &txt[0];
  Image2D J("mask.bmp",1.0,1.0,"grey");
  A.Masque(J);
  A.createBMP("A_Mask.bmp");
  image.set("A_Mask.bmp");
}
void Fenetre::Translate() {
    txt.set_label("Translation : X Y\n Exemple : 50 10");
    bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealTranslate));
}
void Fenetre::RealTranslate(){
  int X;
  int Y;
  std::string txt = entry.get_text().c_str();
  std::istringstream iss(txt);
  std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                             std::istream_iterator<std::string>());
 X = stoi(results[0]);
 Y = stoi(results[1]);

  A.translate(X,Y);
  A.createBMP("A_Trans.bmp");
  image.set("A_Trans.bmp");
}

  void Fenetre::Rotate() {
    txt.set_label("Rotate : teta\n Exemple : 20°");
    bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealRotate));
  }
  void Fenetre::RealRotate(){
    float X;
    std::string txt = entry.get_text().c_str();
    std::istringstream iss(txt);
    std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                               std::istream_iterator<std::string>());
    X = stof(results[0]);
    A.rotate(X);
    A.createBMP("A_Rotate.bmp");
    image.set("A_Rotate.bmp");
  }

void Fenetre::dialogueOuvrirFichier() {
    //Création d'une boîte de dialogue d'ouverture de fichier.
    Gtk::FileChooserDialog dialogue(*this, "Ouverture d'un fichier");

    //Ajout de boutons.
    dialogue.add_button(Gtk::Stock::CANCEL, Gtk::RESPONSE_CANCEL);
    dialogue.add_button(Gtk::Stock::OPEN, Gtk::RESPONSE_OK);

    int resultat = dialogue.run();

    if(resultat == Gtk::RESPONSE_OK) {
        //Obtenir le nom du fichier.
        std::string nomFichier = dialogue.get_filename();
        image.set(nomFichier);
        char* nom = &nomFichier[0];
        Image2D B(nom,4.0,4.0,"RGB");
        A = B;
    }
}

void Fenetre::dialogueNouveau() {
      Image2D C(300,300,255,10.0,10.0,255);
      C.Grey_to_RGB();
      A = C;
      C.createBMP();
      image.set("A.bmp");
}

void Fenetre::SaltAndPepper() {

  txt.set_label("Nombre de points :\n Exemple : 1000");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealSandP));

}
void Fenetre::RealSandP(){
  int X;
  std::string txt = entry.get_text().c_str();
  std::istringstream iss(txt);
  std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                             std::istream_iterator<std::string>());
  X = stoi(results[0]);
  A.saltAndPepper(X);
  A.createBMP("A_SP.bmp");
  image.set("A_SP.bmp");
}
void Fenetre::Convolution() {
    txt.set_label("Convolution : kernel\n Exemple : Moy3;Moy5;HP3;Sobel : Gx;Gy; LP3;Laplacien : Laplace3;\n Prewitt : My;Mz; Gaussien : Gauss5\n Horizontal : H; Vertical : V; Oblique : O1;O2");
    bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealConv));
}
void Fenetre::RealConv(){
  std::string X;
  std::string txt = entry.get_text().c_str();
  std::istringstream iss(txt);
  std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                             std::istream_iterator<std::string>());
    X = results[0];
    if(X== "Moy3"){
        A.convolution(0);
        A.createBMP("A_ConvMoy3.bmp");
        image.set("A_ConvMoy3.bmp");
    }
    else if(X=="Moy5"){
        A.convolution(1);
        A.createBMP("A_ConvMoy5.bmp");
        image.set("A_ConvMoy5.bmp");
    }
    else if(X=="HP3"){
        A.convolution(3);
        A.createBMP("A_ConvHP.bmp");
        image.set("A_ConvHP.bmp");
    }
    else if(X=="Gx"){
        A.convolution(4);
        A.createBMP("A_ConvGx.bmp");
        image.set("A_ConvGx.bmp");
    }
    else if(X=="Gy"){
        A.convolution(5);
        A.createBMP("A_ConvGy.bmp");
        image.set("A_ConvGy.bmp");
    }
    else if(X=="LP3"){
        A.convolution(6);
        A.createBMP("A_ConvLP3.bmp");
        image.set("A_ConvLP3.bmp");
    }
    else if(X=="Laplace3"){
        A.convolution(7);
        A.createBMP("A_ConvLaplace3.bmp");
        image.set("A_ConvLaplace3.bmp");
    }
    else if(X=="My"){
        A.convolution(8);
        A.createBMP("A_ConvMy.bmp");
        image.set("A_ConvMy.bmp");
    }
    else if(X=="Mz"){
        A.convolution(9);
        A.createBMP("A_ConvMz.bmp");
        image.set("A_ConvMz.bmp");
    }
    else if(X=="Gauss5"){
        A.convolution(12);
        A.createBMP("A_ConvGauss5.bmp");
        image.set("A_ConvGauss5.bmp");
    }
    else if(X=="H"){
        A.convolution(13);
        A.createBMP("A_ConvH.bmp");
        image.set("A_ConvH.bmp");
    }
    else if(X=="V"){
        A.convolution(14);
        A.createBMP("A_ConvV.bmp");
        image.set("A_ConvV.bmp");
    }
    else if(X=="O1"){
        A.convolution(15);
        A.createBMP("A_ConvO1.bmp");
        image.set("A_ConvO1.bmp");
    }
    else if(X=="O2"){
        A.convolution(16);
        A.createBMP("A_ConvO2.bmp");
        image.set("A_ConvO2.bmp");
    }
}
void Fenetre::RGB2Grey(){
    if(A.get_option() == "RGB"){
        A.RGB_to_Grey();
        A.createBMP("A_Grey.bmp");
        image.set("A_Grey.bmp");
    }
    else{
        Gtk::MessageDialog dialogue(*this, "Image n'est pas en RGB", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
        dialogue.set_title("Erreur");
        dialogue.set_secondary_text("Utilisez Grey_to_RGB");
        dialogue.run();
    }
}
void Fenetre::Grey2RGB(){
  if(A.get_option() == "grey"){
      A.Grey_to_RGB();
      A.createBMP("A_RGB.bmp");
      image.set("A_RGB.bmp");
  }
  else{
      Gtk::MessageDialog dialogue(*this, "Image n'est pas en grey", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialogue.set_title("Erreur");
      dialogue.set_secondary_text("Utilisez RGB_to_Grey");
      dialogue.run();
  }
}
void Fenetre::SeuilGrey(){
  txt.set_label("Sueil :\n Exemple : 150");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealSeuilGrey));
}
void Fenetre::RealSeuilGrey(){
  if(A.get_option() == "grey"){
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      A.seuillageGreyImage(X);
      A.createBMP("A_SeuilGrey.bmp");
      image.set("A_SeuilGrey.bmp");
  }
  else{
      Gtk::MessageDialog dialogue(*this, "Image n'est pas en grey", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialogue.set_title("Erreur");
      dialogue.set_secondary_text("Utilisez RGB_to_Grey");
      dialogue.run();
  }
}
void Fenetre::SeuilR(){
  txt.set_label("Sueil Rouge:\n Exemple : 150");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealSeuilR));
}
void Fenetre::RealSeuilR(){
  if(A.get_option() == "RGB"){
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      A.seuillageImage(X,"R");
      A.createBMP("A_SeuilR.bmp");
      image.set("A_SeuilR.bmp");
}
  else{
      Gtk::MessageDialog dialogue(*this, "Image n'est pas en RGB", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialogue.set_title("Erreur");
      dialogue.set_secondary_text("Utilisez Grey_to_RGB");
      dialogue.run();
  }
}
void Fenetre::SeuilG(){
  txt.set_label("Sueil Vert:\n Exemple : 150");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealSeuilG));
}
void Fenetre::RealSeuilG(){
  if(A.get_option() == "RGB"){
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      A.seuillageImage(X,"G");
      A.createBMP("A_SeuilG.bmp");
      image.set("A_SeuilG.bmp");
}
  else{
      Gtk::MessageDialog dialogue(*this, "Image n'est pas en RGB", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialogue.set_title("Erreur");
      dialogue.set_secondary_text("Utilisez Grey_to_RGB");
      dialogue.run();
  }
}
void Fenetre::SeuilB(){
  txt.set_label("Sueil Bleu:\n Exemple : 150");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealSeuilB));
}
void Fenetre::RealSeuilB(){
  if(A.get_option() == "RGB"){
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      A.seuillageImage(X,"B");
      A.createBMP("A_SeuilB.bmp");
      image.set("A_SeuilB.bmp");
}
  else{
      Gtk::MessageDialog dialogue(*this, "Image n'est pas en RGB", false, Gtk::MESSAGE_ERROR, Gtk::BUTTONS_CLOSE);
      dialogue.set_title("Erreur");
      dialogue.set_secondary_text("Utilisez Grey_to_RGB");
      dialogue.run();
  }
}
void Fenetre::FiltrageAuto(){
  txt.set_label("Filtrage Auto : Delta Color\n Exemple : 100 R");
  bouton.signal_clicked().connect(sigc::mem_fun(*this, &Fenetre::RealFiltrageAuto));
}
void Fenetre::RealFiltrageAuto(){
  if(A.get_option() == "grey"){
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      A.filtrageAuto_histogramme(X);
      A.createBMP("A_FiltrageAuto.bmp");
      image.set("A_FiltrageAuto.bmp");
  }
  else{
      int X;
      std::string txt = entry.get_text().c_str();
      std::istringstream iss(txt);
      std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                 std::istream_iterator<std::string>());
      X = stoi(results[0]);
      std::string Color = results[1];
      A.filtrageAuto_histogramme(X, Color);
      A.createBMP("A_FiltrageAuto.bmp");
      image.set("A_FiltrageAuto.bmp");
  }
}
void Fenetre::Harris(){
  A.CornerDetection();
  A.createBMP("A_Harris.bmp");
  image.set("A_Harris.bmp");
  //bouton.signal_clicked().connect();
}
void Fenetre::Histo(){
  A.histogramme();
  A.print_histogramme();
  image.set("histo.bmp");
  //bouton.signal_clicked().connect();
}

void Fenetre::Info(){
  std::string info = "Taille : "+std::to_string(A.get_nbX())+"x"+std::to_string(A.get_nbY())+" pixels\n Option : "+A.get_option()+"\n Chemin : "+A.get_path()+"\n";
  txt.set_label(info);
  //bouton.signal_clicked().connect();
}
void Fenetre::Autor(){
  txt.set_label("Alan Métivier\nRennes, France");
  //bouton.signal_clicked().connect();
}
