# 34 - 3D Programming

# Criando Programação 3D em Raylib (C)

# Objetivo da Aula

Nesta aula iremos aprender a criar:

```text
gráficos 3D
```

Agora o projeto começará a possuir:

- mundo tridimensional
- câmera 3D
- objetos 3D
- profundidade
- iluminação
- meshes
- renderização 3D
- fundamentos de engines 3D

Isso é a base de:
- jogos 3D
- FPS
- simuladores
- engines modernas
- gráficos AAA

---

# O que iremos aprender

Nesta aula vamos estudar:

- programação 3D
- câmera 3D
- coordenadas 3D
- perspectiva
- meshes
- iluminação
- renderização 3D
- transformações espaciais

---

# O que é 3D?

3D significa:

```text
três dimensões
```

---

# Em 2D usamos

```text
X e Y
```

---

# Em 3D usamos

```text
X
Y
Z
```

---

# Significado dos eixos

| Eixo | Função |
|---|---|
| X | esquerda/direita |
| Y | cima/baixo |
| Z | profundidade |

---

# Visualização Mental

```text
        Y
        ↑
        │
        │
        └────→ X
       /
      /
     Z
```

---

# O mais importante

3D é:

```text
matemática espacial
```

---

# Jogos 3D famosos

| Jogo | 3D |
|---|---|
| Minecraft | ✔ |
| GTA V | ✔ |
| Doom | ✔ |
| Counter Strike | ✔ |
| Fortnite | ✔ |

---

# Pipeline 3D Moderno

```text
CPU
↓
Engine
↓
OpenGL
↓
Vertex Shader
↓
Matrizes 3D
↓
Rasterização
↓
Fragment Shader
↓
GPU
↓
Monitor
```

---

# Código Completo

```c
// =========================================
// IMPORTA RAYLIB
// =========================================

#include "raylib.h"

// =========================================
// MAIN
// =========================================

int main(void)
{
    // =========================================
    // CRIA JANELA
    // =========================================

    InitWindow(
        1280,
        720,
        "3D Programming"
    );

    // FPS
    SetTargetFPS(60);

    // =========================================
    // CAMERA 3D
    // =========================================

    Camera3D camera = {0};

    // =========================================
    // POSIÇÃO DA CAMERA
    // =========================================

    camera.position =
        (Vector3){0.0f, 10.0f, 20.0f};

    // =========================================
    // PARA ONDE OLHA
    // =========================================

    camera.target =
        (Vector3){0.0f, 0.0f, 0.0f};

    // =========================================
    // CIMA DA CAMERA
    // =========================================

    camera.up =
        (Vector3){0.0f, 1.0f, 0.0f};

    // =========================================
    // FOV
    // =========================================

    camera.fovy = 60.0f;

    // =========================================
    // PROJEÇÃO
    // =========================================

    camera.projection =
        CAMERA_PERSPECTIVE;

    // =========================================
    // PLAYER
    // =========================================

    Vector3 player =
        {0, 1, 0};

    // =========================================
    // LOOP PRINCIPAL
    // =========================================

    while (!WindowShouldClose())
    {
        // =========================================
        // MOVIMENTO PLAYER
        // =========================================

        if (IsKeyDown(KEY_W))
            player.z -= 0.2f;

        if (IsKeyDown(KEY_S))
            player.z += 0.2f;

        if (IsKeyDown(KEY_A))
            player.x -= 0.2f;

        if (IsKeyDown(KEY_D))
            player.x += 0.2f;

        // =========================================
        // CAMERA FOLLOW
        // =========================================

        camera.target = player;

        // =========================================
        // DRAW
        // =========================================

        BeginDrawing();

        ClearBackground(SKYBLUE);

        // =========================================
        // MODO 3D
        // =========================================

        BeginMode3D(camera);

        // =========================================
        // GRID
        // =========================================

        DrawGrid(50, 1.0f);

        // =========================================
        // PLAYER
        // =========================================

        DrawCube(
            player,
            2,
            2,
            2,
            BLUE
        );

        DrawCubeWires(
            player,
            2,
            2,
            2,
            DARKBLUE
        );

        // =========================================
        // CHÃO
        // =========================================

        DrawPlane(
            (Vector3){0,0,0},
            (Vector2){50,50},
            GREEN
        );

        // =========================================
        // PRÉDIOS
        // =========================================

        for (int i = -5; i <= 5; i++)
        {
            DrawCube(
                (Vector3)
                {
                    i * 4,
                    2,
                    -10
                },

                2,
                4,
                2,

                GRAY
            );
        }

        // =========================================
        // ESFERA
        // =========================================

        DrawSphere(
            (Vector3){5, 2, 5},
            2,
            RED
        );

        // =========================================
        // END 3D
        // =========================================

        EndMode3D();

        // =========================================
        // HUD
        // =========================================

        DrawRectangle(
            0,
            0,
            1280,
            160,
            Fade(BLACK, 0.5f)
        );

        DrawText(
            "3D Programming",
            20,
            20,
            40,
            WHITE
        );

        DrawText(
            "WASD = mover cubo",
            20,
            70,
            20,
            WHITE
        );

        DrawText(
            "Camera3D + Mundo 3D",
            20,
            100,
            20,
            YELLOW
        );

        DrawText(
            TextFormat(
                "Player X: %.2f",
                player.x
            ),
            450,
            70,
            20,
            SKYBLUE
        );

        DrawText(
            TextFormat(
                "Player Z: %.2f",
                player.z
            ),
            450,
            100,
            20,
            SKYBLUE
        );

        DrawText(
            "Pipeline 3D em tempo real",
            850,
            100,
            20,
            ORANGE
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

# 1. O que é programação 3D?

Programação 3D é:

```text
renderizar objetos em espaço tridimensional
```

---

# Diferente do 2D

Agora existe:
- profundidade

---

# 2. Coordenadas 3D

Usamos:

```text
X
Y
Z
```

---

# X

```text
esquerda ↔ direita
```

---

# Y

```text
baixo ↔ cima
```

---

# Z

```text
frente ↔ trás
```

---

# 3. Camera3D

```c
Camera3D camera;
```

Representa:
- câmera virtual do mundo

---

# Jogos 3D usam câmera virtual

Assim como:
- filmes
- cinema
- animação 3D

---

# 4. camera.position

```c
camera.position
```

Define:
- onde câmera está

---

# Exemplo

```c
{0,10,20}
```

Significa:
- 10 unidades acima
- 20 unidades afastada

---

# 5. camera.target

```c
camera.target
```

Define:
- para onde câmera olha

---

# Isso é MUITO importante

Sem target:
- câmera não sabe direção

---

# 6. camera.up

```c
camera.up
```

Define:
- orientação vertical

---

# Normalmente

```c
{0,1,0}
```

Porque:
- Y é eixo vertical

---

# 7. FOV

```c
camera.fovy
```

FOV significa:

```text
Field Of View
```

---

# Representa

```text
ângulo da visão
```

---

# Visualização

```text
visão estreita ← FOV → visão aberta
```

---

# 8. Perspectiva

```c
CAMERA_PERSPECTIVE
```

Objetos distantes:
- parecem menores

---

# Isso cria profundidade

---

# Fórmula da perspectiva

:contentReference[oaicite:0]{index=0}

---

# Quanto maior Z

Menor objeto aparece.

---

# 9. BeginMode3D()

```c
BeginMode3D(camera);
```

Ativa:
- renderização 3D

---

# Tudo desenhado depois

usa:
- pipeline 3D

---

# 10. DrawCube()

```c
DrawCube()
```

Desenha:
- cubo 3D

---

# Parâmetros

| Valor | Função |
|---|---|
| posição | local no mundo |
| largura | tamanho X |
| altura | tamanho Y |
| profundidade | tamanho Z |

---

# 11. DrawPlane()

```c
DrawPlane()
```

Cria:
- chão do mundo

---

# 12. DrawGrid()

```c
DrawGrid()
```

Desenha:
- grid 3D

---

# Muito usado em:
- engines
- editores
- debug

---

# 13. DrawSphere()

```c
DrawSphere()
```

Desenha:
- esfera 3D

---

# 14. Camera Follow

```c
camera.target = player;
```

Faz câmera:
- seguir jogador

---

# Isso é MUITO usado

Em:
- third person
- RTS
- simuladores

---

# 15. Pipeline 3D

Fluxo real:

```text
OBJETO 3D
↓
VERTEX SHADER
↓
MATRIZES
↓
PROJEÇÃO
↓
RASTERIZAÇÃO
↓
FRAGMENT SHADER
↓
TELA
```

---

# 16. Matrizes 3D

Motores 3D usam:
- matrizes
- álgebra linear

---

# Matrizes principais

| Matriz | Função |
|---|---|
| Model | posição objeto |
| View | câmera |
| Projection | perspectiva |

---

# MVP Matrix

Muito importante em 3D:

:contentReference[oaicite:1]{index=1}

---

# 17. Vertex Transformation

Todo vértice passa por:

```text
Model
↓
View
↓
Projection
```

---

# Isso transforma

```text
mundo 3D
↓
imagem 2D
```

---

# 18. Rasterização

GPU converte:
- triângulos 3D
- em pixels 2D

---

# 19. Profundidade

GPU usa:

```text
Z-Buffer
```

---

# Isso controla

```text
quem aparece na frente
```

---

# 20. Engines 3D modernas

Engines modernas possuem:
- iluminação
- sombras
- PBR
- SSAO
- ray tracing

---

# 21. FPS Games

FPS usa:
- câmera 3D
- perspectiva
- colisão 3D

---

# Doom revolucionou isso

---

# 22. Minecraft

Minecraft usa:
- voxels 3D
- chunks
- meshes

---

# 23. Matemática do 3D

3D depende muito de:
- álgebra linear
- vetores
- matrizes
- trigonometria

---

# Visualização mental

```text
MUNDO 3D
↓
CAMERA
↓
PROJEÇÃO
↓
TELA 2D
```

---

# Conceitos profissionais aprendidos

| Conceito | Foi usado |
|---|---|
| Camera3D | ✔ |
| Mundo 3D | ✔ |
| Perspectiva | ✔ |
| Pipeline 3D | ✔ |
| Matrizes | ✔ |
| Renderização 3D | ✔ |
| Coordenadas 3D | ✔ |
| Z-Buffer | ✔ |

---

# O que você aprende de verdade

# você entende:

```text
gráficos 3D são matemática espacial renderizada em tempo real
```

E entende:
- câmera 3D
- perspectiva
- renderização moderna
- pipeline gráfico
- engines 3D
- fundamentos usados em jogos AAA

---

# Curiosidade MUITO importante

Mesmo engines modernas ainda usam:
- matrizes
- vetores
- perspectiva
- rasterização

Porque:
- isso é a base da computação gráfica 3D

---

# Resultado esperado

Você verá:

✅ mundo 3D  
✅ câmera 3D  
✅ cubos renderizados  
✅ profundidade  
✅ pipeline 3D  
✅ movimentação no espaço tridimensional  

---

# Atividade da Aula

## Exercício 1

Adicione:
- câmera FPS

---

## Exercício 2

Adicione:
- colisão 3D

---

## Exercício 3

Adicione:
- iluminação dinâmica

---

## Exercício 4

Adicione:
- modelos 3D externos

---

# Desafio Extra

Crie:
- voxel world

---

# Super Desafio

Transforme isso em:
- mini Minecraft
- FPS engine
- deferred rendering
- shadow mapping
- PBR renderer
- mini engine 3D moderna

---

# Próximo passo

Na próxima aula podemos evoluir para:

```text
35 - Vulkan and Modern Graphics.md
```

onde iremos aprender:

- Vulkan
- renderização moderna
- GPU pipeline avançado
- command buffers
- rendering low-level
- gráficos AAA modernos
