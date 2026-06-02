#include "raylib.h"

typedef enum GameState
{
    MENU,
    GAME,
    INSTRUCTIONS,
    GAME_OVER
} GameState;

int main(void)
{
    InitWindow(800, 600, "==*Menu de Jogo*==");
   
    SetTargetFPS(60);
    
    InitAudioDevice();
       Sound sound = LoadSound("menu.mp3");
       Sound sound1 = LoadSound("jogo.mp3");
    
    GameState estadoAtual = MENU;
    
    Vector2 jogador = { 400, 225 };

    float velocidade = 4.55f;

    while (!WindowShouldClose())
    {
        if (estadoAtual == MENU)
        {            
            if (IsKeyPressed(KEY_ENTER))
            {
                estadoAtual = GAME;  
                PlaySound(sound1);
            }

            if (IsKeyPressed(KEY_I))
            {
                estadoAtual = INSTRUCTIONS;
                PlaySound(sound);
            }

            if (IsKeyPressed(KEY_ESCAPE))
            {
                break;
            }
        }
        else if (estadoAtual == INSTRUCTIONS)
        {
            if (IsKeyPressed(KEY_BACKSPACE))
            {
                estadoAtual = MENU;
            }
        }
        else if (estadoAtual == GAME)
        {
            if (IsKeyDown(KEY_RIGHT)) jogador.x += velocidade;
            if (IsKeyDown(KEY_LEFT))  jogador.x -= velocidade;
            if (IsKeyDown(KEY_UP))    jogador.y -= velocidade;
            if (IsKeyDown(KEY_DOWN))  jogador.y += velocidade;

            if (IsKeyPressed(KEY_G))
            {
                estadoAtual = GAME_OVER;
            }
        }
        else if (estadoAtual == GAME_OVER)
        {
            if (IsKeyPressed(KEY_R))
            {
                jogador = (Vector2){ 400, 225 };
                estadoAtual = GAME;
            }

            if (IsKeyPressed(KEY_M))
            {
                jogador = (Vector2){ 400, 225 };
                estadoAtual = MENU;
            }
        }
        BeginDrawing();

        ClearBackground(DARKGREEN);

        if (estadoAtual == MENU)
        {
            DrawText("JOGO DOS BLOCOS", 230, 90, 32, BLACK);
            DrawText("Pressione ENTER para jogar", 250, 170, 22, BLACK);
            DrawText("Pressione I para instrucoes", 260, 210, 22, BLUE);
            DrawText("Pressione ESC para sair", 275, 250, 22, RED);
        }
        else if (estadoAtual == INSTRUCTIONS)
        {
            DrawText("INSTRUCOES", 300, 80, 32, DARKBLUE);
            DrawText("Use as setas para mover o jogador.", 180, 160, 22, BLACK);
            DrawText("Pressione G para simular GAME OVER.", 180, 200, 22, BLACK);
            DrawText("Pressione BACKSPACE para voltar.", 180, 260, 22, MAROON);
        }
        else if (estadoAtual == GAME)
        {
            DrawText("JOGO RODANDO", 20, 20, 24, BLACK);
            DrawText("Pressione as setas para se mover", 20, 55, 18, RED);
            DrawText("Pressione G para Game Over", 20, 80, 18, MAROON);

            DrawRectangleV(jogador, (Vector2){ 40, 40 }, DARKBLUE);
            DrawRectangle(150, 100, 30, 30, MAROON);
            DrawRectangle(300, 200, 30, 30, MAROON);
            DrawRectangle(100, 150, 30, 30, MAROON);
            DrawRectangle(200, 250, 30, 30, MAROON);
            DrawRectangle(300, 350, 25, 25, GRAY);
            DrawRectangle(450, 350, 25, 25, GRAY);
            DrawRectangle(550, 450, 25, 25, GRAY);
            
            
        }
        else if (estadoAtual == GAME_OVER)
        {
            DrawText("GAME OVER", 270, 120, 48, RED);
            DrawText("Pressione R para reiniciar", 260, 220, 22, BLACK);
            DrawText("Pressione M para voltar ao menu", 235, 260, 22, GOLD);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
