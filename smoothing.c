//#include "common.h"
//
//enum
//{
//    HISTORY_MAX = 256
//};
//
//float x_prev[HISTORY_MAX];
//float v_prev[HISTORY_MAX];
//float t_prev[HISTORY_MAX];
//
//int main(void)
//{
//    // Init Window
//    
//    const int screenWidth = 640;
//    const int screenHeight = 360;
//
//    InitWindow(screenWidth, screenHeight, "raylib [springs] example - smoothing");
//
//    // Init Variables
//
//    float t = 0.0;
//    float x = screenHeight / 2.0f;
//    float v = 0.0;
//    float g = x;
//    float goalOffset = 600;
//
//    float halflife = 0.1f;
//    float dt = 1.0 / 60.0f;
//    float timescale = 240.0f;
//    
//    float noise = 0.0f;
//    float jitter = 0.0f;
//    
//    SetTargetFPS(1.0f / dt);
//
//    for (int i = 0; i < HISTORY_MAX; i++)
//    {
//        x_prev[i] = x;
//        v_prev[i] = v;
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
//            v_prev[i] = v_prev[i - 1];
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
//        g += noise * (((float)rand() / RAND_MAX) * 2.0f - 1.0);
//        
//        if (jitter)
//        {
//            g -= jitter;
//            jitter = 0.0;
//        }
//        else if (rand() % (int)(0.5 / dt) == 0)
//        {
//            jitter = noise * 10.0f * (((float)rand() / RAND_MAX) * 2.0f - 1.0);
//            g += jitter;
//        }
//        
//        // Spring Damper
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
//        Rectangle rectC;
//        rectC.x = 100;
//        rectC.y = 70;
//        rectC.width = 120;
//        rectC.height = 20;
//        noise = GuiSliderBar(rectC, "noise", TextFormat("%5.3f", noise), noise, 0.0f, 20.0f);
//        
//        // Update Spring
//        
//        SetTargetFPS(1.0f / dt);
//        
//        t += dt;
//        
//        simple_spring_damper_exact(x, v, g, halflife, dt);
//        
//        x_prev[0] = x;
//        v_prev[0] = v;      
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
//        EndDrawing();
//        
//    }
//
//    CloseWindow();
//
//    return 0;
//}