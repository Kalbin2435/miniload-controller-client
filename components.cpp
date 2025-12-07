#include "components.hpp"
#include "state.hpp"
#include "utils.hpp"
#include "imgui.h"
#include <string>

namespace main_window {

    // Shared state for the modal
    static int s_selected_agoran_idx = 0;
    static int s_selected_mode_idx = 0;
    static bool s_open_popup = false;

    void RenderTopBar() {
        // Handle popup open request from other functions
        if (s_open_popup) {
            ImGui::OpenPopup("ChangeModePopup");
            s_open_popup = false;
        }
        
        if (ImGui::BeginPopupModal("ChangeModePopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            
            if (s_selected_agoran_idx >= (int)g_state.agorans.size()) s_selected_agoran_idx = 0;

            if (!g_state.agorans.empty()) {
                 if (ImGui::BeginCombo("Agoran", ("Agoran " + std::to_string(g_state.agorans[s_selected_agoran_idx].id)).c_str())) {
                    for (int i = 0; i < (int)g_state.agorans.size(); i++) {
                        bool is_selected = (s_selected_agoran_idx == i);
                        if (ImGui::Selectable(("Agoran " + std::to_string(g_state.agorans[i].id)).c_str(), is_selected))
                            s_selected_agoran_idx = i;
                        if (is_selected)
                            ImGui::SetItemDefaultFocus();
                    }
                    ImGui::EndCombo();
                }
            }

            const char* modes[] = { "Automatic", "Manual" };
            if (ImGui::BeginCombo("Mode", modes[s_selected_mode_idx])) {
                for (int i = 0; i < 2; i++) {
                    bool is_selected = (s_selected_mode_idx == i);
                    if (ImGui::Selectable(modes[i], is_selected))
                        s_selected_mode_idx = i;
                    if (is_selected)
                        ImGui::SetItemDefaultFocus();
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button("Apply", ImVec2(120, 0))) {
                if (s_selected_agoran_idx >= 0 && s_selected_agoran_idx < (int)g_state.agorans.size()) {
                    g_state.agorans[s_selected_agoran_idx].mode = (AgoranMode)s_selected_mode_idx;
                    AddLog("User", "Agoran " + std::to_string(g_state.agorans[s_selected_agoran_idx].id), 
                           std::string("Changed mode to ") + modes[s_selected_mode_idx]);
                }
                ImGui::CloseCurrentPopup();
            }
            ImGui::SameLine();
            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
        
        // Removed the button, but kept the function for the modal logic execution
        // We can add distinct top bar content here if needed later
        // ImGui::Separator(); // Keeping separator if we want visual break
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
            for (int i = 0; i < (int)g_state.agorans.size(); ++i) {
                auto& agoran = g_state.agorans[i];
                ImGui::TableNextColumn();
                
                ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
                ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
                
                std::string child_id = "AgoranCard_" + std::to_string(agoran.id);
                if (ImGui::BeginChild(child_id.c_str(), ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY, ImGuiWindowFlags_NoScrollbar)) {
                    
                    // --- Top Section: Robot Info & Controls ---
                    // Header
                    ImGui::Text("Agoran %d", agoran.id);
                    ImGui::SameLine();
                    
                    // Clickable Mode
                    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 1.0f), "[%s]", GetModeStr(agoran.mode));
                    if (ImGui::IsItemHovered()) {
                        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
                    }
                    if (ImGui::IsItemClicked()) {
                        s_selected_agoran_idx = i;
                        s_selected_mode_idx = (int)agoran.mode;
                        s_open_popup = true;
                    }

                    // Status
                    ImGui::Text("Status: ");
                    ImGui::SameLine();
                    ImGui::TextColored(GetStatusColor(agoran.status), "%s", GetStatusStr(agoran.status));

                    // Tray On Robot
                    ImGui::Text("Tray On: ");
                    ImGui::SameLine();
                    if (agoran.trayOn.has_value()) {
                        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.2f, 1.0f), "Holding: %d", agoran.trayOn.value());
                    } else {
                        ImGui::TextDisabled("Empty Handed");
                    }

                    // Manual Command Button
                    ImGui::Spacing();
                    bool manual_active = (agoran.mode == AgoranMode::Manual);
                    if (!manual_active) ImGui::BeginDisabled();
                    if (ImGui::Button("Send Manual Command", ImVec2(-FLT_MIN, 0))) {
                        AddLog("User", "Agoran " + std::to_string(agoran.id), "Manual command sent");
                        agoran.lastResult = "Manual command sent...";
                    }
                    if (!manual_active) ImGui::EndDisabled();

                    ImGui::Separator();

                    // --- Bottom Section: Workstations (Left & Right) ---
                    if (ImGui::BeginTable("WorkstationLayout", 2, ImGuiTableFlags_SizingStretchSame)) {
                        
                        // Left Workstation
                        ImGui::TableNextColumn();
                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
                        if (ImGui::BeginChild("LeftStation", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY, ImGuiWindowFlags_NoScrollbar)) {
                             // Centered Title
                            const char* title = "Left";
                            float windowWidth = ImGui::GetWindowSize().x;
                            float textWidth = ImGui::CalcTextSize(title).x;
                            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                            ImGui::Text("%s", title);
                            
                            ImGui::Separator();
                            
                            if (agoran.leftTray.has_value()) {
                                std::string trayStr = std::to_string(agoran.leftTray.value());
                                textWidth = ImGui::CalcTextSize(trayStr.c_str()).x;
                                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                                ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", trayStr.c_str());
                            } else {
                                const char* emptyStr = "-";
                                textWidth = ImGui::CalcTextSize(emptyStr).x;
                                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                                ImGui::Text("%s", emptyStr);
                            }
                        }
                        ImGui::EndChild();
                        ImGui::PopStyleColor();

                        // Right Workstation
                        ImGui::TableNextColumn();
                        ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.1f, 0.1f, 0.1f, 0.5f));
                        if (ImGui::BeginChild("RightStation", ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY, ImGuiWindowFlags_NoScrollbar)) {
                            // Centered Title
                            const char* title = "Right";
                            float windowWidth = ImGui::GetWindowSize().x;
                            float textWidth = ImGui::CalcTextSize(title).x;
                            ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                            ImGui::Text("%s", title);

                            ImGui::Separator();
                            
                            if (agoran.rightTray.has_value()) {
                                std::string trayStr = std::to_string(agoran.rightTray.value());
                                textWidth = ImGui::CalcTextSize(trayStr.c_str()).x;
                                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                                ImGui::TextColored(ImVec4(0.4f, 1.0f, 0.4f, 1.0f), "%s", trayStr.c_str());
                            } else {
                                const char* emptyStr = "-";
                                textWidth = ImGui::CalcTextSize(emptyStr).x;
                                ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
                                ImGui::Text("%s", emptyStr);
                            }
                        }
                        ImGui::EndChild();
                        ImGui::PopStyleColor();

                        ImGui::EndTable();
                    }

                    ImGui::Separator();
                    ImGui::TextDisabled("Last Result:");
                    ImGui::TextWrapped("%s", agoran.lastResult.c_str());

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
