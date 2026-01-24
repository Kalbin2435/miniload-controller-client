#include "UIElements.hpp"
#include "imgui.h"
#include <format>
#include <string>
#include "UIHelpers.hpp"
#include "ColorScheme.hpp"

void UIElements::AgoranCard(std::string childName, ImVec2 size)
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
    UIHelpers::ColoredText("YOOO", ColorScheme::green);

    //CleanUp
    ImGui::EndChild();
}

void UIElements::AgoranCards(int CardCount)
{
    float spaceing = 8.0f;
    int x = ImGui::GetContentRegionAvail().x - (int)(spaceing * (CardCount-1));
    int y = ImGui::GetContentRegionAvail().y / 2;
    for (int i = 1; i <= CardCount; i++)
    {
        std::string name = std::format("Crane_{}", i);
        UIElements::AgoranCard(name, ImVec2(x/CardCount,y));
        if(i != CardCount) ImGui::SameLine(0.0f,spaceing);
    }
}
