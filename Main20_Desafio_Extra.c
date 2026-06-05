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
    InitWindow(1200, 700, "Physics em Raylib - Pulo Duplo");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    // Posição do jogador
    Vector2 jogador = { 100, 200 };

    // Velocidades
    float velocidadeY = 0;
    float velocidadeX = 350;

    // Física
    float gravidade = 2500; 
    float forcaPulo = -950;

    // Controle de Pulo Duplo
    bool noChao = false;
    int pulosFeitos = 0; // Quantos pulos o jogador já deu no ar
    int maxPulos = 2;    // Limite de pulos (2 = Pulo Duplo)

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

        if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT))
        {
            jogador.x += velocidadeX * delta;
        }

        if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT))
        {
            jogador.x -= velocidadeX * delta;
        }

        // =========================================
        // PULO DUPLO
        // =========================================

        // Verifica se apertou ESPAÇO e se ainda tem pulos disponíveis
        if (IsKeyPressed(KEY_SPACE) && pulosFeitos < maxPulos)
        {
            // Aplica a força do pulo (funciona tanto no chão quanto no ar)
            velocidadeY = forcaPulo;
            
            // Registra que um pulo foi gasto
            pulosFeitos++;
            
            // Sai do chão
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

        noChao = false; 

        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {
            if (CheckCollisionRecs(jogadorRect, plataformas[i]))
            {
                if (velocidadeY > 0 && (jogador.y + 50 - velocidadeY * delta) <= plataformas[i].y + 15)
                {
                    // Encosta jogador na plataforma
                    jogador.y = plataformas[i].y - 50;
                    velocidadeY = 0;
                    
                    // Confirma que tocou no chão
                    noChao = true;
                    
                    // RECARREGA OS PULOS AO TOCAR NO CHÃO
                    pulosFeitos = 0; 
                }
            }
        }

        // Se o jogador cair da plataforma sem pular, consome o primeiro pulo
        // para evitar que ele dê dois pulos no ar depois de cair
        if (!noChao && pulosFeitos == 0 && velocidadeY > 0)
        {
            pulosFeitos = 1; 
        }

        // Reset ao cair no buraco
        if (jogador.y > 900) 
        {
            jogador.x = 100;
            jogador.y = 200;
            velocidadeY = 0;
            pulosFeitos = 0;
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DESENHA PLATAFORMAS
        for (int i = 0; i < NUM_PLATAFORMAS; i++)
        {
            DrawRectangleRec(plataformas[i], DARKGREEN);
        }

        // JOGADOR
        DrawRectangleV(jogador, (Vector2){50, 50}, BLUE);

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.9f));
        DrawText("Physics em Raylib", 20, 20, 30, DARKBLUE);
        DrawText("A/D ou Setas = mover | ESPACO = pular duplo", 20, 60, 20, DARKGRAY);
        DrawText(TextFormat("Velocidade Y: %.2f", velocidadeY), 20, 90, 20, BLACK);
        DrawText(TextFormat("No Chao: %s", noChao ? "SIM" : "NAO"), 320, 90, 20, BLACK);
        
        // Mostra visualmente quantos pulos restam
        DrawText(TextFormat("Pulos Restantes: %d", maxPulos - pulosFeitos), 620, 90, 20, DARKGREEN);

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
