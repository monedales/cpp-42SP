# Cheatsheet de defesa — cpp01

> Formato: **gatilho → resposta**. Detalhe completo está no `concepts.md`.

---

## Conceitos de POO deste módulo

| Gatilho | Resposta |
|---|---|
| pilar mais presente | **encapsulamento** — `private`/`public` em toda classe nova + `getType() const &` (expõe leitura, protege escrita) |
| composição (`has-a`) | `HumanA`/`HumanB` **têm uma** `Weapon` — relação "tem", não "é" |
| refinamento sobre composição | referência vs ponteiro como atributo = **modelagem de dependência** (obrigatória vs opcional), não só sintaxe |
| ciclo de vida / RAII | construtor/destrutor pareados + gerenciamento manual de `new`/`delete` |
| o que NÃO teve ainda | herança (`is-a`), polimorfismo (`virtual`), classes abstratas — vem nos próximos módulos |
| o que foi mais "linguagem" que POO | ex02 (ponteiro/referência solta), ex04 (streams), ex05 (ponteiro pra método) — recursos de C++, não princípios de design |

---

## Stack vs Heap

| Gatilho | Resposta |
|---|---|
| stack | destrói sozinha ao sair do `{ }` (escopo) — destrutor roda automático |
| heap | só morre com `delete` explícito, não liga pra escopo de função |
| quando usar heap | objeto precisa **sobreviver** fora da função que criou |
| quando usar stack | objeto só é usado **dentro** da própria função |
| retornar endereço de var da stack | dangling pointer — a var já morreu quando a função retornou |
| por que compilador não avisa leak | `new` sem `delete` é sintaticamente válido — só checa gramática, não gerenciamento de memória |

---

## new[] / delete[]

| Gatilho | Resposta |
|---|---|
| `new Tipo[N]` | 1 alocação só, bloco contíguo pra N objetos |
| desalocar | `delete[]` (colchetes!) — sem colchetes é UB |
| `new[]` exige | construtor **sem parâmetro** (não dá pra passar argumento nessa sintaxe) |
| como dar valor então | construtor vazio + loop chamando setter em cada posição |

---

## Ponteiro vs Referência (variável solta)

| Gatilho | Resposta |
|---|---|
| `Tipo *ptr = &var` | ponteiro guarda o **endereço** de `var` |
| `Tipo &ref = var` | referência é **apelido** — mesma variável, outro nome |
| `ptr` sozinho | imprime o endereço que ele **guarda** (== `&var`) |
| `&ptr` | endereço de onde o **ponteiro em si** mora (≠ `&var`!) |
| `*ptr` | desreferencia — vai no endereço e pega o **valor** |
| `ref` sozinho | comporta-se como a própria `var`, sem precisar de `*` |
| `&ref` | == `&var` sempre — referência não tem endereço próprio |

---

## Referência/ponteiro como atributo de classe

| Gatilho | Resposta |
|---|---|
| atributo referência (`Tipo &x;`) | só se o objeto **sempre** tem esse dado, obrigatório desde a criação |
| atributo ponteiro (`Tipo *x;`) | dado **opcional** — pode nascer `NULL`, trocar depois via setter |
| referência como atributo — regra rígida | **só** inicializa na lista de inicialização, nunca no corpo, nunca fica vazia |
| acessar método via ponteiro | `->` (ex: `arma->getType()`) |
| acessar método via referência/objeto | `.` (ex: `arma.getType()`) |
| `const Tipo &getX() const` | 2 `const`: 1º não deixa alterar o retornado, 2º não deixa o método alterar o objeto |
| por que referência no retorno | evita copiar — devolve acesso direto ao dado que já existe |

---

## Lista de inicialização — regras

| Gatilho | Resposta |
|---|---|
| só existe em | construtores (setter não tem, só atribui no corpo) |
| ordem de inicialização | segue ordem de **declaração no .hpp**, não a ordem escrita na lista — `-Wreorder` |
| referência/const como atributo | lista de inicialização é **obrigatória**, não opcional |

---

## ifstream / ofstream

| Gatilho | Resposta |
|---|---|
| igual a | `cin`/`cout`, só que lendo/escrevendo arquivo em vez de terminal |
| checar erro de abertura | `.is_open()` |
| ler linha a linha | `while (std::getline(file_in, linha))` |
| `.c_str()` obrigatório | construtor de `ifstream`/`ofstream` em C++98 só aceita `const char*` |
| `getline` não guarda | o `\n` — precisa `<< std::endl` na escrita pra recriar quebra de linha |
| abrir `ofstream` 2x mesmo nome | sobrescreve — abrir 1 vez só, fora de loop |

---

## find/substr (sem replace)

| Gatilho | Resposta |
|---|---|
| `find` não encontrou | retorna `std::string::npos` (não `-1`) |
| substituir 1 ocorrência | `antes = substr(0,pos)` + `s2` + `depois = substr(pos+s1.length())` |
| substituir TODAS | loop, buscando sempre no texto **atualizado**, avançando pra depois do `s2` inserido |
| por que avançar após s2 | evita loop infinito se `s2` contiver `s1` |
| substituição é | "cega" — troca dentro de palavras também, sem respeitar word boundary |

---

## Ponteiro para método de classe

| Gatilho | Resposta |
|---|---|
| declarar | `void (Classe::*ptr)(void);` |
| array de ponteiros pra método | `void (Classe::*arr[4])(void) = {&Classe::m1, &Classe::m2, ...};` |
| `&Classe::metodo` | endereço do método, mesmo `&` do ex02 |
| por que não `ptr[i]()` direto | o compilador só sabe qual método em **runtime**, precisa "resolver" primeiro |
| chamar através do ponteiro | `(this->*arr[i])()` — parênteses obrigatórios |
| `.*` vs `->*` | `.*` com objeto direto, `->*` com ponteiro pro objeto (`this` é ponteiro) |
| padrão anti-if/else | 2 arrays paralelos (strings + ponteiros) na mesma ordem + `for` comparando |
| `static` nos arrays, por quê | só eficiência — evita recriar os mesmos valores fixos a cada chamada |

---

## Onde cada coisa está no código

| Conceito | Onde |
|---|---|
| stack vs heap na prática | `ex00` — `randomChump` (stack) vs `newZombie` (heap) |
| `new[]`/`delete[]` | `ex01` — `zombieHorde` |
| ponteiro vs referência isolados | `ex02` — `main.cpp` |
| referência como atributo (obrigatório) | `ex03` — `HumanA::weapon` |
| ponteiro como atributo (opcional) | `ex03` — `HumanB::weapon`, checagem `NULL` no `attack()` |
| referência constante no retorno | `ex03` — `Weapon::getType()` |
| streams de arquivo | `ex04` — `ifstream`/`ofstream` |
| find/substr sem replace | `ex04` — função `replaceAll` |
| ponteiro pra método de classe | `ex05` — `Harl::complain()` |

---

## ⚠️ Pontos de atenção pra defesa

| Gatilho | Resposta |
|---|---|
| por que `HumanA` é referência e `HumanB` é ponteiro | `HumanA` sempre armado (referência não pode ficar vazia); `HumanB` pode estar desarmado (ponteiro aceita `NULL`) |
| ex04 lida com erro? | sim — arquivo inexistente, `s1`/`s2` vazio, sem argumentos (testado, exit 1 em todos) |
| ex06 (bônus) | não entregue — priorizei o obrigatório por prazo |
| valgrind | pendente rodar no ambiente da 42 (não dá no Mac) |
