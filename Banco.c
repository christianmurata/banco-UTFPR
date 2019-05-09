/**
 * Banco de credito - CG Bank
 * O projeto consite em um sistema bancario em que um funcionario previamente
 * cadastrado tem acesso a todas as funcionalidades do sistema, como cadastrar
 * um cliente, por exemplo. O usuário comum (cliente) do sistema tem acesso ao
 * sistema após o cadastro de um numero de conta e senha válidos por parte do
 * funcionário.
 * 
 * funcionalidades do sistema:
 * 
 * @author Gabriel Perino
 * @author Christian Murata
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// dados conta corrente

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
    char nascimento[12];

    struct regCCorrente *proxConta;
};

// cria os tipos de dados de conta corrente

typedef struct regCCorrente RegCCorrente;

typedef RegCCorrente *RegCCorrentePtr;

// Prototipo das funcoes gerais do sistema

void trim();
void clear();
void clear();
void cabecalho();
void limpaBuffer();
void aguardaTecla();
void addZero(char[2]);
void dataAtual(char[10]);

// Prototipo das funcoes menu

void menucliente();
void menufuncionario();

// Prototipo das funcoes de saida de dados

void imprime(RegCCorrentePtr Lista);
void consultaCCorrente(int nconta, RegCCorrentePtr Lista);
void consultaUltimaMovimentacao(int nconta, RegCCorrentePtr Lista);

double saldoAtualCCorrente(int nconta, RegCCorrentePtr Lista);

// Prototipo das funcoes de insercao, alteracao e exclusao de conta

void insereConta(RegCCorrentePtr* Lista);
void alteraCCorrente(int nconta, RegCCorrentePtr Lista);
void excluiCCorrente(RegCCorrentePtr* Lista, int nconta);


// Prototipo das funcoes de movimentacao

int saqueCCorrente(int nconta, RegCCorrentePtr Lista, double saque);

void transfereValor(int nOrigem, int nDestino, double valor, RegCCorrentePtr Lista);
void depositoCCorrente(int nconta, RegCCorrentePtr Lista, double deposito);

// Prototipo das funcoes "auxiliares" para algumas das funcoes acima

int contaLivre(RegCCorrentePtr Lista);

RegCCorrentePtr leCCorrente(void);
RegCCorrentePtr obtemCCorrente(int nconta, RegCCorrentePtr Lista);
RegCCorrentePtr obtemCCorrenteAnterior(int nconta, RegCCorrentePtr Lista);

// prototippo das funcoes de funcionamento do sistema

void inicializa(RegCCorrentePtr);
void liberaMemoria(RegCCorrentePtr);


int main(void)
{
    // inicializa a lista encadeada
    RegCCorrentePtr Lista = NULL;

    inicializa(Lista);
    liberaMemoria(Lista);

    return 0;
}

/**
 * Inicializa o fluxo de execucao do programa
 * 
 * @param {RegCCorrentePtr} Lista
*/
void inicializa(RegCCorrentePtr Lista){
    int opt;
    char data[10];
    char senhaFuncionario[7] = "987654";
    char senhalida[7];
    int contateste;

    do
    {
        clear();
        cabecalho();

        printf("Bem Vindo ao sistema do CG BANK!\n");
        printf("Digite um numero de conta valido:\n");
        scanf("%d", &contateste);
        
        limpaBuffer();

        aguardaTecla();

        if (contateste == 0)
        {

            clear();
            cabecalho();

            printf("Digite sua senha de funcionario(a)\n");
            fgets(senhalida, 7, stdin);
            
            limpaBuffer();

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
                    
                    limpaBuffer();


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
                fgets(senhalida, sizeof(senhalida), stdin);

                trim(senhalida);

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
                        
                        limpaBuffer();


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
}

/**
 * Verifica qual e o proximo numero de conta livre na lista e o retorna
 * 
 * @param  {RegCCorrentePtr} contaAtual
 * @return {int} numeroConta
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

    printf("Digite o saldo inicial da conta:\n");

    scanf("%lf", &NovaConta->depositoInicial);

    limpaBuffer();

    dataAtual(NovaConta->Dataabertura);
    dataAtual(NovaConta->DataMov);

    NovaConta->tipoMov       = 'D';
    NovaConta->valorMov      = NovaConta->depositoInicial;
    NovaConta->saldoAtual    = NovaConta->depositoInicial;
    NovaConta->saldoAnterior = NovaConta->depositoInicial;

    if (NovaConta->depositoInicial >= 10000)
        NovaConta->tipoConta = 'E';

    else
        NovaConta->tipoConta = 'C';

    printf("\nNome: ");
    fgets(NovaConta->nome, sizeof(NovaConta->nome), stdin);

    trim(NovaConta->nome);

    limpaBuffer();

    printf("\nRg: ");
    fgets(NovaConta->rg, sizeof(NovaConta->rg), stdin);

    trim(NovaConta->rg);

    limpaBuffer();

    printf("\nCPF: ");
    fgets(NovaConta->cpf, sizeof(NovaConta->cpf), stdin);

    trim(NovaConta->cpf);

    limpaBuffer();

    printf("\nData de Nascimento: ");
    fgets(NovaConta->nascimento, sizeof(NovaConta->nascimento), stdin);

    trim(NovaConta->nascimento);

    limpaBuffer();

    printf("\nEscolha uma senha: ");
    fgets(NovaConta->senha, sizeof(NovaConta->senha), stdin);

    trim(NovaConta->senha);

    limpaBuffer();

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

            printf("Banco Christian e Gabriel \n");
            printf("Av. Alberto Carazzai, 1640 - Centro - CEP: 86300-000 - CP, PR  \n");
            printf("---------------------------------------------------------------\n");            
            printf("Conta Corrente: %d - Tipo: %c\n", ContaDestino->conta, ContaDestino->tipoConta);
            printf("Data atual: %s\n", ContaDestino->Dataabertura);
            printf("Nome do cliente: %s\n", ContaDestino->nome);
            printf("CPF: %s  RG: %s\n", ContaDestino->cpf, ContaDestino->rg);
            printf("---------------------------------------------------------------\n");
            printf("Saldo anterior: R$ %.2lf\n", ContaDestino->saldoAnterior);
            printf("---------------------------------------------------------------\n");            
            printf("Data Ult. Mov | Tipo Operacao | Valor Movim.\n");
            printf("%s      | %c             | %.2lf\n", ContaDestino->DataMov, ContaDestino->tipoMov, ContaDestino->valorMov);
            printf("---------------------------------------------------------------\n");            
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
                
                limpaBuffer();

                aguardaTecla();

                switch (opt)
                {
                    case 1:
                        printf("Digite o novo nome do usuario:\n");
                        fgets(ContaDestino->nome, 40, stdin);
                        limpaBuffer();                    
                        aguardaTecla();

                        break;

                    case 2:
                        printf("Digite o novo deposito inicial:\n");
                        scanf("%lf", &ContaDestino->depositoInicial);
                        limpaBuffer();
                        aguardaTecla();
                        break;
                    case 3:
                        printf("Digite a nova senha do usuario:\n");
                        fgets(ContaDestino->senha, 7, stdin);
                        limpaBuffer();                    
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

void dataAtual(char data[10])
{
    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // armazena a data na variavel recebida
    sprintf(data, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
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
    limpaBuffer();
}

void limpaBuffer(){
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
}

/**
 * Funcao que remove as quebras de linha ('\n') lidas pelo fgets da string, ou 
 * seja, substitui '\n' por '\0'
 * 
 * strcspn(str1, str2): encontra a primeira ocorrencia de qualquer caracter de
 * str2 em str1 
 * 
 * @param {string} str
*/
void trim(char str[]){
    str[strcspn(str, "\n")] = 0;
}

/**
 * Desaloca os espacos de memoria alocados dinamicamicamente durante toda a 
 * execucao do programa principal
 * 
 * @param {RegCCorrentePtr} Lista
*/
void liberaMemoria(RegCCorrentePtr Lista){
    if(Lista != NULL){
        RegCCorrentePtr conta     = Lista;
        RegCCorrentePtr proxConta = conta->proxConta;

        free(conta);

        liberaMemoria(proxConta);
    }
}
