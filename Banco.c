/**
 * Banco de credito - CG Bank
 * O projeto consite em um sistema bancario em que um funcionario previamente
 * cadastrado tem acesso a todas as funcionalidades do sistema, como cadastrar
 * um cliente, por exemplo. O usuário comum (cliente) do sistema tem acesso ao
 * sistema após o cadastro de um numero de conta e senha válidos por parte do
 * funcionário.
 * 
 * funcionalidades do sistema:
 * I  ) Cadastrar uma conta corrente
 * II ) Excluir uma conta corrente
 * III) Alterar dados de uma conta corrente
 * IV ) Consultar dados de uma conta corrente
 * V  ) Realizar um deposito em uma conta corrente
 * VI ) Realizar um saque em uma conta corrente
 * VII) Consultar o saldo de uma conta corrente
 * VII) Realizar a movimentacao entre duas contas correntes
 * IX ) Consultar os dados da ultima movimentacao
 * @author Gabriel Perino  R.A. :2101360
 * @author Christian Murata R.A.:
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

void insereConta(RegCCorrentePtr *Lista);
void alteraCCorrente(int nconta, RegCCorrentePtr Lista);
void excluiCCorrente(RegCCorrentePtr *Lista, int nconta);

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
void inicializa(RegCCorrentePtr Lista)
{
    int opt;
    char data[10];
    char senhaFuncionario[7] = "987654";
    char senhalida[7];
    int contalida;
    int contaParametro1;
    int contaParametro2;
    double valorlido;

    do
    {
        cabecalho();

        printf("\nBem Vindo ao sistema do CG BANK!");
        printf("\nDigite um numero de conta valido: ");
        scanf("%d", &contalida);

        limpaBuffer();

        if (contalida == 0)
        {
            cabecalho();

            printf("\nDigite sua senha de funcionario(a): ");
            fgets(senhalida, sizeof(senhalida), stdin);

            limpaBuffer();

            if (strcmp(senhaFuncionario, senhalida) == 0)
            {
                do
                {
                    // imprime o menu de selecao
                    menufuncionario();

                    printf("\nDigite sua opcao: ");
                    scanf("%d", &opt);

                    switch (opt)
                    {
                    // cadastrar
                    case 1:
                        cabecalho();

                        insereConta(&Lista);

                        break;

                    // excluir
                    case 2:
                        cabecalho();
                        printf("\nDigite a conta que deseja deletar:");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        excluiCCorrente(&Lista, contaParametro1);

                        break;

                    // Altera dados da conta
                    case 3:
                        cabecalho();
                        printf("\nDigite a conta que deseja alterar: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        alteraCCorrente(contaParametro1, Lista);

                        break;

                    // Consulta uma conta selecionada
                    case 4:
                        cabecalho();
                        printf("\nDigite a conta que deseja consultar: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        consultaCCorrente(contaParametro1, Lista);

                        break;

                    //Deposito em uma Conta Corrente
                    case 5:
                        cabecalho();

                        printf("\nDigite a conta que ira relizar o deposito: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        if (obtemCCorrente(contaParametro1, Lista) == NULL)
                        {
                            printf("A conta digitada nao existe\n");
                        }

                        else
                        {
                            printf("\nDigite o valor do deposito: ");
                            scanf("%lf", &valorlido);
                            limpaBuffer();
                            depositoCCorrente(contaParametro1, Lista, valorlido);
                        }
                        break;

                    //Saque de uma Conta Corrente
                    case 6:
                        cabecalho();

                        printf("\nDigite a conta que ira relizar o saque: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();
                        if (obtemCCorrente(contaParametro1, Lista) == NULL)
                        {
                            printf("A conta digitada nao existe\n");
                        }
                        else
                        {
                            printf("\nDigite o valor do saque: ");
                            scanf("%lf", &valorlido);
                            limpaBuffer();

                            if (!saqueCCorrente(contaParametro1, Lista, valorlido))
                                printf("\nNao e possivel o realizar o saque!");

                            else
                                printf("\nSaque realizado com sucesso!");
                        }
                        break;

                    //Verifica saldo atual
                    case 7:
                        cabecalho();

                        printf("\nDigite a conta a qual deseja verificar o saldo atual: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        if (saldoAtualCCorrente(contaParametro1, Lista) == 0)
                        {
                            printf("Nao foi possivel encontrar a conta\n");
                        }
                        else
                        {
                            printf("O Saldo atual da conta eh de: %.2lf", saldoAtualCCorrente(contaParametro1, Lista));
                        }

                        break;

                    //transferencia entre duas contas
                    case 8:
                        cabecalho();

                        printf("\nDigite a conta origem da transferencia: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();
                        if (obtemCCorrente(contaParametro1, Lista) == NULL)
                        {
                            printf("A conta digitada nao existe\n");
                        }

                        else
                        {

                            printf("\nDigite a conta destino da transferencia: ");
                            scanf("%d", &contaParametro2);
                            limpaBuffer();
                            if (obtemCCorrente(contaParametro2, Lista) == NULL)
                            {
                                printf("A conta digitada nao existe\n");
                            }
                            else
                            {
                                printf("\nDigite o valor da transferencia: ");
                                scanf("%lf", &valorlido);
                                limpaBuffer();
                                transfereValor(contaParametro1, contaParametro2, valorlido, Lista);
                            }
                        }

                        break;

                    //consulta a ultimamovimentacao da conta
                    case 9:
                        cabecalho();
                        printf("\nDigite a conta que deseja verificar: ");
                        scanf("%d", &contaParametro1);
                        limpaBuffer();

                        consultaUltimaMovimentacao(contaParametro1, Lista);

                        break;

                    // sair
                    case 10:
                        limpaBuffer();
                        // printf("\nPressione qualquer tecla para Sair do menu");
                        break;

                    case 11:
                        cabecalho();
                        limpaBuffer();
                        imprime(Lista);
                        break;

                    default:
                        printf("Opcao invalida");
                        limpaBuffer();
                        break;
                    }

                    aguardaTecla();

                } while (opt != 10);

                clear();
            }

            else
            {
                printf("Senha incorreta!\n");
                aguardaTecla();
            }
        }

        else if (contalida == -1)
        {
            cabecalho();
            printf("\n------ Obrigado por utilizar nosso sistema! -------");
            aguardaTecla();
        }

        else if (contalida > 0)
        {

            RegCCorrentePtr contadestino = obtemCCorrente(contalida, Lista);
            if (contadestino == NULL)
            {

                printf("A conta digita nao existe\n");
                aguardaTecla();
            }

            else
            {
                cabecalho();

                printf("\nDigite a senha da sua conta de usuario: ");
                fgets(senhalida, sizeof(senhalida), stdin);

                limpaBuffer();
                trim(senhalida);

                if (strcmp(contadestino->senha, senhalida) == 0)
                {
                    do
                    {
                        menucliente();

                        printf("\nDigite sua opcao: ");
                        scanf("%d", &opt);
                        limpaBuffer();

                        switch (opt)
                        {
                        // deposito do usuario
                        case 1:
                            cabecalho();
                            printf("\nDigite o valor que deseja depositar: ");
                            scanf("%lf", &valorlido);
                            limpaBuffer();
                            depositoCCorrente(contalida, Lista, valorlido);

                            break;

                        // saque do usuario
                        case 2:
                            cabecalho();
                            printf("\nDigite o valor que deseja sacar: ");
                            scanf("%lf", &valorlido);
                            limpaBuffer();

                            if (!saqueCCorrente(contalida, Lista, valorlido))
                                printf("\nNao e possivel o realizar o saque!");

                            else
                                printf("\nSaque realizado com sucesso!");

                            break;

                        //cosulta de saldo do usuario
                        case 3:
                            cabecalho();

                            if (saldoAtualCCorrente(contalida, Lista) == 0)
                            {
                                printf("Nao foi possivel encontrar a conta\n");
                            }
                            else
                            {
                                printf("O Saldo atual da conta eh de: %.2lf", saldoAtualCCorrente(contalida, Lista));
                            }

                            break;

                        // transferencia do usuario
                        case 4:
                            cabecalho();
                            printf("\nDigite a conta para a qual deseja tranferir: ");
                            scanf("&d", &contaParametro1);
                            limpaBuffer();
                            if (obtemCCorrente(contaParametro1, Lista) == NULL)
                            {
                                printf("A conta digitada nao existe\n");
                            }
                            else
                            {
                                printf("\nDigite o valor que deseja transferir: ");
                                scanf("%lf", &valorlido);
                                limpaBuffer();
                                transfereValor(contalida, contaParametro1, valorlido, Lista);
                            }

                            break;

                        // Consulta da ultima movimentacao do usuario
                        case 5:
                            cabecalho();
                            consultaUltimaMovimentacao(contalida, Lista);

                            break;

                        // sair
                        case 6:
                            // printf("\nSaindo do menu");

                            break;

                        default:
                            printf("Opcao invalida");

                            break;
                        }

                        aguardaTecla();

                    } while (opt != 6);
                }

                else
                {
                    printf("A senha digita esta incorreta\n");
                    aguardaTecla();
                }
            }
        }

    } while (contalida != -1);
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

    
    RegCCorrentePtr contaPtrAux = contaAtual;

    // primeiro numero conta verificado
    int numeroConta = 1;

    do
    {
        // nao eh possivel cadastrar mais nenhuma conta
        // lista cheia
        if (numeroConta >= 999)
        {
            return -1;
        }

        // numero da conta nao disponivel
        // verifica o proximo numero de conta
        if (contaPtrAux->conta == numeroConta)
        {
            numeroConta++;
            
        }

        // proxima conta na lista
        contaPtrAux = contaPtrAux->proxConta;

    } while (contaPtrAux != NULL);

    return numeroConta;
}

/**
 * Insere uma conta em uma lista simplesmente encadeada
 * 
 * @param {RegCCorrentePtr} *Lista
 * 
 * */

void insereConta(RegCCorrentePtr *Lista)
{
    RegCCorrentePtr novaConta; //Nova conta a ser criada

    RegCCorrentePtr Contaatual;

    RegCCorrentePtr Contaanterior;

    int verificaNconta; // Inteiro que eh usado na verificacao de contas disponiveis

    //Verifica se existe memoria disponivel
    if (novaConta != NULL)
    {

        // Gera do numero da conta
        verificaNconta = contaLivre(*Lista);

        if (verificaNconta == -1)
        {
            printf("Impossivel cadastrar mais clientes\n");
            aguardaTecla();
        }

        else
        {
            novaConta = leCCorrente(); //Le os dados de uma conta
            novaConta->conta = verificaNconta;
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

            printf("\nConta cadastrada com sucesso!");
        }
    }

    else //caso nao houver memoria
    {
        printf("Impossivel cadastrar mais clientes\n");
    }
}

/**
 * Exclui uma determinda conta corrente dada o seu numero
 * 
 * @param {RegCCorrentePtr} *Lista
 * 
 * */

void excluiCCorrente(RegCCorrentePtr *Lista, int nconta)
{

    RegCCorrentePtr Contadestino;
    RegCCorrentePtr Contaanterior;
    RegCCorrentePtr lixo;

    if (*Lista == NULL) //Caso da lista estar vazia
    {
        printf("Nao ha contas registradas");
        return;
    }
    else
    {
        Contadestino = obtemCCorrente(nconta, *Lista);
        Contaanterior = obtemCCorrenteAnterior(nconta, *Lista);
        if (Contadestino != NULL)
        {

            //Deleta primeira conta da lista
            if (nconta == (*Lista)->conta)

            {
                RegCCorrentePtr aux;
                aux = *Lista;
                *Lista = (*Lista)->proxConta;

                free(aux);
            }

            // Deleta a conta caso ela nao esteja no comeco da lista
            else if (Contadestino != NULL)
            {
                lixo = Contadestino;
                Contaanterior->proxConta = Contadestino->proxConta;
                free(lixo);
            }
        }

        else
        {
            cabecalho();
            printf("A conta digitada nao existe\n");
        }
    }
}

/**
 * Realiza o deposito em uma conta corrente dado o seu numero e o valor do deposito
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * @param {double} deposito
 * */

void depositoCCorrente(int nconta, RegCCorrentePtr Lista, double deposito)
{
    RegCCorrentePtr Contadestino = obtemCCorrente(nconta, Lista);

    if (Lista == NULL)
    {
        printf("Nao ha contas registradas\n");
    }
    else
    {
        if (Contadestino == NULL)
        {
            printf("A conta digitada nao existe!\n");
        }
        else
        {
            Contadestino->valorMov = deposito;
            Contadestino->saldoAnterior = Contadestino->saldoAtual;
            dataAtual(Contadestino->DataMov);
            Contadestino->tipoMov = 'D';
            Contadestino->saldoAtual = Contadestino->saldoAtual + deposito;

            printf("\nDeposito realizado com sucesso!");
        }
    }
}

/**
 * Realiza o saque em uma conta corrente dado o seu numero e o valor do saque
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * @param {double} saque
 * */

int saqueCCorrente(int nconta, RegCCorrentePtr Lista, double saque)
{
    RegCCorrentePtr Contadestino;
    if (Lista == NULL)
    {
        printf("Nao ha contas registradas\n");
        return 0;
    }

    else
    {
        RegCCorrentePtr Contadestino = obtemCCorrente(nconta, Lista);

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

/**
 * Percorre a lista encadeada ate encontrar a conta com o numero digitado
 * Caso nao encontre a conta digitada retorna NULL
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * 
 * @return {RegCCorrentePtr} percorrelista se encontrar a conta
 * @return NULL se nao encontar a conta 
 * */

RegCCorrentePtr obtemCCorrente(int nconta, RegCCorrentePtr Lista)
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

                return percorrelista;
            }
            anterior = percorrelista;
            percorrelista = percorrelista->proxConta;
        }

        return percorrelista;
    }
}

/**
 * Percorre a lista encadeada ate encontrar a conta que se encontra na posicao anterior da conta digitada
 * Caso nao encontre a conta anterior retorna NULL
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * 
 * @return {RegCCorrentePtr} anterior se encontrar a conta
 * @return NULL se nao encontar a conta 
 * */

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

/**
 * 
 * Funcao que permite a leitura dos dados
 * de uma conta corrente
 * 
 * Tambem aloca a memoria necessaria para conta
 * a ser lida
 * 
 * 
 * */

RegCCorrentePtr leCCorrente(void)
{
    RegCCorrentePtr NovaConta = malloc(sizeof(RegCCorrente));
    NovaConta->proxConta = NULL;

    printf("\nDigite o saldo inicial da conta: ");

    scanf("%lf", &NovaConta->depositoInicial);

    limpaBuffer();

    dataAtual(NovaConta->Dataabertura);
    dataAtual(NovaConta->DataMov);

    NovaConta->tipoMov = 'D';
    NovaConta->valorMov = NovaConta->depositoInicial;
    NovaConta->saldoAtual = NovaConta->depositoInicial;
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

    // printf("\nPressione <ENTER> para confirmar");

    return NovaConta;
}

void transfereValor(int nOrigem, int nDestino, double valor, RegCCorrentePtr Lista)
{

    if (Lista == NULL)
    {
        printf("Nao ha contas registradas\n");
    }

    else
    {

        if (!saqueCCorrente(nOrigem, Lista, valor))
        {
            printf("Nao e possivel fazer a transferencia.\n");
        }
        else
        {
            depositoCCorrente(nDestino, Lista, valor);
        }
    }
}

/**
 * Funcao que retorna o valor do saldo de uma conta dado o seu numero
 * 
 * Caso a conta com o numero especificado nao seja encontrada retorna 0
 * 
 * @param{int} nconta
 * @param{RegCCorrentePtr} Lista
 * 
 * 
 * @return {double} Contadestino->saldo se encontrar a  conta
 * @return {double} 0 se nao encontar a conta
 * 
 * */

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

/**
 * Funcao que imprime os dados de uma conta corrente dado o seu numero
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * 
 * */

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
            cabecalho();

            printf("Banco Christian e Gabriel\n");
            printf("Av. Alberto Carazzai, 1640 - Centro - CEP: 86300-000 - CP, PR\n");
            printf("---------------------------------------------------------------\n");
            printf("Conta Corrente: %d - Tipo: %c\n", ContaDestino->conta, ContaDestino->tipoConta);
            printf("Data de abertura: %s\n", ContaDestino->Dataabertura);
            printf("Nome do cliente: %s      Senha do Cliente: %s\n", ContaDestino->nome, ContaDestino->senha);
            printf("CPF: %s  RG: %s\n", ContaDestino->cpf, ContaDestino->rg);
            printf("Data de nascimento do cliente: %s\n", ContaDestino->nascimento);
            printf("---------------------------------------------------------------\n");
            printf("Saldo anterior: R$ %.2lf\n", ContaDestino->saldoAnterior);
            printf("---------------------------------------------------------------\n");
            printf("Data Ult. Mov | Tipo Operacao | Valor Movim.\n");
            printf("%s      | %c| %.2lf\n", ContaDestino->DataMov, ContaDestino->tipoMov, ContaDestino->valorMov);
            printf("Saldo atual: R$ %.2lf\n", ContaDestino->saldoAtual);
        }
    }
}

/**
 * 
 * Funcao que imprime os dados da ultima movimentacao de uma conta
 * quando se eh dado o seu numero
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr} Lista
 * 
 * */

void consultaUltimaMovimentacao(int nconta, RegCCorrentePtr Lista)
{
    char Dataatual[10];

    dataAtual(Dataatual);
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
            cabecalho();

            printf("Banco Christian e Gabriel \n");
            printf("Av. Alberto Carazzai, 1640 - Centro - CEP: 86300-000 - CP, PR  \n");
            printf("---------------------------------------------------------------\n");
            printf("Conta Corrente: %d - Tipo: %c\n", ContaDestino->conta, ContaDestino->tipoConta);
            printf("Data atual: %s\n", Dataatual);
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

/**
 * 
 * Funcao que permite alterar os dados de uma conta corrente
 * quando se eh fornecido o seu numero
 * 
 * @param {int} nconta
 * @param {RegCCorrentePtr}
 * */

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
        printf("Nao ha contas registradas\n");
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
                cabecalho();

                printf("|                1 - Nome do Usuario                         |\n");
                printf("|                2 - Deposito Inicial                        |\n");
                printf("|                3 - Senha do usuario                        |\n");
                printf("|                4 - Tipo da conta do usuario                |\n");
                printf("|                5 - Sair do menu                            |\n");
                printf("--------------------------------------------------------------\n");
                printf("Digite qual aspecto da conta deseja alterar: ");
                scanf("%d", &opt);

                limpaBuffer();

                switch (opt)
                {
                case 1:
                    printf("\nDigite o novo nome do usuario: ");
                    fgets(ContaDestino->nome, 40, stdin);
                    limpaBuffer();

                    break;

                case 2:
                    printf("\nDigite o novo deposito inicial: ");
                    scanf("%lf", &ContaDestino->depositoInicial);
                    limpaBuffer();

                    break;
                case 3:
                    printf("\nDigite a nova senha do usuario: ");
                    fgets(ContaDestino->senha, 7, stdin);
                    limpaBuffer();

                    break;

                case 4:
                    printf("\nDigite o novo tipo da conta: ");
                    scanf("%c", &tipoAlterado);

                    limpaBuffer();

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

                    break;

                default:
                    printf("Opcao invalida\n");

                    break;
                }

                // aguardaTecla();

            } while (opt != 5);
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

/**
 * Funcao que exibe o cabecalho do projeto
 * */

void cabecalho()
{
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

/**
 * 
 * Funcao que exibe as opcoes do menu do funcionario
 * 
 * 
 * */

void menufuncionario()
{
    clear();
    cabecalho();

    // printf("---------------------------------------------------------------\n");
    printf("----------------------- Bem Vindo! ----------------------------\n");
    printf("|                1 - Cadastrar conta                          |\n");
    printf("|                2 - Excluir conta corrente                   |\n");
    printf("|                3 - Alterar dados da conta corrente          |\n");
    printf("|                4 - Consultar dados da conta                 |\n");
    printf("|                5 - Deposito                                 |\n");
    printf("|                6 - Saque                                    |\n");
    printf("|                7 - consultar saldo                          |\n");
    printf("|                8 - Trasferencia entre contas                |\n");
    printf("|                9 - Dados da ultima movimentacao             |\n");
    printf("|                                                             |\n");
    printf("|               10 - Sair so menu do funcionario              |\n");
    printf("---------------------------------------------------------------\n");
}

/**
 * 
 * Funcao que exibe as opcoes do menu do cliente
 * 
 * */

void menucliente()
{
    clear();
    cabecalho();

    // printf("---------------------------------------------------------------\n");
    printf("----------------------- Bem Vindo! ----------------------------\n");
    printf("|                1 - Deposito                                 |\n");
    printf("|                2 - Saque                                    |\n");
    printf("|                3 - consultar saldo                          |\n");
    printf("|                4 - Trasferencia entre contas                |\n");
    printf("|                5 - Dados da ultima movimentacao             |\n");
    printf("|                                                             |\n");
    printf("|                6 - Sair so menu do cliente                  |\n");
    printf("---------------------------------------------------------------\n");
}

void dataAtual(char data[10])
{
    // get data atual
    time_t date = time(NULL);
    struct tm tm = *localtime(&date);

    // armazena a data na variavel recebida
    sprintf(data, "%d/%d/%d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

/**
 * 
 * Funcao que define o comando de limpeza de tela
 * Explica aqui christian kkkk
 * */

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
    printf("\n\n                 Pressione <ENTER> para continuar            ");

    getchar();
    limpaBuffer();
}

void limpaBuffer()
{
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
void trim(char str[])
{
    str[strcspn(str, "\n")] = 0;
}

/**
 * Desaloca os espacos de memoria alocados dinamicamicamente durante toda a 
 * execucao do programa principal
 * 
 * @param {RegCCorrentePtr} Lista
*/
void liberaMemoria(RegCCorrentePtr Lista)
{
    if (Lista != NULL)
    {
        RegCCorrentePtr conta = Lista;
        RegCCorrentePtr proxConta = conta->proxConta;

        free(conta);

        liberaMemoria(proxConta);
    }
}
