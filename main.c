#include <stdio.h>
#include <stdbool.h>
#include <string.h>

//remover a quantidade de um item do inventário (usado na opcao 2)
int remover_quantidade(char nomes[][50], int quantidades[], int *count, const char nome[], int quantidade) {

    int aux = -1;//posicao do nome
    
    //loop para achar o nome
    for (int i = 0; i < *count; i++) {
        if (strcmp(nomes[i], nome) == 0) {
            aux = i;
            break;
        }
    }

    //se nao achou o nome
    if (aux == -1) {
        return 0;
    }
    
    //se tentou remover uma quantidade invalida
    if (quantidades[aux] < quantidade) {
        return  quantidades[aux];
    }

    quantidades[aux] -= quantidade;

    //atualizar uma 
    if (quantidades[aux] == 0) {
        for (int i = aux; i < *count - 1; i++) {
            strcpy(nomes[i], nomes[i + 1]);
            quantidades[i] = quantidades[i + 1];
        }

        (*count)--;
        
        return -1;
    }

    return -2;
}

//Impressao do menu inicial e leitura da entrada
int iniciar(){

    printf("==================================\nControle de Estoque\n==================================\n"); //titulo
    printf("1. Adicionar Item\n2. Remover Item\n3. Listar Estoque\n4. Sair\n"); //opcoes

    bool valida = false; //variavel para validar a entrada

    int entrada;

    //loop para leitura da entrada
    while(valida == false){
  
        scanf(" %d", &entrada);

        char c;
        while ((c = getchar()) != '\n' && c != EOF);

        if(entrada == 1 || entrada == 2 || entrada == 3 || entrada == 4){
            valida = true;
        }
        else{
            printf("Opção Inválida! Tente Novamente.\n");
        }
    }

    return entrada;
}

//Opcao 1 - Adicionar
void adicionar(){

    char nome[50]; 
    int quantidade; 

    //leitura do item a ser adicionado (nome e quantidade)
    printf("Digite o nome do item: ");
    scanf("%s", &nome); 

    printf("Digite a quantidade: ");
    scanf("%d", &quantidade); 

    //abrir o arquivo inventory.txt
    FILE *inventario = fopen("inventory.txt", "a");

    //adicionar o item em inventory.txt
    fprintf(inventario, "%s\n%d\n", nome, quantidade);

    //mensagem de validacao
    printf("Item adicionado com sucesso!\n");

    fclose(inventario);

}

//Opcao 2 - Remover
void remover(){

    char nome[50];
    int quantidade;

    //leitura do item a ser removido(nome e quantidade)

    printf("Digite o nome do item: ");
    scanf("%s", &nome);

    printf("Digite a quantidade a ser removida: ");
    scanf("%d", &quantidade);

    //abrir o arquivo (salvar o inventario atual em um arquivo temporario)
    FILE *inventario = fopen("inventory.txt", "r");

    int count = 0; //contador das linhas

    char nomes[1000][50];//nomes dos itens do inventario
    int quantidades[1000]; //quantidade dos itens do inventario

    char nome_aux[50]; //auxiliar do nome do item
    int quantidade_aux; //auxiliar da quantidade do item

    while(fscanf(inventario, "%s %d", &nome_aux, &quantidade_aux) != EOF){
        strcpy(nomes[count], nome_aux);
        quantidades[count] = quantidade_aux;

        count++;
    }

    fclose(inventario);

    //remover a quantidade do item do inventario
    int resul = remover_quantidade(nomes, quantidades, &count, nome, quantidade);

    //validar remocao
    if(resul == 0) printf("Item não encontrado.\n");

    else if (resul > 0) printf("Estoque insuficiente. Quantidade disponível: %d\n", resul);

    else {
        //salvar o inventario atualizado
        FILE *inventario = fopen("inventory.txt", "w");

        for (int i = 0; i < count; i++) {
            fprintf(inventario, "%s\n%d\n", nomes[i], quantidades[i]);
        }

        fclose(inventario);
        
        //imprimir se o item foi removido
        if (resul == -1) printf("Item removido do estoque!\n");
        
        //imprimir se a quantidade foi atualizada
        else printf("Quantidade atualizada com sucesso!\n");
    }

}

//Opcao 3 - Listar
void listar(){

    //abrir o arquivo
    FILE *inventario = fopen("inventory.txt", "r");

    //verificar se está vazio (CORRIGIDO)
    int aux = fgetc(inventario);

    if(aux == EOF){
        printf("O estoque está vazio.\n");

        fclose(inventario);
        return;
    }

    printf("==================================\nEstoque Atual\n==================================\n"); // titulo
        

    //voltar para o inicio do arquivo
    rewind(inventario);

    char nome[50];
    int quantidade;

    //loop para ler o arquivo e imprimir os itens
    while(fscanf(inventario, "%s %d", nome, &quantidade) != EOF){
        printf("Nome: %s\nQuantidade: %d\n", nome, quantidade);
    }

    fclose(inventario);
}

//Opcao 4 - Encerrar
void encerrar(){
    printf("Obrigado por usar o Controle de Estoques! Até a próxima.\n");
}

int main(){
    
    while(true){
        int opcao = iniciar();
        
        if(opcao == 1) adicionar();
    
        else if (opcao == 2) remover();

        else if (opcao == 3) listar();
        
        else{
            encerrar();
            return 0;
        }
        
        char opcao_encerrar;
        
        printf("Deseja realizar outra operação? (s/n): ");
        
        char c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        scanf("%c", &opcao_encerrar);
        
        if(opcao_encerrar != 's'){
            printf("\nObrigado por usar o Controle de Estoques! Até a próxima.");
            return 0;
        }
    }
    

    return 0;

}
