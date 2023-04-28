#include "gui.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_dx9.h"
#include "../imgui/imgui_impl_win32.h"
#define IMGUI_DEMO_MARKER(section)  do { if (GImGuiDemoMarkerCallback != NULL) GImGuiDemoMarkerCallback(__FILE__, __LINE__, section, GImGuiDemoMarkerCallbackUserData); } while (0)

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter
);

bool show_ontology_selection_window = true;
bool show_Load_First_Ontology_Menu = true;
bool show_calculation_tool_Menu = true;
bool tab_bar_flags = true;

static bool levenstein = false;
static bool jaro = false;
static bool jaccard = false;
static bool paris = false;
static bool pi = false;
static bool pc = false;
static bool probamap = false;
static bool summation = false;





ImGuiWindowFlags window_flags = 0;


 long __stdcall WindowProcess(
	HWND window,
	UINT message,
	WPARAM wideParameter,
	LPARAM longParameter)
{
	if (ImGui_ImplWin32_WndProcHandler(window, message, wideParameter, longParameter))
		return true;

	switch (message)
	{
	case WM_SIZE: {
		if (gui::device && wideParameter != SIZE_MINIMIZED)
		{
			gui::presentParameters.BackBufferWidth = LOWORD(longParameter);
			gui::presentParameters.BackBufferHeight = HIWORD(longParameter);
			gui::ResetDevice();
		}
	}return 0;

	case WM_SYSCOMMAND: {
		if ((wideParameter & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
	}break;

	case WM_DESTROY: {
		PostQuitMessage(0);
	}return 0;

	case WM_LBUTTONDOWN: {
		gui::position = MAKEPOINTS(longParameter); // set click points
	}return 0;

	case WM_MOUSEMOVE: {
		if (wideParameter == MK_LBUTTON)
		{
			const auto points = MAKEPOINTS(longParameter);
			auto rect = ::RECT{ };

			GetWindowRect(gui::window, &rect);

			rect.left += points.x - gui::position.x;
			rect.top += points.y - gui::position.y;

			if (gui::position.x >= 0 &&
				gui::position.x <= gui::WIDTH &&
				gui::position.y >= 0 && gui::position.y <= 19)
				SetWindowPos(
					gui::window,
					HWND_TOPMOST,
					rect.left,
					rect.top,
					0, 0,
					SWP_SHOWWINDOW | SWP_NOSIZE | SWP_NOZORDER
				);
		}

	}return 0;

	}

	return DefWindowProc(window, message, wideParameter, longParameter);
}
void SetupImGuiStyle()
 {
	 
	ImGuiStyle* style = &ImGui::GetStyle();
	ImVec4* colors = style->Colors;
	
	


	style->Alpha = 1.0f;
	style->DisabledAlpha = 0.6000000238418579f;
	style->WindowPadding = ImVec2(4.0f, 6.0f);
	style->WindowRounding = 0.0f;
	style->WindowBorderSize = 0.0f;
	style->WindowMinSize = ImVec2(32.0f, 32.0f);
	style->WindowTitleAlign = ImVec2(0.0f, 0.5f);
	style->WindowMenuButtonPosition = ImGuiDir_Left;
	style->ChildRounding = 0.0f;
	style->ChildBorderSize = 1.0f;
	style->PopupRounding = 0.0f;
	style->PopupBorderSize = 1.0f;
	style->FramePadding = ImVec2(8.0f, 6.0f);
	style->FrameRounding = 0.0f;
	style->FrameBorderSize = 1.0f;
	style->ItemSpacing = ImVec2(8.0f, 6.0f);
	style->ItemInnerSpacing = ImVec2(8.0f, 6.0f);
	style->CellPadding = ImVec2(4.0f, 2.0f);
	style->IndentSpacing = 20.0f;
	style->ColumnsMinSpacing = 6.0f;
	style->ScrollbarSize = 20.0f;
	style->ScrollbarRounding = 0.0f;
	style->GrabMinSize = 5.0f;
	style->GrabRounding = 0.0f;
	style->TabRounding = 4.0f;
	style->TabBorderSize = 0.0f;
	style->TabMinWidthForCloseButton = 0.0f;
	style->ColorButtonPosition = ImGuiDir_Right;
	style->ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style->SelectableTextAlign = ImVec2(0.0f, 0.0f);

	colors[ImGuiCol_Text] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	colors[ImGuiCol_TextDisabled] = ImVec4(0.4980392158031464f, 0.4980392158031464f, 0.4980392158031464f, 1.0f);
	colors[ImGuiCol_WindowBg] = ImVec4(0.9490196108818054f, 0.9490196108818054f, 0.9490196108818054f, 1.0f);
	colors[ImGuiCol_ChildBg] = ImVec4(0.9490196108818054f, 0.9490196108818054f, 0.9490196108818054f, 1.0f);
	colors[ImGuiCol_PopupBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_Border] = ImVec4(0.6000000238418579f, 0.6000000238418579f, 0.6000000238418579f, 1.0f);
	colors[ImGuiCol_BorderShadow] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_FrameBg] = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
	colors[ImGuiCol_FrameBgHovered] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 0.2000000029802322f);
	colors[ImGuiCol_FrameBgActive] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 1.0f);
	colors[ImGuiCol_TitleBg] = ImVec4(0.03921568766236305f, 0.03921568766236305f, 0.03921568766236305f, 1.0f);
	colors[ImGuiCol_TitleBgActive] = ImVec4(0.1568627506494522f, 0.2862745225429535f, 0.47843137383461f, 1.0f);
	colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.0f, 0.0f, 0.0f, 0.5099999904632568f);
	colors[ImGuiCol_MenuBarBg] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
	colors[ImGuiCol_ScrollbarBg] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
	colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.686274528503418f, 0.686274528503418f, 0.686274528503418f, 1.0f);
	colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.0f, 0.0f, 0.0f, 0.2000000029802322f);
	colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
	colors[ImGuiCol_CheckMark] = ImVec4(0.09803921729326248f, 0.09803921729326248f, 0.09803921729326248f, 1.0f);
	colors[ImGuiCol_SliderGrab] = ImVec4(0.686274528503418f, 0.686274528503418f, 0.686274528503418f, 1.0f);
	colors[ImGuiCol_SliderGrabActive] = ImVec4(0.0f, 0.0f, 0.0f, 0.5f);
	colors[ImGuiCol_Button] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
	colors[ImGuiCol_ButtonHovered] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 0.2000000029802322f);
	colors[ImGuiCol_ButtonActive] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 1.0f);
	colors[ImGuiCol_Header] = ImVec4(0.8588235378265381f, 0.8588235378265381f, 0.8588235378265381f, 1.0f);
	colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 0.2000000029802322f);
	colors[ImGuiCol_HeaderActive] = ImVec4(0.0f, 0.4666666686534882f, 0.8392156958580017f, 1.0f);
	colors[ImGuiCol_Separator] = ImVec4(0.4274509847164154f, 0.4274509847164154f, 0.4980392158031464f, 0.5f);
	colors[ImGuiCol_SeparatorHovered] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 0.7799999713897705f);
	colors[ImGuiCol_SeparatorActive] = ImVec4(0.09803921729326248f, 0.4000000059604645f, 0.7490196228027344f, 1.0f);
	colors[ImGuiCol_ResizeGrip] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.2000000029802322f);
	colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.6700000166893005f);
	colors[ImGuiCol_ResizeGripActive] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.949999988079071f);
	colors[ImGuiCol_Tab] = ImVec4(0.1764705926179886f, 0.3490196168422699f, 0.5764706134796143f, 0.8619999885559082f);
	colors[ImGuiCol_TabHovered] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.800000011920929f);
	colors[ImGuiCol_TabActive] = ImVec4(0.196078434586525f, 0.407843142747879f, 0.6784313917160034f, 1.0f);
	colors[ImGuiCol_TabUnfocused] = ImVec4(0.06666667014360428f, 0.1019607856869698f, 0.1450980454683304f, 0.9724000096321106f);
	colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.1333333402872086f, 0.2588235437870026f, 0.4235294163227081f, 1.0f);
	colors[ImGuiCol_PlotLines] = ImVec4(0.6078431606292725f, 0.6078431606292725f, 0.6078431606292725f, 1.0f);
	colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.0f, 0.4274509847164154f, 0.3490196168422699f, 1.0f);
	colors[ImGuiCol_PlotHistogram] = ImVec4(0.8980392217636108f, 0.6980392336845398f, 0.0f, 1.0f);
	colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.0f, 0.6000000238418579f, 0.0f, 1.0f);
	colors[ImGuiCol_TableHeaderBg] = ImVec4(0.1882352977991104f, 0.1882352977991104f, 0.2000000029802322f, 1.0f);
	colors[ImGuiCol_TableBorderStrong] = ImVec4(0.3098039329051971f, 0.3098039329051971f, 0.3490196168422699f, 1.0f);
	colors[ImGuiCol_TableBorderLight] = ImVec4(0.2274509817361832f, 0.2274509817361832f, 0.2470588237047195f, 1.0f);
	colors[ImGuiCol_TableRowBg] = ImVec4(0.0f, 0.0f, 0.0f, 0.0f);
	colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.0f, 1.0f, 1.0f, 0.05999999865889549f);
	colors[ImGuiCol_TextSelectedBg] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 0.3499999940395355f);
	colors[ImGuiCol_DragDropTarget] = ImVec4(1.0f, 1.0f, 0.0f, 0.8999999761581421f);
	colors[ImGuiCol_NavHighlight] = ImVec4(0.2588235437870026f, 0.5882353186607361f, 0.9764705896377563f, 1.0f);
	colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.0f, 1.0f, 1.0f, 0.699999988079071f);
	colors[ImGuiCol_NavWindowingDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.2000000029802322f);
	colors[ImGuiCol_ModalWindowDimBg] = ImVec4(0.800000011920929f, 0.800000011920929f, 0.800000011920929f, 0.3499999940395355f);

	ImGuiIO& io = ImGui::GetIO();
	io.Fonts->AddFontFromFileTTF("Assets/Fonts/SegoeUI.ttf", 16.0f, NULL);
}


void ShowHelperWindow(bool* p_open) {


}

void OntologySelectionTool(bool* p_open)
{
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	
	ImGui::SetNextWindowSize(ImVec2(520.000f, 280.000f), ImGuiCond_FirstUseEver);

	ImGui::Begin("Ontology Selection Tool", p_open,
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoResize);
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Load First Ontology")) {

			}
			if (ImGui::MenuItem("Load Second Ontology")) {

			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Exit"))
		{
			
			ImGui::EndMenu();
		}
	
		ImGui::EndMenuBar();
		ImGui::Spacing();
		ImGui::SetNextItemWidth(150.000f);
		ImGui::Text("Yago");
		if (ImGui::BeginTable("Yago", 4, NULL))
		{
		
			ImGui::TableSetupColumn("Number of classes");
			ImGui::TableSetupColumn("Number of instances");
			ImGui::TableSetupColumn("Total of axioms");
			ImGui::TableSetupColumn("Logical axioms");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%d", 2000);
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%d", 4000);
			ImGui::TableSetColumnIndex(2);
			ImGui::Text("%d", 200);
			ImGui::TableSetColumnIndex(3);
			ImGui::Text("%d", 1000);
		
			ImGui::EndTable();
		}
	
		ImGui::SetNextItemWidth(150.000f);
		ImGui::Text("Dbpedia");
		if (ImGui::BeginTable("Dbpedia", 4, NULL))
		{

			ImGui::TableSetupColumn("Number of classes");
			ImGui::TableSetupColumn("Number of instances");
			ImGui::TableSetupColumn("Total of axioms");
			ImGui::TableSetupColumn("Logical axioms");
			ImGui::TableHeadersRow();
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%d", 2000);
			ImGui::TableSetColumnIndex(1);
			ImGui::Text("%d", 4000);
			ImGui::TableSetColumnIndex(2);
			ImGui::Text("%d", 200);
			ImGui::TableSetColumnIndex(3);
			ImGui::Text("%d", 1000);
			ImGui::EndTable();
			
		}
	

	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
	ImGui::End();
}
}
void SimilarityCalculationTool(bool* p_open) {
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();

	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
	ImGui::SetNextWindowSize(ImVec2(520.000f, 280.000f), ImGuiCond_FirstUseEver);

	ImGui::Begin("Smilarity Calculation Tool", p_open,
		ImGuiWindowFlags_MenuBar |
		ImGuiWindowFlags_NoResize);
	
	static ImVector<int> active_tabs;
	static int next_tab_id = 0;
	active_tabs.push_back(next_tab_id++);
	
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Options"))
		{
			if (ImGui::MenuItem("Levenstein",0, &levenstein)) {

			}
			if (ImGui::MenuItem("Jaro", 0, &jaro)) {

			}
			if (ImGui::MenuItem("Jaccard", 0, &jaccard)) {

			}
			if (ImGui::MenuItem("Paris", 0, &paris)) {

			}
			if (ImGui::MenuItem("Pi", 0, &pi)) {

			}
			if (ImGui::MenuItem("Pc", 0, &pc)) {

			}
			if (ImGui::MenuItem("ProbaMap", 0, &probamap)) {

			}
			if (ImGui::MenuItem("Summation", 0, &summation)) {

			}
			ImGui::EndMenu();
		}

		ImGui::EndMenuBar();
	if (ImGui::BeginTabBar("TABBAR", tab_bar_flags))
	{	
			bool open = true;
		
			if (ImGui::BeginTabItem("leveinstein", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("leveinstein");
				if (ImGui::BeginTable("leveinstein", 4, NULL))
				{

					ImGui::TableSetupColumn("Number of classes");
					ImGui::TableSetupColumn("Number of instances");
					ImGui::TableSetupColumn("Total of axioms");
					ImGui::TableSetupColumn("Logical axioms");

					ImGui::TableHeadersRow();
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("%d", 2000);
					ImGui::TableSetColumnIndex(1);
					ImGui::Text("%d", 4000);
					ImGui::TableSetColumnIndex(2);
					ImGui::Text("%d", 200);
					ImGui::TableSetColumnIndex(3);
					ImGui::Text("%d", 1000);

					ImGui::EndTable();
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Jaro", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the Jaro tab!");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Jaccard", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the Jaccard tab!");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Paris", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the Paris tab!");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("PI", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the PI tab!");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("PC", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the PC tab!");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("ProbaMap", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the ProbaMap tab!");
				ImGui::EndTabItem();
			}

			if (ImGui::BeginTabItem("Summation", &open, ImGuiTabItemFlags_None))
			{
				ImGui::Text("This is the Summation tab!");
				ImGui::EndTabItem();
			}

		ImGui::EndTabBar();


	ImGui::End();
}
}
}


void gui::CreateHWindow(const char* windowName) noexcept
{
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_CLASSDC;
	
	windowClass.lpfnWndProc = (WNDPROC) WindowProcess;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = GetModuleHandleA(0);
	windowClass.hIcon = 0;
	windowClass.hCursor = 0;
	windowClass.hbrBackground = 0;
	windowClass.lpszMenuName = 0;
	windowClass.lpszClassName = "class001";
	windowClass.hIconSm = 0;

	RegisterClassEx(&windowClass);

	window = CreateWindowEx(
		0,
		"class001",
		windowName,
		WS_OVERLAPPEDWINDOW,
		100,
		100,
		WIDTH,
		HEIGHT,
		nullptr, nullptr, windowClass.hInstance, nullptr
	);

	ShowWindow(window, SW_SHOWDEFAULT);
	UpdateWindow(window);
}

void gui::DestroyHWindow() noexcept
{
	DestroyWindow(window);
	UnregisterClass(windowClass.lpszClassName, windowClass.hInstance);
}

bool gui::CreateDevice() noexcept
{
	d3d = Direct3DCreate9(D3D_SDK_VERSION);

	if (!d3d)
		return false;

	ZeroMemory(&presentParameters, sizeof(presentParameters));

	presentParameters.Windowed = TRUE;
	presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;
	presentParameters.EnableAutoDepthStencil = TRUE;
	presentParameters.AutoDepthStencilFormat = D3DFMT_D16;
	presentParameters.PresentationInterval = D3DPRESENT_INTERVAL_ONE;

	if (d3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		window,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&presentParameters,
		&device) < 0)
		return false;

	return true;
}

void gui::ResetDevice() noexcept
{
	ImGui_ImplDX9_InvalidateDeviceObjects();

	const auto result = device->Reset(&presentParameters);

	if (result == D3DERR_INVALIDCALL)
		IM_ASSERT(0);

	ImGui_ImplDX9_CreateDeviceObjects();
}

void gui::DestroyDevice() noexcept
{
	if (device)
	{
		device->Release();
		device = nullptr;
	}

	if (d3d)
	{
		d3d->Release();
		d3d = nullptr;
	}
}

void gui::CreateImGui() noexcept
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;   
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  
	io.ConfigFlags |= ImGuiViewportFlags_IsPlatformWindow;
	io.IniFilename = NULL;

	//SetupImGuiStyle();
	ImGui::StyleColorsDark();

	
	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(device);
}

void gui::DestroyImGui() noexcept
{
	ImGui_ImplDX9_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void gui::BeginRender() noexcept
{
	MSG message;
	while (PeekMessage(&message, 0, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&message);
		DispatchMessage(&message);

		if (message.message == WM_QUIT)
		{
			isRunning = !isRunning;
			return;
		}
	}

	// Start the Dear ImGui frame
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void gui::EndRender() noexcept
{
	

	device->SetRenderState(D3DRS_ZENABLE, FALSE);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
	device->SetRenderState(D3DRS_SCISSORTESTENABLE, FALSE);

	device->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(0, 0, 0, 255), 1.0f, 0);

	if (device->BeginScene() >= 0)
	{
		ImGui::Render();

		ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		device->EndScene();
	}
	ImGui::EndFrame();

	const auto result = device->Present(0, 0, 0, 0);

	// Handle loss of D3D9 device
	if (result == D3DERR_DEVICELOST && device->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		ResetDevice();
}

void gui::Render() noexcept
{
	
	ImGui::SetNextWindowPos({ 0, 0 });
	ImGui::SetNextWindowSize({ WIDTH, HEIGHT });
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	OntologySelectionTool(&show_ontology_selection_window);
	SimilarityCalculationTool(&show_calculation_tool_Menu);

	
}

