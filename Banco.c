#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
* Estrutura que corresponde ao registro de
* uma conta bancaria
*/

struct regCCorrente
{

    int conta;
    char tipoMov;
    char tipoConta;
    char DataMov[10];
    char Dataabertura[10];

    double valorMov;
    double saldoAtual;
    double saldoAnterior;
    double depositoInicial;
    char nome[40];
    char senha[7];
    char cpf[13];
    char rg[11];
    char nascimento[10];

    struct regCCorrente *proxConta;
};

typedef struct regCCorrente RegCCorrente;

typedef RegCCorrente *RegCCorrentePtr;

/*
*Prototipo da funcao do menu do funcionario
*/

void menufuncionario();
//void opcaofuncionario(int opt, RegCCorrentePtr Lista);

/*
*Prototipo da funcao do menu do cliente
*/

void menucliente();

/*
*Prototipo da funcao que realiza a limpeza de tela
*/

void clear();

void cabecalho();

void aguardaTecla();

void addZero(char[2]);

void dataAtual(char[10]);

void imprime(RegCCorrentePtr Lista);

/*
* Prototipo da funcao que retorna o numero da proxima
* conta livre disponivel
*/

int contaLivre(RegCCorrentePtr Lista);

void insereConta(RegCCorrentePtr* Lista);

void excluiCCorrente(RegCCorrentePtr* Lista, int nconta);

/*
* Prototipo da funcao do que reliza o deposito de uma conta
* bancaria se tendo o numero desta conta
*/

void depositoCCorrente(int nconta, RegCCorrentePtr Lista, double deposito);

/*
* Prototipo da funcao do que reliza o saque de uma conta
* bancaria se tendo o numero desta conta
*/

int saqueCCorrente(int nconta, RegCCorrentePtr Lista, double saque);

RegCCorrentePtr obtemCCorrente(int nconta, RegCCorrentePtr Lista);

RegCCorrentePtr obtemCCorrenteAnterior(int nconta, RegCCorrentePtr Lista);

RegCCorrentePtr leCCorrente(void);

void transfereValor(int nOrigem, int nDestino, double valor, RegCCorrentePtr Lista);

double saldoAtualCCorrente(int nconta, RegCCorrentePtr Lista);

void consultaCCorrente(int nconta, RegCCorrentePtr Lista);

void consultaUltimaMovimentacao(int nconta, RegCCorrentePtr Lista);

void alteraCCorrente(int nconta, RegCCorrentePtr Lista);

/*
* Funcao main do sistema, dentro dessa funcao
* serao chamadas as funcoes correspondentes
* as funcionalidades selecionadas
*/
int main(void)
{
    int opt;
    char data[10];
    char senhaFuncionario[7] = "987654";
    char senhalida[7];
    int contateste;

    // inicializa a lista encadeada
    RegCCorrentePtr Lista = NULL;


    do
    {
        clear();
        cabecalho();
        printf("Bem Vindo ao sistema do CG BANK!\n");
        printf("Digite um numero de conta valido:\n");
        scanf("%d", &contateste);
        fflush(stdin);
        aguardaTecla();

        if (contateste == 0)
        {

            clear();
            cabecalho();

            printf("Digite sua senha de funcionario(a)\n");
            fgets(senhalida, 7, stdin);
            fflush(stdin);

            aguardaTecla();

            if (strcmp(senhaFuncionario, senhalida) == 0)
            {

                printf("Senha valida!\n");
                printf("Abrindo menu do funcionario\n");
                aguardaTecla();

                do
                {
                    // imprime o menu de selecao
                    menufuncionario();

                    printf("\nDigite sua opcao: ");
                    scanf("%d", &opt);
                    fflush(stdin);
                    aguardaTecla();
                    switch (opt)
                    {
                    // cadastrar
                    case 1:
                        clear();
                        cabecalho();
                        insereConta(&Lista);
                        break;

                    // excluir
                    case 2:
                        clear();
                        cabecalho();
                        excluiCCorrente(&Lista, 2);
                        aguardaTecla();
                        break;

                    case 3:
                        clear();
                        cabecalho();
                        alteraCCorrente(2, Lista);
                        aguardaTecla();

                        break;

                    // imprimir todas as conta
                    case 4:

                        clear();
                        cabecalho();
                        consultaCCorrente(2,Lista);
                        getchar();
                        break;
                    case 5:
                        clear();
                        cabecalho();
                        depositoCCorrente(1, Lista, 1000);
                        aguardaTecla();
                        break;

                    case 6:
                        clear();
                        cabecalho();
                        saqueCCorrente(1, Lista, 1000);
                        aguardaTecla();
                        break;

                    case 7:
                        clear();
                        cabecalho();
                        if (saldoAtualCCorrente(2, Lista) == 0)
                        {
                            printf("Nao foi possivel encontrar a conta\n");
                        }
                        else
                        {
                            printf("O Saldo atual da conta eh de: %.2lf", saldoAtualCCorrente(2, Lista));
                        }
                        aguardaTecla();
                        break;

                    case 8:
                        clear();
                        cabecalho();
                        transfereValor(2, 3, 500, Lista);
                        aguardaTecla();
                        break;

                    case 9:
                        clear();
                        cabecalho();
                        consultaUltimaMovimentacao(2, Lista);
                        aguardaTecla();
                        break;

                    // sair
                    case 10:
                        printf("\n------ Obrigado por utilizar nosso sistema! -------");
                        printf("\n       <Pressione qualquer tecla para Sair do menu>\n        ");
                        break;




                    case 11:

                        clear();
                        cabecalho();
                        imprime(Lista);
                        getchar();
                        break;

                    default:
                        printf("Opcao invalida");
                        aguardaTecla();
                        break;
                    }




                } while (opt != 10);

                aguardaTecla();
                clear();
            }

            else
            {

                printf("Senha incorreta!\n");
                aguardaTecla();
            }
        }

        else if (contateste == -1)
        {
            clear();
            cabecalho();
            printf("\n------ Obrigado por utilizar nosso sistema! -------");
            printf("\n   <Pressione qualquer tecla para Sair do programa>\n        ");
        }

        else if (contateste > 0)
        {

            RegCCorrentePtr contadestino = obtemCCorrente(contateste, Lista);
            if (contadestino == NULL)
            {

                printf("A conta digita nao existe\n");
                aguardaTecla();
                clear();
            }

            else
            {
                cabecalho();
                printf("Digite a senha da sua conta de ususario:\n");
                fgets(senhalida, 7, stdin);
                aguardaTecla();
                if (strcmp(contadestino->senha, senhalida) == 0)
                {
                    printf("Senha valida!\n");
                    printf("Abrindo menu do cliente\n");
                    aguardaTecla();
                    do
                    {
                        menucliente();
                        printf("\nDigite sua opcao: ");
                        scanf("%d", &opt);
                        fflush(stdin);
                        aguardaTecla();
                        switch (opt)
                    {
                    // deposito do usuario
                    case 1:
                        clear();
                        cabecalho();
                        depositoCCorrente(contateste,Lista,1000);
                        aguardaTecla();
                        break;

                    // saque do usuario
                    case 2:
                        clear();
                        cabecalho();
                        saqueCCorrente(contateste,Lista,1000);
                        aguardaTecla();
                        break;

                    //cosulta de saldo do usuario
                    case 3:
                        clear();
                        cabecalho();
                        if (saldoAtualCCorrente(contateste, Lista) == 0)
                        {
                            printf("Nao foi possivel encontrar a conta\n");
                        }
                        else
                        {
                            printf("O Saldo atual da conta eh de: %.2lf", saldoAtualCCorrente(contateste, Lista));
                        }
                        aguardaTecla();
                        break;

                    // transferencia do usuario
                    case 4:

                        clear();
                        cabecalho();
                        transfereValor(contateste, 3, 500, Lista);
                        aguardaTecla();
                        break;
                        
                    // Consulta da ultima movimentacao do usuario
                    case 5:
                        clear();
                        cabecalho();
                        consultaUltimaMovimentacao(contateste, Lista);
                        aguardaTecla();
                        break;

                    // sair
                    case 6:
                        printf("\n------ Obrigado por utilizar nosso sistema! -------");
                        printf("\n       <Pressione qualquer tecla para Sair do menu>\n        ");
                        aguardaTecla();
                        break;


                    default:
                        printf("Opcao invalida");
                        aguardaTecla();
                        break;
                    }


                    } while (opt != 6);
                }
                else
                {
                    printf("A senha digita esta incorreta\n");
                    aguardaTecla();
                }
            }
        }

    } while (contateste != -1);

    return 0;
}

/*
* A funcao procura o proximo numero de conta disponivel
*/
int contaLivre(RegCCorrentePtr contaAtual)
{
    // a lista esta vazia
    if (contaAtual == NULL)
        return 1;

    //RegCCorrentePtr inicioLista = contaAtual;
    RegCCorrentePtr contaPtrAux = contaAtual;

    // primeiro numero conta verificado
    int numeroConta = 1;

    do
    {
        // nao eh possivel cadastrar mais nenhuma conta
        // lista cheia
        if (numeroConta > 999)
        {
            return -1;
        }

        // numero da conta nao disponivel
        // verifica o proximo numero de conta
        if (contaPtrAux->conta == numeroConta)
        {
            numeroConta++;
            //contaPtrAux = inicioLista;
        }

        // proxima conta na lista
        contaPtrAux = contaPtrAux->proxConta;

    } while (contaPtrAux != NULL);

    return numeroConta;
}

void insereConta(RegCCorrentePtr* Lista)
{
    RegCCorrentePtr novaConta; //Nova conta a ser criada

    RegCCorrentePtr Contaatual;

    RegCCorrentePtr Contaanterior;

    novaConta = leCCorrente(); //Le os dados de uma conta

    //Verifica se existe memoria disponivel
    if (novaConta != NULL)
    {

        // Gera do numero da conta
        novaConta->conta = contaLivre(*Lista);

        Contaatual = *Lista;

        novaConta->proxConta = NULL;
        Contaanterior = NULL;

        // Encontra o lugar da conta baseado em sem numero
        // Ordena em ordem crescente por numero da conta
        while (Contaatual != NULL && novaConta->conta > Contaatual->conta)
        {
            Contaanterior = Contaatual;
            Contaatual = Contaatual->proxConta;
        }

        if (Contaanterior == NULL)
        {

            novaConta->proxConta = *Lista;

            *Lista = novaConta;
        }

        else
        {
            Contaanterior->proxConta = novaConta;
            novaConta->proxConta = Contaatual;
        }
    }

    /*else//caso nao houver memoria
    {
        printf("Sem memoria pra alocar");
    }*/
}

void excluiCCorrente(RegCCorrentePtr* Lista, int nconta)
{

    RegCCorrentePtr Contadestino;
    RegCCorrentePtr Contaanterior;
    RegCCorrentePtr lixo;

    if (*Lista == NULL) //Caso da lista estar vazia
    {
        printf("Nao ha contas registradas");
        return;
    }

    Contadestino = obtemCCorrente(nconta, *Lista);
    Contaanterior = obtemCCorrenteAnterior(nconta, *Lista);

    //Deleta primeira conta da lista
    if (nconta == (*Lista)->conta)

    {
        RegCCorrentePtr aux;
        aux = *Lista;
        *Lista = (*Lista)->proxConta;
        free(aux);
    }

    /* Deleta a conta caso ela nao esteja no comeco da lista*/

    if (Contadestino != NULL)
    {
        lixo = Contadestino;
        Contaanterior->proxConta = Contadestino->proxConta;
        free(lixo);
    }

    else
    {
        cabecalho();
        printf("A conta digitada nao existe\n");
    }
}

void imprime(RegCCorrentePtr Lista)
{
    // verifica se a lista nao esta vazia
    if (Lista == NULL)
    {
        printf("\nA lista esta vazia!");

        return;
    }

    printf("\n---------------------------------------------------------------");
    printf("\n---------------------- Dados Pessoais -------------------------");
    printf("\nNome              : %s", Lista->nome);
    printf("\nRG                : %s", Lista->rg);
    printf("\nCPF               : %s", Lista->cpf);
    printf("\nData de Nascimento: %s", Lista->nascimento);

    // imprime os dados da conta
    printf("\n---------------------- Dados da conta -------------------------");
    printf("\nNumero da Conta : %d", Lista->conta);
    printf("\nData Abertura   : %s", Lista->Dataabertura);
    printf("\nSaldo atual     : %.2lf", Lista->saldoAtual);
    printf("\nDeposito Inicial: %.2lf", Lista->depositoInicial);
    printf("\nTipo da conta   : %c", Lista->tipoConta);
    printf("\nValor da ultima movimentacao: %.2lf", Lista->valorMov);
    printf("\nTipo de movimentacao:   : %c", Lista->tipoMov);
    printf("\nData da ultima movientacao: %s", Lista->DataMov);
    // verifica se existe mais elementos na lista
    // se nao houver, para a recursao
    if (Lista->proxConta == NULL)
        return;

    // se houver, imprime
    imprime(Lista->proxConta);
}

void cabecalho()
{

    printf("---------------------------------------------------------------\n");
    printf("        ,-----. ,----.    ,--.                   ,--.          \n");
    printf("       '  .--./'  .-./    |  |-.  ,--,--.,--,--, |  |,-.       \n");
    printf("       |  |    |  | .---. | .-. '' ,-.  ||      \\|     /      \n");
    printf("       '  '--'\\'  '--'  | | `-' |\\ '-'  ||  ||  ||  \\  \\   \n");
    printf("        `-----' `------'   `---'  `--`--'`--''--'`--'`--'      \n");
    printf("---------------------------------------------------------------\n");
    printf("---------------------------------------------------------------\n");
}

void menufuncionario()
{
    clear();
    cabecalho();

    printf("\n---------------------------------------------------------------");
    printf("\n----------------------- Bem Vindo! ----------------------------");
    printf("\n|                1 - Cadastrar conta                          |");
    printf("\n|                2 - Excluir conta corrente                   |");
    printf("\n|                3 - Alterar dados da conta corrente          |");
    printf("\n|                4 - Consultar dados da conta                 |");
    printf("\n|                5 - Deposito                                 |");
    printf("\n|                6 - Saque                                    |");
    printf("\n|                7 - consultar saldo                          |");
    printf("\n|                8 - Trasferencia entre contas                |");
    printf("\n|                9 - Dados da ultima movimentacao             |");
    printf("\n|                                                             |");
    printf("\n|               10 - Sair so menu do funcionario              |");
    printf("\n---------------------------------------------------------------");
}



void menucliente()
{
    clear();
    cabecalho();

    printf("\n---------------------------------------------------------------");
    printf("\n----------------------- Bem Vindo! ----------------------------");
    printf("\n|                1 - Deposito                                 |");
    printf("\n|                2 - Saque                                    |");
    printf("\n|                3 - consultar saldo                          |");
    printf("\n|                4 - Trasferencia entre contas                |");
    printf("\n|                5 - Dados da ultima movimentacao             |");
    printf("\n|                                                             |");
    printf("\n|                6 - Sair so menu do cliente                  |");
    printf("\n---------------------------------------------------------------");
}

void clear()
{
#if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
    system("clear");
#endif

#if defined(_WIN32) || defined(_WIN64)
    system("cls");
#endif
}

void aguardaTecla()
{
    getchar();
    fflush(stdin);
}

void addZero(char data[2])
{
    data[1] = data[0];
    data[0] = '0';
}

void depositoCCorrente(int nconta, RegCCorrentePtr Ptrinicial, double deposito)
{
    RegCCorrentePtr Contadestino = obtemCCorrente(nconta, Ptrinicial);
    if (Ptrinicial == NULL)
    {
        printf("Nao ha contas registradas\n");
    }
    else
    {
        if (Contadestino == NULL)
        {
            printf("A conta digitada nao existe\n");
        }
        else
        {
            Contadestino->valorMov = deposito;
            Contadestino->saldoAnterior = Contadestino->saldoAtual;
            dataAtual(Contadestino->DataMov);
            Contadestino->tipoMov = 'D';
            Contadestino->saldoAtual = Contadestino->saldoAtual + deposito;
        }
    }
}

int saqueCCorrente(int nconta, RegCCorrentePtr Ptrinicial, double saque)
{
    RegCCorrentePtr Contadestino;
    if (Ptrinicial == NULL)
    {
        printf("Nao ha contas registradas\n");
    }

    else
    {
        RegCCorrentePtr Contadestino = obtemCCorrente(nconta, Ptrinicial);

        if (Contadestino == NULL)
        {
            printf("A conta digitada nao existe\n");
        }
        else
        {
            if (Contadestino->tipoConta == 'C' && Contadestino->saldoAtual - saque < 0)
            {
                return 0;
            }

            else if (Contadestino->tipoConta == 'E' && Contadestino->saldoAtual - saque < -1000)
            {
                return 0;
            }

            else
            {
                Contadestino->valorMov = saque;
                Contadestino->saldoAnterior = Contadestino->saldoAtual;
                dataAtual(Contadestino->DataMov);
                Contadestino->tipoMov = 'C';

                Contadestino->saldoAtual = Contadestino->saldoAtual - saque;
                return 1;
            }
        }
    }
}

void dataAtual(char data[10])
{
    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // armazena a data na variavel recebida
    sprintf(data, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

RegCCorrentePtr obtemCCorrente(int nconta, RegCCorrentePtr Primeiroptr)
{
    RegCCorrentePtr percorrelista = NULL;

    RegCCorrentePtr anterior = NULL;

    if (Primeiroptr == NULL)
    {
        return NULL;
    }

    else
    {
        percorrelista = Primeiroptr;

        while (percorrelista != NULL)
        {
            if (percorrelista->conta == nconta)
            {

                return percorrelista;
            }
            anterior = percorrelista;
            percorrelista = percorrelista->proxConta;
        }

        return percorrelista;
    }
}

RegCCorrentePtr obtemCCorrenteAnterior(int nconta, RegCCorrentePtr Lista)
{
    RegCCorrentePtr percorrelista = NULL;

    RegCCorrentePtr anterior = NULL;

    if (Lista == NULL)
    {
        return NULL;
    }

    else
    {
        percorrelista = Lista;

        while (percorrelista != NULL)
        {
            if (percorrelista->conta == nconta)
            {

                return anterior;
            }
            anterior = percorrelista;
            percorrelista = percorrelista->proxConta;
        }

        return anterior;
    }
}

RegCCorrentePtr leCCorrente(void)
{
    RegCCorrentePtr NovaConta = malloc(sizeof(RegCCorrente));
    NovaConta->proxConta = NULL;

    dataAtual(NovaConta->Dataabertura);

    printf("Digite o saldo inicial da conta:\n");

    scanf("%lf", &NovaConta->depositoInicial);

    fflush(stdin);
    aguardaTecla();

    NovaConta->tipoMov = 'D';
    dataAtual(NovaConta->DataMov);
    NovaConta->saldoAtual = NovaConta->depositoInicial;
    NovaConta->saldoAnterior = NovaConta->depositoInicial;
    NovaConta->valorMov = NovaConta->depositoInicial;
    if (NovaConta->depositoInicial >= 10000)
        NovaConta->tipoConta = 'E';

    else
        NovaConta->tipoConta = 'C';

    printf("\nNome: ");
    fgets(NovaConta->nome, 40, stdin);

    fflush(stdin);

    printf("\nRg: ");
    fgets(NovaConta->rg, 11, stdin);

    fflush(stdin);

    printf("\nCPF: ");
    fgets(NovaConta->cpf, 13, stdin);

    fflush(stdin);

    printf("\nData de Nascimento: ");
    fgets(NovaConta->nascimento, 10, stdin);

    fflush(stdin);

    printf("\nEscolha uma senha: ");
    fgets(NovaConta->senha, 7, stdin);

    fflush(stdin);

    printf("\nPressione <ENTER> para confirmar");

    return NovaConta;
}

void transfereValor(int nOrigem, int nDestino, double valor, RegCCorrentePtr Lista)
{
    saqueCCorrente(nOrigem, Lista, valor);
    if (saqueCCorrente(nOrigem, Lista, valor) == 0)
    {
        printf("Nao eh possivel fazer a transferencia.\n");
    }
    else
    {
        depositoCCorrente(nDestino, Lista, valor);
    }
}

double saldoAtualCCorrente(int nconta, RegCCorrentePtr Lista)
{
    RegCCorrentePtr ContaDestino;
    if (Lista == NULL)
    {

        return 0;
    }
    else
    {
        RegCCorrentePtr ContaDestino = obtemCCorrente(nconta, Lista);
        if (ContaDestino == NULL)
        {
            return 0;
        }

        else
        {
            return ContaDestino->saldoAtual;
        }
    }
}


void consultaCCorrente(int nconta, RegCCorrentePtr Lista)
{
   RegCCorrentePtr ContaDestino = obtemCCorrente(nconta, Lista);
    if (Lista == NULL)
    {
        printf("Nao ha contas regitradas\n");
    }
    else
    {

        RegCCorrentePtr ContaDestino = obtemCCorrente(nconta, Lista);
        if (ContaDestino == NULL)
        {
            printf("A conta Digitada nao existe\n");
        }
        else
        {

            printf("Banco NOME DO GRUPO DE ALUNOS\n");
            printf("Av. Alberto Carazzai, 1640 - Centro - CEP: 86300-000 - Cornelio Procopio, PR\n");
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Conta Corrente: %d - Tipo: %c\n", ContaDestino->conta, ContaDestino->tipoConta);
            printf("Data de abertura: %s\n", ContaDestino->Dataabertura);
            printf("Nome do cliente: %s      Senha do Cliente: %s\n", ContaDestino->nome,ContaDestino->senha);
            printf("CPF: %s  RG: %s\n", ContaDestino->cpf, ContaDestino->rg);
            printf("Data de nascimento do cliente: %s\n",ContaDestino->nascimento);
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Saldo anterior: R$ %.2lf\n", ContaDestino->saldoAnterior);
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Data Ult. Mov | Tipo Operacao | Valor Movim.\n");
            printf("%s      | %c| %.2lf\n", ContaDestino->DataMov, ContaDestino->tipoMov, ContaDestino->valorMov);
            printf("Saldo atual: R$ %.2lf\n", ContaDestino->saldoAtual);
        }
    }
}
void consultaUltimaMovimentacao(int nconta, RegCCorrentePtr Lista)
{
    RegCCorrentePtr ContaDestino = obtemCCorrente(nconta, Lista);
    if (Lista == NULL)
    {
        printf("Nao ha contas regitradas\n");
    }
    else
    {

        RegCCorrentePtr ContaDestino = obtemCCorrente(nconta, Lista);
        if (ContaDestino == NULL)
        {
            printf("A conta Digitada nao existe\n");
        }
        else
        {

            printf("Banco NOME DO GRUPO DE ALUNOS\n");
            printf("Av. Alberto Carazzai, 1640 - Centro - CEP: 86300-000 - Cornelio Procopio, PR\n");
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Conta Corrente: %d - Tipo: %c\n", ContaDestino->conta, ContaDestino->tipoConta);
            printf("Data atual: %s\n", ContaDestino->Dataabertura);
            printf("Nome do cliente: %s\n", ContaDestino->nome);
            printf("CPF: %s  RG: %s\n", ContaDestino->cpf, ContaDestino->rg);
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Saldo anterior: R$ %.2lf\n", ContaDestino->saldoAnterior);
            printf("--------------------------------------------------------------------------------------------------\n");
            printf("Data Ult. Mov | Tipo Operacao | Valor Movim.\n");
            printf("%s      | %c| %.2lf\n", ContaDestino->DataMov, ContaDestino->tipoMov, ContaDestino->valorMov);
            printf("Saldo atual: R$ %.2lf\n", ContaDestino->saldoAtual);
        }
    }
}

void alteraCCorrente(int nconta, RegCCorrentePtr Lista)
{
    int opt;
    double DepositoAlterado;
    char NomeAlterado[10];
    char senhaAlterada[7];
    char tipoAlterado;
    RegCCorrentePtr ContaDestino;
    if (Lista == NULL)
    {
        printf("Nao ha contas cadastradas\n");
    }

    else
    {
        ContaDestino = obtemCCorrente(nconta, Lista);

        if (ContaDestino == NULL)
        {
            printf("A conta digitada nao existe\n");
        }

        else
        {
            do
            {
                clear();
                cabecalho();

                printf("\n|                1 - Nome do Usuario                         |");
                printf("\n|                2 - Deposito Inicial                        |");
                printf("\n|                3 - Senha do usuario                        |");
                printf("\n|                4 - Tipo da conta do usuario                |");
                printf("\n|                5 - Sair do menu                            |");
                printf("\nDigite qual apecto da conta deseja alterar:\n");
                scanf("%d", &opt);
                fflush(stdin);

                aguardaTecla();

                switch (opt)
                {
                case 1:
                    printf("Digite o novo nome do usuario:\n");
                    fgets(ContaDestino->nome, 40, stdin);
                    fflush(stdin);
                    aguardaTecla();

                    break;

                case 2:
                    printf("Digite o novo deposito inicial:\n");
                    scanf("%lf", &ContaDestino->depositoInicial);
                    fflush(stdin);
                    aguardaTecla();
                    break;
                case 3:
                    printf("Digite a nova senha do usuario:\n");
                    fgets(ContaDestino->senha, 7, stdin);
                    fflush(stdin);
                    aguardaTecla();
                    break;

                case 4:
                    printf("Digite o novo tipo da conta\n");
                    scanf("%c", &tipoAlterado);
                    aguardaTecla();
                    if (tipoAlterado != 'E' && tipoAlterado != 'C')
                    {
                        printf("Tipo de conta invalido\n");
                    }
                    else
                    {
                        ContaDestino->tipoConta = tipoAlterado;
                    }
                    break;

                case 5:
                    printf("Saindo do menu\n");
                    aguardaTecla();
                    break;
                default:
                    printf("Opcao invalida\n");
                    aguardaTecla();
                    break;
                }

            } while (opt != 4);
        }
    }
}
