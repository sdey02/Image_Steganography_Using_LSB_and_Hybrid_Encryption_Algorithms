#include <iostream>
#include <string_view>
#include <vector>
#include <bitset>

struct Color{
    float r, g, b;

    Color();
    Color(float r, float g, float b);
    ~Color();
};

class BMP_Image_OPS {
    private:
        int m_width();
        int m_height();
        std::vector<Color> m_colors;

    public:
        BMP_Image_OPS(int width, int height);
        ~BMP_Image_OPS();

        Color GetColor(int x, int y) const;
        void SetColor(const Color, int x, int y);
        
        void Export(const char* path) const;
};