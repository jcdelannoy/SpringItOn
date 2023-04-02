//#include "common.h"
//
////--------------------------------------
//
//float spring_energy(
//    float x, 
//    float v, 
//    float frequency,
//    float x_rest = 0.0f, 
//    float v_rest = 0.0f,
//    float scale = 1.0f)
//{
//    float s = frequency_to_stiffness(frequency);
//    
//    return (
//        squaref(scale * (v - v_rest)) + s * 
//        squaref(scale * (x - x_rest))) / 2.0f;
//}
//
//float resonant_frequency(float goal_frequency, float halflife)
//{
//    float d = halflife_to_damping(halflife);
//    float goal_stiffness = frequency_to_stiffness(goal_frequency);
//    float resonant_stiffness = goal_stiffness - (d*d)/4.0f;
//    return stiffness_to_frequency(resonant_stiffness);
//}
//
////--------------------------------------
//
//enum
//{
//    HISTORY_MAX = 256
//};
//
//float x_prev[HISTORY_MAX];
//float v_prev[HISTORY_MAX];
//float t_prev[HISTORY_MAX];
//float g_prev[HISTORY_MAX];
//
//int main(void)
//{
//    // Init Window
//    
//    const int screenWidth = 640;
//    const int screenHeight = 360;
//
//    InitWindow(screenWidth, screenHeight, "raylib [springs] example - resonance");
//
//    // Init Variables
//
//    float t = 0.0;
//    float x = screenHeight / 2.0f;
//    float v = 0.0;
//    float g = x;
//    float goalOffset = 600;
//
//    float frequency = 2.0f;
//    float halflife = 2.0f;
//    float dt = 1.0 / 60.0f;
//    float timescale = 240.0f;
//
//    float goal_frequency = 2.5f;
//    float res_frequency = 1.5f;
//    float energy = 0.0;
//    
//    SetTargetFPS(1.0f / dt);
//
//    for (int i = 0; i < HISTORY_MAX; i++)
//    {
//        x_prev[i] = x;
//        v_prev[i] = v;
//        t_prev[i] = t;
//        g_prev[i] = x;
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
//            g_prev[i] = g_prev[i - 1];
//        }
//        
//        // Get Goal
//        
//        g = screenHeight / 2.0f + 10.0 * sinf(t * 2.0f * M_PI * goal_frequency);
//        
//        // Resonance        
//        Rectangle rectA;
//        rectA.x = 125;
//        rectA.y = 95;
//        rectA.width = 120;
//        rectA.height = 20; 
//        if (GuiButton(rectA, "Resonant Frequency"))
//        {
//            frequency = resonant_frequency(goal_frequency, halflife);
//        }
//
//        Rectangle rectB;
//        rectB.x = 125;
//        rectB.y = 20;
//        rectB.width = 120;
//        rectB.height = 20; 
//        halflife = GuiSliderBar(rectB, "halflife", TextFormat("%5.3f", halflife), halflife, 0.0f, 4.0f);
//        Rectangle rectC;
//        rectC.x = 125;
//        rectC.y = 45;
//        rectC.width = 120;
//        rectC.height = 20;
//        frequency = GuiSliderBar(rectC, "frequency", TextFormat("%5.3f", frequency), frequency, 0.0f, 5.0f);
//        Rectangle rectD;
//        rectD.x = 125;
//        rectD.y = 70;
//        rectD.width = 120;
//        rectD.height = 20;
//        goal_frequency = GuiSliderBar(rectD, "goal frequency", TextFormat("%5.3f", goal_frequency), goal_frequency, 0.0f, 5.0f);
//       
//        energy = spring_energy(x, v, frequency, screenHeight/2.0f, 0.0f, 0.01f);
//        
//        Rectangle rectE;
//        rectE.x = 400;
//        rectE.y = 20;
//        rectE.width = 120;
//        rectE.height = 20; 
//        energy = GuiSliderBar(rectD, "energy", TextFormat("%4.1f", energy), energy, 0.0f, 160.0f);
//        
//        // Update Spring        
//        SetTargetFPS(1.0f / dt);
//        
//        t += dt;
//        
//        spring_damper_exact(x, v, g, 0.0f, frequency, halflife, dt);
//        
//        x_prev[0] = x;
//        v_prev[0] = v;      
//        t_prev[0] = t;
//        g_prev[0] = g;
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
//            for (int i = 0; i < HISTORY_MAX - 1; i++)
//            {
//                Vector2 g_start = {goalOffset - (t - t_prev[i + 0]) * timescale, g_prev[i + 0]};
//                Vector2 g_stop  = {goalOffset - (t - t_prev[i + 1]) * timescale, g_prev[i + 1]};
//                
//                DrawLineV(g_start, g_stop, MAROON);                
//                DrawCircleV(g_start, 2, MAROON);
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