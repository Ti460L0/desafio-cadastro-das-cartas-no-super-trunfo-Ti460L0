#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constantes para o total de cartas e o nome do arquivo
// TOTAL_CIDADES é o produto de NUM_ESTADOS e NUM_CIDADES
// ARQUIVO_CIDADES é o nome do arquivo que armazena as cartas
#define NUM_ESTADOS 8
#define NUM_CIDADES 4
#define TOTAL_CIDADES (NUM_ESTADOS * NUM_CIDADES)
#define ARQUIVO_CIDADES "cidades.dat"

// Estrutura para armazenar as informações da carta
typedef struct
{
    char codigo[4]; // Tamanho 4 para armazenar "A01\0"
    char nome[50];
    unsigned long int populacao;
    float area;
    float pib;
    int pontosTuristicos;
    float densidadePopulacional;
    float pibPerCapita;
    float superPoder;
} Cidade;

// Vetor para armazenar todas as cidades cadastradas
Cidade cidades[TOTAL_CIDADES];
int totalCidades = 0;

// Função para calcular propriedades específicas da carta
void calcularPropriedades(Cidade *cidade)
{
    cidade->densidadePopulacional = (cidade->area > 0) ? (float)cidade->populacao / cidade->area : 0;
    cidade->pibPerCapita = (cidade->populacao > 0) ? (cidade->pib * 1e9) / (float)cidade->populacao : 0;
    cidade->superPoder = (float)cidade->populacao + cidade->area + cidade->pib + (float)cidade->pontosTuristicos;
}

// Função para salvar as cartas em arquivo cidades.dat
void salvarCartas()
{
    FILE *arquivo = fopen(ARQUIVO_CIDADES, "wb");
    if (arquivo)
    {
        fwrite(&totalCidades, sizeof(int), 1, arquivo); // Salva o total de cidades
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
    memset(cidades, 0, sizeof(cidades)); // Limpa o vetor de cidades
    FILE *arquivo = fopen(ARQUIVO_CIDADES, "rb");
    if (arquivo)
    {
        fread(&totalCidades, sizeof(int), 1, arquivo); // Lê o total de cidades
        fread(cidades, sizeof(Cidade), totalCidades, arquivo);
        fclose(arquivo);
        printf("%d cartas carregadas com sucesso!\n", totalCidades);
    }
    else
    {
        printf("Erro ao abrir arquivo para leitura.\n");
        totalCidades = 0; // Garante que o número de cidades não fique corrompido
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
    scanf("%lu", &cidade->populacao);

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
    printf("Populacao: %lu\n", cidade.populacao);
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

// Função para comparar duas cartas
void compararCartas(Cidade *c1, Cidade *c2)
{
    int jogador1 = 0, jogador2 = 0; // Jogadores 1 e 2 inicializados com 0 pontos

    printf("Comparando cartas %s e %s\n", c1->codigo, c1->nome, c2->codigo, c2->nome);
    printf("Populacao: %lu vs %lu\n", c1->populacao, c2->populacao);
    printf("Area: %.2f vs %.2f\n", c1->area, c2->area);
    printf("PIB: %.2f vs %.2f\n", c1->pib, c2->pib);
    printf("Pontos Turisticos: %d vs %d\n", c1->pontosTuristicos, c2->pontosTuristicos);
    printf("Densidade Populacional: %.2f vs %.2f\n", c1->densidadePopulacional, c2->densidadePopulacional);
    printf("PIB per Capita: %.2f vs %.2f\n", c1->pibPerCapita, c2->pibPerCapita);
    printf("Super Poder: %.2f vs %.2f\n", c1->superPoder, c2->superPoder);
    printf("\nVencedor: ");
    // Comparar os atributos e determinar o vencedor
    if (c1->populacao > c2->populacao)
    {
        jogador1++;
    }
    else if (c1->populacao < c2->populacao)
    {
        jogador2++;
    }

    if (c1->area > c2->area)
    {
        jogador1++;
    }
    else if (c1->area < c2->area)
    {
        jogador2++;
    }
    if (c1->pib > c2->pib)
    {
        jogador1++;
    }
    else if (c1->pib < c2->pib)
    {
        jogador2++;
    }
    if (c1->pontosTuristicos > c2->pontosTuristicos)
    {
        jogador1++;
    }
    else if (c1->pontosTuristicos < c2->pontosTuristicos)
    {
        jogador2++;
    }
    if (c1->densidadePopulacional > c2->densidadePopulacional)
    {
        jogador1++;
    }
    else if (c1->densidadePopulacional < c2->densidadePopulacional)
    {
        jogador2++;
    }
    if (c1->pibPerCapita > c2->pibPerCapita)
    {
        jogador1++;
    }
    else if (c1->pibPerCapita < c2->pibPerCapita)
    {
        jogador2++;
    }
    if (c1->superPoder > c2->superPoder)
    {
        jogador1++;
    }
    else if (c1->superPoder < c2->superPoder)
    {
        jogador2++;
    }
    if (jogador1 > jogador2)
    {
        printf("Placar: Jogador 1 (%d) x Jogador 2 (%d)\n", jogador1, jogador2);
        printf("Jogador 1 venceu!\n");
    }
    else if (jogador1 < jogador2)
    {
        printf("Placar: Jogador 1 (%d) x Jogador 2 (%d)\n", jogador1, jogador2);
        printf("Jogador 2 venceu!\n");
    }
    else
    {
        printf("Placar: Jogador 1 (%d) x Jogador 2 (%d)\n", jogador1, jogador2);
        printf("Empate!\n");
    }
    printf("\n");
    printf("Pressione Enter para continuar...\n");
    while (getchar() != '\n')
        ;      // Limpar o buffer do teclado
    getchar(); // Espera o usuário pressionar Enter
}

// Função para jogar o Super Trunfo
void jogar()
{
    char codigo1[4], codigo2[4];
    Cidade *carta1 = NULL, *carta2 = NULL;

    printf("Digite o codigo da primeira carta: ");
    scanf(" %3s", codigo1);

    for (int i = 0; i < totalCidades; i++)
    {
        if (strcmp(cidades[i].codigo, codigo1) == 0)
        {
            carta1 = &cidades[i];
            break;
        }
    }

    if (carta1 == NULL)
    {
        printf("Carta com codigo %s nao encontrada.\n", codigo1);
        return;
    }

    imprimirCarta(*carta1);

    printf("Digite o codigo da segunda carta: ");
    scanf(" %3s", codigo2);

    for (int i = 0; i < totalCidades; i++)
    {
        if (strcmp(cidades[i].codigo, codigo2) == 0)
        {
            carta2 = &cidades[i];
            break;
        }
    }

    if (carta2 == NULL)
    {
        printf("Carta com codigo %s nao encontrada.\n", codigo2);
        return;
    }

    imprimirCarta(*carta2);

    compararCartas(carta1, carta2);
}

// Função principal do para executar as funções.
int main()
{
    char escolha;

    do
    {
        printf("\n=== Super Trunfo Paises ===\n");
        printf("1 - Jogar o Super Trunfo\n");
        printf("2 - Gerenciar Cartas\n");
        printf("3 - Sair\n");
        printf("Opcao: ");
        scanf(" %c", &escolha);

        switch (escolha)
        {
        case '1':
            jogar();
            break;
        case '2':
            printf("\n=== Gerenciar Cartas ===\n");
            printf("1 - Cadastrar Nova Carta\n");
            printf("2 - Imprimir Cartas\n");
            printf("3 - Salvar Cartas\n");
            printf("4 - Carregar Cartas\n");
            printf("5 - Deletar Cartas\n");
            printf("6 - Voltar\n");
            printf("Opcao: ");
            char escolha2;
            scanf(" %c", &escolha2);
            switch (escolha2)
            {
            case '1':
                cadastroCarta();
                break;
            case '2':
                imprimirCartas();
                break;
            case '3':
                salvarCartas();
                break;
            case '4':
                carregarCidades();

                break;
            case '5':
                deletarCartas();
                break;
            case '6':
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
