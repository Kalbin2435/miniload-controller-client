#pragma once
#include "enums.hpp"
#include <vector>

namespace main_window {
    class AgoransState {
        public:
            static AgoransState& getInstance();
        private:
            struct Agoran {
                int agoran_id;
                AgoranStatus status;
                AgoranMode mode;
                int loaded_tray;
                int left_workstation_loaded_tray;
                int right_workstation_loaded_tray;
            };
            std::vector<Agoran> agorans_list_;
            void FetchAgoransData();
            static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
            AgoransState();
            ~AgoransState();
    };
}
