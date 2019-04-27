#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct regCCorrente{

int conta;
char tipoMov;
char tipoConta;
char DataMov[10];
char Dataabertura[10];

double valorMov;
double saldoAtual;
double depositoInicial;

struct dadosPessoais {
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

void addZero(char[2]);
void formataData(char[10], char[10]);
void dataAtual(char[10], int, int, int);

void imprime(RegCCorrentePtr);

void insereConta(RegCCorrentePtr *, int, char[10], double);
void insereContaMeio(RegCCorrentePtr *, int, char[10], double);
void insereDadosPessoais(RegCCorrentePtr *);

int main(void)
{
    char data[10];

    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // data (int) to data (char)
    dataAtual(data, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // inicializa a lista encadeada
    RegCCorrentePtr contas = NULL;

    // insere algumas contas, de exemplo
    insereConta(&contas, 1, data, 0);
    insereConta(&contas, 2, data, 0);

    // imprime as contas
    imprime(contas);

    return 0;
}

void insereConta(RegCCorrentePtr *novaContaPtr, int conta, char dataAbertura[10],
                    double depositoInicial)
{
    RegCCorrentePtr novaConta;
    novaConta = malloc(sizeof(RegCCorrente));

    // leitura dos dados pessoais
    insereDadosPessoais(&novaConta);
    
    // cria a nova conta
    novaConta->conta            = conta;
    novaConta->saldoAtual       = depositoInicial;
    novaConta->depositoInicial  = depositoInicial;
    
    // formataData(novaConta->Dataabertura, dataAbertura);
    sprintf(novaConta->Dataabertura, "%s", dataAbertura);

    novaConta->proxConta = *novaContaPtr;   /* O endereco da proxConta, nesse
                                            caso, eh referente ao endereco da
                                            conta anterior, ou seja, a nova
                                            conta eh add no comeco da lista */

    // (*conta)->proxConta = novaConta;
    *novaContaPtr = novaConta;

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
}

void imprime(RegCCorrentePtr contaAtual){
    // verifica se a lista nao esta vazia
    if(contaAtual == NULL){
        printf("\nA lista esta vazia!");
        
        return;
    }

    printf("\n\n---------------------- Dados Pessoais -----------------------");
    printf("\nNome              : %s", contaAtual->DadosPessoais.nome);
    printf("\nRG                : %s", contaAtual->DadosPessoais.rg);
    printf("\nCPF               : %s", contaAtual->DadosPessoais.cpf);
    printf("\nData de Nascimento: %s", contaAtual->DadosPessoais.nascimento);


    // imprime os dados da conta
    printf("\n------------------------ Dados da conta -----------------------");    
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

void addZero(char data[2]){
    data[1] = data[0];
    data[0] = '0';
}

void dataAtual(char data[10], int dia, int mes, int ano){
    char d[2], m[2], a[4];

    itoa(dia, d, 10);
    itoa(mes, m, 10);
    itoa(ano, a, 10);

    if(dia < 9)
        addZero(d);

    if(mes < 9)
        addZero(m);

    for(int dt = 0; dt < 10; dt++){
        if(dt < 2)
            data[dt] = d[dt];

        else if(dt == 2)
            data[dt] = '/';

        else if(dt > 2 && dt < 5)
            data[dt] = m[dt - 3];

        else if(dt == 5)
            data[dt] = '/';
        
        else
            data[dt] = a[dt - 6];
    }
}