# CheatSheet — C++ Module 04

## Pré-requisitos

- [x] O código compila com `c++` e as flags `-Wall -Wextra -Werror`
- [x] O projeto segue o padrão **C++98** — funções ou contêineres C++11 (e posteriores) **não** são esperados
- [x] Nenhuma função implementada dentro de um arquivo de cabeçalho (exceto templates)
- [x] Nenhuma função proibida usada (`*alloc`, `*printf`, `free`, `using namespace`, `friend`)

### 🚫 Não avaliar o exercício se…

- Uma função é implementada em um arquivo de cabeçalho *(exceto funções de template)*
- O Makefile compila sem as flags necessárias e/ou com outro compilador que não seja `c++`

### 🏴 Sinalizar com "Função Proibida" se houver…

- Uso de uma função **C** (`*alloc`, `*printf`, `free`)
- Uso de uma função não permitida nas diretrizes do exercício
- Uso de `using namespace <ns_name>` ou da palavra-chave `friend`
- Uso de biblioteca externa ou recursos de versões diferentes de C++98

---

## Exercício 00: Polymorphism

> `Animal` com `type` protegido, `Dog`/`Cat` herdando dele, e o par `WrongAnimal`/`WrongCat` mostrando o que acontece sem `virtual`.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas

### Classe Animal

- [x] `Animal` tem o atributo `type` (`std::string`)
- [x] Dá pra instanciar e usar a classe normalmente

### Herança

- [x] `Dog` e `Cat` herdam de `Animal`
- [x] Mensagens de construtor/destrutor claras e diferentes por classe (cor própria por classe, ver `concepts.md`)

### Atributo type por classe derivada

- [x] `type` é setado certo na criação de cada animal (`"Dog"` pro Dog, `"Cat"` pro Cat)

### makeSound() e o par Wrong

- [x] `makeSound()` é `virtual` em `Animal` — chamar via `Animal*` sempre usa a versão certa da classe real
- [x] Existe o exemplo `WrongAnimal`/`WrongCat` sem `virtual`
- [x] `WrongCat` só produz a saída própria dele quando chamado como `WrongCat` direto — via `WrongAnimal*` sai a saída do `WrongAnimal` (bug demonstrado e testado no `main.cpp`)
- [x] Sem vazamento de memória (`leaks --atExit`, 0 leaks, com delete explícito em tudo que foi `new`)

---

## Exercício 01: I don't want to set the world on fire

> Nova classe `Brain` (privada em `Dog`/`Cat`, não em `Animal`). Cópia de `Dog`/`Cat` precisa ser profunda — senão dois objetos acabam apontando pro mesmo `Brain` e um `delete` duplo estraga tudo.

- [ ] Ainda não iniciado.
- [ ] `Brain` criado, com saída própria de criação/remoção
- [ ] `Dog`/`Cat` ganham `Brain*` privado (não pode morar em `Animal`)
- [ ] Cópia (construtor e `operator=`) é profunda — testar criando um `Dog`, copiando pra um escopo interno, e conferindo que o `Brain` original sobrevive ao fim do escopo
- [ ] Destrutor do `Animal` precisa ser `virtual` (isso já foi resolvido no ex00, então essa parte já está pronta)
- [ ] Forma canônica ortodoxa completa, nada público sem necessidade

---

## Exercício 02: Abstract class

> `Animal` vira abstrata — `makeSound()` passa a ser `virtual void makeSound() const = 0;`. Não dá mais pra instanciar `Animal` puro.

- [ ] Ainda não iniciado.
- [ ] `makeSound()` com `= 0` (pura)
- [ ] `Animal animal;` não compila mais (erro de classe abstrata)
- [ ] `Dog`/`Cat` continuam funcionando exatamente como no ex01

---

## Exercício 03: Interface and recap

> Sistema de `AMateria`/`ICharacter`/`IMateriaSource` com `Ice`/`Cure` concretas — bem mais denso que os três exercícios anteriores juntos.

- [ ] Opcional — o subject confirma que dá pra passar o módulo sem ele. Mesmo padrão de skip do `BSP` (cpp02) e `DiamondTrap` (cpp03).
