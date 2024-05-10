// You should modify this file by adding code between /* Fill Your Code Below */ 
// and /* Fill Your Code Above */, then submit it.

// Fill your student ID and name bellow, so that we can check your contribution in group
// Modified By:
// Seq      Student ID      Name            Note
// 1.       1234567         Zhang Yunlong
// 2.


#include <cmath>
#include "image.h"

double Image::pixelNearest(double x, double y, int c) const {
    double pixelValue = 0;

    /**********Fill Your Code Below*********/
    //TODO Nearest Resample
    // You should Write Code to implement nearest resample, compute 
    // pixel value of non-intergral coordinate (x,y) and c channel.
    // You may want to use Image::clampedPixel to ensure your resampling
    // pixels are in bound.




    /**********Fill Your Code Above*********/
    
    return pixelValue;
}

double Image::pixelBilinear(double x, double y, int c) const{
    double pixelValue = 0;

    /**********Fill Your Code Below*********/
    //TODO Bilinear Resample
    // You should Write Code to implement bilinear resample, compute 
    // pixel value of non-intergral coordinate (x,y) and c channel.
    // You may want to use Image::clampedPixel to ensure your resampling
    // pixels are in bound.


    

    /**********Fill Your Code Above*********/

    return pixelValue;
}

double Image::pixelBicubic(double x, double y, int c) const{
    double pixelValue = 0;
    /**********Fill Your Code Below*********/
    //TODO Bicubic Resample
    // You should Write Code to implement bicubic resample, compute 
    // pixel value of non-intergral coordinate (x,y) and c channel.
    // You may want to use Image::clampedPixel to ensure your resampling
    // pixels are in bound.
    // Notice that we cannot ensure pixel valued computed is in [0,1]. You
    // should let values greater than 1 be 1, and let values less than 0 be
    // 0.


    

    /**********Fill Your Code Above*********/
    return pixelValue;
}

Image nearestResize(Image const& image, int width, int height){
    Image ret(width,height,image.nChannel());
    
    /**********Fill Your Code Below*********/
    //TODO Nearest Resize
    // Iterate all pixels in resized image, compute their corresponding coordinates
    // in original image, and then use function pixelNearest above to get pixel value,
    // then assign it to the pixel in resized image.
    // Notice that you should consider coordinate transform between resizde image and
    // original image.


    

    /**********Fill Your Code Above*********/

    return ret;
}

Image bilinearResize(Image const& image, int width, int height){
    Image ret(width,height,image.nChannel());

    /**********Fill Your Code Below*********/
    //TODO Bilinear Resize
    // Iterate all pixels in resized image, compute their corresponding coordinates
    // in original image, and then use function pixelBilinear above to get pixel value,
    // then assign it to the pixel in resized image.
    // Notice that you should consider coordinate transform between resizde image and
    // original image.


    

    /**********Fill Your Code Above*********/

    return ret;
}

Image bicubicResize(Image const& image, int width, int height){
    Image ret(width,height,image.nChannel());
    
    /**********Fill Your Code Below*********/
    //TODO Bicubic Resize
    // Iterate all pixels in resized image, compute their corresponding coordinates
    // in original image, and then use function pixelBicubic above to get pixel value,
    // then assign it to the pixel in resized image.
    // Notice that you should consider coordinate transform between resizde image and
    // original image.


    

    /**********Fill Your Code Above*********/

    return ret;
}