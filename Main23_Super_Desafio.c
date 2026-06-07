#include "raylib.h"
#include <stdio.h>

// =========================================
// ESTRUTURAS DO SISTEMA DE UI
// =========================================
typedef struct UIButton {
    Rectangle bounds;
    bool hover;
    bool clicado;
    Texture2D icon;
    const char *text;
} UIButton;

typedef struct UIWindow {
    Rectangle bounds;
    const char* title;
    bool isDragging;
    Vector2 dragOffset;
    bool active;
} UIWindow;

typedef struct UISlider {
    Rectangle bounds;
    float value; // 0.0f a 1.0f
    bool isDragging;
    const char* text;
} UISlider;

typedef struct UICheckbox {
    Rectangle bounds;
    bool checked;
    bool hover;
    const char* text;
} UICheckbox;

// =========================================
// FUNÇÕES DE ATUALIZAÇÃO E DESENHO
// =========================================

void UpdateDrawButton(UIButton *botao, Vector2 mouse) {
    botao->hover = CheckCollisionPointRec(mouse, botao->bounds);
    botao->clicado = (botao->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON));

    Rectangle drawBounds = botao->bounds;
    float escala = 1.0f;
    
    if (botao->hover && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) escala = 0.98f;
    else if (botao->hover) escala = 1.05f;

    if (escala != 1.0f) {
        float novaLargura = botao->bounds.width * escala;
        float novaAltura = botao->bounds.height * escala;
        drawBounds.x = botao->bounds.x - (novaLargura - botao->bounds.width) / 2;
        drawBounds.y = botao->bounds.y - (novaAltura - botao->bounds.height) / 2;
        drawBounds.width = novaLargura;
        drawBounds.height = novaAltura;
    }

    Color corBase = botao->hover ? LIME : DARKGRAY;
    if (botao->hover && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) corBase = BLUE;

    DrawRectangleRounded(drawBounds, 0.3f, 10, corBase);
    DrawRectangleRoundedLines(drawBounds, 0.3f, 10, BLACK);

    int fontSize = 20;
    int larguraTexto = MeasureText(botao->text, fontSize);
    DrawText(botao->text, drawBounds.x + drawBounds.width / 2 - larguraTexto / 2, 
             drawBounds.y + drawBounds.height / 2 - fontSize / 2, fontSize, WHITE);
}

void UpdateDrawWindow(UIWindow *win, Vector2 mouse) {
    if (!win->active) return;

    Rectangle titleBar = { win->bounds.x, win->bounds.y, win->bounds.width, 30 };

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, titleBar)) {
        win->isDragging = true;
        win->dragOffset.x = mouse.x - win->bounds.x;
        win->dragOffset.y = mouse.y - win->bounds.y;
    }
    
    if (win->isDragging) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            win->bounds.x = mouse.x - win->dragOffset.x;
            win->bounds.y = mouse.y - win->dragOffset.y;
        } else {
            win->isDragging = false;
        }
    }

    DrawRectangle(win->bounds.x + 5, win->bounds.y + 5, win->bounds.width, win->bounds.height, Fade(BLACK, 0.3f));
    DrawRectangleRec(win->bounds, LIGHTGRAY);
    DrawRectangleLinesEx(win->bounds, 2, DARKGRAY);

    DrawRectangleRec(titleBar, DARKBLUE);
    DrawText(win->title, titleBar.x + 10, titleBar.y + 8, 15, WHITE);
    
    Rectangle closeBtn = { titleBar.x + titleBar.width - 25, titleBar.y + 5, 20, 20 };
    bool closeHover = CheckCollisionPointRec(mouse, closeBtn);
    DrawRectangleRec(closeBtn, closeHover ? RED : MAROON);
    DrawText("X", closeBtn.x + 5, closeBtn.y + 3, 15, WHITE);
    
    if (closeHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        win->active = false;
    }
}

void UpdateDrawSlider(UISlider *slider, Vector2 mouse) {
    Rectangle areaInterativa = { slider->bounds.x, slider->bounds.y - 10, slider->bounds.width, slider->bounds.height + 20 };
    
    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mouse, areaInterativa)) {
        slider->isDragging = true;
    }

    if (slider->isDragging) {
        if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            slider->value = (mouse.x - slider->bounds.x) / slider->bounds.width;
            if (slider->value < 0.0f) slider->value = 0.0f;
            if (slider->value > 1.0f) slider->value = 1.0f;
        } else {
            slider->isDragging = false;
        }
    }

    DrawRectangleRec(slider->bounds, DARKGRAY);
    DrawRectangle(slider->bounds.x, slider->bounds.y, slider->bounds.width * slider->value, slider->bounds.height, BLUE);
    
    float knobX = slider->bounds.x + (slider->bounds.width * slider->value);
    DrawCircle(knobX, slider->bounds.y + slider->bounds.height / 2, 10, LIME);

    DrawText(slider->text, slider->bounds.x, slider->bounds.y - 20, 15, BLACK);
    DrawText(TextFormat("%i%%", (int)(slider->value * 100)), slider->bounds.x + slider->bounds.width + 15, slider->bounds.y, 15, BLACK);
}

void UpdateDrawCheckbox(UICheckbox *chk, Vector2 mouse) {
    chk->hover = CheckCollisionPointRec(mouse, chk->bounds);
    
    if (chk->hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        chk->checked = !chk->checked;
    }

    DrawRectangleRec(chk->bounds, WHITE);
    DrawRectangleLinesEx(chk->bounds, 2, chk->hover ? BLUE : DARKGRAY);

    if (chk->checked) {
        DrawRectangle(chk->bounds.x + 4, chk->bounds.y + 4, chk->bounds.width - 8, chk->bounds.height - 8, BLUE);
    }

    DrawText(chk->text, chk->bounds.x + chk->bounds.width + 10, chk->bounds.y + 2, 15, BLACK);
}

void DrawInventoryGrid(UIWindow *win, Vector2 mouse) {
    if (!win->active) return;
    
    int colunas = 4;
    int linhas = 4;
    float slotSize = 50.0f;
    float spacing = 10.0f;
    float startX = win->bounds.x + 20;
    float startY = win->bounds.y + 50;

    for (int y = 0; y < linhas; y++) {
        for (int x = 0; x < colunas; x++) {
            Rectangle slot = { startX + x * (slotSize + spacing), startY + y * (slotSize + spacing), slotSize, slotSize };
            bool hover = CheckCollisionPointRec(mouse, slot);
            
            DrawRectangleRec(slot, hover ? LIGHTGRAY : RAYWHITE);
            DrawRectangleLinesEx(slot, 1, DARKGRAY);
            
            if (x == 0 && y == 0) {
                DrawCircle(slot.x + slotSize/2, slot.y + slotSize/2, 15, GOLD);
                if (hover) {
                    DrawRectangle(mouse.x + 10, mouse.y, 100, 25, Fade(BLACK, 0.8f));
                    DrawText("Moeda de Ouro", mouse.x + 15, mouse.y + 5, 10, WHITE);
                }
            }
        }
    }
}

// =========================================
// MÁQUINA DE ESTADOS
// =========================================
typedef enum { STATE_MAIN_MENU, STATE_PLAYING, STATE_PAUSED } GameState;

int main(void) {
    InitWindow(1200, 800, "Sistema de UI com Áudio");
    
    // 1. INICIALIZAÇÃO DO ÁUDIO
    InitAudioDevice(); 
    
    // Carregamento de Recursos (coloque seus arquivos na mesma pasta)
    Sound fxClick = LoadSound("settings.mp3"); 
    Music bgMusic = LoadMusicStream("music.mp3"); 
    
    PlayMusicStream(bgMusic); // Inicia a música de fundo
    
    SetTargetFPS(60);

    GameState currentState = STATE_MAIN_MENU;

    // Declaração dos Componentes de UI
    UIButton btnStart = { {450, 300, 300, 60}, false, false, {0}, "INICIAR JOGO" };
    UIButton btnQuitApp = { {450, 400, 300, 60}, false, false, {0}, "SAIR" };
    
    UIButton btnResume = { {450, 200, 300, 60}, false, false, {0}, "VOLTAR AO JOGO" };
    UIButton btnInventory = { {450, 290, 300, 60}, false, false, {0}, "INVENTÁRIO" };
    UIButton btnSettings = { {450, 380, 300, 60}, false, false, {0}, "CONFIGURAÇÕES" };
    UIButton btnQuitToMenu = { {450, 470, 300, 60}, false, false, {0}, "MENU PRINCIPAL" };

    // Janelas e seus elementos internos (Aumentei a janela para caber o novo botão)
    UIWindow winSettings = { {200, 200, 400, 300}, "Configurações", false, {0}, false };
    
    // Inicializa o slider em 50% (0.5f)
    UISlider sldVolume = { {0, 0, 200, 15}, 0.5f, false, "Volume da Música" }; 
    UICheckbox chkMuteMusic = { {0, 0, 20, 20}, false, false, "Mutar Música" };
    UICheckbox chkFullscreen = { {0, 0, 20, 20}, false, false, "Tela Cheia" };

    UIWindow winInventory = { {700, 200, 280, 320}, "Inventário", false, {0}, false };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        
        // 2. ATUALIZA A MÚSICA DE FUNDO CONSTANTEMENTE
        UpdateMusicStream(bgMusic);

        // 3. LÓGICA DE CONTROLE DE VOLUME E MUTE
        if (chkMuteMusic.checked) {
            SetMusicVolume(bgMusic, 0.0f); // Se o checkbox estiver marcado, volume zero
        } else {
            SetMusicVolume(bgMusic, sldVolume.value); // Senão, segue o slider
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // =========================================
        // LÓGICA: MENU PRINCIPAL
        // =========================================
        if (currentState == STATE_MAIN_MENU) {
            DrawText("MEU SUPER JOGO", 380, 150, 50, DARKBLUE);
            
            UpdateDrawButton(&btnStart, mouse);
            UpdateDrawButton(&btnQuitApp, mouse);

            // Toca som se clicar e muda de estado
            if (btnStart.clicado) { PlaySound(fxClick); currentState = STATE_PLAYING; }
            if (btnQuitApp.clicado) { PlaySound(fxClick); break; }
        }
        
        // =========================================
        // LÓGICA: JOGANDO
        // =========================================
        else if (currentState == STATE_PLAYING) {
            ClearBackground(SKYBLUE);
            DrawText("Pressione ESC ou P para Pausar", 10, 10, 20, DARKBLUE);
            DrawCircle(600, 400, 50 + (sldVolume.value * 50), MAROON); 

            if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_P)) {
                PlaySound(fxClick);
                currentState = STATE_PAUSED;
                SetExitKey(KEY_NULL); 
            }
        }
        
        // =========================================
        // LÓGICA: MENU DE PAUSA
        // =========================================
        else if (currentState == STATE_PAUSED) {
            ClearBackground(Fade(BLACK, 0.6f));
            DrawText("JOGO PAUSADO", 400, 80, 50, WHITE);

            bool blockMenuClicks = (winSettings.active || winInventory.active);

            if (!blockMenuClicks) {
                UpdateDrawButton(&btnResume, mouse);
                UpdateDrawButton(&btnInventory, mouse);
                UpdateDrawButton(&btnSettings, mouse);
                UpdateDrawButton(&btnQuitToMenu, mouse);

                // Toca som e processa a ação
                if (btnResume.clicado) { PlaySound(fxClick); currentState = STATE_PLAYING; }
                if (btnInventory.clicado) { PlaySound(fxClick); winInventory.active = true; }
                if (btnSettings.clicado) { PlaySound(fxClick); winSettings.active = true; }
                if (btnQuitToMenu.clicado) { PlaySound(fxClick); currentState = STATE_MAIN_MENU; }
            } else {
                DrawRectangleRounded(btnResume.bounds, 0.3f, 10, DARKGRAY);
                DrawRectangleRounded(btnInventory.bounds, 0.3f, 10, DARKGRAY);
                DrawRectangleRounded(btnSettings.bounds, 0.3f, 10, DARKGRAY);
                DrawRectangleRounded(btnQuitToMenu.bounds, 0.3f, 10, DARKGRAY);
            }

            // --- JANELA DE CONFIGURAÇÕES ---
            if (winSettings.active) {
                UpdateDrawWindow(&winSettings, mouse);
                
                // Posições baseadas na janela (Draggable)
                sldVolume.bounds.x = winSettings.bounds.x + 50;
                sldVolume.bounds.y = winSettings.bounds.y + 100;
                
                chkMuteMusic.bounds.x = winSettings.bounds.x + 50;
                chkMuteMusic.bounds.y = winSettings.bounds.y + 150;

                chkFullscreen.bounds.x = winSettings.bounds.x + 50;
                chkFullscreen.bounds.y = winSettings.bounds.y + 200;

                UpdateDrawSlider(&sldVolume, mouse);
                UpdateDrawCheckbox(&chkMuteMusic, mouse);
                UpdateDrawCheckbox(&chkFullscreen, mouse);

                // Toca som se os checkboxes ou o slider forem clicados
                if (chkMuteMusic.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) PlaySound(fxClick);
                if (chkFullscreen.hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) PlaySound(fxClick);

                // Tela cheia
                if (chkFullscreen.checked && !IsWindowFullscreen()) ToggleFullscreen();
                else if (!chkFullscreen.checked && IsWindowFullscreen()) ToggleFullscreen();
            }

            // --- JANELA DE INVENTÁRIO ---
            if (winInventory.active) {
                UpdateDrawWindow(&winInventory, mouse);
                DrawInventoryGrid(&winInventory, mouse);
            }
            
            // Retorna ao jogo com ESC
            if (IsKeyPressed(KEY_ESCAPE)) {
                if (winSettings.active) winSettings.active = false;
                else if (winInventory.active) winInventory.active = false;
                else currentState = STATE_PLAYING;
            }
        }

        EndDrawing();
    }

    // 4. DESCARREGAMENTO SEGURO
    UnloadSound(fxClick);
    UnloadMusicStream(bgMusic);
    CloseAudioDevice(); // Fechar o dispositivo de áudio

    CloseWindow();
    return 0;
}
