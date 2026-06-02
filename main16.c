// Atividade de Aula:

#include "raylib.h"

#define MAX_PARTICULAS 300

typedef struct Particula
{
    // Posição da partícula
    Vector2 posicao;

    // Velocidade da partícula
    Vector2 velocidade;

    // Tamanho da partícula
    float tamanho;

    // Tempo de vida da partícula
    float tempoVida;

    // Indica se a partícula está ativa
    bool ativa;

    // Cor da partícula
    Color cor;

} Particula;


// FUNÇÃO PARA CRIAR EXPLOSÃO


void CriarExplosao(Particula particulas[], Vector2 origem)
{
    // Percorre todas as partículas disponíveis
    for (int i = 0; i < MAX_PARTICULAS; i++)
    {
        // Ativa somente partículas livres
        if (!particulas[i].ativa)
        {
            // Ativa a partícula
            particulas[i].ativa = true;

            // Define origem da partícula
            particulas[i].posicao = origem;

            // Define velocidade aleatória em X
            particulas[i].velocidade.x = GetRandomValue(-450, 450) / 100.0f;

            // Define velocidade aleatória em Y
            particulas[i].velocidade.y = GetRandomValue(-450, 450) / 100.0f;

            // Define tamanho aleatório
            particulas[i].tamanho = GetRandomValue(2, 4);

            // Define tempo de vida
            particulas[i].tempoVida = 3.0f;

            // Define cor
          particulas[i].cor = RED;
        }
    }
}

// MAIN

int main(void)
{
    // Cria janela
    InitWindow(1000, 600, "Particulas em Raylib");

    // Define FPS
    SetTargetFPS(60);

    // Cria vetor de partículas
    Particula particulas[MAX_PARTICULAS] = { 0 };

    // Posição inicial da explosão
    Vector2 origem = { 500, 300 };

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        // Captura delta time
        float delta = GetFrameTime();

        // Se apertar ESPAÇO, cria explosão
        if (IsKeyPressed(KEY_SPACE))
        {
            CriarExplosao(particulas, origem);
        }

        // Move origem com o mouse
        origem = GetMousePosition();

        // Atualiza partículas
        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            // Só atualiza partículas ativas
            if (particulas[i].ativa)
            {
                // Move partícula no eixo X
                particulas[i].posicao.x += particulas[i].velocidade.x * 100 * delta;

                // Move partícula no eixo Y
                particulas[i].posicao.y += particulas[i].velocidade.y * 100 * delta;

                // Reduz tempo de vida
                particulas[i].tempoVida -= delta;

                // Reduz tamanho aos poucos
                particulas[i].tamanho -= delta * 3;

                // Se acabou o tempo de vida
                if (particulas[i].tempoVida <= 0 || particulas[i].tamanho <= 0)
                {
                    // Desativa partícula
                    particulas[i].ativa = false;
                }
            }
        }
        
        // DRAW
      
        BeginDrawing();

        // Fundo
        ClearBackground(RAYWHITE);

        // Título
        DrawText(
            "Sistema de Particulas",
            20,
            20,
            30,
            DARKBLUE
        );

        // Instrução
        DrawText(
            "Mova o mouse e pressione ESPACO para criar explosao",
            20,
            60,
            20,
            DARKGRAY
        );

        // Desenha origem
        DrawCircleV(
            origem,
            8,
            RED
        );

        // Desenha partículas
        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            // Só desenha partículas ativas
            if (particulas[i].ativa)
            {
                DrawCircleV(
                    particulas[i].posicao,
                    particulas[i].tamanho,
                    particulas[i].cor
                );
            }
        }

        // Texto inferior
        DrawText(
            "Particulas = posicao + velocidade + tempo de vida",
            20,
            560,
            18,
            MAROON
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}


// Desafio Extra:

#include "raylib.h"

#define MAX_PARTICULAS 300

typedef struct Particula
{
    // Posição da partícula
    Vector2 posicao;

    // Velocidade da partícula
    Vector2 velocidade;

    // Tamanho da partícula
    float tamanho;

    // Tempo de vida da partícula
    float tempoVida;

    // Indica se a partícula está ativa
    bool ativa;

    // Cor da partícula
    Color cor;

} Particula;


// FUNÇÃO PARA CRIAR EXPLOSÃO


void CriarExplosao(Particula particulas[], Vector2 origem)
{
    // Percorre todas as partículas disponíveis
    for (int i = 0; i < MAX_PARTICULAS; i++)
    {
        // Ativa somente partículas livres
        if (!particulas[i].ativa)
        {
            // Ativa a partícula
            particulas[i].ativa = true;

            // Define origem da partícula
            particulas[i].posicao = origem;

            // Define velocidade aleatória em X
            particulas[i].velocidade.x = GetRandomValue(-450, 450) / 100.0f;

            // Define velocidade aleatória em Y
            particulas[i].velocidade.y = GetRandomValue(-450, 450) / 100.0f;

            // Define tamanho aleatório
            particulas[i].tamanho = GetRandomValue(2, 4);

            // Define tempo de vida
            particulas[i].tempoVida = 3.0f;

            // Define cor
            particulas[i].cor = (Color){
                
                GetRandomValue(300, 500),
                GetRandomValue(90,190),
                0,
                250
                
                 
            };
        }
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1000, 600, "Particulas em Raylib");

    // Define FPS
    SetTargetFPS(60);

    // Cria vetor de partículas
    Particula particulas[MAX_PARTICULAS] = { 0 };

    // Posição inicial da explosão
    Vector2 origem = { 500, 300 };

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        // Captura delta time
        float delta = GetFrameTime();

        // Se apertar ESPAÇO, cria explosão
        if (IsKeyPressed(KEY_SPACE))
        {
            CriarExplosao(particulas, origem);
        }

        // Move origem com o mouse
        origem = GetMousePosition();

        // Atualiza partículas
        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            // Só atualiza partículas ativas
            if (particulas[i].ativa)
            {
                // Move partícula no eixo X
                particulas[i].posicao.x += particulas[i].velocidade.x * 100 * delta;

                // Move partícula no eixo Y
                particulas[i].posicao.y += particulas[i].velocidade.y * 100 * delta;

                // Reduz tempo de vida
                particulas[i].tempoVida -= delta;

                // Reduz tamanho aos poucos
                particulas[i].tamanho -= delta * 3;

                // Se acabou o tempo de vida
                if (particulas[i].tempoVida <= 0 || particulas[i].tamanho <= 0)
                {
                    // Desativa partícula
                    particulas[i].ativa = false;
                }
            }
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        // Fundo
        ClearBackground(RAYWHITE);

        // Título
        DrawText(
            "Sistema de Particulas",
            20,
            20,
            30,
            DARKBLUE
        );

        // Instrução
        DrawText(
            "Mova o mouse e pressione ESPACO para criar explosao",
            20,
            60,
            20,
            DARKGRAY
        );

        // Desenha origem
        DrawCircleV(
            origem,
            8,
            RED
        );

        // Desenha partículas
        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            // Só desenha partículas ativas
            if (particulas[i].ativa)
            {
                DrawCircleV(
                    particulas[i].posicao,
                    particulas[i].tamanho,
                    particulas[i].cor
                );
            }
        }

        // Texto inferior
        DrawText(
            "Particulas = posicao + velocidade + tempo de vida",
            20,
            560,
            18,
            MAROON
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}

// Super Desafio: 

#include "raylib.h"

#define MAX_PARTICULAS 300

typedef struct Particula
{
    Vector2 posicao;
    Vector2 velocidade;
    float tamanho;
    float tempoVida;
    bool ativa;
    Color cor;
} Particula;


void CriarExplosao(Particula particulas[], Vector2 origem)
{
    for (int i = 0; i < MAX_PARTICULAS; i++)
    {
        if (!particulas[i].ativa)
        {
            particulas[i].ativa = true;
            particulas[i].posicao = origem;
            particulas[i].velocidade.x = GetRandomValue(-200, 200) / 100.0f;
            particulas[i].velocidade.y = GetRandomValue(-200, 200) / 100.0f;
            particulas[i].tamanho = GetRandomValue(3, 6);
            particulas[i].tempoVida = 2.5f;
            particulas[i].cor = ORANGE;
        }
    }
}

void CriarFumaca(Particula particulas[], Vector2 origem)
{
    // Ativa apenas algumas partículas por vez para poder misturar os efeitos
    int ativadas = 0;
    for (int i = 0; i < MAX_PARTICULAS && ativadas < 50; i++)
    {
        if (!particulas[i].ativa)
        {
            particulas[i].ativa = true;
            particulas[i].posicao = origem;
            particulas[i].velocidade.x = GetRandomValue(-250, 250) / 100.0f;
            particulas[i].velocidade.y = GetRandomValue(-250, 250) / 100.0f; 
            particulas[i].tamanho = GetRandomValue(4, 8);
            particulas[i].tempoVida = 10.0f;
            particulas[i].cor = GRAY;
            ativadas++;
        }
    }
}

void CriarMagia(Particula particulas[], Vector2 origem)
{
    int ativadas = 0;
    for (int i = 0; i < MAX_PARTICULAS && ativadas < 40; i++)
    {
        if (!particulas[i].ativa)
        {
            particulas[i].ativa = true;
            particulas[i].posicao = origem;
            particulas[i].velocidade.x = GetRandomValue(-150, 150) / 100.0f;
            particulas[i].velocidade.y = GetRandomValue(-150, 150) / 100.0f; 
            particulas[i].tamanho = GetRandomValue(2, 5);                   
            particulas[i].tempoVida = 3.0f;
            particulas[i].cor = PURPLE;
            ativadas++;
        }
    }
}

void CriarGelo(Particula particulas[], Vector2 origem)
{
    int ativadas = 0;
    for (int i = 0; i < MAX_PARTICULAS && ativadas < 40; i++)
    {
        if (!particulas[i].ativa)
        {
            particulas[i].ativa = true;
            particulas[i].posicao = origem;
            particulas[i].velocidade.x = GetRandomValue(-165, 165) / 100.0f;
            particulas[i].velocidade.y = GetRandomValue(-165, 165) / 100.0f; 
            particulas[i].tamanho = GetRandomValue(2, 4); 
            
            particulas[i].tempoVida = 15.0f;
            particulas[i].cor = BLUE;
            ativadas++;
        }
    }
}

void CriarMoedas(Particula particulas[], Vector2 origem)
{
    int ativadas = 0;
    for (int i = 0; i < MAX_PARTICULAS && ativadas < 20; i++)
    {
        if (!particulas[i].ativa)
        {
            particulas[i].ativa = true;
            particulas[i].posicao = origem;
            particulas[i].velocidade.x = GetRandomValue(-140, 140) / 100.0f;
            particulas[i].velocidade.y = GetRandomValue(-140, 140) / 100.0f; // Corrigido .y
            particulas[i].tamanho = GetRandomValue(3, 5);  
            particulas[i].tempoVida = 10.0f;
            particulas[i].cor = YELLOW;
            ativadas++;
        }
    }
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    InitWindow(1000, 600, "Particulas distintas");
    SetTargetFPS(60);

    InitAudioDevice();
    Sound soundExplosao = LoadSound("explosao.mp3");
    Sound soundFumaca = LoadSound("fumaca.mp3");
    Sound soundMagia = LoadSound("magia.mp3");
    Sound soundGelo = LoadSound("gelo.mp3");
    Sound soundMoeda = LoadSound("moedas.mp3");

    Particula particulas[MAX_PARTICULAS] = { 0 };
    Vector2 origem = { 500, 300 };

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================
        float delta = GetFrameTime();

        if (IsKeyPressed(KEY_SPACE)) {
            PlaySound(soundExplosao);
            CriarExplosao(particulas, origem);
        }
        if (IsKeyPressed(KEY_F)) {
            PlaySound(soundFumaca);
            CriarFumaca(particulas, origem);
        }
        if (IsKeyPressed(KEY_M)) {
            PlaySound(soundMagia);
            CriarMagia(particulas, origem);
        }
        if (IsKeyPressed(KEY_G)) {
            PlaySound(soundGelo);
            CriarGelo(particulas, origem);
        }
        if (IsKeyPressed(KEY_C)) {
            PlaySound(soundMoeda);
            CriarMoedas(particulas, origem);
        }

        origem = GetMousePosition();

        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            if (particulas[i].ativa)
            {
                particulas[i].posicao.x += particulas[i].velocidade.x * 100 * delta;
                particulas[i].posicao.y += particulas[i].velocidade.y * 100 * delta;
                particulas[i].tempoVida -= delta;
                particulas[i].tamanho -= delta * 3;

                if (particulas[i].tempoVida <= 0 || particulas[i].tamanho <= 0)
                {
                    particulas[i].ativa = false;
                }
            }
        }

        // =========================================
        // DRAW
        // =========================================
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Sistema de Particulas", 20, 20, 30, DARKBLUE);
        DrawText("Mova o mouse e pressione: ESPACO (Explosao) | F (Fumaca) | M (Magia) | G (Gelo) | C (Moedas)", 20, 60, 16, DARKGRAY);

        DrawCircleV(origem, 8, RED);

        for (int i = 0; i < MAX_PARTICULAS; i++)
        {
            if (particulas[i].ativa)
            {
                DrawCircleV(particulas[i].posicao, particulas[i].tamanho, particulas[i].cor);
            }
        }

        DrawText("Particulas = posicao + velocidade + tempo de vida", 20, 560, 18, MAROON);
        EndDrawing();
    }

    // DESCARREGAR ARQUIVOS E FECHAR
    UnloadSound(soundExplosao);
    UnloadSound(soundFumaca);
    UnloadSound(soundMagia);
    UnloadSound(soundGelo);
    UnloadSound(soundMoeda);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
