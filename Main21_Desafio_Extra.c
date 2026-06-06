// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdbool.h>

// =========================================
// DEFINIÇÕES
// =========================================

#define NUM_INIMIGOS 5

// =========================================
// ESTADOS DO INIMIGO
// =========================================

typedef enum EnemyState
{
    IDLE,
    PATROL,
    CHASE,
    FLEE
} EnemyState;

// =========================================
// STRUCT DO INIMIGO
// =========================================

typedef struct Enemy
{
    // Posição
    Vector2 posicao;

    // Velocidade
    float velocidade;

    // Direção (1 para direita, -1 para esquerda)
    int direcao;

    // Estado atual
    EnemyState estado;
    
    // Fugir
    bool fugir; // true = fugir, false = persegue (Adicionado ponto e vírgula)

} Enemy;

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "Enemy AI - Estados: IDLE, PATROL, CHASE e FLEE");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // JOGADOR
    // =========================================

    Vector2 jogador = { 300, 300 };
    
    // Velocidade do jogador aumentada para compensar a velocidade do inimigo
    float velocidadJogador = 450;

    // =========================================
    // INIMIGOS (ARRAY)
    // =========================================

    Enemy inimigos[NUM_INIMIGOS];

    // Inimigo 0
    inimigos[0].posicao = (Vector2){ 700, 300 };
    inimigos[0].velocidade = 200;
    inimigos[0].direcao = 1;
    inimigos[0].estado = IDLE;
    inimigos[0].fugir = false; // Corrigido erro de digitação 'inimgos'

    // Inimigo 1
    inimigos[1].posicao = (Vector2){ 850, 450 };
    inimigos[1].velocidade = 220;
    inimigos[1].direcao = -1;
    inimigos[1].estado = IDLE;
    inimigos[1].fugir = false;

    // Inimigo 2
    inimigos[2].posicao = (Vector2){ 550, 150 };
    inimigos[2].velocidade = 180;
    inimigos[2].direcao = 1;
    inimigos[2].estado = IDLE;
    inimigos[2].fugir = false;
    
    // Inimigo 3
    inimigos[3].posicao = (Vector2){ 450, 250 };
    inimigos[3].velocidade = 190;
    inimigos[3].direcao = 1;
    inimigos[3].estado = IDLE;
    inimigos[3].fugir = false;
    
    // Inimigo 4
    inimigos[4].posicao = (Vector2){ 100, 500 };
    inimigos[4].velocidade = 50; 
    inimigos[4].direcao = -1;
    inimigos[4].estado = IDLE;
    inimigos[4].fugir = true; // Este inimigo irá fugir 

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
        // MOVIMENTO DO JOGADOR
        // =========================================

        if (IsKeyDown(KEY_D))
            jogador.x += velocidadJogador * delta;

        if (IsKeyDown(KEY_A))
            jogador.x -= velocidadJogador * delta;

        if (IsKeyDown(KEY_W))
            jogador.y -= velocidadJogador * delta;

        if (IsKeyDown(KEY_S))
            jogador.y += velocidadJogador * delta;

        // Variável para o HUD saber quantos estão perseguindo
        int inimigosPerseguindo = 0;

        // =========================================
        // LÓGICA DOS INIMIGOS
        // =========================================

        for (int i = 0; i < NUM_INIMIGOS; i++)
        {
            // DISTÂNCIA ENTRE JOGADOR E INIMIGO ATUAL
            float distancia = Vector2Distance(jogador, inimigos[i].posicao);

            // =========================================
            // TROCA DE ESTADO
            // =========================================
            
            if (distancia < 400)
            {
                if (inimigos[i].fugir)
                {
                    inimigos[i].estado = FLEE; // Se for fujão, muda para FLEE
                }
                else
                {
                    inimigos[i].estado = CHASE; // Se não, muda para CHASE
                    inimigosPerseguindo++;
                }
            }
            else if (distancia >= 400 && distancia < 600)
            {
                inimigos[i].estado = PATROL;
            }
            else
            {
                inimigos[i].estado = IDLE;
            }

            // =========================================
            // IA - IDLE
            // =========================================
            
            if (inimigos[i].estado == IDLE)
            {
                // Parado
            }

            // =========================================
            // IA - PATRULHA
            // =========================================
            
            if (inimigos[i].estado == PATROL)
            {
                inimigos[i].posicao.x += inimigos[i].velocidade * inimigos[i].direcao * delta;

                if (inimigos[i].posicao.x > 1000)
                {
                    inimigos[i].direcao = -1;
                }

                if (inimigos[i].posicao.x < 400)
                {
                    inimigos[i].direcao = 1;
                }
            }
            
            // =========================================
            // IA - PERSEGUIÇÃO
            // =========================================
            
            if (inimigos[i].estado == CHASE)
            {
                Vector2 direcao = Vector2Subtract(jogador, inimigos[i].posicao);
                direcao = Vector2Normalize(direcao);

                inimigos[i].posicao.x += direcao.x * inimigos[i].velocidade * 1.8f * delta;
                inimigos[i].posicao.y += direcao.y * inimigos[i].velocidade * 1.8f * delta;
            }
            
            // =========================================
            // IA - FUGA (FLEE)
            // =========================================
            
            if (inimigos[i].estado == FLEE)
            {
                // Vetor invertido para afastar do jogador
                Vector2 direcao = Vector2Subtract(inimigos[i].posicao, jogador);
                direcao = Vector2Normalize(direcao);

                inimigos[i].posicao.x += direcao.x * inimigos[i].velocidade * 1.5f * delta;
                inimigos[i].posicao.y += direcao.y * inimigos[i].velocidade * 1.5f * delta;
            }
        } // CHAVE DE FECHAMENTO DO LOOP FOR DOS INIMIGOS (Faltava aqui!)
        
        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // CHÃO
        // =========================================

        DrawRectangle(0, 620, 1200, 80, DARKGREEN);

        // =========================================
        // JOGADOR
        // =========================================

        DrawRectangleV(jogador, (Vector2){50, 50}, BLUE);

        // =========================================
        // DESENHA INIMIGOS E LINHAS DE VISÃO
        // =========================================

        for (int i = 0; i < NUM_INIMIGOS; i++)
        {
            Color corInimigo;

            if (inimigos[i].estado == IDLE)
            {
                corInimigo = GRAY;
            }
            else if (inimigos[i].estado == PATROL)
            {
                corInimigo = ORANGE;
            }
            else if (inimigos[i].estado == CHASE) 
            {
                corInimigo = RED;
                DrawLineV(jogador, inimigos[i].posicao, RED);
            }
            else // FLEE
            {
                corInimigo = PINK;
            }

            // Desenha o inimigo
            DrawRectangleV(inimigos[i].posicao, (Vector2){50, 50}, corInimigo);
        }

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.9f));

        DrawText("Enemy AI em Raylib - Estados: IDLE, PATROL, CHASE, FLEE", 20, 20, 30, DARKBLUE);

        DrawText("Teclas W, A, S, D = mover jogador", 20, 60, 20, DARKGRAY);

        DrawText(TextFormat("Inimigos Totais: %d", NUM_INIMIGOS), 20, 90, 20, BLACK);

        DrawText(TextFormat("Perseguindo: %d", inimigosPerseguindo), 250, 90, 20, 
                 inimigosPerseguindo > 0 ? RED : BLACK);

        DrawText("Cinza = IDLE | Laranja = Patrulha | Vermelho = Perseguicao | Rosa = Fuga", 450, 90, 20, MAROON);

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
