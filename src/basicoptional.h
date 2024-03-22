#pragma once

/// Simplified version of std::optional, to return set or unset values
/// Primarily used for values that does not have any destructor logic and where
/// copying is cheap
template <typename T>
class BasicOptional {
    T value = {};
    bool isSet = false;

public:
    constexpr BasicOptional() = default;
    constexpr BasicOptional(const T &value)
        : value{value}
        , isSet{true} {}

    void reset() {
        isSet = false;
    }
};
