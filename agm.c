#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
// CRIANDO UMA ESTRUTURA DE ARESTAS
struct Aresta
{
    int origem, dest, peso;
};
 
// CRIANDO UMA ESTRUTURA DE GRAFOS
struct Grafo
{
    int V, A;
    struct Aresta* aresta;
};
 
//CRIA UM GRAFO COM AS COORDENADAS PASSADAS PELO USUÁRIO NO INICIO
struct Grafo* criaGrafo(int V, int A)
{
    //CRIA UM PONTEIRO DO TIPO GRAFO E ALOCA ESPAÇO PARA ELE
    struct Grafo* grafo = (struct Grafo*) malloc( sizeof(struct Grafo) );
    
    grafo->V = V;
    grafo->A = A;

    // NO CAMPO DE ARESTA DO PONTEIRO CRIADO ACIMA RECEBE UM PONTEIRO DE ARESTAS ALOCANDO ESPAÇO 
    grafo->aresta = (struct Aresta*) malloc( grafo->A * sizeof( struct Aresta ) );
 
    return grafo;
}
 
/*CRIA UMA ESTRUTURA DE SUBGRAFO PARA OS VALORES ENCONTRADOS
  PAI LIGAÇÃO DE MAIOR PESO - RANK É A POSIÇÃO DAS LIGAÇÕES*/
struct subGrafo
{
    int pai;
    int rank;
};
 
//ENCONTRA AS ARESTAS DE MAIOR PESO
int encontrar(struct subGrafo subGrafos[], int i)
{  
    if (subGrafos[i].pai != i)
        subGrafos[i].pai = encontrar(subGrafos, subGrafos[i].pai);
 
    return subGrafos[i].pai;
}
 
//AQUI SÃO ADICIONADOS OS VALORES AO NOVO GRAFO, SE ELES NÃO FORMAREM CICLO SÃO INSERIDOS
void uniao(struct subGrafo subGrafos[], int x, int y)
{
    int nova = encontrar(subGrafos, x);
    int presente = encontrar(subGrafos, y);

    /*CRIANDO A ORDEM DE INSERÇÃO DE ACORDO COM O PESO
      SE O PESO DA NOVA LIGAÇÃO FOR MENOR QUE OS DEMAIS JÁ PRESENTES NO NOVO GRAFO MANTEM O PESO DA ANTERIOR EM CIMA
      AO CONTRÁRIO COLOQUE ESTA NOVA LIGAÇÃO COMO A DE MAIOR PESO   
    */
    if (subGrafos[nova].rank < subGrafos[presente].rank)
        subGrafos[nova].pai = presente;
    else if (subGrafos[nova].rank > subGrafos[presente].rank)
        subGrafos[presente].pai = nova;

    // SE O PESO DA NOVA LIGAÇÃO FOR O MESMO DA EXISTENTE COLOQUE-A NA PROXIMA POSIÇÃO 
    else
    {
        subGrafos[presente].pai = nova;
        subGrafos[nova].rank++;
    }
}
 
//COMPARANDO AS ARESTAS A FIM DE ENCONTAR A DE MAIOR PESO 
int comparacao(const void* a, const void* b)
{
    struct Aresta* a1 = (struct Aresta*)b;
    struct Aresta* b1 = (struct Aresta*)a;
    return a1->peso > b1->peso;
}
 
void arvoreMaxima(struct Grafo* grafo)
{
    int pesoTotal = 0;
    int V = grafo->V;
    struct Aresta resultado[V];
    int e = 0;
    int i = 0; 
 
    /*ORDENAR O GRAFO UTILIZANDO QUICKSORT. ORDEM = MAIORES PESOS E AS SUAS LIGAÇÕES*/
    qsort(grafo->aresta, grafo->A, sizeof(grafo->aresta[0]), comparacao);
 
    // CRIANDO UM PONTEIRO SUBGRAFO DO TAMANHO DO VÉRTICE SOMADO MAIS 10 PARA O CASO DE GRAFOS COM NUMERO DE ARESTAS BEM SUPERIOR
    struct subGrafo *subGrafos = (struct subGrafo*) malloc( V+10 * sizeof(struct subGrafo) );
    
    for (int v = 0; v < V; ++v)
    {
        subGrafos[v].pai = v;
        subGrafos[v].rank = 0;
    }
 
    //ENQUANTO O NUMERO DE VERTICES FOR V-1 ESCOLHE OS VERTICES DE MAIOR PESO
    while (e < V - 1)
    {
        struct Aresta next_aresta = grafo->aresta[i++];
        int x = encontrar(subGrafos, next_aresta.origem);
        int y = encontrar(subGrafos, next_aresta.dest);

        //SE NÃO FORMAR CICLO ADICIONE A ARESTA E SEU PESO    
        if (x != y)
        {
            resultado[e++] = next_aresta;
            uniao(subGrafos, x, y);
        }
    }
 
    //IMPRIMINDO O CAMINHO A SEGUIR DA ARVORE GERADORA MÁXIMA E A SOMA DOS SEUS PESSOS NO MELHOR CASO
    printf("Este é o caminho a seguir que trará o maior valor de peso\n");
    for (i = 0; i < e; ++i){
        printf("%d -- %d == %d\n", resultado[i].origem, resultado[i].dest, resultado[i].peso);
    	pesoTotal += resultado[i].peso;
    }
    printf("Ao seguir o caminho acima obterá a soma dos pesos igual á: %d\n",pesoTotal);	
    return;
}

void inicio(){
    
        int A, V, i, origem, destino, peso;

    //LENDO A QUANTIDADE DE VÉRTICES E ARESTAS PRESENTES NO GRAFO.   
        printf("Informe a quantidade de vertices e pressione [Enter]: ");
        scanf("%d",&V); 
        printf("Informe a quantidade de arestas e pressione [Enter]: ");
        scanf("%d",&A);

    //SETANDO ESTES VALORES NA ESTRUTURA GRAFO
        struct Grafo* grafo = criaGrafo(V, A);
 
    //LENDO TODAS AS LIGAÇÕES DO GRAFO 
      for(i =0; i<A;i++){
        
        system("clear");
        printf("Informe o vertice origem e pressione [Enter]: ");
        scanf("%d",&origem);
        grafo->aresta[i].origem = origem;
            
        printf("Informe o vertice destino e pressione [Enter]: ");
           scanf("%d",&destino);
        grafo->aresta[i].dest = destino;
            
        printf("Informe o peso da ligação e pressione [Enter] ");
        scanf("%d",&peso);
        grafo->aresta[i].peso = peso;
        
      }
    //CHAMANDO A FUNÇÃO ARVOREMAXIMA
    arvoreMaxima(grafo);
 
}


int main()
{
   int i, teste;
    
    //DEFININDO A QUANTIDADE DE VEZES QUE O ALGORÍTIMO SERÁ EXECUTADO.
    printf("Informe a quantidade de testes que deseja realizar\n");
    scanf("%d", &teste);

    for (i = 0; i <teste; i++)
    {
        inicio();
    }

    return 0;
}
