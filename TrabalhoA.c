#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//                                                   |-------------------------------------------------------|
typedef struct aluno //                              | Struct com as informações do aluno                    |
{                    //                              |                                                       |
    char nome[15];   //                              | Nome                                                  |
    int matric;      //                              | Número da matrícula                                   |
    float nota[3];   //                              | Três notas (em um vetor)                              |
    float media;     //                              | Média das três notas                                  |
} aluno;             //                              |-------------------------------------------------------|
//                                                   |-------------------------------------------------------|
void ordem(aluno *a, int N);                //       | Inicialização da função de ordenação                  |
void media_al(aluno *p, int N);             //       | Inicialização da função de média para cada aluno      |
float mediat(aluno *p, int N);              //       | Inicialização da função de média geral                |
void maior_med(aluno *p, int N);            //       | Inicialização da função para verificar a MAIOR nota   |
void menor_med(aluno *p, int N);            //       | Inicialização da função para verificar a MENOR nota   |
void exec(aluno *p, int N);                 //       | Inicialização da função de execução de opções         |
int aprova(aluno *alunos, int N);           //       | Inicialização da função de contagem de aprovação      |
int reprova(aluno *alunos, int N);          //       | Inicialização da função de contagem de reprovação     |
int cont_linha(FILE *arq);                  //       | Inicialização da função de contar linha               |
void dados_stt(aluno *p, int N, FILE *arq); //       | Inicialização da função de guardar dados na struct    |
void menu();                                //       | Inicialização da função da interface do menu          |
void nw_archv(aluno *p, int N, FILE *arq);  //       | Inicialização da função de criar um novo arquivo      |
//                                                   |-------------------------------------------------------|
int main() //------------------------------------- Main
{
    int N;
    FILE *arq;
    aluno *alunos;
    N = cont_linha(arq);
    alunos = (aluno *)malloc(N * sizeof(aluno));
    dados_stt(alunos, N, arq);
    media_al(alunos, N);
    ordem(alunos, N);
    exec(alunos, N);
    nw_archv(alunos, N, arq);
    free(alunos);
    return 0;
} //-------------------------------------------------------------------------------------------------|

void nw_archv(aluno *p, int N, FILE *arq) //------- Função de criar um novo arquivo
{
    arq = fopen("alunos2.txt", "w");
    if (arq == NULL)
    {
        printf("Nao foi possivel ler o arquivo\n");
        exit(1);
    }
    for (int i = 0; i < N; i++)
    {
        fprintf(arq, "%d  ", p[i].matric);
        fprintf(arq, "%s  ", p[i].nome);
        fprintf(arq, "%.1f ", p[i].nota[0]);
        fprintf(arq, "%.1f ", p[i].nota[1]);
        fprintf(arq, "%.1f  ", p[i].nota[2]);
        fprintf(arq, "%.1f\n", p[i].media);
    }
    fclose(arq);
} //-------------------------------------------------------------------------------------------------|

void dados_stt(aluno *p, int N, FILE *arq) //------ Função de guardar dados do .txt nas structs
{
    int i, j;
    arq = fopen("alunos.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel ler o arquivo\n");
        exit(1);
    }
    for (i = 0; i < N; i++)
    {
        fscanf(arq, "%d", &p[i].matric);
        fscanf(arq, "%s", &p[i].nome);
        for (j = 0; j < 3; j++)
        {
            fscanf(arq, "%f", &p[i].nota[j]);
        }
    }
    fclose(arq);
} //-------------------------------------------------------------------------------------------------|

int cont_linha(FILE *arq) //                         Função de contar as linhas do arquivo
{
    char c;
    int count = 0;
    arq = fopen("alunos.txt", "r");
    if (arq == NULL)
    {
        printf("Nao foi possivel ler o arquivo\n");
        exit(1);
    }
    for (c = getc(arq); c != EOF; c = getc(arq))
        if (c == '\n')
            count = count + 1;
    count++;
    fclose(arq);
    return count;
} //-------------------------------------------------------------------------------------------------|

void ordem(aluno *p, int N) //                       Função de ordenação a partir da matrícula
{
    aluno aux;

    for (int i = 1; i < N; i++)
    {

        for (int j = 0; j < N - 1; j++)
        {
            if (p[j].matric > p[j + 1].matric)
            {
                aux = p[j + 1];
                p[j + 1] = p[j];
                p[j] = aux;
            }
        }
    }
} //-------------------------------------------------------------------------------------------------|

void media_al(aluno *p, int N) //                    Função para calcular a media de cada aluno
{
    float soma;
    for (int i = 0; i < N; i++)
    {
        soma = 0;
        for (int j = 0; j < 3; j++)
        {
            soma = soma + p[i].nota[j];
        }
        p[i].media = soma / 3;
    }
} //-------------------------------------------------------------------------------------------------|

float mediat(aluno *p, int N) //                    Função para calcular a media geral
{
    float med;
    med = 0;
    for (int i = 0; i < N; i++)
    {
        med += p[i].media;
    }
    med = med / N;
    return med;
} //-------------------------------------------------------------------------------------------------|

void maior_med(aluno *p, int N) //                   Função para calcular a media de cada aluno
{
    int ind;
    float maior;
    for (int i = 0; i < N; i++) // Calcular MAIOR média
    {
        if (i == 0)
        {
            maior = p[i].media;
        }
        if (maior <= p[i].media)
        {
            maior = p[i].media;
            ind = i;
        }
        else
        {
            maior = maior;
        }
    }
    printf("|Maior nota\n|----------\n|Matricula - %d\n|Nome - %s\n|Media final - %.2f\n----------\n|", p[ind].matric, p[ind].nome, p[ind].media);
} //-------------------------------------------------------------------------------------------------|

void menor_med(aluno *p, int N) // Função para calcular a media de cada aluno
{
    int ind;
    float menor;
    for (int i = 0; i < N; i++) // Calcular MENOR média
    {
        if (i == 0)
        {
            menor = p[i].media;
        }
        if (menor > p[i].media)
        {
            menor = p[i].media;
            ind = i;
        }
    }
    printf("|Menor nota\n|----------\n|Matricula - %d\n|Nome - %s\n|Media final - %.2f\n----------\n|", p[ind].matric, p[ind].nome, p[ind].media);
} //-------------------------------------------------------------------------------------------------|

int aprova(aluno *alunos, int N) //--------------------------------------------  FUNÇÂO DE CONTAR ALUNOS APROVADOS
{
    int aprov = 0;
    for (int i = 0; i < N; i++)
    {
        if (alunos[i].media >= 6) //     |---------------------------|
        {                         //     |                           |
            aprov++;              //     |  Contar a qtd de alunos   |
        }                         //     |  Contar a quantidade de   |
    }                             //     |  alunos aprovados         |
    return aprov;                 //     |---------------------------|
} //-------------------------------------------------------------------------------------------------|

int reprova(aluno *alunos, int N) //-------------------------------------------  FUNÇÂO DE CONTAR ALUNOS REPROVADOS
{
    int reprov = 0;
    for (int i = 0; i < N; i++)
    {
        if (alunos[i].media < 6) //     |---------------------------|
        {                        //     |                           |
            reprov++;            //     |  Contar a qtd de alunos   |
        }                        //     |  Contar a quantidade de   |
    }                            //     |  alunos reprovados        |
    return reprov;               //     |---------------------------|
} //-------------------------------------------------------------------------------------------------|

void menu() //-------------------------------------------------------  FUNÇÂO DE IMPRIMIR O MENU
{
    printf("\n\n|---------------------------------MENU---------------------------------|\n|\n| Escolha o que deseja fazer|\n|\n");
    printf("|(1) Visualizar os dados|\n|\n|(2) Nome dos alunos|\n|\n|(3) Nome e nota final dos alunos|\n|\n|(4) Buscar um aluno|\n|\n|(5) Alunos em ordem de matricula|\n|\n|(6) Editar uma nota|\n|\n|(7) Aluno com a maior media|\n|");
    printf("\n|(8) Aluno com a menor media|\n|\n|(9) Quantidade de alunos aprovados/reprovados - Media geral|\n|\n|(0) Sair do programa|\n|");
} //-------------------------------------------------------------------------------------------------|
void exec(aluno *alunos, int N) //------------------------  FUNÇÂO DE AÇÔES DO MENU
{
    char search[10];
    int busca, search_num, aprov = 0, reprov = 0, edit, opcao = -999;
    float media_total, new;
    media_total = mediat(alunos, N);
    while (opcao != 0)
    {
        media_al(alunos, N); // Calcular todas as médias e armazená-las na struct de cada aluno
        menu();              // Interface do menu
        scanf("%d", &opcao);
        switch (opcao) //----------Função de cada opção da interface---------// Enquanto não for digitado zero o menu continuará se repetindo
        {              // Ao digitar zero o programa criará um novo arquivo de texto com as informações atualizadas e se encerrará
        case 1:        //                              | 1 -> Mostar todas as informações de todos os alunos
            for (int i = 0; i < N; i++)
            {
                printf("\n|Numero de matricula - %d |\n|Nome - %s |\n|Notas - %.1f - %.1f - %.1f |\n|Media final - %.1f|\n\n", alunos[i].matric, alunos[i].nome, alunos[i].nota[0], alunos[i].nota[1], alunos[i].nota[2], alunos[i].media);
            }
            break;
        case 2: //                              | 2 -> Imprimir todos os nomes
            for (int i = 0; i < N; i++)
            {
                printf("|Nome - %s |\n\n", alunos[i].nome);
            }
            break;
        case 3: //                              | 3 -> Imprimir todos os nomes e suas respectivas medias
            for (int i = 0; i < N; i++)
            {
                printf("|Nome - %s     Nota - %.1f|\n\n", alunos[i].nome, alunos[i].media);
            }
            break;
        case 4: //                              | 4 -> Buscar um aluno
            printf("|Escolha o que deseja procurar\n\n|(1) Matricula -- (2) Nome |\n");
            scanf("%d", &busca);
            switch (busca)
            {
            case 1: //                              | 1 -> Se o usuário decidir buscar pelo número de matrícula do aluno
                printf("| Digite o numero\n");
                scanf("%d", &search_num);
                for (int i = 0; i < N; i++)
                {
                    if (alunos[i].matric == search_num) // Se for encontrado ele retornará as informações do aluno
                    {
                        printf("\nNumero de matricula - %d \nNome - %s \nNotas - %.1f-%.1f-%.1f \nMedia final - %.1f\n\n", alunos[i].matric, alunos[i].nome, alunos[i].nota[0], alunos[i].nota[1], alunos[i].nota[2], alunos[i].media);
                    }
                    if (alunos[i].matric != search_num && i == N) // Se não for encontrado ele retornará uma mensagem e levará o usuário de volta ao menu
                    {
                        printf("\nMatricula nao encontrada\n");
                    }
                }
                break;
            case 2: //                              | 2 -> Se o usuário decidir buscar pelo nome do aluno
                printf("|Digite o nome|\n");
                strcpy(search, "");
                setbuf(stdin, NULL);
                gets(search);
                for (int i = 0; i < N; i++)
                {
                    if (strcmp(alunos[i].nome, search) == 0) // Se for encontrado ele retornará as informações do aluno
                    {
                        printf("\n|Numero de matricula - %d |\n|Nome - %s |\n|Notas - %.1f - %.1f - %.1f |\n|Media final - %.1f|\n\n", alunos[i].matric, alunos[i].nome, alunos[i].nota[0], alunos[i].nota[1], alunos[i].nota[2], alunos[i].media);
                    }
                    if (strcmp(alunos[i].nome, search) != 0 && i == N) // Se não for encontrado ele retornará uma mensagem e levará o usuário de volta ao menu
                    {
                        printf("|Matricula nao encontrada|\n");
                    }
                }
            }
            break;
        case 5: //                              | 5 -> Imprimir dados dos alunos de ordenados por matrícula
            for (int i = 0; i < N; i++)
            {
                printf("----------\n|Matricula - %d\n|Nome - %s\n|Media final - %.2f\n----------\n", alunos[i].matric, alunos[i].nome, alunos[i].media);
            }
            break;
        case 6: //                              | 6 -> Editar as notas de um aluno
            printf("|Digite a matricula de um aluno que deseja editar|\n");
            scanf("%d", &search_num);
            for (int i = 0; i < N; i++)
            {
                if (alunos[i].matric == search_num) // Buscar os dados de um aluno a partir de sua matrícula
                {
                    printf("\nNumero de matricula - %d \nNome - %s \nNotas - %.1f-%.1f-%.1f \nMedia final - %.1f\n\n", alunos[i].matric, alunos[i].nome, alunos[i].nota[0], alunos[i].nota[1], alunos[i].nota[2], alunos[i].media);
                    printf("|Escolha a nota que deseja editar|\n|\n|(1)  (2)  (3)|\n");
                    scanf("%d", &edit);
                    printf("|Digite o novo valor da nota %d|\n|\n|", edit);
                    edit--;
                    scanf("%f", &new);
                    alunos[i].nota[edit] = new;
                }
                if (alunos[i].matric != search_num && i == N) // Se não for encontrado o aluno irá retornar uma mensagem e levará o usuário de volta ao menu
                {
                    printf("\nMatricula nao encontrada\n");
                }
            }
            break;
        case 7: //                              | 7 -> Imprimir as informações do aluno com a MAIOR media
            maior_med(alunos, N);
            break;
        case 8: //                              | 8 -> Imprimir as informações do aluno com a MENOR media
            menor_med(alunos, N);
            break;
        case 9: //                              | 9 -> Imprimir a quantidade de alunos aprovados/reprovados e a media geral da turma
            aprov = aprova(alunos, N);
            reprov = reprova(alunos, N);
            printf("\n\n|%d alunos aprovados - %d alunos reprovados - Media geral igual a %.1f|\n|\n", aprov, reprov, media_total);
            break;
        default: //                             | Número inválido
            printf("|Saindo do programa|");
            break;
        }
    }
} //-------------------------------------------------------------------------------------------------|
