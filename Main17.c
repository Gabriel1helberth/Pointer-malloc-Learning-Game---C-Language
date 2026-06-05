// Atividade da Aula:
#include "raylib.h"

// MAIN

int main(void)
{
    // Cria janela
    InitWindow(1000, 600, "Sprite Sheet");

    // Define FPS
    SetTargetFPS(60);

    // CARREGA TEXTURA

    Texture2D sprite =
        LoadTexture("mario.png");

    // CONFIGURAÇÃO DOS FRAME

    // Quantidade de frames
    int frames = 6;

    // Frame atual
    int frameAtual = 0;

    // Largura de cada frame
    int larguraFrame =
        sprite.width / frames;

    // Altura do frame
    int alturaFrame =
        sprite.height;

    // Controle do tempo da animação
    float tempoAnimacao = 0.4f;

    // Velocidade da animação
    float velocidadeAnimacao = 0.05f;

    // POSIÇÃO DO PERSONAGEM

    Vector2 posicao = { 450, 250 };

    // LOOP PRINCIPAL

    while (!WindowShouldClose()){

        // UPDATE

        // Delta time
        float delta = GetFrameTime();

        // Atualiza tempo da animação
        tempoAnimacao += delta;

        // Troca frame
        if (tempoAnimacao >= velocidadeAnimacao)
        {
            // Próximo frame
            frameAtual++;

            // Reinicia animação
            if (frameAtual >= frames)
            {
                frameAtual = 0;
            }

            // Reinicia temporizador
            tempoAnimacao = 0;
        }

        // Movimento do personagem
        if (IsKeyDown(KEY_RIGHT))
            posicao.x += 200 * delta;

        if (IsKeyDown(KEY_LEFT))
            posicao.x -= 200 * delta;

        if (IsKeyDown(KEY_UP))
            posicao.y -= 200 * delta;

        if (IsKeyDown(KEY_DOWN))
            posicao.y += 200 * delta;

        // SOURCE RECTANGLE

        Rectangle source = {

            // Frame atual
            frameAtual * larguraFrame,

            // Linha da sprite sheet
            0,

            // Largura do frame
            larguraFrame,

            // Altura do frame
            alturaFrame
        };

        // DESTINATION RECTANGLE

        Rectangle dest = {

            // Posição X
            posicao.x,

            // Posição Y
            posicao.y,

            // Escala horizontal
            larguraFrame * 3,

            // Escala vertical
            alturaFrame * 2
        };

        // DRAW

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Título
        DrawText(
            "Animacao com Sprite Sheet",
            20,
            20,
            30,
            DARKBLUE
        );

        // Instruções
        DrawText(
            "Use as setas para mover",
            20,
            60,
            20,
            DARKGRAY
        );

        // Desenha sprite animado
        DrawTexturePro(
            sprite,
            source,
            dest,
            (Vector2){0, 0},
            0,
            WHITE
        );

        // Informações
        DrawText(
            TextFormat("Frame Atual: %d",
                       frameAtual),
            20,
            100,
            20,
            BLACK
        );

        DrawText(
            "Sprite Sheet = varios frames em uma unica imagem",
            20,
            560,
            18,
            MAROON
        );

        EndDrawing();
    }

    // LIBERA MEMÓRIA

    UnloadTexture(sprite);

    CloseWindow();

    return 0;
}

// Desafio:
#include "raylib.h"

// MAIN
int main(void)
{
    // Cria janela
    InitWindow(1000, 600, "Sprite Sheet");

    // Define FPS
    SetTargetFPS(60);

    // CARREGA TEXTURA
    Texture2D sprite = LoadTexture("mario1.png"); // Adicione a extensão se necessário

    // CONFIGURAÇÃO DOS FRAMES
    int frames = 6;
    int frameAtual = 0;
    int larguraFrame = sprite.width / frames;
    int alturaFrame = sprite.height;

    // Controle do tempo da animação
    float tempoAnimacao = 0.4f;
    float velocidadeAnimacao = 0.05f;

    // POSIÇÃO DO PERSONAGEM
    Vector2 posicao = { 450, 250 };

    // DIREÇÃO DO PERSONAGEM (1 = Direita, -1 = Esquerda)
    int direcao = 1;

    // LOOP PRINCIPAL
    while (!WindowShouldClose()){

        // UPDATE
        float delta = GetFrameTime();
        tempoAnimacao += delta;

        // Troca frame
        if (tempoAnimacao >= velocidadeAnimacao)
        {
            frameAtual++;

            if (frameAtual >= frames)
            {
                frameAtual = 0;
            }

            tempoAnimacao = 0;
        }

        // Movimento e Atualização da Direção
        if (IsKeyDown(KEY_RIGHT)) {
            posicao.x += 200 * delta;
            direcao = 1;  // Olha para a direita
        }

        if (IsKeyDown(KEY_LEFT)) {
            posicao.x -= 200 * delta;
            direcao = -1; // Olha para a esquerda
        }

        if (IsKeyDown(KEY_UP)) {
            posicao.y -= 200 * delta;
        }

        if (IsKeyDown(KEY_DOWN)) {
            posicao.y += 200 * delta;
        }

        // SOURCE RECTANGLE
        Rectangle source = {
            // Posição X inicial do frame
            frameAtual * larguraFrame,
            
            // Linha da sprite sheet
            0,
            
            // LARGURA DO FRAME: Multiplicado pela direção. 
            // Se for -1, fica negativo e a Raylib espelha a imagem.
            larguraFrame * direcao, 
            
            // Altura do frame
            alturaFrame
        };

        // DESTINATION RECTANGLE
        Rectangle dest = {
            posicao.x,
            posicao.y,
            // A escala no destino sempre deve usar valores positivos
            larguraFrame * 3,
            alturaFrame * 2
        };

        // DRAW
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Título e Instruções
        DrawText("Animacao com Sprite Sheet", 20, 20, 30, DARKBLUE);
        DrawText("Use as setas para mover (Esq/Dir para virar)", 20, 60, 20, DARKGRAY);

        // Desenha sprite animado
        DrawTexturePro(
            sprite,
            source,
            dest,
            (Vector2){0, 0},
            0,
            WHITE
        );

        // Informações na tela
        DrawText(TextFormat("Frame Atual: %d", frameAtual), 20, 100, 20, BLACK);
        DrawText(TextFormat("Direcao (1 Dir, -1 Esq): %d", direcao), 20, 130, 20, BLUE);

        DrawText("Sprite Sheet = varios frames em uma unica imagem", 20, 560, 18, MAROON);

        EndDrawing();
    }

    // LIBERA MEMÓRIA
    UnloadTexture(sprite);
    CloseWindow();

    return 0;
}

Super Desafio:
#include "raylib.h"

// ESTADOS DO PERSONAGEM
// Usamos um enum onde cada valor corresponde a uma LINHA na Sprite Sheet.
typedef enum {
    IDLE = 0,   // Linha 0: Parado
    WALK = 1,   // Linha 1: Andando
    ATTACK = 2, // Linha 2: Atacando
    JUMP = 3    // Linha 3: Pulando
} EstadoPersonagem;

int main(void)
{
    // Cria janela e define FPS
    InitWindow(1000, 600, "Multiplas Animacoes");
    SetTargetFPS(60);

    // CARREGA TEXTURA
    // Assumimos que sua sprite sheet tem 4 linhas de animação
    Texture2D sprite = LoadTexture("mario_completo.png"); 

    // CONFIGURAÇÃO DOS FRAMES DA SPRITE SHEET
    int colunasMaximas = 6; // O número máximo de frames na maior animação
    int linhasMaximas = 4;  // Idle, Walk, Attack, Jump

    // Largura e Altura calculadas dividindo a imagem inteira
    int larguraFrame = sprite.width / colunasMaximas;
    int alturaFrame = sprite.height / linhasMaximas;

    // CONTROLES DE ANIMAÇÃO
    float tempoAnimacao = 0.0f;
    float velocidadeAnimacao = 0.1f; // Mais rápido para ficar fluido
    int frameAtual = 0;
    int maxFramesEstado = 4; // Quantidade de frames da animação atual

    // ESTADO E DIREÇÃO
    EstadoPersonagem estado = IDLE;
    EstadoPersonagem estadoAnterior = IDLE;
    int direcao = 1; // 1 = Direita, -1 = Esquerda

    // POSIÇÃO DO PERSONAGEM
    Vector2 posicao = { 450, 250 };
    float velocidadeMovimento = 200.0f;

    // LOOP PRINCIPAL
    while (!WindowShouldClose()){

        float delta = GetFrameTime();
        
        // Salva o estado do frame anterior para saber se precisamos reiniciar a animação
        estadoAnterior = estado;

        // 1. VERIFICAÇÃO DE INPUT E MUDANÇA DE ESTADO
        if (IsKeyDown(KEY_Z)) {
            // Tecla Z para atacar
            estado = ATTACK;
        } 
        else if (IsKeyDown(KEY_UP)) {
            // Seta pra cima para pular
            estado = JUMP;
            posicao.y -= velocidadeMovimento * delta;
        } 
        else if (IsKeyDown(KEY_RIGHT)) {
            estado = WALK;
            posicao.x += velocidadeMovimento * delta;
            direcao = 1;
        } 
        else if (IsKeyDown(KEY_LEFT)) {
            estado = WALK;
            posicao.x -= velocidadeMovimento * delta;
            direcao = -1;
        } 
        else if (IsKeyDown(KEY_DOWN)) {
            // Opcional em jogos plataforma, mas mantido para movimento livre
            estado = WALK;
            posicao.y += velocidadeMovimento * delta;
        } 
        else {
            // Se nenhuma tecla for pressionada, fica parado
            estado = IDLE;
        }

        // 2. CONFIGURA A QUANTIDADE DE FRAMES DE CADA ANIMAÇÃO
        // (Altere esses números dependendo de quantos frames cada ação tem na sua imagem)
        switch (estado) {
            case IDLE:   maxFramesEstado = 4; break; // Exemplo: Idle tem 4 frames
            case WALK:   maxFramesEstado = 6; break; // Exemplo: Walk tem 6 frames
            case ATTACK: maxFramesEstado = 3; break; // Exemplo: Attack tem 3 frames
            case JUMP:   maxFramesEstado = 2; break; // Exemplo: Jump tem 2 frames
        }

        // 3. REINICIA A ANIMAÇÃO SE O ESTADO MUDOU
        // Isso impede que um ataque comece no frame 3, por exemplo.
        if (estado != estadoAnterior) {
            frameAtual = 0;
            tempoAnimacao = 0.0f;
        }

        // 4. ATUALIZA O TEMPO E O FRAME
        tempoAnimacao += delta;
        if (tempoAnimacao >= velocidadeAnimacao) {
            frameAtual++;
            
            // Volta pro frame 0 se passou do limite da animação atual
            if (frameAtual >= maxFramesEstado) {
                frameAtual = 0;
            }
            tempoAnimacao = 0.0f;
        }

        // 5. SOURCE RECTANGLE (Corte na Imagem)
        Rectangle source = {
            // Coluna atual (FrameX)
            frameAtual * larguraFrame,

            // Linha atual (FrameY) baseada no estado (0=Idle, 1=Walk, etc.)
            estado * alturaFrame, 

            // Largura invertida baseada na direção (-1 ou 1)
            larguraFrame * direcao, 

            // Altura do frame
            alturaFrame
        };

        // 6. DESTINATION RECTANGLE (Onde e tamanho na tela)
        Rectangle dest = {
            posicao.x,
            posicao.y,
            larguraFrame * 3,
            alturaFrame * 2
        };

        // DRAW
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Textos na tela
        DrawText("Multiplas Animacoes", 20, 20, 30, DARKBLUE);
        DrawText("SETAS: Mover | UP: Pular | Z: Atacar", 20, 60, 20, DARKGRAY);

        // Desenha personagem
        DrawTexturePro(sprite, source, dest, (Vector2){0, 0}, 0, WHITE);

        // Depuração (Para você ver o que está acontecendo internamente)
        DrawText(TextFormat("Estado Atual (Linha): %d", estado), 20, 100, 20, BLACK);
        DrawText(TextFormat("Frame Atual: %d / %d", frameAtual + 1, maxFramesEstado), 20, 130, 20, RED);

        EndDrawing();
    }

    // LIBERA MEMÓRIA
    UnloadTexture(sprite);
    CloseWindow();

    return 0;
}
