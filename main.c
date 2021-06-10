#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
//======    CONSTANTES  ================
#define N_CONDOMINIO 4
#define N_PREDIO 3
#define N_APT 3
/************************************************/

//======    ESTRUTURAS  ================

typedef struct
{
    int idApt;
    char porta[5];
    int andar;
    char dono[50];
    int estado;
    float preco;
    char tipologia[5];

} Apartamento;

typedef struct
{
    char indentificador; // nome do predio vai ser as letras do alfabeto
    int id;
    Apartamento apartamento[N_APT];
    //int ativo;

} Predio;

typedef struct
{
    char nomeCond[50];
    Predio predio[N_PREDIO];
    char cidade[50];
    int ativo;
    int id;
} Condominio;
Condominio condominio[N_CONDOMINIO];
/************************************************/

//======    PROTOTIPOS  ==========

// FUNCOES ECENCIAS
void cadastrarCond();
void cadastrarApt(int i, int j);


void iniciar();
void listaApt();
void listarCond();
void listarPredio();
void pegarDadosCond();
void pegarDadosApt();
void pesquisarCond();
void pesquisarApt();
void editarCond();
void editarApt();
void eliminarCond();
void eliminarApt();
// funcoes de auxilio
int localizaPredio(char c);
void concatenar_LetraString(char texto[], char letra); // tive de concatenar o valor da
int letraM(char ch);

//  FUNCOES auto incrementaveis
void ai_indet_Predio(int n);
void aiPorta(int i, int j, int k);
void ai_Andar(int i, int j, int k);
void ai_Preco(int i, int j, int k);

/************************************************/

//======    VARIAVEIS GLOBAIS  ========

FILE *ficheiro;

/************************************************/

/*************************************************************************/
/*************************************************************************/
int main(int argc, char const *argv[])
{
    int i;
    setlocale(LC_ALL, "portuguese");
    system("cls");
    system("color 3F");
    iniciar();
    pegarDadosCond();
    pegarDadosApt();

    menu();

    putchar('\n');
    system("pause");
    return 0;
}
/******************************************************************************************/
/******************************************************************************************/

//============    FUNCOeS  ================

void iniciar()
{

    register int i, j, k;
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        condominio[i].ativo = 0;

        // condominio[i].id = i;
        ai_indet_Predio(i);

        for (j = 0; j < N_PREDIO; j++)
        {
            condominio[i].predio[j].id = j;
            for (k = 0; k < N_APT; k++)
            {
                condominio[i].predio[j].apartamento[k].estado = 0;
                condominio[i].predio[j].apartamento[k].idApt = k;
                condominio[i].predio[j].apartamento[k].dono[0] = '\0';
            }
        }
    }
}
int verificar()
{
    int i;
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 0)
        {
            return i;
        }
        else if (i == N_CONDOMINIO)
        {
            return -1;
        }
    }
}

int verificarApt()
{
    int i, j;
    register int k;
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {
            for (j = 0; j < N_PREDIO; j++)
            {
                for (k = 0; k < N_APT; k++)
                {
                    if (condominio[i].predio[j].apartamento[k].estado == 0)
                    {
                        return k;
                    }
                    else if (k == N_APT)
                    {
                        return -1;
                    }
                }
            }
        }
    }
}

void cadastrarCond()
{
    system("cls");
    int op, i, existe = 0;
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {
            existe++;
        }
    }
    if (existe != N_CONDOMINIO)
    {

        for (i = 0; i < N_CONDOMINIO; i++)
        {

            system("cls");
            listarCond();
            printf("\n------\tCADASTRAR CONDOMINIOS\t------");
            int cad = verificar();
            condominio[i].id = cad;
            printf("\nID do condominio: %d ", condominio[i].id);
            printf("\nDigite o nome do condominio: ");
            fflush(stdin);
            gets(condominio[i].nomeCond);
            condominio[i].ativo = 1;

            printf("\nDigite cidade: ");
            fflush(stdin);
            gets(condominio[i].cidade);

            if ((i + 1) == N_CONDOMINIO)
            {

                printf("\nExcedeu o numero Maximo de Condominios que podem ser adicionados\n");
                system("pause");
                break;
            }
            else
            {
                printf("\n1-continuar\n0-sair\nDigite: ");
                fflush(stdin);
                scanf(" %d", &op);
                if (op == 0)
                {
                    break;
                }
            }
        }
        if ((ficheiro = fopen("condominio.txt", "w")) != NULL)
        {
            int i;
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if (condominio[i].ativo == 1)
                {
                    fprintf(ficheiro, "%d %s %s %d\n", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade, condominio[i].ativo);
                }
            }
            printf("\nDADOS SALVOS COM SUCESSO \n");
            fclose(ficheiro);
        }
    }
    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
    system("pause");
}
//Menu Principal
void menu()
{
    int op, a, b, op2;
    do
    {
        system("cls");
        printf("\n==========\t MENU PRINCIPAL \t==========\n");
        printf("\n (1) - Menu Cadastrar ");
        printf("\n (2) - Menu Editar ");
        printf("\n (3) - Menu Liminar ");
        printf("\n (4) - Menu Listar");
        printf("\n (5) - Menu Pesquisar");
        printf("\n (0) - Sair do Programa");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        scanf(" %d", &op);
        printf("\n========================================\n ");
        switch (op)
        {
        case 1:
        {
            do
            {
                system("cls");
                printf("\n==========\t MENU CADASTRAR \t==========\n");
                printf("\n (1) - Cadastrar Condominios");
                printf("\n (2) - Cadastrar Apartamentos ");
                printf("\n (0) - Voltar ao Menu Principal ");
                printf("\n DIGITE AQUI: ");
                fflush(stdin);
                scanf(" %d", &op2);
                switch (op2)
                {
                case 1:
                    cadastrarCond();
                    break;
                case 2:

                    cadastrarApt(a, b);
                    break;
                }
            } while (op2 != 0);
            break;
        }
        case 2:
        {
            do
            {
                system("cls");
                printf("\n==========\t MENU EDITAR \t==========\n");
                printf("\n (1) - Editar Condominios");
                printf("\n (2) - Editar Apartamentos ");
                printf("\n (0) - Voltar ao Menu Principal ");
                printf("\n DIGITE AQUI: ");
                fflush(stdin);
                scanf(" %d", &op2);
                switch (op2)
                {
                case 1:
                    editarCond();
                    break;
                case 2:

                    editarApt();
                    break;
                }
            } while (op2 != 0);
            break;
        }

        case 3:
        {
            do
            {
                system("cls");
                printf("\n==========\t MENU ELIMINAR \t==========\n");
                printf("\n (1) - Eliminar Condominios");
                printf("\n (2) - Eliminar Apartamentos ");
                printf("\n (0) - Voltar ao Menu Principal ");
                printf("\n DIGITE AQUI: ");
                fflush(stdin);
                scanf(" %d", &op2);
                switch (op2)
                {
                case 1:
                    eliminarCond();
                    break;
                case 2:

                    eliminarApt();
                    break;
                }
            } while (op2 != 0);
            break;
        }
        case 4:
        {
            do
            {
                system("cls");
                printf("\n==========\t MENU LISTAR \t==========\n");
                printf("\n (1) - Listar Condominios ");
                printf("\n (2) - Listar Predios ");
                printf("\n (3) - Listar Apartamentos");
                printf("\n (0) - Voltar ao Menu Principal ");
                printf("\n DIGITE AQUI: ");
                fflush(stdin);
                scanf(" %d", &op2);

                switch (op2)
                {
                case 1:
                    listarCond();
                    break;
                case 2:
                    listarPredio();
                    break;
                case 3:
                    listaApt();
                    break;
                }
            } while (op2 != 0);
            break;
        }

        case 5:
        {
            do
            {
                system("cls");
                printf("\n==========\t MENU PESQUISAR \t==========\n");
                printf("\n (1) - Pesquisar por Condominios");
                printf("\n (2) - Pesquisar por Apartamentos ");
                printf("\n (0) - Voltar ao Menu Principal ");
                printf("\n DIGITE AQUI: ");
                fflush(stdin);
                scanf(" %d", &op2);
                switch (op2)
                {
                case 1:
                    pesquisarCond();
                    break;
                case 2:

                    pesquisarApt();
                    break;
                }
            } while (op2 != 0);
            break;
        }
        }
    } while (op != 0);
}

void cadastrarApt(int i, int j)
{
    int op;
    do
    {
        system("cls");
        listarPredio();
        int cadApt = verificarApt();
        char c;

        printf("\n==========\t CADASTRAR APARTAMENTOS \t==========\n");
        printf("\nDigite Id do condomino: ");
        fflush(stdin);
        scanf(" %d", &i);
        printf("\ndigite a Letra do predio: ");
        fflush(stdin);
        c = getchar();
        c = letraM(c);
        j = localizaPredio(c);
        printf("\nCondominio: %s", condominio[i].nomeCond);
        printf("\nPredio: %c", condominio[i].predio[j].indentificador);
        printf("\nDigte Dono: ");
        fflush(stdin);
        gets(condominio[i].predio[j].apartamento[cadApt].dono);

        condominio[i].predio[j].apartamento[cadApt].estado = 1;
        aiPorta(i, j, cadApt);
        ai_Andar(i, j, cadApt);
        printf("\nDigite a tipologia: ");
        fflush(stdin);
        gets(condominio[i].predio[j].apartamento[cadApt].tipologia);
        ai_Preco(i, j, cadApt);
        printf("\n-------------------------------------------\n ");
        printf("\n1-continuar\n0-sair\nDigite: ");
        fflush(stdin);
        scanf(" %d", &op);
    } while (op != 0);

    if ((ficheiro = fopen("apartamento.txt", "w")) != NULL)
    {
        int i, j, k;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {

                for (j = 0; j < N_PREDIO; j++)
                {

                    for (k = 0; k < N_APT; k++)
                    {
                        
                        if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                        {
                            fprintf(ficheiro, "%d ", condominio[i].id);
                            fprintf(ficheiro, "%c ", condominio[i].predio[j].indentificador);
                            fprintf(ficheiro, "%s %s %f %d %s %d\n", condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].preco, condominio[i].predio[j].apartamento[k].andar, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].estado);
                        }
                    }
                }
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }
    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
}

void ai_indet_Predio(int n)
{
    int i;
    char letra = 'A';
    for (i = 0; i < N_PREDIO; i++)
    {
        condominio[n].predio[i].indentificador = letra++;
    }
}
void aiPorta(int i, int j, int k)
{
    int inteiro = condominio[i].predio[j].apartamento[k].idApt;
    char porta[5];
    char indentificador = condominio[i].predio[j].indentificador;

    itoa(inteiro, porta, 10);
    concatenar_LetraString(porta, indentificador);
    strcpy(condominio[i].predio[j].apartamento[k].porta, porta);
}
void concatenar_LetraString(char texto[], char letra)
{
    size_t tamanho = strlen(texto);
    texto[tamanho] = letra;
    texto[tamanho + 1] = '\0';
}
void ai_Andar(int i, int j, int k)
{
    if (condominio[i].predio[j].apartamento[k].idApt < 1)
    {
        condominio[i].predio[j].apartamento[k].andar = 0;
    }
    else if (condominio[i].predio[j].apartamento[k].idApt < 2)
    {
        condominio[i].predio[j].apartamento[k].andar = 1;
    }
    else if (condominio[i].predio[j].apartamento[k].idApt < 3)
    {
        condominio[i].predio[j].apartamento[k].andar = 2;
    }
    else if (condominio[i].predio[j].apartamento[k].idApt < 4)
    {
        condominio[i].predio[j].apartamento[k].andar = 3;
    }
    else if (condominio[i].predio[j].apartamento[k].idApt <= 5)
    {
        condominio[i].predio[j].apartamento[k].andar = 4;
    }
}
void ai_Preco(int i, int j, int k)
{

    if ((strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t2")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T2")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t 2")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T 2")) == 0)
    {
        condominio[i].predio[j].apartamento[k].preco = 50000000;
    }
    else if ((strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t3")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T3")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t 3")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T 3")) == 0)
    {
        condominio[i].predio[j].apartamento[k].preco = 80000000;
    }
    else if ((strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t4")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T4")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t 4")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T 4")) == 0)
    {
        condominio[i].predio[j].apartamento[k].preco = 120000000;
    }
    else if ((strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t5")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T5")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "t 5")) == 0 || (strcmp(condominio[i].predio[j].apartamento[k].tipologia, "T 5")) == 0)
    {
        condominio[i].predio[j].apartamento[k].preco = 140000000;
    }
}

void listarCond()
{
    int i, existe = 0;
    system("cls");
    printf("\n==========\t CONDOMINIOS JA CADASTRADOS \t==========\n");
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {
            printf("\n===============================================\n");
            printf("\n ID: %d - Condominio: %s; Cidade: %s.\n", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
            printf("\n===============================================\n");
            existe++;
        }
    }
    if (existe == 0)
    {
        printf("\nNao existe nenhum condominio cadastrado AINDA! \n");
    }
    else if (existe == N_CONDOMINIO)
    {
        printf("\nO Numero Maximo de condominios ja foi cadastrado ");
    }
    else if (existe > 0)
    {
        printf("\nExistem %d Condominos que ainda pode cadastrar ", (N_CONDOMINIO - existe));
    }
    putchar('\n');
    system("pause");
}

void listarPredio()
{
    int existe = 0, i, j, k, apt, id;
    system("cls");
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {
            existe++;

            printf("\n-----\tID: %d. CONDOMINIO: %s \t----- \n", condominio[i].id, condominio[i].nomeCond);

            for (j = 0; j < N_PREDIO; j++)
            {
                for (k = 0, apt = 0; k < N_APT; k++)
                {
                    if (condominio[i].predio[j].apartamento[k].estado == 1)
                    {
                        apt++;
                    }
                }
                printf("\n%d - Predio %c ", (condominio[i].predio[j].id + 1), condominio[i].predio[j].indentificador);
                if (apt == N_APT)
                {
                    printf("Todos os apartamentos encontram-se ocupados");
                }
                else
                {
                    printf("Apartamentos disponiveis: %d", (N_APT - apt));
                }
            }
            putchar('\n');
        }
    }
    if (existe == 0)
    {
        printf("\nNenhum condominio foi cadastrado, por isso nao esxiste nenhum predio ");
    }
    system("pause");
}
void pegarDadosCond()
{
    int i, id, ativo, m;
    char nomeCond[100], cidade[100], c;

    if ((ficheiro = fopen("condominio.txt", "r")) == NULL)
    {

        printf("\nImpossivel Abrir ficheiro");
    }
    else
    {

        for (i = 0; (i < N_CONDOMINIO) && (fscanf(ficheiro, "%d %s %s %d", &id, &nomeCond, &cidade, &ativo) != EOF); i++)
        {
            if (condominio[i].ativo == 0)
            {
                condominio[i].id = id;
                strcpy(condominio[i].nomeCond, nomeCond);
                strcpy(condominio[i].cidade, cidade);
                condominio[i].ativo = ativo;
            }
        }
    }
}

int localizaPredio(char c)
{
    int i, j;
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {
            for (j = 0; j < N_PREDIO; j++)
            {
                if (condominio[i].predio[j].indentificador == c)
                {
                    return condominio[i].predio[j].id;
                }
            }
        }
    }
    printf("\nNenhum Predio localizado com esse indentificador %c", c);
    return -1;
}

void listaApt()
{
    int i, j, k;
    system("cls");
    for (i = 0; i < N_CONDOMINIO; i++)
    {
        if (condominio[i].ativo == 1)
        {

            printf("\n\n============================================================");
            printf("\n\t\tID %d CONDOMINIO: %s \n", condominio[i].id, condominio[i].nomeCond);
            printf("============================================================\n");

            for (j = 0; j < N_PREDIO; j++)
            {
                printf("\n--------------\t%d - PREDIO: %c \t-------------- \n", (condominio[i].predio[j].id + 1), condominio[i].predio[j].indentificador);
                for (k = 0; k < N_APT; k++)
                {
                    if (condominio[i].predio[j].apartamento[k].estado == 1)
                    {
                        printf("\n\t*****\t%d - APARTAMENTO\t***** ", (k + 1));
                        printf("\n Dono: %s", condominio[i].predio[j].apartamento[k].dono);
                        printf("\n Preco: %.2f", condominio[i].predio[j].apartamento[k].preco);
                        printf("\n Tipologia: %s", condominio[i].predio[j].apartamento[k].tipologia);
                        printf("\n Andar: %d", condominio[i].predio[j].apartamento[k].andar);
                        printf("\n Porta: %s", condominio[i].predio[j].apartamento[k].porta);
                        printf("\n-----------------------------------------------\n");
                    }
                }
            }
        }
    }
    system("pause");
}

void pegarDadosApt()
{

    int iD_cond, andar, i, j, k, estado;
    char dono[50];
    float preco;
    char tipologia[5];
    char porta[3];
    char identificador;

    if ((ficheiro = fopen("apartamento.txt", "r")) == NULL)
    {

        printf("\nImpossivel Abrir ficheiro");
    }
    else
    {
        while (fscanf(ficheiro, "%d %c %s %s %f %d %s %d", &iD_cond, &identificador, &dono, &tipologia, &preco, &andar, &porta, &estado) != EOF)
        {
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if (condominio[i].ativo == 1)
                {
                    if (condominio[i].id == iD_cond)
                    {
                        for (j = 0; j < N_PREDIO; j++)
                        {
                            if (condominio[i].predio[j].indentificador == identificador)
                            {
                                for (k = 0; k < N_APT; k++)
                                {
                                    if (condominio[i].predio[j].apartamento[k].dono[0] == '\0')
                                    {
                                        strcpy(condominio[i].predio[j].apartamento[k].dono, dono);
                                        strcpy(condominio[i].predio[j].apartamento[k].tipologia, tipologia);
                                        strcpy(condominio[i].predio[j].apartamento[k].porta, porta);
                                        condominio[i].predio[j].apartamento[k].preco = preco;
                                        condominio[i].predio[j].apartamento[k].andar = andar;
                                        condominio[i].predio[j].apartamento[k].estado = estado;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void pesquisarCond()
{
    int i, op, id, r = 0;
    char pesquisar[100];
    system("cls");
    do
    {
        printf("\n==========\t PESQUISAR POR CONDOMINIO \t==========\n");
        printf("\n (1) - Pesquisar pelo ID ");
        printf("\n (2) - Pesquisar pelo NOME DO CONDOMINIO ");
        printf("\n (3) - Pesquisar pela CIDADE");
        printf("\n (0) - SAIR ");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        scanf(" %d", &op);

        switch (op)
        {
        case 1:
        {
            r = 0;
            printf("\nDigite o ID do Condominio: ");
            fflush(stdin);
            scanf(" %d", &id);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if (condominio[i].id == id)
                {

                    printf("\nID %d Condominio %s Cidade %s", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
                    r++;
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            break;
        }
        case 2:
        {
            r = 0;
            printf("\nDigite o NOME do Condominio: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if ((strcmp(condominio[i].nomeCond, pesquisar)) == 0)
                {

                    printf("\nID %d Condominio %s Cidade %s", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
                    r++;
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            break;
        }
        case 3:
        {
            r = 0;
            printf("\nDigite a CIDADE do Condominio: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if ((strcmp(condominio[i].cidade, pesquisar)) == 0)
                {

                    printf("\nID %d Condominio %s Cidade %s", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
                    r++;
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            break;
        }
        }
        putchar('\n');
        system("pause");
    } while (op != 0);
}

void pesquisarApt()
{
    int i, op, id, r = 0, j, k;
    char pesquisar[100], c;

    do
    {
        system("cls");
        printf("\n==========\t PESQUISAR POR APARTAMENTO \t==========\n");

        printf("\n (1) - Pesquisar pelo NOME DO DONO ");
        printf("\n (2) - Pesquisar pela TIPOLOGIA ");
        printf("\n (3) - Pesquisar pelo ANDAR");
        printf("\n (4) - Pesquisar pelo NOME DO CONDOMINIO");
        printf("\n (5) - Pesquisar pela CIDADE");
        printf("\n (6) - Pesquisar pelo PREDIO");
        printf("\n (0) - SAIR ");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        scanf(" %d", &op);
        switch (op)
        {
        case 1:
        {
            r = 0;
            printf("\nDigite o Nome do DONO: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                for (j = 0; j < N_PREDIO; j++)
                {
                    for (k = 0; k < N_APT; k++)
                    {
                        if (strcmp(condominio[i].predio[j].apartamento[k].dono, pesquisar) == 0)
                        {
                            printf("\n===============================================================================================\n");
                            printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                            r++;
                            printf("\n===============================================================================================\n");
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        case 2:
        {
            r = 0;
            printf("\nDigite a Tipologia do Apartamento: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                for (j = 0; j < N_PREDIO; j++)
                {
                    for (k = 0; k < N_APT; k++)
                    {
                        if (strcmp(condominio[i].predio[j].apartamento[k].tipologia, pesquisar) == 0)
                        {
                            if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                            {
                                printf("\n===============================================================================================\n");
                                printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                                r++;
                                printf("\n===============================================================================================\n");
                            }
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        case 3:

        {
            r = 0;
            printf("\nDigite o Andar do Apartamento: ");
            fflush(stdin);
            scanf(" %d", &id);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                for (j = 0; j < N_PREDIO; j++)
                {
                    for (k = 0; k < N_APT; k++)
                    {
                        if (condominio[i].predio[j].apartamento[k].andar == id)
                        {
                            if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                            {
                                printf("\n===============================================================================================\n");
                                printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                                r++;
                                printf("\n===============================================================================================\n");
                            }
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        case 4:

        {
            r = 0;
            printf("\nDigite o NOME do Condominio: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if ((strcmp(condominio[i].nomeCond, pesquisar)) == 0)
                {

                    for (j = 0; j < N_PREDIO; j++)
                    {
                        for (k = 0; k < N_APT; k++)
                        {
                            if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                            {
                                printf("\n===============================================================================================\n");
                                printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                                r++;
                                printf("\n===============================================================================================\n");
                            }
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        case 5:

        {
            r = 0;
            printf("\nDigite a Cidade: ");
            fflush(stdin);
            gets(pesquisar);
            for (i = 0; i < N_CONDOMINIO; i++)
            {
                if ((strcmp(condominio[i].cidade, pesquisar)) == 0)
                {

                    for (j = 0; j < N_PREDIO; j++)
                    {
                        for (k = 0; k < N_APT; k++)
                        {
                            if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                            {
                                printf("\n===============================================================================================\n");
                                printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                                r++;
                                printf("\n===============================================================================================\n");
                            }
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        case 6:

        {
            r = 0;
            printf("\nDigite a letra do Predio: ");
            fflush(stdin);
            scanf(" %c", &c);
            for (i = 0; i < N_CONDOMINIO; i++)
            {

                for (j = 0; j < N_PREDIO; j++)
                {
                    if (condominio[i].predio[j].indentificador == c)
                    {
                        for (k = 0; k < N_APT; k++)
                        {
                            if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                            {
                                printf("\n=============================================================================================== \n");
                                printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                                r++;
                                printf("\n=============================================================================================== \n");
                            }
                        }
                    }
                }
            }
            if (r != 0)
            {
                printf("\nRESULTADOS ENCOTRADO(s) %d ", r);
            }
            else
            {
                printf("\nNENHUM RESULTADO ENCONTRADO ");
            }
            putchar('\n');
            system("pause");
            break;
        }
        }
    } while (op != 0);
}

void editarCond()
{
    int id, i, op;
    char op2;
    do
    {
        system("cls");

        //pegarDadosCond();
        listarCond();
        printf("\n==========\t EDITAR CONDOMINIOS \t==========\n");
        printf("\nDigite o ID do Condominio a EDITAR: ");
        fflush(stdin);
        scanf("%d", &id);
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].id == id)
            {

                printf("\nID %d Condominio %s Cidade %s", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
                break;
            }
        }
        printf("\n (1) - Editar nome condominio ");
        printf("\n (2) - Editar cidade ");
        printf("\n (0) - CANCELAR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        scanf(" %d", &op);
        switch (op)
        {
        case 1:
        {

            printf("\nCondominio %s ", condominio[i].nomeCond);
            printf("\nDigite o NOVO NOME DO CONDOMINIO: ");
            fflush(stdin);
            gets(condominio[i].nomeCond);
            printf("\nNovo nome do condominio: %s ", condominio[i].nomeCond);
            break;
        }
        case 2:
        {

            printf("\nCondominio %s Cidade %s", condominio[i].nomeCond, condominio[i].cidade);
            printf("\nDigite a NOVA CIDADE DO CONDOMINIO: ");
            fflush(stdin);
            gets(condominio[i].cidade);
            printf("\nNova cidade do condominio: %s ", condominio[i].cidade);
            break;
        }
        default:
            break;
        }
        putchar('\n');
        printf("\n (1) - Continuar editando ");
        printf("\n (0) - SAIR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        op2 = getchar();
    } while (op2 != '0');
    if ((ficheiro = fopen("condominio.txt", "w")) != NULL)
    {
        int i;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {
                fprintf(ficheiro, "%d %s %s %d\n", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade, condominio[i].ativo);
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }

    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
}

void editarApt()
{
    int i, j, k, op, l, m, n;
    char s[50], op2;

    do
    {
        system("cls");
        listaApt();
        printf("\nDigite o nome do DONO: ");
        fflush(stdin);
        gets(s);
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            for (j = 0; j < N_PREDIO; j++)
            {
                for (k = 0; k < N_APT; k++)
                {
                    if (strcmp(condominio[i].predio[j].apartamento[k].dono, s) == 0)
                    {
                        printf("\n===================================================================================\n");
                        printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                        l = i;
                        m = j;
                        n = k;
                        break;
                        printf("\n===================================================================================\n");
                    }
                }
            }
        }
        printf("\n (1) - Editar nome do Dono do apartamento");
        printf("\n (2) - Editar Tipologia do apartamento ");
        printf("\n (0) - CANCELAR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        scanf(" %d", &op);
        switch (op)
        {
        case 1:
        {

            printf("\nDONO %s", condominio[l].predio[m].apartamento[n].dono);
            printf("\nDigite o NOVO NOME DO CONDOMINIO: ");
            fflush(stdin);
            gets(condominio[l].predio[m].apartamento[n].dono);
            printf("\nNovo nome do DONO: %s ", condominio[l].predio[m].apartamento[n].dono);
            break;
        }
        case 2:
        {

            printf("\nDono %s Tipologia %s", condominio[l].predio[m].apartamento[n].dono, condominio[l].predio[m].apartamento[n].tipologia);
            printf("\nDigite a NOVA TIPOLOGIA DO APARTAMENTO: ");
            fflush(stdin);
            gets(condominio[l].predio[m].apartamento[n].tipologia);
            ai_Preco(l, m, n);
            printf("\nNOVA TIPOLOGIA DO APARTAMENTO: %s ", condominio[l].predio[m].apartamento[n].tipologia);
            break;
        }
        default:
            break;
        }
        putchar('\n');
        printf("\n (1) - Continuar editando ");
        printf("\n (0) - SAIR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        op2 = getchar();
    } while (op2 != '0');

    if ((ficheiro = fopen("apartamento.txt", "w")) != NULL)
    {
        int i, j, k;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {

                for (j = 0; j < N_PREDIO; j++)
                {

                    for (k = 0; k < N_APT; k++)
                    {
                        if (condominio[i].predio[j].apartamento[k].dono[0] != '\0')
                        {
                            fprintf(ficheiro, "%d ", condominio[i].id);
                            fprintf(ficheiro, "%c ", condominio[i].predio[j].indentificador);
                            fprintf(ficheiro, "%s %s %f %d %s %d\n", condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].preco, condominio[i].predio[j].apartamento[k].andar, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].estado);
                        }
                    }
                }
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }
    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
}

void eliminarCond()
{
    int id, op, i;
    char op2, c;
    do
    {
        listarCond();
        printf("\n==========\t ELIMINAR CONDOMINIOS \t==========\n");
        printf("\nDigite o ID do Condominio a ELIMINAR: ");
        fflush(stdin);
        scanf("%d", &id);
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].id == id)
            {

                printf("\nSera ELIMINADO\nID %d Condominio %s Cidade %s", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade);
                printf("\nVOCE TEM CERTEZA QUE QUER ELIMINA S/N ? :  ");
                fflush(stdin);
                c = getchar();
                if (c == 's' || c == 'S')
                {
                    printf("\nELIMINADO");
                    condominio[i].ativo = 0;
                }
                else
                {
                    printf("\nCANSELANDO A ELIMINACAO ");
                }

                printf("\n================================== ");
                break;
            }
        }
        putchar('\n');
        printf("\n (1) - Continuar editando ");
        printf("\n (0) - SAIR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        op2 = getchar();
    } while (op2 != '0');
    if ((ficheiro = fopen("condominio.txt", "w")) != NULL)
    {
        int i;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {
                fprintf(ficheiro, "%d %s %s %d\n", condominio[i].id, condominio[i].nomeCond, condominio[i].cidade, condominio[i].ativo);
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }

    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
     if ((ficheiro = fopen("apartamento.txt", "w")) != NULL)
    {
        int i, j, k;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {

                for (j = 0; j < N_PREDIO; j++)
                {

                    for (k = 0; k < N_APT; k++)
                    {
                        if (condominio[i].predio[j].apartamento[k].estado != 0)
                        {
                            fprintf(ficheiro, "%d ", condominio[i].id);
                            fprintf(ficheiro, "%c ", condominio[i].predio[j].indentificador);
                            fprintf(ficheiro, "%s %s %f %d %s %d\n", condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].preco, condominio[i].predio[j].apartamento[k].andar, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].estado);
                        }
                    }
                }
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }
    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
}

void eliminarApt()
{

    int i, j, k, n = 0;
    char s[50], op2, c;

    do
    {
        system("cls");
        listaApt();
        printf("\n==========\t ELIMINAR APARTAMENTO \t==========\n");
        printf("\nDIGITE O NOME DO DONO DO APARTAMENTO A ELIMINAR: ");
        fflush(stdin);
        gets(s);
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            for (j = 0; j < N_PREDIO; j++)
            {
                for (k = 0; k < N_APT; k++)
                {
                    if (strcmp(condominio[i].predio[j].apartamento[k].dono, s) == 0)
                    {
                        printf("\n===================================================================================\n");
                        printf("\nSERA ELIMINADO O APARTAMENTO");
                        printf("\nCondominio %s; cidade %s; Predio %c; Dono %s; Porta %s; Tipologia %s; Andar %d.\n", condominio[i].nomeCond, condominio[i].cidade, condominio[i].predio[j].indentificador, condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].andar);
                        n++;
                        printf("\nVOCE TEM CERTEZA QUE QUER ELIMINA S/N ? :  ");
                        fflush(stdin);
                        c = getchar();
                        if (c == 's' || c == 'S')
                        {
                            printf("\nELIMINADO");
                            condominio[i].predio[j].apartamento[k].estado = 0;
                        }
                        else
                        {
                            printf("\nCANSELANDO A ELIMINACAO ");
                        }
                        printf("\n===================================================================================\n");
                        break;
                    }
                }
            }
        }
        if (n == 0)
        {
            printf("\nNENHUM DONO ENCONTRADO COM ESSE NOME %s ", s);
            putchar('\n');
            system("pause");
        }
        putchar('\n');
        printf("\n (1) - Continuar eliminando ");
        printf("\n (0) - SAIR");
        printf("\n DIGITE AQUI: ");
        fflush(stdin);
        op2 = getchar();
    } while (op2 != '0');

    if ((ficheiro = fopen("apartamento.txt", "w")) != NULL)
    {
        int i, j, k;
        for (i = 0; i < N_CONDOMINIO; i++)
        {
            if (condominio[i].ativo == 1)
            {

                for (j = 0; j < N_PREDIO; j++)
                {

                    for (k = 0; k < N_APT; k++)
                    {
                        if (condominio[i].predio[j].apartamento[k].estado != 0)
                        {
                            fprintf(ficheiro, "%d ", condominio[i].id);
                            fprintf(ficheiro, "%c ", condominio[i].predio[j].indentificador);
                            fprintf(ficheiro, "%s %s %f %d %s %d\n", condominio[i].predio[j].apartamento[k].dono, condominio[i].predio[j].apartamento[k].tipologia, condominio[i].predio[j].apartamento[k].preco, condominio[i].predio[j].apartamento[k].andar, condominio[i].predio[j].apartamento[k].porta, condominio[i].predio[j].apartamento[k].estado);
                        }
                    }
                }
            }
        }
        printf("\nDADOS SALVOS COM SUCESSO \n");
        fclose(ficheiro);
    }
    else
    {
        printf("\nNao foi possivel cadastrar mais Condominos\n");
    }
}
int letraM(char ch)
{
    if (ch >= 'a' && ch <= 'z')
    {
        return ch - 'a' + 'A';
    }
    else
    {
        return ch;
    }
}
/******************************************************************************************/
