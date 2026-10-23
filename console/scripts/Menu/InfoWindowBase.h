#pragma once

#include <vector>
#include <string>

class InfoWindowBase
{
protected:
    int _maxWidth;
    size_t _countRows;
    std::vector<std::wstring> _items;
    std::wstring _title;

public:
    InfoWindowBase();
    virtual ~InfoWindowBase() = 0;

    int GetMaxWidth() const;
    int GetCountRows() const;
    int GetTitleLength() const;

    const std::wstring& GetTitle() const;
    const std::vector<std::wstring>& GetItems() const;
};