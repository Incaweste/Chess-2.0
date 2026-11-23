#pragma once

class TextBlock::Line
{
private:
    using ColorTarget = TextBlock::ColorTarget; 
    struct ColorHandler final
    {
    private:
        const RGB* _activeColor = nullptr;
        const RGB* _defaultColor = nullptr;
        std::wstring_view _setColorCommand;
        std::wstring _resetColorCommand;

    public:
        constexpr ColorHandler(bool isTextHandler, const RGB* defaultColor, bool isColorAlreadySetted) noexcept : 
            _setColorCommand{isTextHandler ? L"[38;2;" : L"[48;2;"}, 
            _resetColorCommand{isTextHandler ? L"[39m" : L"[49m"},
            _defaultColor{defaultColor},
            _activeColor{isColorAlreadySetted ? defaultColor : nullptr}
        {
        }

        constexpr ColorHandler(bool isTextHandler) noexcept : ColorHandler{isTextHandler, {}, false}
        {
        }

        constexpr const RGB* GetActiveColor() const noexcept
        {
            return _activeColor;
        }

        constexpr void SetDefaultColor(const RGB* defaultColor) noexcept
        {
            _defaultColor = defaultColor;
        }

        void SetActiveColorToDefault(Line& handlingLine);
        
        bool TrySetActiveColor(Line& handlingLine, const RGB* activeColor);

        void ResetActiveColor(Line& handlingLine);
    };

private:
    std::wstring _line{};
    ColorHandler _textColorHandler;
    ColorHandler _bgColorHandler;

public:
    constexpr Line(
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted, 
        std::size_t expectedLineLength = 0,
        std::wstring line = {}
    ) :
        _textColorHandler{true, defaultTextColor, areColorsAlreadySetted}, 
        _bgColorHandler{false, defaultBGColor, areColorsAlreadySetted},
        _line{std::move(line)}
    {
        _line.reserve(expectedLineLength);
    }

    constexpr Line(
        const RGB* defaultTextColor, 
        const RGB* defaultBGColor, 
        bool areColorsAlreadySetted, 
        std::wstring line
    ) : Line{defaultTextColor, defaultBGColor, areColorsAlreadySetted, 0, line}
    {
    }

    constexpr explicit Line(std::size_t expectedLineLength) noexcept : Line{{}, {}, false, expectedLineLength}
    {
    }

    constexpr explicit Line(std::wstring line) noexcept : Line{{}, {}, false, line}
    {
    }

    constexpr Line() : Line{0}
    {
    }

    constexpr Line& operator=(std::wstring_view other)
    {
        _line = other;
        return *this;
    }

    constexpr Line& operator+=(const wchar_t& other)
    {
        _line += other;
        return *this;
    }

    constexpr Line& operator+=(std::wstring_view other)
    {
        _line += other;
        return *this;
    }

    constexpr Line& operator+=(const Line& other)
    {
        _line += other._line;
        return *this;
    }

    friend constexpr Line operator+(Line first, const Line& second)
    {   
        first += second;
        return first;
    }

    constexpr operator std::wstring_view() const noexcept
    {
        return std::wstring_view{_line};
    }

    constexpr operator std::wstring_view() noexcept
    {
        return std::wstring_view{_line};
    }

    constexpr void AddChars(std::size_t count, wchar_t character = L' ')
    {
        _line.append(count, character);
    }

    constexpr std::size_t GetWidth() const noexcept
    {
        return _line.size();
    }

    constexpr const RGB* GetActiveColor(ColorTarget target) const noexcept
    {
        return GetColorHandler(target).GetActiveColor();
    }

    constexpr void SetDefaultColor(ColorTarget target, const RGB* defaultColor) noexcept
    {
        GetColorHandler(target).SetDefaultColor(defaultColor);
    }

    void SetActiveColorToDefault(ColorTarget target);
    
    bool TrySetActiveColor(ColorTarget target, const RGB* activeColor);

    void ResetActiveColor(ColorTarget target);
private:
    constexpr const ColorHandler& GetColorHandler(ColorTarget target) const noexcept
    {
        return target == ColorTarget::TEXT ? _textColorHandler : _bgColorHandler;
    }

    constexpr ColorHandler& GetColorHandler(ColorTarget target) noexcept
    {
        return target == ColorTarget::TEXT ? _textColorHandler : _bgColorHandler;
    }
};