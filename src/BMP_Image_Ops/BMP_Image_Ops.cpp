#include "BMP_Image_Ops.hpp"
#include <fstream>

// Color struct implementations
Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::~Color() {
    
}

// BMP_Image_OPS class implementations
BMP_Image_OPS::BMP_Image_OPS(int width, int height) {

}

BMP_Image_OPS::~BMP_Image_OPS() {

}

Color BMP_Image_OPS::GetColor(int x, int y) const {

}

void BMP_Image_OPS::SetColor(const Color color, int x, int y) {
 
}

void BMP_Image_OPS::Export(const char* path) const {

}