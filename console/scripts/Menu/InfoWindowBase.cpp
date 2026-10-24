#include "InfoWindowBase.h"

InfoWindowBase::InfoWindowBase() = default;
InfoWindowBase::~InfoWindowBase() = default;

int InfoWindowBase::GetTitleLength() const
{
    return _title.size();
}

int InfoWindowBase::GetMaxWidth() const
{
    size_t maxLength = 0;

    for (const std::wstring& item : _items)
    {
        if (item.length() > maxLength)
            maxLength = item.length();
    }

    maxLength = (_title.length() > maxLength) ? _title.length() : maxLength;

    return static_cast<int>(maxLength);
}

int InfoWindowBase::GetCountRows() const
{
    return _countRows;
}

const std::wstring& InfoWindowBase::GetTitle() const
{
    return _title;
}

const std::vector<std::wstring>& InfoWindowBase::GetItems() const
{
    return _items;
}