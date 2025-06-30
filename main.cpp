#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include <limits>
#include <locale>

class ContaBancaria
{
protected:
    std::string numeroConta;
    double saldo;
    std::string tipoConta;

public:
    ContaBancaria(std::string numConta, double saldoInicial, std::string tipo)
        : numeroConta(numConta), saldo(saldoInicial), tipoConta(tipo)
    {
    }

    virtual void sacar(double valor)
    {
        if (valor <= 0)
        {
            throw std::invalid_argument("Valor de saque inválido.");
        }
        saldo -= valor;
        std::cout << "[SUCESSO] Saque de R$" << valor
            << " realizado. Saldo atual: R$" << saldo << std::endl;
    }

    virtual void depositar(double valor)
    {
        if (valor <= 0)
        {
            throw std::invalid_argument("Valor de depósito inválido.");
        }
        saldo += valor;
        std::cout << "[SUCESSO] Depósito de R$" << valor
            << " realizado. Saldo atual: R$" << saldo << std::endl;
    }

    virtual void verSaldo()
    {
        std::cout << "[SALDO] Conta " << tipoConta << " (" << numeroConta
            << "): R$" << saldo << std::endl;
    }

    std::string getTipoConta() const { return tipoConta; }
    std::string getNumeroConta() const { return numeroConta; }

    virtual ~ContaBancaria() {}
};

class ContaCorrente : public ContaBancaria
{
public:
    ContaCorrente(std::string numConta, double saldoInicial)
        : ContaBancaria(numConta, saldoInicial, "Corrente")
    {
    }
};

class ContaPoupanca : public ContaBancaria
{
public:
    ContaPoupanca(std::string numConta, double saldoInicial)
        : ContaBancaria(numConta, saldoInicial, "Poupança")
    {
    }
};

class ContaSalario : public ContaBancaria
{
public:
    ContaSalario(std::string numConta, double saldoInicial)
        : ContaBancaria(numConta, saldoInicial, "Salário")
    {
    }
};

class ContaInvestimento : public ContaBancaria
{
public:
    ContaInvestimento(std::string numConta, double saldoInicial)
        : ContaBancaria(numConta, saldoInicial, "Investimento")
    {
    }
};

template <typename T>
class VerificacaoSaldo : public T
{
public:
    template <typename... Args>
    VerificacaoSaldo(Args... args) : T(args...) {}

    void sacar(double valor) override
    {
        if (valor > this->saldo)
        {
            std::cerr << "[LOG DE ERRO] Saldo insuficiente na conta " << this->getTipoConta()
                << " (" << this->getNumeroConta() << "). Tentativa de saque: R$" << valor << std::endl;
            throw std::runtime_error("Saldo insuficiente.");
        }
        T::sacar(valor);
    }
};

void exibirMenu()
{
    std::cout << "\n=== SISTEMA BANCÁRIO ===" << std::endl;
    std::cout << "1. Criar Conta" << std::endl;
    std::cout << "2. Sacar" << std::endl;
    std::cout << "3. Depositar" << std::endl;
    std::cout << "4. Ver Saldo" << std::endl;
    std::cout << "5. Sair" << std::endl;
    std::cout << "Escolha uma opção: ";
}

void exibirTiposConta()
{
    std::cout << "\nTipos de Conta:" << std::endl;
    std::cout << "1. Corrente" << std::endl;
    std::cout << "2. Poupança" << std::endl;
    std::cout << "3. Salário" << std::endl;
    std::cout << "4. Investimento" << std::endl;
    std::cout << "Escolha o tipo: ";
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    std::vector<ContaBancaria*> contas;
    int opcao;

    do
    {
        exibirMenu();
        std::cin >> opcao;

        try
        {
            switch (opcao)
            {
            case 1: {
                std::string numConta;
                double saldoInicial;
                int tipo;

                exibirTiposConta();
                std::cin >> tipo;

                std::cout << "Número da Conta: ";
                std::cin >> numConta;
                std::cout << "Saldo Inicial: R$";
                std::cin >> saldoInicial;

                switch (tipo)
                {
                case 1: contas.push_back(new VerificacaoSaldo<ContaCorrente>(numConta, saldoInicial)); break;
                case 2: contas.push_back(new VerificacaoSaldo<ContaPoupanca>(numConta, saldoInicial)); break;
                case 3: contas.push_back(new VerificacaoSaldo<ContaSalario>(numConta, saldoInicial)); break;
                case 4: contas.push_back(new VerificacaoSaldo<ContaInvestimento>(numConta, saldoInicial)); break;
                default: throw std::invalid_argument("Tipo de conta inválido.");
                }
                std::cout << "[SUCESSO] Conta criada!" << std::endl;
                break;
            }
            case 2: {
                if (contas.empty()) throw std::runtime_error("Nenhuma conta cadastrada.");

                std::string numConta;
                double valor;

                std::cout << "Número da Conta: ";
                std::cin >> numConta;

                for (auto& conta : contas)
                {
                    if (conta->getNumeroConta() == numConta)
                    {
                        std::cout << "Valor do Saque: R$";
                        std::cin >> valor;
                        conta->sacar(valor);
                        goto next;
                    }
                }
                throw std::runtime_error("Conta não encontrada.");
            }
            case 3: {
                if (contas.empty()) throw std::runtime_error("Nenhuma conta cadastrada.");

                std::string numConta;
                double valor;

                std::cout << "Número da Conta: ";
                std::cin >> numConta;

                for (auto& conta : contas)
                {
                    if (conta->getNumeroConta() == numConta)
                    {
                        std::cout << "Valor do Depósito: R$";
                        std::cin >> valor;
                        conta->depositar(valor);
                        goto next;
                    }
                }
                throw std::runtime_error("Conta não encontrada.");
            }
            case 4: {
                if (contas.empty()) throw std::runtime_error("Nenhuma conta cadastrada.");

                for (auto& conta : contas)
                {
                    conta->verSaldo();
                }
                break;
            }
            case 5: std::cout << "Saindo..." << std::endl; break;
            default: throw std::invalid_argument("Opção inválida.");
            }
        next:;
        }
        catch (const std::exception& e)
        {
            std::cerr << "[ERRO] " << e.what() << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    } while (opcao != 5);

    for (auto& conta : contas)
    {
        delete conta;
    }

    return 0;
}