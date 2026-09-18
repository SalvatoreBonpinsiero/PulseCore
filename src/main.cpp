#include <iostream>
#include <vector>
#include <cstdlib>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

void ApplyModernDarkTheme() {
    ImGuiStyle& style = ImGui::GetStyle();


    style.WindowRounding    = 8.0f;
    style.ChildRounding     = 6.0f;
    style.FrameRounding     = 5.0f;
    style.PopupRounding     = 6.0f;
    style.ScrollbarRounding = 4.0f;
    style.GrabRounding      = 4.0f;


    style.WindowPadding     = ImVec2(16.0f, 16.0f);
    style.FramePadding      = ImVec2(10.0f, 6.0f);
    style.ItemSpacing       = ImVec2(8.0f, 8.0f);


    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg]          = ImVec4(0.09f, 0.09f, 0.11f, 1.00f);
    colors[ImGuiCol_ChildBg]           = ImVec4(0.12f, 0.12f, 0.15f, 1.00f);
    colors[ImGuiCol_PopupBg]           = ImVec4(0.12f, 0.12f, 0.15f, 0.98f);
    colors[ImGuiCol_Border]            = ImVec4(0.20f, 0.20f, 0.25f, 0.50f);
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

    colors[ImGuiCol_CheckMark]         = ImVec4(0.95f, 0.95f, 1.00f, 1.00f);
    colors[ImGuiCol_SliderGrab]        = ImVec4(0.52f, 0.38f, 0.95f, 1.00f);
    colors[ImGuiCol_SliderGrabActive]  = ImVec4(0.60f, 0.46f, 1.00f, 1.00f);
}

int main() {
    if (!glfwInit()) return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(900, 560, "PulseCore - Sentinel Dashboard", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ApplyModernDarkTheme();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

 
    std::vector<float> ping_history(60, 22.0f);
    float current_ping = 22.0f;
    bool watchdog_enabled = true;
    int port_range = 1024;

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

       
        int w, h;
        glfwGetWindowSize(window, &w, &h);
        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2((float)w, (float)h));

        ImGuiWindowFlags root_flags = ImGuiWindowFlags_NoTitleBar 
                                    | ImGuiWindowFlags_NoResize 
                                    | ImGuiWindowFlags_NoMove;

        ImGui::Begin("RootDashboard", nullptr, root_flags);

        ImGui::TextColored(ImVec4(0.55f, 0.38f, 0.98f, 1.0f), "[*] PULSECORE");
        ImGui::SameLine();
        ImGui::TextDisabled("| System & Network Sentinel");

        ImGui::SameLine(ImGui::GetWindowWidth() - 85);
        if (ImGui::Button("Exit", ImVec2(70, 22))) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
        ImGui::Separator();
        ImGui::Spacing();

        ImGui::BeginChild("ConfigPanel", ImVec2(250, 0), true);
        ImGui::Text("Watchdog Configuration");
        ImGui::Spacing();
        ImGui::Checkbox("Active Sentry", &watchdog_enabled);
        ImGui::SliderInt("Scan Ports", &port_range, 80, 8080);
        
        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        if (ImGui::Button("Flush Metrics", ImVec2(-1, 32))) {
            std::fill(ping_history.begin(), ping_history.end(), 12.0f);
        }
        ImGui::EndChild();

        ImGui::SameLine();

        ImGui::BeginChild("MetricsPanel", ImVec2(0, 0), true);
        ImGui::Text("Network Latency Pipeline");

        current_ping += ((rand() % 100) / 10.0f - 4.8f);
        if (current_ping < 6.0f) current_ping = 6.0f;
        if (current_ping > 90.0f) current_ping = 90.0f;

        ping_history.erase(ping_history.begin());
        ping_history.push_back(current_ping);

        char overlay_text[32];
        sprintf(overlay_text, "RTT: %.1f ms", current_ping);
        ImGui::PlotLines("##latency_graph", ping_history.data(), (int)ping_history.size(), 0, overlay_text, 0.0f, 100.0f, ImVec2(-1, 140));

        ImGui::Spacing();
        ImGui::Text("Interface Status:");
        ImGui::BulletText("127.0.0.1:8080  - Local Proxy Router [ACTIVE]");
        ImGui::BulletText("0.0.0.0:51820    - WireGuard Tunnel   [ONLINE]");
        ImGui::BulletText("192.168.1.1:53   - DNS Sentry Daemon  [RESOLVING]");
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
