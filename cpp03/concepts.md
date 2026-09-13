# C++ — Conceitos (Módulo 03)

> Notas de estudo e referência. Tema do módulo: herança. Padrão: C++98.

---

## 1. `unsigned int` e aritmética modular (wraparound)

```cpp
if (this->hitPoints < amount)
    this->hitPoints = 0;   // clamp — evita o wraparound
else
    this->hitPoints -= amount;
```

`unsigned int` não representa números negativos. Quando uma subtração "passaria" de zero, o resultado não vira negativo — ele **dá a volta** pro outro extremo do intervalo (com 32 bits, próximo de 4.294.967.295). Isso é diferente do `<<` com `int` negativo que vimos no cpp02: aquilo era comportamento **indefinido** (UB); isto aqui é comportamento **definido e previsível**, só que contraintuitivo — por isso é fácil não perceber o bug até testar com um valor de dano maior que a vida restante. A defesa é checar antes de subtrair, nunca depois.

---

## 2. Ordem do print importa quando a mensagem depende do estado pós-cópia

```cpp
ClapTrap::ClapTrap(const ClapTrap &obj)
{
    *this = obj;                                            // copia primeiro
    std::cout << "Copy constructor for " << this->name;     // só então imprime
}
```

Se o print viesse **antes** de `*this = obj;`, `this->name` ainda estaria vazio (o objeto sendo construído não tem esse dado ainda) — a mensagem sairia sem nome. Fazendo a cópia primeiro, o atributo já está preenchido na hora de montar a mensagem. Detalhe pequeno, mas é o tipo de coisa que só aparece testando de verdade (rodando o programa), não só lendo o código.

---

## 3. Herança básica: `class Filha : public Pai`

```cpp
class ScavTrap : public ClapTrap
{
    ...
};
```

Essa sintaxe diz: "todo `ScavTrap` **é um** `ClapTrap`, com coisas a mais". `ScavTrap` ganha automaticamente todos os atributos e métodos de `ClapTrap` (com as regras de acesso que vêm a seguir), sem precisar reescrever nada — só declara o que é **novo** ou **diferente**.

---

## 4. Construtor da classe filha precisa chamar o construtor certo do pai

```cpp
ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name)
{
    this->hitPoints = 100;   // sobrescreve depois que o ClapTrap já construiu
    ...
}
```

Antes do corpo do construtor da filha rodar, a "parte pai" do objeto precisa existir. Você escolhe qual construtor do pai usar chamando ele na lista de inicialização, igual se fosse um atributo. Só depois disso o corpo do construtor da filha roda — por isso dá pra sobrescrever atributos herdados no corpo (eles já existem nesse ponto).

---

## 5. Se você não especifica, o C++ chama o construtor padrão do pai

```cpp
ScavTrap::ScavTrap(const ScavTrap &obj)   // sem ": ClapTrap(obj)"
{
    ...
}
```

Sem `: ClapTrap(algumaCoisa)` explícito, o compilador chama `ClapTrap()` (o construtor **padrão**) sozinho, silenciosamente, antes do corpo. Isso compila e roda sem erro — mas se a intenção era copiar de outro objeto, o resultado fica errado ou, na melhor das hipóteses, redundante (a classe base é inicializada com valores padrão e depois sobrescrita à toa). Pergunta pra sempre fazer: "qual construtor do pai eu realmente preciso aqui?" — e escrever isso explicitamente.

---

## 6. `protected` vs `private`: por que os atributos do ClapTrap mudaram

```cpp
class ClapTrap
{
    protected:              // era private
        std::string name;
        unsigned int hitPoints;
        ...
};
```

`private` bloqueia acesso pra **qualquer um** fora da própria classe, inclusive classes filhas. `protected` libera acesso pras classes filhas (via herança), mas continua bloqueando pra código externo qualquer. `ScavTrap` precisava sobrescrever `hitPoints`/`energyPoints`/`attackDamage` com valores próprios (100/50/20) direto no construtor — só é possível se esses atributos forem, no mínimo, `protected`.

---

## 7. Override: mesma assinatura, versão mais específica vence

```cpp
class ClapTrap { void attack(const std::string &target); };
class ScavTrap : public ClapTrap { void attack(const std::string &target); };  // override
```

Quando a classe filha declara um método com a **mesma assinatura** de um método já existente no pai, ela está sobrescrevendo (override). Chamando `algumScavTrap.attack(...)`, o C++ usa a versão de `ScavTrap`, não a herdada de `ClapTrap` — a mais específica sempre vence. Métodos que a filha não sobrescreve (`takeDamage`, `beRepaired`) continuam vindo direto do pai, sem precisar redeclarar nada.

---

## 8. Ordem de construção/destruição em cadeia

Construção: pai primeiro, filho depois. Destruição: filho primeiro, pai depois (ordem inversa — igual pilha, o que "abriu" por último "fecha" primeiro).

```
Default constructor called          <- ClapTrap (pai)
Default ScavTrap constructor called <- ScavTrap (filho)
...
Destructor for ScavTrap called      <- ScavTrap (filho) — sai primeiro
Destructor for  called              <- ClapTrap (pai) — sai por último
```

Faz sentido: o filho pode depender de partes do pai já existirem pra funcionar, então o pai tem que estar pronto primeiro. Na destruição, o filho ainda pode precisar acessar coisas do pai até o último instante, então ele é desmontado primeiro, deixando o pai por último.

---

## 9. Custo de ação (energia) é fixo — não confundir com a força da ação (dano)

```cpp
this->energyPoints--;   // sempre -1, não importa o attackDamage
```

`attackDamage` varia por classe (0 no `ClapTrap`, 20 no `ScavTrap`, 30 no `FragTrap`) — é **quanto dano** o ataque causa no alvo. O custo de energia pra realizar a ação é outra coisa, fixa em `1` pra todas as classes ("atacar e reparar custam 1 ponto de energia cada", direto do subject). São dois números independentes: um mede a força do golpe, o outro mede o "combustível" gasto pra desferir ele. Um `FragTrap` com 100 de energia não gasta menos por ataque — ele só aguenta **mais ataques no total** antes de zerar.

---

## 10. Nem toda subclasse sobrescreve os mesmos métodos

`ScavTrap` sobrescreve `attack()` (a régua pede mensagem diferente). `FragTrap` **não** sobrescreve `attack()` — o subject só pede mensagens diferentes de construtor/destrutor pra ele, então `attack()` continua vindo direto do `ClapTrap`, sem redeclarar nada. Override é uma ferramenta que você usa **onde precisa**, não algo que se aplica igual em todas as subclasses só porque uma delas usou.

---

## Dúvidas / a aprofundar

- [ ] Revisitar a decisão do construtor de cópia delegar pro `operator=` quando aparecer a primeira classe com memória alocada dinamicamente (mesma nota do cpp02).
- [ ] Herança múltipla e o "diamond problem" — só vai aparecer de fato se formos fazer o ex03 (`DiamondTrap`).
