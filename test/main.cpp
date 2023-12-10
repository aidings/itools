#include "itools.hpp"

#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image.h"
#include "stb/stb_image_write.h"

void test_npy(){
    vector<float> data({1.0, 2.0, 3.0});
    itools::Matrix<float> mat({2,3}, data.data());

    mat.save("matrix.npy");
    mat.show();

    itools::Matrix<float> mat2({1, 6});

    mat2.load("matrix.npy");
    mat2.show();
}

void test_image(){
    string path = "/home/ding/iwork/github/opencv-4.x/samples/winrt/OcvImageProcessing/OcvImageProcessing/Assets/Lena.png";
    int w, h, n;
    unsigned char *img_buf = stbi_load(path.c_str(), &w, &h, &n, 0);

    std::cout << "width:" << w << " height:" << h << " channel: " << n << std::endl; 

    stbi_write_jpg("a.jpg", w, h, n, img_buf, 0);

    vector<unsigned long int> shape({(unsigned long int)(w), (unsigned long int)(h), 3});

    itools::Matrix<unsigned char> image(shape, img_buf);

    image.save("image.npy");
    // image.show();
}

int main(){
    //test_npy(); 
    test_image();

    return 0;
}