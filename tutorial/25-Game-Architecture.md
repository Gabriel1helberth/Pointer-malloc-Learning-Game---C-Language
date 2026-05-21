# 25 - Game Architecture

# Criando Arquitetura Profissional de Jogos em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
arquitetura profissional de jogos
```

Agora o projeto deixará de ser:

```text
um único arquivo gigante
```

e passará a possuir:

- organização profissional
- múltiplos arquivos
- módulos
- separação de responsabilidades
- engine architecture
- estrutura real de desenvolvimento

Isso é a base de qualquer:

- jogo profissional
- engine
- projeto grande
- software escalável

---

# O que iremos aprender

Nesta aula vamos estudar:

- arquitetura de software
- separação de arquivos
- módulos
- headers
- encapsulamento
- game loop profissional
- organização de projeto
- engine architecture

---

# O problema dos projetos iniciantes

No começo normalmente fazemos:

```text
tudo dentro do main.c
```

Exemplo:

```text
main.c
↓
10.000 linhas
↓
bagunça
↓
difícil manutenção
```

---

# O que acontece em projetos reais?

Projetos profissionais usam:

- múltiplos arquivos
- módulos separados
- sistemas independentes
- arquitetura organizada

---

# Exemplo real

```text
player.c
enemy.c
audio.c
physics.c
ui.c
save.c
scene_manager.c
```

Cada arquivo:
- possui responsabilidade própria

---

# Estrutura Profissional

# Exemplo de Organização

```text
meu_jogo/
│
├── assets/
│   ├── textures/
│   ├── audio/
│   └── fonts/
│
├── src/
│   ├── main.c
│   ├── player.c
│   ├── player.h
│   ├── enemy.c
│   ├── enemy.h
│   ├── physics.c
│   ├── physics.h
│   ├── ui.c
│   ├── ui.h
│   ├── save.c
│   ├── save.h
│   ├── scene_manager.c
│   └── scene_manager.h
│
├── build/
│
└── README.md
```

---

# O que cada pasta faz

| Pasta | Função |
|---|---|
| assets | imagens, sons, fontes |
| src | código fonte |
| build | executáveis |
| README | documentação |

---

# O que é um módulo?

Módulo é:

```text
parte isolada do sistema
```

Exemplo:

| Módulo | Responsabilidade |
|---|---|
| player | jogador |
| enemy | inimigos |
| audio | sons |
| physics | física |
| ui | interface |

---

# Arquitetura Moderna

```text
GAME
│
├── INPUT
├── PLAYER
├── ENEMY
├── PHYSICS
├── AUDIO
├── UI
├── SAVE SYSTEM
└── SCENE MANAGER
```

---

# Código Completo da Estrutura

# main.c

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// IMPORTA MÓDULOS
// =========================================

#include "player.h"
#include "enemy.h"
#include "ui.h"

// =========================================
// MAIN
// =========================================

int main(void)
{
    // Inicializa janela
    InitWindow(1200, 700, "Game Architecture");

    // FPS
    SetTargetFPS(60);

    // =========================================
    // INICIALIZA SISTEMAS
    // =========================================

    InitPlayer();

    InitEnemy();

    InitUI();

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // UPDATE
        // =========================================

        UpdatePlayer();

        UpdateEnemy();

        UpdateUI();

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawPlayer();

        DrawEnemy();

        DrawUI();

        EndDrawing();
    }

    // Fecha janela
    CloseWindow();

    return 0;
}
```

---

# player.h

```c
#ifndef PLAYER_H
#define PLAYER_H

// =========================================
// FUNÇÕES DO PLAYER
// =========================================

void InitPlayer();

void UpdatePlayer();

void DrawPlayer();

#endif
```

---

# player.c

```c
#include "raylib.h"

#include "player.h"

// =========================================
// DADOS PRIVADOS
// =========================================

static Vector2 jogador;

static float velocidade;

// =========================================
// INIT
// =========================================

void InitPlayer()
{
    jogador = (Vector2){300, 300};

    velocidade = 300;
}

// =========================================
// UPDATE
// =========================================

void UpdatePlayer()
{
    float delta = GetFrameTime();

    if (IsKeyDown(KEY_RIGHT))
        jogador.x += velocidade * delta;

    if (IsKeyDown(KEY_LEFT))
        jogador.x -= velocidade * delta;

    if (IsKeyDown(KEY_UP))
        jogador.y -= velocidade * delta;

    if (IsKeyDown(KEY_DOWN))
        jogador.y += velocidade * delta;
}

// =========================================
// DRAW
// =========================================

void DrawPlayer()
{
    DrawRectangleV(
        jogador,
        (Vector2){50, 50},
        BLUE
    );
}
```

---

# enemy.h

```c
#ifndef ENEMY_H
#define ENEMY_H

void InitEnemy();

void UpdateEnemy();

void DrawEnemy();

#endif
```

---

# enemy.c

```c
#include "raylib.h"

#include "enemy.h"

// =========================================
// DADOS DO ENEMY
// =========================================

static Vector2 enemy;

// =========================================
// INIT
// =========================================

void InitEnemy()
{
    enemy = (Vector2){700, 300};
}

// =========================================
// UPDATE
// =========================================

void UpdateEnemy()
{
    enemy.x += sin(GetTime()) * 0.5f;
}

// =========================================
// DRAW
// =========================================

void DrawEnemy()
{
    DrawRectangleV(
        enemy,
        (Vector2){50, 50},
        RED
    );
}
```

---

# ui.h

```c
#ifndef UI_H
#define UI_H

void InitUI();

void UpdateUI();

void DrawUI();

#endif
```

---

# ui.c

```c
#include "raylib.h"

#include "ui.h"

// =========================================
// INIT
// =========================================

void InitUI()
{

}

// =========================================
// UPDATE
// =========================================

void UpdateUI()
{

}

// =========================================
// DRAW
// =========================================

void DrawUI()
{
    DrawRectangle(
        0,
        0,
        1200,
        100,
        Fade(LIGHTGRAY, 0.9f)
    );

    DrawText(
        "Arquitetura Profissional",
        20,
        30,
        30,
        DARKBLUE
    );
}
```

---

# Explicação COMPLETA da Arquitetura

# 1. O que é arquitetura?

Arquitetura é:

```text
como o projeto é organizado
```

---

# Sem arquitetura

```text
código gigante
↓
difícil manutenção
↓
bugs
↓
bagunça
```

---

# Com arquitetura

```text
sistemas separados
↓
mais organização
↓
mais clareza
↓
mais escalabilidade
```

---

# 2. O que é separação de responsabilidades?

Cada módulo deve fazer:

```text
uma única coisa
```

---

# Exemplo

| Arquivo | Responsabilidade |
|---|---|
| player.c | jogador |
| enemy.c | inimigos |
| ui.c | interface |
| physics.c | física |

---

# Isso é MUITO importante

Evita:

```text
acoplamento excessivo
```

---

# 3. O que é .h?

Arquivos:

```text
.h
```

são:

```text
headers
```

---

# Eles funcionam como

```text
contratos do módulo
```

---

# Exemplo

```c
void UpdatePlayer();
```

Significa:

```text
“existe uma função chamada UpdatePlayer”
```

---

# 4. O que é .c?

Arquivos:

```text
.c
```

contêm:

```text
implementação real
```

---

# Exemplo

```c
void UpdatePlayer()
{
    ...
}
```

---

# 5. Include Guards

```c
#ifndef PLAYER_H
#define PLAYER_H
#endif
```

Evita:
- inclusão duplicada

---

# Isso é MUITO importante

Sem isso:
- compilador gera erros

---

# 6. static

```c
static Vector2 jogador;
```

Torna variável:

```text
privada do módulo
```

---

# Isso significa

Outros arquivos:
- NÃO conseguem acessar diretamente

---

# Isso melhora encapsulamento

Muito importante em:
- engenharia de software
- arquitetura
- engines

---

# 7. Init / Update / Draw

Arquitetura moderna normalmente usa:

```text
Init()
Update()
Draw()
```

---

# Fluxo profissional

```text
Init
↓
Loop:
    Update
    Draw
```

---

# 8. Init

```c
InitPlayer();
```

Responsável por:
- inicializar sistema

---

# Exemplo

- posição inicial
- velocidade
- assets
- texturas

---

# 9. Update

```c
UpdatePlayer();
```

Responsável por:
- lógica
- física
- IA
- movimentação

---

# 10. Draw

```c
DrawPlayer();
```

Responsável por:
- renderização visual

---

# Isso separa lógica e renderização

MUITO importante.

---

# 11. Fluxo completo da arquitetura

```text
MAIN
↓
Init Systems
↓
Game Loop
    ↓
    Update Systems
    ↓
    Draw Systems
```

---

# Visualização mental

```text
ENGINE
│
├── PLAYER
├── ENEMY
├── UI
├── AUDIO
├── SAVE
└── PHYSICS
```

---

# 12. Escalabilidade

Agora o projeto pode crescer.

Sem isso:
- impossível manter

---

# Exemplo real

Jogos grandes possuem:

```text
centenas de módulos
```

---

# 13. Encapsulamento

Cada módulo controla:
- seus próprios dados

---

# Isso evita

```text
efeito dominó
```

onde:
- um sistema quebra outro

---

# 14. Game Loop profissional

```c
while (!WindowShouldClose())
```

Agora o loop:
- apenas coordena sistemas

---

# Isso é MUITO importante

Main:
- não deve conter tudo

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Arquitetura | ✔ |
| Modularização | ✔ |
| Headers | ✔ |
| Encapsulamento | ✔ |
| Init/Update/Draw | ✔ |
| Organização | ✔ |
| Game Loop | ✔ |
| Escalabilidade | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
jogos profissionais NÃO são feitos em um único arquivo
```

E entende:
- organização profissional
- modularização
- separação de responsabilidades
- arquitetura escalável
- estrutura real de engines

---

# Curiosidade MUITO importante

Grandes engines usam exatamente isso:

| Engine | Arquitetura modular |
|---|---|
| Unity | ✔ |
| Unreal | ✔ |
| Godot | ✔ |
| Source Engine | ✔ |

---

# Resultado esperado

Você verá:

✅ projeto modular  
✅ múltiplos arquivos  
✅ arquitetura organizada  
✅ game loop profissional  
✅ sistemas separados  
✅ estrutura escalável  

---

# Atividade da Aula

## Exercício 1

Crie:
- physics.c

---

## Exercício 2

Crie:
- audio.c

---

## Exercício 3

Crie:
- save.c

---

## Exercício 4

Separe:
- input system

---

# Desafio Extra

Crie:
- asset manager

---

# Super Desafio

Transforme o projeto em:

- mini engine
- ECS
- scene system
- event system
- framework completo

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
26 - Asset Manager.md
```

onde iremos aprender:

- gerenciamento de assets
- texturas
- sons
- cache
- loading
- gerenciamento profissional de recursos
