#include <stdio.h>
#include <stdlib.h>
#include<string.h>

typedef struct  RegCCorrente{

int Nconta;
char nome[40];
char senha[6];
char cpf[12];
char rg [10];
char nascimento[10];
char Dataabertura[10];
double depositStart;
char typeconta;
double saldonow;
char DataMov[10];
char typeMov;
double ValMov;
struct regCCorrente *Nextconta;




}  regCCorrente;
void leconta(void);
void insertconta(void);
void deleteconta(void);
int main(void)
{
    regCCorrente *L=NULL;
    regCCorrente teste;

    L = malloc(100*sizeof(regCCorrente));
 teste.depositStart=27.80;

printf("CU : %4.2lf", teste.depositStart);

    return 0;
}
