/****

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

***/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
int main()
{
    int i = 0;
    int j = 0;
    int pa;
    char alpha[26] =  {'A', 'B', 'C', 'D', 'E', 'F', 'G','H', 'I', 'J', 'K', 'L', 'M', 'N','O', 'P', 'Q', 'R', 'S', 'T', 'U',
    'V', 'W', 'X', 'Y', 'Z'};
    char alpha_shift[26];
    char alpha_pa[26];
    char alpha_pg[26];
    char alpha_fibonacci[26];
    int pg;
    int opcao;
    char palavra[50];
    int shift;
    int tamanho_alpha = sizeof(alpha) / sizeof(alpha[0]);
    printf("\n", sizeof(alpha));
    printf("Vamos fazer uma dupla criptografia!!\n");
    printf("Digite uma palavra: \n");
    scanf("%s", palavra);
    int qtd_letras = strlen(palavra);
    char palavra_shift[qtd_letras + 1];
    char palavra_criptografada[qtd_letras + 1];
    printf("Digite o valor de SHIFT(primeira fase da criptografia): ");
    scanf("%d", &shift);
    // printf("Digite o valor da progressão aritmética: ");
    // scanf("%d", &pa);
    // printf("Digite o valor da progressão geométrica: ");
    // scanf("%d", &pg);
    printf("--------------------------\n");
    
    for (i = 0; i < qtd_letras; i++) {
        palavra[i] = toupper((unsigned char)palavra[i]);
    }
    
    
    // Primeira etapa de criptografia: SHIFT
    
    // No primeiro laço de repetição abaixo, ele está deslocando as posições do vetor
    // alpha_shift[0] = alpha[0 + 5] -> alpha_shift[0] = alpha[5](F); alpha_shift[1] = alpha[1 + 5](G)...
    for (i = 0; i < tamanho_alpha; i++) {
        alpha_shift[i] = alpha[(i + shift) % tamanho_alpha];
    }
    int tamanho_shift = sizeof(alpha_shift) / sizeof(alpha_shift[0]);
    for (j = 0; j < qtd_letras; j++) {
        for (i = 0; i < 26; i++) {
            if (palavra[j] == alpha[i]) {
                palavra_shift[j] = alpha_shift[i];
                break;
            }
        }
    }

    palavra_shift[qtd_letras] = '\0';
    
    
    int usado[26] = {0};
    int indice;
    int proximo;
    int anterior = 0;
    int atual = 1;
    for (i = 0; i < tamanho_shift; i++) {

        // 1. Calcula o índice candidato de Fibonacci
        indice = atual % tamanho_shift;

    // 2. Verifica se o índice já foi utilizado
        while (usado[indice] == 1) {
            indice = (indice + 1) % tamanho_shift;
        }

        // 3. Armazena a letra e marca o índice
        alpha_fibonacci[i] = alpha_shift[indice];
        usado[indice] = 1;

        // 4. Calcula o próximo termo sem deixar crescer
        proximo = (anterior + atual) % tamanho_shift;

        // 5. Atualiza os dois termos anteriores
        anterior = atual;
        atual = proximo;
    }
    

    
    printf("\nEscolha o tipo da segunda criptografia:\n");
    printf("1 - Progressao aritmetica\n");
    printf("2 - Progressao geometrica\n");
    printf("3 - Fibonacci\n");

    
    scanf("%d", &opcao);
    switch (opcao) {
    case 1:
        printf("Digite o valor da progressão aritmética: ");
        scanf("%d", &pa);
        // 1. Copia as posições múltiplas de pa
        for (i = 0; i < 26; i += pa) {
            alpha_pa[j] = alpha_shift[i];
            j++;
        }

        // 2. Copia as posições restantes
        for (i = 0; i < 26; i++) {
            if (i % pa != 0) {
                alpha_pa[j] = alpha_shift[i];
                j++;
            }
        }
        for (j = 0; j < qtd_letras; j++) {
            for (i = 0; i < 26; i++) {
                if (palavra_shift[j] == alpha[i]) {
                    palavra_criptografada[j] = alpha_pa[i];
                    break;
                }
            }
        }

        palavra_criptografada[qtd_letras] = '\0';
        break;

    case 2:
        printf("Digite o valor da progressão geométrica: ");
        scanf("%d", &pg);
        j = 0;
        for (i = 0; i < 26; i++) {
            if (i * pg > 25 && i > 0){
                alpha_pg[i] = alpha_shift[(i * pg) % 26];
            } else {
                alpha_pg[i] = alpha_shift[i * pg];
            }
        }
        for (j = 0; j < qtd_letras; j++) {
            for (i = 0; i < 26; i++) {
                if (palavra_shift[j] == alpha[i]) {
                    palavra_criptografada[j] = alpha_pg[i];
                    break;
                }
            }
        }

        palavra_criptografada[qtd_letras] = '\0';
        break;

    case 3:
        for (j = 0; j < qtd_letras; j++) {
            for (i = 0; i < 26; i++) {
                if (palavra_shift[j] == alpha[i]) {
                    palavra_criptografada[j] = alpha_fibonacci[i];
                    break;
                }
            }
        }

        palavra_criptografada[qtd_letras] = '\0';
        break;
    default:
        printf("Opcao invalida!\n");
        break;
}
    

printf("\n \nA seguir, a palavra criptografada:");
printf("\n%s", palavra_criptografada);

    return 0;
}