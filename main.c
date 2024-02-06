#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_UTILIZADORES 100
#define MAX_COMPONENTES 100
#define MAX_LOJAS 5

struct Utilizador {
    char nome[35];
    int idade;
    char email[50];
    int contacto;
    char password[20];
    char confirmarPassword[20];
};

struct Componente {
    int id;
    char nome[50];
    float custo;
    int quantidade;
};

struct Loja {
    int id;
    char nome[50];
    struct Componente componentes[MAX_COMPONENTES];
    int num_componentes;
};

int login(struct Utilizador utilizadores[], int totalUtilizadores, char email[], char password[])
{
    for (int i = 0; i < totalUtilizadores; ++i)
    {
        if (strcmp(utilizadores[i].email, email) == 0 && strcmp(utilizadores[i].password, password) == 0) // verifica se o email e pass introduzidas existem no array utilizadores
        {
            return i;  // retorna o índice do utilizador encontrado
        }
    }
    return -1;  // retorna -1 se o login falhar
}

int contemApenasLetras(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return 0; // se não for uma letra, retorna 0
        }
    }
    return 1; // se passar por todos os carateres e todos forem letras, retorna 1
}

int signup(struct Utilizador utilizadores[], int totalUtilizadores)
{
    struct Utilizador novoUtilizador;

    do
    {
        printf("Nome: ");
        scanf("%s", novoUtilizador.nome);

        if (!contemApenasLetras(novoUtilizador.nome))
        {
            printf("Erro! O nome deve conter apenas letras.\n");
            continue;
        }

        printf("Email: ");
        scanf("%s", novoUtilizador.email);

        if (strchr(novoUtilizador.email, '@') == NULL)
        {
            printf("Erro! O email deve conter '@'.\n");
            continue;
        }

        printf("Idade: ");
        if (scanf("%d", &novoUtilizador.idade) != 1 || novoUtilizador.idade <= 0)
        {
            printf("Erro! Idade inválida. A idade deve ser maior que 0.\n");
            while (getchar() != '\n');  // limpa o buffer do teclado
            continue;
        }

        printf("Telefone: ");
        char telefone[20];
        scanf("%s", telefone);

        int valido = 1;
        for (int i = 0; telefone[i] != '\0'; i++)
        {
            if (!isdigit(telefone[i]))
            {
                valido = 0;
                break;
            }
        }

        if (!valido)
        {
            printf("Erro! O telefone deve conter apenas números.\n");
            continue;
        }

        // converter o telefone para inteiro e atribuir à estrutura
        novoUtilizador.contacto = atoi(telefone);

        printf("Password: ");
        scanf("%s", novoUtilizador.password);

        printf("Confirmar a password: ");
        scanf("%s", novoUtilizador.confirmarPassword);

        if (strcmp(novoUtilizador.password, novoUtilizador.confirmarPassword) == 0)
        {
            utilizadores[totalUtilizadores] = novoUtilizador;
            printf("Registo bem-sucedido!\n");
            return totalUtilizadores + 1;
        }
        else
        {
            printf("Erro! As passwords devem ser iguais.\n");
        }
    } while (1);
}

void procurarLoja(struct Loja lojas[], int totalLojas)
{
    char nomeLoja[50];
    printf("Introduza o nome da loja que deseja procurar: ");
    getchar(); // limpar o buffer de entrada antes de usar fgets
    fgets(nomeLoja, sizeof(nomeLoja), stdin);
    // remover o caratere de nova linha da string lida pelo fgets
    nomeLoja[strcspn(nomeLoja, "\n")] = '\0';
    
    int encontrada = 0;
    for (int i = 0; i < totalLojas; ++i)
    {
        if (strcasecmp(lojas[i].nome, nomeLoja) == 0)
        {
            encontrada = 1;
            printf("Loja encontrada:\n");
            printf("ID da Loja: %d\n", lojas[i].id);
            printf("Nome: %s\n", lojas[i].nome);
            printf("Produtos:\n");
            for (int j = 0; j < lojas[i].num_componentes; ++j)
            {
                printf("ID do Produto: %d, Nome: %s, Custo: %.2f, Quantidade: %d\n",
                       lojas[i].componentes[j].id,
                       lojas[i].componentes[j].nome,
                       lojas[i].componentes[j].custo,
                       lojas[i].componentes[j].quantidade);
            }
            break;
        }
    }
    if (!encontrada)
    {
        printf("Loja não encontrada.\n");
    }
}

void procurarProduto(struct Loja lojas[], int totalLojas)
{
    char nomeProduto[50];
    printf("Introduza o nome do produto que deseja procurar: ");
    getchar(); // limpar o buffer de entrada antes de usar fgets
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    // remover o caratere de nova linha da string lida pelo fgets
    nomeProduto[strcspn(nomeProduto, "\n")] = '\0';
    
    int encontrado = 0;
    for (int i = 0; i < totalLojas; ++i)
    {
        for (int j = 0; j < lojas[i].num_componentes; ++j)
        {
            if (strcasecmp(lojas[i].componentes[j].nome, nomeProduto) == 0)
            {
                encontrado = 1;
                printf("Produto encontrado:\n");
                printf("ID da Loja: %d\n", lojas[i].id);
                printf("ID do Produto: %d, Nome: %s, Custo: %.2f, Quantidade: %d\n",
                       lojas[i].componentes[j].id,
                       lojas[i].componentes[j].nome,
                       lojas[i].componentes[j].custo,
                       lojas[i].componentes[j].quantidade);
                break;
            }
        }
    }
    if (!encontrado)
    {
        printf("Produto não encontrado.\n");
    }
}

void comprarProdutos(struct Loja lojas[], int totalLojas)
{
    int idLoja, idProduto, quantidade;
    float total = 0.0;

    printf("\nIntroduza o ID da loja: ");
    scanf("%d", &idLoja);

    if (idLoja < 1 || idLoja > totalLojas) {
        printf("ID da loja inválido.\n");
        return;
    }

    do {
        printf("\nIntroduza o ID do produto (0 para finalizar a compra): ");
        scanf("%d", &idProduto);

        if (idProduto == 0) {
            printf("A finalizar a compra...\n");
            break;
        } else if (idProduto < 1 || idProduto > lojas[idLoja - 1].num_componentes) {
            printf("ID do produto inválido.\n");
            continue;
        }

        printf("Introduza a quantidade desejada: ");
        scanf("%d", &quantidade);

        // verificar se a quantidade desejada está disponível
        if (quantidade > lojas[idLoja - 1].componentes[idProduto - 1].quantidade) {
            printf("Quantidade indisponível.\n");
            continue;
        }

        // calcular o custo do produto selecionado
        total += quantidade * lojas[idLoja - 1].componentes[idProduto - 1].custo;

        // atualizar o stock
        lojas[idLoja - 1].componentes[idProduto - 1].quantidade -= quantidade;

        printf("Produto adicionado ao carrinho.\n");

    } while (idProduto != 0);

    printf("Total da compra: %.2f\n", total);

    char confirmacao;
    printf("Confirmar compra (s/n): ");
    scanf(" %c", &confirmacao);

    if (confirmacao == 's' || confirmacao == 'S') {
        printf("Compra bem-sucedida.\n");
    } else {
        printf("Compra cancelada.\n");
    }
}

int main()
{
    struct Utilizador utilizadores[MAX_UTILIZADORES];
    int totalUtilizadores = 0;

    struct Loja lojas[MAX_LOJAS] = {
        {1, "Loja 1", {}, 0},
        {2, "Loja 2", {}, 0},
        {3, "Loja 3", {}, 0},
        {4, "Loja 4", {}, 0},
        {5, "Loja 5", {}, 0}
    };

    lojas[0].componentes[0] = (struct Componente){1, "Grafica RTX 4090", 1799.90, 5};
    lojas[0].componentes[1] = (struct Componente){2, "Grafica RTX 4080", 1250.00, 10};
    lojas[0].num_componentes = 2;

    lojas[1].componentes[0] = (struct Componente){3, "Processador i9-14900K", 650.00, 15};
    lojas[1].componentes[1] = (struct Componente){4, "Processador i7-14700K", 474.90, 20};
    lojas[1].num_componentes = 2;

    lojas[2].componentes[0] = (struct Componente){5, "Motherboard ATX Asus ROG Z790", 689.90, 20};
    lojas[2].componentes[1] = (struct Componente){6, "Motherboard ATX Gigabyte X670", 350.90, 35};
    lojas[2].num_componentes = 2;

    lojas[3].componentes[0] = (struct Componente){7, "Fonte ATX Corsair 1600W", 500.00, 30};
    lojas[3].componentes[1] = (struct Componente){8, "Fonte ATX CoolerMaster 1250W", 209.90, 40};
    lojas[3].num_componentes = 2;

    lojas[4].componentes[0] = (struct Componente){9, "RAM Kingston 32GB DDR5", 142.90, 45};
    lojas[4].componentes[1] = (struct Componente){10, "RAM Kingston 32GB DDR4", 79.90, 60};
    lojas[4].num_componentes = 2;

    while (1)
    {
        int escolha;
        printf("\n1. Login\n2. Signup\n3. Sair\nEscolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
            case 1:
                {
                    char email[50];
                    char password[20];

                    printf("Email: ");
                    scanf("%s", email);

                    printf("Password: ");
                    scanf("%s", password);

                    int index = login(utilizadores, totalUtilizadores, email, password);

                    if (index != -1) {
                        printf("Login bem-sucedido! Bem-vindo, %s!\n", utilizadores[index].nome);

                        int opcao;
                        do {
                            printf("\n1. Procurar por loja\n2. Procurar por produto\n3. Comprar produtos\n4. Voltar para a página principal\nEscolha: ");
                            scanf("%d", &opcao);
                            switch (opcao) {
                                case 1:
                                    {
                                        procurarLoja(lojas, MAX_LOJAS);
                                    }
                                    break;
                                case 2:
                                    {
                                        procurarProduto(lojas, MAX_LOJAS);
                                    }
                                    break;
                                case 3:
                                    {
                                        comprarProdutos(lojas, MAX_LOJAS);
                                    }
                                    break;
                                case 4:
                                    printf("A voltar para a página principal...\n");
                                    break;
                                default:
                                    printf("Opção inválida.\n");
                            }
                        } while (opcao != 4);
                    } else {
                        printf("Login incorreto.\n");
                    }
                }
                break;

            case 2:
                totalUtilizadores = signup(utilizadores, totalUtilizadores);
                break;

            case 3:
                printf("A fechar o programa...\n");
                return 0;

            default:
                printf("Escolha inválida.\n");
        }
    }

    return 0;
}
