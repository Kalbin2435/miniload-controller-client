#pragma once

#include "types.hpp"
#include "imgui.h"
#include <string>

namespace main_window {

    std::string GetTimeStr();
    ImVec4 GetStatusColor(AgoranStatus status);
    const char* GetStatusStr(AgoranStatus status);
    const char* GetModeStr(AgoranMode mode);
    std::string reverse_utf8(std::string s);

}
