#include "UIHelpers.hpp"
#include <string>

void UIHelpers::CenterCursorBasedOnText(std::string text)
{
    float textWidth = ImGui::CalcTextSize(text.c_str()).x;
    float windowWidth = ImGui::GetContentRegionAvail().x;
    float indentation = (windowWidth - textWidth) * 0.5f;
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + indentation);
}

void UIHelpers::ColoredText(std::string text, ImVec4 color)
{
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::TextWrapped(text.c_str());
    ImGui::PopStyleColor();
}





