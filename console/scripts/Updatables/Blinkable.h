#pragma once

#include <chrono>
#include <optional>
#include <unordered_set>

#include "IUpdatable.h"

class Blinkable : public IUpdatable
{
private:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;
private:
    static constexpr int BLINKING_FREQUENCY_MS = 500;
    static inline bool _isShining = false; 
    static inline std::optional<TimePoint> _blinkingTimer = std::nullopt;
    static inline std::unordered_set<Blinkable*> _updatingBlinkables{};

public:
    static void PushUpdatingBlinkable(Blinkable* newBlinkable)
    {
        _updatingBlinkables.insert(newBlinkable);
    }

    static void EraseUpdatingBlinkable(Blinkable* oldBlinkable)
    {
        _updatingBlinkables.erase(oldBlinkable);
    }

    static void ResetBlinkingTimer()
    {
        _blinkingTimer = std::nullopt;
        _isShining = false;
    }

    static void UpdateAll()
    {
        if (!_blinkingTimer.has_value())
            _blinkingTimer = Clock::now();
        else if (Clock::now() - *_blinkingTimer >= std::chrono::milliseconds(BLINKING_FREQUENCY_MS))
        {
            std::erase_if(_updatingBlinkables, [](const Blinkable* el){
                return el == nullptr;
            });
            
            _isShining = !_isShining;
            if (_updatingBlinkables.size() > 0)
                for (Blinkable* el : _updatingBlinkables)
                    el->Update();

            _blinkingTimer = Clock::now();
        }
    }

    Blinkable() = default;
    Blinkable(const Blinkable& other) = default;

    ~Blinkable() noexcept override
    {
        EraseUpdatingBlinkable(this);
    }

    Blinkable& operator=(const Blinkable& other) = default;

protected:
    bool GetIsShining() const noexcept
    {
        return _isShining;
    }
};