# C++ — Conceitos (Módulo 05)

> Notas de estudo e referência. Tema do módulo: try/catch/throw, what(). Padrão: C++98.

---

## 1. try/catch/throw

A ideia central: exceção é um jeito de interromper o fluxo normal quando algo dá errado, sem precisar devolver código de erro a cada passo. Vou pelas quatro peças.

**`throw` — levantar a exceção**

Quando uma função detecta uma situação inválida, ela não retorna nada, ela lança um objeto:

```cpp
if (grade < 1)
    throw Bureaucrat::GradeTooHighException();
```

Isso cria um objeto da classe de exceção e aborta na hora a execução dali pra frente. Nenhuma linha depois do throw roda. O controle “salta pra fora” procurando quem saiba lidar com aquilo.

**`try / catch` — capturar**

Quem chama envolve o trecho arriscado num try e diz, no catch, o que fazer se algo for lançado:

```cpp
try
{
    Bureaucrat b("Bob", 200);        // 200 > 150, vai lançar
    std::cout << "nunca chega aqui" << std::endl;
}
catch (std::exception &e)
{
    std::cout << e.what() << std::endl;   // aqui sim
}
```

Se o try roda sem problema, o catch é ignorado. Se algo é lançado lá dentro, o C++ pula direto pro catch compatível. 
-> A linha do cout dentro do try não executa, o throw lá no construtor já desviou o fluxo.

**O que acontece no meio: stack unwinding**

Entre o throw e o catch, o C++ vai “desempilhando” tudo que estava vivo no caminho e chama o destrutor de cada objeto local -> igual ao desempilhamento no Módulo 01, só que disparado por uma exceção em vez de pelo fim normal do escopo. Isso é o que garante que nada vaza mesmo quando o programa toma esse atalho. Por isso exceção não é “gambiarra” —> ela limpa a casa ao sair.

**`catch` por referência e por que `std::exception`**

Você captura por referência (&) por dois motivos: evita copiar a exceção, e preserva o polimorfismo do CPP04. Como as exceções herdam de std::exception, um único catch `(std::exception &e)` pega qualquer uma delas -> GradeTooHigh, GradeTooLow, e até exceções da STL. É o ponteiro/referência-pra-base apontando pra derivada, de novo.

**`what()` — a mensagem**

std::exception tem um método virtual what() que devolve a descrição do erro. Você sobrescreve nas suas classes:

```cpp
class GradeTooHighException : public std::exception
{
    public:
        const char *what() const throw();
};

const char *GradeTooHighException::what() const throw()
{
    return ("Grade too high");
}
```

Dois detalhes de C++98 que a régua cobra: o retorno é const char * (não std::string), e a assinatura termina em throw() — a promessa “este método não lança nada”. Em C++11 isso virou noexcept, mas aqui o padrão é 98, então é throw() mesmo.

O throw dentro do construtor, a parte mais importante

Esse é o ponto que a gente tocou no ex00. Um construtor não tem return, então como ele avisa “não consegui criar um objeto válido”? Lançando exceção. E aí entra uma garantia forte do C++:

>se um construtor lança, o objeto nunca termina de ser construído, ele não passa a existir.

```cpp
Bureaucrat::Bureaucrat(const std::string &name, int grade) : name(name), grade(grade)
{
    if (grade < 1)
        throw GradeTooHighException();   // objeto é abortado aqui
    if (grade > 150)
        throw GradeTooLowException();
}
```

Consequências práticas:

Nunca vai existir um Bureaucrat com grade 0 ou 999. Ou ele nasce válido, ou não nasce. Isso é o que torna o atributo confiável no resto do programa — você não precisa checar validade toda hora depois.
O destrutor desse objeto não roda, porque ele nunca ficou pronto. (Os membros que já tinham sido construídos na lista de inicialização — tipo o name — esses sim são destruídos, via o stack unwinding.)
Por isso a validação fica no corpo do construtor, depois da lista de inicialização: a lista já rodou, e o throw interrompe antes de o objeto ser dado como concluído.

---

## Classes Aninhadas (Nested Classes)

- No exemplo do ex00 elas moram dentro do Bureaucrat e são acessadas como `Bureaucrat::GradeTooHighException`

