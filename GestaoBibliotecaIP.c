//Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 10 //Quantidade maxima de livros

typedef struct { //Estrutura das informacoes do livro
    int id;
    char autor[100];
    char titulo[100];
    char editora[100];
    int ano;
    int situacao;
} Livro; //Nome da struct

typedef struct { //Estrutura da biblioteca
    int qntd;
    Livro livros[MAX]; 
} biblioteca; 
//funcoes para o programa
void cadastrar_Livro(biblioteca *b); //* ponteiro para a biblioteca;
void listar_Livros(biblioteca *b);
void procurar_Livro(biblioteca *b);
void remover_Livro(biblioteca *b);
void informacoes_dos_Livros(Livro *b);

int main() { //Funcao principal para o inicio e fim do programa
    biblioteca Biblioteca; //Biblioteca para armazenamento dos livros
    int opcao;
    Biblioteca.qntd = 0;

    do { //Menu
        printf("\nSelecione uma opcao abaixo:\n\n");
        printf("1 - Cadastrar Livro\n");
        printf("2 - Listar Livros\n");
        printf("3 - Procurar Livro\n");
        printf("4 - Remover livro\n");
        printf("5 - Sair\n");
        printf("Digite a opcao desejada: \n");
        scanf("%d", &opcao);
        getchar(); //limpa o buffer

        //switch com a finalidade de chamar as funcoes
        switch (opcao) {
            case 1:
                cadastrar_Livro(&Biblioteca);
                break;
            case 2:
                listar_Livros(&Biblioteca);
                break;
            case 3:
                procurar_Livro(&Biblioteca);
                break;
            case 4:
                remover_Livro(&Biblioteca);
                break;
            case 5:
                printf("Fechando o programa...\n");
                break;
            default:
                printf("Opcao invalida\n");
        }
    } while (opcao != 5); //o programa so fecha quando o usuario digitar 5

    return 0;
}

void remover_Livro(biblioteca *b) { //remove um livro da biblioteca pelo ID
    int id, i, encontrado = 0;      

    printf("Digite o ID do livro que deseja remover:\n");
    scanf("%d", &id);

    for (i = 0; i < b->qntd; i++) {
        if (b->livros[i].id == id) { //verifica se o ID digitado e igual ao ID de algum livro
            encontrado = 1; 
            break;
        }
    }

    if (!encontrado) { 
        printf("Livro nao encontrado\n");
        return;
    }

    for (int j = i; j < b->qntd - 1; j++) { //remove o livro
        b->livros[j] = b->livros[j + 1]; //posicao ocupada pelo livro removido e substituida pela posicao seguinte
    }
    b->qntd--;
    printf("Livro removido\n");
}

void informacoes_dos_Livros(Livro *b) { 
    FILE *arquivoID = fopen("biblioteca.txt", "a"); //abre o arquivo para mostrar as informacoes dos livros "a" serve para adicionar informacoes ao arquivo ja existente
    if (arquivoID == NULL){ //verifica se o arquivo foi aberto. NULL = serve para realizar a verificacao
        printf("Erro ao abrir o arquivo\n");
        return;
    }
    fprintf(arquivoID, "%d %s %s %s %d %d\n", b->id, b->autor, b->titulo, b->editora, b->ano, b->situacao); //b-> = ponteiro para a struct Livro 
    fclose(arquivoID); 
}

void procurar_Livro(biblioteca *b) { 
    int id, encontrado = 0;

    if (b->qntd == 0) { //verifica se ha algum livro cadastrado 
        printf("Nenhum livro cadastrado.\n");
        return;
    }

    printf("Digite o ID do livro que deseja procurar:\n");
    scanf("%d", &id);

    for (int i = 0; i < b->qntd; i++) { 
        if (b->livros[i].id == id) { //b->livros[i]. e o ponteiro para a struct livro sendo acessado pelo "i"
            printf("\nLivro encontrado:\n");
            printf("ID: %d\n", b->livros[i].id);
            printf("Titulo: %s\n", b->livros[i].titulo);
            printf("Autor: %s\n", b->livros[i].autor);
            printf("Editora: %s\n", b->livros[i].editora);
            printf("Ano: %d\n", b->livros[i].ano);
            printf("Situacao: %s\n", b->livros[i].situacao == 1 ? "Disponivel" : "Indisponivel");
            encontrado = 1; 
            break;
        }
    }

    if (!encontrado) {
        printf("Livro nao encontrado.\n");
    }
} 

void cadastrar_Livro(biblioteca *b) {
    if (b->qntd == MAX) { //faz a verificacao da quantidade de livros cadastrados
        printf("Limite excedido\n");
        return;
    }
    
    Livro adicionarLivro;
    printf("\nDigite o ID do livro:\n");
    scanf("%d", &adicionarLivro.id);
    getchar();

    printf("\nDigite o nome do autor:\n");
    fgets(adicionarLivro.autor, 100, stdin); //100, stdin = tamanho do vetor e entrada de dados
    adicionarLivro.autor[strcspn(adicionarLivro.autor, "\n")] = '\0';

    printf("\nDigite o titulo do livro:\n");
    fgets(adicionarLivro.titulo, 100, stdin);
    adicionarLivro.titulo[strcspn(adicionarLivro.titulo, "\n")] = '\0';

    printf("\nDigite a editora do livro:\n");
    fgets(adicionarLivro.editora, 100, stdin);
    adicionarLivro.editora[strcspn(adicionarLivro.editora, "\n")] = '\0';

    printf("\nDigite o ano do livro:\n");
    scanf("%d", &adicionarLivro.ano);

    printf("\nDigite a disponibilidade do livro (1 - Disponivel, 2 - Indisponivel): \n");
    scanf("%d", &adicionarLivro.situacao);

    b->livros[b->qntd] = adicionarLivro;
    b->qntd++;

    informacoes_dos_Livros(&adicionarLivro); //chama a funcao e passa o ponteiro para a struct Livro

    printf("\n\nLivro cadastrado!\n\n");
}

void listar_Livros(biblioteca *b){ //Lista todos os livros cadastrados
    if (b->qntd == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    //imprime as informacoes dos livros
    for (int i = 0; i < b->qntd; i++) { 
        printf("\nID: %d\n", b->livros[i].id); 
        printf("Titulo: %s\n", b->livros[i].titulo);
        printf("Autor: %s\n", b->livros[i].autor);
        printf("Editora: %s\n", b->livros[i].editora);
        printf("Ano: %d\n", b->livros[i].ano);
        printf("Situacao: %s\n", b->livros[i].situacao == 1 ? "Disponivel" : "Indisponivel");
    }
}
