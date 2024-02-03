#include <stdio.h>
#include <string.h>

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

// Função para realizar o registo
int signup(struct Utilizador utilizadores[], int totalUtilizadores)
{
    struct Utilizador novoUtilizador;

    printf("Nome: ");
    scanf("%s", novoUtilizador.nome);

    printf("Email: ");
    scanf("%s", novoUtilizador.email);

    printf("Idade: ");
    scanf("%d", &novoUtilizador.idade);

    printf("Telefone: ");
    scanf("%d", &novoUtilizador.contacto);

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
