#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>
#define NUM_ESTADOS 8
#define NUM_CIDADES 4
#define TOTAL_CIDADES (NUM_ESTADOS * NUM_CIDADES)
#define ARQUIVO_CIDADES "cidades.dat"

// Estrutura para armazenar as informações da carta
typedef struct
{
    char codigo[4]; // Tamanho 4 para armazenar "A01\0"
    char nome[50];
    float populacao;
    float area;
    float pib;
    float densidadePopulacional;
    float pibPerCapita;
    int pontosTuristicos;
    float superPoder;
} Cidade;

// Vetor para armazenar todas as cidades cadastradas
Cidade cidades[TOTAL_CIDADES];
int totalCidades = 0;

// Função para calcular as propriedades da carta
void calcularPropriedades(Cidade *cidade)
{
    cidade->densidadePopulacional = (cidade->area > 0) ? cidade->populacao / cidade->area : 0;
    cidade->pibPerCapita = (cidade->populacao > 0) ? cidade->pib / cidade->populacao : 0;
    cidade->superPoder = cidade->populacao + cidade->area + cidade->pib + cidade->pontosTuristicos;
}

// Função para salvar as cartas em arquivo cidades.dat
void salvarCartas()
{
    FILE *arquivo = fopen(ARQUIVO_CIDADES, "wb");
    if (arquivo)
    {
        fwrite(cidades, sizeof(Cidade), totalCidades, arquivo);
        fclose(arquivo);
        printf("Cartas salvas com sucesso!\n");
    }
    else
    {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
}

// Função para deletar as cartas do arquivo cidades.dat
void deletarCartas()
{
    FILE *arquivo = fopen(ARQUIVO_CIDADES, "wb");
    if (arquivo)
    {
        fclose(arquivo);
        printf("Cartas deletadas com sucesso!\n");
    }
    else
    {
        printf("Erro ao abrir arquivo para escrita.\n");
    }
}

// Função para carregar as cartas do arquivo cidades.dat
void carregarCidades()
{
    FILE *arquivo = fopen(ARQUIVO_CIDADES, "rb");
    if (arquivo)
    {
        totalCidades = fread(cidades, sizeof(Cidade), TOTAL_CIDADES, arquivo);
        fclose(arquivo);
        printf("%d cartas carregadas com sucesso!\n", totalCidades);
    }
    else
    {
        printf("Erro ao abrir arquivo para leitura.\n");
    }
}

// Função para cadastrar a carta
void cadastroCarta()
{
    if (totalCidades >= TOTAL_CIDADES)
    {
        printf("Limite de cartas atingido!\n");
        return;
    }

    Cidade *cidade = &cidades[totalCidades];

    // Solicitar o código da cidade a ser cadastrada
    printf("Digite o codigo da Cidade (A01 a H04): ");
    scanf(" %3s", cidade->codigo);

    // Converter a primeira letra para maiúscula para padronizar
    cidade->codigo[0] = toupper(cidade->codigo[0]);

    // Validação do código (1 letra de A a H, 2 e 3 digitos de 01 a 04)
    if (cidade->codigo[0] < 'A' || cidade->codigo[0] > 'H' ||
        cidade->codigo[1] < '0' || cidade->codigo[1] > '9' ||
        cidade->codigo[2] < '0' || cidade->codigo[2] > '9')
    {
        printf("Codigo invalido! Tente novamente. O formato deve ser algo como A01, B02, C03, etc.\n");
        return;
    }

    // Transformar o número do código em inteiro para validar se está entre 01 e 04
    int numero = (cidade->codigo[1] - '0') * 10 + (cidade->codigo[2] - '0');

    if (numero < 1 || numero > 4)
    {
        printf("Codigo invalido! O número deve estar entre 01 e 04.\n");
        return;
    }

    totalCidades++; // Apenas aumenta se o código for válido.

    printf("Cadastro de Cidade com codigo %s\n", cidade->codigo);

    printf("Digite o nome da cidade: ");
    while (getchar() != '\n')
        ; // Limpar o buffer do teclado
    fgets(cidade->nome, sizeof(cidade->nome), stdin);
    cidade->nome[strcspn(cidade->nome, "\n")] = 0; // remove '\n' do final da string

    printf("Digite a populacao (milhoes): ");
    scanf("%f", &cidade->populacao);

    printf("Digite a area (km^2): ");
    scanf("%f", &cidade->area);

    printf("Digite o PIB (bilhoes): ");
    scanf("%f", &cidade->pib);

    printf("Digite a quantidade de pontos turisticos: ");
    scanf("%d", &cidade->pontosTuristicos);

    calcularPropriedades(cidade);

    printf("Carta cadastrada com sucesso!\n");
}

// Função para imprimir uma carta
void imprimirCarta(Cidade cidade)
{
    printf("Codigo: %s\n", cidade.codigo);
    printf("Nome: %s\n", cidade.nome);
    printf("Populacao (milhoes): %.2f\n", cidade.populacao);
    printf("Area (km^2): %.2f\n", cidade.area);
    printf("PIB (bilhoes): %.2f\n", cidade.pib);
    printf("Pontos Turisticos: %d\n", cidade.pontosTuristicos);
    printf("Densidade Populacional: %.2f\n", cidade.densidadePopulacional);
    printf("PIB per Capita: %.2f\n", cidade.pibPerCapita);
    printf("Super Poder: %.2f\n", cidade.superPoder);
    printf("\n");
}

// Função para imprimir todas as cartas cadastradas
void imprimirCartas()
{
    if (totalCidades == 0)
    {
        printf("Nenhuma cidade cadastrada ainda.\n");
        return;
    }

    for (int i = 0; i < totalCidades; i++)
    {
        imprimirCarta(cidades[i]);
    }
}

// Função para jogar o Super Trunfo
void jogar()
{
    printf("Jogar Super Trunfo em construcao...\n");
    printf("Deseja voltar ao menu principal? (S/N): ");
    char escolha;
    scanf(" %c", &escolha);
    if (escolha == 'S' || escolha == 's')
    {
        return;
    }
    else
    {
        printf("Jogo em construcao...\n");
        printf("Deseja voltar ao menu principal? (S/N): ");
        scanf(" %c", &escolha);
    }
}

// Função principal
int main()
{
    char escolha;

    do
    {
        printf("\n=== Super Trunfo Paises ===\n");
        printf("1 - Jogar (em construcao...)\n");
        printf("2 - Opcoes\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &escolha);

        switch (escolha)
        {
        case '1':
            jogar();
            break;
        case '2':
            printf("\n=== Opcoes ===\n");
            printf("1 - Cadastrar Carta\n");
            printf("2 - Imprimir Cartas\n");
            printf("3 - Imprimir Todas as Cartas\n");
            printf("4 - Salvar Cartas\n");
            printf("5 - Carregar Cartas\n");
            printf("6 - Deletar Cartas\n");
            printf("7 - Voltar\n");
            printf("Opcao: ");
            char escolha2;
            scanf(" %c", &escolha2);
            switch (escolha2)
            {
            case '1':
                cadastroCarta();
                break;
            case '2':
                imprimirCarta(cidades[totalCidades - 1]);
                break;
            case '3':
                imprimirCartas();
                break;
            case '4':
                salvarCartas();
                break;
            case '5':
                carregarCidades();
                break;
            case '6':
                deletarCartas();
                break;
            case '7':
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
            }
            break;

        case '3':
            printf("Saindo...\n");
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            break;
        }
    } while (escolha != '3');

    return 0;
}
