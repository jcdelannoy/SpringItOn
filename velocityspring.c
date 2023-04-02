#include "common.h"

//--------------------------------------

void velocity_spring_damper_exact(
    float& x,
    float& v,
    float& xi,
    float x_goal,
    float v_goal,
    float halflife,
    float dt,
    float apprehension = 2.0f,
    float eps = 1e-5f)
{
    float x_diff = ((x_goal - xi) > 0.0f ? 1.0f : -1.0f) * v_goal;
    
    float t_goal_future = dt + apprehension * halflife;
    float x_goal_future = fabs(x_goal - xi) > t_goal_future * v_goal ?
        xi + x_diff * t_goal_future : x_goal;
    
    simple_spring_damper_exact(x, v, x_goal_future, halflife, dt);
    
    xi = fabs(x_goal - xi) > dt * v_goal ? xi + x_diff * dt : x_goal; 
}

//--------------------------------------

enum
{
    HISTORY_MAX = 256
};

float x_prev[HISTORY_MAX];
float v_prev[HISTORY_MAX];
float t_prev[HISTORY_MAX];

float xi_prev[HISTORY_MAX];

int main(void)
{
    // Init Window
    
    const int screenWidth = 640;
    const int screenHeight = 360;

    InitWindow(screenWidth, screenHeight, "raylib [springs] example - velocityspring");

    // Init Variables

    float t = 0.0;
    float x = screenHeight / 2.0f;
    float v = 0.0;
    float g = x;
    float goalOffset = 600;

    float halflife = 0.1f;
    float dt = 1.0 / 60.0f;
    float timescale = 240.0f;

    float goal_velocity = 100.0f;
    float apprehension = 2.0f;

    float xi = x;

    SetTargetFPS(1.0f / dt);

    for (int i = 0; i < HISTORY_MAX; i++)
    {
        x_prev[i] = x;
        v_prev[i] = v;
        t_prev[i] = t;
        
        xi_prev[i] = x;
    }

    while (!WindowShouldClose())
    {
        // Shift History
        
        for (int i = HISTORY_MAX - 1; i > 0; i--)
        {
            x_prev[i] = x_prev[i - 1];
            v_prev[i] = v_prev[i - 1];
            t_prev[i] = t_prev[i - 1];
            
            xi_prev[i] = xi_prev[i - 1];
        }
        
        // Get Goal
        
        if (IsMouseButtonDown(MOUSE_RIGHT_BUTTON))
        {
            g = GetMousePosition().y;
        }
        
        // Timed Spring
        Rectangle rectA;
        rectA.x = 100;
        rectA.y = 20;
        rectA.width = 120;
        rectA.height = 20;
        halflife = GuiSliderBar(rectA, "halflife", TextFormat("%5.3f", halflife), halflife, 0.0f, 1.0f);
        Rectangle rectB;
        rectB.x = 100;
        rectB.y = 45;
        rectB.width = 120;
        rectB.height = 20;
        goal_velocity = GuiSliderBar(rectB, "goal velocity", TextFormat("%5.3f", goal_velocity), goal_velocity, 0.0f, 500.0f);
        Rectangle rectC;
        rectC.x = 100;
        rectC.y = 75;
        rectC.width = 120;
        rectC.height = 20;
        apprehension = GuiSliderBar(rectC, "apprehension", TextFormat("%5.3f", apprehension), apprehension, 0.0f, 5.0f);
        
        // Update Spring
        
        SetTargetFPS(1.0f / dt);
        
        t += dt;
        
        velocity_spring_damper_exact(x, v, xi, g, goal_velocity, halflife, dt);
        
        x_prev[0] = x;
        v_prev[0] = v;      
        t_prev[0] = t;
        
        xi_prev[0] = xi;
        
        BeginDrawing();
        
            ClearBackground(RAYWHITE);
            
            Vector2 vecA;
            vecA.x = goalOffset;
            vecA.y = g; 
            DrawCircleV(vecA, 5, MAROON);
            Vector2 vecB;
            vecB.x = goalOffset;
            vecB.y = x;
            DrawCircleV(vecB, 5, DARKBLUE);
            
            for (int i = 0; i < HISTORY_MAX - 1; i++)
            {
                Vector2 g_start = {goalOffset - (t - t_prev[i + 0]) * timescale, xi_prev[i + 0]};
                Vector2 g_stop  = {goalOffset - (t - t_prev[i + 1]) * timescale, xi_prev[i + 1]};
                
                DrawLineV(g_start, g_stop, MAROON);                
                DrawCircleV(g_start, 2, MAROON);
            }
            
            for (int i = 0; i < HISTORY_MAX - 1; i++)
            {
                Vector2 x_start = {goalOffset - (t - t_prev[i + 0]) * timescale, x_prev[i + 0]};
                Vector2 x_stop  = {goalOffset - (t - t_prev[i + 1]) * timescale, x_prev[i + 1]};
            
                DrawLineV(x_start, x_stop, BLUE);                
                DrawCircleV(x_start, 2, BLUE);
            }
            
        EndDrawing();
        
    }

    CloseWindow();

    return 0;
}