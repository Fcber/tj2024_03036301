/***** DO NOT CHANGE, MODIFY OR DELETE THE FOLLOWING CODE *****/

// Implementation of loading and saving functio of Image class

// C Standard Libraries
#include <cstdlib>
#include <cstdio>

// C++ STL
#include <iostream>
#include <string>

// Class Declaration File
#include "image.h"

// stb libraries used to read and write images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

void Image::load(std::string const& filename) {
    int width, height, nchannel;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nchannel, 0);

    if(!data) {
        std::cerr << "Failure: load image " << filename << "  Reason:"<<stbi_failure_reason()<<std::endl;
        exit(0);
    }

    int ch = nchannel;
    if(nchannel == 4) ch = 3;
    Image image(width, height, ch);

    for(int i = 0; i < width; ++ i) for(int j = 0; j < height; ++j) for(int c = 0; c < ch; ++c){
        int dstId = j * width * ch + i * ch + c;
        int srcId = j * width * nchannel + i * nchannel + c;
        image.m_data[dstId] = (double)data[srcId]/255.0;
    }
    stbi_image_free(data);
    *this = std::move(image);
}

void Image::save(std::string const& filename) const {
    enum IMAGE_TYPE { png, bmp, jpg};
    IMAGE_TYPE imageType = png;
    
    std::string suffix = filename.substr(filename.find_last_of(".")+1);
    std::string writeName = filename;
    if(suffix == "png") imageType = png;
    else if(suffix == "jpeg" || suffix == "jpg") imageType = jpg;
    else if(suffix == "bmp") imageType = bmp;
    else writeName += ".png";

    unsigned char *buf = (unsigned char *)calloc(m_width * m_height * m_nchannel, sizeof(unsigned char));
    for(int i = 0; i < m_width * m_height * m_nchannel; ++i) {
        buf[i] = (unsigned char) roundl(255.0 * m_data[i]);
    }

    int success = 0;
    switch (imageType)
    {
    case bmp:
        success = stbi_write_bmp(writeName.c_str(), m_width, m_height, m_nchannel, buf);
        break;
    case jpg:
        success = stbi_write_jpg(writeName.c_str(), m_width, m_height, m_nchannel, buf, 100);
        break;
    default:
        success = stbi_write_png(writeName.c_str(), m_width, m_height, m_nchannel, buf, m_width*m_nchannel);
        break;
    }

    free(buf);
    if(!success) {
        std::cerr << "Failure: save image " << filename << std::endl;
    }
}

// Image I/O functions
Image loadImage(std::string const& filename) {
    Image image;
    image.load(filename);
    return image;
}

void saveImage(std::string const& filename, Image const& image) {
    image.save(filename);
}
