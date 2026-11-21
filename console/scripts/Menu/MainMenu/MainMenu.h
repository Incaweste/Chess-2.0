#pragma once

#include "InfoWindowBase.h"
#include "IMenuInput.h"

class MainMenu : public InfoWindowBase, public IMenuInput
{
private:
    struct MenuItem final
    {
        std::wstring text;
        MenuAction action;
    };

    std::wstring _title;
    std::vector<MenuItem> _items;

    int _selectedIndex = 0;

    constexpr inline static int _LEFT_RIGHT_INDENTS = 4;
    constexpr inline static int _UP_BOTTOM_INDENTS = 2;

public:
    MainMenu();

    void Update() override;

    int GetMaxWidth() const;

    void PrintContent() const override;
    std::optional<MenuAction> HandleMenuSelect() override;
    std::optional<MenuAction> SelectItem() const;

private:
    struct Keys final
    {
        constexpr inline static int ENTER = 13;
        constexpr inline static int ARROW_UP = 72;
        constexpr inline static int ARROW_DOWN = 80;
        constexpr inline static int SPECIAL_1 = 0;
        constexpr inline static int SPECIAL_2 = 224;

        virtual ~Keys() = 0;
    };
};