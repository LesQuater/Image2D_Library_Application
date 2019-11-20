#ifndef IMAGE2D_H
#define IMAGE2D_H
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>

class Image2D
{
    public:

        Image2D();
        Image2D(int nbX, int nbY, int maxValue, double dx, double dy, int initValue);
        Image2D(char* chemin, double x, double y, std::string option);
        ~Image2D();

        int get_nbX();
        int get_nbY();
        int get_maxValue();
        int get_nbPixel();
        double get_dx();
        double get_dy();
        unsigned char* get_header();
        std::string get_path();
        std::string get_option();
        int get_histoGrey(int i);

        void set_nbX(int X);
        void set_nbY(int Y);
        void set_maxValue(int max);
        void set_nbPixel(int imageSize, int x);
        void set_dx(double x);
        void set_dy(double y);
        void set_header(unsigned char head[54]);
        void set_path(char* chemin);

        int get_R_PixelValue(int i, int j);
        int get_G_PixelValue(int i, int j);
        int get_B_PixelValue(int i, int j);
        void set_PixelValue(int i, int j, int value_R, int value_G, int value_B);
        void set_R_PixelValue(int i, int j, int value_R);
        void set_G_PixelValue(int i, int j, int value_G);
        void set_B_PixelValue(int i, int j, int value_B);
        void set_Grey_PixelValue(int i, int j, int value_Grey);
// Cr�er fichier image
        void createBMP();
        void createBMP(char* chemin);
// Trnasformation image
        void seuillageGreyImage(int seuil);
        void seuillageImage(int seuil,std::string composante);

        void RGB_to_Grey();
        void Grey_to_RGB();

        void saltAndPepper(int nbPoint);
        void CornerDetection();
// Convolution
        //Image2D & operator*(const Image2D& p2);
        Image2D & operator= (const Image2D & p2);
        Image2D & operator+ (const Image2D & p2);
        Image2D & operator== (const Image2D & p2);

        void print_histogramme();
        void histogramme();

        void convolution(int type);
        void rotate(double teta);
        void translate(int x, int y);
        void Masque(const Image2D & p2);

        void filtrageAuto_histogramme(int delta);
        void filtrageAuto_histogramme(int delta, std::string color);


    protected:

        void alloue_partie_dynamique(int dimx, int dimy);
        void libere_partie_dynamique();
        void init(int initValue);

    private:

        int nbX;
        int nbY;
        int maxValue;
        int nbPixel;
        double dx;
        double dy;
        unsigned char header[54];
        std::string path;
        std::string option;
        int** ptrR;
        int** ptrB;
        int** ptrG;
        int** ptrGrey;
        int* histoR;
        int* histoG;
        int* histoB;
        int* histoGrey;

};

#endif
