#include "raylib.h"

// =========================================
// STRUCT BUTTON
// =========================================
typedef struct UIButton
{
    Rectangle bounds;
    const char *texto;
    bool hover;
    bool clicado;
    Texture2D icon; // Adicionado: Ícone do botão
} UIButton;

// =========================================
// FUNÇÃO DRAW BUTTON
// =========================================
void DrawButton(UIButton botao)
{
    Rectangle drawBounds = botao.bounds;
    
    // Fator de escala
    float escala = 1.0f;
    if (botao.clicado) escala = 1.05f;
    else if (botao.hover) escala = 1.02f;

    // Ajuste de escala e centralização
    if (escala > 1.0f)
    {
        float novaLargura = botao.bounds.width * escala;
        float novaAltura = botao.bounds.height * escala;
        drawBounds.x = botao.bounds.x - (novaLargura - botao.bounds.width) / 2;
        drawBounds.y = botao.bounds.y - (novaAltura - botao.bounds.height) / 2;
        drawBounds.width = novaLargura;
        drawBounds.height = novaAltura;
    }

    // Cores
    Color cor = DARKBLUE;
    if (botao.clicado) cor = GREEN;
    else if (botao.hover) cor = LIME;

    // Desenha Fundo e Borda
    DrawRectangleRounded(drawBounds, 0.3f, 10, cor);
    DrawRectangleRoundedLines(drawBounds, 0.3f, 10, BLACK);

    // Desenha Ícone (se carregado)
    if (botao.icon.id > 0)
    {
        float iconSize = drawBounds.height * 0.6f;
        DrawTexturePro(botao.icon, 
            (Rectangle){0, 0, (float)botao.icon.width, (float)botao.icon.height},
            (Rectangle){drawBounds.x + 20, drawBounds.y + (drawBounds.height - iconSize)/2, iconSize, iconSize},
            (Vector2){0, 0}, 0, WHITE);
    }

    // Desenha Texto centralizado
    int fontSize = 30;
    int larguraTexto = MeasureText(botao.texto, fontSize);
    DrawText(botao.texto, 
             drawBounds.x + drawBounds.width / 2 - larguraTexto / 2 + 15, 
             drawBounds.y + drawBounds.height / 2 - fontSize / 2, 
             fontSize, WHITE);
}

// =========================================
// MAIN
// =========================================
int main(void)
{
    InitWindow(1200, 800, "UI Buttons");
    InitAudioDevice();

    // Carregamento de Recursos
    Texture2D texPlay = LoadTexture("iconplay.png");
    Texture2D texOpt = LoadTexture("iconoptions.png");
    Texture2D texSet = LoadTexture("iconsettings.png");
    Texture2D texQuit = LoadTexture("iconquit.png");

    Sound soundPlay = LoadSound("play.mp3");
    Sound soundOptions = LoadSound("options.mp3");
    Sound soundSettings = LoadSound("settings.mp3");
    Sound soundQuit = LoadSound("quit.mp3");

    SetTargetFPS(60);

    // Criação dos Botões 
    UIButton playButton = { {450, 200, 300, 80}, "PLAY", false, false, texPlay };
    UIButton optionsButton = { {450, 320, 300, 80}, "OPTIONS", false, false, texOpt };
    UIButton settingsButton = { {450, 430, 300, 80}, "SETTINGS", false, false, texSet };
    UIButton quitButton = { {450, 550, 300, 80}, "QUIT", false, false, texQuit };

    const char *mensagem = "Nenhum botao clicado";

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // RESET DOS CLICKS
        playButton.clicado = false;
        optionsButton.clicado = false;
        quitButton.clicado = false;
        settingsButton.clicado = false;

        // VERIFICA HOVER
        playButton.hover = CheckCollisionPointRec(mouse, playButton.bounds);
        optionsButton.hover = CheckCollisionPointRec(mouse, optionsButton.bounds);
        settingsButton.hover = CheckCollisionPointRec(mouse, settingsButton.bounds);
        quitButton.hover = CheckCollisionPointRec(mouse, quitButton.bounds);
                
        // CLICKS
        if (playButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundPlay); playButton.clicado = true; mensagem = "PLAY clicado!"; }
        if (optionsButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundOptions); optionsButton.clicado = true; mensagem = "OPTIONS clicado!"; }
        if (settingsButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundSettings); settingsButton.clicado = true; mensagem = "SETTINGS clicado!"; }
        if (quitButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundQuit); quitButton.clicado = true; mensagem = "QUIT clicado!"; }
        
        // DRAW
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Sistema de UI Buttons", 320, 80, 50, DARKBLUE);

        DrawButton(playButton);
        DrawButton(optionsButton);
        DrawButton(settingsButton);
        DrawButton(quitButton);

        DrawRectangle(300, 700, 600, 60, Fade(LIGHTGRAY, 0.9f));
        DrawText(mensagem, 350, 720, 25, MAROON);

        EndDrawing();
    }
    
    UnloadTexture(texPlay);
    UnloadTexture(texOpt);
    UnloadTexture(texSet);
    UnloadTexture(texQuit);
    
    UnloadSound(soundPlay);
    UnloadSound(soundOptions);
    UnloadSound(soundSettings);
    UnloadSound(soundQuit);

    CloseWindow();
    return 0;
}
