# Documentação do projeto --- Cifra de César em C

## 1. Apresentação

Este documento registra a evolução do projeto de Cifra de César em C,
desde a ideia inicial de deslocar letras até a versão atual, que combina
uma primeira camada SHIFT com uma segunda substituição selecionável.

A documentação separa o comportamento implementado da intenção de
projeto e das melhorias futuras. O escopo limita-se à Cifra de César.

## 2. Ponto de partida

O projeto começou como um exercício de criptografia por substituição,
baseado no alfabeto latino de 26 letras. A ideia central da Cifra de
César é deslocar cada letra por uma quantidade definida.

O vetor `alpha` passou a ser o alfabeto de referência. Em vez de alterar
esse vetor, o programa cria alfabetos auxiliares, permitindo localizar
letras por índice e consultar substituições diferentes.

## 3. Evolução da implementação

### 3.1. SHIFT configurável

A versão atual lê `shift` do usuário e constrói o alfabeto deslocado:

``` c
for (i = 0; i < tamanho_alpha; i++) {
    alpha_shift[i] = alpha[(i + shift) % tamanho_alpha];
}
```

O módulo (`%`) faz o índice retornar ao início do alfabeto quando
ultrapassa a última posição. Com `SHIFT = 3`, o alfabeto começa em `D`:

``` text
ABCDEFGHIJKLMNOPQRSTUVWXYZ
DEFGHIJKLMNOPQRSTUVWXYZABC
```

A palavra é convertida para maiúsculas com `toupper()` para corresponder
ao alfabeto de referência.

### 3.2. Separação da primeira camada

O projeto evoluiu para armazenar a palavra transformada pelo SHIFT em
`palavra_shift`, mantendo `palavra_criptografada` para o resultado
final. Essa separação permite que a segunda camada opere sobre o
resultado real da primeira.

### 3.3. Segunda camada selecionável

O menu permite escolher: 1. Progressão aritmética (PA). 2. Progressão
geométrica (PG). 3. Fibonacci.

Em cada caso, o programa localiza a letra de `palavra_shift` em `alpha`
e usa o mesmo índice no alfabeto auxiliar correspondente.

### 3.4. PA: posições múltiplas

O código solicita `pa` e usa dois laços: 1. Copia as posições
`0, pa, 2*pa, ...` de `alpha_shift`. 2. Copia as posições que não são
múltiplas de `pa`.

O contador `j` indica a próxima posição livre em `alpha_pa`. Essa é a
regra particular definida para a PA no projeto. Ela exige `pa > 0`; o
código atual ainda não valida essa condição.

### 3.5. PG: multiplicação modular

A opção PG monta `alpha_pg` selecionando posições segundo
`(i * pg) % 26`, com letras retiradas de `alpha_shift`.

Apesar do nome, o algoritmo atual não gera uma progressão geométrica
tradicional de termos sucessivos: multiplica o índice por `pg` e aplica
módulo 26. Se `pg` e 26 tiverem um divisor comum maior que 1, índices
podem se repetir. Para percorrer todos os 26 índices exatamente uma vez,
`pg` precisa ser coprimo de 26.

### 3.6. Fibonacci: reorganização de alfabeto

O programa constrói `alpha_fibonacci` antes de apresentar o menu.
`anterior`, `atual` e `proximo` mantêm a sequência; `indice` guarda o
candidato; `usado[26]` marca posições já utilizadas. Quando um índice
candidato já foi usado, o `while` avança para a próxima posição livre,
circularmente.

Isso produz uma reorganização do alfabeto baseada em candidatos
derivados de Fibonacci. Não equivale a somar um termo de Fibonacci
diferente a cada letra da palavra.

## 4. Fluxo atual de execução

1.  Declara variáveis e alfabetos.
2.  Lê a palavra e calcula seu tamanho.
3.  Declara os vetores intermediário e final.
4.  Lê SHIFT e converte a palavra para maiúsculas.
5.  Constrói `alpha_shift`.
6.  Aplica SHIFT à palavra e salva em `palavra_shift`.
7.  Constrói `alpha_fibonacci`.
8.  Mostra o menu e lê a opção.
9.  Constrói `alpha_pa` ou `alpha_pg` conforme a escolha; Fibonacci já
    está pronto.
10. Substitui as letras de `palavra_shift` usando o alfabeto escolhido.
11. Finaliza a string e exibe o resultado.

## 5. Exemplo confirmado da primeira camada

Entrada:

``` text
Palavra: coracao
SHIFT: 3
```

Depois da conversão:

``` text
CORACAO
```

A aplicação do SHIFT gera:

``` text
FRUDFDR
```

  Original     Índice Após SHIFT 3
  ---------- -------- --------------
  C                 2 F
  O                14 R
  R                17 U
  A                 0 D
  C                 2 F
  A                 0 D
  O                14 R

O resultado final depende da segunda opção escolhida.

## 6. Duas interpretações diferentes para Fibonacci

Durante a formulação surgiu um modelo que descrevia o deslocamento por
letra como `SHIFT + sequência[i]`, isto é:

``` text
novo índice = (índice original + SHIFT + fibonacci[i]) % 26
```

Esse modelo usa um deslocamento variável em cada posição da palavra. O
código atual, por outro lado, organiza um alfabeto auxiliar usando
índices derivados de Fibonacci e depois faz substituição por índice. Os
dois algoritmos são diferentes; os exemplos de teste precisam
corresponder à regra escolhida.

## 7. Estado atual

### Implementado

-   Alfabeto `A`--`Z`.
-   Leitura da palavra e conversão para maiúsculas.
-   SHIFT configurável.
-   Aplicação do SHIFT à palavra em uma primeira camada.
-   Vetor intermediário `palavra_shift`.
-   Menu para PA, PG ou Fibonacci.
-   Construção de alfabetos auxiliares.
-   Substituição da palavra intermediária.
-   Terminador `\0` nos casos válidos.

### Problemas e limitações conhecidos

1.  **Leitura:** `scanf("%s", palavra)` não limita a entrada ao tamanho
    de `palavra[50]`.
2.  **SHIFT:** valores negativos podem resultar em índices negativos em
    C; é necessário validar a entrada.
3.  **PA:** `pa = 0` faz o laço `i += pa` não avançar; valores negativos
    também devem ser rejeitados.
4.  **PG:** valores não positivos não são tratados adequadamente; alguns
    valores positivos repetem índices.
5.  **Opção inválida:** o programa ainda tenta imprimir
    `palavra_criptografada`, que pode não ter sido inicializada.
6.  **Caracteres fora de A--Z:** não há tratamento específico para
    pontuação, números ou letras acentuadas.
7.  **Segurança:** a Cifra de César é educacional e não deve proteger
    dados reais.

## 8. Próximas etapas

1.  Validar entradas e limites dos vetores.
2.  Definir formalmente a regra de PG.
3.  Escolher a interpretação desejada para Fibonacci.
4.  Criar testes de mesa para cada método e casos de borda.
5.  Implementar descriptografia, caso esteja no escopo.
6.  Separar o programa em funções, como `construir_shift`,
    `construir_pa`, `construir_pg`, `construir_fibonacci` e
    `criptografar`.

## 9. Glossário

-   **Alfabeto de referência:** `alpha`, vetor de `A` a `Z`.
-   **Índice:** posição de um elemento, começando em zero.
-   **SHIFT:** deslocamento circular do alfabeto.
-   **Camada:** etapa de transformação aplicada à palavra.
-   **Vetor intermediário:** `palavra_shift`.
-   **Módulo (`%`):** resto da divisão, usado para manter índices dentro
    de um intervalo.
-   **Permutação:** reordenação de elementos sem repeti-los ou
    eliminá-los.
-   **Terminador nulo (`\0`):** caractere que marca o fim de uma string
    em C.

## 10. Conclusão

O projeto evoluiu de uma substituição simples por deslocamento para uma
composição de transformações e alfabetos auxiliares. A separação entre
`palavra_shift` e `palavra_criptografada` é a mudança estrutural mais
importante para a dupla camada.

O próximo passo é alinhar as regras pretendidas ao comportamento real de
cada método, validar as entradas e criar testes reproduzíveis antes de
ampliar as funcionalidades.
