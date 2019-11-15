# IMAGE_Library_Application
Gtkmm software using IMAGE C++ library

To compilate :
code &g++ -g Fenetre.cpp main.cpp Image2D.cpp  -o Image_App `pkg-config gtkmm-3.0 --cflags --libs`
To launch :
<code> &./Image_App </code>

Content :

* Create and read .bmp images.
* Rotation
* Translation
* Thresholding
* Salt and pepper noise
* Mask
* Convolution :
  - Low Pass
  - High Pass
  - Gaussien
  - Median
  - Sobel
  - Prewitt
  - ...
* Histogramme
* ..
