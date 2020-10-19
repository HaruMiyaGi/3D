#pragma once
#include <Windows.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_dx11.h"
#include "imgui/imgui_impl_win32.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Gui
{
public:
	Gui()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		Style();
	}
	~Gui()
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();
	}
	void Init(HWND hwnd, ID3D11Device* device, ID3D11DeviceContext* context)
	{
		ImGui_ImplWin32_Init(hwnd);
		ImGui_ImplDX11_Init(device, context);
	}
	bool WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
			return true;
		else
			return false;
	}
	void StartFrame()
	{
		if (show)
		{
			ImGui_ImplDX11_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
		}
	}
	void EndFrame()
	{
		if (show)
		{
			Draw();
			ImGui::Render();
			ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
		}
	}

	void Toggle()
	{
		if (show)
			show = false;
		else
			show = true;
	}

private:
	void Draw()
	{
		if (ImGui::Begin("[F1]", 0, ImGuiWindowFlags_NoResize))
		{
			ImGui::Text("Hey :3");
		}
		ImGui::End();
	}
	void Style()
	{
		ImGuiStyle* style = &ImGui::GetStyle();

		style->Alpha = 0.9f;
		style->WindowPadding = ImVec2(15, 15);
		style->WindowRounding = 0.0f;
		style->WindowBorderSize = 1.0f;
		style->WindowTitleAlign = ImVec2(1.0f, 0.5f);
		//style->WindowTitleAlign = ImVec2(0.5f, 0.5f);
		style->WindowMenuButtonPosition = ImGuiDir_None;
		style->FramePadding = ImVec2(1, 1);
		style->FrameRounding = 2.0f;
		style->FrameBorderSize = 1.0f;
		style->ItemSpacing = ImVec2(6, 9);
		style->ItemInnerSpacing = ImVec2(10, 10);

		style->ScrollbarSize = 6.0f;
		style->ScrollbarRounding = 0.0f;

		style->WindowMinSize = ImVec2(280.f, 300.f);


		style->Colors[ImGuiCol_Text] = ImVec4(0.756f, 0.749f, 0.866f, 1.0f);
		style->Colors[ImGuiCol_WindowBg] = ImVec4(0.141f, 0.121f, 0.274f, 1.0f);
		style->Colors[ImGuiCol_Border] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);

		//style->Colors[ImGuiCol_TextDisabled] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		//style->Colors[ImGuiCol_ChildBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		//style->Colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		//style->Colors[ImGuiCol_BorderShadow] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_FrameBg] = ImVec4(0.117f, 0.101f, 0.227f, 1.0f);
		style->Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.117f, 0.101f, 0.227f, 1.0f);
		style->Colors[ImGuiCol_FrameBgActive] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);

		style->Colors[ImGuiCol_TitleBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
		style->Colors[ImGuiCol_TitleBgActive] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);
		style->Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

		style->Colors[ImGuiCol_MenuBarBg] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

		style->Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);
		style->Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.756f, 0.749f, 0.866f, 1.0f);
		style->Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

		style->Colors[ImGuiCol_CheckMark] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);

		style->Colors[ImGuiCol_SliderGrab] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);

		style->Colors[ImGuiCol_Button] = ImVec4(0.141f, 0.121f, 0.274f, 1.0f);
		style->Colors[ImGuiCol_ButtonHovered] = ImVec4(0.117f, 0.101f, 0.227f, 1.0f);
		style->Colors[ImGuiCol_ButtonActive] = ImVec4(0.388f, 0.301f, 0.866f, 1.0f);

		style->Colors[ImGuiCol_Header] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_Separator] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_SeparatorHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_SeparatorActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ResizeGrip] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ResizeGripActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_Tab] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TabHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TabActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TabUnfocused] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotLines] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotHistogram] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_DragDropTarget] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_NavHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_NavWindowingHighlight] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
		style->Colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
	}
private:
	bool show = true;
};