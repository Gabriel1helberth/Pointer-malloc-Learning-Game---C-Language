// IMPORTA RAYLIB
#include "raylib.h"

// CONSTANTES

// Quantidade de colunas
#define MAP_WIDTH 25

// Quantidade de linhas
#define MAP_HEIGHT 15

// Tamanho de cada tile
#define TILE_SIZE 64

// MAIN
int main(void)
{
    // Cria janela
    InitWindow(
        MAP_WIDTH * TILE_SIZE,
        MAP_HEIGHT * TILE_SIZE,
        "Tilemap em Raylib - Texturas e Jogador Quadrado"
    );

    // Define FPS
    SetTargetFPS(60);

    // TEXTURAS (Carrega as imagens reais da pasta do projeto)
    Texture2D texParede = LoadTexture("parede.png");
    Texture2D texGrama  = LoadTexture("grama.png");
    Texture2D texAgua   = LoadTexture("agua.png");
    Texture2D texLava   = LoadTexture("lava.png");
    Texture2D texVazio  = LoadTexture("pedra.png");

    // MAPA

    // Matriz do mapa (25x15)
    // 0 = Pedra, 1 = Parede, 2 = Grama, 3 = Água, 4 = Lava
    int mapa[MAP_HEIGHT][MAP_WIDTH] =
    {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,0,3,3,1,0,0,4,4,4,0,0,0,0,0,0,0,0,0,1},
        {1,0,2,2,2,0,0,3,3,1,0,0,4,4,4,4,0,0,0,0,0,0,0,0,1},
        {1,0,0,2,2,2,0,0,0,1,1,1,1,1,0,0,0,0,2,2,2,0,0,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,2,2,2,2,0,0,0,1},
        {1,0,0,3,3,0,0,0,0,0,0,0,0,1,0,0,0,0,2,2,0,0,0,0,1},
        {1,0,0,3,3,3,0,0,4,4,4,0,0,1,0,0,0,0,0,0,0,3,3,0,1},
        {1,0,0,0,3,3,0,0,4,4,4,0,0,1,0,0,0,0,0,0,0,3,3,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,1},
        {1,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,1},
        {1,0,0,0,0,2,2,2,2,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,1},
        {1,0,2,2,2,2,2,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,1},
        {1,3,3,3,3,3,3,3,3,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
    };

    // JOGADOR
    Vector2 jogador = { 100, 100 };
    float velocidade = 175;

    // LOOP PRINCIPAL
    while (!WindowShouldClose())
    {
        // UPDATE
        float delta = GetFrameTime();

        // Guarda posição antiga
        Vector2 antigaPosicao = jogador;

        // Movimento
        if (IsKeyDown(KEY_D)) jogador.x += velocidade * delta;
        if (IsKeyDown(KEY_A)) jogador.x -= velocidade * delta;
        if (IsKeyDown(KEY_W)) jogador.y -= velocidade * delta;
        if (IsKeyDown(KEY_S)) jogador.y += velocidade * delta;

        // COLISÃO COM TILES
        int coluna = jogador.x / TILE_SIZE;
        int linha = jogador.y / TILE_SIZE;

        // Verifica limites
        if (linha >= 0 && linha < MAP_HEIGHT && coluna >= 0 && coluna < MAP_WIDTH)
        {
            // Tile sólido (Neste caso, apenas o 1/Parede impede o movimento)
            if (mapa[linha][coluna] == 1)
            {
                // Volta posição antiga
                jogador = antigaPosicao;
            }
        }

        // DRAW
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // DESENHA MAPA
        for (int l = 0; l < MAP_HEIGHT; l++)
        {
            for (int c = 0; c < MAP_WIDTH; c++)
            {
                // Posição do tile
                int x = c * TILE_SIZE;
                int y = l * TILE_SIZE;

                // Tipo do tile
                int tile = mapa[l][c];

                // DESENHA AS TEXTURAS BASEADAS NO NÚMERO
                if (tile == 0)
                {
                    DrawTexture(texVazio, x, y, WHITE);
                }
                else if (tile == 1)
                {
                    DrawTexture(texParede, x, y, WHITE);
                }
                else if (tile == 2)
                {
                    DrawTexture(texGrama, x, y, WHITE);
                }
                else if (tile == 3)
                {
                    DrawTexture(texAgua, x, y, WHITE);
                }
                else if (tile == 4)
                {
                    DrawTexture(texLava, x, y, WHITE);
                }
            }
        }

        // DESENHA JOGADOR EM FORMA DE QUADRADO
        DrawRectangleV(jogador, (Vector2){40, 40}, RED);

        // HUD
        DrawRectangle(
            0, 0, MAP_WIDTH * TILE_SIZE, 90, Fade(LIGHTGRAY, 0.9f)
        );

        DrawText("Tilemap em Raylib", 20, 20, 30, DARKBLUE);
        DrawText("Teclas W, S, A, D movem | Cuidado com a Lava!", 20, 55, 20, DARKGRAY);

        EndDrawing();
    }

    // DESCARREGA IMAGENS DA MEMÓRIA
    UnloadTexture(texParede);
    UnloadTexture(texGrama);
    UnloadTexture(texAgua);
    UnloadTexture(texLava);
    UnloadTexture(texVazio);

    // Fecha janela
    CloseWindow();

    return 0;
}
