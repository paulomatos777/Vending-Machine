#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//criando primeiro no da pilha
struct no_produto {
  char produto[30];
  struct no_produto *next;
};

//no com ponteiro para o topo
struct pilha_produto {
  struct no_produto *topo;
  int tamanho;
};

//funcao criar pilha
struct pilha_produto *criar_pilha_produto(void)
{
  struct pilha_produto *apilha;
  apilha = (struct pilha_produto *)malloc(sizeof(struct pilha_produto));
  if (apilha != NULL) {
    apilha->topo = NULL;
    apilha->tamanho = 0;
  }
  return apilha;
}

//funcao push
void empilhar_produto(struct pilha_produto *apilha, char produto[])
{
  //declarar-Alocar-Guardar
  struct no_produto *novoelemento;//declaro
  novoelemento = (struct no_produto *)malloc(sizeof(struct no_produto));//aloco
  //guardo
  strcpy(novoelemento->produto, produto);
  novoelemento->next = apilha->topo;
  //atualizar valores da estrutura pilha_produto apilha->topo
  apilha->topo = novoelemento;
  apilha->tamanho = apilha->tamanho + 1;

}

//funcao pop
void desempilhar_produto(struct pilha_produto *apilha)
{
  struct no_produto *aux = NULL;
  char valor_a_remover[30];
  if (apilha->topo != NULL) {
    aux = apilha->topo;
    strcpy(valor_a_remover, aux->produto);

    apilha->topo = aux->next;
    apilha->tamanho = apilha->tamanho - 1;
    free(aux);

  }
  //return valor_a_remover;
}

void imprimir_pilha_produtos(struct pilha_produto *apilha)
{
  struct no_produto *atual;
  atual = apilha->topo;
  while (atual != NULL) {
     printf("%s\n", atual->produto);
     atual = atual->next;
   }
}


int main(void)
{
  struct pilha_produto **slots;

  //struct pilha *apilha = criarpilha();
  //printf("push X para empilhar:\npop X para desempilhar\ni para imprimir pilha\n");
  char entrada[30],  produto[30], caractere, linha[50];
  int i, read_bytes;
  float valor, soma_custo = 0, precos[10];
  const int n = 10;

  //printf("\nProdutos :\n");
  // cadastrando produtos na vending machine
  for (i = 0; i < n; i++) {
    // alocando memoria para cada pilha/slot
    slots[i] = criar_pilha_produto();
    // lendo produto a produto
    do {
      scanf("%s", produto);
      empilhar_produto(slots[i], produto);
    } while (getchar() != '\n');
  }
  //getchar();
  // //printf("\nLendo Precos :\n");
  for (i = 0; i < n; i++)
    scanf("%f", &precos[i]);

  // printf("\nPrecos Lidos:\n");
  // for (i = 0; i < n; i++){
  //   printf("\nSlot %d :\n",i);
  //   imprimir_pilha_produtos(slots[i]);
  // }


  // for (i = 0; i< n; i++){
  //   printf("%.2f ", precos[i]);
  // }
  printf("\n");

  // Lendo os produtos que o usuário deseja comprar
  do {
    // procurando produto nos slots e desempilhando produto do slot correto
    //strcpy(produto, "");
    if (scanf("%s", produto) == EOF) {
      break;
    } else {
      for (i = 0; i < n; i++) {
        if (slots[i]->topo != NULL && strcmp(produto, slots[i]->topo->produto) == 0) {
          if (i == 5)
            printf("Opa, um item 0800!\n");
          else
            soma_custo = soma_custo + precos[i];
          desempilhar_produto(slots[i]);
          break;
        }
      }
      // verificando se o loop terminou (não conseguiu encontrar produto)
      if (i == n)
        printf("\nNao temos %s disponivel no momento.", produto);
    }
  }while (getchar() != EOF ); // criterio de parada EOF : fim do arquivo ou CTRL+D

  printf("\nCompras realizadas com sucesso. Voce gastou R$%.2f", soma_custo);
  //return 0;

}

