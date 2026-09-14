# C++ — Conceitos (Módulo 04)

> Notas de estudo e referência. Tema do módulo: polimorfismo. Padrão: C++98.

---

## 1. Polimorfismo dinâmico e a palavra-chave `virtual`

```cpp
class Animal
{
protected:
	std::string	type;

public:
	...
	virtual void		makeSound() const;
};
```

Sem `virtual`, o compilador decide qual versão de um método chamar **na hora de compilar**, olhando só pro tipo declarado do ponteiro/referência. Com `virtual`, essa decisão é adiada pra **hora de executar**: o programa olha pro tipo real do objeto que tá ali e chama a versão certa. Mecanicamente, uma classe com método `virtual` ganha uma tabela interna (vtable) que aponta pra versão de cada função por tipo — é essa tabela que é consultada em tempo de execução.

---

## 2. Comparando os dois lados: `Animal` (virtual) vs `WrongAnimal` (sem virtual)

```cpp
Animal* j = new Dog();
j->makeSound();          // Dog::makeSound() -> "Woof!"

WrongAnimal* wc = new WrongCat();
wc->makeSound();         // WrongAnimal::makeSound(), NUNCA WrongCat::makeSound()
```

Mesma estrutura dos dois lados (base + derivada, ponteiro pra base guardando um objeto derivado), só muda o `virtual`. Do lado de `Animal`, o polimorfismo funciona: `j` é `Animal*`, mas como o objeto real é um `Dog`, `makeSound()` sai certo. Do lado de `WrongAnimal`, o compilador resolve `makeSound()` já na compilação, olhando só pro tipo do ponteiro (`WrongAnimal*`) — ignora completamente que o objeto real é um `WrongCat`. Esse é o exercício ex00 inteiro: mostrar o antes/depois de adicionar uma palavra.

---

## 3. Destrutor também precisa ser `virtual` — não só os métodos "normais"

```cpp
class Animal
{
public:
	virtual ~Animal();
};

class WrongAnimal
{
public:
	~WrongAnimal();   // não virtual
};
```

O mesmo problema do item 2 vale pro destrutor. Testando na prática:

```cpp
const WrongAnimal* wrongCat = new WrongCat();
...
delete wrongCat;
// saída: só "WrongAnimal destructor called"
// "WrongCat destructor called" nunca aparece
```

Deletar um objeto derivado através de um ponteiro pra base **sem destrutor virtual** é, formalmente, comportamento indefinido (UB) pelo padrão — o compilador nem olha pro tipo real, só chama o destrutor da base. Aqui não quebrou nada visível porque `WrongCat` não adiciona nenhum atributo próprio (mesmo tamanho que `WrongAnimal`), mas a regra geral é: **toda classe base pensada pra ser usada por ponteiro/referência polimorficamente precisa de destrutor virtual**, sem exceção — mesmo que hoje pareça "funcionar sem".

---

## 4. Duas hierarquias paralelas, sem nenhuma relação entre si

```cpp
class Animal { ... };
class Dog : public Animal { ... };

class WrongAnimal { ... };          // não herda de Animal
class WrongCat : public WrongAnimal { ... };
```

`WrongAnimal`/`WrongCat` não têm nenhuma relação de herança com `Animal`/`Dog`/`Cat` — são duas árvores genealógicas separadas, existindo lado a lado só pra comparação. Herança nunca é implícita ou "por semelhança de nome"; é sempre uma linha explícita (`: public X`) na declaração da classe.

---

## 5. Const-correctness: por que `makeSound()`/`getType()` precisam ser `const`

```cpp
const Animal* meta = new Animal();
meta->makeSound();   // só compila porque makeSound() é const
```

Chamar um método não-`const` através de um ponteiro/referência `const` é erro de compilação. Como o exemplo do subject guarda os objetos em `const Animal*`, todo método chamado neles (`getType()`, `makeSound()`) precisa estar marcado `const` na declaração, senão nada compila.

---

## 6. Retornar `std::string const &` em vez de `std::string`

```cpp
std::string const &Animal::getType() const
{
	return (this->type);
}
```

Retornar por referência constante evita copiar a string toda vez que alguém chama `getType()`, e o `const` garante que quem recebeu não consegue alterar o `type` original através do retorno. É estritamente melhor que retornar por valor aqui — sem trade-off real, já que `type` já existe e vive o tempo todo que o objeto vive.

---

## 7. `operator=` da classe filha delega pro `operator=` da base

```cpp
Dog &Dog::operator=(const Dog &obj)
{
	if (this != &obj)
		Animal::operator=(obj);
	std::cout << CYAN << "Dog copy assignment operator called" << RESET << std::endl;
	return (*this);
}
```

Igual o construtor de cópia pode chamar o construtor da base na lista de inicialização (visto no cpp03), o `operator=` da filha pode chamar `Animal::operator=(obj)` explicitamente pra reaproveitar a lógica de cópia do `type`, em vez de reimplementar. `Dog` não tem atributo próprio além do herdado, então essa chamada já resolve tudo que precisa ser copiado.

---

## Dúvidas / a aprofundar

- [ ] Revisitar o item 3 (delete sem destrutor virtual) com um exemplo onde a classe derivada tem atributo a mais que a base — aí sim dá pra ver o lado realmente perigoso (tamanho de bloco errado no `operator delete`), que aqui ficou "escondido" por `WrongCat` não ter atributo extra.
- [ ] ex02: `Animal` vira abstrata (não instanciável) — atualizar esse arquivo com o que muda na prática.
- [ ] ex03 (Materia/Character, interfaces puras) não vai ser feito nesse módulo por causa do prazo — se sobrar tempo depois da entrega, revisitar o conceito de interface pura (todos os métodos = 0).
