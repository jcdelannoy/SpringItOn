//#include "common.h"
//
//enum
//{
//    HISTORY_MAX = 256
//};
//
//float x_prev[HISTORY_MAX];
//float t_prev[HISTORY_MAX];
//
//int main(void)
//{
//    // Init Window
//    
//    const int screenWidth = 640;
//    const int screenHeight = 360;
//
//    InitWindow(screenWidth, screenHeight, "raylib [springs] example - damper");
//
//    // Init Variables
//
//    float t = 0.0;
//    float x = screenHeight / 2.0f;
//    float g = x;
//    float goalOffset = 600;
//    //float factor = 0.1;
//
//    //float damping = 10.0f;
//    float halflife = 0.1f;
//    float dt = 1.0 / 60.0f;
//    float timescale = 240.0f;
//
//    SetTargetFPS(1.0f / dt);
//
//    for (int i = 0; i < HISTORY_MAX; i++)
//    {
//        x_prev[i] = x;
//        t_prev[i] = t;
//    }    
//
//    while (!WindowShouldClose())
//    {
//        // Shift History
//        
//        for (int i = HISTORY_MAX - 1; i > 0; i--)
//        {
//            x_prev[i] = x_prev[i - 1];
//            t_prev[i] = t_prev[i - 1];
//        }
//
//        // Get Goal
//        
//        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
//        {
//            g = GetMousePosition().y;
//        }
//        
//        // Damper
//        
//        //factor = GuiSliderBar((Rectangle){ 100, 20, 120, 20 }, "factor", TextFormat("%5.3f", factor), factor, 0.0f, 1.0f);
//        //damping = GuiSliderBar((Rectangle){ 100, 20, 120, 20 }, "damping", TextFormat("%5.3f", damping), damping, 0.01f, 30.0f);
//        Rectangle rectA;
//        rectA.x = 100;
//        rectA.y = 20;
//        rectA.width = 120;
//        rectA.height = 20;
//        halflife = GuiSliderBar(rectA, "halflife", TextFormat("%5.3f", halflife), halflife, 0.0f, 1.0f);
//        Rectangle rectB;
//        rectB.x = 100;
//        rectB.y = 45;
//        rectB.width = 120;
//        rectB.height = 20;
//        dt = GuiSliderBar(rectB, "dt", TextFormat("%5.3f", dt), dt, 1.0 / 60.0f, 0.1f);
//
//        // Update Spring
//        
//        SetTargetFPS(1.0f / dt);
//        
//        t += dt;
//
//        //x = damper(x, g, factor);
//        //x = damper_bad(x, g, damping, dt);
//        //x = damper_exponential(x, g, damping, dt);
//        x = damper_exact(x, g, halflife, dt);
//        
//        x_prev[0] = x;
//        t_prev[0] = t;
//
//        BeginDrawing();
//        
//            ClearBackground(RAYWHITE);
//
//            Vector2 vecA;
//            vecA.x = goalOffset;
//            vecA.y = g;
//            DrawCircleV(vecA, 5, MAROON);
//            Vector2 vecB;
//            vecB.x = goalOffset;
//            vecB.y = x;
//            DrawCircleV(vecB, 5, DARKBLUE);
//            
//            for (int i = 0; i < HISTORY_MAX - 1; i++)
//            {
//                Vector2 x_start = {goalOffset - (t - t_prev[i + 0]) * timescale, x_prev[i + 0]};
//                Vector2 x_stop  = {goalOffset - (t - t_prev[i + 1]) * timescale, x_prev[i + 1]};
//            
//                DrawLineV(x_start, x_stop, BLUE);                
//                DrawCircleV(x_start, 2, BLUE);
//            }
//
//            
//        EndDrawing();
//        
//    }
//
//    CloseWindow();
//
//    return 0;
//}