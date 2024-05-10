/***** DO NOT CHANGE, MODIFY OR DELETE THE FOLLOWING CODE *****/

// Implementation of base operations of Image class

#include <cstdio>
#include <cassert>
#include <cstring>
#include <cmath>

#include "image.h"

Image gray2rgb(Image const& image, double r, double g, double b){
    assert(image.nChannel()==1 && "NOT Grayscale Image.");
    Image rgb(image.width(),image.height(),3);

    for(int i=0;i<rgb.width();++i)for(int j=0;j<rgb.height();++j){
        rgb(i,j,0) = r*image(i,j);
        rgb(i,j,1) = g*image(i,j);
        rgb(i,j,2) = b*image(i,j);
    }
    return rgb;
}

Image rgb2gray(Image const& image){
    assert(image.nChannel()==3 && "NOT RGB Image.");
    Image gray(image.width(),image.height(),1);

    for(int i=0;i<gray.width();++i) for(int j=0;j<gray.height();++j) gray(i,j)  = 0.299 * image(i,j,0) + 0.587 * image(i,j,1) + 0.114 * image(i,j,2);
    return gray;
}

void clampedImage(Image &image){
    for(int i=0;i<image.width();++i)for(int j=0;j<image.height();++j)for(int k=0;k<image.nChannel();++k){
        if(image(i,j,k)<0.0) image(i,j,k)=0.0;
        else if(image(i,j,k)>1.0) image(i,j,k)=1.0;
    }
}

void l1Normalize(Image &image) {
    for(int c=0;c<image.nChannel();++c){
        double s = 0;
        for(int i=0;i<image.width();++i)for(int j=0;j<image.height();++j) s+=image(i,j,c);
        for(int i=0;i<image.width();++i)for(int j=0;j<image.height();++j) image(i,j,c)/=s;
    }
}

void featureNormalize(Image &image) {
    assert(image.width()!=0 && image.height()!=0);
    double minVal = image(0,0,0);
    double maxVal = image(0,0,0);
    for(int i=0;i<image.width();++i)for(int j=0;j<image.height();++j)for(int c=0;c<image.nChannel();++c){
        if(minVal>image(i,j,c)) minVal=image(i,j,c);
        if(maxVal<image(i,j,c)) maxVal=image(i,j,c);
    }

    for(int i=0;i<image.width();++i)for(int j=0;j<image.height();++j)for(int c=0;c<image.nChannel();++c){
        image(i,j,c) = (image(i,j,c)-minVal)/(maxVal-minVal);
    }
}

void Image::transposeInPlace(){
    if(m_width == 1 || m_height == 1) {
        using namespace std;
        swap(m_width, m_height);
        return;
    }
    *this = transpose();
}

Image Image::transpose() const{
    Image ret(m_height, m_width, m_nchannel);
    for(int i=0;i<ret.width();++i)for(int j=0;j<ret.height();++j)for(int c=0;c<ret.nChannel();++c)
        ret(i,j,c)=pixelAddressHelper(j,i,c);
    return ret;
}

Image Image::abs() const{
    Image ret = *this;
    for(int i=0;i<ret.width();++i)for(int j=0;j<ret.height();++j)for(int c=0;c<ret.nChannel();++c)
        ret(i,j,c)=fabsl(pixelAddressHelper(i,j,c));
    return ret;
}

bool operator==(Image const& lhs, Image const& rhs){
    assert(lhs.width()==rhs.width());
    assert(lhs.height()==rhs.height());
    assert(lhs.nChannel()==rhs.nChannel());

    for(int i=0;i<lhs.width();++i)for(int j=0;j<lhs.height();++j)for(int k=0;k<lhs.nChannel();++k) 
        if(!(lhs(i,j,k)-rhs(i,j,k)<EPS && rhs(i,j,k) - lhs(i,j,k)<EPS)) return false;
    return true;
}

void Image::clamp() { clampedImage(*this); }
Image Image::gray2rgb(double r, double g, double b) const{return ::gray2rgb(*this,r,g,b);}
Image Image::rgb2gray() const { return ::rgb2gray(*this); }
void Image::l1Normalize() {::l1Normalize(*this);}
void Image::featureNormalize() {::featureNormalize(*this);}