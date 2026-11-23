#pragma once

struct TextBlock::Color final
{
public:
    static constexpr RGB BLACK{0, 0, 0};
    static constexpr RGB BLUE{0, 0, 255};
    static constexpr RGB CYAN{0, 255, 255};
    static constexpr RGB GRAY{128, 128, 128};
    static constexpr RGB GREEN{0, 255, 0};
    static constexpr RGB LIGHT_BLUE{173, 216, 230};
    static constexpr RGB LIGHT_CYAN {224, 255, 255};
    static constexpr RGB LIGHT_GREEN{144, 238, 144};
    static constexpr RGB LIGHT_MAGENTA{255, 182, 255};
    static constexpr RGB LIGHT_RED{255, 182, 193};
    static constexpr RGB LIGHT_YELLOW{255, 255, 182};
    static constexpr RGB MAGENTA{255, 0, 255};
    static constexpr RGB RED{255, 0, 0};
    static constexpr RGB WHITE{255, 255, 255};
    static constexpr RGB YELLOW{255, 255, 0};

    Color() = delete;
};