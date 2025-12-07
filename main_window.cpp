#include "main_window.hpp"
#include "components.hpp"
#include "state.hpp"
#include "imgui.h"

namespace main_window {

    void create_main_window() {
        InitializeState();

        static bool use_work_area = true;
        static ImGuiWindowFlags flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;

        const ImGuiViewport* viewport = ImGui::GetMainViewport();
        ImGui::SetNextWindowPos(use_work_area ? viewport->WorkPos : viewport->Pos);
        ImGui::SetNextWindowSize(use_work_area ? viewport->WorkSize : viewport->Size);

        ImGui::Begin("Agoran Control Center", nullptr, flags);

        RenderTopBar();
        RenderAgoranDashboard();
        RenderLogWindow();

        ImGui::End();
    }

}
