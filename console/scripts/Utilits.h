#pragma once

#include <format>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <windows.h>
#undef RGB

#include "TextBlock.h"
#include "Vector2.h"

namespace Utilits
{
    template <typename T>
    inline auto GetSharedPtr(std::weak_ptr<T> weakPtr)
    {
        auto sharedPtr = weakPtr.lock();
        if (sharedPtr == nullptr)
            throw std::runtime_error(std::format("Weak pointer has been empty. The type of this weak pointer: {}", typeid(typename decltype(weakPtr)::element_type).name()));
        
        return sharedPtr;
    }

    enum class DeltaMove
    {
        UP = VK_UP,
        DOWN = VK_DOWN,
        LEFT = VK_LEFT,
        RIGHT = VK_RIGHT
    };

    template <class T, class PositionOf = std::identity>
    requires std::invocable<PositionOf&, const T&> && std::convertible_to<std::invoke_result_t<PositionOf&, const T&>, Vector2>
    int FindNextPositionIndex(const std::vector<T>& candidates, 
        Vector2 current, DeltaMove direction, std::size_t chessboardSize, PositionOf positionOf = PositionOf{}) 
    {
        bool isVertical = direction == DeltaMove::UP || direction == DeltaMove::DOWN;
        bool isTowardLower = direction == DeltaMove::UP || direction == DeltaMove::LEFT;

        Vector2 wrapAnchor = current;
        int oppositeEdge = isTowardLower ? chessboardSize : -1;
        if (isVertical)
            wrapAnchor.row = oppositeEdge;
        else
            wrapAnchor.col = oppositeEdge;

        int bestIndex = -1;
        std::tuple<bool, int, int, int> bestKey{};

        std::size_t candidatesCount = candidates.size();
        for (std::size_t i = 0; i < candidatesCount; ++i)
        {
            Vector2 position = std::invoke(positionOf, candidates[i]);

            if (!isVertical && position.row != current.row)
                continue;

            int axisDelta = isVertical ? position.row - current.row : position.col - current.col;

            if (axisDelta == 0)
                continue;

            bool wraps = (axisDelta < 0) != isTowardLower;
            Vector2 anchor = wraps ? wrapAnchor : current;
            int deltaRow = position.row - anchor.row;
            int deltaCol = position.col - anchor.col;

            auto key = std::tuple{
                wraps, deltaRow * deltaRow + deltaCol * deltaCol, position.row, position.col
            };

            if (bestIndex < 0 || key < bestKey)
            {
                bestIndex = i;
                bestKey = key;
            }
        }

        return bestIndex;
    }
}