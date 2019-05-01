#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct regCCorrente{ /* Struct principal com os dados da conta*/

int conta;
char tipoMov;
char tipoConta;
char DataMov[10];
char Dataabertura[10];

double valorMov;
double saldoAtual;
double depositoInicial;

struct dadosPessoais { /*Sub-Struct que contem os dados pessoais da conta*/
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

void menu();
void clear();
void cabecalho();
void aguardaTecla();

void addZero(char[2]);
void formataData(char[10], char[10]);
void dataAtual(char[10], int, int, int);

void imprime(RegCCorrentePtr);
int contaLivre(RegCCorrentePtr, int);

void insereConta(RegCCorrentePtr *, int, char[10], double);
void insereContaMeio(RegCCorrentePtr *, int, char[10], double);
void insereDadosPessoais(RegCCorrentePtr *);
void excluiCCorrente (RegCCorrentePtr* , int);

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
            // cadastrar
            case 1:
                cabecalho();
                insereConta(&contas, contaLivre(contas, 1), data, 0);
                break;
            
            // excluir
            case 2:
                excluiCCorrente(&contas, 1);
                break;
            
            // imprimir conta
            case 3:
                cabecalho();
                imprime(contas);
                aguardaTecla();
                break;
            
            default:
                printf("Opcao invalida");
                break;
        }

    } while(opt != -1);

    return 0;
}

int contaLivre(RegCCorrentePtr novaConta, int numero)
{
    // primeira conta
    if(novaConta == NULL)
        return 1;

    if(novaConta->conta != numero)
        return 1;

    return contaLivre(novaConta->proxConta, numero + 1) + 1;
}

void insereConta(RegCCorrentePtr *novaContaPtr, int conta, char dataAbertura[10], double depositoInicial)
{
    RegCCorrentePtr novaConta;//Nova conta a ser criada

    RegCCorrentePtr   Contaatual;

    RegCCorrentePtr Contaanterior;

    novaConta = malloc(sizeof(RegCCorrente)); //Aloca memoria para a proxima conta

    //Verifica se existe memoria disponivel
    if(novaConta!=NULL){
        
        // leitura dos dados pessoais
        insereDadosPessoais(&novaConta);

        // cria a nova conta
        novaConta->conta            = conta;
        novaConta->saldoAtual       = depositoInicial;
        novaConta->depositoInicial  = depositoInicial;

        // formataData(novaConta->Dataabertura, dataAbertura);	
        sprintf(novaConta->Dataabertura, "%s", dataAbertura);

        Contaatual = *novaContaPtr;

        novaConta->proxConta = NULL;
        Contaanterior        = NULL;

        // Encontra o lugar da conta baseado em sem numero
        // Ordena em ordem crescente por numero da conta
        while(Contaatual!=NULL&&conta > Contaatual->conta)
        {
            Contaanterior=Contaatual;
            Contaatual=Contaatual->proxConta;
        }

        if(Contaanterior == NULL){

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

    /* Deleta a conta caso ela nao esteja no comeco da lista*/
   percorreconta = *Headlista;

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

void imprime(RegCCorrentePtr contaAtual){
    // verifica se a lista nao esta vazia
    if(contaAtual == NULL){
        printf("\nA lista esta vazia!");

        return;
    }


    printf("\n---------------------------------------------------------------");
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
    printf("\n|                2 - Alterar dados da conta                   |");
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

void formataData(char data[10], char dataAbertura[10]){
    for(int dt = 0; dt < 10; dt++)
        data[dt] = dataAbertura[dt];
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