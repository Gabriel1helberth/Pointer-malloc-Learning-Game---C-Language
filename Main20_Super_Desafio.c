// =========================================
// IMPORTA RAYLIB E MATH
// =========================================
#include "raylib.h"
#include <math.h>

// =========================================
// ESTRUTURAS (Metroidvania / Sandbox)
// =========================================

typedef struct Player {
    Vector2 pos;
    Vector2 vel;
    Vector2 tamanho;
    int pulosFeitos;
    bool noChao;
    bool naParede;
    int direcaoParede;
    
    bool temDash;
    bool dandoDash;
    float tempoDash;
    int direcaoDash;
} Player;

typedef struct CaixaFisica {
    Vector2 pos;
    Vector2 vel;
    Vector2 tamanho;
} CaixaFisica;

typedef struct Plataforma {
    Rectangle rect;
    Color cor;
} Plataforma;

// =========================================
// MAIN
// =========================================
int main(void)
{
    const int telaLargura = 1200;
    const int telaAltura = 700;
    InitWindow(telaLargura, telaAltura, "Mario + Parkour + Metroidvania + Sandbox");
    SetTargetFPS(60);

    // =========================================
    // INICIALIZAÇÃO DOS OBJETOS
    // =========================================

    Player jogador = { 
        .pos = { 100, 400 }, 
        .vel = { 0, 0 }, 
        .tamanho = { 40, 40 },
        .temDash = false 
    };

    CaixaFisica caixa = {
        .pos = { 500, 200 },
        .vel = { 0, 0 },
        .tamanho = { 60, 60 }
    };

    Rectangle powerUpDash = { -400, 350, 30, 30 }; 
    bool pegouPowerUp = false;

    #define QTD_PLATAFORMAS 11
    Plataforma mapa[QTD_PLATAFORMAS] = {
        {{ -500, 600, 2500, 200 }}, 
        {{ 300, 450, 150, 30 }},    
        {{ 600, 300, 200, 30 }},    
        {{ 900, 150, 150, 30 }},    
        {{ 1100, -100, 50, 700 }},  
        {{ -600, -100, 50, 700 }},  
        {{ -200, 500, 100, 100 }},  
        {{ -400, 400, 150, 30 }},   
        {{ 150, 250, 50, 350 }},    
        {{ 1300, 400, 200, 30 }},   
        {{ -200, 200, 150, 30 }}    
    };

    // =========================================
    // CÂMERA (Ajustada para visão maior)
    // =========================================
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ telaLargura / 2.0f, telaAltura / 2.0f };
    camera.rotation = 0.0f;
    camera.zoom = 0.65f; // Começa mais afastada (65% do tamanho original)

    // Constantes de Física
    float gravidade = 2500;
    float deslizeParede = 400;
    float velAndar = 350;
    float velDash = 1000;
    float forcaPulo = -900;
    float forcaWallJumpX = 500;
    float forcaWallJumpY = -800;

    // LOOP PRINCIPAL
    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // =========================================
        // INPUT E LÓGICA DO JOGADOR
        // =========================================
        
        if (jogador.dandoDash) {
            jogador.tempoDash -= delta;
            jogador.vel.y = 0; 
            jogador.vel.x = jogador.direcaoDash * velDash;
            if (jogador.tempoDash <= 0) jogador.dandoDash = false;
        } else {
            jogador.vel.x = 0;
            if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) jogador.vel.x = velAndar;
            if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) jogador.vel.x = -velAndar;

            if (jogador.temDash && IsKeyPressed(KEY_LEFT_SHIFT) && !jogador.dandoDash) {
                jogador.dandoDash = true;
                jogador.tempoDash = 0.2f;
                jogador.direcaoDash = (jogador.vel.x < 0) ? -1 : 1;
                if (jogador.vel.x == 0) jogador.direcaoDash = 1;
            }

            if (jogador.naParede && jogador.vel.y > 0) {
                jogador.vel.y += deslizeParede * delta;
                if (jogador.vel.y > deslizeParede) jogador.vel.y = deslizeParede;
            } else {
                jogador.vel.y += gravidade * delta;
            }
        }

        if (IsKeyPressed(KEY_SPACE)) {
            if (jogador.naParede && !jogador.noChao) {
                jogador.vel.y = forcaWallJumpY;
                jogador.vel.x = jogador.direcaoParede * forcaWallJumpX;
                jogador.pulosFeitos = 1;
            } else if (jogador.pulosFeitos < 2) {
                jogador.vel.y = forcaPulo;
                jogador.pulosFeitos++;
            }
        }

        // =========================================
        // FÍSICA E COLISÃO
        // =========================================

        jogador.noChao = false;
        jogador.naParede = false;

        jogador.pos.x += jogador.vel.x * delta;
        Rectangle rectX = { jogador.pos.x, jogador.pos.y, jogador.tamanho.x, jogador.tamanho.y };
        
        for (int i = 0; i < QTD_PLATAFORMAS; i++) {
            if (CheckCollisionRecs(rectX, mapa[i].rect)) {
                if (jogador.vel.x > 0) {
                    jogador.pos.x = mapa[i].rect.x - jogador.tamanho.x;
                    jogador.naParede = true;
                    jogador.direcaoParede = -1;
                } else if (jogador.vel.x < 0) {
                    jogador.pos.x = mapa[i].rect.x + mapa[i].rect.width;
                    jogador.naParede = true;
                    jogador.direcaoParede = 1;
                }
                jogador.vel.x = 0;
            }
        }

        jogador.pos.y += jogador.vel.y * delta;
        Rectangle rectY = { jogador.pos.x, jogador.pos.y, jogador.tamanho.x, jogador.tamanho.y };

        for (int i = 0; i < QTD_PLATAFORMAS; i++) {
            if (CheckCollisionRecs(rectY, mapa[i].rect)) {
                if (jogador.vel.y > 0) {
                    jogador.pos.y = mapa[i].rect.y - jogador.tamanho.y;
                    jogador.noChao = true;
                    jogador.pulosFeitos = 0;
                } else if (jogador.vel.y < 0) {
                    jogador.pos.y = mapa[i].rect.y + mapa[i].rect.height;
                }
                jogador.vel.y = 0;
            }
        }

        caixa.vel.y += gravidade * delta;
        caixa.vel.x *= 0.9f; 
        caixa.pos.y += caixa.vel.y * delta;
        
        Rectangle rectCaixa = { caixa.pos.x, caixa.pos.y, caixa.tamanho.x, caixa.tamanho.y };
        
        for (int i = 0; i < QTD_PLATAFORMAS; i++) {
            if (CheckCollisionRecs(rectCaixa, mapa[i].rect) && caixa.vel.y > 0) {
                caixa.pos.y = mapa[i].rect.y - caixa.tamanho.y;
                caixa.vel.y = 0;
            }
        }

        Rectangle rectJogadorAtual = { jogador.pos.x, jogador.pos.y, jogador.tamanho.x, jogador.tamanho.y };
        rectCaixa.y = caixa.pos.y; 
        
        if (CheckCollisionRecs(rectJogadorAtual, rectCaixa)) {
            if (jogador.vel.y > 0 && jogador.pos.y + jogador.tamanho.y - 15 <= caixa.pos.y) {
                jogador.pos.y = caixa.pos.y - jogador.tamanho.y;
                jogador.vel.y = 0;
                jogador.noChao = true;
                jogador.pulosFeitos = 0;
            } else {
                if (jogador.pos.x < caixa.pos.x) { 
                    caixa.pos.x = jogador.pos.x + jogador.tamanho.x;
                    caixa.vel.x = 200;
                } else { 
                    caixa.pos.x = jogador.pos.x - caixa.tamanho.x;
                    caixa.vel.x = -200;
                }
            }
        }

        if (!pegouPowerUp && CheckCollisionRecs(rectJogadorAtual, powerUpDash)) {
            pegouPowerUp = true;
            jogador.temDash = true;
        }

        // =========================================
        // ATUALIZA CÂMERA (Segue e Faz Zoom)
        // =========================================
        
        // Controle de Zoom via Roda do Mouse
        float controleZoom = GetMouseWheelMove();
        if (controleZoom != 0) {
            camera.zoom += controleZoom * 0.05f;
            
            // Limita o zoom para não bugar (muito longe ou muito perto)
            if (camera.zoom < 0.25f) camera.zoom = 0.25f; 
            if (camera.zoom > 2.5f) camera.zoom = 2.5f;   
        }

        camera.target.x += (jogador.pos.x - camera.target.x) * 5.0f * delta; 
        camera.target.y += ((jogador.pos.y - 100) - camera.target.y) * 5.0f * delta;

        if (jogador.pos.y > 1500) {
            jogador.pos = (Vector2){ 100, 400 };
            jogador.vel.y = 0;
        }

        // =========================================
        // DRAW
        // =========================================
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode2D(camera);

            for (int i = 0; i < QTD_PLATAFORMAS; i++) {
                DrawRectangleRec(mapa[i].rect, DARKGRAY);
                DrawRectangleLinesEx(mapa[i].rect, 2, BLACK);
            }

            if (!pegouPowerUp) {
                DrawRectangleRec(powerUpDash, GOLD);
                DrawText("POWER-UP", powerUpDash.x - 20, powerUpDash.y - 20, 10, ORANGE);
            }

            DrawRectangleV(caixa.pos, caixa.tamanho, BROWN);
            DrawRectangleLines(caixa.pos.x, caixa.pos.y, caixa.tamanho.x, caixa.tamanho.y, BLACK);

            Color corJogador = jogador.dandoDash ? SKYBLUE : BLUE;
            if (jogador.naParede && !jogador.noChao) corJogador = PURPLE; 
            
            DrawRectangleV(jogador.pos, jogador.tamanho, corJogador);

        EndMode2D(); 

        // HUD
        DrawRectangle(0, 0, telaLargura, 80, Fade(BLACK, 0.7f));
        DrawText("Metroidvania Parkour Sandbox", 20, 10, 20, WHITE);
        DrawText("A/D: Andar | ESPACO: Pulo | Mouse Wheel: Ajustar Zoom", 20, 40, 15, LIGHTGRAY);
        
        if (jogador.temDash) {
            DrawText("Habilidade: Pressione SHIFT para DASH", 600, 40, 15, GOLD);
        } else {
            DrawText("Explore para encontrar habilidades...", 600, 40, 15, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
