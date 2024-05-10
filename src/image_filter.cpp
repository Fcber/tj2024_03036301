// You should modify this file by adding code between /* Fill Your Code Below */ 
// and /* Fill Your Code Above */, then submit it.

// Fill your student ID and name bellow, so that we can check your contribution in group
// Modified By:
// Seq      Student ID      Name            Note
// 1.       1234567         Zhang Yunlong
// 2.

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>

#include "image.h"

Image convolveImage(Image const& image, Image const& filter){
    assert(filter.nChannel() == 1 && "Filter MUST be 1-channel");
    Image ret(image.width(),image.height(),image.nChannel());

    /**********Fill Your Code Below*********/
    //TODO Image Convolution Operation
    // You should Write Code to implement image convolution operation.




    /**********Fill Your Code Above*********/

    return ret;
}

Image makeBoxFilter(int width){
    assert(width&0x1 && "Width of Filter MUST be odd.");

    Image filter(width,width);

    /**********Fill Your Code Below*********/
    //TODO Box Filter
    // You should fill filter to make it be a box filter with width*width size.
    // You can fill all values with 1.0 and then perform a L1 Normalize operation.
    // You may want to check l1Normalize function in image.h and image_base_opeartion.cpp.




    /**********Fill Your Code Above*********/

    return filter;
}

Image makeLaplacianFilter(){
    Image filter(3,3,1);
    /**********Fill Your Code Below*********/
    //TODO Lalacian Filter
    // You should fill filter to make it be a laplacian filter.
    // Laplacian filter is a 3*3 filter with formation below
    //  0   -1    0
    // -1    4   -1
    //  0   -1    0
    // Fill filter with values above.




    /**********Fill Your Code Above*********/
 
    return filter;
}

Image makePrewittXFilter(){
    Image filter(3,3,1);

    /**********Fill Your Code Below*********/
    //TODO Prewitt Filter
    // You should fill filter to make it be a Prewitt filter in X direction.
    // Prewitt filter is a 3*3 filter with formation below (X direction)
    // -1    0    1
    // -1    0    1
    // -1    0    1
    // Fill filter with values above.




    /**********Fill Your Code Above*********/
 
    return filter;
}

Image makePrewittYFilter(){
    Image filter(3,3,1);
    
    /**********Fill Your Code Below*********/
    //TODO Prewitt Filter
    // You should fill filter to make it be a Prewitt filter in Y direction.
    // Prewitt filter is a 3*3 filter with formation below (Y direction)
    // -1   -1   -1
    //  0    0    0
    //  1    1    1
    // Fill filter with values above.




    /**********Fill Your Code Above*********/
 
    return filter;
}

Image makeSobelXFilter(){
    Image filter(3,3,1);

    /**********Fill Your Code Below*********/
    //TODO Sobel Filter
    // You should fill filter to make it be a Sobel filter in X direction.
    // Prewitt filter is a 3*3 filter with formation below (X direction)
    // -1    0    1
    // -2    0    2
    // -1    0    1
    // Fill filter with values above.




    /**********Fill Your Code Above*********/
 
    return filter;
}

Image makeSobelYFilter(){
    Image filter(3,3,1);

    /**********Fill Your Code Below*********/
    //TODO Sobel Filter
    // You should fill filter to make it be a Sobel filter in Y direction.
    // Prewitt filter is a 3*3 filter with formation below (Y direction)
    // -1   -2   -1
    //  0    0    0
    //  1    2    1
    // Fill filter with values above.




    /**********Fill Your Code Above*********/
 
    return filter;
}

Image makeGaussianFilter(double sigma){
    Image filter(1,1,1);
    int width = 0;

    /**********Fill Your Code Below*********/
    //TODO Gaussian Filter
    // You should fill filter to make it be a Gaussian filter.
    // Your code may consist of 4 parts below.
    // 1. Compute the width of gaussian filter with Standard Deviation sigma.
    //    You must know 3-sigma principle, thus we use 6*sigma as the width of
    //    filter size. For width must be odd, we use the next odd integral number
    //    of 6*sigma as width.
    // 2. Make filter have size width*width. You can simply use
    //    filter = Image(width,width);
    //    to resize image.
    // 3. Use 2d Gaussian Distribution to compute values in pixels.
    //    $ G(x,y) = \frac{1}{2*\pi*\sigma^2}\exp{-\frac{x^2+y^2}{2\sigma^2}} $
    //    Notice that x and y is coordinate relative to the center of filter.
    // 4. Perform L1 Normalization on the filter. You may want to confirm image.h
    //    and image_base_operation.cpp to confirm Image::l1Normalize.
    // You may notice that the coefficient of Gaussian is not needed, for L1 Normalization
    // is performed behind.




    /**********Fill Your Code Above*********/

    return filter;
}

Image makeLOGFilter(double sigma){
    Image filter(1,1,1);
    int width;

    /**********Fill Your Code Below*********/
    //TODO LOG(Laplace of Gaussian) Filter
    // You should fill filter to make it be a LOG filter.
    // Your code may consist of 3 parts below.
    // 1. Compute the width of gaussian filter with Standard Deviation sigma.
    //    You must know 3-sigma principle, thus we use 6*sigma as the width of
    //    filter size. For width must be odd, we use the next odd integral number
    //    of 6*sigma as width.
    // 2. Make filter have size width*width. You can simply use
    //    filter = Image(width,width);
    //    to resize image.
    // 3. Use 2d Gaussian Distribution to compute values in pixels.
    //    $ G(x,y) = \frac{x^2+y^2-2\sigma^2}{2\pi\sigma^6}\exp{-\frac{x^2+y^2}{2\sigma^2}} $
    //    Notice that x and y is coordinate relative to the center of filter.




    /**********Fill Your Code Above*********/

    return filter;
}

std::pair<Image, Image> sobelFilteredImage(Image const& image){
    assert(image.nChannel()==1 || image.nChannel()==3);

    Image mag(image.width(),image.height()), theta(image.width(), image.height());

    /**********Fill Your Code Below*********/
    //TODO Use Sobel Filter to compute magnitude of gradient and direction of gradient
    // You should follow the steps below:
    // 1. Use Sobel to compute X direction and Y direction magnitude magx and magy.
    // 2. for each pixel, compute the magnitude and direction by:
    //    $ mag(i,j) = \sqrt(magx(i,j)^2+magy(i,j)^2) $
    //    $ theta(i,j) = atan2(magx(i,j), magy(i,j)) $
    // 3. Store the values and return.




    /**********Fill Your Code Above*********/

    return {mag,theta};
}