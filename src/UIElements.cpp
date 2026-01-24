#include "UIElements.hpp"
#include "imgui.h"
#include <format>
#include <string>
#include "UIHelpers.hpp"
#include "ColorScheme.hpp"

void UIElements::CraneWorkstation(std::string side, int TrayNumber)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ColorScheme::element_background_dark);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
    ImGui::BeginChild(side.c_str(), ImVec2(0, 0), ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    UIHelpers::CenterCursorBasedOnText(side.c_str());
    ImGui::TextWrapped(side.c_str(), ColorScheme::green);
    ImGui::Separator();
    UIHelpers::CenterCursorBasedOnText(std::to_string(TrayNumber).c_str());
    ImGui::TextWrapped(std::to_string(TrayNumber).c_str(), ColorScheme::green);

    ImGui::EndChild();
}

void UIElements::CraneCard(std::string childName, ImVec2 size)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ColorScheme::element_background);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
    ImGui::BeginChild(childName.c_str(), size, ImGuiChildFlags_Borders | ImGuiWindowFlags_NoScrollbar);
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();

    UIHelpers::CenterCursorBasedOnText(childName);
    UIHelpers::ColoredText(childName, ColorScheme::blue);
    ImGui::Separator();

    ImGui::TextWrapped("Status:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("YOOO", ColorScheme::blue);

    ImGui::TextWrapped("SapTask:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("1000000415", ColorScheme::red);
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("[PENDING]", ColorScheme::orange);
    if(ImGui::IsItemHovered())
    {
        ImGui::SetMouseCursor(ImGuiMouseCursor_Hand);
    }

    ImGui::TextWrapped("TrayOnBoard:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("340", ColorScheme::green);

    if(ImGui::BeginTable("WorkstationLayout", 2, ImGuiTableFlags_SizingStretchSame))
    {
        ImGui::TableNextColumn();
        UIElements::CraneWorkstation("Right", 22);
        ImGui::TableNextColumn();
        UIElements::CraneWorkstation("Left", 425);
        ImGui::EndTable();
    }

    ImGui::EndChild();
}

void UIElements::CraneCards(int CardCount)
{
    float spaceing = 8.0f;
    int x = ImGui::GetContentRegionAvail().x - (int)(spaceing * (CardCount-1));
    int y = ImGui::GetContentRegionAvail().y / 2;
    for (int i = CardCount; i >= 1; i--)
    {
        std::string name = std::format("Crane_{}", i);
        UIElements::CraneCard(name, ImVec2(x/CardCount,y));
        if(i != 1) ImGui::SameLine(0.0f,spaceing); //keep on same line unless last loop
    }
}
