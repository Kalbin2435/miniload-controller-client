#include "utils.hpp"
#include <ctime>
#include <iomanip>
#include <sstream>

namespace main_window {

    std::string GetTimeStr() {
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
        return oss.str();
    }

    ImVec4 GetStatusColor(AgoranStatus status) {
        switch (status) {
            case AgoranStatus::StandBy: return ImVec4(0.4f, 0.7f, 1.0f, 1.0f); 
            case AgoranStatus::Working: return ImVec4(0.95f, 0.85f, 0.25f, 1.0f);
            case AgoranStatus::Error: return ImVec4(0.8f, 0.2f, 0.2f, 1.0f); 
            case AgoranStatus::Disabled: return ImVec4(0.5f, 0.5f, 0.5f, 1.0f); 
            default: return ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
        }
    }

    const char* GetStatusStr(AgoranStatus status) {
        switch (status) {
            case AgoranStatus::StandBy: return "Stand-By";
            case AgoranStatus::Working: return "Working";
            case AgoranStatus::Error: return "Error";
            case AgoranStatus::Disabled: return "Disabled";
            default: return "Unknown";
        }
    }

    const char* GetModeStr(AgoranMode mode) {
        switch (mode) {
            case AgoranMode::Automatic: return "Automatic";
            case AgoranMode::Manual: return "Manual";
            default: return "Unknown";
        }
    }

}
