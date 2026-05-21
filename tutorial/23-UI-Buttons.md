# 23 - UI Buttons

# Criando Botões e Interface Gráfica em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
botões interativos
```

Agora o jogo deixará de depender apenas do teclado.

Vamos implementar:

- botões clicáveis
- interface gráfica
- mouse
- hover
- clique
- menus interativos
- UI básica

Isso é a base de:

- menus de jogos
- telas de pausa
- inventários
- configurações
- interfaces modernas

---

# O que iremos aprender

Nesta aula vamos estudar:

- botões
- mouse
- colisão do mouse
- hover
- clique
- Rectangle
- interfaces
- interação gráfica
- UI systems

---

# O que é UI?

UI significa:

```text
User Interface
```

Ou seja:

```text
interface do usuário
```

---

# Exemplos de UI em jogos

| Elemento | UI |
|---|---|
| botão PLAY | ✔ |
| menu pause | ✔ |
| inventário | ✔ |
| minimapa | ✔ |
| HUD | ✔ |

---

# O que é um botão?

Um botão normalmente possui:

- área clicável
- texto
- estado visual
- hover
- clique

---

# Estados visuais

| Estado | Significado |
|---|---|
| normal | parado |
| hover | mouse em cima |
| click | pressionado |

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// STRUCT BUTTON
// =========================================

typedef struct UIButton
{
    // Área do botão
    Rectangle bounds;

    // Texto
    const char *texto;

    // Estado hover
    bool hover;

    // Estado click
    bool clicado;

} UIButton;

// =========================================
// FUNÇÃO DRAW BUTTON
// =========================================

void DrawButton(UIButton botao)
{
    // Cor do botão
    Color cor = DARKBLUE;

    // Se mouse estiver em cima
    if (botao.hover)
    {
        cor = BLUE;
    }

    // Se clicado
    if (botao.clicado)
    {
        cor = SKYBLUE;
    }

    // Fundo do botão
    DrawRectangleRounded(
        botao.bounds,
        0.3f,
        10,
        cor
    );

    // Borda
    DrawRectangleRoundedLines(
        botao.bounds,
        0.3f,
        10,
        BLACK
    );

    // Calcula largura do texto
    int larguraTexto =
        MeasureText(
            botao.texto,
            30
        );

    // Desenha texto centralizado
    DrawText(
        botao.texto,
        botao.bounds.x +
        botao.bounds.width / 2 -
        larguraTexto / 2,

        botao.bounds.y + 20,

        30,
        WHITE
    );
}

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Cria janela
    InitWindow(1200, 700, "UI Buttons");

    // Define FPS
    SetTargetFPS(60);

    // =========================================
    // BOTÕES
    // =========================================

    UIButton playButton =
    {
        {450, 200, 300, 80},
        "PLAY",
        false,
        false
    };

    UIButton optionsButton =
    {
        {450, 320, 300, 80},
        "OPTIONS",
        false,
        false
    };

    UIButton quitButton =
    {
        {450, 440, 300, 80},
        "QUIT",
        false,
        false
    };

    // =========================================
    // TEXTO DE STATUS
    // =========================================

    const char *mensagem =
        "Nenhum botao clicado";

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // POSIÇÃO DO MOUSE
        // =========================================

        Vector2 mouse =
            GetMousePosition();

        // =========================================
        // RESET DOS CLICKS
        // =========================================

        playButton.clicado = false;
        optionsButton.clicado = false;
        quitButton.clicado = false;

        // =========================================
        // HOVER
        // =========================================

        playButton.hover =
            CheckCollisionPointRec(
                mouse,
                playButton.bounds
            );

        optionsButton.hover =
            CheckCollisionPointRec(
                mouse,
                optionsButton.bounds
            );

        quitButton.hover =
            CheckCollisionPointRec(
                mouse,
                quitButton.bounds
            );

        // =========================================
        // CLICK PLAY
        // =========================================

        if (playButton.hover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            playButton.clicado = true;

            mensagem =
                "PLAY clicado!";
        }

        // =========================================
        // CLICK OPTIONS
        // =========================================

        if (optionsButton.hover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            optionsButton.clicado = true;

            mensagem =
                "OPTIONS clicado!";
        }

        // =========================================
        // CLICK QUIT
        // =========================================

        if (quitButton.hover &&
            IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            quitButton.clicado = true;

            mensagem =
                "QUIT clicado!";
        }

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        // =========================================
        // TÍTULO
        // =========================================

        DrawText(
            "Sistema de UI Buttons",
            320,
            80,
            50,
            DARKBLUE
        );

        // =========================================
        // DESENHA BOTÕES
        // =========================================

        DrawButton(playButton);

        DrawButton(optionsButton);

        DrawButton(quitButton);

        // =========================================
        // STATUS
        // =========================================

        DrawRectangle(
            300,
            580,
            600,
            60,
            Fade(LIGHTGRAY, 0.9f)
        );

        DrawText(
            mensagem,
            350,
            600,
            25,
            MAROON
        );

        // =========================================
        // MOUSE INFO
        // =========================================

        DrawText(
            TextFormat(
                "Mouse: %.0f %.0f",
                mouse.x,
                mouse.y
            ),
            20,
            20,
            20,
            BLACK
        );

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
```

---

# Explicação COMPLETA da Arquitetura

# 1. O que é UI?

UI é:

```text
a camada visual de interação do usuário
```

Ela permite:
- clicar
- navegar
- selecionar
- interagir

---

# 2. Struct UIButton

```c
typedef struct UIButton
```

Criamos um tipo personalizado para:
- botão completo

---

# Campos do botão

| Campo | Função |
|---|---|
| bounds | área clicável |
| texto | texto do botão |
| hover | mouse em cima |
| clicado | estado de clique |

---

# 3. Rectangle bounds

```c
Rectangle bounds
```

Representa:
- posição
- largura
- altura

do botão.

---

# Exemplo

```c
{450, 200, 300, 80}
```

Significa:

| Valor | Função |
|---|---|
| 450 | posição X |
| 200 | posição Y |
| 300 | largura |
| 80 | altura |

---

# 4. GetMousePosition()

```c
GetMousePosition()
```

Retorna:

```text
posição atual do mouse
```

---

# Resultado

```text
X = horizontal
Y = vertical
```

---

# 5. Hover

```c
CheckCollisionPointRec()
```

Verifica:

```text
se ponto do mouse está dentro do botão
```

---

# Isso cria hover

```text
mouse entra no botão
↓
hover = true
```

---

# 6. Mudando cor no hover

```c
if (botao.hover)
{
    cor = BLUE;
}
```

Quando mouse passa em cima:
- botão muda cor

---

# Isso melhora UX

O jogador entende:
- que botão é interativo

---

# 7. Clique do mouse

```c
IsMouseButtonPressed(
    MOUSE_LEFT_BUTTON
)
```

Detecta:
- clique esquerdo

---

# 8. Clique + hover

```c
if (hover && click)
```

Significa:

```text
clicou DENTRO do botão
```

---

# Isso é MUITO importante

Sem hover:
- clique funcionaria em qualquer lugar

---

# 9. DrawRectangleRounded()

```c
DrawRectangleRounded()
```

Desenha:
- botão arredondado

---

# Isso deixa UI mais moderna

Sem arredondamento:
- aparência mais “antiga”

---

# 10. DrawRectangleRoundedLines()

Desenha:
- borda do botão

---

# 11. MeasureText()

```c
MeasureText()
```

Calcula:
- largura do texto

---

# Isso permite centralizar

```c
largura / 2
```

---

# 12. Centralização do texto

```c
botao.bounds.width / 2 -
larguraTexto / 2
```

Move texto:
- exatamente para centro

---

# 13. Estados visuais

Agora o botão possui:

| Estado | Cor |
|---|---|
| normal | azul escuro |
| hover | azul |
| click | azul claro |

---

# Isso é feedback visual

O jogador sente:
- interação
- resposta da interface

---

# 14. Fluxo completo do botão

```text
mouse move
↓
hover detecta colisão
↓
botão muda cor
↓
clique detectado
↓
ação executada
```

---

# Visualização mental

```text
MOUSE
   ↓
entra no botão
   ↓
hover
   ↓
click
   ↓
ação
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| UI | ✔ |
| Botões | ✔ |
| Hover | ✔ |
| Mouse | ✔ |
| Click | ✔ |
| Rectangle | ✔ |
| UX | ✔ |
| Feedback Visual | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
interfaces gráficas funcionam usando colisão
```

E entende:
- como menus funcionam
- como botões detectam mouse
- como interfaces modernas são feitas
- como jogos criam menus interativos

---

# Curiosidade MUITO importante

Mesmo engines gigantes usam:
- rectangles
- colisão
- eventos
- estados de botão

Inclusive:
- Unity
- Unreal
- Godot
- Roblox

---

# Resultado esperado

Você verá:

✅ botões clicáveis  
✅ hover funcionando  
✅ clique funcionando  
✅ mudança de cor  
✅ UI moderna  
✅ menu interativo  

---

# Atividade da Aula

## Exercício 1

Adicione botão:

```text
SETTINGS
```

---

## Exercício 2

Adicione:
- som ao clicar

---

## Exercício 3

Faça botão mudar:
- tamanho no hover

---

## Exercício 4

Adicione:
- ícones nos botões

---

# Desafio Extra

Crie:
- menu pause

---

# Super Desafio

Crie:
- menu completo
- inventário
- janela draggable
- sliders
- checkboxes
- sistema completo de UI

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
24 - Scene Manager.md
```

onde iremos aprender:

- trocar telas
- trocar fases
- game states
- menu → gameplay
- gerenciamento de cenas
- arquitetura profissional de jogos
