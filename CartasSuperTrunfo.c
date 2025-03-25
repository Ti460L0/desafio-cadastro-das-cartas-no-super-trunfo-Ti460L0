//Programa criado pelo aluno Tiago Lopes do curso de Engenharia de Software.

/* Pontos a corrigir:
 1. Gerar código para as cartas seguindo o padrão de A a H para o país e de 1 a 4 para a cidade. Ex. A01, A02, B01, B02...
    Cadastrar uma carta por vez e para cada pais será permitido cadastrar até 4 cidades.
    O código será gerado automaticamente pelo sistema e não será necessário informar ao usuário.
    Para uma melhor usabilidade, limitarei os paises de modo a serem apenas paises que iniciem com a letra A, B, C, D, E, F, G e H.
    Deve ser possível selecionar uma carta ou se deseja cadastrar uma nova carta.
 2.Novas Propriedades Calculadas:
    Densidade Populacional: População dividida pela área da cidade.
    PIB per Capita: PIB total dividido pela população.
    O sistema agora calculará automaticamente a Densidade Populacional e o PIB per Capita com base nos dados inseridos.
    Essas novas propriedades serão adicionadas às informações exibidas para cada cidade.
3. Comparação de Cartas:
    O sistema permitirá ao usuário comparar duas cartas com base nas propriedades inseridas e calculadas.
    Modificar para selecionar as cartas pelo código digitado.
*/


#include <stdio.h>
#include <string.h>

/*
Optei por utilizar uma estrutura para representar a carta, pois assim é possível armazenar todos os atributos da carta em um único objeto.
Dessa forma, é mais fácil de manipular os dados da carta e comparar os atributos.
*/
typedef struct
{
    int codigo;
    char nome[50];
    float populacao;
    float area;
    float pib;
    int pontosTuristicos;
} Carta;

int gerarCodigo()
{
    static int codigo = 0;
    return ++codigo;
}

// Função para cadastrar a carta
void cadastroCarta(Carta *carta)
{
    printf("Digite o codigo: ");
    scanf("%d", &carta->codigo);

    
    /*
    Solução encontrada para limpar o buffer do teclado após a leitura de um inteiro
    e antes da leitura de uma string pois o fgets não funciona corretamente após a
    leitura de um inteiro com o scanf e dai não estava sendo possível digitar o nome
    da cidade após a leitura do código.
    */
   while (getchar() != '\n');
    printf("Digite o Nome da Cidade: ");
    fgets(carta->nome, sizeof(carta->nome), stdin);
    carta->nome[strcspn(carta->nome, "\n")] = 0;

    printf("Digite a populacao (milhoes): ");
    scanf("%f", &carta->populacao);

    printf("Digite a area (km²): ");
    scanf("%f", &carta->area);

    printf("Digite o pib: ");
    scanf("%f", &carta->pib);

    printf("Digite os pontos turisticos: ");
    scanf("%d", &carta->pontosTuristicos);

    printf("\n");
}

// Função para imprimir a carta
void imprimirCarta(Carta carta)
{
    printf("Codigo: %d\n", carta.codigo);
    printf("Nome: %s\n", carta.nome);
    printf("Populacao(milhoes): %.2f\n", carta.populacao);
    printf("Area(km²): %.2f\n", carta.area);
    printf("PIB: %.2f\n", carta.pib);
    printf("Pontos Turisticos: %d\n", carta.pontosTuristicos);
    printf("\n");
}

// Função para comparar os atributos
int compararAtributo(Carta c1, Carta c2, int escolha)
{
    switch (escolha)
    {
    case 1:
        return (c1.populacao > c2.populacao) - (c1.populacao < c2.populacao);
    case 2:
        return (c1.area > c2.area) - (c1.area < c2.area);
    case 3:
        return (c1.pib > c2.pib) - (c1.pib < c2.pib);
    case 4:
        return (c1.pontosTuristicos > c2.pontosTuristicos) - (c1.pontosTuristicos < c2.pontosTuristicos);
    default:
        return 0;
    }
}

// Função para calcular o superpoder
float superPoder(Carta c)
{
    float superPoder = c.populacao + c.area + c.pib + (float)c.pontosTuristicos;
    return superPoder;
}

// Função principal
int main()
{
    Carta c1, c2;
    char escolha;

    // Loop para jogar novamente    
    do
    {
        
        int pontosJ1 = 0, pontosJ2 = 0;
        
        printf("\nBem-vindo ao jogo de cartas de trunfo!\n");
        printf("\nO que deseja fazer?\n");
        printf("\n1 - Jogar\n2 - Cadastrar nova carta\n3 - Consultar carta\n4 - Sair\n");
        printf("\nDigite a opcao desejada: ");
        int opcao;
        scanf("%d", &opcao);

        if (opcao == 3)
        {
            printf("\nObrigado por jogar!\n");
            return 0;
        }

        if (opcao == 2)
        {
            // Cadastrar nova carta
        }

        if (opcao == 1)
        {
            // Jogar
            printf("\nJogar:\n");

            printf("\nPlacar inicial:\n");
            printf("\nJogador 1: %d x %d :Jogador 2\n", pontosJ1, pontosJ2);
            printf("\n");

            printf("\nJogador 1, cadastre sua carta:\n");
            cadastroCarta(&c1);

            printf("\nJogador 2, cadastre sua carta:\n");
            cadastroCarta(&c2);

            printf("\nCartas cadastradas:\n");
            printf("\nJogador 1:");
            imprimirCarta(c1);
            printf("\nJogador 2:");
            imprimirCarta(c2);

            // Loop para que se possa resolver em duas rodadas
            for (int i = 0; i < 2; i++)
            {
                int escolhaAtributo;
                printf("\nRodada %d - Escolha um atributo para comparar:\n", i + 1);
                printf("1 - Populacao\n2 - Area\n3 - PIB\n4 - Pontos Turisticos\n");
                scanf("%d", &escolhaAtributo);

                int resultado = compararAtributo(c1, c2, escolhaAtributo);

                if (resultado > 0)
                {
                    printf("\nJogador 1 vence a rodada!\n");
                    pontosJ1++;
                }
                else if (resultado < 0)
                {
                    printf("\nJogador 2 vence a rodada!\n");
                    pontosJ2++;
                }
                else
                {
                    printf("\nEmpate na rodada!\n");
                    i--; // Decrement i to redo the round in case of a tie
                }
            }

            if (pontosJ1 > pontosJ2)
            {
                printf("\nJogador 1 venceu o jogo!\n");
            }
            else if (pontosJ1 < pontosJ2)
            {
                printf("\nJogador 2 venceu o jogo!\n");
            }
            // Em caso de empate, o superpoder é utilizado para desempate.
            else
            {
                printf("\nO jogo terminou em empate!\n");
                printf("\nSuperpoder ativado!\n");
                printf("\nSuperpoder de Jogador 1: %.2f\n", superPoder(c1));
                printf("\nSuperpoder de Jogador 2: %.2f\n", superPoder(c2));
                printf("\nComparando superpoder...\n");

                if (superPoder(c1) > superPoder(c2))
                {
                    printf("\nJogador 1 usou o superpoder e virou o jogo!\n");
                    printf("\nParabens jogador 1, voce venceu o jogo!\n");
                }
                else if (superPoder(c2) > superPoder(c1))
                {
                    printf("\nJogador 2 usou o superpoder e virou o jogo!\n");
                    printf("\nParabens jogador 2, voce venceu o jogo!\n");
                }
                else
                {
                    printf("\nO jogo terminou em empate mesmo com superpoderes!\n");
                }
            }
        }

        printf("\nDeseja jogar novamente? (S/N): ");
        while (getchar() != '\n')
            ;
        escolha = getchar();
    } while (escolha == 's' || escolha == 'S');

    return 0;
}

