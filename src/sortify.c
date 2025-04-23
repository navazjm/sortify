#include "imgui_impl_raylib.h"
#include "raylib.h"
#include "rlcimgui.h"
#include <stdlib.h>

// Main code
int main()
{
    // Setup raylib window
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 720, "Sortify");
    SetTargetFPS(144);

    // Setup Dear ImGui context
    igCreateContext(NULL);
    ImGuiIO *ioptr = igGetIO();
    ioptr->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

    // set docking
#ifdef IMGUI_HAS_DOCK
    ioptr->ConfigFlags |= ImGuiConfigFlags_DockingEnable;   // Enable Docking
    ioptr->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
#endif

    // Setup Dear ImGui style
    igStyleColorsDark(NULL);

    // Setup Platform/Renderer backends
    ImGui_ImplRaylib_Init();

    ImFontAtlas_AddFontDefault(ioptr->Fonts, NULL);
    rligSetupFontAwesome();

    // required to be called to cache the font texture with raylib
    ImGui_ImplRaylib_BuildFontAtlas();

    // Our state
    bool showDemoWindow = true;
    bool showAnotherWindow = false;
    ImVec4 clearColor = {0.45f, 0.55f, 0.60f, 1.00f};

    // Main loop
    bool done = false;
    while (!done)
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your
        // inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or
        // clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or
        // clear/overwrite your copy of the keyboard data. Generally you may always pass all inputs to dear imgui, and
        // hide them from your application based on those two flags.
        ImGui_ImplRaylib_ProcessEvents();

        // Start the Dear ImGui frame
        ImGui_ImplRaylib_NewFrame();
        igNewFrame();

        {
            static float f = 0.0f;
            static int counter = 0;

            igBegin("Hello, world!", NULL, 0); // Create a window called "Hello, world!" and append into it.

            igText("This is some useful text.");        // Display some text (you can use a format strings too)
            igCheckbox("Demo Window", &showDemoWindow); // Edit bools storing our window open/close state
            igCheckbox("Another Window", &showAnotherWindow);

            igSliderFloat("Float", &f, 0.0f, 1.0f, "%.3f", 0); // Edit 1 float using a slider from 0.0f to 1.0f

            ImVec2 buttonSize;
            buttonSize.x = 0;
            buttonSize.y = 0;
            if (igButton(
                    "Button",
                    buttonSize)) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            igSameLine(0.0f, -1.0f);
            igText("counter = %d", counter);

            igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / igGetIO()->Framerate,
                   igGetIO()->Framerate);
            igEnd();
        }

        // Rendering
        igRender();
        BeginDrawing();
        ClearBackground((Color){(unsigned char)(clearColor.x * 255), (unsigned char)(clearColor.y * 255),
                                (unsigned char)(clearColor.z * 255), (unsigned char)(clearColor.w * 255)});
        ImGui_ImplRaylib_RenderDrawData(igGetDrawData());
        EndDrawing();

        done = WindowShouldClose();
    }

    // Cleanup
    ImGui_ImplRaylib_Shutdown();
    igDestroyContext(NULL);

    CloseWindow();

    return 0;
}
