// Day 2 - Exercise 3: reference solution.

#include <cstdint>
#include <iostream>
#include <vector>

#include "check.hpp"

using Image = std::vector<std::uint8_t>;

int index_of(int x, int y, int width) {
    return y * width + x;
}

std::uint8_t get_pixel(const Image& img, int width, int x, int y) {
    return img[index_of(x, y, width)];
}

void set_pixel(Image& img, int width, int x, int y, std::uint8_t value) {
    img[index_of(x, y, width)] = value;
}

Image make_gradient(int width, int height) {
    Image img(width * height, 0);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int value = x * 255 / (width - 1);  // multiply BEFORE dividing, or integer division gives 0
            set_pixel(img, width, x, y, static_cast<std::uint8_t>(value));
        }
    }
    return img;
}

void invert(Image& img) {
    for (std::uint8_t& p : img) {   // reference: modify the pixel itself
        p = static_cast<std::uint8_t>(255 - p);
    }
}

Image threshold(const Image& img, std::uint8_t t) {
    Image out(img.size());
    for (std::size_t i = 0; i < img.size(); ++i) {
        out[i] = (img[i] >= t) ? 255 : 0;   // condition ? if_true : if_false
    }
    return out;
}

std::vector<int> histogram(const Image& img) {
    std::vector<int> hist(256, 0);
    for (std::uint8_t p : img) {
        ++hist[p];   // the pixel value IS the bin index
    }
    return hist;
}

void print_image(const Image& img, int width, int height) {
    const char ramp[] = " .:-=+*#%@";
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int level = get_pixel(img, width, x, y) * 9 / 255;
            std::cout << ramp[level];
        }
        std::cout << '\n';
    }
}

int main() {
    std::cout << "A 40x4 gradient:\n";
    print_image(make_gradient(40, 4), 40, 4);
    std::cout << '\n';

    CHECK(index_of(0, 0, 10) == 0);
    CHECK(index_of(5, 3, 10) == 35);
    CHECK(index_of(1, 1, 4) == 5);

    Image small(4 * 3, 0);
    set_pixel(small, 4, 2, 1, 200);
    CHECK(small[6] == 200);
    CHECK(get_pixel(small, 4, 2, 1) == 200);
    CHECK(get_pixel(small, 4, 1, 2) == 0);

    Image g = make_gradient(5, 2);
    CHECK(g.size() == 10);
    CHECK(get_pixel(g, 5, 0, 0) == 0);
    CHECK(get_pixel(g, 5, 2, 1) == 127);
    CHECK(get_pixel(g, 5, 4, 1) == 255);

    Image b = threshold(g, 128);
    CHECK(get_pixel(b, 5, 2, 0) == 0);
    CHECK(get_pixel(b, 5, 3, 0) == 255);
    CHECK(get_pixel(g, 5, 3, 0) == 191);

    std::vector<int> h = histogram(g);
    CHECK(h.size() == 256);
    CHECK(h[0] == 2);
    CHECK(h[63] == 2);
    CHECK(h[255] == 2);
    CHECK(h[100] == 0);

    invert(g);
    CHECK(get_pixel(g, 5, 0, 0) == 255);
    CHECK(get_pixel(g, 5, 1, 1) == 192);

    return check::summary();
}
