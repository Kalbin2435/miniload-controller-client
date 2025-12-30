#pragma once

#include "types.hpp"
#include <vector>
#include <string>

namespace main_window {

    struct AppState {
        std::vector<Agoran> agorans;
        std::vector<LogEntry> logs;
        bool initialized = false;
    };

    extern AppState g_state;

    void InitializeState();
    void AddLog(const std::string& from, const std::string& to, const std::string& message);

}
