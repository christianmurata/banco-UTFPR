#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*
* Estrutura que corresponde ao registro de
* uma conta bancaria
*/

struct regCCorrente{

int conta;
char tipoMov;
char tipoConta;
char DataMov[10];
char Dataabertura[10];

double valorMov;
double saldoAtual;
double depositoInicial;
char nome[40];
char senha[6];
char cpf[12];
char rg [10];
char nascimento[10];


struct regCCorrente *proxConta;

};

typedef struct regCCorrente RegCCorrente;

typedef RegCCorrente *RegCCorrentePtr;

/*
*Prototipo da função do menu do funcionario
*/

void menu();

/*
*Prototipo da função que realiza a limpeza de tela
*/

void clear();

void cabecalho();

void aguardaTecla();

void addZero(char[2]);

void dataAtual(char[10], int, int, int);

void imprime(RegCCorrentePtr);

/*
* Prototipo da função que retorna o numero da proxima
* conta livre disponivel
*/

int contaLivre(RegCCorrentePtr, int);

void insereConta(RegCCorrentePtr *, char[10]);

void insereContaMeio(RegCCorrentePtr *, int, char[10], double);

void insereDadosPessoais(RegCCorrentePtr *);

void excluiCCorrente (RegCCorrentePtr* , int);

/*
* Prototipo da função do que reliza o deposito de uma conta
* bancaria se tendo o numero desta conta
*/

void depositoCCorrente(int ,RegCCorrentePtr*, double);

/*
* Prototipo da função do que reliza o saque de uma conta
* bancaria se tendo o numero desta conta
*/

void saqueCCorrente(int ,RegCCorrentePtr*, double);


RegCCorrente * obtemCCorrente(int, RegCCorrentePtr);

RegCCorrente* leCCorrente (void);

void transfereValor(int, int, double,RegCCorrentePtr);


/*
* Função main do sistema, dentro dessa função
* serão chamadas as funções correspondentes
* as funcionalidades selecionadas
*/
int main(void)
{
    int opt;
    char data[10];

    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // data (int) to data (char)
    dataAtual(data, tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // inicializa a lista encadeada
    RegCCorrentePtr contas = NULL;

    do{
        // imprime o menu de selecao
        menu();

        printf("\nDigite sua opcao: ");
        scanf("%d", &opt);

        fflush(stdin);

        switch (opt)
        {
						// sair
						case -1:
								cabecalho();
								printf("\n------ Obrigado por utilizar nosso sistema! -------");
								printf("\n       <Pressione qualquer tecla para Sair>        ");
								break;

            // cadastrar
            case 1:
                cabecalho();
                insereConta(&contas, data);
                break;

            // excluir
            case 2:
                excluiCCorrente(&contas, 2);
                break;

            // imprimir conta
            case 3:
                cabecalho();
                imprime(contas);
                break;
            case 4:
                cabecalho();
                depositoCCorrente(1,&contas,1000);
                break;

            case 7:
                cabecalho();
                transfereValor(2,3,500,contas);
                break;

            default:
                printf("Opcao invalida");
                break;
        }

				aguardaTecla();

    } while(opt != -1);

    return 0;
}


/*
* A função procura o proximo numero de conta disponivel
*/
int contaLivre(RegCCorrentePtr PrimeiroPtr, int numero)
{
    // primeira conta
    if(PrimeiroPtr == NULL)
        return 1;

    if(PrimeiroPtr->conta != numero)
        return 1;

    return contaLivre(PrimeiroPtr->proxConta, numero + 1) + 1;
}

void insereConta(RegCCorrentePtr *Ptrinicial, char dataAbertura[10])
{
    RegCCorrentePtr novaConta;//Nova conta a ser criada

    RegCCorrentePtr   Contaatual;

    RegCCorrentePtr Contaanterior;

    novaConta = leCCorrente(); //Aloca memoria para a proxima conta

    //Verifica se existe memoria disponivel
    if(novaConta!=NULL){

        // leitura dos dados pessoais


        // cria a nova conta
        novaConta->conta            = contaLivre(*Ptrinicial,1);

        // formataData(novaConta->Dataabertura, dataAbertura);
        sprintf(novaConta->Dataabertura, "%s", dataAbertura);

        Contaatual = *Ptrinicial;

        novaConta->proxConta = NULL;
        Contaanterior        = NULL;

        // Encontra o lugar da conta baseado em sem numero
        // Ordena em ordem crescente por numero da conta
        while(Contaatual!=NULL&&novaConta->conta > Contaatual->conta)
        {
            Contaanterior=Contaatual;
            Contaatual=Contaatual->proxConta;
        }

        if(Contaanterior == NULL){

            novaConta->proxConta = *Ptrinicial;


            *Ptrinicial = novaConta;
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

/*void insereDadosPessoais(RegCCorrentePtr *dadosPessoa)
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

		printf("\nPressione <ENTER> para confirmar");
}*/

void excluiCCorrente (RegCCorrentePtr *PrimeiroPtr, int nconta)
{

   RegCCorrentePtr Contadestino;
   RegCCorrentePtr Contaanterior;
   RegCCorrentePtr lixo;

   if(PrimeiroPtr==NULL) //Caso da lista estar vazia
   {
       printf("Nao ha contas registradas");
       return ;

   }

   //Deleta primeira conta da lista
  if (nconta == (*PrimeiroPtr)->conta)

   {
       RegCCorrentePtr aux;
       aux= *PrimeiroPtr;
       *PrimeiroPtr=(*PrimeiroPtr)->proxConta;
       free(aux);

   }
   ;
    /* Deleta a conta caso ela nao esteja no comeco da lista*/
   Contadestino  = obtemCCorrente(nconta,*PrimeiroPtr);
   Contaanterior = obtemCCorrente(nconta-1,*PrimeiroPtr);


    if(Contadestino !=NULL)
    {
        lixo=Contadestino ;
        Contaanterior->proxConta=Contadestino ->proxConta;
        free(lixo);
    }

}

void imprime(RegCCorrentePtr contaAtual){
    // verifica se a lista nao esta vazia
    if(contaAtual == NULL){
        printf("\nA lista esta vazia!");

        return;
    }


    printf("\n---------------------------------------------------------------");
    printf("\n---------------------- Dados Pessoais -------------------------");
    printf("\nNome              : %s", contaAtual->nome);
    printf("\nRG                : %s", contaAtual->rg);
    printf("\nCPF               : %s", contaAtual->cpf);
    printf("\nData de Nascimento: %s", contaAtual->nascimento);


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

void cabecalho(){
    clear();

    printf("---------------------------------------------------------------\n");
    printf("        ,-----. ,----.    ,--.                   ,--.          \n");
    printf("       '  .--./'  .-./    |  |-.  ,--,--.,--,--, |  |,-.       \n");
    printf("       |  |    |  | .---. | .-. '' ,-.  ||      \\|     /      \n");
    printf("       '  '--'\\'  '--'  | | `-' |\\ '-'  ||  ||  ||  \\  \\   \n");
    printf("        `-----' `------'   `---'  `--`--'`--''--'`--'`--'      \n");
    printf("---------------------------------------------------------------\n");
    printf("---------------------------------------------------------------\n");
}

void menu(){
    clear();
    cabecalho();

    printf("\n---------------------------------------------------------------");
    printf("\n----------------------- Bem Vindo! ----------------------------");
    printf("\n|                1 - cadastrar conta                          |");
    printf("\n|                2 - Excluir conta corrente                   |");
    printf("\n|                3 - Consultar dados da conta                 |");
    printf("\n|                4 - Deposito                                 |");
    printf("\n|                5 - Saque                                    |");
    printf("\n|                6 - consultar saldo                          |");
    printf("\n|                7 - Trasferencia entre contas                |");
    printf("\n|                8 - Dados da ultima movimentacao             |");
    printf("\n|                                                             |");
    printf("\n|             (-1) - sair                                     |");
    printf("\n---------------------------------------------------------------");
}

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void aguardaTecla(){
    getchar();
    fflush(stdin);
}

void addZero(char data[2]){
    data[1] = data[0];
    data[0] = '0';
}

void depositoCCorrente(int nconta,RegCCorrentePtr* Ptrinicial, double deposito )
{
    RegCCorrentePtr Contadestino=obtemCCorrente(nconta,*Ptrinicial);






        Contadestino->saldoAtual=Contadestino->saldoAtual+deposito;



}


void saqueCCorrente(int nconta,RegCCorrentePtr* Ptrinicial, double saque)
{
        RegCCorrentePtr Contadestino= obtemCCorrente(nconta,*Ptrinicial);

        Contadestino->saldoAtual=Contadestino->saldoAtual-saque;
        //if(Contadestino->depositoInicial=='C'&&Contadestino->depositoInicial<0) O saque pra conta espcial e comum funciona diferente, não implementei ainda
        //{printf()}



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



RegCCorrente * obtemCCorrente(int nconta, RegCCorrentePtr Primeiroptr)
{
    RegCCorrentePtr percorrelista;

    RegCCorrentePtr anterior;

    percorrelista=Primeiroptr;

    while(percorrelista!=NULL && percorrelista->conta!=nconta)
    {
        anterior=percorrelista;
        percorrelista=percorrelista->proxConta;
    }
    return percorrelista;


}

RegCCorrente* leCCorrente (void)
{
    RegCCorrentePtr NovaConta= malloc(sizeof(RegCCorrente));
    NovaConta->proxConta=NULL;
    //NovaConta->conta=contaLivre(1,Headlist) sem idea se o numero da conta deve ser obtido aqui

    printf("Digite o saldo inicial da conta:\n");

    scanf("%lf",&NovaConta->depositoInicial);

    fflush(stdin);

    NovaConta->saldoAtual=NovaConta->depositoInicial;

    if(NovaConta->depositoInicial>10000)
    NovaConta->tipoConta='E';

    else
    NovaConta->tipoConta='C';

    printf("\nNome: ");
    gets(NovaConta->nome);

    fflush(stdin);

    printf("\nRg: ");
    gets(NovaConta->rg);

    fflush(stdin);

    printf("\nCPF: ");
    gets(NovaConta->cpf);

    fflush(stdin);

    printf("\nData de Nascimento: ");
    gets(NovaConta->nascimento);

    fflush(stdin);

    printf("\nEscolha uma senha: ");
    gets(NovaConta->senha);

    fflush(stdin);

		printf("\nPressione <ENTER> para confirmar");


    return NovaConta;
}
void transfereValor(int norigem, int ndestino, double valor,RegCCorrentePtr PrimeiroPtr)
{
    //RegCCorrentePtr ContaOrigim=obtemCCorrente(norigem,PrimeiroPtr);

    //RegCCorrentePtr ContaDestino=obtemCCorrente(ndestino,PrimeiroPtr);

    saqueCCorrente(norigem,&PrimeiroPtr,valor);
    depositoCCorrente(ndestino,&PrimeiroPtr,valor);


}
