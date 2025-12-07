#include "components.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "imgui.h"
#include <string>

namespace main_window {

    void RenderTopBar() {
        if (ImGui::Button("Change Agoran Mode")) {
            ImGui::OpenPopup("ChangeModePopup");
        }
        
        if (ImGui::BeginPopupModal("ChangeModePopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            static int selected_agoran_idx = 0;
            static int selected_mode_idx = 0;
            
            if (selected_agoran_idx >= (int)g_state.agorans.size()) selected_agoran_idx = 0;

            if (!g_state.agorans.empty()) {
                 if (ImGui::BeginCombo("Agoran", ("Agoran " + std::to_string(g_state.agorans[selected_agoran_idx].id)).c_str())) {
                    for (int i = 0; i < (int)g_state.agorans.size(); i++) {
                        bool is_selected = (selected_agoran_idx == i);
                        if (ImGui::Selectable(("Agoran " + std::to_string(g_state.agorans[i].id)).c_str(), is_selected))
                            selected_agoran_idx = i;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            const char* modes[] = { "Automatic", "Manual" };
            if (ImGui::BeginCombo("Mode", modes[selected_mode_idx])) {
                for (int i = 0; i < 2; i++) {
                    bool is_selected = (selected_mode_idx == i);
                    if (ImGui::Selectable(modes[i], is_selected))
                        selected_mode_idx = i;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button("Apply", ImVec2(120, 0))) {
                if (selected_agoran_idx >= 0 && selected_agoran_idx < (int)g_state.agorans.size()) {
                    g_state.agorans[selected_agoran_idx].mode = (AgoranMode)selected_mode_idx;
                    AddLog("User", "Agoran " + std::to_string(g_state.agorans[selected_agoran_idx].id), 
                           std::string("Changed mode to ") + modes[selected_mode_idx]);
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        
        ImGui::Separator();
    }

    void RenderAgoranDashboard() {
        float window_width = ImGui::GetContentRegionAvail().x;
        float card_width = 250.0f;
        int num_items = (int)g_state.agorans.size();
        
        int columns = (int)(window_width / card_width);
        if (columns < 1) columns = 1;
        
        if (num_items <= columns) {
            columns = num_items;
        }

        if (columns > 0 && ImGui::BeginTable("AgoranGrid", columns, ImGuiTableFlags_SizingStretchSame)) {
            for (auto& agoran : g_state.agorans) {
                ImGui::TableNextColumn();
                
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
                
                std::string child_id = "AgoranCard_" + std::to_string(agoran.id);
                if (ImGui::BeginChild(child_id.c_str(), ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY, ImGuiWindowFlags_NoScrollbar)) {
                    
                    // Header
                    ImGui::Text("Agoran %d", agoran.id);
                    ImGui::SameLine();
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "[%s]", GetModeStr(agoran.mode));
                    ImGui::Separator();

                    // Status
                    ImGui::Text("Status: ");
                    ImGui::SameLine();
                    ImGui::TextColored(GetStatusColor(agoran.status), "%s", GetStatusStr(agoran.status));

                    // Tray
                    ImGui::Text("Tray On: ");
                    ImGui::SameLine();
                    if (agoran.trayOn.has_value()) {
                        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.2f, 1.0f), "%d", agoran.trayOn.value());
                    } else {
                        ImGui::TextDisabled("None");
                    }

                    // Last Result
                    ImGui::Text("Last Result:");
                    ImGui::TextWrapped("%s", agoran.lastResult.c_str());

                    // Manual Command Button
                    ImGui::Spacing();
                    bool manual_active = (agoran.mode == AgoranMode::Manual);
                    if (!manual_active) ImGui::BeginDisabled();
                    if (ImGui::Button("Send Manual Command", ImVec2(-FLT_MIN, 0))) {
                        AddLog("User", "Agoran " + std::to_string(agoran.id), "Manual command sent");
                        agoran.lastResult = "Manual command executed wow naotna otnawot nawto nawto nawt oawn toawtn awo";
                    }
                    if (!manual_active) ImGui::EndDisabled();

                }
                ImGui::EndChild();
                ImGui::PopStyleColor();
                ImGui::PopStyleVar();
            }
            ImGui::EndTable();
        }

        ImGui::Separator();
    }

    void RenderLogWindow() {
        ImGui::Text("Communication Log");
        ImGui::BeginChild("LogRegion", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
        
        for (const auto& log : g_state.logs) {
            ImGui::TextColored(ImVec4(0.5f, 0.5f, 0.5f, 1.0f), "[%s]", log.timestamp.c_str());
            ImGui::SameLine();
            ImGui::TextColored(ImVec4(0.4f, 0.8f, 1.0f, 1.0f), "%s -> %s:", log.from.c_str(), log.to.c_str());
            ImGui::SameLine();
            ImGui::TextUnformatted(log.message.c_str());
        }

        // Auto-scroll to bottom
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
    }

}
