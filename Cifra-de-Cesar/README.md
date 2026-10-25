# Cifra de César --- Criptografia em C

Projeto de estudo em C que explora a Cifra de César e alfabetos de
substituição. A versão atual aplica um SHIFT à palavra e, em seguida,
uma segunda substituição escolhida pelo usuário: PA, PG ou Fibonacci.

> **Estado atual:** a palavra após o SHIFT fica em `palavra_shift`. A
> opção Fibonacci atual reorganiza um alfabeto usando índices derivados
> de Fibonacci; ela não soma um termo diferente de Fibonacci a cada
> letra.

## Objetivos

-   Praticar vetores, strings, laços, condições e `switch`.
-   Construir alfabetos derivados do alfabeto `A`--`Z`.
-   Permitir SHIFT configurável.
-   Explorar regras de reorganização por PA, PG modular e Fibonacci.
-   Separar o resultado intermediário do resultado final.

## Fluxo

1.  Lê uma palavra e converte para maiúsculas.
2.  Lê o valor de SHIFT.
3.  Constrói `alpha_shift`.
4.  Aplica SHIFT à palavra e guarda o resultado em `palavra_shift`.
5.  O usuário escolhe PA, PG ou Fibonacci.
6.  O programa constrói ou consulta o alfabeto auxiliar correspondente.
7.  Cada letra de `palavra_shift` é localizada em `alpha` e substituída
    pela letra do mesmo índice no alfabeto escolhido.
8.  Exibe `palavra_criptografada`.

## Compilação

Com GCC e suporte a C99 ou posterior:

``` bash
gcc CriptografiaCesar.c -o cifra
./cifra
```

No Windows, dependendo do ambiente:

``` bash
gcc CriptografiaCesar.c -o cifra.exe
cifra.exe
```

## Vetores principais

  -----------------------------------------------------------------------
  Vetor                               Finalidade
  ----------------------------------- -----------------------------------
  `alpha`                             Alfabeto de referência, `A`--`Z`.

  `alpha_shift`                       Alfabeto deslocado por `shift`.

  `palavra_shift`                     Palavra após a primeira camada.

  `alpha_pa`                          Alfabeto reorganizado pela regra de
                                      PA.

  `alpha_pg`                          Alfabeto selecionado por
                                      multiplicação modular.

  `alpha_fibonacci`                   Alfabeto reorganizado com índices
                                      derivados de Fibonacci.

  `palavra_criptografada`             Resultado final da segunda camada.
  -----------------------------------------------------------------------

## Métodos implementados

-   **SHIFT:** usa `(i + shift) % 26` para montar o alfabeto deslocado.
-   **PA:** copia primeiro os índices múltiplos de `pa` de `alpha_shift`
    e depois as posições restantes.
-   **PG:** seleciona letras por `(i * pg) % 26`. Isso não é uma
    progressão geométrica tradicional de termos sucessivos. Para visitar
    todos os 26 índices sem repetição, `pg` deve ser coprimo de 26.
-   **Fibonacci:** gera índices candidatos usando Fibonacci modular e
    avança até uma posição ainda não usada. Isso cria uma reorganização
    do alfabeto, não um deslocamento variável por caractere.

## Exemplo da primeira camada

Com `coracao` e `SHIFT = 3`:

``` text
CORACAO -> FRUDFDR
```

O resultado final depende do método e, em PA/PG, do parâmetro informado.

## Limitações conhecidas

-   `scanf("%s", palavra)` não limita a entrada ao tamanho de
    `palavra[50]`.
-   `palavra_criptografada` e `palavra_shift` precisam ter espaço para
    `qtd_letras + 1`, incluindo o terminador `\0`.
-   `pa` deve ser positivo; `pa = 0` faz o laço da PA não avançar.
-   Valores não positivos de `pg` precisam ser rejeitados; alguns
    valores positivos repetem índices.
-   A opção inválida pode levar à impressão de um vetor não
    inicializado.
-   Caracteres fora de `A`--`Z` não têm tratamento específico.
-   A Cifra de César é didática e não oferece segurança para proteger
    dados reais.

## Próximos passos sugeridos

1.  Validar entradas e proteger limites dos vetores.
2.  Definir formalmente a regra de PG.
3.  Decidir se Fibonacci continuará reorganizando o alfabeto ou se será
    um deslocamento variável por letra.
4.  Criar testes de mesa e casos de borda.
5.  Implementar descriptografia, se desejado.
6.  Separar a lógica em funções para facilitar testes e manutenção.
