# CheatSheet — C++ Module 00

## Pré-requisitos

- [ ] O código compila com `c++` e as flags `-Wall -Wextra -Werror`
- [ ] O projeto segue o padrão **C++98** — funções ou contêineres C++11 (e posteriores) **não** são esperados

### 🚫 Não avaliar o exercício se…

- Uma função é implementada em um arquivo de cabeçalho *(exceto funções de template)*
- O Makefile compila sem as flags necessárias e/ou com outro compilador que não seja `c++`

### 🏴 Sinalizar com "Função Proibida" se houver…

- Uso de uma função **C** (`*alloc`, `*printf`, `free`)
- Uso de uma função não permitida nas diretrizes do exercício
- Uso de `using namespace <ns_name>` ou da palavra-chave `friend`
- Uso de biblioteca externa ou recursos de versões diferentes de C++98

---

## Exercício 00: Megafone

> Aquecimento para descobrir fluxos de I/O C++ básicos.

### Makefile

- [ ] Existe um Makefile que compila usando as flags apropriadas

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Está funcionando?

Desenvolver um programa `to_upper` com comportamento específico quando executado **sem nenhum parâmetro**.

- [ ] Resolvido em uma abordagem C++ (strings/upper)

---

## Exercício 01: Minha Agenda Incrível

> Escrever classes simples e um pequeno programa interativo que as utiliza.
> Se o exercício não estiver totalmente funcional, **avalie o que pode ser avaliado**.

### Makefile

- [ ] Existe um Makefile que compila usando as flags apropriadas

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Tratamento de erros

Requer um pouco de tratamento de erros, mas **não há comportamentos esperados no subject**.
Sair ou outro tratamento está bem. **Segfault não!** :D

`Rate it from 0 (failed) through 5 (excellent)`

### O comando EXIT

- [ ] Avaliar o comando `EXIT` conforme descrito no subject

### Visibilidade

- [ ] Os atributos da classe `Contact` são **privados**
- [ ] A classe expõe os **acessadores** correspondentes
- [ ] Tudo que só é usado dentro de uma classe é privado *(não apenas na `Contact`)*
- [ ] Tudo que pode ser usado fora de uma classe é público

> 💡 Iniciantes tendem a colocar tudo em público — não é isso que você quer aqui!

`Rate it from 0 (failed) through 5 (excellent)`

### As classes Contact e Phonebook

- [ ] Existe uma classe `Contact` *(ou qualquer nome que o aluno tenha dado)*
- [ ] Essa classe tem atributos para **cada campo** de contato
- [ ] Existe uma classe `Phonebook` contendo um **array de `Contact`s**

### Loop Read/Eval

- [ ] O programa tem um loop read/eval: lê a entrada, processa, e espera outro comando até `EXIT`
- [ ] O loop é feito de **forma C++** (`std::cin`)

### O comando ADD

- [ ] Avaliar o comando `ADD` conforme descrito no subject

`Rate it from 0 (failed) through 5 (excellent)`

### O comando SEARCH

- [ ] Avaliar o comando `SEARCH` conforme descrito no subject

> 📌 **A formatação da saída pode ser diferente, não importa.**
> Esta parte é sobre usar os **iomanips** do C++ — é nisso que você deve se concentrar.

`Rate it from 0 (failed) through 5 (excellent)`
