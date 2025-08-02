#pragma once

#include <cstdio>
#include <functional>
#include <string>

namespace ATC {
class LogFormatter {
private:
    std::function<std::string()> builder_;

public:
    template<typename... Args>
    LogFormatter(const char* text, Args&&... args) :
        builder_([=]() mutable {
            size_t size = std::snprintf(
                nullptr, 0, text, std::forward<Args>(args)...
            );

            std::string output(size + 1, '\0');
            std::snprintf(
                &output[0], size, text, std::forward<Args>(args)...
            );
            return output;
        }) {}

    std::string operator()() {
        return builder_();
    }
};
}