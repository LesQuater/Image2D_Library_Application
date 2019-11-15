#include <iostream>
#include <cstdio>
#include "Image2D.h"
using namespace std;

int main()
{
    Image2D A;
    Image2D B(100,200,255,10.0,10.0,100);
    cout << "A.createBMP()\n";
    A.createBMP();
    cout << "B.createBMP(Out2.bmp)\n";
    B.createBMP("OUT2.bmp");

    cout << "Image2D A\n";
    cout<<"Nb X : "<<A.get_nbX()<<"\n";
    cout<<"Nb Y : "<<A.get_nbY()<<"\n";
    cout<<"Max grey value : "<<A.get_maxValue()<<"\n";
    cout<<"Nb Pixels : "<<A.get_nbPixel()<<"\n";
    cout<<"Taille X pixel : "<<A.get_dx()<<"\n";
    cout<<"Taille Y pixel : "<<A.get_dy()<<"\n";
    cout<<"Path : "<<A.get_path()<<"\n";
    printf("Header : %s\n", A.get_header());
    cout<<"Value_R[i][j] : "<<A.get_R_PixelValue(10,15)<<"\n";
    cout<<"otpion : "<<A.get_option()<<"\n";

    Image2D C = A;
    int C_NbX = C.get_nbX();
    int C_NbY = C.get_nbY();
    for(int i=1;i<C_NbX;i=i+5){
        for(int j=1;j<C_NbY;j=j+5){
            C.set_PixelValue(i,j,0,0,50); //vert
        }
    }
    C.createBMP("OUT3.bmp");

    Image2D D("lena.bmp",4.0,4.0,"grey");
    cout << D.get_option()<<"\n";
    D.createBMP("lenaGrey.bmp");
    D.translate(100,100);
    D.createBMP("lenaTranslate.bmp");
    D.saltAndPepper(10000);
    D.createBMP("lenaS&P.bmp");
    D.seuillageGreyImage(70);
    D.createBMP("lenaSeuillage.bmp");
    D.Grey_to_RGB();
    D.seuillageImage(180,"R");
    D.RGB_to_Grey();
    D.createBMP("lenaGrey2RGBseuil.bmp");


    Image2D E("lena.bmp",4.0,4.0,"RGB");
    cout << E.get_option()<<"\n";
    E.createBMP("lenaRGB.bmp");
    E.seuillageImage(180,"R");
    E.createBMP("lenaSeuilR.bmp");
    E.seuillageImage(180,"G");
    E.createBMP("lenaSeuilR+G.bmp");
    E.saltAndPepper(10000);
    E.createBMP("lenaRGB_S&P.bmp");
    E.RGB_to_Grey();
    E.createBMP("lenaRGB_S&P_grey.bmp");

    Image2D H("lena.bmp",4.0,4.0,"grey");
    H.createBMP("H.bmp");
    H.rotate(45.0);
    H.createBMP("H_rotate.bmp");

    Image2D F("lena.bmp",4.0,4.0,"grey");
    F.createBMP("F.bmp");
    F.histogramme();
    F.print_histogramme();
    /*int valueGrey = 0;
    Image2D Histo(255,100,255,1.0,1.0,255);
    for(int i=0;i<255;i++){
      valueGrey = F.get_histoGrey(i);
      valueGrey = (valueGrey * 100)/F.get_nbPixel();
      for(int j = 0; j<valueGrey;j++){
          Histo.set_Grey_PixelValue(i,j,0);
      }
    }
    Histo.createBMP("histo.bmp");*/
    /*
    /*int** Kernel = new int* [3];
    for (int i=0; i<3 ; i++){
      Kernel[i] = new int[3];
    }*/
    cout << F.get_option()<<"\n";
    F.convolution(0);
    F.createBMP("F_Conv.bmp");
    F.convolution(1);
    F.createBMP("F_Conv2.bmp");
    Image2D K("lena.bmp",1.0,1.0,"grey");
    K.convolution(3);//High_Pass
    K.createBMP("K_High.bmp");

    Image2D I("lena.bmp",1.0,1.0,"grey");
    Image2D J("mask.bmp",1.0,1.0,"grey");
    I.Masque(J);
    I.createBMP("I_Mask.bmp");


    return 0;
}
