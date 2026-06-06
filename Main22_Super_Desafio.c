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
#define MAX_INIMIGOS 3

// =========================================
// ESTRUTURAS DE DADOS
// =========================================

typedef enum {
    MENU_INICIAL,
    JOGANDO,
    MENU_PAUSA,
    TELA_MORTE
} EstadoJogo;

typedef struct SaveData
{
    char nome[50];                 // Nome do jogador
    Vector2 jogador;               // Posição do jogador
    Vector2 checkpoint;            // Posição de respawn (Checkpoint)
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

void InicializarNovoJogo(SaveData *dados)
{
    strcpy(dados->nome, "Aventureiro");
    dados->score = 0;
    dados->vida = VIDA_MAXIMA;
    dados->fase = 1;
    dados->moedas = 0;
    dados->checkpoint = (Vector2){300, 400};
    dados->jogador = dados->checkpoint;
    
    for (int i = 0; i < MAX_INVENTARIO; i++) dados->inventario[i] = 0;
    ResetarInimigos(dados);
}

void DefinirCheckpointDaFase(SaveData *dados)
{
    if (dados->fase == 1) dados->checkpoint = (Vector2){300, 400};
    else if (dados->fase == 2) dados->checkpoint = (Vector2){100, 300};
    else if (dados->fase == 3) dados->checkpoint = (Vector2){100, 200};
    
    dados->jogador = dados->checkpoint;
}

// =========================================
// SISTEMA DE SAVE E LOAD
// =========================================

void SalvarJogo(SaveData dados, int slot)
{
    char nomeArquivo[32];
    sprintf(nomeArquivo, "save_slot_%d.txt", slot);
    FILE *arquivo = fopen(nomeArquivo, "w");

    if (arquivo != NULL)
    {
        fprintf(arquivo, "%s\n", dados.nome);
        fprintf(arquivo, "%f %f\n", dados.jogador.x, dados.jogador.y);
        fprintf(arquivo, "%f %f\n", dados.checkpoint.x, dados.checkpoint.y);
        fprintf(arquivo, "%d %d %d %d\n", dados.score, dados.vida, dados.fase, dados.moedas);

        for (int i = 0; i < MAX_INVENTARIO; i++) fprintf(arquivo, "%d ", dados.inventario[i]);
        fprintf(arquivo, "\n");

        for (int i = 0; i < MAX_INIMIGOS; i++) 
            fprintf(arquivo, "%f %f %d\n", dados.inimigos[i].x, dados.inimigos[i].y, dados.inimigosVivos[i]);

        fclose(arquivo);
    }
}

bool CarregarJogo(SaveData *dados, int slot)
{
    char nomeArquivo[32];
    sprintf(nomeArquivo, "save_slot_%d.txt", slot);
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo != NULL)
    {
        fscanf(arquivo, "%49s", dados->nome);
        fscanf(arquivo, "%f %f", &dados->jogador.x, &dados->jogador.y);
        fscanf(arquivo, "%f %f", &dados->checkpoint.x, &dados->checkpoint.y);
        fscanf(arquivo, "%d %d %d %d", &dados->score, &dados->vida, &dados->fase, &dados->moedas);

        for (int i = 0; i < MAX_INVENTARIO; i++) fscanf(arquivo, "%d", &dados->inventario[i]);
        for (int i = 0; i < MAX_INIMIGOS; i++) 
            fscanf(arquivo, "%f %f %d", &dados->inimigos[i].x, &dados->inimigos[i].y, &dados->inimigosVivos[i]);

        fclose(arquivo);
        return true;
    }
    return false;
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    InitWindow(1200, 700, "Persistência Completa - Menus e Autosave");
    SetTargetFPS(60);

    SaveData dados;
    InicializarNovoJogo(&dados);

    EstadoJogo estado = MENU_INICIAL;
    int slotSelecionado = 1;
    float velocidade = 300;
    float temporizadorDano = 0.0f; 
    float timerAutosave = 0.0f; // Controla o tempo da mensagem "Auto-salvando"

    while (!WindowShouldClose())
    {
        float delta = GetFrameTime();

        // =========================================
        // MÁQUINA DE ESTADOS (LÓGICA)
        // =========================================

        if (estado == MENU_INICIAL || estado == MENU_PAUSA)
        {
            // Navegação entre os slots
            if (IsKeyPressed(KEY_RIGHT)) { slotSelecionado++; if (slotSelecionado > TOTAL_SLOTS) slotSelecionado = 1; }
            if (IsKeyPressed(KEY_LEFT)) { slotSelecionado--; if (slotSelecionado < 1) slotSelecionado = TOTAL_SLOTS; }

            // Ações de Carregar/Salvar/Novo Jogo
            if (estado == MENU_INICIAL)
            {
                if (IsKeyPressed(KEY_ENTER))
                {
                    if (!CarregarJogo(&dados, slotSelecionado)) 
                    {
                        InicializarNovoJogo(&dados);
                        SalvarJogo(dados, slotSelecionado); // Cria o save se não existir
                    }
                    estado = JOGANDO;
                }
            }
            else if (estado == MENU_PAUSA)
            {
                if (IsKeyPressed(KEY_TAB)) estado = JOGANDO;
                if (IsKeyPressed(KEY_Q)) SalvarJogo(dados, slotSelecionado);
                if (IsKeyPressed(KEY_L)) CarregarJogo(&dados, slotSelecionado);
            }
        }
        else if (estado == TELA_MORTE)
        {
            if (IsKeyPressed(KEY_ENTER))
            {
                dados.vida = VIDA_MAXIMA;
                dados.jogador = dados.checkpoint; // Renasce no Checkpoint
                estado = JOGANDO;
            }
        }
        else if (estado == JOGANDO)
        {
            // Pausar jogo
            if (IsKeyPressed(KEY_TAB)) estado = MENU_PAUSA;

            // Movimento
            if (IsKeyDown(KEY_D)) dados.jogador.x += velocidade * delta;
            if (IsKeyDown(KEY_A)) dados.jogador.x -= velocidade * delta;
            if (IsKeyDown(KEY_W)) dados.jogador.y -= velocidade * delta;
            if (IsKeyDown(KEY_S)) dados.jogador.y += velocidade * delta;

            // Ações
            if (IsKeyPressed(KEY_P)) dados.score += 10;
            if (IsKeyPressed(KEY_M)) dados.moedas += 5; 
            
            if (IsKeyPressed(KEY_I)) 
            {
                for (int i = 0; i < MAX_INVENTARIO; i++) {
                    if (dados.inventario[i] == 0) { dados.inventario[i] = 1; break; }
                }
            }
            if (IsKeyPressed(KEY_V)) dados.vida -= 10;
            if (IsKeyPressed(KEY_C)) { dados.vida += 10; if (dados.vida > VIDA_MAXIMA) dados.vida = VIDA_MAXIMA; }

            // Lógica de Morte (Checkpoint Trigger)
            if (dados.vida <= 0) estado = TELA_MORTE;

            // Avançar/Voltar Fase + AUTOSAVE
            bool trocouFase = false;
            if (IsKeyPressed(KEY_F) && dados.fase < FASE_MAXIMA) 
            {
                dados.fase++; trocouFase = true;
            }
            if (IsKeyPressed(KEY_R) && dados.fase > 1) 
            {
                dados.fase--; trocouFase = true;
            }

            if (trocouFase)
            {
                ResetarInimigos(&dados);
                DefinirCheckpointDaFase(&dados);
                SalvarJogo(dados, slotSelecionado); // AUTOSAVE
                timerAutosave = 2.0f; // Exibe a mensagem por 2 segundos
            }

            // Colisões com ambiente
            Rectangle rectJogador = { dados.jogador.x, dados.jogador.y, 50, 50 };

            if (dados.fase == 3)
            {
                Rectangle areaLava = { 400, 300, 500, 150 };
                if (CheckCollisionRecs(rectJogador, areaLava))
                {
                    temporizadorDano += delta;
                    if (temporizadorDano >= 0.5f) { dados.vida -= 5; temporizadorDano = 0.0f; }
                }
                else temporizadorDano = 0.0f;
            }

            // Colisões Inimigos
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
            
            // Timer do Autosave (reduz com o tempo)
            if (timerAutosave > 0) timerAutosave -= delta;
        }

        // =========================================
        // DRAW (RENDERIZAÇÃO)
        // =========================================

        BeginDrawing();

        // 1. DESENHA O JOGO EM FUNDO (Se não estiver no Menu Inicial)
        if (estado != MENU_INICIAL)
        {
            Color corFundo = RAYWHITE;
            if (dados.fase == 1) corFundo = GREEN;
            else if (dados.fase == 2) corFundo = BEIGE;
            else if (dados.fase == 3) corFundo = DARKGRAY;

            ClearBackground(corFundo);

            // Desenha Fase
            switch (dados.fase)
            {
                case 1:
                    DrawCircle(200, 300, 40, LIME); DrawRectangle(190, 300, 20, 60, BROWN);
                    DrawCircle(900, 500, 50, LIME); DrawRectangle(890, 500, 20, 70, BROWN);
                    break;
                case 2:
                    DrawRectangle(300, 300, 150, 80, DARKBROWN); DrawRectangle(700, 450, 100, 120, DARKBROWN);
                    break;
                case 3:
                    DrawRectangle(400, 300, 500, 150, ORANGE); DrawRectangle(500, 200, 50, 50, GRAY);
                    break;
            }

            // Desenha Inimigos e Jogador
            for (int i = 0; i < MAX_INIMIGOS; i++)
                if (dados.inimigosVivos[i] == 1) DrawRectangleV(dados.inimigos[i], (Vector2){40, 40}, RED);

            DrawRectangleV(dados.jogador, (Vector2){50, 50}, BLUE);

            // =========================================
            // HUD PRINCIPAL (Durante Jogo)
            // =========================================
            if (estado == JOGANDO || estado == TELA_MORTE)
            {
                DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.9f));
                DrawLine(0, 120, 1200, 120, DARKGRAY);

                DrawText("WASD: Move | P: Score | M: Moeda | I: Item | V: Dano | C: Cura | F/R: Fases | TAB: Menu Save", 20, 15, 18, DARKGRAY);
                
                DrawText(TextFormat("Score: %d | Moedas: %d", dados.score, dados.moedas), 20, 50, 20, BLACK);
                
                Color corVida = (dados.vida > 30) ? DARKGREEN : RED;
                DrawText(TextFormat("Vida: %d / %d", dados.vida, VIDA_MAXIMA), 20, 80, 20, corVida);
                DrawText(TextFormat("Fase: %d", dados.fase), 400, 50, 20, ORANGE);

                // Inventário Simplificado na HUD
                DrawText("Inventário:", 600, 50, 20, BLACK);
                for (int i = 0; i < MAX_INVENTARIO; i++)
                {
                    Rectangle slotInv = { 720 + (i * 45), 45, 30, 30 };
                    DrawRectangleLinesEx(slotInv, 2, DARKGRAY);
                    if (dados.inventario[i] == 1) DrawRectangle(slotInv.x + 4, slotInv.y + 4, 22, 22, LIME);
                }

                // Notificação de Autosave
                if (timerAutosave > 0)
                {
                    DrawText("Auto-salvando...", 1000, 50, 20, DARKGREEN);
                }
            }
        }
        else 
        {
            ClearBackground(DARKBLUE); // Fundo do Menu Inicial
        }

        // =========================================
        // SOBREPOSIÇÕES: MENUS E TELAS
        // =========================================

        if (estado == MENU_INICIAL || estado == MENU_PAUSA)
        {
            if (estado == MENU_PAUSA) DrawRectangle(0, 0, 1200, 700, Fade(BLACK, 0.7f));

            const char* titulo = (estado == MENU_INICIAL) ? "TELA INICIAL" : "MENU DE PAUSA";
            DrawText(titulo, 450, 150, 40, RAYWHITE);
            DrawText("Use <- e -> para escolher o Slot", 420, 220, 20, LIGHTGRAY);

            if (estado == MENU_INICIAL) DrawText("Pressione ENTER para Jogar", 430, 500, 25, GREEN);
            else DrawText("Q: Salvar | L: Carregar | TAB: Voltar", 400, 500, 25, YELLOW);

            // Renderiza os Caixas de Slot
            for (int i = 1; i <= TOTAL_SLOTS; i++)
            {
                Rectangle slotBox = { 350 + (i - 1) * 180, 280, 140, 180 };
                bool selecionado = (slotSelecionado == i);
                
                char nomeArq[32];
                sprintf(nomeArq, "save_slot_%d.txt", i);
                bool temSave = FileExists(nomeArq);

                DrawRectangleRec(slotBox, selecionado ? SKYBLUE : RAYWHITE);
                DrawRectangleLinesEx(slotBox, selecionado ? 5 : 2, selecionado ? BLUE : GRAY);

                DrawText(TextFormat("SLOT %d", i), slotBox.x + 30, slotBox.y + 20, 20, DARKGRAY);
                DrawText(temSave ? "DADOS\nSALVOS" : "VAZIO", slotBox.x + 30, slotBox.y + 80, 20, temSave ? DARKGREEN : MAROON);
            }
        }
        else if (estado == TELA_MORTE)
        {
            DrawRectangle(0, 0, 1200, 700, Fade(BLACK, 0.8f));
            DrawText("VOCÊ MORREU!", 400, 250, 50, RED);
            DrawText("Pressione ENTER para voltar ao último Checkpoint", 280, 350, 25, LIGHTGRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
