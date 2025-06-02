#pragma once
#include <string>

class SystemMessage {
public:
    static void set(const std::string& msg);
    static const std::string& get();
    static void clear();

private:
    static std::string currentMessage;
};
