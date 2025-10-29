# DNSTrieSimulator

# Simulador de DNS com Árvore Trie

Este é um programa em C que simula um resolvedor de DNS (Sistema de Nomes de Domínio) simples. Ele usa uma estrutura de dados **Trie (árvore de prefixo)** modificada para armazenar e consultar rapidamente nomes de domínio e seus endereços IP correspondentes.

## Como Funciona

### 1. Carregamento de Dados
* O programa lê um arquivo chamado `dns.txt` na inicialização.
* Espera-se que este arquivo contenha pares de `[nome_do_dominio]` e `[endereco_IP]` em cada linha.
    ```
    google.com 172.217.14.228
    exemplo.org 93.184.216.34
    ```

### 2. Inversão de Strings
* Uma característica principal deste código é a função `inverte`. Antes de um nome de domínio ser inserido ou buscado na Trie, ele é **invertido**.
* Por exemplo, `google.com` é armazenado e buscado como `moc.elgoog`.
* Isso é feito para que a Trie agrupe os domínios pelo seu TLD (Top-Level Domain) primeiro (todos os `.com`, depois todos os `.org`, etc.), otimizando a estrutura.

### 3. Estrutura da Trie Modificada
O `struct Nodo` foi adaptado para essa tarefa:

* `filho[26]`: Armazena os ponteiros para os próximos caracteres (`a`-`z`).
* `prox`: Este é um ponteiro especial. Em vez de tratar o `.` como um caractere filho, ele é usado para "pular" para o próximo segmento do domínio (ex: de `moc` para `elgoog`).
* `marcanodo` e `conteudo`: Quando um domínio completo é inserido, o último nó é marcado (`marcanodo = 1`) e o endereço IP (`conteudo`) é armazenado nele.

### 4. Execução e Busca
* Após carregar o `dns.txt` na memória (dentro da Trie), o programa entra em um loop e aguarda a entrada do usuário.
* O usuário digita um nome de domínio (ex: `exemplo.com`).
* O programa inverte a entrada (`moc.elpmaxe`) e a procura na Trie.
* Se o domínio invertido for encontrado e estiver marcado como um nó final, o endereço IP associado é impresso.
* Caso contrário, ele imprime "endereco nao encontrado."
* O programa termina quando o usuário digita `*`.
