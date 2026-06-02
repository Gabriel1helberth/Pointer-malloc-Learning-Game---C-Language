//Importando biblioteca Raylib
#include "raylib.h"

//Criando estados possíveis do jogo

// MAIN
int main(void) {
    
    InitWindow(1000, 600, "HUD");
    
    InitAudioDevice();
    Sound soundDano = LoadSound("dano.mp3");
    Sound soundPontos = LoadSound("pontos.mp3");
    Sound soundTiro = LoadSound("tiro.mp3");
    Sound soundReload = LoadSound("reload.mp3");
    
    SetTargetFPS(60);
    
    // PLAYER
    Vector2 jogador = { 480, 300 }; // Posição inicial do jogador
    float velocidade = 5.0f;
    
    // HUD DO PLAYER
    int score = 0;
    int vida = 100;
    int municao = 30;
    float tempoJogo = 0;
    
    // LOOP PRINCIPAL
    while (!WindowShouldClose()) {
        
        // UPDATE
        tempoJogo += GetFrameTime(); // Atualização do tempo
        
        // MOVIMENTAÇÃO DO PLAYER
        if (IsKeyDown(KEY_RIGHT)) jogador.x += velocidade; // Direita
        if (IsKeyDown(KEY_LEFT))  jogador.x -= velocidade; // Esquerda
        if (IsKeyDown(KEY_UP))    jogador.y -= velocidade; // Para cima
        if (IsKeyDown(KEY_DOWN))  jogador.y += velocidade; // Para baixo
        
        // AÇÕES DO PLAYER
        
        // pontuação
        if (IsKeyPressed(KEY_P)) {
            PlaySound(soundPontos);
            score += 10;
        }
        
        // dano
        if (IsKeyPressed(KEY_H)) {
            PlaySound(soundDano);
            vida -= 5;
            if (vida < 0){
                vida = 0;
            }
        } 
        
        // gasto de munição e tiro
        if (IsKeyPressed(KEY_SPACE)) { 
            PlaySound(soundTiro);
            municao--;
            if (municao < 0) municao = 0;
        }
        
        // recarregamento
        if (IsKeyPressed(KEY_R)) {
            PlaySound(soundReload);
            municao += 5;
        }
        
        // INTERFACE DO JOGO
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            // desenho do jogador
            DrawRectangleV(jogador, (Vector2){40, 40}, BLUE);
            
            // HUD DO PLAYER
            // fundo da HUD
            DrawRectangle(0, 0, 1000, 115, DARKBLUE);
            
            // linha separadora
            DrawLine(0, 115, 1000, 115, BLACK);
        
            // título
            DrawText("HUD do Player", 20, 15, 20, BLACK);
        
            // pontuação 
            DrawText(TextFormat("Score: %d", score), 20, 65, 20, GOLD);
        
            // vida
            DrawText(TextFormat("Vida: %d", vida), 220, 65, 20, DARKGREEN);
           
            // Barra de vida
            // fundo da barra
            DrawRectangle(220, 40, 200, 20, RED);
            // representação visual da vida
            DrawRectangle(220, 40, vida * 2, 20, GREEN);
            // borda da barra de vida
            DrawRectangleLines(220, 40, 200, 20, BLACK);
             
            // Munição
            DrawText(TextFormat("Munição: %d", municao), 470, 65, 20, BLACK);
           
            // Tempo de Jogo
            DrawText(TextFormat("Tempo: %.1f", tempoJogo), 700, 65, 20, BLACK);
            
            // Texto Explicativo
            DrawText("P = pontos | H = Dano | Botão Direito Mouse = Atirar | R = recarregamento", 20, 560, 18, BLACK);
            
        EndDrawing();
    }
    
    // Descarrega os arquivos de áudio da memória antes de fechar o jogo
    UnloadSound(soundDano);
    UnloadSound(soundPontos);
    UnloadSound(soundTiro);
    UnloadSound(soundReload);
    CloseAudioDevice();
    
    CloseWindow();
    
    return 0;
}
