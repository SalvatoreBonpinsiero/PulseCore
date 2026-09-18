#include <iostream>
#include <vector>
#include <cmath>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Настройка современного стиля UI
void ApplyModernDarkTheme() {
    ImGuiStyle& style = ImGui::GetStyle();
    
    // Скругления и геометрия
    style.WindowRounding    = 8.0f;
    style.ChildRounding     = 6.0f;
    style.FrameRounding     = 5.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;

    style.WindowPadding     = ImVec2(14.0f, 14.0f);
    style.FramePadding      = ImVec2(10.0f, 6.0f);
    style.ItemSpacing       = ImVec2(8.0f, 8.0f);

    // Палитра Dark Zinc + Violet
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]          = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
    colors[ImGuiCol_ChildBg]           = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_Border]            = ImVec4(0.20f, 0.20f, 0.24f, 0.50f);
    colors[ImGuiCol_Text]              = ImVec4(0.93f, 0.94f, 0.96f, 1.00f);
    colors[ImGuiCol_TextDisabled]      = ImVec4(0.45f, 0.47f, 0.53f, 1.00f);

    colors[ImGuiCol_FrameBg]           = ImVec4(0.15f, 0.15f, 0.19f, 1.00f);
    colors[ImGuiCol_FrameBgHovered]    = ImVec4(0.20f, 0.20f, 0.26f, 1.00f);
    colors[ImGuiCol_FrameBgActive]     = ImVec4(0.24f, 0.24f, 0.32f, 1.00f);

    colors[ImGuiCol_Button]            = ImVec4(0.44f, 0.28f, 0.86f, 1.00f);
    colors[ImGuiCol_ButtonHovered]     = ImVec4(0.52f, 0.35f, 0.95f, 1.00f);
    colors[ImGuiCol_ButtonActive]      = ImVec4(0.38f, 0.22f, 0.78f, 1.00f);

    colors[ImGuiCol_Header]            = ImVec4(0.18f, 0.18f, 0.24f, 1.00f);
    colors[ImGuiCol_HeaderHovered]     = ImVec4(0.25f, 0.25f, 0.33f, 1.00f);
    colors[ImGuiCol_HeaderActive]      = ImVec4(0.44f, 0.28f, 0.86f, 0.80f);
}

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(880, 560, "PulseCore - Sentinel Dashboard", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ApplyModernDarkTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Буфер истории задержки пакетов (Ping)
    std::vector<float> ping_history(60, 24.0f);
    float current_ping = 24.0f;
    bool service_watchdog = true;
    int scanned_ports = 1024;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Главное окно на весь вьюпорт
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        int w, h;
        glfwGetWindowSize(window, &w, &h);
        ImGui::SetNextWindowSize(ImVec2((float)w, (float)h));

        ImGuiWindowFlags win_flags = ImGuiWindowFlags_NoTitleBar 
                                   | ImGuiWindowFlags_NoResize 
                                   | ImGuiWindowFlags_NoMove;

        ImGui::Begin("PulseCoreRoot", nullptr, win_flags);

        // Header панели
        ImGui::TextColored(ImVec4(0.55f, 0.38f, 0.98f, 1.0f), "[*] PULSECORE");
        ImGui::SameLine();
        ImGui::TextDisabled("| Telemetry & Network Sentinel");

        ImGui::SameLine(ImGui::GetWindowWidth() - 90);
        if (ImGui::Button("Exit", ImVec2(80, 22))) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::Separator();
        ImGui::Spacing();

        // Левая панель: контроллеры
        ImGui::BeginChild("ControlPanel", ImVec2(240, 0), true);
        ImGui::Text("Watchdog Settings");
        ImGui::Spacing();
        ImGui::Checkbox("Socket Sentry", &service_watchdog);
        ImGui::SliderInt("Port Range", &scanned_ports, 80, 8080);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Flush Buffer", ImVec2(-1, 30))) {
            std::fill(ping_history.begin(), ping_history.end(), 15.0f);
        }
        ImGui::EndChild();

        ImGui::SameLine();

        // Правая панель: телеметрия и график
        ImGui::BeginChild("TelemetryPanel", ImVec2(0, 0), true);
        ImGui::Text("Network Latency Telemetry");
        
        // Симуляция плавающего пинга
        current_ping += ((rand() % 100) / 10.0f - 4.8f);
        if (current_ping < 8.0f) current_ping = 8.0f;
        if (current_ping > 95.0f) current_ping = 95.0f;

        ping_history.erase(ping_history.begin());
        ping_history.push_back(current_ping);

        char overlay[32];
        sprintf(overlay, "Current: %.1f ms", current_ping);
        ImGui::PlotLines("##latency", ping_history.data(), (int)ping_history.size(), 0, overlay, 0.0f, 120.0f, ImVec2(-1, 140));

        ImGui::Spacing();
        ImGui::Text("Active Listeners:");
        ImGui::BulletText("127.0.0.1:8080 - HTTP Proxy [LISTENING]");
        ImGui::BulletText("0.0.0.0:51820   - WireGuard Peer [ONLINE]");
        ImGui::BulletText("192.168.1.1:53   - Local DNS Resolver [ACTIVE]");
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();
        glViewport(0, 0, w, h);
        glClearColor(0.09f, 0.09f, 0.11f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
