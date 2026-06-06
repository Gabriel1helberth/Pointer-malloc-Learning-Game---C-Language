// =========================================
// IMPORTA RAYLIB E BIBLIOTECAS C
// =========================================

#include "raylib.h"
#include <stdio.h>
#include <string.h>

// =========================================
// CONSTANTES DE LIMITES
// =========================================

#define VIDA_MAXIMA 100
#define FASE_MAXIMA 3
#define TOTAL_SLOTS 3

// =========================================
// STRUCT SAVE DATA
// =========================================

typedef struct SaveData
{
    char nome[50];   // Nome do jogador
    Vector2 jogador; // Posição do jogador
    int score;       // Score
    int vida;        // Vida do jogador 
    int fase;        // Fase atual do jogo 
} SaveData;

// =========================================
// FUNÇÃO SAVE E LOAD
// =========================================

void SalvarJogo(SaveData dados, int slot)
{
    char nomeArquivo[32];
    sprintf(nomeArquivo, "save_slot_%d.txt", slot);
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%s\n", dados.nome);
        fprintf(arquivo, "%f\n", dados.jogador.x);
        fprintf(arquivo, "%f\n", dados.jogador.y);
        fprintf(arquivo, "%d\n", dados.score);
        fprintf(arquivo, "%d\n", dados.vida);
        fprintf(arquivo, "%d\n", dados.fase);
        fclose(arquivo);
    }
}

void CarregarJogo(SaveData *dados, int slot)
{
    char nomeArquivo[32];
    sprintf(nomeArquivo, "save_slot_%d.txt", slot);
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL)
    {
        fscanf(arquivo, "%49s", dados->nome);
        fscanf(arquivo, "%f", &dados->jogador.x);
        fscanf(arquivo, "%f", &dados->jogador.y);
        fscanf(arquivo, "%d", &dados->score);
        fscanf(arquivo, "%d", &dados->vida);
        fscanf(arquivo, "%d", &dados->fase);
        fclose(arquivo);
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    InitWindow(1200, 700, "Save System - Fases Diferentes");
    SetTargetFPS(60);

    SaveData dados;
    strcpy(dados.nome, "Jogador012");
    dados.jogador = (Vector2){300, 400};
    dados.score = 0;
    dados.vida = VIDA_MAXIMA;
    dados.fase = 1;

    int slotAtual = 1;
    float velocidade = 300;
    
    // Temporizador para controlar o dano da lava na Fase 3
    float temporizadorDano = 0.0f; 

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // =========================================
        // MOVIMENTO
        // =========================================

        if (IsKeyDown(KEY_D)) dados.jogador.x += velocidade * delta;
        if (IsKeyDown(KEY_A)) dados.jogador.x -= velocidade * delta;
        if (IsKeyDown(KEY_W)) dados.jogador.y -= velocidade * delta;
        if (IsKeyDown(KEY_S)) dados.jogador.y += velocidade * delta;

        // =========================================
        // AÇÕES E LIMITADORES
        // =========================================

        if (IsKeyPressed(KEY_P)) dados.score += 10;
        
        if (IsKeyPressed(KEY_V)) 
        {
            dados.vida -= 10;
            if (dados.vida < 0) dados.vida = 0;
        }

        if (IsKeyPressed(KEY_C)) 
        {
            dados.vida += 10;
            if (dados.vida > VIDA_MAXIMA) dados.vida = VIDA_MAXIMA;
        }

        if (IsKeyPressed(KEY_F)) 
        {
            if (dados.fase < FASE_MAXIMA) dados.fase += 1;
        }

        // Retorna fase para testes
        if (IsKeyPressed(KEY_R)) 
        {
            if (dados.fase > 1) dados.fase -= 1;
        }

        // =========================================
        // COLISÕES DO AMBIENTE (Lógica da Fase)
        // =========================================

        Rectangle rectJogador = { dados.jogador.x, dados.jogador.y, 50, 50 };

        if (dados.fase == 3)
        {
            // Define a área da Lava na Fase 3
            Rectangle areaLava = { 400, 300, 500, 150 };
            
            // Se o jogador pisar na lava, perde vida com o tempo
            if (CheckCollisionRecs(rectJogador, areaLava))
            {
                temporizadorDano += delta;
                if (temporizadorDano >= 0.5f) // A cada 0.5 segundos na lava
                {
                    dados.vida -= 5;
                    if (dados.vida < 0) dados.vida = 0;
                    temporizadorDano = 0.0f; // Reseta o timer
                }
            }
            else
            {
                temporizadorDano = 0.0f; // Reseta se sair da lava
            }
        }

        // =========================================
        // CONTROLE DE SLOTS E SAVE/LOAD
        // =========================================
        
        // Sistema de troca de slots com as setas (Ciclo)
        if (IsKeyPressed(KEY_RIGHT)) 
        {
            slotAtual++;
            if (slotAtual > TOTAL_SLOTS) slotAtual = 1;
        }
        
        if (IsKeyPressed(KEY_LEFT)) 
        {
            slotAtual--;
            if (slotAtual < 1) slotAtual = TOTAL_SLOTS;
        }

        // Mantidos os atalhos numéricos para praticidade
        if (IsKeyPressed(KEY_ONE)) slotAtual = 1;
        if (IsKeyPressed(KEY_TWO)) slotAtual = 2;
        if (IsKeyPressed(KEY_THREE)) slotAtual = 3;

        if (IsKeyPressed(KEY_Q)) SalvarJogo(dados, slotAtual);
        if (IsKeyPressed(KEY_L)) CarregarJogo(&dados, slotAtual);

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        // Escolhe a cor de fundo baseado na fase
        Color corFundo = RAYWHITE;
        if (dados.fase == 1) corFundo = GREEN;
        else if (dados.fase == 2) corFundo = BEIGE;
        else if (dados.fase == 3) corFundo = DARKGRAY;

        ClearBackground(corFundo);

        // =========================================
        // DESENHO DOS ELEMENTOS DA FASE
        // =========================================

        switch (dados.fase)
        {
            case 1:
                // FASE 1
                DrawCircle(200, 300, 40, LIME);
                DrawRectangle(190, 300, 20, 60, BROWN);

                DrawCircle(900, 500, 50, LIME);
                DrawRectangle(890, 500, 20, 70, BROWN);
                
                DrawCircle(400, 300, 20, DARKGREEN);
                DrawCircle(430, 300, 45, DARKGREEN);
                DrawCircle(420, 300, 50, DARKGREEN);
                
                DrawCircle(600, 700, 45, DARKGREEN);
                DrawCircle(630, 700, 50, DARKGREEN);
                DrawCircle(620, 700, 60, DARKGREEN);
                break;

            case 2:
                // FASE 2
                DrawRectangle(300, 300, 150, 80, DARKBROWN);
                DrawRectangle(700, 450, 100, 120, DARKBROWN);
                break;

            case 3:
                // FASE 3
                DrawRectangle(400, 300, 500, 150, ORANGE);
                DrawRectangle(500, 200, 50, 50, GRAY);
                DrawRectangle(300, 200, 50, 50, GRAY);
                DrawRectangle(500, 350, 50, 50, GRAY);
                DrawRectangle(700, 450, 50, 50, GRAY);
                DrawRectangle(100, 600, 50, 50, GRAY);
                break;
        }

        // =========================================
        // JOGADOR
        // =========================================
        
        DrawRectangleV(dados.jogador, (Vector2){50, 50}, BLUE);

        // =========================================
        // HUD PRINCIPAL
        // =========================================

        DrawRectangle(0, 0, 1200, 180, Fade(LIGHTGRAY, 0.9f));
        DrawLine(0, 180, 1200, 180, DARKGRAY);

        DrawText("Configurações do Jogo", 20, 20, 25, DARKBLUE);
        
        DrawText("WASD = mover   |   P = score", 20, 60, 20, DARKGRAY);
        DrawText("V = dano       |   C = curar", 20, 90, 20, DARKGRAY);
        DrawText("F = avançar    |   R = voltar fase", 20, 120, 20, DARKGRAY);
        DrawText("Q = Salvar     |   L = Carregar", 20, 150, 20, MAROON);

        DrawText(TextFormat("Nome: %s", dados.nome), 350, 60, 20, BLACK);
        DrawText(TextFormat("Score: %d", dados.score), 350, 90, 20, BLACK);
        
        Color corVida = (dados.vida > 30) ? DARKGREEN : RED;
        DrawText(TextFormat("Vida: %d / %d", dados.vida, VIDA_MAXIMA), 550, 60, 20, corVida);
        
        // Exibe o nome da fase
        char nomeFase[20];
        if (dados.fase == 1) strcpy(nomeFase, "Floresta");
        else if (dados.fase == 2) strcpy(nomeFase, "Deserto");
        else strcpy(nomeFase, "Vulcao");

        DrawText(TextFormat("Fase: %d (%s)", dados.fase, nomeFase), 550, 90, 20, ORANGE);

        // =========================================
        // INTERFACE VISUAL DE SLOTS
        // =========================================
        
        // Instrução visual do novo sistema
        DrawText("Use as setas para trocar de slot", 750, 5, 16, DARKBLUE);

        for (int i = 1; i <= TOTAL_SLOTS; i++)
        {
            // Caixas movidas um pouco mais para baixo (y=25 -> y=28) para não colidir com o texto
            Rectangle slotBox = { 750 + (i - 1) * 140, 28, 120, 130 };
            bool selecionado = (slotAtual == i);
            
            char nomeArquivo[32];
            sprintf(nomeArquivo, "save_slot_%d.txt", i);
            bool temSave = FileExists(nomeArquivo);

            Color corCaixa = selecionado ? Fade(SKYBLUE, 0.4f) : Fade(RAYWHITE, 0.8f);
            Color corBorda = selecionado ? BLUE : GRAY;

            DrawRectangleRec(slotBox, corCaixa);
            DrawRectangleLinesEx(slotBox, selecionado ? 4 : 2, corBorda);

            DrawText(TextFormat("SLOT %d", i), slotBox.x + 25, slotBox.y + 15, 20, selecionado ? DARKBLUE : DARKGRAY);
            
            if (temSave) 
            {
                DrawText("SALVO", slotBox.x + 30, slotBox.y + 60, 20, DARKGREEN);
                DrawText("Ocupado", slotBox.x + 25, slotBox.y + 90, 15, GRAY);
            } 
            else 
            {
                DrawText("VAZIO", slotBox.x + 30, slotBox.y + 60, 20, MAROON);
                DrawText("Livre", slotBox.x + 40, slotBox.y + 90, 15, GRAY);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
