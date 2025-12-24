#include "../includes/ui.hpp"

void Ui::init(GLFWwindow* window) {
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
}

void Ui::beginFrame() {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Ui::render() {
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void Ui::loadUi(float fps) {
    ImGui::Begin("Inspector", nullptr, ImGuiWindowFlags_NoMove);
    float panelWidth = ImGui::GetContentRegionAvail().x;
    width = panelWidth;
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(12, 12));
    ImGui::BeginChild("PerformancePanel", ImVec2(panelWidth, 80), true);
    ImGui::PopStyleVar();
    ImGui::Text("Performance");
    ImGui::Separator();
    ImGui::Text("FPS: %.1f", fps);
    ImGui::EndChild();
    ImGui::Spacing();
    ImGui::BeginChild("PropertiesPanel", ImVec2(panelWidth, 260), true);
    ImGui::Text("Properties");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::ColorEdit4("Color", glm::value_ptr(color));
    ImGui::Spacing();
    ImGui::Text("Transform");
    ImGui::DragFloat3("Position", glm::value_ptr(position), 0.1f);
    ImGui::Spacing();
    ImGui::DragFloat3("Rotation", glm::value_ptr(rotation), 0.5f);
    ImGui::Spacing();
    ImGui::DragFloat3("Scale", glm::value_ptr(scale), 0.1f);
    ImGui::Spacing();
    ImGui::Text("Shadows");
    ImGui::SliderFloat("Shadow Strength", &darkenStrength, 0.0f, 2.0f);
    ImGui::EndChild();
    ImGui::BeginChild("WorldEffectsPanel", ImVec2(panelWidth, 0), true);
    ImGui::Text("World Effects");
    ImGui::Separator();
    ImGui::Spacing();
    ImGui::ColorEdit4("Color", glm::value_ptr(worldColor));
    ImGui::EndChild();
    ImGui::End();
}

void Ui::deleteUi() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}
