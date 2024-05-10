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

#include <algorithm>
#include <random>

#include "image.h"
#include "matrix.h"

Image twoImage(Image const& left, Image const& right){
    assert(left.nChannel() == right.nChannel());
    int w = left.width() + right.width();
    int h = std::max(left.height(), right.height());
    Image ret(w,h,left.nChannel());

    for(int i=0;i<left.width();++i)for(int j=0;j<left.height();++j)
    for(int c=0;c<left.nChannel();++c){
        ret(i,j,c) = left(i,j,c);
    }

    for(int i=0;i<right.width();++i)for(int j=0;j<right.height();++j)
    for(int c=0;c<right.nChannel();++c){
        ret(i+left.width(),j,c) = right(i,j,c);
    }

    return ret;
}

Image drawMatches(Image const& left, Image const& right, 
                  std::vector<Match> const& matches, std::vector<Match> const& inliers){
    
    Image merge = twoImage(left, right);

    // outliers
    for(int i=0;i<matches.size();++i){
        int x1 = matches[i].src->pt.x;
        int x2 = matches[i].dst->pt.x;
        int y1 = matches[i].src->pt.y;
        int y2 = matches[i].dst->pt.y;
        double k = (double)(y2-y1)/(double)(x2+left.width()-x1);
        double y = y1;
        for(int x = x1; x<=x2+left.width();++x){
            y+=k;
            merge.setPixel(x,y,0,1);
            merge.setPixel(x,y,1,0);
            merge.setPixel(x,y,2,0);
        }
    }

    // inliers
    for(int i=0;i<inliers.size();++i){
        int x1 = inliers[i].src->pt.x;
        int x2 = inliers[i].dst->pt.x;
        int y1 = inliers[i].src->pt.y;
        int y2 = inliers[i].dst->pt.y;
        double k = (double)(y2-y1)/(double)(x2+left.width()-x1);
        double y = y1;
        for(int x = x1; x<=x2+left.width();++x){
            y+=k;
            merge.setPixel(x,y,0,0);
            merge.setPixel(x,y,1,1);
            merge.setPixel(x,y,2,0);
        }
    }

    return merge;
}

Image findAndDrawRawMatches(Image const& image1, Image const& image2, 
                         double sigma, double thresh, int window, int nms){
    std::vector<Descriptor> desc1 = harrisCornerDetector(image1, sigma, thresh, window ,nms);
    std::vector<Descriptor> desc2 = harrisCornerDetector(image2, sigma, thresh, window ,nms);
    std::vector<Match> matches = matchDescriptors(desc1, desc2);

    Image cornerImage1 = markCorners(image1, desc1);
    Image cornerImage2 = markCorners(image2, desc2);
    Image ret = drawMatches(cornerImage1, cornerImage2, matches, {});

    return ret;
}


double l1Distance(Descriptor const& lhs, Descriptor const& rhs){
    assert(lhs.data.size()==rhs.data.size());

    double dist = 0;

    /**********Fill Your Code Below*********/
    //TODO L1 Distance
    // Compute Lq Distance between two descriptor.
    // L1 Distance is sum of absolute values of differences.
    // $ dist = \sum_{i}(|x_i-y_i|) $



    /**********Fill Your Code Above*********/

    return dist;
}

std::vector<int> forwardMatch(std::vector<Descriptor> const& src, std::vector<Descriptor> const& dst){
    std::vector<int> indexes(src.size(),-1);
    
    /**********Fill Your Code Below*********/
    //TODO Unidirectional Match
    // Compute matches from src to dst.
    // For each Descriptor in src, you should compute the nearest Descriptor in dst using L1 Distance, and
    // fill its index in array indexes.
    // You may want to check l1Distance above.


    /**********Fill Your Code Above*********/

    return indexes;
}

std::vector<Match> matchDescriptors(std::vector<Descriptor> const& src, std::vector<Descriptor> const& dst){
    if(src.size()==0 || dst.size()==0) return {};

    std::vector<Match> matches;

    /**********Fill Your Code Below*********/
    //TODO Brute-force match
    // Use cross match to find matches.
    // You should perform forwardMatch from src to dst, and perform forwardMatch from dst to src. If 
    // for a descriptor src[i], its match from src to dst is dst[j], and match from dst[j] is src[i], 
    // we recognize them as a match, and add them to matches.
    // You may want to check forwardMatch above and Match class in image.h.


    /**********Fill Your Code Above*********/

    return matches;
}

double l2Distance(Point const& pt1, Point const& pt2){

    double dist = 0;
    
    /**********Fill Your Code Below*********/
    //TODO L2 Distance
    // Compute L2 Distance (or Euclidean Distance) between two points.


    /**********Fill Your Code Above*********/

    return dist;
}

Point projectPoint(Matrix const& H, Point const& pt){
    Point projectedPt;

    /**********Fill Your Code Below*********/
    //TODO Project Point
    // Add a transform H to a point pt, compute projected point.
    // You may want to check Matrix class in matrix.h.


    /**********Fill Your Code Above*********/

    return projectedPt;
}

std::vector<Match> calInliers(std::vector<Match> const& matches, Matrix const& H, double thresh){
    std::vector<Match> inliers;

    /**********Fill Your Code Below*********/
    //TODO Compute Inliers
    // For each match in matches, using H to project src->pt. If L2 Distance between projected point
    // and dst->pt is less than thresh, we recognize it as a inlier.


    /**********Fill Your Code Above*********/

    return inliers;
}

void randmizeInPlace(std::vector<Match> & arr){
    
    /**********Fill Your Code Below*********/
    //TODO randmizeInPlace
    // Randmized arr.


    /**********Fill Your Code Above*********/

}

Matrix calHomography(std::vector<Match> const& matches){
    if(matches.size()<4){
        //fprintf(stderr, "4 pairs of points needed to calculate homography\n, %zu provided.\n", matches.size());
        return Matrix::identity(3,3);
    }
    Matrix H(3,3);

    /**********Fill Your Code Below*********/
    //TODO Compute Homography
    // Use matches compute corresponding homography.
    // You may want to check solveEquation in matrix.h.


    /**********Fill Your Code Above*********/

    return H;
}

Matrix ransac(std::vector<Match> &matches, double thresh, int k, int cutoff){
    int n = 4;
    if(matches.size()<n){
        //printf("4 pairs of points needed for RANSAC\n");
        return Matrix::identity(3,3);
    }

    Matrix H = Matrix::zeros(3,3);
    // Initilization
    H(0,0) = 1; H(1,1) = 1;H(2,2) = 1; H(0,2) = 256;

    /**********Fill Your Code Below*********/
    //TODO RANSAC
    // Perform ransac on matches.


    /**********Fill Your Code Above*********/

    return H;
}

