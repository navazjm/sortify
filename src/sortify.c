#include "imgui_impl_raylib.h"
#include "rlcimgui.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

char *get_config_path()
{
    const char *home = getenv("HOME");
    if (!home)
        return NULL;

    const char *relative = "/.config/sortify/imgui.ini";
    size_t len = strlen(home) + strlen(relative) + 1;

    char *full_path = (char *)malloc(len);
    if (full_path)
    {
        snprintf(full_path, len, "%s%s", home, relative);
    }

    return full_path;
}

void ensure_config_dir_exists()
{
    const char *home = getenv("HOME");
    if (!home)
        return;

    const char *config_dir = "/.config/sortify";
    size_t len = strlen(home) + strlen(config_dir) + 1;

    char *full_path = (char *)malloc(len);
    if (full_path)
    {
        snprintf(full_path, len, "%s%s", home, config_dir);
        mkdir(full_path, 0755); // Only creates if it doesn't exist
    }
}

bool imgui_ini_exists(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file)
    {
        fclose(file);
        return true;
    }
    return false;
}

int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_MAXIMIZED);
    InitWindow(GetScreenWidth(), GetScreenHeight(), "Sortify");
    SetTargetFPS(144);

    // Force internal framebuffer to update by doing a dummy resize
    // fixes weird offset issue
    int screen_w = GetScreenWidth();
    int screen_h = GetScreenHeight();
    SetWindowSize(screen_w - 1, screen_h - 1);
    SetWindowSize(screen_w, screen_h);

    igCreateContext(NULL);
    ImGuiIO *ioptr = igGetIO();
    ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
#ifdef IMGUI_HAS_DOCK
    ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ioptr->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
#endif

    int render_w = GetRenderWidth();
    int render_h = GetRenderHeight();
    ioptr->DisplayFramebufferScale = (ImVec2){(float)render_w / screen_w, (float)render_h / screen_h};

    igStyleColorsDark(NULL);
    ImGui_ImplRaylib_Init();
    ImFontAtlas_AddFontDefault(ioptr->Fonts, NULL);
    rligSetupFontAwesome();
    ImGui_ImplRaylib_BuildFontAtlas();

    ImGuiStyle *style = igGetStyle();
    style->WindowRounding = 0.0f;
    style->WindowBorderSize = 0.0f;

    bool first_launch = true;
    // store imgui.ini at $HOME/.config/sortify/imgui.ini
    ensure_config_dir_exists();
    char *ini_path = get_config_path();
    if (ini_path)
    {
        ioptr->IniFilename = ini_path;
        first_launch = !imgui_ini_exists(ini_path);
    }

    bool done = false;
    while (!done)
    {

        ImGui_ImplRaylib_ProcessEvents();
        ImGui_ImplRaylib_NewFrame();
        igNewFrame();

        ImGuiViewport *viewport = igGetMainViewport();

        ImVec2 newPos = {viewport->WorkPos.x, viewport->WorkPos.y};
        igSetNextWindowPos(newPos, ImGuiCond_Always, (ImVec2){0, 0});

        ImVec2 dockspace_size = viewport->WorkSize;
        igSetNextWindowSize(dockspace_size, ImGuiCond_Always);

        igSetNextWindowViewport(viewport->ID);
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse |
                                        ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                                        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
                                        ImGuiWindowFlags_NoBackground;

        igPushStyleVar_Vec2(ImGuiStyleVar_WindowPadding, (ImVec2){0, 0});
        igBegin("DockSpaceWindow", NULL, window_flags);
        {
            igPopStyleVar(1);

            ImGuiID dockspace_id = igGetID_Str("MyDockSpace");
            ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
            igDockSpace(dockspace_id, (ImVec2){0, 0}, dockspace_flags, NULL);

            static bool dock_initialized = false;
            if (!dock_initialized && first_launch)
            {
                igDockBuilderRemoveNode(dockspace_id);
                igDockBuilderAddNode(dockspace_id, dockspace_flags | ImGuiDockNodeFlags_DockSpace);
                igDockBuilderSetNodeSize(dockspace_id, dockspace_size);

                ImGuiID left_id, right_id;
                igDockBuilderSplitNode(dockspace_id, ImGuiDir_Right, 0.2f, &right_id, &left_id);

                igDockBuilderDockWindow("Main View", left_id);
                igDockBuilderDockWindow("Side Panel", right_id);

                igDockBuilderFinish(dockspace_id);
                dock_initialized = true;
            }
        }
        igEnd();

        igBegin("Main View", NULL, ImGuiWindowFlags_None);
        {
            igText("This is the main content area.");
            static float f = 0.0f;
            static int counter = 0;
            igSliderFloat("Float", &f, 0.0f, 1.0f, "%.3f", 0);
            if (igButton("Button", (ImVec2){0, 0}))
                counter++;
            igSameLine(0.0f, -1.0f);
            igText("counter = %d", counter);
        }
        igEnd();

        igBegin("Side Panel", NULL, ImGuiWindowFlags_None);
        {
            igText("This is the side panel (20%% width).");
            igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ioptr->Framerate, ioptr->Framerate);
        }
        igEnd();

        // Rendering
        igRender();
        BeginDrawing();
        ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
        EndDrawing();

        done = WindowShouldClose();
    }

    ImGui_ImplRaylib_Shutdown();
    igDestroyContext(NULL);
    CloseWindow();
    free(ini_path);
    return 0;
}
