#include "../image.h"
#define TEST do {\
    fprintf(stderr, "[%30s] running in %20s, line %5d\n", __FUNCTION__, __FILE__, __LINE__);\
}while(0)

void testLoadAndSave() {
    TEST;
    Image image;
    image = loadImage("data/house.jpg");
    saveImage("output/house.png",image);
}

void testResampler(){
    TEST;
    Image image = loadImage("data/house.jpg");
    Image nnImage = nearestResize(image,image.width()*4,image.height()*4);
    saveImage("output/house_nn_4x4.jpg",nnImage);
    Image blImage = bilinearResize(image,image.width()*4,image.height()*4);
    saveImage("output/house_bl_4x4.jpg",blImage);
    Image bcImage = bicubicResize(image,image.width()*4,image.height()*4);
    saveImage("output/house_bc_4x4.jpg",bcImage);
}

void testFilters(){
    TEST;

    Image image = loadImage("data/house.jpg");
    Image boxFilterImage = convolveImage(image, makeBoxFilter(3));
    saveImage("output/house_box_filter.jpg", boxFilterImage);
    
    Image lapLaceFilterImage = convolveImage(image, makeLaplacianFilter());
    lapLaceFilterImage.featureNormalize();
    saveImage("output/house_laplace_filter.jpg", lapLaceFilterImage);
    
    Image prewittFilterImage = convolveImage(image, makePrewittXFilter());
    prewittFilterImage.featureNormalize();
    saveImage("output/house_prewitt_x_filter.jpg", prewittFilterImage);
    
    auto sobelPair = sobelFilteredImage(image);
    sobelPair.first.featureNormalize();sobelPair.second.featureNormalize();
    saveImage("output/house_sobel.jpg",sobelPair.first);
    saveImage("output/house_sobel_angle.jpg",sobelPair.second);

    Image gaussianImage = convolveImage(image, makeGaussianFilter(2));
    saveImage("output/house_gaussian.jpg", gaussianImage);

    Image logImage = convolveImage(image, makeLOGFilter(2));
    logImage.featureNormalize();
    saveImage("output/house_log.jpg", logImage);
}

void testHarris(){
    TEST;
    Image image = loadImage("data/1.jpg");
    Image corners = detectAndDrawCorners(image,2,0.6,5,3);
    saveImage("output/corners.jpg",corners);

    Image M = autocorrelationMatrix(image, 2);
    Image R = cornernessResponse(M);
    Image nms = nonMaxSupress(R, 3);

    M.featureNormalize();
    R.featureNormalize();
    nms.featureNormalize();

    saveImage("output/autoCorrelation.jpg", M);
    saveImage("output/response.jpg", R);
    saveImage("output/nms.jpg", nms);
}

void testMatch(){
    TEST;
    Image image1 = loadImage("data/1.jpg");
    Image image2 = loadImage("data/2.jpg");
    Image rawMatch = findAndDrawRawMatches(image1, image2, 2, 0.4, 7, 3);
    saveImage("output/rawmatch.jpg", rawMatch);
    
    std::vector<Descriptor> descs1 = harrisCornerDetector(image1, 2, 0.4, 5, 3);
    std::vector<Descriptor> descs2 = harrisCornerDetector(image2, 2, 0.4, 5, 3);
    //for(int i=0;i<descs1.size();++i) printf("(%lf, %lf)\n", descs1[i].pt.x, descs1[i].pt.y);
    //for(int i=0;i<descs2.size();++i) printf("(%lf, %lf)\n", descs2[i].pt.x, descs2[i].pt.y);
    std::vector<Match> matches = matchDescriptors(descs1, descs2);

    //for(int i=0;i<matches.size();++i) printf("(%lf, %lf) (%lf, %lf)\n", matches[i].src->pt.x, matches[i].src->pt.y, matches[i].dst->pt.x, matches[i].dst->pt.y);
    std::vector<Match> inliers = calInliers(matches, ransac(matches, 5, 10000, 50), 5);

    Image cornerImage1 = markCorners(image1, descs1);
    Image cornerImage2 = markCorners(image2, descs2);
    Image ransacMatch = drawMatches(cornerImage1, cornerImage2, matches, inliers);

    saveImage("output/ransacmatch.jpg", ransacMatch);
}

void myTest(){

}

void runTests() {
    myTest();
    testLoadAndSave();
    testResampler();
    testFilters();
    testHarris();
    testMatch();
}

int main() {
    runTests();
    return 0;
}