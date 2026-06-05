Main 18:

// Atividade de Sala:

// IMPORTA RAYLIB

#include "raylib.h"

// MAIN

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "MiniMundo");

    // Define FPS
    SetTargetFPS(60);

    // JOGADOR

    // Posição do jogador no mundo
    Vector2 jogador = { 500, 500 };

    // Velocidade
    float velocidade = 300;

    // CAMERA

    Camera2D camera = { 0 };

    // Centro da câmera na tela
    camera.offset = (Vector2){ 600, 350 };

    // Alvo da câmera
    camera.target = jogador;

    // Rotação da câmera
    camera.rotation = 0.0f;

    // Zoom
    camera.zoom = 1.0f;

    // LOOP PRINCIPAL

    while (!WindowShouldClose()){
        
        // UPDATE

        // Delta time
        float delta = GetFrameTime();

        // Movimento direita
        if (IsKeyDown(KEY_D))
            jogador.x += velocidade * delta;

        // Movimento esquerda
        if (IsKeyDown(KEY_A))
            jogador.x -= velocidade * delta;

        // Movimento cima
        if (IsKeyDown(KEY_W))
            jogador.y -= velocidade * delta;

        // Movimento baixo
        if (IsKeyDown(KEY_S))
            jogador.y += velocidade * delta;

        // Atualiza alvo da câmera
        camera.target.x += (jogador.x - camera.target.x) * 0.1f;

        // Zoom com mouse wheel
        camera.zoom += GetMouseWheelMove() * 0.1f;

        // Limites do zoom
        if (camera.zoom < 0.2f)
            camera.zoom = 0.2f;

        if (camera.zoom > 5.0f)
            camera.zoom = 3.0f;

        // Rotação com teclas
        if (IsKeyDown(KEY_Q))
            camera.rotation -= 50 * delta;

        if (IsKeyDown(KEY_E))
            camera.rotation += 50 * delta;

        // DRAW

        BeginDrawing();

        // Fundo
        ClearBackground(RAYWHITE);

        // MODO CAMERA 2D

        BeginMode2D(camera);

        // MUNDO

        // Grid do mundo
        for (int x = -10000; x < 10000; x += 100)
        {
            DrawLine(x, -10000, x, 10000, LIGHTGRAY);
        }

        for (int y = -10000; y < 10000; y += 100)
        {
            DrawLine(-10000, y, 10000, y, LIGHTGRAY);
        }

        // Centro do mundo
        DrawCircle(0, 0, 20, RED);

        // Jogador
        DrawRectangleV(
            jogador,
            (Vector2){50, 50},
            BLUE
        );

        // Objetos do mundo
        DrawRectangle(1000, 300, 200, 200, GREEN);
        DrawRectangle(-800, -400, 300, 150, ORANGE);
        DrawCircle(-1200, 700, 100, PURPLE);
        DrawRectangle(3000, 450 , 300, 300, GOLD);
        DrawCircle(-500, 500, 250, BLACK);
        DrawRectangle(400, 1000, 600, 600, YELLOW);
        DrawLine(400, 400, 100, 100, BLACK);

        // Finaliza modo câmera
        EndMode2D();

        // HUD

        DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.8f));

        DrawText(
            "Camera2D em Raylib",
            20,
            20,
            30,
            DARKBLUE
        );

        DrawText(
            "Teclas = W, S, A , D | Mouse Wheel = zoom | Q/E = rotacao",
            20,
            60,
            20,
            DARKGRAY
        );

        DrawText(
            TextFormat("Posicao: %.0f %.0f",
                       jogador.x,
                       jogador.y),
            20,
            90,
            20,
            BLACK
        );

        DrawText(
            TextFormat("Zoom: %.2f",
                       camera.zoom),
            350,
            90,
            20,
            BLACK
        );

        DrawText(
            TextFormat("Rotacao: %.1f",
                       camera.rotation),
            520,
            90,
            20,
            BLACK
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}

// Desafio Extra:

// IMPORTA RAYLIB
#include "raylib.h"

// MAIN
int main(void)
{
    // Tamanho da tela
    const int screenWidth = 1200;
    const int screenHeight = 700;
    
    // Janela do jogo
    InitWindow(screenWidth, screenHeight, "MiniMundo");
   
    // Textura do minimapa
    RenderTexture2D miniMapTexture = LoadRenderTexture(200, 200);
    
    float texWidth = (float)miniMapTexture.texture.width;
    float texHeight = (float)miniMapTexture.texture.height;
    
    Rectangle sourceRec = { 0.0f, 0.0f, texWidth, -texHeight };
    Rectangle destRec = { (float)screenWidth - 220.0f, 140.0f, 200.0f, 200.0f };
    
    // Matriz do mapa (5 linhas por 11 colunas)
    int mapa[5][11] = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    // Define FPS
    SetTargetFPS(60);

    // JOGADOR
    Vector2 jogador = { 500, 500 };
    float velocidad = 300;

    // CAMERA
    Camera2D camera = { 0 };
    camera.offset = (Vector2){ 600, 350 };
    camera.target = jogador;
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // LOOP PRINCIPAL
    while (!WindowShouldClose()){
        
        // UPDATE
        float delta = GetFrameTime();

        // Movimento
        if (IsKeyDown(KEY_D)) jogador.x += velocidad * delta;
        if (IsKeyDown(KEY_A)) jogador.x -= velocidad * delta;
        if (IsKeyDown(KEY_W)) jogador.y -= velocidad * delta;
        if (IsKeyDown(KEY_S)) jogador.y += velocidad * delta;

        // Atualiza alvo da câmera
        camera.target.x += (jogador.x - camera.target.x) * 0.1f;
        camera.target.y += (jogador.y - camera.target.y) * 0.1f;

        // Zoom com mouse wheel
        camera.zoom += GetMouseWheelMove() * 0.1f;
        if (camera.zoom < 0.2f) camera.zoom = 0.2f;
        if (camera.zoom > 5.0f) camera.zoom = 3.0f;

        // Rotação com teclas
        if (IsKeyDown(KEY_Q)) camera.rotation -= 50 * delta;
        if (IsKeyDown(KEY_E)) camera.rotation += 50 * delta;
        
        // Rnderização do Minimapa na textura
        BeginTextureMode(miniMapTexture);
            ClearBackground(RAYWHITE); // Usando fundo preto para destacar os objetos
         
            float mapaEscala = 0.06f;
            Vector2 centroMiniMapa = { 100, 100 };
            Vector2 offset = { centroMiniMapa.x - (jogador.x * mapaEscala), centroMiniMapa.y - (jogador.y * mapaEscala) };
        
            // Desenhar os blocos do minimapa com base no offset do jogador
            int tamanhoTile = 20;
            for (int i = 0; i < 5; i ++){
                for (int j = 0; j < 11; j ++){ // Corrigido limite para 11 colunas da matriz
                    if (mapa[i][j] == 1){
                        float tileX = (j * tamanhoTile) * mapaEscala + offset.x;
                        float tileY = (i * tamanhoTile) * mapaEscala + offset.y;
                    }
                }
            }

            // Desenho dos objetos escalados no minimapa
            DrawCircle(0 * mapaEscala + offset.x, 0 * mapaEscala + offset.y, 20 * mapaEscala, RED);
            DrawRectangle(1000 * mapaEscala + offset.x, 300 * mapaEscala + offset.y, 200 * mapaEscala, 200 * mapaEscala, GREEN);
            DrawRectangle(-800 * mapaEscala + offset.x, -400 * mapaEscala + offset.y, 300 * mapaEscala, 150 * mapaEscala, ORANGE);
            DrawCircle(-1200 * mapaEscala + offset.x, 700 * mapaEscala + offset.y, 100 * mapaEscala, PURPLE);
            DrawRectangle(3000 * mapaEscala + offset.x, 450 * mapaEscala + offset.y, 300 * mapaEscala, 300 * mapaEscala, GOLD);
            DrawCircle(-500 * mapaEscala + offset.x, 500 * mapaEscala + offset.y, 250 * mapaEscala, GRAY); 
            DrawRectangle(400 * mapaEscala + offset.x, 1000 * mapaEscala + offset.y, 600 * mapaEscala, 600 * mapaEscala, YELLOW);

            // Desenha o jogador fixo no centro para o mapa correr ao redor dele
            DrawCircle(centroMiniMapa.x, centroMiniMapa.y, 5, BLUE);
          
        EndTextureMode();

        // Draw Tela Principal
        BeginDrawing();
            ClearBackground(RAYWHITE);

            // MODO CAMERA 2D (Desenha apenas o mundo do jogo)
            BeginMode2D(camera);

                // Grid do mundo
                for (int x = -10000; x < 10000; x += 100) DrawLine(x, -10000, x, 10000, LIGHTGRAY);
                for (int y = -10000; y < 10000; y += 100) DrawLine(-10000, y, 10000, y, LIGHTGRAY);

                // Centro do mundo
                DrawCircle(0, 0, 20, RED);

                // Jogador
                DrawRectangleV(jogador, (Vector2){50, 50}, BLUE);

                // Objetos do mundo
                DrawRectangle(1000, 300, 200, 200, GREEN);
                DrawRectangle(-800, -400, 300, 150, ORANGE);
                DrawCircle(-1200, 700, 100, PURPLE);
                DrawRectangle(3000, 450 , 300, 300, GOLD);
                DrawCircle(-500, 500, 250, BLACK);
                DrawRectangle(400, 1000, 600, 600, YELLOW);

            EndMode2D();

            // HUD e INTERFACE 
            
            // Desenha a textura gerada do mini mapa
            DrawTexturePro(miniMapTexture.texture, sourceRec, destRec, (Vector2){0, 0}, 0.0f, WHITE);
            
            // Desenha a borda visual azul escuro por cima do minimapa
            DrawRectangleLinesEx(destRec, 4.0f, DARKBLUE);
            
            // Caixa cinza superior informativa
            DrawRectangle(0, 0, 1200, 120, Fade(LIGHTGRAY, 0.8f));
            DrawText("Camera2D em Raylib", 20, 20, 30, DARKBLUE);
            DrawText("Teclas = W, S, A , D | Mouse Wheel = zoom | Q/E = rotacao", 20, 60, 20, DARKGRAY);
            DrawText(TextFormat("Posicao: %.0f %.0f", jogador.x, jogador.y), 20, 90, 20, BLACK);
            DrawText(TextFormat("Zoom: %.2f", camera.zoom), 350, 90, 20, BLACK);
            DrawText(TextFormat("Rotacao: %.1f", camera.rotation), 520, 90, 20, BLACK);

        EndDrawing();
    }
    
    UnloadRenderTexture(miniMapTexture);
    CloseWindow();

    return 0;
}
