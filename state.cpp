#include "state.hpp"
#include "utils.hpp"
#include <string>

namespace main_window {

    AppState g_state;

    void AddLog(const std::string& from, const std::string& to, const std::string& message) {
        g_state.logs.push_back({ GetTimeStr(), from, to, message });
    }

    void InitializeState() {
        if (g_state.initialized) return;
        g_state.agorans.clear();
        for (int i = 0; i < 5; ++i) {
            Agoran a;
            a.id = i + 1;
            a.status = AgoranStatus::Idle;
            a.mode = AgoranMode::Automatic;
            a.trayOn = std::nullopt;
            a.lastResult = "System initialized";
            g_state.agorans.push_back(a);
        }

        g_state.agorans[1].status = AgoranStatus::Working;
        g_state.agorans[1].trayOn = 101;
        g_state.agorans[2].status = AgoranStatus::Error;
        g_state.agorans[2].lastResult = "Connection timeout";
        
        if (g_state.agorans.size() > 4) {
            g_state.agorans[4].mode = AgoranMode::Manual;
            g_state.agorans[4].status = AgoranStatus::Disabled;
        }

        AddLog("System", "All", "Initialization complete.");
        g_state.initialized = true;
    }

}
