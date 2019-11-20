#include <iostream>
#include "Image2D.h"
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include "math.h"
#define LONGUEUR_ENTETE 54
Image2D::Image2D(){
    path = "OUT.bmp";
    nbX = 128;
    nbY = 128;
    maxValue = 255;
    nbPixel = nbX*nbY;
    dx=1;
    dy=1;
    alloue_partie_dynamique(128,128);
    option = "RGB";
    unsigned char head[54]={0x42 ,0x4d ,//BM
        0x36 ,0xc0 ,0x0 ,0x0 ,//File size 54+(nbx*nby)*3
        0x0 ,0x0 ,0x0 ,0x0 ,//unused
        0x36 ,0x0 ,0x0 ,0x0 ,//Offset from beginning to file 54 //start of infoheader
        0x28 ,0x0 ,0x0 ,0x0 ,//size of info header=40
        0x80 ,0x0 ,0x0 ,0x0 ,//width
        0x80 ,0x0 ,0x0 ,0x0 ,//height
        0x1 ,0x0 ,//planes
        0x18 ,0x0 ,//bits per pixel
        0x0 ,0x0 ,0x0 ,0x0 ,//No compression
        0x0 ,0x0 ,0xc ,0x0 ,//Image size, no compression
        0x74 ,0x12 ,0x0 ,0x0 ,//horizontal resolution: Pixels/meter
        0x74 ,0x12 ,0x0 ,0x0 ,//vertical resolution: Pixels/meter
        0x0 ,0x0 ,0x0 ,0x0 ,//Colors Used
        0x0 ,0x0 ,0x0 ,0x0};  //Important Colors
    for(int k=0;k<54;k++){
        header[k]=head[k];
    }


    for(int i=0;i<nbX;i++){
        for(int j=0;j<nbY;j++){
            ptrR[i][j] = 255;
            ptrG[i][j] = 255;
            ptrB[i][j] = 255;
            ptrGrey[i][j] = 0;
        }
    }

}
Image2D::Image2D(int X, int Y, int maxVal, double x, double y, int initValue){
    path = "OUT.bmp";
    nbX = X;
    nbY = Y;
    maxValue = maxVal;
    nbPixel = X*Y;
    int fileSize = (nbPixel*3)+54;
    dx=x;
    dy=y;
    option = "grey";
    alloue_partie_dynamique(nbX,nbY);
    for(int i=0;i<nbX;i++){
        for(int j=0;j<nbY;j++){
            ptrR[i][j] = 0;
            ptrG[i][j] = 0;
            ptrB[i][j] = 0;
            ptrGrey[i][j] = initValue;
        }
    }

    unsigned char fileSizeBIT[4];
    fileSizeBIT[0] = fileSize >>0;
    fileSizeBIT[1] = fileSize >>8;
    fileSizeBIT[2] = fileSize >>16;
    fileSizeBIT[3] = fileSize >>24;

    unsigned char nbXBIT[4];
    nbXBIT[0] = nbX >>0;
    nbXBIT[1] = nbX >>8;
    nbXBIT[2] = nbX >>16;
    nbXBIT[3] = nbX >>24;

    unsigned char nbYBIT[4];
    nbYBIT[0] = nbY >>0;
    nbYBIT[1] = nbY >>8;
    nbYBIT[2] = nbY >>16;
    nbYBIT[3] = nbY >>24;

    unsigned char maxValueBIT[2];
    maxValueBIT[0] = maxValue >>0;
    maxValueBIT[1] = maxValue >>8;

    int dxValue = (int)(x*1000);
    int dyValue = (int)(y*1000);

    unsigned char dxValueBIT[4];
    dxValueBIT[0] = dxValue >>0;
    dxValueBIT[1] = dxValue >>8;
    dxValueBIT[2] = dxValue >>16;
    dxValueBIT[3] = dxValue >>24;

    unsigned char dyValueBIT[4];
    dyValueBIT[0] = dyValue >>0;
    dyValueBIT[1] = dyValue >>8;
    dyValueBIT[2] = dyValue >>16;
    dyValueBIT[3] = dyValue >>24;
    unsigned char head[54]={0x42 ,0x4d ,//BM
        fileSizeBIT[0] ,fileSizeBIT[1] ,fileSizeBIT[2] ,fileSizeBIT[3] ,//File size 54+(nbx*nby)*3
        0x0 ,0x0 ,0x0 ,0x0 ,//unused
        0x36 ,0x0 ,0x0 ,0x0 ,//Offset from beginning to file 54 //start of infoheader
        0x28 ,0x0 ,0x0 ,0x0 ,//size of info header=40
        nbXBIT[0] ,nbXBIT[1] ,nbXBIT[2] ,nbXBIT[3] ,//width
        nbYBIT[0] ,nbYBIT[1] ,nbYBIT[2] ,nbYBIT[3] ,//height
        0x1 ,0x0 ,//planes
        0x18 ,0x0 ,//maxValueBIT[0] ,maxValueBIT[1] ,//bits per pixel
        0x0 ,0x0 ,0x0 ,0x0 ,//No compression
        0x0 ,0x0 ,0xc ,0x0 ,//Image size, no compression
        dxValueBIT[0] ,dxValueBIT[1] ,dxValueBIT[2] ,dxValueBIT[3] ,//horizontal resolution: Pixels/meter
        dyValueBIT[0] ,dyValueBIT[1] ,dyValueBIT[2] ,dyValueBIT[3] ,//vertical resolution: Pixels/meter
        0x0 ,0x0 ,0x0 ,0x0 ,//Colors Used
        0x0 ,0x0 ,0x0 ,0x0};
    for(int k=0;k<54;k++){
        header[k]=head[k];
    }

}
Image2D::Image2D(char* chemin, double x, double y, std::string opt){

    FILE* fp;
    fp=fopen(chemin,"rb+");
    unsigned char head[LONGUEUR_ENTETE+1];
    fread(head,sizeof(unsigned char),LONGUEUR_ENTETE,fp);
    int width;
    int height;
    width = head[18] + (head[19] << 8) + (head[20] << 16) + (head[21] << 24);
    height = head[22] + (head[23] << 8) + (head[24] << 16) + (head[25] << 24);
    nbX = width;
    nbY = height;
    nbPixel = nbX*nbY;
    path = chemin;
    alloue_partie_dynamique(nbX,nbY);
    unsigned char* image =(unsigned char*)malloc((nbPixel*3)*sizeof(unsigned char));
    unsigned char* R =(unsigned char*)malloc((nbPixel)*sizeof(unsigned char));
    unsigned char* G =(unsigned char*)malloc((nbPixel)*sizeof(unsigned char));
    unsigned char* B =(unsigned char*)malloc((nbPixel)*sizeof(unsigned char));

    fread(image,sizeof(char),nbPixel*3,fp);
    option=opt;
    if(option == "grey"){
        for(int l=0;l<nbPixel; l++){
            G[l] = image[3*l];
            B[l] = image[3*l+1];
            R[l] = image[3*l+2];
        }
        for (int i=0; i<nbX; i++) {
            for (int j=0; j<nbY; j++) {
                ptrGrey[i][j] = ((double)B[i*(nbY)+j]+(double)G[i*(nbY)+j]+(double)R[i*(nbY)+j])/3;
                ptrR[i][j] = 0;
                ptrG[i][j] = 0;
                ptrB[i][j] = 0;
            }
        }
    }
    else if(option == "RGB"){
        for(int l=0;l<nbPixel; l++){
            G[l] = image[3*l];
            B[l] = image[3*l+1];
            R[l] = image[3*l+2];
        }
        for (int i=0; i<nbX; i++) {
            for (int j=0; j<nbY; j++) {
                ptrR[i][j] = (double)R[i*(nbY)+j];
                ptrG[i][j] = (double)G[i*(nbY)+j];
                ptrB[i][j] = (double)B[i*(nbY)+j];
                ptrGrey[i][j] = 0;
            }
        }
    }
    dx = x;
    dy = y;
    for(int k=0;k<54;k++){
        header[k]=head[k];
    }
}
Image2D::~Image2D(){
    libere_partie_dynamique();
}

int Image2D::get_nbX(){
    return nbX;
}
int Image2D::get_nbY(){
    return nbY;
}
int Image2D::get_maxValue(){
    return maxValue;
}
int Image2D::get_nbPixel(){
    return nbPixel;
}
double Image2D::get_dx(){
    return dx;
}
double Image2D::get_dy(){
    return dy;
}
unsigned char* Image2D::get_header(){
    return header;
}
std::string Image2D::get_path(){
    return path;
}
std::string Image2D::get_option(){
    return option;
}
int Image2D::get_histoGrey(int i){
    return histoGrey[i];
}

void Image2D::set_nbX(int X){
    nbX = X;
    unsigned char nbXBIT[4];
    nbXBIT[0] = X >>0;
    nbXBIT[1] = X >>8;
    nbXBIT[2] = X >>16;
    nbXBIT[3] = X >>24;
    header[18]=nbXBIT[0];
    header[19]=nbXBIT[1];
    header[20]=nbXBIT[2];
    header[21]=nbXBIT[3];

    nbPixel = nbX*nbY;
    int fileSize = (nbPixel*3)+54;
    unsigned char fileSizeBIT[4];
    fileSizeBIT[0] = fileSize >>0;
    fileSizeBIT[1] = fileSize >>8;
    fileSizeBIT[2] = fileSize >>16;
    fileSizeBIT[3] = fileSize >>24;
    header[2]=fileSizeBIT[0];
    header[3]=fileSizeBIT[1];
    header[4]=fileSizeBIT[2];
    header[5]=fileSizeBIT[3];


}
void Image2D::set_nbY(int Y){
    nbX = Y;
    unsigned char nbYBIT[4];
    nbYBIT[0] = Y >>0;
    nbYBIT[1] = Y >>8;
    nbYBIT[2] = Y >>16;
    nbYBIT[3] = Y >>24;
    header[22]=nbYBIT[0];
    header[23]=nbYBIT[1];
    header[24]=nbYBIT[2];
    header[25]=nbYBIT[3];

    nbPixel = nbX*nbY;
    int fileSize = (nbPixel*3)+54;
    unsigned char fileSizeBIT[4];
    fileSizeBIT[0] = fileSize >>0;
    fileSizeBIT[1] = fileSize >>8;
    fileSizeBIT[2] = fileSize >>16;
    fileSizeBIT[3] = fileSize >>24;
    header[2]=fileSizeBIT[0];
    header[3]=fileSizeBIT[1];
    header[4]=fileSizeBIT[2];
    header[5]=fileSizeBIT[3];
}
void Image2D::set_maxValue(int max){
    maxValue = max;
}
void Image2D::set_nbPixel(int imageSize, int X){
    nbPixel = imageSize;
    nbX = X;
    nbY = nbPixel/nbX - (nbPixel/nbX);
    int Y = nbY;
    unsigned char nbXBIT[4];
    nbXBIT[0] = X >>0;
    nbXBIT[1] = X >>8;
    nbXBIT[2] = X >>16;
    nbXBIT[3] = X >>24;
    header[18]=nbXBIT[0];
    header[19]=nbXBIT[1];
    header[20]=nbXBIT[2];
    header[21]=nbXBIT[3];
    unsigned char nbYBIT[4];
    nbYBIT[0] = Y >>0;
    nbYBIT[1] = Y >>8;
    nbYBIT[2] = Y >>16;
    nbYBIT[3] = Y >>24;
    header[22]=nbYBIT[0];
    header[23]=nbYBIT[1];
    header[24]=nbYBIT[2];
    header[25]=nbYBIT[3];
    int fileSize = (nbPixel*3)+54;
    unsigned char fileSizeBIT[4];
    fileSizeBIT[0] = fileSize >>0;
    fileSizeBIT[1] = fileSize >>8;
    fileSizeBIT[2] = fileSize >>16;
    fileSizeBIT[3] = fileSize >>24;
    header[2]=fileSizeBIT[0];
    header[3]=fileSizeBIT[1];
    header[4]=fileSizeBIT[2];
    header[5]=fileSizeBIT[3];
}
void Image2D::set_dx(double x){
    dx = x;
}
void Image2D::set_dy(double y){
    dy = y;
}
void Image2D::set_header(unsigned char head[54]){
    for(int i=0;i<54;i++){
        header[i]=head[i];
    }
}
void Image2D::set_path(char* chemin){
    path = chemin;
}

int Image2D::get_R_PixelValue(int i, int j){
    if(option =="RGB"){
      return ptrR[i][j];
  }
    else{std::cout<<"Not RGB, use Grey_to_RGB\n";return 1;}
}
int Image2D::get_G_PixelValue(int i, int j){
    if(option =="RGB"){
      return ptrG[i][j];
  }
    else{std::cout<<"Not RGB, use Grey_to_RGB\n";return 1;}
}
int Image2D::get_B_PixelValue(int i, int j){
    if(option =="RGB"){
      return ptrB[i][j];
  }
    else{std::cout<<"Not RGB, use Grey_to_RGB\n";return 1;}
}

void Image2D::set_PixelValue(int i, int j, int value_R, int value_G, int value_B){
    ptrR[i][j]=value_R;
    ptrG[i][j]=value_G;
    ptrB[i][j]=value_B;
}
void Image2D::set_R_PixelValue(int i, int j, int value_R){
    ptrR[i][j]=value_R;
}
void Image2D::set_G_PixelValue(int i, int j,int value_G){
    ptrG[i][j]=value_G;
}
void Image2D::set_B_PixelValue(int i, int j,int value_B){
    ptrB[i][j]=value_B;
}
void Image2D::set_Grey_PixelValue(int i, int j,int value_Grey){
    ptrGrey[i][j]=value_Grey;
}

void Image2D::createBMP(){
    FILE* fp;
    fp=fopen("OUT.bmp","wb+");
    fwrite(header,sizeof(unsigned char),LONGUEUR_ENTETE,fp);
    if(option=="RGB"){
        for(int i=0;i<nbX;i++){
            for(int j=0;j<nbY;j++){
                fwrite(&ptrG[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrB[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrR[i][j],sizeof(unsigned char),1,fp);
            }
        }
    }
    else if(option=="grey"){
        for(int i=0;i<nbX;i++){
            for(int j=0;j<nbY;j++){
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
            }
        }
    }
}
void Image2D::createBMP(char* chemin){
    FILE* fp;
    fp=fopen(chemin,"wb+");
    path=chemin;
    fwrite(header,sizeof(unsigned char),LONGUEUR_ENTETE,fp);
    if(option=="RGB"){
        for(int i=0;i<nbX;i++){
            for(int j=0;j<nbY;j++){
                fwrite(&ptrG[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrB[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrR[i][j],sizeof(unsigned char),1,fp);
            }
        }
    }
    else if(option=="grey"){
        for(int i=0;i<nbX;i++){
            for(int j=0;j<nbY;j++){
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
                fwrite(&ptrGrey[i][j],sizeof(unsigned char),1,fp);
            }
        }
    }
    else{
            std::cout<<"Error";
            }
}

void Image2D::seuillageGreyImage(int seuil){
    if(option=="grey"){
        for(int i=0;i<nbX;i++){
            for(int j=0;j<nbY;j++){

                if(ptrGrey[i][j]<seuil){
                    ptrGrey[i][j]=0;
                }
                else{
                    ptrGrey[i][j]=255;
                }
            }
        }
    }
    else{
        std::cout<<"Impossible votre image n'est pas en grey, vous pouvez utiliser RBG_to_Grey() de Image2D";
    }
}
void Image2D::seuillageImage(int seuil,std::string composante){
        if(composante=="R"){
            for(int i=0;i<nbX;i++){
                for(int j=0;j<nbY;j++){

                    if(ptrR[i][j]<seuil){
                        ptrR[i][j]=0;
                        ptrG[i][j]=0;
                        ptrB[i][j]=0;
                    }
                    else{
                        ptrR[i][j]=255;
                        ptrG[i][j]=0;
                        ptrB[i][j]=0;
                    }
                }
            }
        }
        else if(composante=="G"){
            for(int i=0;i<nbX;i++){
                for(int j=0;j<nbY;j++){

                    if(ptrG[i][j]<seuil){
                        ptrG[i][j]=0;
                        ptrR[i][j]=0;
                        ptrB[i][j]=0;
                    }
                    else{
                        ptrG[i][j]=255;
                        ptrR[i][j]=0;
                        ptrB[i][j]=0;
                    }
                }
            }
    }
        else if(composante=="B"){
            for(int i=0;i<nbX;i++){
                for(int j=0;j<nbY;j++){

                    if(ptrB[i][j]<seuil){
                        ptrB[i][j]=0;
                        ptrG[i][j]=0;
                        ptrR[i][j]=0;
                    }
                    else{
                        ptrB[i][j]=255;
                        ptrG[i][j]=0;
                        ptrR[i][j]=0;
                    }
                }
            }
    }
}
void Image2D::RGB_to_Grey(){
  if(option == "RGB"){
    for(int i=0;i<nbX;i++){
        for(int j=0;j<nbY;j++){
            ptrGrey[i][j] = (ptrR[i][j]+ptrG[i][j]+ptrB[i][j])/3;
            ptrR[i][j] = 0;
            ptrG[i][j] = 0;
            ptrB[i][j] = 0;
        }
    }
    option = "grey";
  }
  else{std::cout<<"Déjà en grey \n";}
}
void Image2D::Grey_to_RGB(){
  if(option == "grey"){
    for(int i=0;i<nbX;i++){
        for(int j=0;j<nbY;j++){
            ptrR[i][j] = ptrGrey[i][j];
            ptrG[i][j] = ptrGrey[i][j];
            ptrB[i][j] = ptrGrey[i][j];
            ptrGrey[i][j] = 0;
        }
    }
    option = "RGB";
  }
  else{std::cout<<"Déjà en RGB \n";}
}

int rand_a(int a){
    return rand()%a;
}

void Image2D::saltAndPepper(int nbPoint){
    std::srand(std::time(0));
    if(option == "grey"){
        for(int i = 0; i<nbPoint; i++){

            ptrGrey[rand_a(nbX)][rand_a(nbY)]=rand_a(2)*255;
        }
    }
    else if(option == "RGB"){
        for(int i = 0; i<nbPoint; i++){
            int randX = rand_a(nbX);
            int randY = rand_a(nbY);
            int SorP = rand_a(2)*255;
            ptrR[randX][randY]=SorP;
            ptrG[randX][randY]=SorP;
            ptrB[randX][randY]=SorP;
        }
    }
}
void Image2D::convolution(int type){

  double Kernel[10][10];
  int taille;
  switch(type){
    case 0 : //Moy 3x3

                    taille = 1;
                    Kernel[0][0]=0.111;
                    Kernel[0][1]=0.111;
                    Kernel[0][2]=0.111;
                    Kernel[1][0]=0.111;
                    Kernel[1][1]=0.111;
                    Kernel[1][2]=0.111;
                    Kernel[2][0]=0.111;
                    Kernel[2][1]=0.111;
                    Kernel[2][2]=0.111;
    break;
    case 1 : //Moy 5x5
                    taille = 2;
                    Kernel[0][0]=0.02777;
                    Kernel[0][1]=0.02777;
                    Kernel[0][2]=0.02777;
                    Kernel[0][3]=0.02777;
                    Kernel[0][4]=0.02777;

                    Kernel[1][0]=0.02777;
                    Kernel[1][1]=0.02777;
                    Kernel[1][2]=0.02777;
                    Kernel[1][3]=0.02777;
                    Kernel[1][4]=0.02777;

                    Kernel[2][0]=0.02777;
                    Kernel[2][1]=0.02777;
                    Kernel[2][2]=0.02777;
                    Kernel[2][3]=0.02777;
                    Kernel[2][4]=0.02777;

                    Kernel[3][0]=0.02777;
                    Kernel[3][1]=0.02777;
                    Kernel[3][2]=0.02777;
                    Kernel[3][3]=0.02777;
                    Kernel[3][4]=0.02777;

                    Kernel[4][0]=0.02777;
                    Kernel[4][1]=0.02777;
                    Kernel[4][2]=0.02777;
                    Kernel[4][3]=0.02777;
                    Kernel[4][4]=0.02777;

    break;
    case 2 : // Gabor
                    /*Kernel[5][0]=0.02777;
                    Kernel[5][1]=0.02777;
                    Kernel[5][2]=0.02777;
                    Kernel[5][3]=0.02777;
                    Kernel[5][4]=0,02777;
                    Kernel[5][5]=0,02777;*/
    break;
    case 3 : // High_Pass :
                    taille = 1;
                    Kernel[0][0]=0;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=0;
                    Kernel[1][0]=-1;
                    Kernel[1][1]=5;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=0;
                    Kernel[2][1]=-1;
                    Kernel[2][2]=-0;
    break;
    case 4 ://Sobel Gx" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=-2;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=0;
                    Kernel[1][1]=0;
                    Kernel[1][2]=0;
                    Kernel[2][0]=1;
                    Kernel[2][1]=2;
                    Kernel[2][2]=1;
    break;
    case 5 ://Sobel Gy" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=0;
                    Kernel[0][2]=1;
                    Kernel[1][0]=-2;
                    Kernel[1][1]=0;
                    Kernel[1][2]=2;
                    Kernel[2][0]=-1;
                    Kernel[2][1]=0;
                    Kernel[2][2]=1;
    break;
    case 6 ://Passe bas" :
                    taille = 1;
                    Kernel[0][0]=1;
                    Kernel[0][1]=1;
                    Kernel[0][2]=1;
                    Kernel[1][0]=1;
                    Kernel[1][1]=4;
                    Kernel[1][2]=1;
                    Kernel[2][0]=1;
                    Kernel[2][1]=1;
                    Kernel[2][2]=1;
    break;
    case 7 ://Laplacien" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=-1;
                    Kernel[1][1]=8;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=-1;
                    Kernel[2][1]=-1;
                    Kernel[2][2]=-1;
    break;
    case 8 ://Prewitt My" :
                    taille = 1;
                    Kernel[0][0]=1;
                    Kernel[0][1]=0;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=1;
                    Kernel[1][1]=0;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=1;
                    Kernel[2][1]=0;
                    Kernel[2][2]=-1;
    break;
    case 9 ://Prewitt Mz" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=0;
                    Kernel[1][1]=0;
                    Kernel[1][2]=0;
                    Kernel[2][0]=1;
                    Kernel[2][1]=1;
                    Kernel[2][2]=1;
    break;
    case 12 ://Gauss" :
                    taille = 2;
                    Kernel[0][0]=0;
                    Kernel[0][1]=0;
                    Kernel[0][2]=-1;
                    Kernel[0][3]=0;
                    Kernel[0][4]=0;

                    Kernel[1][0]=0;
                    Kernel[1][1]=-1;
                    Kernel[1][2]=-2;
                    Kernel[1][3]=-1;
                    Kernel[1][4]=0;

                    Kernel[2][0]=-1;
                    Kernel[2][1]=-2;
                    Kernel[2][2]=16;
                    Kernel[2][3]=-2;
                    Kernel[2][4]=-1;

                    Kernel[3][0]=0;
                    Kernel[3][1]=-1;
                    Kernel[3][2]=-2;
                    Kernel[3][3]=-1;
                    Kernel[3][4]=0;

                    Kernel[4][0]=0;
                    Kernel[4][1]=0;
                    Kernel[4][2]=-1;
                    Kernel[4][3]=0;
                    Kernel[4][4]=0;
    break;
    case 13 ://Horizontal mask : H" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=2;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=-1;
                    Kernel[1][1]=2;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=-1;
                    Kernel[2][1]=2;
                    Kernel[2][2]=-1;
    break;
    case 14 ://Vertical mask : V" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=2;
                    Kernel[1][1]=2;
                    Kernel[1][2]=2;
                    Kernel[2][0]=-1;
                    Kernel[2][1]=-1;
                    Kernel[2][2]=-1;
    break;
    case 15 ://Oblique mask : O1" :
                    taille = 1;
                    Kernel[0][0]=-1;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=2;
                    Kernel[1][0]=-1;
                    Kernel[1][1]=2;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=2;
                    Kernel[2][1]=-1;
                    Kernel[2][2]=-1;
    break;
    case 16 ://Oblique mask : O2" :
                    taille = 1;
                    Kernel[0][0]=2;
                    Kernel[0][1]=-1;
                    Kernel[0][2]=-1;
                    Kernel[1][0]=-1;
                    Kernel[1][1]=2;
                    Kernel[1][2]=-1;
                    Kernel[2][0]=-1;
                    Kernel[2][1]=-1;
                    Kernel[2][2]=2;
    break;
  }
  if(option=="grey"){
    int somme;
    double** newPtr = new double* [nbX];
      for (int k=0; k<nbX ; k++){
      newPtr[k] = new double[nbY];
      }

    for(int i = 0; i<nbX;i++){
      for(int j=0;j<nbY;j++){
              somme = 0;
              if(i<taille || j<taille || i>=nbX-taille || j>=nbY-taille){
                  newPtr[i][j] = 255;
              }
              else{
                  for(int n = 0;n<taille*2+1;n++){
                      for(int m=0;m<taille*2+1;m++){
                          newPtr[i][j] += (Kernel[m][n])*(ptrGrey[i-taille+m][j-taille+n]);
                      }
                  }
              }
      }
    }

    for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
          if(newPtr[i][j]>255){
            ptrGrey[i][j]=255;
          }
          else if(newPtr[i][j]<0){
            ptrGrey[i][j]=0;
          }
          else{
            ptrGrey[i][j]=newPtr[i][j];
          }
      }
    }

}
  else{
    int somme;
    double** newPtrR = new double* [nbX];
      for (int k=0; k<nbX ; k++){
      newPtrR[k] = new double[nbY];
      }
    double** newPtrG = new double* [nbX];
      for (int k=0; k<nbX ; k++){
      newPtrG[k] = new double[nbY];
    }
    double** newPtrB = new double* [nbX];
      for (int k=0; k<nbX ; k++){
      newPtrB[k] = new double[nbY];
      }

    for(int i = 0; i<nbX;i++){
      for(int j=0;j<nbY;j++){
              somme = 0;
              if(i<taille || j<taille || i>=nbX-taille || j>=nbY-taille){
                  newPtrR[i][j] = 255;
                  newPtrG[i][j] = 255;
                  newPtrB[i][j] = 255;
              }
              else{
                  for(int n = 0;n<taille*2+1;n++){
                      for(int m=0;m<taille*2+1;m++){
                          newPtrR[i][j] += (Kernel[m][n])*(ptrR[i-taille+m][j-taille+n]);
                          newPtrG[i][j] += (Kernel[m][n])*(ptrG[i-taille+m][j-taille+n]);
                          newPtrB[i][j] += (Kernel[m][n])*(ptrB[i-taille+m][j-taille+n]);
                      }
                  }
              }
      }
    }

    for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
          ptrR[i][j]=newPtrR[i][j];
          ptrG[i][j]=newPtrG[i][j];
          ptrB[i][j]=newPtrB[i][j];
          if(newPtrR[i][j]>255){
            ptrR[i][j]=255;
          }
          if(newPtrG[i][j]>255){
            ptrG[i][j]=255;
          }
          if(newPtrB[i][j]>255){
            ptrB[i][j]=255;
          }
          if(newPtrR[i][j]<0){
            ptrR[i][j]=0;
          }
          if(newPtrG[i][j]<0){
            ptrG[i][j]=0;
          }
          if(newPtrB[i][j]<0){
            ptrB[i][j]=0;
          }
      }
    }
  }
}
/*void Image2D::printHistogrammeGrey(){
    Image2D Histo(255,100,1.0,1.0,255);
    for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
      }
    }
}*/
void Image2D::rotate(double teta){
  int** newPtrGrey = new int* [nbX];
  for (int k=0; k<nbX ; k++){
    newPtrGrey[k] = new int[nbY];
  }
  int** newPtrR = new int* [nbX];
  for (int k=0; k<nbX ; k++){
    newPtrR[k] = new int[nbY];
  }
  int** newPtrB = new int* [nbX];
  for (int k=0; k<nbX ; k++){
    newPtrB[k] = new int[nbY];
  }
  int** newPtrG = new int* [nbX];
  for (int k=0; k<nbX ; k++){
    newPtrG[k] = new int[nbY];
  }
  int centreX = nbX/2;
  int centreY = nbY/2;
  int X;
  int Y;
  double pi = 3.1415;
  teta = teta*pi/180;

  for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
            X = cos(teta)*(i - centreX)-sin(teta)*(j-centreY)+centreX;
            Y = sin(teta)*(i- centreX)+cos(teta)*(j-centreY)+centreY;
            if(X>=0 && X<nbX && Y>=0 && Y<nbY){
                newPtrGrey[i][j]= ptrGrey[X][Y];
                newPtrR[i][j]= ptrR[X][Y];
                newPtrG[i][j]= ptrG[X][Y];
                newPtrB[i][j]= ptrB[X][Y];
            }
            else{
                newPtrGrey[i][j]= 0;
                newPtrR[i][j]= 0;
                newPtrG[i][j]= 0;
                newPtrB[i][j]= 0;
            }
      }
  }
  for(int k=0;k<nbX;k++){
      for(int l=0;l<nbY;l++){
            ptrGrey[k][l]=newPtrGrey[k][l];
            ptrR[k][l]=newPtrR[k][l];
            ptrG[k][l]=newPtrG[k][l];
            ptrB[k][l]=newPtrB[k][l];
      }
  }
}

void Image2D::translate(int x, int y){
        for(int i = 0; i<nbX-x;i++){
          for(int j=0;j<nbY-y;j++){
            ptrGrey[i][j]=ptrGrey[i+x][j+y];
            ptrR[i][j]=ptrR[i+x][j+y];
            ptrG[i][j]=ptrG[i+x][j+y];
            ptrB[i][j]=ptrB[i+x][j+y];
          }
        }
        for(int k=0;k<nbX;k++){
          for(int l=nbY-y;l<nbY;l++){
            ptrGrey[k][l]=0;
            ptrR[k][l]=0;
            ptrG[k][l]=0;
            ptrB[k][l]=0;
          }
        }
        for(int m=0;m<nbY;m++){
          for(int n=nbX-x;n<nbY;n++){
            ptrGrey[n][m]=0;
            ptrR[n][m]=0;
            ptrG[n][m]=0;
            ptrB[n][m]=0;
          }
        }
}
void Image2D::Masque(const Image2D & p2){

  if(option == "grey" && p2.option == "grey"){
    for(int i = 0; i<nbX;i++){
      for(int j=0;j<nbY;j++){
        if(p2.ptrGrey[i][j] != 0){
          ptrGrey[i][j]=0;
        }
      }
    }
}

}

void Image2D::histogramme(){

  int valueR = 0;
  int valueG = 0;
  int valueB = 0;
  int valueGrey = 0;

  for(int i = 0; i<nbX;i++){
    for(int j=0;j<nbY;j++){
      valueR = ptrR[i][j];
      valueG = ptrG[i][j];
      valueB = ptrB[i][j];
      valueGrey = ptrGrey[i][j];
      //std::cout<<valueGrey<<"\n";

      histoGrey[valueGrey]++;
      //std::cout<<histoGrey[valueGrey]<<" : histo\n";
      histoR[valueR]++;
      histoB[valueB]++;
      histoG[valueG]++;
    }
  }
}

void Image2D::print_histogramme(){

  if(option == "grey"){
       int valueGrey = 0;
       Image2D A(255,100,255,4.0,4.0,255);
       // A.set_Grey_PixelValue(1,1,0);
       // A.set_Grey_PixelValue(2,1,0);
       // A.set_Grey_PixelValue(3,1,0);
       // A.set_Grey_PixelValue(10,2,0);
       // A.set_Grey_PixelValue(10,3,0);
       // A.set_Grey_PixelValue(10,4,0);
       for(int i=0;i<256;i++){
         //SvalueGrey = histoGrey[i];
         valueGrey = histoGrey[i]*100;
         valueGrey = valueGrey/16384;
         for(int j = 0; j<valueGrey;j++){
             A.set_Grey_PixelValue(i,j,0);
         }
       }
       A.createBMP("histo.bmp");
  }

}
void Image2D::filtrageAuto_histogramme(int delta){

  if(option == "grey"){
       int maxGrey = 0;
       int maxI = 0;
       for(int i=0;i<255;i++){
         if(maxGrey < histoGrey[i]){
           maxGrey = histoGrey[i];
           maxI = i;
         }
       }
       for(int j=0;j<nbX;j++){
         for(int k=0;k<nbY;k++){
              if(ptrGrey[j][k] <= maxI+delta && ptrGrey[j][k] >= maxI-delta){
              }
              else{
                ptrGrey[j][k] = 0;
              }
         }
       }

  }
  else{
    int maxR = 0;
    int maxG = 0;
    int maxB = 0;
    int maxI_R = 0;
    int maxI_G = 0;
    int maxI_B = 0;
    for(int i=0;i<255;i++){
      if(maxR < histoR[i]){
        maxR = histoR[i];
        maxI_R = i;
      }
      if(maxG < histoG[i]){
        maxG = histoG[i];
        maxI_G = i;
      }
      if(maxB < histoB[i]){
        maxB = histoB[i];
        maxI_B = i;
      }
    }
    for(int j=0;j<nbX;j++){
      for(int k=0;k<nbY;k++){
          if(maxR < maxG && maxR<maxB){
             if(ptrR[j][k] <= maxI_R+delta && ptrR[j][k] >= maxI_R-delta){
               ptrG[j][k]=0;
               ptrB[j][k]=0;
             }
             else{
               ptrR[j][k] = 0;
               ptrG[j][k]=0;
               ptrB[j][k]=0;
             }
         }
         else if(maxG < maxR && maxG<maxB){
            if(ptrG[j][k] <= maxI_G+delta && ptrG[j][k] >= maxI_G-delta){
              ptrR[j][k]=0;
              ptrB[j][k]=0;
            }
            else{
              ptrG[j][k]=0;
              ptrR[j][k]=0;
              ptrB[j][k]=0;
            }
        }
        else if(maxB < maxR && maxB<maxG){
           if(ptrB[j][k] <= maxI_B+delta && ptrB[j][k] >= maxI_B-delta){
             ptrR[j][k]=0;
             ptrG[j][k]=0;
           }
           else{
             ptrG[j][k]=0;
             ptrR[j][k]=0;
             ptrB[j][k]=0;
           }
       }
      }
    }
  }

}
void Image2D::filtrageAuto_histogramme(int delta, std::string color){

  if(option == "RGB"){
    if(color == "R"){
             int maxR = 0;
             int maxI = 0;
             for(int i=0;i<255;i++){
               if(maxR < histoR[i]){
                 maxR = histoR[i];
                 maxI = i;
               }
             }
             for(int j=0;j<nbX;j++){
               for(int k=0;k<nbY;k++){
                   if(ptrR[j][k] <= maxI+delta && ptrR[j][k] >= maxI-delta){
                     ptrG[j][k]=0;
                     ptrB[j][k]=0;
                   }
                   else{
                     ptrR[j][k] = 0;
                     ptrG[j][k]=0;
                     ptrB[j][k]=0;
                   }
               }
             }
     }
     else if(color == "G"){
              int maxG = 0;
              int maxI = 0;
              for(int i=0;i<255;i++){
                if(maxG < histoG[i]){
                  maxG = histoG[i];
                  maxI = i;
                }
              }
              for(int j=0;j<nbX;j++){
                for(int k=0;k<nbY;k++){
                    if(ptrG[j][k] <= maxI+delta && ptrG[j][k] >= maxI-delta){
                      ptrR[j][k]=0;
                      ptrB[j][k]=0;
                    }
                    else{
                      ptrG[j][k]=0;
                      ptrR[j][k]=0;
                      ptrB[j][k]=0;
                    }
                }
              }
      }
      else if(color == "B"){
               int maxB = 0;
               int maxI = 0;
               for(int i=0;i<255;i++){
                 if(maxB < histoB[i]){
                   maxB = histoB[i];
                   maxI = i;
                 }
               }
               for(int j=0;j<nbX;j++){
                 for(int k=0;k<nbY;k++){
                     if(ptrB[j][k] <= maxI+delta && ptrB[j][k] >= maxI-delta){
                       ptrR[j][k]=0;
                       ptrG[j][k]=0;
                     }
                     else{
                       ptrG[j][k]=0;
                       ptrR[j][k]=0;
                       ptrB[j][k]=0;
                     }
                 }
               }
       }

  }
}
void Image2D::CornerDetection(){
    if(option == "grey"){
  double** Ux = new double* [nbX];
  double** Uy = new double* [nbX];
  double** Uxx = new double* [nbX];
  double** Uyx = new double* [nbX];
  double** Uxy = new double* [nbX];
  double** Uyy = new double* [nbX];
  for (int k=0; k<nbX ; k++){
    Ux[k] = new double[nbY];
    Uy[k] = new double[nbY];
    Uxx[k] = new double[nbY];
    Uyx[k] = new double[nbY];
    Uxy[k] = new double[nbY];
    Uyy[k] = new double[nbY];
  }

  for(int i=0;i<nbX-1;i++){
      for(int j=0;j<nbY-1;j++){
        Ux[i][j]=ptrGrey[i][j]-ptrGrey[i+1][j];
        Uy[i][j]=ptrGrey[i][j]-ptrGrey[i][j+1];
        Uxx[i][j] = Ux[i][j]* Ux[i][j];
        Uyx[i][j] = Uy[i][j]* Ux[i][j];
        Uxy[i][j] = Ux[i][j]* Uy[i][j];
        Uyy[i][j] = Uy[i][j]* Uy[i][j];
      }
  }

  double Kernel[10][10];
  int taille = 2;
  Kernel[0][0]=0;
  Kernel[0][1]=0;
  Kernel[0][2]=-1;
  Kernel[0][3]=0;
  Kernel[0][4]=0;

  Kernel[1][0]=0;
  Kernel[1][1]=-1;
  Kernel[1][2]=-2;
  Kernel[1][3]=-1;
  Kernel[1][4]=0;

  Kernel[2][0]=-1;
  Kernel[2][1]=-2;
  Kernel[2][2]=16;
  Kernel[2][3]=-2;
  Kernel[2][4]=-1;

  Kernel[3][0]=0;
  Kernel[3][1]=-1;
  Kernel[3][2]=-2;
  Kernel[3][3]=-1;
  Kernel[3][4]=0;

  Kernel[4][0]=0;
  Kernel[4][1]=0;
  Kernel[4][2]=-1;
  Kernel[4][3]=0;
  Kernel[4][4]=0;
  /*taille = 1;
  Kernel[0][0]=-1;
  Kernel[0][1]=-1;
  Kernel[0][2]=-1;
  Kernel[1][0]=-1;
  Kernel[1][1]=8;
  Kernel[1][2]=-1;
  Kernel[2][0]=-1;
  Kernel[2][1]=-1;
  Kernel[2][2]=-1;
  Laplacien
  */

  double** J11 = new double* [nbX];
    for (int k=0; k<nbX ; k++){
    J11[k] = new double[nbY];
    }
  double** J22 = new double* [nbX];
    for (int k=0; k<nbX ; k++){
    J22[k] = new double[nbY];
  }
  double** J12 = new double* [nbX];
    for (int k=0; k<nbX ; k++){
    J12[k] = new double[nbY];
    }

  for(int i = 0; i<nbX;i++){
    for(int j=0;j<nbY;j++){
            if(i<taille || j<taille || i>=nbX-taille || j>=nbY-taille){
                J11[i][j] = 255;
                J22[i][j] = 255;
                J12[i][j] = 255;
            }
            else{
                for(int n = 0;n<taille*2+1;n++){
                    for(int m=0;m<taille*2+1;m++){
                        J11[i][j] += (Kernel[m][n])*(Uxx[i-taille+m][j-taille+n]);
                        J22[i][j] += (Kernel[m][n])*(Uyy[i-taille+m][j-taille+n]);
                        J12[i][j] += (Kernel[m][n])*(Uyx[i-taille+m][j-taille+n]);
                    }
                }
            }
    }
  }

  /*for(int i=0;i<nbX;i++){
    for(int j=0;j<nbY;j++){
        J11[i][j]=J11[i][j];
        J22[i][j]=J22[i][j];
        J12[i][j]=J12[i][j];
        if(J11[i][j]>255){
          J11[i][j]=255;
        }
        if(J22[i][j]>255){
          J22[i][j]=255;
        }
        if(J12[i][j]>255){
          J12[i][j]=255;
        }
        if(J11[i][j]<0){
          J11[i][j]=0;
        }
        if(J22[i][j]<0){
          J22[i][j]=0;
        }
        if(J12[i][j]<0){
          J12[i][j]=0;
        }
    }
  }*/

  double** H = new double* [nbX];
    for (int k=0; k<nbX ; k++){
    H[k] = new double[nbY];
    }

  for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
        H[i][j] = ((J11[i][j] * J22[i][j]) - (J12[i][j] * J12[i][j])) - 0.04 * (J11[i][j] + J22[i][j]);
        //std::cout << H[i][j]<< "\n";
        //std::cout << J11[i][j]<< "\n";
        //std::cout << J22[i][j]<< "\n";
        //std::cout << J12[i][j]<< "\n";
        if(H[i][j]>10000000){
          for(int b = -5;b<6;b++){
            if(i+b<nbX && i+b>0){
              ptrGrey[i+b][j] = 255;
            }
          }
          for(int c = -5;c<6;c++){
            if(i+c<nbY && i+c>0){
              ptrGrey[i][j+c] = 255;
            }
          }
        }
      }
  }

  }
}

/*void Image2D::EM_histogramme(int delta, std::string color){
  if(option == "grey"){
       int *pic = new int [nbPixel];
       int maxGrey = 0;
       int maxI = 0;
       for(int i=0;i<255;i++){
         if(maxGrey < histoGrey[i]){
           maxGrey = histoGrey[i];
           maxI = i;
         }
       }
       int seuil = maxGrey /2;

       for(int i=0;i<255;i++){
         if(histoGrey[i] < seuil){
           pic[i] = 0;
         }
       }
       for(int j=0;j<nbX;j++){
         for(int k=0;k<nbY;k++){
              if(ptrGrey[j][k] <= maxI+delta && ptrGrey[j][k] >= maxI-delta){
              }
              else{
                ptrGrey[j][k] = 0;
              }
         }
       }
  }
}
*/
Image2D & Image2D::operator= (const Image2D & p2){
    if(this != &p2){
      nbX = p2.nbX;
      nbY = p2.nbY;
      maxValue = p2.maxValue;
      nbPixel = p2.nbPixel;
      dx = p2.dx;
      dy = p2.dy;
      for(int i = 0; i<54;i++){
        (*this).header[i] = p2.header[i];
      }
      option = p2.option;
      alloue_partie_dynamique(nbX,nbY);
      for(int j = 0; j<nbX;j++){
        for(int k = 0;k<nbY;k++){
          ptrR[j][k] = p2.ptrR[j][k];
          ptrB[j][k] = p2.ptrB[j][k];
          ptrG[j][k] = p2.ptrG[j][k];
          ptrGrey[j][k] = p2.ptrGrey[j][k];
        }
      }

    }
}
Image2D & Image2D::operator+ (const Image2D & p2){
    if(this != &p2 && nbX == p2.nbX && nbY == p2.nbY && option == p2.option){
      alloue_partie_dynamique(nbX,nbY);
      for(int j = 0; j<nbX;j++){
        for(int k = 0;k<nbY;k++){
          ptrR[j][k] = ptrR[j][k] + p2.ptrR[j][k];
          ptrB[j][k] = ptrB[j][k] + p2.ptrB[j][k];
          ptrG[j][k] = ptrG[j][k] + p2.ptrG[j][k];
          ptrGrey[j][k] = ptrGrey[j][k] + p2.ptrGrey[j][k];
        }
      }

    }
}

//Convolution par une image
/*Image2D & Image2D::operator*(const Image2D& p2){
  if(option=="grey" && p2.get_option()=="grey" && p2.get_nbX() == p2.get_nbY()){
      int taille = p2.get_nbX();
      int** newPtr = new int* [nbX];
      for (int k=0; k<nbX ; k++){
        newPtr[k] = new int[nbY];
      }

      for(int i = 0; i<nbX;i++){
          for(int j=0;j<nbY;j++){
                  if(i<taille || j<taille || i>=nbX-taille || j>=nbY-taille){
                      newPtr[i][j] = 255;
                  }
                  else{
                      for(int n = 0;n<taille*2+1;n++){
                          for(int m=0;m<taille*2+1;m++){
                              newPtr[i][j] += (p2.ptrGrey[m][n])*(ptrGrey[i-taille+m][j-taille+n]);
                          }
                      }
                  }
          }
    }

  for(int i=0;i<nbX;i++){
      for(int j=0;j<nbY;j++){
            ptrGrey[i][j]=newPtr[i][j];
      }
  }
}
  else{
    std::cout<<"Votre image n'est pas grise, utiliser RGB_to_Grey\n";
  }
}*/

void Image2D::alloue_partie_dynamique(int dimx, int dimy){
  if ( dimx<=0 || dimy<=0 )
    {
      std::cout<<"Dimension de l'allocation anormales...\n";
      std::cout<<"dimx : " << dimx << ", dimy :" << dimy << "\n" ;
      exit ( 1 );
    }

  histoR = new int [nbPixel];
  histoG = new int [nbPixel];
  histoB = new int [nbPixel];
  histoGrey = new int [nbPixel];

  ptrG = new int* [dimx];
  ptrB = new int* [dimx];
  ptrR = new int* [dimx];
  ptrGrey = new int* [dimx];
  for (int i=0; i<dimx ; i++){
    ptrG[i] = new int[dimy];
    ptrB[i] = new int[dimy];
    ptrR[i] = new int[dimy];
    ptrGrey[i] = new int[dimy];
    if ( ptrG==NULL || ptrG[i]==NULL )
    {
      std::cout<<"Probleme allocation memoire...exiting\n";
      exit ( 1 );
    }
    if ( ptrB==NULL || ptrB[i]==NULL )
    {
      std::cout<<"Probleme allocation memoire...exiting\n";
      exit ( 1 );
    }
    if ( ptrR==NULL || ptrR[i]==NULL )
    {
      std::cout<<"Probleme allocation memoire...exiting\n";
      exit ( 1 );
    }
    if ( ptrGrey==NULL || ptrGrey[i]==NULL )
    {
      std::cout<<"Probleme allocation memoire...exiting\n";
      exit ( 1 );
    }
  }

}

void Image2D::libere_partie_dynamique(){
  if ( ptrG!=NULL )
      {
 for(int i=0; i< ((*this).nbX) ; i++){
   if ( ptrG[i]!=NULL ){
     delete [] ptrG[i];
   }
 }
 delete [] ptrG;
        ptrG=NULL;
      }
  if ( ptrB!=NULL )
      {
 for(int i=0; i< ((*this).nbX) ; i++){
   if ( ptrB[i]!=NULL ){
     delete [] ptrB[i];
   }
 }
 delete [] ptrB;
        ptrB=NULL;
      }
  if ( ptrR!=NULL )
      {
 for(int i=0; i< ((*this).nbX) ; i++){
   if ( ptrR[i]!=NULL ){
     delete [] ptrR[i];
   }
 }
 delete [] ptrR;
        ptrR=NULL;
      }
  if ( ptrGrey!=NULL )
      {
 for(int i=0; i< ((*this).nbX) ; i++){
   if ( ptrGrey[i]!=NULL ){
     delete [] ptrGrey[i];
   }
 }
 delete [] ptrGrey;
        ptrGrey=NULL;
      }
}
