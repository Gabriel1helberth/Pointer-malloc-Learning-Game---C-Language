# 02 - Draw Rectangle

# Desenhando Retângulos em Raylib (C)

```c
#include "raylib.h"

int main()
{
    InitWindow(800, 600, "Draw Rectangle");

    while (!WindowShouldClose())
    {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawRectangle(300, 200, 200, 100, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
```

---

# O que foi adicionado nesta etapa

Nesta etapa aprendemos:

* desenhar formas geométricas
* trabalhar com coordenadas
* entender posição X e Y
* criar largura e altura
* desenhar usando cores
* entender pixels na tela

Agora começamos realmente a criar elementos gráficos de jogos.

---

# Explicação linha por linha

## Criando a janela

```c
InitWindow(800, 600, "Draw Rectangle");
```

Cria a janela principal.

Parâmetros:

| Valor            | Significado |
| ---------------- | ----------- |
| 800              | largura     |
| 600              | altura      |
| "Draw Rectangle" | título      |

---

# Loop principal

```c
while (!WindowShouldClose())
```

Repete o jogo continuamente.

Cada repetição:

* atualiza a tela
* desenha novamente
* cria um novo frame

---

# Começar renderização

```c
BeginDrawing();
```

Informa:

> “começar a desenhar o frame atual”.

---

# Limpar fundo

```c
ClearBackground(RAYWHITE);
```

Pinta toda a tela de branco.

Isso evita:

* rastros
* imagens antigas
* acúmulo de pixels

---

# Desenhando o retângulo

```c
DrawRectangle(300, 200, 200, 100, BLUE);
```

Essa função desenha um retângulo.

Parâmetros:

| Valor | Significado |
| ----- | ----------- |
| 300   | posição X   |
| 200   | posição Y   |
| 200   | largura     |
| 100   | altura      |
| BLUE  | cor         |

---

# Entendendo coordenadas

A tela funciona como um plano cartesiano simplificado.

```text
(0,0)
┌─────────────────────────→ X
│
│
│
│
↓
Y
```

Importante:

* X cresce para direita
* Y cresce para baixo

---

# Entendendo posição do retângulo

```text
X = 300
Y = 200
```

Significa:

* andar 300 pixels para direita
* andar 200 pixels para baixo

antes de desenhar.

---

# Largura e altura

```text
largura = 200
altura = 100
```

O retângulo ocupará:

```text
200 pixels na horizontal
100 pixels na vertical
```

---

# Sistema de pixels

Tudo na tela é desenhado usando pixels.

Um pixel é:

> o menor ponto visível da tela.

Então:

```text
800x600
```

significa:

```text
800 colunas de pixels
600 linhas de pixels
```

---

# Trabalhando com cores

```c
BLUE
```

A Raylib já possui várias cores prontas.

Exemplos:

| Cor    |
| ------ |
| RED    |
| GREEN  |
| BLUE   |
| YELLOW |
| BLACK  |
| WHITE  |
| PURPLE |
| ORANGE |
| PINK   |

---

# Finalizar renderização

```c
EndDrawing();
```

Entrega o frame pronto para a GPU.

---

# Fechar janela

```c
CloseWindow();
```

Libera os recursos corretamente.

---

# Fluxo visual do programa

```text
InitWindow()

↓ LOOP

BeginDrawing()
    ↓
ClearBackground()
    ↓
DrawRectangle()
    ↓
EndDrawing()

↓
CloseWindow()
```

---

# Conceito novo aprendido

| Conceito     | Explicação              |
| ------------ | ----------------------- |
| Coordenadas  | posição na tela         |
| Pixel        | menor ponto da tela     |
| Retângulo    | forma geométrica básica |
| Renderização | desenhar na GPU         |
| Frame        | imagem exibida          |

---

# O que acontece internamente

Quando você chama:

```c
DrawRectangle()
```

A Raylib:

1. envia comandos para OpenGL
2. define os vértices do retângulo
3. envia cor
4. GPU rasteriza os pixels
5. monitor mostra o resultado

---

# O que é rasterização

Rasterização é:

> transformar formas geométricas em pixels reais.

A GPU pega:

```text
retângulo matemático
```

E converte para:

```text
milhares de pixels coloridos
```

---

# Resultado esperado

Você verá:

* janela branca
* um retângulo azul
* no centro aproximado da tela

---

# Por que isso é importante

Quase tudo em jogos 2D começa com:

* quadrados
* colisores
* hitbox
* plataformas
* paredes
* interface
* barras de vida

Muitos jogos usam retângulos invisíveis internamente.

---

# Desafio

## Desafio 1

Mude a cor:

```c
BLUE
```

para:

```c
RED
```

---

## Desafio 2

Mude a posição:

```c
300, 200
```

para:

```c
100, 50
```

---

## Desafio 3

Crie um segundo retângulo:

```c
DrawRectangle(100, 400, 150, 80, GREEN);
```

---

## Desafio 4

Tente desenhar:

* uma casa
* um robô
* um personagem

usando apenas retângulos.

---

# Curiosidade

Muitos jogos antigos eram feitos quase totalmente usando:

* quadrados
* retângulos
* sprites simples

inclusive:

* Atari
* NES
* jogos arcade
* engines antigas

---

# Próximo passo

Na próxima etapa iremos aprender:

* variáveis
* movimentação
* atualização por frame
* animação básica

usando:

```c
x += 1;
```
