#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_UTILIZADORES 100

// Estrutura para armazenar informações do utilizador
struct Utilizador {
    char nome[35];
    int idade;
    char email[50];
    int contacto;
    char password[20];
    char confirmarPassword[20];
};

// Função para realizar o login
int login(struct Utilizador utilizadores[], int totalUtilizadores, char email[], char password[])
{
    // Ciclo para percorrer todos os utilizadores
    for (int i = 0; i < totalUtilizadores; ++i)
    {
        if (strcmp(utilizadores[i].email, email) == 0 && strcmp(utilizadores[i].password, password) == 0) // Verifica se o email e pass introduzidas existem no array utilizadores
        {
            return i;  // Retorna o índice do usuário encontrado
        }
    }
    return -1;  // Retorna -1 se o login falhar
}

// Função para verificar se uma string contém apenas letras
int contemApenasLetras(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isalpha(str[i]))
        {
            return 0; // Se não for uma letra, retorna 0
        }
    }
    return 1; // Se passar por todos os caracteres e todos forem letras, retorna 1
}

// Função para realizar o registo
int signup(struct Utilizador utilizadores[], int totalUtilizadores)
{
    struct Utilizador novoUtilizador;

    // Loop até que o registo seja bem-sucedido
    do
    {
        printf("Nome: ");
        scanf("%s", novoUtilizador.nome);

        // Verifica se o nome contém apenas letras
        if (!contemApenasLetras(novoUtilizador.nome))
        {
            printf("Erro! O nome deve conter apenas letras.\n");
            continue;
        }

        printf("Email: ");
        scanf("%s", novoUtilizador.email);

        // Verifica se o email contém '@'
        if (strchr(novoUtilizador.email, '@') == NULL)
        {
            printf("Erro! O email deve conter '@'.\n");
            continue;
        }

        printf("Idade: ");
        if (scanf("%d", &novoUtilizador.idade) != 1 || novoUtilizador.idade <= 0)
        {
            printf("Erro! Idade inválida. A idade deve ser maior que 0.\n");
            while (getchar() != '\n');  // Limpa o buffer do teclado
            continue;
        }

        printf("Telefone: ");
        char telefone[20]; // Usamos uma string para armazenar temporariamente o telefone
        scanf("%s", telefone);

        // Verifica se o telefone contém apenas dígitos
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

        // Se chegou até aqui, convertemos o telefone para inteiro e atribuímos à estrutura
        novoUtilizador.contacto = atoi(telefone);

        printf("Password: ");
        scanf("%s", novoUtilizador.password);

        printf("Confirmar a password: ");
        scanf("%s", novoUtilizador.confirmarPassword);

        if (strcmp(novoUtilizador.password, novoUtilizador.confirmarPassword) == 0)
        {
            // Adiciona o novo usuário ao array
            utilizadores[totalUtilizadores] = novoUtilizador;
            printf("Registo bem-sucedido!\n");
            return totalUtilizadores + 1;  // Retorna o novo total de usuários
        }
        else
        {
            printf("Erro! As passwords devem ser iguais.\n");
        }
    } while (1);
}

int main()
{
    struct Utilizador utilizadores[MAX_UTILIZADORES];
    int totalUtilizadores = 0;

    // Ciclo que continua sempre a percorrer até que retorne 0
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
                        // Após o login bem-sucedido, ofereça opções adicionais
                        int opcao;
                        do {
                            printf("\n1. Procurar por loja\n2. Procurar por produto\n3. Voltar para a página de login/signup\nEscolha: ");
                            scanf("%d", &opcao);
                            switch (opcao) {
                                case 1:
                                    printf("Opção 'Procurar por loja' selecionada.\n");
                                    // Lógica para procurar por loja
                                    break;
                                case 2:
                                    printf("Opção 'Procurar por produto' selecionada.\n");
                                    // Lógica para procurar por produto
                                    break;
                                case 3:
                                    printf("Voltando para a página de login/signup...\n");
                                    break;
                                default:
                                    printf("Opção inválida. Por favor, escolha novamente.\n");
                            }
                        } while (opcao != 3); // Continue até que o usuário opte por voltar
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
