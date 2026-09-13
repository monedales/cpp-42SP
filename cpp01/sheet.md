# CheatSheet — C++ Module 01

## Pré-requisitos

- [x] O código compila com `c++` e as flags `-Wall -Wextra -Werror`
- [x] O projeto segue o padrão **C++98** — funções ou contêineres C++11 (e posteriores) **não** são esperados

### 🚫 Não avaliar o exercício se…

- Uma função é implementada em um arquivo de cabeçalho *(exceto funções de template)*
- O Makefile compila sem as flags necessárias e/ou com outro compilador que não seja `c++`

### 🏴 Sinalizar com "Função Proibida" se houver…

- Uso de uma função **C** (`*alloc`, `*printf`, `free`)
- Uso de uma função não permitida nas diretrizes do exercício
- Uso de `using namespace <ns_name>` ou da palavra-chave `friend`
- Uso de biblioteca externa ou recursos de versões diferentes de C++98

---

## Exercício 00: BraiiiiiiinnnzzzZ

> Entender como alocar memória em C++.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Classe Zombie

- [x] Existe uma classe `Zombie`
- [x] Tem um atributo `name` **privado**
- [x] Tem pelo menos um construtor
- [x] Tem uma função membro `announce( void )` que imprime: `"<name>: BraiiiiiiinnnzzzZ..."`
- [x] O destrutor imprime uma mensagem de debug que inclui o nome do zumbi

### newZombie

- [x] Existe uma função `newZombie()` prototipada como: `Zombie* newZombie( std::string name );`
- [x] Aloca um `Zombie` no **heap** e retorna
- [x] Chama o construtor que recebe uma string e inicializa o `name`
- [x] O zumbi consegue se anunciar com o nome passado
- [x] Há testes provando que funciona
- [x] O zumbi é deletado corretamente antes do fim do programa

### randomChump

- [x] Existe uma função `randomChump()` prototipada como: `void randomChump( std::string name );`
- [x] Cria um `Zombie` na **stack** e o faz se anunciar
- [x] Alocado na stack (deletado implicitamente ao fim da função)
- [x] Há testes provando que funciona

> 💡 O aluno deve conseguir justificar a escolha stack vs heap — ver seção "Stack vs Heap" no `concepts.md`.

---

## Exercício 01: Moar brainz!

> Alocar vários objetos de uma vez com `new[]`, inicializar, e deletar corretamente.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### zombieHorde

- [x] A classe `Zombie` tem um construtor **padrão** (sem parâmetro)
- [x] Existe uma função `zombieHorde()` prototipada como: `Zombie* zombieHorde( int N, std::string name );`
- [x] Aloca N zumbis no **heap** explicitamente usando `new[]`
- [x] Depois da alocação, inicializa os objetos (define o `name`)
- [x] Retorna um ponteiro pro primeiro zumbi
- [x] Há testes suficientes na main provando os pontos acima (ex: `announce()` em todos)
- [x] Todos os zumbis são deletados **de uma vez** na main (`delete[]`)

---

## Exercício 02: HI THIS IS BRAIN

> Desmistificar referências.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### HI THIS IS BRAIN

- [x] Existe uma string contendo `"HI THIS IS BRAIN"`
- [x] `stringPTR` é um ponteiro para a string
- [x] `stringREF` é uma referência para a string
- [x] O endereço da string é exibido usando a variável `string`, o `stringPTR` e o `stringREF`
- [x] O conteúdo da variável é exibido usando o `stringPTR` e o `stringREF`

---

## Exercício 03: Unnecessary violence

> Entender que ponteiros e referências têm diferenças que os tornam mais ou menos adequados dependendo do ciclo de vida do objeto.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Weapon

- [x] Existe uma classe `Weapon` com uma string `type`, `getType()` e `setType()`
- [x] `getType()` retorna uma **referência constante** à string `type`

### HumanA e HumanB

- [x] `HumanA` tem uma **referência** para a `Weapon` (ela existe desde a criação até a destruição, e nunca muda)
- [x] `HumanB` tem um **ponteiro** para a `Weapon` (o campo não é definido na criação, e a arma pode ser `NULL`)

> 💡 Testado: `HumanB` sem arma imprime "has no weapon!" corretamente, sem crash.

---

## Exercício 04: Sed is for losers

> Ganhar familiaridade com `ifstream` e `ofstream`.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Exercício 04

- [x] Existe uma função `replace` (ou outro nome) que funciona conforme especificado no subject — extraída como `replaceAll(std::string &line, const std::string &s1, const std::string &s2)`, chamada dentro do loop de leitura no `main()`
- [x] Tratamento de erro eficiente: arquivo inexistente ✅ testado (`"Unable to open file."`, exit 1)
- [x] `s1`/`s2` vazios ✅ testado (`"Usage: [filename] [s1] [s2]"`, exit 1)
- [x] Chamado sem argumentos ✅ testado (mesma mensagem de uso, exit 1)
- [x] Lê usando `ifstream`, escreve usando `ofstream`
- [x] Implementado usando funções de `std::string` (`find`/`substr`), **não** char por char

> 💡 Ainda pendente: rodar `valgrind` no ambiente da 42 (não disponível no Mac) antes da submissão final.

---

## Exercício 05: Harl 2.0

> Usar ponteiros para funções membro de classe. Conhecer os níveis de log.

### Makefile

- [x] Existe um Makefile que compila usando as flags apropriadas
- [x] Existe pelo menos uma main para testar o exercício

> ⚠️ Se não for o caso, a avaliação **deste exercício termina aqui**. Pode passar para o próximo.

### Our beloved Harl

- [x] Existe uma classe `Harl` com as 4 funções membro **privadas** (`debug`, `info`, `warning`, `error`) + `complain()` pública
- [x] `complain()` executa as outras funções usando um **ponteiro para elas** (array de ponteiros pra método + array de strings paralelos)
- [x] **Sem** `if/else if/else` feio — usa `for` + `(this->*ptr[i])()`
- [x] Testado com os 4 níveis válidos + 1 nível inválido (mensagem de fallback, sem crash)

---

## Exercício 06: Harl filter (bônus) — ⏭️ NÃO ENTREGUE

> Descobrir a declaração `switch`.

- [ ] **Não implementado neste ciclo** — priorizado o obrigatório (ex00–ex05) por causa do prazo de entrega das listas 02, 03 e 04.
- Caso sobre tempo depois da entrega: usar `switch` com `default`, sem `if/else if/else`, comparando os níveis (`DEBUG < INFO < WARNING < ERROR`).
