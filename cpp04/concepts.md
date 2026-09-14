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

## 8. Cópia rasa (shallow) vs cópia profunda (deep)

```cpp
Dog basic;             // basic.brain aponta pro Brain #1
Dog tmp = basic;       // cópia RASA: tmp.brain também aponta pro Brain #1 (mesmo endereço!)
```

Quando um objeto tem um ponteiro cru dentro, a cópia **gerada automaticamente pelo compilador** só copia o valor guardado no ponteiro — ou seja, o **endereço**, não o que tá lá dentro. Os dois objetos acabam apontando pro mesmo bloco de memória. Se `tmp` morre primeiro (sai de escopo, destrutor roda, `delete` no Brain #1), `basic` fica com um ponteiro "pendurado" (dangling) pra memória já liberada. Usar isso depois é UB; se `basic` também morrer e tentar deletar o mesmo Brain de novo, é **double free**.

```cpp
Dog::Dog(const Dog &obj): Animal(obj)
{
	this->brain = new Brain(*obj.brain);   // cópia PROFUNDA: bloco novo, conteúdo copiado
}
```

Cópia profunda aloca um bloco **novo** e copia o conteúdo pra lá — os dois objetos ficam com ponteiros diferentes, cada um dono do seu próprio Brain. É isso que o construtor de cópia e o `operator=` do `Dog`/`Cat` fazem manualmente (o exercício existe justamente pra forçar escrever isso à mão, em vez de confiar na cópia automática do compilador).

---

## 9. Por que o `Brain` não precisa de ponteiro interno, mas o `Dog`/`Cat` precisam apontar pra ele

```cpp
class Brain
{
private:
	std::string	ideas[100];   // array de objetos, não de ponteiros
};
```

`Brain` só guarda `std::string`, que já sabe se copiar direito sozinha (sem vazar, sem endereço compartilhado) — então a cópia campo-a-campo do `Brain` é segura por natureza, sem precisar de nenhum cuidado especial. O perigo mora exatamente onde existe um **ponteiro cru gerenciado manualmente** (`new`/`delete`) — é aí que a cópia padrão do compilador (que só copia o endereço) quebra. O subject bota o `Brain*` no `Dog`/`Cat` de propósito, pra criar esse cenário.

---

## 10. Destrutor virtual reafirmado: array misto de `Animal*`

```cpp
Animal* animals[4];
animals[0] = new Dog();
animals[1] = new Dog();
animals[2] = new Cat();
animals[3] = new Cat();
...
for (int i = 0; i < 4; i++)
	delete animals[i];   // cada delete dispara Brain -> Dog/Cat -> Animal, na ordem certa
```

Esse teste é o item 3 na prática, só que agora com objetos que **têm** algo a perder (o `Brain` alocado): se o destrutor de `Animal` não fosse `virtual`, `delete animals[i]` chamaria só `~Animal()`, o `Brain` de cada `Dog`/`Cat` nunca seria deletado, e `leaks` acusaria memória perdida — diferente do `WrongCat` do ex00, aqui o vazamento seria real e visível, não só teórico.

---

## Dúvidas / a aprofundar

- [ ] Revisitar o item 3 (delete sem destrutor virtual) com um exemplo onde a classe derivada tem atributo a mais que a base — aí sim dá pra ver o lado realmente perigoso (tamanho de bloco errado no `operator delete`), que aqui ficou "escondido" por `WrongCat` não ter atributo extra.
- [ ] ex02: `Animal` vira abstrata (não instanciável) — atualizar esse arquivo com o que muda na prática.
- [ ] ex03 (Materia/Character, interfaces puras) não vai ser feito nesse módulo por causa do prazo — se sobrar tempo depois da entrega, revisitar o conceito de interface pura (todos os métodos = 0).
