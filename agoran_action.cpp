#include "imgui.h"
#include <cstring>
#include <map>
#include "agoran_action.hpp"
#include "utils.hpp"
#include "enums.hpp"

namespace main_window {
    static bool open_agoran_action_popup = false;
    static std::map<ActionType, const char*> action_types = {
        {ActionType::Goto,reverse_utf8_c_str("תזוזה"),},
        {ActionType::Push,reverse_utf8_c_str("הבאת מגש")},
        {ActionType::Take,reverse_utf8_c_str("החזרת מגש")}
    };
    static ActionType selected_action_type = ActionType::Goto;

    int x_val = 1;
    int y_val = 1;
    static side side = side::center;


    void render_goto() {
        int min=1, max=20;
        bool x_invalid = (x_val < min || x_val > max);
        bool two = (y_val < min || y_val > max);
        render_validated_int("my_x", x_val, x_invalid, min, max);
        render_validated_int("my_y", y_val, two, min, max);
    }
    void render_push() {
        int min=1, max=20;
        bool x_invalid = (x_val < min || x_val > max);
        bool two = (y_val < min || y_val > max);
        render_validated_int("my_x", x_val, x_invalid, min, max);
        render_validated_int("my_y", y_val, two, min, max);
    }
    void render_take() {
        int min=1, max=20;
        bool x_invalid = (x_val < min || x_val > max);
        bool two = (y_val < min || y_val > max);
        render_validated_int("my_x", x_val, x_invalid, min, max);
        render_validated_int("my_y", y_val, two, min, max);
    }
    void RenderCustomPopUp() {
        if ( open_agoran_action_popup ) { 
            ImGui::OpenPopup("AgoranActionPopUp");
            open_agoran_action_popup = false;
        }
        if (ImGui::BeginPopupModal("AgoranActionPopUp", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            if (ImGui::BeginCombo("##Action Type", action_types[selected_action_type])) {
                for (const auto& [key, value]: action_types) {
                    if(ImGui::Selectable(action_types[key], key == selected_action_type)) {
                        selected_action_type = key;
                    }
                }
                ImGui::EndCombo();
            }

            switch (selected_action_type) {
                case ActionType::Goto:
                    render_goto();
                    break;
                case ActionType::Push:
                    render_push();
                    break;
                case ActionType::Take:
                    render_take();
                    break;
            }

            if (ImGui::Button("Cancel", ImVec2(120, 0))) {
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }
    }

    void open_custom_popup() {
        open_agoran_action_popup = true;
    }

    void render_validated_int(const char* text,int &value, bool invalid, int min, int max) {
        ImGui::Text("%s", text);
        ImGui::SameLine();
        if (invalid) {
            ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(1.0f, 0.4f, 0.4f, 1.0f));
            ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f)); 
        }
        ImGui::PushID(text);
        ImGui::InputInt("##input", &value, 0, 0);
        ImGui::PopID();
        if (invalid) {
            ImGui::PopStyleColor(2);
            if (ImGui::IsItemHovered()) {
                ImGui::SetTooltip("Value must be between %d and %d", min, max);
            }
        }
    }
}
