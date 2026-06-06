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
#define MAX_INVENTARIO 5
#define MAX_INIMIGOS 3 // isso em cada fase

// =========================================
// STRUCT SAVE DATA
// =========================================

typedef struct SaveData
{
    char nome[50];                 // Nome do jogador
    Vector2 jogador;               // Posição do jogador
    int score;                     // Score
    int vida;                      // Vida do jogador 
    int fase;                      // Fase atual do jogo 
    int moedas;                    // Quantidade de moedas
    int inventario[MAX_INVENTARIO];// Array do inventário (0 = vazio, 1 = item)
    Vector2 inimigos[MAX_INIMIGOS];// Posição dos inimigos
    int inimigosVivos[MAX_INIMIGOS];// Status dos inimigos (1 = vivo, 0 = morto)
} SaveData;

// =========================================
// FUNÇÕES DE INICIALIZAÇÃO E UTILIDADE
// =========================================

void ResetarInimigos(SaveData *dados)
{
    for (int i = 0; i < MAX_INIMIGOS; i++)
    {
        dados->inimigosVivos[i] = 1;
        
        if (dados->fase == 1)
            dados->inimigos[i] = (Vector2){ 500 + (i * 150), 400 + (i * 50) };
        else if (dados->fase == 2)
            dados->inimigos[i] = (Vector2){ 300 + (i * 200), 550 };
        else
            dados->inimigos[i] = (Vector2){ 200 + (i * 250), 500 - (i * 50) };
    }
}

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
        fprintf(arquivo, "%d\n", dados.moedas);

        for (int i = 0; i < MAX_INVENTARIO; i++) 
            fprintf(arquivo, "%d ", dados.inventario[i]);
        fprintf(arquivo, "\n");

        for (int i = 0; i < MAX_INIMIGOS; i++) 
            fprintf(arquivo, "%f %f %d\n", dados.inimigos[i].x, dados.inimigos[i].y, dados.inimigosVivos[i]);

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
        fscanf(arquivo, "%d", &dados->moedas);

        for (int i = 0; i < MAX_INVENTARIO; i++) 
            fscanf(arquivo, "%d", &dados->inventario[i]);

        for (int i = 0; i < MAX_INIMIGOS; i++) 
            fscanf(arquivo, "%f %f %d", &dados->inimigos[i].x, &dados->inimigos[i].y, &dados->inimigosVivos[i]);

        fclose(arquivo);
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    InitWindow(1200, 700, "Save System - HUD");
    SetTargetFPS(60);

    SaveData dados;
    strcpy(dados.nome, "Jogador012");
    dados.jogador = (Vector2){300, 400};
    dados.score = 0;
    dados.vida = VIDA_MAXIMA;
    dados.fase = 1;
    dados.moedas = 0;
    
    for (int i = 0; i < MAX_INVENTARIO; i++) dados.inventario[i] = 0;
    ResetarInimigos(&dados);

    int slotAtual = 1;
    float velocidade = 300;
    float temporizadorDano = 0.0f; 

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // =========================================
        // MOVIMENTO E AÇÕES
        // =========================================

        if (IsKeyDown(KEY_D)) dados.jogador.x += velocidade * delta;
        if (IsKeyDown(KEY_A)) dados.jogador.x -= velocidade * delta;
        if (IsKeyDown(KEY_W)) dados.jogador.y -= velocidade * delta;
        if (IsKeyDown(KEY_S)) dados.jogador.y += velocidade * delta;

        if (IsKeyPressed(KEY_P)) dados.score += 10;
        if (IsKeyPressed(KEY_M)) dados.moedas += 5; 
        
        if (IsKeyPressed(KEY_I)) 
        {
            for (int i = 0; i < MAX_INVENTARIO; i++)
            {
                if (dados.inventario[i] == 0)
                {
                    dados.inventario[i] = 1; 
                    break;
                }
            }
        }

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
            if (dados.fase < FASE_MAXIMA) 
            {
                dados.fase += 1;
                ResetarInimigos(&dados);
            }
        }

        if (IsKeyPressed(KEY_R)) 
        {
            if (dados.fase > 1) 
            {
                dados.fase -= 1;
                ResetarInimigos(&dados);
            }
        }

        // =========================================
        // COLISÕES
        // =========================================

        Rectangle rectJogador = { dados.jogador.x, dados.jogador.y, 50, 50 };

        if (dados.fase == 3)
        {
            Rectangle areaLava = { 400, 300, 500, 150 };
            if (CheckCollisionRecs(rectJogador, areaLava))
            {
                temporizadorDano += delta;
                if (temporizadorDano >= 0.5f)
                {
                    dados.vida -= 5;
                    if (dados.vida < 0) dados.vida = 0;
                    temporizadorDano = 0.0f;
                }
            }
            else temporizadorDano = 0.0f;
        }

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {
            if (dados.inimigosVivos[i] == 1)
            {
                Rectangle rectInimigo = { dados.inimigos[i].x, dados.inimigos[i].y, 40, 40 };
                
                if (CheckCollisionRecs(rectJogador, rectInimigo))
                {
                    dados.inimigosVivos[i] = 0;
                    dados.score += 50;
                    dados.moedas += 10;
                }
            }
        }

        // =========================================
        // SLOTS E SAVE/LOAD
        // =========================================
        
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

        if (IsKeyPressed(KEY_ONE)) slotAtual = 1;
        if (IsKeyPressed(KEY_TWO)) slotAtual = 2;
        if (IsKeyPressed(KEY_THREE)) slotAtual = 3;

        if (IsKeyPressed(KEY_Q)) SalvarJogo(dados, slotAtual);
        if (IsKeyPressed(KEY_L)) CarregarJogo(&dados, slotAtual);

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        Color corFundo = RAYWHITE;
        if (dados.fase == 1) corFundo = GREEN;
        else if (dados.fase == 2) corFundo = BEIGE;
        else if (dados.fase == 3) corFundo = DARKGRAY;

        ClearBackground(corFundo);

        switch (dados.fase)
        {
            case 1:
                DrawCircle(200, 300, 40, LIME);
                DrawRectangle(190, 300, 20, 60, BROWN);
                DrawCircle(900, 500, 50, LIME);
                DrawRectangle(890, 500, 20, 70, BROWN);
                break;
            case 2:
                DrawRectangle(300, 300, 150, 80, DARKBROWN);
                DrawRectangle(700, 450, 100, 120, DARKBROWN);
                break;
            case 3:
                DrawRectangle(400, 300, 500, 150, ORANGE);
                DrawRectangle(500, 200, 50, 50, GRAY);
                break;
        }

        for (int i = 0; i < MAX_INIMIGOS; i++)
        {
            if (dados.inimigosVivos[i] == 1)
            {
                DrawRectangleV(dados.inimigos[i], (Vector2){40, 40}, RED);
                DrawText("Mal", dados.inimigos[i].x + 5, dados.inimigos[i].y - 15, 15, DARKGRAY);
            }
        }

        DrawRectangleV(dados.jogador, (Vector2){50, 50}, BLUE);

        // =========================================
        // HUD PRINCIPAL - ESPAÇADA
        // =========================================

        // Área aumentada (Y vai até 260 agora)
        DrawRectangle(0, 0, 1200, 260, Fade(LIGHTGRAY, 0.9f));
        DrawLine(0, 260, 1200, 260, DARKGRAY);

        // --- COLUNA 1: CONTROLES ---
        DrawText("Configurações do Jogo", 30, 20, 25, DARKBLUE);
        DrawText("WASD = Mover    | P = Score  | M = Moeda", 30, 70, 20, DARKGRAY);
        DrawText("V = Tomar Dano  | C = Curar  | I = Pegar Item", 30, 110, 20, DARKGRAY);
        DrawText("F = Avançar     | R = Voltar Fase", 30, 150, 20, DARKGRAY);
        DrawText("Q = Salvar      | L = Carregar", 30, 200, 20, MAROON);

        // --- COLUNA 2: STATUS E INVENTÁRIO ---
        DrawText(TextFormat("Nome: %s", dados.nome), 480, 70, 20, BLACK);
        DrawText(TextFormat("Score: %d", dados.score), 480, 110, 20, BLACK);
        DrawText(TextFormat("Moedas: %d", dados.moedas), 480, 150, 20, GOLD);
        
        Color corVida = (dados.vida > 30) ? DARKGREEN : RED;
        DrawText(TextFormat("Vida: %d / %d", dados.vida, VIDA_MAXIMA), 680, 70, 20, corVida);
        
        char nomeFase[20];
        if (dados.fase == 1) strcpy(nomeFase, "Floresta");
        else if (dados.fase == 2) strcpy(nomeFase, "Deserto");
        else strcpy(nomeFase, "Vulcao");
        DrawText(TextFormat("Fase: %d (%s)", dados.fase, nomeFase), 680, 110, 20, ORANGE);

        // Inventário centralizado abaixo do status
        DrawText("Inventário:", 480, 205, 20, BLACK);
        for (int i = 0; i < MAX_INVENTARIO; i++)
        {
            Rectangle slotInv = { 600 + (i * 50), 195, 40, 40 };
            DrawRectangleLinesEx(slotInv, 2, DARKGRAY);
            
            if (dados.inventario[i] == 1) 
            {
                DrawRectangle(slotInv.x + 5, slotInv.y + 5, 30, 30, LIME);
            }
        }

        // --- COLUNA 3: SLOTS DE SAVE ---
        DrawText("Use <- e -> para trocar o slot", 860, 20, 18, DARKBLUE);

        for (int i = 1; i <= TOTAL_SLOTS; i++)
        {
            // Caixas de slot maiores e mais espaçadas
            Rectangle slotBox = { 860 + (i - 1) * 110, 60, 100, 150 };
            bool selecionado = (slotAtual == i);
            
            char nomeArquivo[32];
            sprintf(nomeArquivo, "save_slot_%d.txt", i);
            bool temSave = FileExists(nomeArquivo);

            Color corCaixa = selecionado ? Fade(SKYBLUE, 0.4f) : Fade(RAYWHITE, 0.8f);
            Color corBorda = selecionado ? BLUE : GRAY;

            DrawRectangleRec(slotBox, corCaixa);
            DrawRectangleLinesEx(slotBox, selecionado ? 4 : 2, corBorda);

            DrawText(TextFormat("SLOT %d", i), slotBox.x + 15, slotBox.y + 20, 20, selecionado ? DARKBLUE : DARKGRAY);
            
            if (temSave) 
                DrawText("SALVO", slotBox.x + 20, slotBox.y + 70, 18, DARKGREEN);
            else 
                DrawText("VAZIO", slotBox.x + 25, slotBox.y + 70, 18, MAROON);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
