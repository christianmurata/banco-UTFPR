#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct regCCorrente{ /* Struct principal com os dados
                        da conta*/

int conta;
char tipoMov;
char tipoConta;
char DataMov[10];
char Dataabertura[9];

double valorMov;
double saldoAtual;
double depositoInicial;

struct dadosPessoais {        /*Sub-Struct que contem os dados pessoais da conta*/
    char nome[40];
    char senha[6];
    char cpf[12];
    char rg [10];
    char nascimento[10];
} DadosPessoais;

struct regCCorrente *proxConta;

};

typedef struct regCCorrente RegCCorrente;
typedef RegCCorrente *RegCCorrentePtr;

void formataData(char[10], char[10]);

void imprime(RegCCorrentePtr);

void insereConta(RegCCorrentePtr *, int, char[10], double);
void insereContaMeio(RegCCorrentePtr *, int, char[10], double);
void insereDadosPessoais(RegCCorrentePtr *);
void excluiCCorrente (RegCCorrentePtr* , int);


int main(void)
{
    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    printf("now: %d/%d/%d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);


    char data[10] = {'2', '6', '/', '0', '4', '/', '2', '0', '1', '9'};
    // printf("%s", data);

    // inicializa a lista encadeada
    RegCCorrentePtr contas = NULL;

    // insere algumas contas, de exemplo

    insereConta(&contas, 14, data, 0);
    insereConta(&contas, 3, data, 0);
    insereConta(&contas, 1, data, 0);



    imprime(contas);
    excluiCCorrente(&contas,1);
    imprime(contas);


    return 0;
}

void insereConta(RegCCorrentePtr *novaContaPtr, int conta, char dataAbertura[10],double depositoInicial)
{
    RegCCorrentePtr novaConta;//Nova conta a ser criada

    RegCCorrentePtr   Contaatual;

    RegCCorrentePtr Contaanterior;



    novaConta = malloc(sizeof(RegCCorrente)); //Aloca memoria para a proxima conta

    if(novaConta!=NULL){//Verifica se existe memoria disponivel

    // leitura dos dados pessoais
    insereDadosPessoais(&novaConta);

    // cria a nova conta
    novaConta->conta            = conta;
    novaConta->saldoAtual       = depositoInicial;
    novaConta->depositoInicial  = depositoInicial;

    formataData(novaConta->Dataabertura, dataAbertura);


    novaConta->proxConta=NULL;
    Contaanterior=NULL;
    Contaatual=*novaContaPtr;

    while(Contaatual!=NULL&&conta > Contaatual->conta) // Encontra o lugar da conta baseado em sem numero
    {                                                  // Ordena em ordem crescente por numero da conta
        Contaanterior=Contaatual;
        Contaatual=Contaatual->proxConta;
    }

    if(Contaanterior==NULL){

    novaConta->proxConta = *novaContaPtr;


    *novaContaPtr = novaConta;
    }

    else
    {
        Contaanterior->proxConta=novaConta;
        novaConta->proxConta=Contaatual;
    }
    }

    else//caso não houver memoria
    {
        printf("Sem memoria pra alocar");
    }

}

void insereDadosPessoais(RegCCorrentePtr *dadosPessoa)
{
    printf("\nNome: ");
    gets((*dadosPessoa)->DadosPessoais.nome);

    fflush(stdin);

    printf("\nRg: ");
    gets((*dadosPessoa)->DadosPessoais.rg);

    fflush(stdin);

    printf("\nCPF: ");
    gets((*dadosPessoa)->DadosPessoais.cpf);

    fflush(stdin);

    printf("\nData de Nascimento: ");
    gets((*dadosPessoa)->DadosPessoais.nascimento);

    fflush(stdin);

    printf("\nEscolha uma senha: ");
    gets((*dadosPessoa)->DadosPessoais.senha);

    fflush(stdin);
}

void imprime(RegCCorrentePtr contaAtual){
    // verifica se a lista nao esta vazia
    if(contaAtual == NULL){
        printf("\nA lista esta vazia!");

        return;
    }

    printf("\n---------------------- Dados Pessoais -------------------------");
    printf("\nNome              : %s", contaAtual->DadosPessoais.nome);
    printf("\nRG                : %s", contaAtual->DadosPessoais.rg);
    printf("\nCPF               : %s", contaAtual->DadosPessoais.cpf);
    printf("\nData de Nascimento: %s", contaAtual->DadosPessoais.nascimento);


    // imprime os dados da conta
    printf("\n---------------------- Dados da conta -------------------------");
    printf("\nNumero da Conta : %d",   contaAtual->conta);
    printf("\nData Abertura   : %s",   contaAtual->Dataabertura);
    printf("\nSaldo atual     : %.2f", contaAtual->saldoAtual);
    printf("\nDeposito Inicial: %.2f", contaAtual->depositoInicial);

    // verifica se existe mais elementos na lista
    // se não houver, para a recursão
    if(contaAtual->proxConta == NULL)
        return;

    // se houver, imprime
    imprime(contaAtual->proxConta);
}

void formataData(char data[10], char dataAbertura[10]){
    for(int dt = 0; dt < 10; dt++)
        data[dt] = dataAbertura[dt];
}
void excluiCCorrente (RegCCorrentePtr *Headlista, int nconta)
{
   RegCCorrentePtr percorreconta;
   RegCCorrentePtr contaAnterior;
   RegCCorrentePtr lixo;
   if(Headlista==NULL) //Caso da lista estar vazia
   {
       printf("Nao ha contas registradas");
       exit(0);

   }


   //Deleta primeira conta da lista
  if (nconta == (*Headlista)->conta)

   {
       RegCCorrentePtr aux;
       aux= *Headlista;
       *Headlista=(*Headlista)->proxConta;
       free(aux);

   }



   percorreconta = *Headlista;                /* Deleta a conta caso
                                               ela nao esteja no
                                               comeco da lista*/
   while(percorreconta!= NULL&&percorreconta->conta!=nconta)
   {
       contaAnterior= percorreconta;
       percorreconta= percorreconta->proxConta;
                                                }
   if(percorreconta!=NULL)
   {
       lixo=percorreconta;
       contaAnterior->proxConta=percorreconta->proxConta;
       free(lixo);
   }

}
