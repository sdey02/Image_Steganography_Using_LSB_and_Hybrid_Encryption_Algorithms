#include "BMP_Image_Ops.hpp"
#include <fstream>
#include <iostream>

// Color struct implementations
Color::Color() : r(0), g(0), b(0) {}  // Default constructor, initializes color to black

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {}  // Constructor with RGB values

Color::~Color() {
    // Destructor (empty as there's no dynamic memory allocation)
}

// BMP_Image_OPS class implementations
BMP_Image_OPS::BMP_Image_OPS(int width, int height) : m_width(width), m_height(height), m_colors(std::vector<Color>(width * height)) {}
// Constructor: initializes image dimensions and creates a vector of Colors

BMP_Image_OPS::~BMP_Image_OPS() {
    // Destructor (empty as there's no dynamic memory allocation)
}

Color BMP_Image_OPS::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];  // Returns color at specified coordinates
}

void BMP_Image_OPS::SetColor(const Color color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;  // Set red component
    m_colors[y * m_width + x].g = color.g;  // Set green component
    m_colors[y * m_width + x].b = color.b;  // Set blue component
}

void BMP_Image_OPS::Read(const char* path) {
    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);  // Open file in binary mode

    if (!f.is_open()) {
        std::cout << "File not opened";
        return;
    }

    const int file_header_size = 14;
    const int info_header_size = 40;

    unsigned char fileHeader[file_header_size];
    f.read(reinterpret_cast<char*>(fileHeader), file_header_size);  // Read file header
    unsigned char informationHeader[info_header_size];
    f.read(reinterpret_cast<char*>(informationHeader), info_header_size);  // Read info header

    int fileSize = fileHeader[2] + (fileHeader[3] << 8) + (fileHeader[4] << 16) + (fileHeader[5] << 24);  // Calculate file size

    // Extract image dimensions from the information header
    m_width = informationHeader[4] + (informationHeader[5] << 8) + (informationHeader[6] << 16) + (informationHeader[7] << 24); 
    m_height = informationHeader[8] + (informationHeader[9] << 8) + (informationHeader[10] << 16) + (informationHeader[11] << 24);

    m_colors.resize(m_width * m_height);  // Resize color vector to match image dimensions
    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);  // Calculate padding

    // Read pixel data
    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);
            // Convert and store color values (BMP stores colors in BGR order)
            m_colors[y * m_width + x].r = static_cast<float>(color[2]) / 255.0f;
            m_colors[y * m_width + x].g = static_cast<float>(color[1]) / 255.0f;
            m_colors[y * m_width + x].b = static_cast<float>(color[0]) / 255.0f;
        }
        f.ignore(paddingAmount);  // Skip padding bytes
    }

    f.close();
    std::cout << "File read" << std::endl;
}

void BMP_Image_OPS::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);  // Open file for writing in binary mode

    if (!f.is_open()) {
        std::cout << "File not opened";
        return;
    }

    unsigned char BMP_Pad[3] = {0, 0, 0};  // Padding bytes

    const int padding_amt = ((4 - (m_width * 3) % 4) % 4);  // Calculate padding

    const int file_header_size = 14;
    const int info_header_size = 40;
    const int file_size = file_header_size + info_header_size + (m_width * m_height * 3) + (padding_amt * m_height);  // Calculate total file size

    unsigned char fileHeader[file_header_size];

    // Populate file header
    fileHeader[0] = 'B';
    fileHeader[1] = 'M';
    // File size
    fileHeader[2] = file_size; 
    fileHeader[3] = file_size >> 8;
    fileHeader[4] = file_size >> 16;
    fileHeader[5] = file_size >> 24;
    // Reserved fields
    fileHeader[6] = 0;
    fileHeader[7] = 0;
    fileHeader[8] = 0;
    fileHeader[9] = 0;
    // Pixel data offset
    fileHeader[10] = file_header_size + info_header_size;
    fileHeader[11] = 0;
    fileHeader[12] = 0;
    fileHeader[13] = 0;

    unsigned char informationHeader[info_header_size];

    // Populate information header
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
    // X pixels per meter (Not specified)
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

    // Write headers to file
    f.write(reinterpret_cast<char*>(fileHeader), file_header_size); 
    f.write(reinterpret_cast<char*>(informationHeader), info_header_size);

    // Write pixel data
    for (std::size_t i = 0; i < m_height; ++i) {
        for (std::size_t j = 0; j < m_width; ++j)
        {
            // Convert float color values to unsigned char (0-255 range)
            unsigned char r = static_cast<unsigned char>(GetColor(j, i).r * 255.0f);
            unsigned char g = static_cast<unsigned char>(GetColor(j, i).g * 255.0f);
            unsigned char b = static_cast<unsigned char>(GetColor(j, i).b * 255.0f);

            unsigned char color[] = {b, g, r};  // BMP format uses BGR order

            f.write(reinterpret_cast<char*>(color), 3);  // Write color data
        } 
        f.write(reinterpret_cast<char*>(BMP_Pad), padding_amt);  // Write padding
    }
    
    f.close();

    std::cout << "File Created" << std::endl;
}