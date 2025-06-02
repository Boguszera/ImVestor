#include "SystemMessage.h"

std::string SystemMessage::currentMessage = "";

void SystemMessage::set(const std::string& msg) {
    currentMessage = msg;
}

const std::string& SystemMessage::get() {
    return currentMessage;
}

void SystemMessage::clear() {
    currentMessage.clear();
}
