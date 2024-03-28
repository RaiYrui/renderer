#include"UWidget.h"
namespace RR {
    Window* UWidget::window = nullptr;
	UWidget::UWidget(std::shared_ptr<World>world) {
		this->world = world;
        this->window = Window::getInstance();
        this->main_viewport = nullptr;
        this->window_flags = 0;
        this->utype = U_Entity;
        this->dis_index = -1;
	}
	void UWidget::Init() {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
        ImGui::StyleColorsDark();
        ImGui_ImplGlfw_InitForOpenGL(Window::glfw_window, true);
        ImGui_ImplOpenGL3_Init("#version 330");
	}
    void UWidget::Hierarchy() {
        this->main_viewport = ImGui::GetMainViewport();
        static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
        int index = 0;
        this->window_flags = 0;
        this->window_flags |= ImGuiWindowFlags_NoMove;
        this->window_flags |= ImGuiWindowFlags_NoResize;
        this->window_flags |= ImGuiWindowFlags_NoCollapse;
        bool* p = nullptr;
        static int selection_mask = (1 << 2);
        int node_clicked = -1;
        ImGui::SetNextWindowPos(this->main_viewport->Pos);
        ImGui::SetNextWindowSize(ImVec2(this->window->H_width,this->window->H_height));
        if (!ImGui::Begin("Hierarchy",p, this->window_flags))
        {
            ImGui::End();
            return;
        }
        //添加Light
        ImGuiTreeNodeFlags light_flag = base_flags;
        this->lights = this->world->get_Lights();
        if ((selection_mask & (1 << index)) != 0)
            light_flag |= ImGuiTreeNodeFlags_Selected;
        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)index, light_flag, "Lights");
        //点击灯光组
        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            node_clicked = index;
            this->dis_index = -1;
        }
        if (node_open) {
            ImGuiTreeNodeFlags lights_flag = base_flags;
            lights_flag |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
            //每个灯光
            for (int j = 0; j < lights.size(); ++j) {
                index++;
                if ((selection_mask & (1 << index)) != 0)
                    lights_flag |= ImGuiTreeNodeFlags_Selected;
                ImGui::TreeNodeEx((void*)(intptr_t)index, lights_flag, lights[j]->name.c_str());
                //点击灯光Item
                if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                    node_clicked = index;
                    this->utype = U_Light;
                    this->dis_index = j;
                }
            }
            ImGui::TreePop();
        }
        ImGuiTreeNodeFlags entity_flag = base_flags;
        entity_flag |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen;
        this->El = this->world->get_Entitylist();
        //每个物体
        for (int j=0 ; j <El.size(); ++j) {
            ++index;
            if ((selection_mask & (1 << index)) != 0)
                entity_flag |= ImGuiTreeNodeFlags_Selected;
            ImGui::TreeNodeEx((void*)(intptr_t)index, entity_flag, El[j]->name.c_str());
            //点击物体Item
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
                node_clicked = index;
                this->utype = U_Entity;
                this->dis_index = j;
            }
        }
        if (node_clicked != -1)
        {
            if (ImGui::GetIO().KeyCtrl)
                selection_mask ^= (1 << node_clicked);          
            else 
                selection_mask = (1 << node_clicked); 
        }
        ImGui::End();
    }
    void UWidget::Inspector() {
        this->main_viewport = ImGui::GetMainViewport();
        this->window_flags = 0;
        this->window_flags |= ImGuiWindowFlags_NoMove;
        this->window_flags |= ImGuiWindowFlags_NoResize;
        this->window_flags |= ImGuiWindowFlags_NoCollapse;
        bool* p = nullptr;
        ImGui::SetNextWindowPos(ImVec2(this->main_viewport->Pos.x + this->window->H_width+this->window->gl_width, this->main_viewport->Pos.y));
        ImGui::SetNextWindowSize(ImVec2(this->window->Ins_width , this->window->Ins_height));
        if (!ImGui::Begin("Inspector", p, this->window_flags))
        {
            ImGui::End();
            return;
        }
        if (this->dis_index >= 0) {
            if (this->utype == U_Entity) {
                this->El[this->dis_index]->component_dis();
            }
            else if (this->utype == U_Light) {
                this->lights[this->dis_index]->component_dis();
            }
            else {

            }
        }

        ImGui::End();
    }
    void UWidget::Resources() {
        this->main_viewport = ImGui::GetMainViewport();
        this->window_flags = 0;
        this->window_flags |= ImGuiWindowFlags_NoMove;
        this->window_flags |= ImGuiWindowFlags_NoResize;
        this->window_flags |= ImGuiWindowFlags_NoCollapse;
        bool* p = nullptr;
        ImGui::SetNextWindowPos(ImVec2(this->main_viewport->Pos.x, this->main_viewport->Pos.y+this->window->gl_height));
        ImGui::SetNextWindowSize(ImVec2(this->window->R_width , this->window->R_height));
        if (!ImGui::Begin("Resources", p, this->window_flags))
        {
            ImGui::End();
            return;
        }
        ImGui::End();
    }
    void UWidget::updategui() {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //ImGui::ShowDemoWindow(&demo);
        this->Hierarchy();
        this->Inspector();
        this->Resources();
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}