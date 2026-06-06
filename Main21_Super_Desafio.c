// =========================================
// IMPORTA RAYLIB E BIBLIOTECAS
// =========================================

#include "raylib.h"
#include "raymath.h"
#include <math.h>
#include <stdbool.h>

// =========================================
// DEFINIÇÕES
// =========================================

#define NUM_INIMIGOS 4

// =========================================
// ENUMS: ESTADOS E TIPOS
// =========================================

typedef enum EnemyState
{
    IDLE,
    PATROL,
    CHASE,
    FLEE,
    ATTACK
} EnemyState;

typedef enum EnemyType
{
    TYPE_GRUNT,  
    TYPE_RUNNER, 
    TYPE_BOSS    
} EnemyType;

// =========================================
// STRUCT DO INIMIGO EXPANDIDA
// =========================================

typedef struct Enemy
{
    Vector2 posicao;
    float velocidade;
    int direcao;
    float raio; 
    
    // IA e Tipo
    EnemyState estado;
    EnemyType tipo;
    bool ativo; // false = Inimigo morreu e sumirá do jogo
    
    // Status de Combate
    int hp;
    int hpMax;
    
    // Sistema de Cooldown de Ataque do Inimigo
    float attackCooldown; 
    float attackTimer;    

} Enemy;

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "IA Avançada - Sistema de Combate Completo");
    SetTargetFPS(60);

    // =========================================
    // STATUS DO JOGADOR
    // =========================================

    Vector2 jogador = { 300, 300 };
    float velocidadeJogador = 450;
    int hpJogador = 100;
    Color corJogador = BLUE;
    float danoTimer = 0.0f; 

    // NOVO: Mecânicas de Ataque do Jogador
    float playerAttackRange = 100.0f;    // Alcance do ataque do jogador
    float playerAttackCooldown = 0.4f; // Tempo entre os ataques
    float playerAttackTimer = 0.0f;    // Cronômetro do ataque
    int playerDano = 15;                // Dano por golpe (Dano no Boss é balanceado na lógica)

    // =========================================
    // INICIALIZAÇÃO DOS INIMIGOS
    // =========================================

    Enemy inimigos[NUM_INIMIGOS];

    // Inimigo 0: Grunt (Padrão)
    inimigos[0].tipo = TYPE_GRUNT;
    inimigos[0].posicao = (Vector2){ 700, 300 };
    inimigos[0].velocidade = 200;
    inimigos[0].direcao = 1;
    inimigos[0].raio = 25.0f;
    inimigos[0].estado = IDLE;
    inimigos[0].ativo = true;
    inimigos[0].hp = 40; inimigos[0].hpMax = 40;
    inimigos[0].attackCooldown = 1.0f; inimigos[0].attackTimer = 0;

    // Inimigo 1: Grunt (Padrão)
    inimigos[1].tipo = TYPE_GRUNT;
    inimigos[1].posicao = (Vector2){ 850, 450 };
    inimigos[1].velocidade = 220;
    inimigos[1].direcao = -1;
    inimigos[1].raio = 25.0f;
    inimigos[1].estado = IDLE;
    inimigos[1].ativo = true;
    inimigos[1].hp = 40; inimigos[1].hpMax = 40;
    inimigos[1].attackCooldown = 1.0f; inimigos[1].attackTimer = 0;

    // Inimigo 2: Runner (Fujão)
    inimigos[2].tipo = TYPE_RUNNER;
    inimigos[2].posicao = (Vector2){ 100, 500 };
    inimigos[2].velocidade = 50;
    inimigos[2].direcao = 1;
    inimigos[2].raio = 20.0f; 
    inimigos[2].estado = IDLE;
    inimigos[2].ativo = true;
    inimigos[2].hp = 20; inimigos[2].hpMax = 20;
    inimigos[2].attackCooldown = 0.0f; inimigos[2].attackTimer = 0;

    // Inimigo 3: O BOSS
    inimigos[3].tipo = TYPE_BOSS;
    inimigos[3].posicao = (Vector2){ 900, 150 };
    inimigos[3].velocidade = 140; 
    inimigos[3].direcao = -1;
    inimigos[3].raio = 50.0f; 
    inimigos[3].estado = IDLE;
    inimigos[3].ativo = true;
    inimigos[3].hp = 300; inimigos[3].hpMax = 300;
    inimigos[3].attackCooldown = 1.5f; 
    inimigos[3].attackTimer = 0;

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // =========================================
        // JOGADOR - LÓGICA E MOVIMENTO
        // =========================================

        if (IsKeyDown(KEY_D)) jogador.x += velocidadeJogador * delta;
        if (IsKeyDown(KEY_A)) jogador.x -= velocidadeJogador * delta;
        if (IsKeyDown(KEY_W)) jogador.y -= velocidadeJogador * delta;
        if (IsKeyDown(KEY_S)) jogador.y += velocidadeJogador * delta;

        // Efeito visual de tomar dano
        if (danoTimer > 0) danoTimer -= delta;
        corJogador = (danoTimer > 0) ? WHITE : BLUE;

        // Atualiza timer de ataque do jogador
        if (playerAttackTimer > 0) playerAttackTimer -= delta;

        // Centro do jogador para cálculo exato de distância esférica
        Vector2 centroJogador = { jogador.x + 25, jogador.y + 25 };

        // EXECUTA ATAQUE DO JOGADOR (Butão Direito do Mouse)
        if (IsKeyPressed(KEY_SPACE) && playerAttackTimer <= 0 && hpJogador > 0)
        {
            playerAttackTimer = playerAttackCooldown; // Inicia Cooldown

            // Verifica se algum inimigo vivo está no alcance do golpe
            for (int i = 0; i < NUM_INIMIGOS; i++)
            {
                if (!inimigos[i].ativo) continue;

                float distAtaque = Vector2Distance(centroJogador, inimigos[i].posicao);
                
                // Se a distância for menor que o alcance do player + o tamanho do inimigo: HIT!
                if (distAtaque <= playerAttackRange + inimigos[i].raio)
                {
                    inimigos[i].hp -= playerDano;
                    
                    // Se o HP do inimigo zerar, ele morre
                    if (inimigos[i].hp <= 0)
                    {
                        inimigos[i].hp = 0;
                        inimigos[i].ativo = false;
                    }
                }
            }
        }

        // =========================================
        // IA E COMBATE DOS INIMIGOS
        // =========================================

        int inimigosVivos = 0;

        for (int i = 0; i < NUM_INIMIGOS; i++)
        {
            if (!inimigos[i].ativo) continue; // Pula inimigos mortos
            inimigosVivos++;

            float distancia = Vector2Distance(centroJogador, inimigos[i].posicao);

            // 1. Atualiza Timers de Cooldown do inimigo
            if (inimigos[i].attackTimer > 0) inimigos[i].attackTimer -= delta;

            // 2. MÁQUINA DE ESTADOS (Decisões)
            if (inimigos[i].tipo == TYPE_RUNNER)
            {
                if (distancia < 350) inimigos[i].estado = FLEE;
                else inimigos[i].estado = PATROL;
            }
            else 
            {
                float alcanceInimigo = (inimigos[i].tipo == TYPE_BOSS) ? 90.0f : 50.0f;

                if (distancia <= alcanceInimigo)
                {
                    inimigos[i].estado = ATTACK;
                }
                else if (distancia > alcanceInimigo && distancia < 500)
                {
                    inimigos[i].estado = CHASE;
                }
                else if (distancia >= 500 && distancia < 700)
                {
                    inimigos[i].estado = PATROL;
                }
                else
                {
                    inimigos[i].estado = IDLE;
                }
            }

            // 3. EXECUÇÃO DOS ESTADOS DOS INIMIGOS
            switch (inimigos[i].estado)
            {
                case IDLE: break;

                case PATROL:
                    inimigos[i].posicao.x += inimigos[i].velocidade * inimigos[i].direcao * delta;
                    if (inimigos[i].posicao.x > 1100 || inimigos[i].posicao.x < 100)
                        inimigos[i].direcao *= -1;
                    break;

                case CHASE:
                    {
                        Vector2 dir = Vector2Normalize(Vector2Subtract(centroJogador, inimigos[i].posicao));
                        float multVel = (inimigos[i].tipo == TYPE_BOSS) ? 1.2f : 1.5f;
                        inimigos[i].posicao.x += dir.x * inimigos[i].velocidade * multVel * delta;
                        inimigos[i].posicao.y += dir.y * inimigos[i].velocidade * multVel * delta;
                    }
                    break;

                case FLEE:
                    {
                        Vector2 dir = Vector2Normalize(Vector2Subtract(inimigos[i].posicao, centroJogador));
                        inimigos[i].posicao.x += dir.x * inimigos[i].velocidade * 1.5f * delta;
                        inimigos[i].posicao.y += dir.y * inimigos[i].velocidade * 1.5f * delta;
                    }
                    break;

                case ATTACK:
                    if (inimigos[i].attackTimer <= 0 && hpJogador > 0)
                    {
                        inimigos[i].attackTimer = inimigos[i].attackCooldown;
                        int dano = (inimigos[i].tipo == TYPE_BOSS) ? 20 : 5;
                        hpJogador -= dano;
                        danoTimer = 0.2f; 
                        if (hpJogador < 0) hpJogador = 0;
                    }
                    break;
            }
        }

        // =========================================
        // DRAW (RENDERIZAÇÃO)
        // =========================================

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawRectangle(0, 620, 1200, 80, DARKGREEN); // Chão

        // Desenha Efeito Visual do Ataque do Jogador (Animação rápida de corte circular)
        if (playerAttackTimer > 0.25f) 
        {
            DrawCircleLinesV(centroJogador, playerAttackRange, Fade(SKYBLUE, 0.6f));
            DrawCircleV(centroJogador, playerAttackRange, Fade(SKYBLUE, 0.2f));
        }

        // Desenha Jogador
        if (hpJogador > 0)
        {
            DrawRectangleV(jogador, (Vector2){50, 50}, corJogador);
            DrawRectangle(jogador.x, jogador.y - 15, 50, 6, RED);
            DrawRectangle(jogador.x, jogador.y - 15, (hpJogador / 100.0f) * 50, 6, GREEN);
        }

        // Desenha Inimigos Vivos
        for (int i = 0; i < NUM_INIMIGOS; i++)
        {
            if (!inimigos[i].ativo) continue;

            Color corInimigo;
            if (inimigos[i].tipo == TYPE_BOSS)
            {
                corInimigo = (inimigos[i].attackTimer > 0) ? GOLD : PURPLE;
            }
            else if (inimigos[i].tipo == TYPE_RUNNER)
            {
                corInimigo = PINK;
            }
            else 
            {
                if (inimigos[i].estado == IDLE) corInimigo = GRAY;
                else if (inimigos[i].estado == PATROL) corInimigo = ORANGE;
                else if (inimigos[i].estado == CHASE) corInimigo = RED;
                else corInimigo = BLACK; 
            }

            // Corpo do Inimigo
            DrawCircleV(inimigos[i].posicao, inimigos[i].raio, corInimigo);

            // Barra de HP flutuante para TODOS os inimigos
            float larguraBarra = inimigos[i].raio * 2.0f;
            DrawRectangle(inimigos[i].posicao.x - inimigos[i].raio, inimigos[i].posicao.y - inimigos[i].raio - 15, larguraBarra, 6, RED);
            DrawRectangle(inimigos[i].posicao.x - inimigos[i].raio, inimigos[i].posicao.y - inimigos[i].raio - 15, (inimigos[i].hp / (float)inimigos[i].hpMax) * larguraBarra, 6, GREEN);
        }

        // =========================================
        // HUD / TEXTOS
        // =========================================

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.9f));
        DrawText("SISTEMA DE COMBATE TOTAL: Jogador vs Inimigos", 20, 20, 30, DARKBLUE);
        DrawText(TextFormat("HP JOGADOR: %d", hpJogador), 20, 60, 20, (hpJogador < 30) ? RED : DARKGREEN);
        DrawText("Controles: W,A,S,D (Mover) | ESPAÇO (Atacar em Área)", 20, 85, 20, DARKGRAY);
        
        DrawText(TextFormat("Inimigos Vivos: %d", inimigosVivos), 800, 60, 20, BLACK);

        // Telas de Fim de Jogo
        if (hpJogador <= 0)
        {
            DrawRectangle(0, 0, 1200, 700, Fade(BLACK, 0.8f));
            DrawText("GAME OVER", 450, 300, 60, RED);
        }
        else if (inimigosVivos == 0)
        {
            DrawRectangle(0, 0, 1200, 700, Fade(DARKBLUE, 0.8f));
            DrawText("WIN", 480, 300, 60, GREEN);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
