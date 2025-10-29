#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define tam 26

typedef struct Nodo
{
    char conteudo[100]; // conteudo é o IP que será marcado no final da trie
    int marcanodo; // marcanodo é a flag que marca o final da trie
    struct Nodo* prox; // prox para acessar o prox
    struct Nodo* filho[tam]; // filho que é o da raiz (pai)
}Nodo;

Nodo* CriaNodo()
{
    int i;

    struct Nodo *r = (Nodo *)malloc(sizeof(Nodo)); // aloca o nodo r

    r->marcanodo = 0; // começa marcando nodo como 0
    r->prox = NULL; // começa marcando o prox como NULL

    for (i = 0; i < tam; i++)
        r->filho[i] = NULL; // marca os filhos da raiz como NULL

    return r; // retorna a raiz
}

int busca(Nodo *r, char *s) // funcao que busca a trie
{
    if(*s == '.') // se encontrar .
    {
        if(r->prox == NULL) // se o prox da raiz for NULL
        {
            printf("endereco nao encontrado.\n"); // diz que nao encontrou o endereco
            return; // return para sair
        }
        else // se nao
        {
            r = r->prox; // percorre para o proximo da raiz
            s++; // percorre a string
        }
    }

    else if(*s == '\0') // se chegou no final da string
    {
        if(r->marcanodo == 0) // verifica se o nodo esta marcado
        {
            printf("endereco nao encontrado.\n"); // imprime que nao encontrou
            return; // return para sair
        }
        else // se está marcado
        {
            printf("%s\n", r->conteudo); // imprime o conteudo(IP)
            return; // return para sair
        }
    }

    else if(r->filho[*s - 'a'] == NULL) // se o filho for igual a NULL
    {
        printf("endereco nao encontrado.\n"); // imprime endereço não encontrado
        return; // return para sair
    }
    else // se não
    {
        r = r->filho[*s - 'a']; // percorre a trie
        s++; // percorre a string
    }

    return busca(r,s); // return busca para o proximo nodo filho
}

void insere(Nodo *r, char *s, char *conteudo) // funcao que insere na trie
{
    Nodo* raiz = r; // começa pelo nodo raiz

    if(*s == '.') // se encontrar .
    {
        if(raiz->prox == NULL) // se o prox for NULL
        {
            raiz->prox = CriaNodo(); // cria um nodo para o prox
            raiz = raiz->prox; // percorre para o proximo da raiz
            s++; // percorre a string
        }
        else // se nao
        {
            raiz = raiz->prox; // percorre para o proximo da raiz
            s++; // percorre a string
        }
    }

    if(*s == '\0') // se chegou no final da string
    {
        raiz->marcanodo = 1;    // marca o nodo atual como folha
        strcpy(raiz->conteudo,conteudo); // insere o IP(conteudo) no final da trie parecido com o marcanodo
        return; // return para sair
    }
    else // se nao
    {
        // cria um novo nodo se o caminho nao existir
        if(raiz->filho[*s - 'a'] == NULL)
        raiz->filho[*s - 'a'] = CriaNodo();
    }
    raiz = raiz->filho[*s - 'a']; // percorre a trie
    s++; // percorre a string
    insere(raiz, s, conteudo); // vai para o proximo nodo filho
}

void inverte(char *s) // funcao para inverter a string
{
    char invertida[100]; // string auxiliar
    int i;
    int j=0; // j para percorrer normalmente
    int tamanho = strlen(s); // pega o tamanho da string

    for(i=tamanho-1; i>=0;i--) // esse for percorre de trás para frente
    {
        invertida[j] = s[i]; // invertida[inicio] = s[fim]
        j++;
    }
    for(i=0; i< tamanho;i++) // outro for para passar a string invertida para a string utilizada na trie
    {
        s[i] = invertida[i]; // recebe a string invertida
    }
}

void liberatrie(Nodo* r)
{
    int i;
    r->marcanodo = 0; // marca o nodo como 0
    r->prox = NULL; // marca o prox como NULL
    for (i = 0; i < tam; i++)
    r->filho[i] = NULL; // marca os filhos da raiz como NULL
    free(r); // libera memória do nodo raiz
}

int main()
{
    FILE *file; // cria um arquivo

    Nodo* r = CriaNodo(); // cria o nodo da trie

    file = fopen("dns.txt", "r"); // abre o arquivo como leitura

    char s[100]; // string que será utilizada nas funções
    char conteudo[100]; // conteudo que é o IP que será marcado no final da string/trie

    while(fscanf(file,"%s %s",s,conteudo) != EOF) // pega o endereço e depois o IP até chegar no final do arquivo
    {
        inverte(s); // inverte a string
        insere(r,s,conteudo); // insere na trie
    }

    while(*s != '*') // enquanto não digitar *
    {
        scanf("%s", s); // le a string do usuario
        inverte(s); // inverte a string
        if(*s != '*') // se a string for diferente de *
        busca(r,s); // busca na trie
    }

    fclose(file); // fecha o arquivo
    liberatrie(r); // libera a memória da trie

    return 0;
}
