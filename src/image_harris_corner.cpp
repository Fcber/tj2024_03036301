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
#include <cassert>
#include <cmath>
#include <climits>
#include <cfloat>

#include "image.h"


Descriptor describeIndex(Image const& image, int i, int j, int width){
    Descriptor desc;
    desc.pt.x = (double)i;
    desc.pt.y = (double)j;
    desc.data.reserve(width*width*image.nChannel());
    int halfWidth = width/2;

    for(int c=0;c<image.nChannel();++c)
    for(int x=-halfWidth;x<=halfWidth;++x)for(int y=-halfWidth;y<=halfWidth;++y){
        desc.data.push_back(image.clampedPixel(i+x,j+y,c)-image.clampedPixel(i,j,c));
    }

    return desc;
}

void markSpot(Image &image, Point const& pt){
    int x = pt.x, y = pt.y;
    for(int i = -9;i<10;++i){
        image.setPixel(x+i,y,0,1.0);image.setPixel(x,y+i,0,1.0);
        image.setPixel(x+i,y,1,0.0);image.setPixel(x,y+i,1,0.0);
        image.setPixel(x+i,y,2,1.0);image.setPixel(x,y+i,2,1.0);
    }
}

Image markCorners(Image const& image, std::vector<Descriptor> const& descs){
    Image ret = image;
    for(Descriptor const& desc:descs){
        markSpot(ret, desc.pt);
    }
    return ret;
}

Image make1dGaussianFilter(double sigma){
    int width;
    Image filter;

    /**********Fill Your Code Below*********/
    //TODO Gassian Filter
    // similar to makeGaussianFilter, but you just make a
    // 1d guassian filter whose size is size*1.



    /**********Fill Your Code Above*********/

    return filter;
}

Image gaussianFilterImage(Image const &image, double sigma){
    Image ret;

    /**********Fill Your Code Below*********/
    //TODO Gassian Filter
    // Add Gaussian Blur (with Std. sigma) to a image
    // Certainly You can straightly use makeGaussianFilter, but
    // to accelerate, you can also use a 1d gaussian filter, and
    // then perform convolution on X and Y direction.
    // You may use Image::trasformInPlace to get a y direction gaussian.



    /**********Fill Your Code Above*********/

    return ret;
}

Image autocorrelationMatrix(Image const& image, double sigma){
    assert(image.nChannel()==1 || image.nChannel()==3);

    Image ret;
    if(image.nChannel() == 3) ret=image.rgb2gray();
    else ret = image;

    Image M(image.width(),image.height(),3);

    /**********Fill Your Code Below*********/
    //TODO Compute auto correlation matrix
    // You should compute auto correlation matrix of each pixel, and store them in
    // a 3-channel image. You can follow steps bellow:
    // 1. Compute X direction gradient Gx and Y direction gradient Gy. You may want to
    //    use makeSobelXFilter and makeSobelYFilter in image.h and image_filter.cpp.
    // 2. Add a gaussian blur to Gx and Gy. You may want to use gaussianFilterImage above.
    // 3. Compute auto correlation matrices and store them in a 3-channel image. For each
    //    pixel (i,j), you should store as:
    //    M(i,j,0) = Gx'(i,j)*Gx'(i,j)
    //    M(i,j,1) = Gy'(i,j)*Gy'(i,j)
    //    M(i,j,2) = Gx'(i,j)*Gy'(i,j)



    /**********Fill Your Code Above*********/

    return M;
}

Image cornernessResponse(Image const& M){
    Image R(M.width(), M.height());
    
    /**********Fill Your Code Below*********/
    //TODO Cornerness Response
    // You should compute cornerness response of each pixel.
    // We use $ R = det(M) - 0.06tr^2(M) $ to compute cornerss response.



    /**********Fill Your Code Above*********/

    return R;
}

Image nonMaxSupress(Image const& image, int radius){
    Image ret = image;

    /**********Fill Your Code Below*********/
    //TODO Non Max Supress
    // You should perform non max supress on image.
    // You can check the pixel in a (2*radius+1, 2*radius+1) window, whose
    // center is the pixel. If there is pixels greater than the pixel, supress
    // the pixel by set it to a very small value (e.g. -1e10)
    // You may want to use Image::clampedPixel to ensure pixel is in the bound.



    /**********Fill Your Code Above*********/

    return ret;
}

std::vector<Descriptor> detectCorners(Image const& image, Image const& nms, double thresh, double window){
    std::vector<Descriptor> descs;
    
    /**********Fill Your Code Below*********/
    //TODO detect corners
    // You should detect corners and describ their features.
    // You sould use non max suppress image to detect corners and describe their features.
    // For each pixel, you can check if its value is greater than thresh. If so, use describeIndex to describe
    // its feature and add it to descs. If not, do nothing.
    // You may want to check describeIndex above and std::vector::push_back or std::vector::emplace_back.



    /**********Fill Your Code Above*********/

    return descs;
}

std::vector<Descriptor> harrisCornerDetector(Image const& image, double sigma, double thresh, 
        double window, double nms){
    
    Image M = autocorrelationMatrix(image, sigma);
    Image R = cornernessResponse(M);
    Image nmsR = nonMaxSupress(R, nms);
    return detectCorners(image, nmsR, thresh, window);
}

Image detectAndDrawCorners(Image const& image, double sigma, double thresh, double window, double nms){
    std::vector<Descriptor> descs = harrisCornerDetector(image, sigma, thresh, window,nms);
    return markCorners(image, descs);
}