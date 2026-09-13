# Cheatsheet de defesa — cpp03

> Formato: **gatilho → resposta**. Detalhe completo está no `concepts.md`.

---

## Conceitos de POO deste módulo

| Gatilho | Resposta |
|---|---|
| pilar do módulo | **herança** (`is-a`) — primeira vez usando de verdade nesse cursus |
| `protected` | libera acesso pras classes filhas, continua bloqueando acesso externo — meio-termo entre `private` e `public` |
| override | classe filha redeclara método com mesma assinatura do pai → versão mais específica vence na chamada |
| o que NÃO teve ainda | herança múltipla, `virtual`, classes abstratas (viria no ex03, pulado) |

---

## `unsigned int` e clamp

| Gatilho | Resposta |
|---|---|
| subtração que passaria de 0 | não vira negativo — dá a volta (wraparound) pro topo do intervalo |
| diferença do `<<` negativo (cpp02) | aquilo era UB (indefinido); isso aqui é definido e previsível, só contraintuitivo |
| como evitar | checar **antes** de subtrair: `if (valor < quantidade) valor = 0; else valor -= quantidade;` |
| "clamp" | forçar um valor a não passar de um teto/piso, em vez de deixar a conta normal acontecer |

---

## Herança básica

| Gatilho | Resposta |
|---|---|
| sintaxe | `class Filha : public Pai { ... }` |
| o que a filha ganha | todos os atributos/métodos do pai automaticamente, só declara o que é novo/diferente |
| chamar construtor do pai | lista de inicialização: `Filha::Filha(...) : Pai(argumento) { ... }` |
| se não especificar | C++ chama o construtor **padrão** do pai sozinho, silenciosamente — pode ficar redundante/errado se a intenção era outra |
| quando dá pra sobrescrever atributo herdado | só no **corpo** do construtor, depois que `: Pai(...)` já rodou |

---

## Ordem de construção/destruição

| Gatilho | Resposta |
|---|---|
| construção | pai primeiro, filho depois |
| destruição | filho primeiro, pai depois (ordem inversa, tipo pilha) |
| por quê | filho pode depender de partes do pai já prontas; na destruição, filho ainda pode precisar do pai até o fim |

---

## Override seletivo

| Gatilho | Resposta |
|---|---|
| `ScavTrap` sobrescreve `attack()` | régua pede mensagem diferente pra ele especificamente |
| `FragTrap` não sobrescreve `attack()` | subject só pede msg diferente de construtor/destrutor pra ele — `attack()` vem direto do `ClapTrap` |
| regra geral | override é ferramenta usada **onde o subject pede**, não algo automático em toda subclasse |

---

## Custo de ação vs força da ação

| Gatilho | Resposta |
|---|---|
| `attackDamage` | varia por classe (0/20/30) — quanto dano o ataque causa |
| custo de energia por ação | fixo em `1`, sempre, não importa o `attackDamage` — "atacar e reparar custam 1 ponto de energia cada" |
| por que `FragTrap` (100 de energia) não é "mais eficiente" | ele não gasta menos por ataque, só aguenta mais ataques **no total** antes de zerar |

---

## Onde cada coisa está no código

| Conceito | Onde |
|---|---|
| OCF + clamp de `unsigned int` | `ex00` — `ClapTrap` |
| herança básica, `protected`, chamada explícita de construtor pai, override de `attack()` | `ex01` — `ScavTrap` |
| encadeamento construção/destruição provado nos testes | `ex01` e `ex02` |
| override seletivo (só o que muda) | `ex02` — `FragTrap` não sobrescreve `attack()` |

---

## ⚠️ Pontos de atenção pra defesa

**Construtor de cópia sem `: Pai(obj)`:** sem isso, o C++ monta a "parte pai" do objeto usando o construtor **padrão** dele (não o de cópia) — mesmo estando copiando de um objeto com valores diferentes do padrão. O resultado final ainda fica certo (`*this = obj` corrige depois), mas é trabalho à toa e deixa mensagem estranha no meio: apareceu `"Default constructor called"` no lugar de `"Copy constructor called"`, exatamente o que aconteceu com o `ScavTrap` antes da correção. A solução é sempre nomear o construtor certo do pai: `: ClapTrap(obj)`.

| Gatilho | Resposta |
|---|---|
| ex00: por que `private`, e não `protected`? | régua pede `private` especificamente pro `ex00` — só vira `protected` a partir do `ex01`, quando existe herança de verdade |
| ex03 (DiamondTrap) | não entregue — priorizado cpp04 por prazo; subject confirma que dá pra passar o módulo sem ele |
| leaks | testado com `leaks --atExit` no Mac — 0 leaks em `ex00`, `ex01`, `ex02` |
