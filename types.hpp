#pragma once

#include <string>
#include <optional>

namespace main_window {

    enum class AgoranStatus {
        StandBy,
        Working,
        Error,
        Disabled
    };

    enum class AgoranMode {
        Automatic,
        Manual
    };

    struct Agoran {
        int id;
        AgoranStatus status;
        AgoranMode mode;
        std::optional<int> trayOn;
        std::optional<int> leftTray;
        std::optional<int> rightTray;
        std::string lastResult;
    };

    struct LogEntry {
        std::string timestamp;
        std::string from;
        std::string to;
        std::string message;
    };

}
