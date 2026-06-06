#include "raylib.h"

// =========================================
// STRUCT BUTTON 
// =========================================

typedef struct PauseMenu
{
    Rectangle bounds;
    bool hover;
    bool clicado;
    Texture2D icon;
    const char *text; 
} PauseMenu;

// =========================================
// FUNÇÃO DRAW BUTTON
// =========================================

void DrawButton(PauseMenu botao)
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
    Color cor = GOLD;
    if (botao.clicado) cor = BLUE;
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
    int larguraTexto = MeasureText(botao.text, fontSize);
    DrawText(botao.text, 
             drawBounds.x + drawBounds.width / 2 - larguraTexto / 2 + 15, 
             drawBounds.y + drawBounds.height / 2 - fontSize / 2, 
             fontSize, WHITE);
}

int main(void)
{
    InitWindow(1200, 800, "Pause Menu");
    InitAudioDevice();

    // Carregamento de Recursos
    Texture2D texRes = LoadTexture("iconrestart.png");
    Texture2D texMain = LoadTexture("iconoptions.png");
    Texture2D texQuit = LoadTexture("iconquit.png");
    Texture2D texSett = LoadTexture("iconsettings.png");

    Sound soundRes = LoadSound("restart.mp3");
    Sound soundMain = LoadSound("mainmenu.mp3");
    Sound soundSett = LoadSound("settings.mp3");
    Sound soundQuit = LoadSound("quitgame.mp3");

    SetTargetFPS(60);

    // Criação dos Botões
    PauseMenu restartButton = { {450, 200, 300, 80}, false, false, texRes, "RESTART" };
    PauseMenu mainmenuButton = { {450, 320, 300, 80}, false, false, texMain, "MAIN MENU" };
    PauseMenu quitgameButton = { {450, 430, 300, 80}, false, false, texSett, "SETTINGS" };
    PauseMenu settingsButton = { {450, 550, 300, 80}, false, false, texQuit, "QUIT GAME" };
    
    const char *mensagem = "Selecione uma opcao"; // Variável declarada

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // RESET DOS CLICKS
        restartButton.clicado = false;
        mainmenuButton.clicado = false;
        quitgameButton.clicado = false;
        settingsButton.clicado = false;

        // VERIFICA HOVER
        restartButton.hover = CheckCollisionPointRec(mouse, restartButton.bounds);
        mainmenuButton.hover = CheckCollisionPointRec(mouse, mainmenuButton.bounds);
        quitgameButton.hover = CheckCollisionPointRec(mouse, quitgameButton.bounds);
        settingsButton.hover = CheckCollisionPointRec(mouse, settingsButton.bounds);
                
        // CLICKS
        if (restartButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundRes); restartButton.clicado = true; }
        if (mainmenuButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundMain); mainmenuButton.clicado = true; }
        if (quitgameButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundQuit); quitgameButton.clicado = true; }
        if (settingsButton.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { PlaySound(soundSett); settingsButton.clicado = true; }
        
        // DRAW
        BeginDrawing();
        ClearBackground(RED);

        DrawText("PAUSE MENU", 350, 100, 75, DARKBLUE);

        DrawButton(restartButton);
        DrawButton(mainmenuButton);
        DrawButton(quitgameButton);
        DrawButton(settingsButton);

        DrawRectangle(300, 700, 600, 60, Fade(LIGHTGRAY, 0.9f));
        DrawText(mensagem, 350, 720, 25, MAROON);

        EndDrawing();
    }
    
    // Descarregamento
    UnloadTexture(texRes);
    UnloadTexture(texMain);
    UnloadTexture(texQuit);
    UnloadTexture(texSett);
    
    UnloadSound(soundRes);
    UnloadSound(soundMain);
    UnloadSound(soundQuit);
    UnloadSound(soundSett);

    CloseWindow();
    return 0;
}
