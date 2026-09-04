# C++ — Conceitos (Módulo 01)

> Notas de estudo e referência. Tema do módulo: alocação de memória, ponteiros para membros, referências e switch. Padrão: C++98.

---

## 1. Stack vs Heap

Stack: pilha de pratos que vive dentro do escopo de uma função. Quando a função termina (o `{ }` fecha), o C++ desempilha tudo automaticamente e destrói cada coisa nessa hora, chamando o destrutor.

Heap: área de memória sem relação com escopo de função. Uma vez que você faz `new`, o objeto fica vivo até alguém mandar `delete` explicitamente, não importa se a função que criou já terminou.

```cpp
Zombie zombs(name);              // stack: destrutor roda sozinho ao sair do escopo
Zombie *z = new Zombie(name);    // heap: só morre com delete explícito
```

`new`/`delete` em C++ é equivalente a `malloc`/`free` em C, mas já chamando construtor/destrutor automaticamente.

Quando usar cada um: se o objeto só é usado dentro da própria função, stack. Se precisa sobreviver e ser usado fora dela, heap (e alguém precisa dar `delete` depois).

Retornar endereço de objeto da stack é perigoso: quando a função termina, o objeto é destruído e o ponteiro retornado vira um dangling pointer.

---

## 2. Por que newZombie/randomChump não são métodos de Zombie

São funções livres que usam a classe, não fazem parte dela. `newZombie` precisa criar um `Zombie` do zero; se fosse método, eu precisaria já ter um objeto existente pra chamar nele, o que não faz sentido.

---

## 3. Os dois const (não confundir)

```cpp
void announce(void) const;              // const no final do método
Zombie(const std::string &name);        // const antes do parâmetro
```

`const` no final do método promete que ele não modifica atributos do objeto. `const &` no parâmetro promete não alterar o argumento recebido por referência. São independentes.

---

## 4. Lista de inicialização vs atribuição no corpo

```cpp
Zombie::Zombie(const std::string &name) { this->name = name; }  // pior: constrói vazio, depois atribui
Zombie::Zombie(const std::string &name) : name(name) {}          // melhor: inicializa direto
```

Atributos são construídos antes do corpo `{ }` rodar. Atribuir no corpo é desperdício.

Detalhe: mesmo recebendo `name` por referência, `name(name)` na lista de inicialização ainda copia, porque `this->name` precisa ter vida própria, independente da string original.

---

## 5. Memory leak: por que o compilador não avisa

`new` sem `delete` correspondente é sintaticamente válido. O compilador checa regras da linguagem, não gerenciamento de memória. Isso é responsabilidade do programador e só aparece em runtime (valgrind), não em compile-time.

---

## 6. new[] / delete[]: alocação de array em bloco único

`new Tipo[N]` aloca um bloco contíguo de memória pra N objetos, numa única alocação (diferente de N chamadas separadas de `new Tipo(...)`).

```cpp
Zombie *horde = new Zombie[N];   // uma alocação, N objetos
delete[] horde;                   // desalocação correspondente, com colchetes
```

Usar `delete` sem colchetes num array alocado com `new[]` é comportamento indefinido.

## 7. new[] exige construtor sem parâmetro

`new Tipo[N]` constrói cada posição automaticamente, mas não tem como passar argumentos nessa sintaxe, só chama o construtor padrão (sem parâmetro).

Se a classe só tem construtor com parâmetro obrigatório, `new Tipo[N]` nem compila. Solução: adicionar um construtor vazio (`Zombie()`) e, depois de alocado o array, percorrer com um loop chamando um setter em cada posição pra dar o valor certo.

## 8. Lista de inicialização só existe em construtores

`: atributo(valor)` só é válido no momento em que o atributo está sendo criado pela primeira vez, ou seja, dentro de um construtor. Um setter é chamado depois que o objeto já existe, o atributo já foi construído, então só resta atribuir no corpo (`this->atributo = valor;`), não tem "lista de inicialização" fora desse contexto.

---

## 9. Ponteiro vs referência: desmistificando (tema importante)

Referência não é "mágica nova", é outra sintaxe pra trabalhar com endereços, só que mais simples de usar no dia a dia.

```cpp
std::string string = "HI THIS IS BRAIN";
std::string *stringPTR = &string;    // ponteiro: guarda o endereço de string
std::string &stringREF = string;     // referência: é um apelido pra string, mesma variável
```

### O que cada símbolo faz, e onde

| Símbolo | Contexto | Significado |
|---|---|---|
| `&var` | na frente de uma variável comum | "endereço de", pega o endereço de `var` |
| `Tipo *ptr` | na declaração | diz "isso é um ponteiro" |
| `*ptr` | usando o ponteiro depois de declarado | "desreferencia", vai até o endereço guardado e pega o valor de lá |
| `Tipo &ref` | na declaração | diz "isso é uma referência", um apelido pra outra variável |
| `ref` (sem símbolo) | usando a referência depois de declarada | se comporta como a própria variável original, sem precisar de `*` |

### Tabela de prints (a parte que costuma confundir)

Considerando `string`, `stringPTR` e `stringREF` como acima:

| Expressão | O que imprime | Por quê |
|---|---|---|
| `string` | `HI THIS IS BRAIN` | o valor guardado na variável |
| `&string` | endereço (ex: `0x16f...aa0`) | "endereço de" |
| `stringPTR` | o mesmo endereço de `&string` | o ponteiro guarda esse endereço como conteúdo dele |
| `&stringPTR` | um endereço DIFERENTE | é o endereço onde o próprio ponteiro mora na memória, não o que ele aponta |
| `*stringPTR` | `HI THIS IS BRAIN` | desreferencia, vai até o endereço guardado e pega o valor de lá |
| `stringREF` | `HI THIS IS BRAIN` | referência usada sozinha se comporta como a variável original |
| `&stringREF` | o mesmo endereço de `&string` | referência não tem endereço próprio, é a mesma variável com outro nome |

### A armadilha mais comum
`stringPTR` sozinho (sem `*`) já imprime um endereço, então é fácil achar que já pegou "o valor". Mas esse endereço é o que o ponteiro aponta, não o que ele guarda como variável em si (isso seria `&stringPTR`, outro endereço totalmente diferente). Pra pegar o valor de fato, precisa desreferenciar com `*stringPTR`.

Resumo da simetria: `stringPTR` (sem `*`) == `&string`. E `&stringREF` == `&string`. Referência nunca tem endereço próprio, ela É a variável original.

---

## 10. Referência constante como tipo de retorno

Retornar `const std::string &` (referência constante) em vez de `std::string` (valor) evita copiar o dado, entrega acesso direto ao que já existe no objeto. O `const` impede que quem chamou a função modifique o dado original através do retorno.

```cpp
const std::string &getType() const;   // dois const: um no tipo de retorno, outro no método
```

O `return` dentro da função é igual a um getter comum (`return this->type;`), a diferença toda está na assinatura, o compilador entende que não deve copiar.

## 11. Referência vs ponteiro como atributo de classe

Referência como atributo (`Tipo &nome;`) só serve quando o objeto sempre vai ter esse dado, obrigatoriamente, desde a criação. Referência precisa ser inicializada na lista de inicialização do construtor, não tem outra forma, e nunca pode ficar vazia nem trocar de alvo depois.

Ponteiro como atributo (`Tipo *nome;`) serve quando o dado é opcional, pode nascer nulo (`NULL` em C++98) e ser atribuído depois via setter, ou trocar de valor ao longo da vida do objeto.

```cpp
class HumanA { const Weapon &weapon; ... };   // sempre armado, referência
class HumanB { Weapon *weapon; ... };          // pode estar desarmado, ponteiro
```

Acessar método através de ponteiro usa `->` (ex: `weapon->getType()`), diferente de referência ou objeto direto, que usa `.` (ex: `weapon.getType()`).

## 12. Ordem de inicialização segue a declaração, não a lista

O C++ sempre inicializa os atributos na ordem em que foram declarados na classe (no `.hpp`), não na ordem escrita na lista de inicialização do construtor. Escrever a lista fora dessa ordem gera warning (`-Wreorder`), que vira erro com `-Werror`.

```cpp
class Foo
{
    std::string name;    // declarado primeiro, inicializado primeiro
    const Weapon &weapon; // declarado depois, inicializado depois
};

// a lista deve seguir essa mesma ordem, senão dá warning:
Foo::Foo(...) : name(name), weapon(weapon) {}
```

---

## Dúvidas / a aprofundar

- [ ] Ponteiros para membros de função (ex05).
- [ ] Declaração switch (ex06, opcional).
- [ ] Testar com valgrind no ambiente da 42 antes de submeter.
