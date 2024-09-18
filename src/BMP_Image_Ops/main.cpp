#include "BMP_Image_Ops.hpp"
#include <iostream>

int main() {
    const int width = 640;
    const int height = 480;

    BMP_Image_OPS image(width, height);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float r = static_cast<float>(x) / static_cast<float>(width);
            float g = 1.0f - (static_cast<float>(x) / static_cast<float>(width));
            float b = static_cast<float>(y) / static_cast<float>(height);
            image.SetColor(Color(r, g, b), x, y);
        }
    }

    image.Export("image.bmp");

    return 0;
}