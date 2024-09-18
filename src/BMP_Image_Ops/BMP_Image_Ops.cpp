#include "BMP_Image_Ops.hpp"
#include <fstream>
#include <iostream>

// Color struct implementations
Color::Color() : r(0), g(0), b(0) {}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}

Color::~Color() {
    
}

// BMP_Image_OPS class implementations
BMP_Image_OPS::BMP_Image_OPS(int width, int height) : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height)) {}

BMP_Image_OPS::~BMP_Image_OPS() {

}

Color BMP_Image_OPS::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void BMP_Image_OPS::SetColor(const Color color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void BMP_Image_OPS::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File not opened";
        return;
    } 

    unsigned char BMP_Pad[3] = {0, 0, 0};

    const int padding_amt = ((4 - (m_width * 3) % 4) % 4);

    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + (m_width * m_height * 3) + (padding_amt * m_height);

    unsigned char fileHeader[file_header_size];

    // File type
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

   // File size
    fileHeader[2] = file_size; 
    fileHeader[3] = file_size >> 8;
    fileHeader[4] = file_size >> 16;
    fileHeader[5] = file_size >> 24;

    // Reserved 1 (Not used)
    fileHeader[6] = 0;
    fileHeader[7] = 0;

    // Reserved 2 (Not used)
    fileHeader[8] = 0;
    fileHeader[9] = 0;

    // Pixel data offset
    fileHeader[10] = file_header_size + info_header_size;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

   unsigned char informationHeader[info_header_size];

    // Header size
    informationHeader[0] = info_header_size;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    // Image width
    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    // Image height
    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;

    // Planes
    informationHeader[12] = 1;
    informationHeader[13] = 0;

    // Bits per pixel (RGB)
    informationHeader[14] = 24;
    informationHeader[15] = 0;

    // Compression (No compression)
    informationHeader[16] = 0;
    informationHeader[17] = 0;
    informationHeader[18] = 0;
    informationHeader[19] = 0;

    // Image size (No compression)
    informationHeader[20] = 0;
    informationHeader[21] = 0;
    informationHeader[22] = 0;
    informationHeader[23] = 0;

    // X pixels per meter (Not specified).
    informationHeader[24] = 0;
    informationHeader[25] = 0;
    informationHeader[26] = 0;
    informationHeader[27] = 0;

    // Y pixels per meter (Not specified)
    informationHeader[28] = 0;
    informationHeader[29] = 0;
    informationHeader[30] = 0;
    informationHeader[31] = 0;

    // Total colors (Color palette not used)
    informationHeader[32] = 0;
    informationHeader[33] = 0;
    informationHeader[34] = 0;
    informationHeader[35] = 0;

    // Important colors (Generally ignored)
    informationHeader[36] = 0;
    informationHeader[37] = 0;
    informationHeader[38] = 0;
    informationHeader[39] = 0;

    f.write(reinterpret_cast<char*>(fileHeader), file_header_size); 
    f.write(reinterpret_cast<char*>(informationHeader), info_header_size);

    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j)
        {
            unsigned char r = static_cast<unsigned char>(GetColor(j, i).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(j, i).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(j, i).b * 255.0f);

            unsigned char color[] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        } 
        f.write(reinterpret_cast<char*>(BMP_Pad), padding_amt);
    }
    
    f.close();

    std::cout << "File Created" << std::endl;
}