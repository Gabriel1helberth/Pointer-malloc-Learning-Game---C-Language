// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// Quantidade de plataformas na fase
#define NUM_PLATAFORMAS 5

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "Physics em Raylib - Pesado e Multiplas Plataformas");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    // Posição do jogador (começando um pouco mais alto)
    Vector2 jogador = { 100, 200 };

    // Velocidades
    float velocidadeY = 0;
    float velocidadeX = 350; // Um pouco mais rápido para compensar o peso

    // Gravidade aumentada (Personagem mais "pesado")
    float gravidade = 2500; 

    // Força do pulo ajustada para a nova gravidade
    float forcaPulo = -950;

    // Verifica se está no chão
    bool noChao = false;

    // =========================================
    // PLATAFORMAS (Array de Rectangles)
    // =========================================

    Rectangle plataformas[NUM_PLATAFORMAS] = {
        { 0, 600, 1200, 100 },   // [0] Chão principal
        { 300, 480, 200, 30 },   // [1] Plataforma 1
        { 600, 380, 200, 30 },   // [2] Plataforma 2
        { 900, 280, 150, 30 },   // [3] Plataforma 3
        { 150, 250, 150, 30 }    // [4] Plataforma 4
    };

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // DELTA TIME
        // =========================================
        float delta = GetFrameTime();

        // =========================================
        // MOVIMENTO HORIZONTAL
        // =========================================

        // Direita (Adicionado suporte às setinhas também)
        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            jogador.x += velocidadeX * delta;
        }

        // Esquerda
        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            jogador.x -= velocidadeX * delta;
        }

        // =========================================
        // PULO
        // =========================================

        // Só pula se estiver no chão
        if (IsKeyPressed(KEY_SPACE) && noChao)
        {
            velocidadeY = forcaPulo;
            noChao = false;
        }

        // =========================================
        // GRAVIDADE
        // =========================================

        velocidadeY += gravidade * delta;
        jogador.y += velocidadeY * delta;

        // =========================================
        // HITBOX DO JOGADOR
        // =========================================

        Rectangle jogadorRect = { jogador.x, jogador.y, 50, 50 };

        // =========================================
        // COLISÃO COM PLATAFORMAS
        // =========================================

        // Assume que está no ar até provar o contrário
        noChao = false; 

        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {
            if (CheckCollisionRecs(jogadorRect, plataformas[i]))
            {
                // Só colide se estiver caindo (velocidadeY > 0)
                // Isso permite pular e atravessar as plataformas por baixo!
                if (velocidadeY > 0 && (jogador.y + 50 - velocidadeY * delta) <= plataformas[i].y + 15)
                {
                    // Encosta jogador na plataforma
                    jogador.y = plataformas[i].y - 50;

                    // Para velocidade vertical
                    velocidadeY = 0;

                    // Marca que está no chão
                    noChao = true;
                }
            }
        }

        // Mecânica extra: se cair no buraco (fora da tela), volta pro início
        if (jogador.y > 900) 
        {
            jogador.x = 100;
            jogador.y = 200;
            velocidadeY = 0;
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // DESENHA PLATAFORMAS
        // =========================================

        // Faz um loop por todas as plataformas para desenhá-las
        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {
            DrawRectangleRec(plataformas[i], DARKGREEN);
        }

        // =========================================
        // JOGADOR
        // =========================================

        DrawRectangleV(jogador, (Vector2){50, 50}, BLUE);

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.9f));
        DrawText("Physics em Raylib", 20, 20, 30, DARKBLUE);
        DrawText("A/D ou Setas = mover | ESPACO = pular", 20, 60, 20, DARKGRAY);
        DrawText(TextFormat("Velocidade Y: %.2f", velocidadeY), 20, 90, 20, BLACK);
        DrawText(TextFormat("Posicao Y: %.2f", jogador.y), 320, 90, 20, BLACK);
        DrawText(TextFormat("No Chao: %s", noChao ? "SIM" : "NAO"), 620, 90, 20, BLACK);
        DrawText("Personagem mais pesado e multiplas plataformas", 720, 90, 20, MAROON);

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
