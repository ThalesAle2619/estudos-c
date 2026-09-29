/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <stdio.h>

int main() {

    float valor_a_sacar, saldo_disponivel;

    int estourar_limite, valor_divisivel5;

    int dezenas, centenas, unidades, notas_cem, notas_dez,
        notas_vinte, notas_cinco, notas_cinquenta;


    //Saldo disponível estipulado para testes

    saldo_disponivel = 500;


    // Pedindo o valor do saque para o usuário

    printf("Digite o valor a ser sacado: ");
    scanf("%f", &valor_a_sacar);


    // Fluxo de repetição para validar tanto se o número é múltiplo de 5, ou se ele é maior que o saldo

    while (valor_a_sacar > saldo_disponivel || (int)valor_a_sacar % 5 != 0) {

        //O fluxo vai ficar girando até que o número seja múltiplo e também seja menor que o saldo

        if (valor_a_sacar > saldo_disponivel) {

            estourar_limite = 1;

            while (estourar_limite == 1) {

                printf("Seu limite é igual a %.2f\n", saldo_disponivel);
                printf("Digite um valor válido: ");
                scanf("%f", &valor_a_sacar);

                if (valor_a_sacar <= saldo_disponivel) {
                    estourar_limite = 0;
                }
            }

        }


        //Esse fluxo de condição e repetição verifica se o saque é maior que o saldo, e vai pedir para o usuário informar um número válido se esse for o caso

        if ((int)valor_a_sacar % 5 != 0) {

            valor_divisivel5 = 0;

            while (valor_divisivel5 == 0) {

                printf("Este caixa só possui notas de 100, 50, 20 e 10.\n");
                printf("Digite um valor que as notas possam ser entregues completamente: ");
                scanf("%f", &valor_a_sacar);

                if ((int)valor_a_sacar % 5 == 0) {
                    valor_divisivel5 = 1;
                }
            }

        }

    }


    //Já esse verifica se o número é múltiplo de 5.


    //Aqui o número do saque tá sendo quebrado em partes, foi a maneira de contar as notas

    centenas = ((int)valor_a_sacar / 100) * 100;
    dezenas  = (((int)valor_a_sacar % 100) / 10) * 10;
    unidades = (int)valor_a_sacar % 10;


    //Aqui divide a centena e consegue a quantidade de notas, tipo, se for 200, 200 / 100 = 2 notas de 100

    notas_cem = centenas / 100;

    notas_cinquenta = dezenas / 50;


    if (notas_cinquenta >= 1) {

        notas_vinte = (dezenas - (50 * notas_cinquenta)) / 20;

    } else {

        notas_vinte = dezenas / 20;

    }


    //Como para as notas de 50, 20 e 10 eu estou usando a mesma base, que é as dezenas, é importante subtrair valor da dezena do saque com base na quantidade de notas anteriores.

    //Vamos considerar o número 280: 280 = 200 + 80, ou seja, 80 nesse fluxo primeiro vai ser dividido por 50, o que vai dar 1,6, nisso teremos 1 nota de cinquenta.

    //Mas 80 por 20 é igual a 4, então subtraímos 80 por 50 * x notas de cinquenta(no caso 1) 80 - 50 = 30, então a quantidade de notas de vinte vai usar 30 como valor a ser divido


    if (notas_cinquenta >= 1 || notas_vinte >= 1) {

        notas_dez = (dezenas - (50 * notas_cinquenta) - (20 * notas_vinte)) / 10;

    } else {

        notas_dez = dezenas / 10;

    }


    //Aqui o mesmo caso das notas de 20 é aplicado, só que adicionando a possibilidade da subtração por 20

    //Ainda no exemplo de 280, 80 - 50 = 30; 30 - 20 = 10 e 10 / 10 = 1 nota só de 10


    notas_cinco = unidades / 5;


    if (notas_cem > 0) {
        printf("%d de 100\n", notas_cem);
    }

    if (notas_cinquenta > 0) {
        printf("%d notas de 50\n", notas_cinquenta);
    }

    if (notas_vinte > 0) {
        printf("%d notas de 20\n", notas_vinte);
    }

    if (notas_dez > 0) {
        printf("%d notas de 10\n", notas_dez);
    }

    if (notas_cinco > 0) {
        printf("%d notas de 5\n", notas_cinco);
    }


    //Por fim, a gente imprime os números caso existam notas de seus respectivos valores.

    return 0;
}