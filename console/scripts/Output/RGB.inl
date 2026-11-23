#pragma once

struct TextBlock::RGB final
{
    friend struct Color;
public:
    int r;
    int g;
    int b;
private:
    constexpr RGB(int r, int g, int b) noexcept : r{r}, g{g}, b{b}
    {
    }
    RGB(const RGB& other) noexcept = default;
    RGB(RGB&& other) noexcept = default;
    RGB& operator=(const RGB& other) noexcept = default;
    RGB& operator=(RGB&& other) noexcept = default;
};