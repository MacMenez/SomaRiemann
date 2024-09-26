#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

float calcularDeltaX(float b, float a, int n){
    float d = (b-a)/n;
    return d;
}

void calcularPontosDir(float pontos[], float a, int n, float d){
    int j = 1;
    for(int i = 0; i < n; i++, j++){
        pontos[i] = a+(j*d);
    }
}

void calcularPontosEsq(float pontos[], float a, int n, float d){
    for(int i = 0; i < n; i++){
        pontos[i] = a+(i*d);
    }
}

//detecta quantidade de termos contando n° de espacos.
int contarTermos(char* s, int tam){
    int c = 1;
    for(int i = 0; i < tam; i++){
        if(s[i] == ' '){
            c++;
        }
    }
    return c;
}

void dividirTermosDaFuncao(char* f, char** termos, int num[], int c){
    //preencher um vetor de strings com os termos da funcao
    char sep[] = " ";
    int i = 0;
    char* token;
    token = strtok(f, sep);
    while(token != NULL){
        termos[i++] = token;
        token = strtok(NULL, sep);
    }

    //preencher um vetor de inteiros cujo conteudo corresponde ao valor numerico dos elementos armazenados no vetor de strings
    for(int i = 0; i < c; i++){
        num[i] = atoi(termos[i]);
    }
    
    //Obs: se determinado elemento do vetor num[] for igual a 0, significa que nao foi possivel transformar o termo correspondente do vetor termos[] em um numero inteiro, ou seja, provavelmente 0 corresponde a x^alguma coisa. Precisamos conservar os dois vetores para conseguir realizar a operacao.
}

bool isXNegativo(char* x){
    bool r = false;
    char primeiro_caractere = x[0];
    if(primeiro_caractere == '-'){
        r = true;
    }
    return r;
}

int identificarExpoente(char* x){
    int p = 1;
    int tam = strlen(x);
    //Se tam for 4, significa que a incognita é precedida por um sinal de negativo ou positivo
    if(tam == 4){
        sscanf(x, " %*c%*c%*c%d", &p); //ex: -x^2
    } else {
        sscanf(x, " %*c%*c%d", &p); //ex: x^2
    }
    return p;
}

float calcularSomaDir(char* f, int b, int a, int n){
    //calcular delta x
    float d = calcularDeltaX(b, a, n);
    
    //preencher vetor com valor dos pontos
    float pontos[n];
    calcularPontosDir(pontos, a, n, d);

    //CRIAR VETORES PARA ARMAZENAR TERMOS DA FUNCAO
    int c = contarTermos(f, strlen(f));
    char* termos[c];    
    int num[c];
    dividirTermosDaFuncao(f, termos, num, c);
    
    //declarar vetor que guarda "o valor da funcao nos pontos escolhidos"
    float fxi[n];
    //inicializar posicoes do vetor com zero para evitar que ele armazene lixo
    for(int i = 0; i < n; i++){
        fxi[i] = 0;
    }

    //CALCULO DO VALOR DA FUNCAO NOS PONTOS ESCOLHIDOS
    //for externo percorre o vetor de pontos[]
    for(int i = 0; i < n; i++){
        //for interno percorre o vetor num[] para calcular o termo fxi[i]
        for(int j = 0; j < c; j++){
            if(num[j] == 0){
                int expoente = identificarExpoente(termos[j]);
                if(expoente == 1){
                    if(isXNegativo(termos[j])){
                        fxi[i] += -pontos[i];
                    } else {
                        fxi[i] += pontos[i];
                    }
                } else {
                    if(isXNegativo(termos[j])){
                        fxi[i] += pow((-pontos[i]), expoente);
                    } else {
                        fxi[i] += pow(pontos[i], expoente);
                    }
                }
            } else {
                fxi[i] += num[j];
            }
        }
    }

    //CALCULO DO SOMATORIO
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += fxi[i]*d;
    }

    return soma;
}

float calcularSomaEsq(char* f, int b, int a, int n){
    //calcular delta x
    float d = calcularDeltaX(b, a, n);
    
    //preencher vetor com valor dos pontos
    float pontos[n];
    calcularPontosEsq(pontos, a, n, d);

    //CRIAR VETORES PARA ARMAZENAR TERMOS DA FUNCAO
    int c = contarTermos(f, strlen(f));
    char* termos[c];
    int num[c];
    dividirTermosDaFuncao(f, termos, num, c);
    
    //declarar vetor que guarda "o valor da funcao nos pontos escolhidos"
    float fxi[n];
    //inicializar posicoes do vetor com zero para evitar que ele armazene lixo
    for(int i = 0; i < n; i++){
        fxi[i] = 0;
    }

    //CALCULO DO VALOR DA FUNCAO NOS PONTOS ESCOLHIDOS
    //for externo percorre o vetor de pontos[]
    for(int i = 0; i < n; i++){
        //for interno percorre o vetor num[] para calcular o termo fxi[i]
        for(int j = 0; j < c; j++){
            if(num[j] == 0){
                int expoente = identificarExpoente(termos[j]);
                if(expoente == 1){
                    if(isXNegativo(termos[j])){
                        fxi[i] += -pontos[i];
                    } else {
                        fxi[i] += pontos[i];
                    }
                } else {
                    if(isXNegativo(termos[j])){
                        fxi[i] += pow((-pontos[i]), expoente);
                    } else {
                        fxi[i] += pow(pontos[i], expoente);
                    }
                }
            } else {
                fxi[i] += num[j];
            }
        }
    }

    //CALCULO DO SOMATORIO
    float soma = 0;
    for(int i = 0; i < n; i++){
        soma += fxi[i]*d;
    }

    return soma;
}

void imprimirResultado(char* f, int b, int a, int n){
    printf("\nN = %d\n", n);
    float somaDir = calcularSomaDir(f, b, a, n);
    float somaEsq = calcularSomaEsq(f, b, a, n);
    printf("Resultado da soma de Riemann a direita: %.9f\n", somaDir);
    printf("Resultado da soma de Riemann a esquerda: %.9f\n", somaEsq);
}

int main() {
    printf("Obs: Apos o primeiro termo da funcao, o sinal (+ ou -) que acompanha os termos seguintes precisa ser escrito junto do seu respectivo termo (sem espaco) para que o codigo funcione, por ex: x^2 +x +1\n");
    
    int n1 = 100, n2 = 300, n3 = 600, n4 = 1000, n5 = 1500, n6 = 2000;
    
    char f[50];
    printf("Digite a funcao: ");
    scanf(" %50[^\r\n]", f);
    
    float b = 0, a = 0;
    printf("Digite o intervalo da funcao (formato: b, a): ");
    scanf(" %f %*c %f", &b, &a);
    
    //imprimimos o resultado do somatorio à direita e à esquerda para cada n
    imprimirResultado(f, b, a, n1);
    imprimirResultado(f, b, a, n2);
    imprimirResultado(f, b, a, n3);
    imprimirResultado(f, b, a, n4);
    imprimirResultado(f, b, a, n5);
    imprimirResultado(f, b, a, n6);

    return 0;
}