/****************************************************************\
 * @brief   Accessing, loading and some operations on images.   *
 * @file    image.h                                             *
 * @author  Zhang Yunlong                                       *
 * @date    Feb 10th 2024                                       *
 * @version 1.0                                                 *
 * @mark                                                        *
\****************************************************************/

/***** DO NOT CHANGE, MODIFY OR DELETE THE FOLLOWING CODE *****/

#ifndef IMAGE_H
#define IMAGE_H

// C standard libraries
#include <cassert>
#include <cmath>
#include <cstring>

// C++ STL
#include <algorithm>
#include <exception>
#include <string>
#include <vector>
#include <memory>

#include "matrix.h"

#ifndef M_PI
#define M_PI 3.141592635879323846
#endif
#define EPS 0.005

// Declarations
class Image;

class Image{
private:
    int          m_width;       // width of image
    int          m_height;      // height of image
    int          m_nchannel;    // number of image channels
    double *     m_data;        // data segment

public:
    // Freinds
    friend bool operator==(Image const& lhs, Image const& rhs);

    // Constructors

    /*
     * @brief Default Constructor for Image class, create an image with no data
     */
    Image(): m_width(0),m_height(0),m_nchannel(0),m_data(nullptr) {}

    /*
     * @brief Create an image with w width, h height and n channels
     * @param w The width of image
     * @param h The height of image
     * @param c The number of channels, default 1
     */
    Image(int w, int h, int c = 1):  m_width(w), m_height(h), m_nchannel(c) {
        assert( w >=0 && h >=0 && c >=0 && "Invalid image size");
        m_data = (double *)calloc(m_width * m_height * m_nchannel, sizeof(double));
    }

    // Copy Constructor

    /*
     * @brief Copy Constructor
     * @param other image to be copied
     */
    Image(Image const& other): m_width(0), m_height(0), m_nchannel(0), m_data(nullptr){
        *this = other;
    }

    // Copy Assignment

    /*
     * @brief Copy Assignment
     * @param other image to be copied
     */
    Image& operator=(Image const& other){
        auto newdata = (double *) calloc(other.m_width * other.m_height * other.m_nchannel, 
            sizeof(double));
        
        memcpy(newdata, other.m_data, sizeof(double) * other.m_width * other.m_height * other.m_nchannel);
        free(m_data);

        m_width = other.m_width;
        m_height = other.m_height;
        m_nchannel = other.m_nchannel;
        m_data = newdata;
        return *this;
    }

    // Move Constructor
    /*
     * @brief Move Constructor
     * @param other image to be moved
     */
    Image(Image && other) noexcept: m_width(other.m_width), m_height(other.m_height), 
            m_nchannel(other.m_nchannel), m_data(other.m_data) {
        other.m_width = other.m_height = other.m_nchannel = 0;
        other.m_data = nullptr;
    }

    // Move Assignment
    /*
     * @brief Move Assignment
     * @param other image to be moved
     */
    Image& operator=(Image && other) noexcept{
        if(this != &other){
            free(m_data);

            m_width = other.m_width;
            m_height = other.m_height;
            m_nchannel = other.m_nchannel;
            m_data = other.m_data;

            other.m_width = other.m_height = other.m_nchannel = 0;
            other.m_data = nullptr;
        }

        return *this;
    }

    // Destructor
    ~Image() {
        free(m_data);
    }

    // Width, Height and number of channels accessor

    /*
     * @brief width accessor
     * @return The width of image
     */
    int width() const{ return m_width; }

    /*
     * @brief height accessor
     * @return The height of image
     */
    int height() const{return m_height; }

    /*
     * @brief number of channels accessor
     * @return The number of channel of image
     */
    int nChannel() const{return m_nchannel; }

    // Get a pixel using operator()
private:
    // Pixel access helpers

    /*
     * @brief pixel address accessor
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param c The channel of pixel
     * @return The addres of pixel in array, by HWC format
     */
    int pixelAddressHelper(int x, int y, int c) const{
        return y * m_width * m_nchannel + x * m_nchannel + c;
    }

    /*
     * @brief pixel accessor for mutable image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param c The channel of pixel
     * @return Reference of pixel value in (x,y) and c channel
     */
    double& getPixelHelper(int x, int y, int c) {
        assert( x >=0 && y >=0 && x < m_width && y < m_height && c < m_nchannel && "Out of bound" );
        return m_data[pixelAddressHelper(x,y,c)];
    }
    
    /*
     * @brief pixel accessor for const image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param c The channel of pixel
     * @return Const reference of pixel value in (x,y) and c channel
     */
    double const& getPixelHelper(int x, int y, int c) const {
        assert( x >=0 && y >=0 && x < m_width && y < m_height && c < m_nchannel && "Out of bound" );
        return m_data[pixelAddressHelper(x,y,c)];
    }

    /*
     * @brief pixel accessor for mutable grayscale image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return Reference of pixel value in (x,y) of grayscale image
     */
    double& getPixelHelper(int x, int y) {
        assert( x >=0 && y >=0 && x < m_width && y < m_height && "Out of bound" );
        assert( m_nchannel == 1 && "Invalid usage");
        return m_data[pixelAddressHelper(x,y,0)];
    }

    /*
     * @brief pixel accessor for const grayscale image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return Reference of pixel value in (x,y) of grayscale image
     */
    double const& getPixelHelper(int x, int y) const {
        assert( x >=0 && y >=0 && x < m_width && y < m_height && "Out of bound" );
        assert( m_nchannel == 1 && "Invalid usage");
        return m_data[pixelAddressHelper(x,y,0)];
    }

public:
    // Pixel accessor

    /*
     * @brief pixel accessor for mutable image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param c The channel of pixel
     * @return Reference of pixel value in (x,y) and c channel
     */
    double &operator()(int x, int y, int c) { return getPixelHelper(x,y,c); }

    /*
     * @brief pixel accessor for const image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param c The channel of pixel
     * @return Const reference of pixel value in (x,y) and c channel
     */
    double const& operator()(int x, int y, int c) const{ return getPixelHelper(x,y,c); }

    /*
     * @brief pixel accessor for mutable grayscale image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return Reference of pixel value in (x,y) of grayscale image
     */
    double &operator()(int x, int y) { return getPixelHelper(x,y); }

    /*
     * @brief pixel accessor for const grayscale image
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return Reference of pixel value in (x,y) of grayscale image
     */
    double const& operator()(int x, int y) const { return getPixelHelper(x,y); }

    /*
     * @brief clamped pixel value in coordinate (x,y) and c channel
     * @details This function return clamped pixel. When coordinate (x,y) is out of\n
     *         bound, operator() will cause an error. But this function will return the\n
     *         value of the pixel nearest to the coordinate in the bound.
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return a double value of clamped pixel value in (x,y) and c channel
     */
    double clampedPixel(int x, int y, int c) const {
        assert( c >= 0 && c < m_nchannel && "Invalid channel");
        if(x<0) x=0;
        if(y<0) y=0;
        if(x>=m_width) x=m_width-1;
        if(y>=m_height) y=m_height-1;
        return getPixelHelper(x,y,c);
    }

    /*
     * @brief clamped pixel value in coordinate (x,y) if grayscale image
     * @details This function return clamped pixel. When coordinate (x,y) is out of\n
     *         bound, operator() will cause an error. But this function will return the\n
     *         value of the pixel nearest to the coordinate in the bound.
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @return a double value of clamped pixel value in (x,y)
     */
    double clampedPixel(int x, int y) const {
        assert(m_nchannel == 1 && "Invalid channel");
        if(x<0) x=0;
        if(y<0) y=0;
        if(x>=m_width) x=m_width-1;
        if(y>=m_height) y=m_height-1;
        return getPixelHelper(x,y);
    }

    // Pixel modifier
    /*
     * @brief set pixel in (x,y) and c channel to newValue
     * @details This function set pixel (x,y) and c channel to newValue withount any\n
     *         error. If (x,y,c) is out of bound, this function do nothing.
     * @param x The x coordinate of pixel
     * @param y The y coordinate of pixel
     * @param newValue new pixel value to be set
     */
    void setPixel(int x, int y, int c, double newValue) {
        if(x < 0 || x >= m_width || y < 0 || y >= m_height) return;
        getPixelHelper(x,y,c) = newValue;
    }

    // Utilities

    /*
     * @brief number of bytes image data occupies
     * @return the number of bytes
     */
    int size() const { return m_width * m_height * m_nchannel; }
    void clear() { memset(m_data, 0, sizeof(double) * m_nchannel * m_width * m_height); }

    // Resamplers
    /*
     * @brief nerest resample for non-integral coordinate (x,y) and c channel
     * @param x Non-integral x coordinate
     * @param y Non-integral y coordinate
     * @param c The c channel
     * @return nearest resapled pixel value of (x,y,c)
     */
    double pixelNearest(double x, double y, int c) const;

    /*
     * @brief bilinear resample for non-integral coordinate (x,y) and c channel
     * @param x Non-integral x coordinate
     * @param y Non-integral y coordinate
     * @param c The c channel
     * @return bilinear resapled pixel value of (x,y,c)
     */
    double pixelBilinear(double x, double y, int c) const;

    /*
     * @brief biculic resample for non-integral coordinate (x,y) and c channel
     * @param x Non-integral x coordinate
     * @param y Non-integral y coordinate
     * @param c The c channel
     * @return bicubic resapled pixel value of (x,y,c)
     */
    double pixelBicubic(double x, double y, int c) const;


    // Image I/O
public:
    /*
     * @brief load image to this object
     * @param filname absolute path or relative path to current working directory of image.
     */
    void load(std::string const& filename);

    /*
     * @breif save image to given file
     * @param filename absolute path or relative path to current working directory of image.
     */
    void save(std::string const& filename) const;

public:
    // Normalize

    /*
     * @brief Perform L1 Normalize on this image.
     * @details For every channel, we compute the sum of all pixels. Then\n
     *         divide all pixel values by the sum.
     */
    void l1Normalize();

    /*
     * @brief Perform Feature Normalize on this image.
     * @details We compute the max and min value of all pixels. Then \n
     *         perform a linear trasform $$T(v)=(v-min)/(max-min)$$ on\n
     *         all pixels to ensure all pixels are in [0,1].
     */
    void featureNormalize();

    // ColorSpace 

    /*
     * @breif Convert a grayscale image to rgb image by given fractions.
     * @param r R fraction
     * @param g G fraction
     * @param b B fraction
     * @return RGB image.
     */
    Image gray2rgb(double r, double g, double b) const;

    /*
     * @brief Convert a RGB image to grayscale image.
     * @return Grayscale image.
     */
    Image rgb2gray() const;

    void transposeInPlace();
    Image transpose() const;
    Image abs() const;

    /*
     * @brief clamp pixels out of bound to [0,1]
     */
    void clamp();
};

// Point Class for Feature Extaction
struct Point {
    double x,y;
    Point()=default;
    Point(double x, double y):x(x),y(y) {}
};

// Descriptor Class for Feature Match
struct Descriptor{
    Point pt;
    std::vector<double> data;

    Descriptor()=default;
    Descriptor(Point const& p):pt(p){}
};

// Match Class for Feature Match
struct Match{
    Descriptor const* src=nullptr;
    Descriptor const* dst=nullptr;
    double distance=0;

    Match()=default;
    Match(Descriptor const* a, Descriptor const* b, double distance=0):src(a),dst(b),distance(distance) {}
};

bool operator==(Image const& lhs, Image const& rhs);

// Image I/O functions

/*
 * @brief load image
 * @param filename absolute path or relative path to cwd.
 * @return image corrresponding to file name.
 */
Image loadImage(std::string const& filename) ;

/*
 * @brief save image
 * @param filename absolute path or relative path to cwd.
 * @param image 
 */
void saveImage(std::string const& filename, Image const& image);


// Resize image

/*
 * @brief resize using nearest resample
 * @param image image to be resized
 * @param width width to be resized to
 * @param height height to be resized to
 * @return resized image
 */
Image nearestResize(Image const& image, int width, int height);

/*
 * @brief resize using nearest resample
 * @param image image to be resized
 * @param width width to be resized to
 * @param height height to be resized to
 * @return resized image
 */
Image bilinearResize(Image const& image, int width, int height);

/*
 * @brief resize using nearest resample
 * @param image image to be resized
 * @param width width to be resized to
 * @param height height to be resized to
 * @return resized image
 */
Image bicubicResize(Image const& image, int width, int height);

/*
 * @brief convert grayscale image to RGB image
 * @param image grayscale image
 * @param r R fraction
 * @param g G fraction
 * @param b B fraction
 * @return RGB image
 */
Image gray2rgb(Image const& image, double r, double g, double b);

/*
 * @brief convert RGB image to grayscale image
 * @param image RGB image
 * @return grayscale image
 */
Image rgb2gray(Image const& image);

/*
 * @brief Clamp image
 * @details make pixel values greater than 1 be 1, and pixel values less than 0 be 0.
 * @param image image to be clamped
 */
void clampedImage(Image &image);

/*
 * @brief Perform L1 Normalization on an image
 * @param image image to be normalized
 */
void l1Normalize(Image &image);

/*
 * @brief Perform Feature Normalization on an image
 * @param image image to be normalized
 */
void featureNormalize(Image &image);

// Filter
/*
 * @brief Perform convolution on image by filter
 * @param image image to be convolved
 * @param filter filter kernel
 */
Image convolveImage(Image const& image, Image const& filter);

/*
 * @brief Make a box filter with width*width size and return it.
 * @param width filter width
 * @return box filter
 */
Image makeBoxFilter(int width);

/*
 * @brief Make a 3*3 laplacian filter and return it.
 * @return 3*3 Laplacian filter
 */
Image makeLaplacianFilter();

/*
 * @brief Make a 3*3 prewitt filter of X direction and return it.
 * @return 3*3 prewitt filter of X direction
 */
Image makePrewittXFilter();

/*
 * @brief Make a 3*3 prewitt filter of Y direction and return it.
 * @return 3*3 prewitt filter of Y direction
 */
Image makePrewittYFilter();

/*
 * @brief Make a 3*3 Sobel filter of X direction and return it.
 * @return 3*3 Sobel filter of X direction
 */
Image makeSobelXFilter();

/*
 * @brief Make a 3*3 Sobel filter of Y direction and return it.
 * @return 3*3 Sobel filter of Y direction
 */
Image makeSobelYFilter();

/*
 * @brief Make a gaussian filter with Std. sigma.
 * @param sigma Standard Deviation
 * @return Gaussian filter
 */
Image makeGaussianFilter(double sigma);

/*
 * @brief Make a laplacian of gaussian filter with Std. sigma.
 * @param sigma Standard Deviation
 * @return LOG filter
 */
Image makeLOGFilter(double sigma);

/*
 * @brief Compute Magnitude and Direction of Gradient.
 * @param image image to be computed
 * @return a pair of image, first is magnitude, second is direction.
 */
std::pair<Image, Image> sobelFilteredImage(Image const& image);

// Harris Corner Detector

/*
 * @brief Compute autocorrelation matrix of image with standard deviation sigma.
 * @param image image to be detected
 * @param sigma Standard Deviation
 * @return 3-channel image storing autocorrelation matrixs
 */
Image autocorrelationMatrix(Image const& image, double sigma);

/*
 * @brief Compute cornerness response of autocorrelation matrix M
 * @param M autocorrelation matrix image
 * @return cornerness response image
 */
Image cornernessResponse(Image const& M);

/*
 * @brief Perform Non Max Supress on image
 * @param R cornerness response image
 * @param radius Readius of window (Chebyshev distance)
 */
Image nonMaxSupress(Image const& R, int radius);

/*
 * @brief Perform corner detection on image with non max supress image and describe their features
 * @param image image to be detected
 * @param nms non max supress image
 * @param thresh detection threshold
 * @param window window size for describing feature
 * @return descriptors of detected corners
 */
std::vector<Descriptor> detectCorners(Image const& image, Image const& nms, double thresh, double window);

/*
 * @brief Perform harris corner detect on an image
 * @param image image to be detected
 * @param sigma standard deviation
 * @param thresh detection threshold
 * @param window window width for describing feature
 * @param nms radius in non max supress
 */
std::vector<Descriptor> harrisCornerDetector(Image const& image, double sigma, double thresh, 
        double window, double nms);

/*
 * @brief Detect and draw corners of image
 * @param image image to be detected
 * @param sigma standard deviation for Gaussian used in computation of autocorrelation matrix
 * @param thresh threshold while detecting corners using non max supress image
 * @param window window size for feature description
 * @param nms radius in non max supress
 * @return image with corners marked
 */
Image detectAndDrawCorners(Image const& image, double sigma, double thresh, double window, double nms);

/*
 * @brief mark corners in image
 * @param image image corners marked in
 * @param desc corners' descriptors
 * @return image with corners marked
 */
Image markCorners(Image const&image, std::vector<Descriptor> const& desc);

/*
 * @breif mark a point in image
 * @param image image point marked in
 * @param pt point to be marked
 * @return an image with pt marked in given image 
 */
void markSpot(Image &image, Point const& pt);

// Feature Matchers

/*
 * @brief Combine two images in one image, one is on the left side, and another is on the right side.
 * @param left image on the left side
 * @param right image on the right side
 * @return combined image
 */
Image twoImage(Image const& left, Image const& right);

/*
 * @brief Draw matches of left image and right image
 * @param left left image
 * @param right right image
 * @param matches matches of left and right image
 * @param inliers inlier matches
 * @return match image
 */
Image drawMatches(Image const& left, Image const& right, std::vector<Match> const& matches, std::vector<Match> const& inliers);

/*
 * @brief find matches of image1 and image2, then draw the matches in a combined image
 * @param image1 image to be detected and matched
 * @param image2 image to be detected and matched
 * @param sigma standard deviation for gaussian filter in autocorrelation compting.
 * @param thresh threshold while detecting corners using non max supress image
 * @param window window width while descring features of a point
 * @param nms radius in non max supress
 * @return Match image
 */
Image findAndDrawRawMatches(Image const& image1, Image const& image2, double sigma, double thresh, int window, int nms);

/*
 * @breif Compute L1 Distance between two Descriptor
 * @param lhs Descriptor for a point in left image
 * @param rhs Descriptor for a point in right image
 * @return L1 distance between lhs and rhs
 */
double l1Distance(Descriptor const& lhs, Descriptor const& rhs);

/*
 * @brief Unidirectional Match from src to dst
 * @param src Descriptors we match from
 * @param dst Descroptors we match to
 * @return an integer array recording the match index from src to dst
 */
std::vector<int> forwardMatch(std::vector<Descriptor> const& src, std::vector<Descriptor> const& dst);

/*
 * @brief Match Two Descriptor set
 * @param src Descriptors of left image
 * @param dst Descriptors of right image
 * @return Match result
 */
std::vector<Match> matchDescriptors(std::vector<Descriptor> const& src, std::vector<Descriptor> const& dst);

/*
 * @brief compute L2 Distance between two points
 * @param pt1 Start point
 * @param pt2 End Point
 * @return L2 Distance between pt1 and pt2
 */
double l2Distance(Point const& pt1, Point const& pt2);

/*
 * @brief Project Homography to Point
 * @param H Homography Matrix
 * @param pt Point to be projected
 * @return Projected Point
 */
Point projectPoint(Matrix const& H, Point const& pt);

/*
 * @brief Compute Inliers of matches using Homography
 * @param Matches matches where inliers are selected from
 * @param H homography
 * @param thresh Threshold of distance between projected point and match point
 * @return Inliers
 */
std::vector<Match> calInliers(std::vector<Match> const& matches, Matrix const& H, double thresh);

/*
 * @brief Reandmize a match array
 * @param Arr match array
 * @return Randomly arranged arr
 */
void randmizeInPlace(std::vector<Match> & arr);

/*
 * @brief Compute Homography using matches
 * @param Matches matches for homography computation
 * @return Homography
 */
Matrix calHomography(std::vector<Match> const& matches);

/*
 * @breif Perform RANSAC procedure
 * @param matches Matches RANSAC process
 * @param thresh Threshold for inliers computation
 * @param k Iterations
 * @param cutoff Exit iteration if number of inlieirs is greater than cutoff
 * @return Homography
 */
Matrix ransac(std::vector<Match> &matches, double thresh, int k, int cutoff);

#endif