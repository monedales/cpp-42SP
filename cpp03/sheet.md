# CheatSheet — C++ Module 03

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

## Exercício 00: Eeeee... ABRIU!

> Introduz a classe `ClapTrap` — vida, energia, dano, e as 3 ações que gastam ou sofrem esses recursos.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas

### Classe e atributos

- [x] `ClapTrap` tem os 4 atributos privados: `name`, hit points, energy points, attack damage
- [x] Atributos inicializados nos valores pedidos (`hitPoints=10`, `energyPoints=10`, `attackDamage=0`)

### Funções membro

- [x] `attack()` presente e funcional (bloqueia sem vida/energia, gasta 1 de energia)
- [x] `takeDamage()` presente e funcional (com clamp em 0, sem underflow de `unsigned int`)
- [x] `beRepaired()` presente e funcional (mesma guarda do `attack`)
- [x] Testado: 8 cenários (OCF completa, guarda de energia, guarda de vida, clamp de dano)
- [x] Sem vazamento de memória (`leaks --atExit`, 0 leaks)

---

## Exercício 01: Serena, my love!

> `ScavTrap` herda de `ClapTrap` — primeira herança de verdade do módulo.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas

### Classe e atributos

- [x] `ScavTrap` herda publicamente de `ClapTrap` (`class ScavTrap : public ClapTrap`)
- [x] Não redeclara os atributos herdados
- [x] Atributos do `ClapTrap` são `protected` (só nessa pasta em diante — `ex00` continua `private`, como a régua pede especificamente pra ele)
- [x] Atributos inicializados nos valores pedidos (`hitPoints=100`, `energyPoints=50`, `attackDamage=20`)

### Funções membro

- [x] `attack()` sobrescrito, com mensagem diferente da do `ClapTrap`
- [x] `takeDamage()`/`beRepaired()` herdados, funcionais sem redeclarar
- [x] `guardGate()` presente e funcional

### Construção e destruição

- [x] Testado: ordem de construção (ClapTrap → ScavTrap) e destruição (ScavTrap → ClapTrap) correta nos 7 cenários de teste
- [x] Mensagens de construtor/destrutor/`attack()` diferentes das do `ClapTrap`
- [x] Sem vazamento de memória (`leaks --atExit`, 0 leaks)

---

## Exercício 02: Trabalho repetitivo

> `FragTrap` herda de `ClapTrap`, mesmo esquema do `ScavTrap` com valores e habilidade diferentes.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas (só `ClapTrap.cpp` + `FragTrap.cpp` no `SRC`; `ScavTrap` presente na pasta pra entrega, mas fora da build)

### Classe e atributos

- [x] `FragTrap` herda publicamente de `ClapTrap`
- [x] Não redeclara atributos sem motivo
- [x] Atributos inicializados nos valores pedidos (`hitPoints=100`, `energyPoints=100`, `attackDamage=30`)

### Construção e destruição

- [x] Testado: ordem de construção (ClapTrap → FragTrap) e destruição (FragTrap → ClapTrap) correta nos 7 cenários de teste
- [x] Mensagens de construtor/destrutor diferentes das do `ClapTrap`

### Funções membro

- [x] `highFivesGuys()` presente e funcional
- [x] `attack()`/`takeDamage()`/`beRepaired()` herdados sem redeclarar (`FragTrap` não precisa de mensagem própria pro `attack()` — só `ScavTrap` precisa)
- [x] Sem vazamento de memória (`leaks --atExit`, 0 leaks)

---

## Exercício 03: Agora está estranho!

> `DiamondTrap` herda de `FragTrap` **e** `ScavTrap` ao mesmo tempo — precisa de herança virtual pra não duplicar `ClapTrap`.

- [ ] Ainda não iniciado — opcional, o subject confirma que dá pra passar o módulo sem ele.
