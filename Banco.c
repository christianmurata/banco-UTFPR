#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct regCCorrente{

int conta;
char tipoMov;
char tipoConta;
char DataMov[10];
char Dataabertura[9];

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

void formataData(char[10], char[10]);

void imprime(RegCCorrentePtr);

void insereConta(RegCCorrentePtr *, int, char[10], double);
void insereContaMeio(RegCCorrentePtr *, int, char[10], double);
void insereDadosPessoais(RegCCorrentePtr *);

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

    insereConta(&contas, 1, data, 0);

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
    
    formataData(novaConta->Dataabertura, dataAbertura);


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