#include "UIElements.hpp"
#include "imgui.h"
#include <format>
#include <string>
#include "UIHelpers.hpp"

void UIElements::AgoranCard(std::string childName, ImVec2 size)
{
    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.15f, 0.15f, 0.15f, 1.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 12.0f);
    ImGui::BeginChild(childName.c_str(), size, ImGuiChildFlags_Borders | ImGuiWindowFlags_NoScrollbar);
    UIHelpers::CenterCursorBasedOnText(childName);

    ImGui::TextWrapped("Status:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("YOOO", ImVec4(0.99f, 0.55f, 0.15f, 1.0f));

    ImGui::TextWrapped("SapTask:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("YOOO", ImVec4(0.99f, 0.55f, 0.15f, 1.0f));

    ImGui::TextWrapped("TrayOnBoard:");
    ImGui::SameLine(0,5.0f);
    UIHelpers::ColoredText("YOOO", ImVec4(0.99f, 0.55f, 0.15f, 1.0f));

    //CleanUp
    ImGui::EndChild();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
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
//void ShowCardExample() {
//    ImGui::Begin("Card Window");
//
//    // Define card size
//    ImVec2 cardSize = ImVec2(300, 150);
//    
//    // Push styling for better visual separation
//    ImGui::PushStyleColor(ImGuiCol_ChildBg, ImVec4(0.2f, 0.2f, 0.2f, 1.0f)); // Dark grey bg
//    
//    // Create the card container
//    if (ImGui::BeginChild("Card1", cardSize, true, ImGuiWindowFlags_None)) {
//        ImGui::TextColored(ImVec4(1.0f, 0.8f, 0.0f, 1.0f), "Card Title");
//        ImGui::Separator();
//        ImGui::Spacing();
//        ImGui::TextWrapped("This is some text inside the card.");
//        ImGui::TextWrapped("You can add buttons or other widgets.");
//        
//        ImGui::Spacing();
//        if (ImGui::Button("Action")) {
//            // Button action here
//        }
//    }
//    ImGui::EndChild();
//    ImGui::PopStyleColor(); // Pop the background color
//
//    ImGui::End();
//}
