# Sistema Bancário C++ com Abordagem de Aspectos

Este repositório contém uma implementação de um sistema bancário simples em C++, explorando uma abordagem inspirada em Programação Orientada a Aspectos (AOP) para lidar com preocupações transversais, como a verificação de saldo.

## 🚀 Visão Geral do Projeto

O projeto simula um sistema bancário básico, permitindo a criação de diferentes tipos de contas (Corrente, Poupança, Salário, Investimento), e a realização de operações como saque, depósito e consulta de saldo. O diferencial reside na forma como a validação de saldo para saques é injetada nas operações, emulando conceitos de AOP sem o uso de frameworks AOP externos como o AspectJ, que foi a ferramenta sugerida para a abordagem.

## ✨ Conceitos de AOP em C++

A implementação utiliza **templates de classes** e **herança** para "envolver" as classes de conta base (`ContaBancaria` e suas subclasses), adicionando funcionalidades de forma modular.

A classe `VerificacaoSaldo<T>` atua como um "aspecto" (ou *mixin* de comportamento) que adiciona a lógica de verificação de saldo antes que a operação de saque da conta subjacente (`T`) seja executada. Isso desacopla a lógica de validação da lógica de negócio principal da conta.

## ⚙️ Funcionalidades

* **Criação de Contas:**
    * Conta Corrente
    * Conta Poupança
    * Conta Salário
    * Conta Investimento
* **Operações Bancárias:**
    * Saque (com verificação de saldo automatizada)
    * Depósito
    * Consulta de Saldo
* **Tratamento de Erros:** Utilização de exceções para lidar com entradas inválidas, saldo insuficiente e contas não encontradas.
* **Localização:** Configuração para `Portuguese` para exibição de mensagens.

## 🛠️ Tecnologias Utilizadas

* **C++11/14/17:** Linguagem principal para desenvolvimento.
* **Compilador:** Compatível com padrões C++ modernos (ex: g++, Clang, MSVC).

## 🚀 Como Compilar e Executar

### Pré-requisitos

Certifique-se de ter um compilador C++ moderno (como g++ ou Clang) instalado em seu sistema.

* **No Linux/macOS (com g++ ou Clang):**
    ```bash
    sudo apt update
    sudo apt install build-essential # Para Linux (Ubuntu/Debian)
    # ou
    xcode-select --install # Para macOS
    ```
* **No Windows (com MinGW-w64 ou MSVC):**
    * Instale [MinGW-w64](https://www.mingw-w64.org/doku.php/download) e certifique-se de que o `g++` esteja no seu PATH.
    * Ou use o [Visual Studio Community](https://visualstudio.microsoft.com/pt-br/vs/community/) com as ferramentas de desenvolvimento C++.

### Compilação

Navegue até o diretório raiz do projeto no seu terminal e compile o código-fonte:

```bash
g++ main.cpp -o sistema_bancario -std=c++17 -Wall
main.cpp: Substitua pelo nome do seu arquivo principal, se for diferente.

-o sistema_bancario: Define o nome do executável de saída.

-std=c++17: Garante que o código seja compilado com o padrão C++17 (pode ser c++11 ou c++14 dependendo da sua versão do compilador e recursos utilizados).

-Wall: Habilita todos os avisos do compilador (boa prática).

Execução
Após a compilação, execute o programa:

Bash

./sistema_bancario
No Windows, você pode precisar apenas de sistema_bancario.exe.

🧑‍💻 Exemplo de Uso (no terminal)
=== SISTEMA BANCÁRIO ===
1. Criar Conta
2. Sacar
3. Depositar
4. Ver Saldo
5. Sair
Escolha uma opção: 1

Tipos de Conta:
1. Corrente
2. Poupança
3. Salário
4. Investimento
Escolha o tipo: 1
Número da Conta: 12345
Saldo Inicial: R$1000
[SUCESSO] Conta criada!

=== SISTEMA BANCÁRIO ===
...
Escolha uma opção: 2
Número da Conta: 12345
Valor do Saque: R$1200
[LOG DE ERRO] Saldo insuficiente na conta Corrente (12345). Tentativa de saque: R$1200
[ERRO] Saldo insuficiente.

=== SISTEMA BANCÁRIO ===
...
Escolha uma opção: 4
[SALDO] Conta Corrente (12345): R$1000
📝 Estrutura do Código
ContaBancaria (Base Class): Define a interface e comportamento comum para todas as contas.

ContaCorrente, ContaPoupanca, ContaSalario, ContaInvestimento (Derived Classes): Implementam os tipos específicos de conta.

VerificacaoSaldo<T> (Aspect/Wrapper): Uma classe template que "decora" as classes de conta, injetando a lógica de verificação de saldo antes de cada saque.

exibirMenu(), exibirTiposConta(): Funções utilitárias para a interface do usuário.

main(): Ponto de entrada do programa, gerencia o fluxo de execução e a interação com o usuário.

🤝 Contribuições
Contribuições são bem-vindas! Se você tiver sugestões, melhorias ou encontrar bugs, sinta-se à vontade para:

Abrir uma Issue para relatar um bug ou sugerir uma feature.

Criar um Pull Request com suas alterações.

📄 Licença
Este projeto está licenciado sob a Licença MIT. Veja o arquivo LICENSE para mais detalhes.
