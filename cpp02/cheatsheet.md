# Cheatsheet de defesa — cpp02

> Formato: **gatilho → resposta**. Detalhe completo está no `concepts.md`.

---

## Conceitos de POO deste módulo

| Gatilho | Resposta |
|---|---|
| pilar mais presente | **polimorfismo ad-hoc** (sobrecarga) — mesmo nome de operador, comportamento diferente por assinatura/tipo |
| regra de design nova | **OCF** obrigatória do módulo 02 em diante (padrão, cópia, `operator=`, destrutor) |
| `static` | pertence à **classe**, não a um objeto — sem `this` |
| por que 2 versões (const/não-const) de `min`/`max` | preservar a constância do retorno de acordo com a entrada |
| o que NÃO teve ainda | herança, `virtual`, classes abstratas — vem nos próximos módulos |

---

## Forma Canônica Ortodoxa (OCF)

| Gatilho | Resposta |
|---|---|
| as 4 funções obrigatórias | padrão, cópia, `operator=`, destrutor |
| construtor de cópia vs `operator=` | pergunta: **o objeto da esquerda já existe?** não → cópia; sim → `operator=` |
| construtor de cópia delegando (`*this = src`) | válido, DRY — mas cuidado com memória dinâmica no futuro (libera "lixo" não inicializado) |
| `operator=` — assinatura | `Fixed &operator=(const Fixed &src)` — retorna referência, não cópia |
| `operator=` — autoatribuição | `if (this != &src)` — hábito essencial quando há memória dinâmica |
| `operator=` — por que retorna `*this` | permite encadear `a = b = c;` |

---

## `static const int` como membro

| Gatilho | Resposta |
|---|---|
| declarar (`.hpp`) | `static const int fractBits;` |
| definir (`.cpp`) | `const int Fixed::fractBits = 8;` |
| por que definir fora, não só inicializar no `.hpp` | evita erro de linkagem se algum dia usar por referência/endereço |
| `static` no `.cpp` | **nunca** se repete — só existe na declaração |

---

## Conversões int/float ↔ fixed

| Gatilho | Resposta |
|---|---|
| int → fixed | `value = i_num * (1 << fractBits)` (multiplicação, não `<<` direto — negativo é UB) |
| fixed → int (`toInt`) | `value >> fractBits` — trunca, não arredonda |
| float → fixed | `roundf(f_num * (1 << fractBits))` + `static_cast<int>` |
| fixed → float (`toFloat`) | `static_cast<float>(value) / (1 << fractBits)` |
| por que não usar `<<`/`>>` no float | são operadores de **bits**, só existem pra inteiros |

---

## `operator<<`

| Gatilho | Resposta |
|---|---|
| por que não é método da classe | `Fixed` não pode estar à esquerda do `<<` — quem fica é `std::cout` |
| assinatura | `std::ostream &operator<<(std::ostream &o, const Fixed &f)` — função livre, fora da classe |
| onde declarar | no `.hpp`, depois do `};` que fecha a classe |
| por que retorna `std::ostream&` | permite encadear `std::cout << a << std::endl;` |

---

## Comparadores e aritméticos

| Gatilho | Resposta |
|---|---|
| comparar 2 `Fixed` | compara `value` bruto direto — mesma escala nos dois lados, não precisa converter |
| somar/subtrair/multiplicar/dividir | `toFloat()` dos dois, opera em float, reconstrói com `Fixed(resultado)` |
| retorno dos aritméticos | `Fixed` (objeto novo) — retorno dos comparadores é `bool` |

---

## `++`/`--` e o epsilon

ϵ é o **degrau mínimo** que esse sistema consegue representar — a menor distância possível entre um valor e o próximo, dado que só existem 8 bits pra fração. Como o valor real é sempre `bruto / 256`, o menor incremento possível no `int` bruto (`+1`) já É o menor incremento possível no valor real: `1/256 = 0.00390625`. Não tem conta pra fazer — é justamente esse número que aparece quando `++a` roda a partir de `a = 0` (testado e confirmado).

| Gatilho | Resposta |
|---|---|
| "menor ϵ representável" | `value += 1` no bruto — não precisa calcular nada |
| por quê | cada unidade do `value` cru já vale `1/2^fractBits` no mundo real |
| exemplo pra defesa | `a = 0`, `++a` → `0.00390625` = `1/256` — é o ϵ na prática |
| pré (`++a`) | `Fixed &operator++(void)` — modifica e retorna o próprio objeto |
| pós (`a++`) | `Fixed operator++(int)` — `int` fantasma só pra diferenciar assinatura; guarda cópia antes de mudar, retorna a cópia (por valor, nunca referência — a cópia é local) |

---

## `min`/`max` estáticos

| Gatilho | Resposta |
|---|---|
| assinatura não-const | `static Fixed &min(Fixed &a, Fixed &b);` |
| assinatura const | `static const Fixed &min(const Fixed &a, const Fixed &b);` |
| retorno | referência a `a` ou `b` (o objeto que já existe), nunca cópia nova |
| por que só a versão const não basta | perderia a mutabilidade do resultado quando os argumentos originais não são `const` |

---

## Onde cada coisa está no código

| Conceito | Onde |
|---|---|
| OCF completa | `ex00` |
| `static const int` declarado/definido | `ex00` — `fractBits` |
| construtores int/float, `toInt`/`toFloat`, `operator<<` | `ex01` |
| 6 comparadores, 4 aritméticos | `ex02` |
| `++`/`--` pré e pós, epsilon | `ex02` |
| `min`/`max` estáticos (const/não-const) | `ex02` |

---

## ⚠️ Pontos de atenção pra defesa

| Gatilho | Resposta |
|---|---|
| por que `i_num * (1 << fractBits)` e não `i_num << fractBits` | deslocar `int` **negativo** com `<<` é UB em C++98 |
| divisão por zero nos aritméticos | aceitável o programa quebrar — o subject autoriza |
| ex03 (BSP) | não entregue — priorizei cpp03/cpp04 por prazo; subject confirma que dá pra passar sem ele |
| leaks | testado com `leaks --atExit` no Mac (sem valgrind) — 0 leaks nos 3 exercícios |
