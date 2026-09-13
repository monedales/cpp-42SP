# CheatSheet — C++ Module 02

## Pré-requisitos

- [x] O código compila com `c++` e as flags `-Wall -Wextra -Werror`
- [x] O projeto segue o padrão **C++98** — funções ou contêineres C++11 (e posteriores) **não** são esperados
- [x] Nenhuma função implementada dentro de um arquivo de cabeçalho (exceto templates)
- [x] Nenhuma função proibida usada (`*alloc`, `*printf`, `free`, `using namespace`, `friend`)
- [x] Sem bibliotecas externas ou recursos pós-C++98

### 🚫 Não avaliar o exercício se…

- Uma função é implementada em um arquivo de cabeçalho *(exceto funções de template)*
- O Makefile compila sem as flags necessárias e/ou com outro compilador que não seja `c++`

### 🏴 Sinalizar com "Função Proibida" se houver…

- Uso de uma função **C** (`*alloc`, `*printf`, `free`)
- Uso de uma função não permitida nas diretrizes do exercício
- Uso de `using namespace <ns_name>` ou da palavra-chave `friend`
- Uso de biblioteca externa ou recursos de versões diferentes de C++98

---

## Exercício 00: Minha Primeira Classe na Forma Canônica Ortodoxa

> Entender a Forma Canônica Ortodoxa (OCF) com um exercício aritmético simples: números de ponto fixo.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Compilação limpa, sem warnings

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Acessores

- [x] `int getRawBits( void ) const;` presente e funcional
- [x] `void setRawBits( int const raw );` presente e funcional

### Classe canônica

- [x] Construtor padrão presente e funcional
- [x] Destrutor presente e funcional
- [x] Construtor de cópia presente e funcional
- [x] Operador de atribuição de cópia presente e funcional
- [x] Testado: output bate exatamente com o exemplo do subject (`0`, `0`, `0`)
- [x] Sem vazamento de memória (`leaks --atExit`, 0 leaks)

---

## Exercício 01: Rumo a uma classe de número de ponto fixo mais útil

> A classe do ex00 só representava o valor `0.0`. Aqui ela ganha construtores de verdade e conversões.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas

### Construtor via float

- [x] Instancia a partir de um número de ponto flutuante, presente e funcional

### Construtor via int

- [x] Instancia a partir de um inteiro, presente e funcional

### operator<<

- [x] Presente e funcional

### toInt / toFloat

- [x] `int toInt( void ) const;` presente e funcional
- [x] `float toFloat( void ) const;` presente e funcional
- [x] Testado: output bate exatamente com o exemplo do subject
- [x] Sem vazamento de memória

---

## Exercício 02: Agora estamos falando

> Adiciona operadores de comparação e aritméticos à classe.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas

### Operadores de comparação

- [x] Os 6 operadores (`>`, `<`, `>=`, `<=`, `==`, `!=`) presentes e funcionais

### Operadores aritméticos

- [x] Os 4 operadores (`+`, `-`, `*`, `/`) presentes e funcionais
- [x] Divisão por zero: aceitável que o programa quebre, conforme o subject (não testado deliberadamente)

### Outros operadores

- [x] Os 4 operadores de incremento/decremento (pré e pós, `++`/`--`) presentes e funcionais

### Sobrecarga de funções membro estáticas públicas

- [x] `min()` (versão const e não-const) presente e funcional
- [x] `max()` (versão const e não-const) presente e funcional
- [x] Testado: output bate exatamente com o exemplo do subject, mais casos extras que o exemplo não cobre (`--`, `min`, `-`, `/`)
- [x] Sem vazamento de memória

---

## Exercício 03: BSP — ⏭️ NÃO ENTREGUE

> Implementar uma função que indica se um ponto está dentro ou fora de um triângulo, usando a classe `Fixed`.

- [ ] **Não implementado neste ciclo** — priorizado cpp03 e cpp04 por causa do prazo de entrega. O próprio subject confirma que dá pra passar o módulo sem esse exercício.
