# C++ — Conceitos (Módulo 00)

> Notas de estudo e referência. Padrão do módulo: **C++98**.

---

## 1. Estrutura de arquivos

| Arquivo | O que contém |
|---------|--------------|
| `.hpp` (header) | **Declarações**: atributos e assinaturas de classes e métodos. A "interface" pública. |
| `.cpp` (source) | **Implementação** do que foi declarado no `.hpp`. O "como por dentro". |

Regra de ouro dos includes: **"include what you use"** — cada arquivo inclui diretamente o que ele mesmo usa, sem "pegar carona" nas dependências de outro arquivo.

- O `.hpp` só precisa dos includes necessários pra sua *interface* fazer sentido.
- Detalhes internos de implementação (ex: `<sstream>`, `<iomanip>`) moram no `.cpp`, não no `.hpp`.

---

## 2. Classes

- **member functions** → funções declaradas dentro de uma classe.
- **member attributes** → variáveis declaradas dentro de uma classe.
- `private` → só acessível de dentro da própria classe.
- `public` → acessível de fora.

Regra prática (do subject): o que **sempre** será usado só dentro da classe é `private`; o que pode ser usado de fora é `public`.

```cpp
class Contact
{
    private:
        std::string firstName;   // member attribute (privado)
    public:
        std::string getFirstName() const;  // member function (pública)
};
```

> Isso vale também pra **métodos auxiliares**, não só atributos. No projeto, `formatRow` começou público e foi movido pra `private` — ele só é chamado de dentro do `listContacts`, nada externo usa. É um ponto que a régua de avaliação cobra explicitamente.

---

## 3. Construtores e destrutores

- **Construtor**: código executado quando a classe é **instanciada**. Bom lugar pra inicializar os atributos.
- **Destrutor** (`~`): código executado quando o objeto é **destruído** (sai de escopo, etc.).

```cpp
Example::Example() { this->foo = 42; }  // inicialização no corpo
Example::~Example() { }
```

### Lista de inicialização
Forma idiomática de inicializar atributos **antes** do corpo do construtor rodar:

```cpp
// hpp
class Example {
    public:
        char  a1;
        int   a2;
        float a3;
        Example(char p1, int p2, float p3);
        ~Example();
};

// cpp — lista de inicialização vem depois dos ':'
Example::Example(char p1, int p2, float p3) : a1(p1), a2(p2), a3(p3) { }
```

> Detalhe visto no projeto: atributos de uma classe são construídos **antes** do corpo `{ }` do construtor executar (por isso, ao criar um `PhoneBook`, os 8 `Contact` do array são construídos primeiro).

---

## 4. `this->`

- `this` é um **ponteiro** para o próprio objeto — equivalente conceitual do `self` do Python. ✅
- Usado pra acessar atributos/métodos da própria instância.

```cpp
void Contact::SetField(e_field field, std::string value) {
    this->firstName = value;
}
```

---

## 5. `const` em métodos

`const` **no final** da assinatura de um método promete que ele **não altera** nenhum atributo do objeto — e o compilador força isso (dá erro se você tentar alterar).

```cpp
std::string getFirstName() const;  // só lê, nunca modifica
```

- Getters → `const` (só leem).
- Setters → **não** `const` (precisam modificar).
- Bônus: só métodos `const` podem ser chamados num objeto `const`.

---

## 6. `static` (em classes)

`static` em C++ tem significado **diferente** do C:
- **Em classe**: o membro pertence à **classe inteira**, compartilhado por todos os objetos (não há uma cópia por instância).
- Um valor `static`/constante pode ser acessado via `NomeDaClasse::MEMBRO`, sem precisar de um objeto.

> No projeto: `Contact::FIRST_NAME` (valor do enum) é acessado pelo nome da classe, não por um objeto específico — porque é o mesmo pra todos.

*(Obs: `static` de função no C — "só visível dentro do arquivo" — é um conceito à parte, mesma palavra, sentido diferente.)*

### `static const` como constante de compilação

Um `const` comum é **por objeto** e só ganha valor quando o objeto é construído. Por isso ele **não serve** como tamanho de array — o tamanho precisa ser conhecido em tempo de compilação, muito antes de qualquer construtor rodar:

```cpp
const int MAX_CONTACTS;            // valor só existe em runtime
Contact contacts[MAX_CONTACTS];    // ✗ não compila
```

Já `static const` com inicializador inline é **da classe** e conhecido em compilação — o construtor não entra na história:

```cpp
class PhoneBook {
    private:
        static const int MAX_CONTACTS = 8;
        Contact contacts[MAX_CONTACTS];   // ✓
};
```

Dois detalhes que pegam:

- **A ordem de declaração importa.** A constante precisa vir **antes** do array. Corpos de método enxergam a classe inteira (por isso podem usar atributos declarados mais abaixo), mas declarações de membro — como o tamanho de um array — resolvem os nomes na ordem em que aparecem.
- Em C++98, se a constante for usada de um jeito que exija um endereço de memória (passar pra algo que recebe `const int &`, por exemplo), o linker pede uma definição fora da classe, no `.cpp`: `const int PhoneBook::MAX_CONTACTS;` — sem repetir o `= 8`.

---

## 7. Namespaces e `::`

- **Namespace**: agrupamento de símbolos e funções. Funciona como um **sobrenome** que evita conflito de nomes (tipo distinguir "Ana Silva" de "Ana Souza").

```cpp
namespace Name {
    int bla = 3;
    int foo(void) { return 4; }
}
```

- **`::`** → *scope resolution operator* ("operador de resolução de escopo"). Diz a que escopo algo pertence — "vá procurar dentro de X".
- `::` também é usado pra implementar métodos no `.cpp`: `Contact::getFirstName()` = "o método `getFirstName` **da classe** `Contact`".

### O namespace `std::`

- `std` é o namespace da **biblioteca padrão** (o nome vem de "**st**an**d**ard").
- **Não é um objeto** — é só um nome de escopo (um "rótulo de agrupamento"). Não guarda dados, não tem métodos, não é instanciável.
- Escrever `std::` antes de tudo é dizer "essa coisa **pertence à** biblioteca padrão", não uma versão qualquer que outra biblioteca poderia ter com o mesmo nome:
  - `std::cout` → o objeto `cout` que vive dentro de `std` (aqui `cout` **é** objeto, mas `std` não).
  - `std::string` → o tipo `string` que vive dentro de `std`.
  - `std::getline(...)` → a função `getline` que vive dentro de `std`.
- Sem o `std::`, o compilador não sabe onde procurar por `string`/`cout`/etc.
- Existe o atalho `using namespace std;` que dispensaria repetir `std::` — mas o **subject proíbe** no módulo, justamente pra você praticar sabendo de onde cada coisa vem.

---

## 8. Streams / I/O

- `std::cin` → standard input (entrada padrão).
- `std::cout` → standard output (saída padrão).
- `<<` → operador de **inserção** ("joga pra dentro de" um stream de saída).
- `>>` → operador de **extração** ("tira de" um stream de entrada).
- `std::endl` → quebra de linha (e dá flush no buffer).

```cpp
std::cout << "Nome: " << firstName << std::endl;
std::cin >> comando;
```

### `getline`
Lê a linha inteira **até** a quebra de linha (e descarta o `\n`, não guarda na string). Diferente de `cin >>`, aceita **espaços** no meio.

```cpp
std::getline(std::cin, value);  // lê "nome composto com espaços" inteiro
```

> Pegadinha do buffer: misturar `cin >>` com `getline` deixa um `\n` sobrando no buffer. Soluções: `cin.ignore(...)` pra limpar, **ou** usar `getline` pra tudo (o que evita o problema).

Streams também carregam **estado de erro**, que é assunto da próxima seção.

---

## 9. Estados de um stream (`fail`, `eof`, `clear`, `ignore`)

### Por que a doc do `cin` parece incompleta

Procurar `ignore()` ou `clear()` na página do `std::cin` não acha nada — e o motivo é herança. `cin` é um **objeto**, uma instância de `istream`, e os métodos moram nas classes-base:

```
ios_base  →  ios  →  istream  →  cin (é uma instância de istream)
              │        │
              │        └── ignore(), getline(), operator>>
              └── clear(), fail(), eof(), good()
```

A página do `cin` lista só o que é específico dele. Pra achar o resto, **suba na árvore de herança**: `ignore` está documentado em `istream`, e `clear`/`fail`/`eof` em `ios`.

### As flags

Um stream carrega flags que descrevem seu estado. As duas que importam aqui:

- **`failbit`** — a última operação falhou. Checa com `cin.fail()`.
- **`eofbit`** — a entrada acabou (Ctrl+D, fim de arquivo). Checa com `cin.eof()`.

Um `getline` que bate no fim da entrada liga **as duas**.

### `clear()` + `ignore()`

- `clear()` → apaga as flags de erro, deixando o stream utilizável de novo.
- `ignore(n, delim)` → descarta até `n` caracteres, **ou** até encontrar `delim`, o que vier primeiro.

```cpp
std::cin.clear();
std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
```

Decodificando aquele segundo argumento:

- `streamsize` é o tipo que a biblioteca de streams usa pra representar "quantidade de caracteres".
- `std::numeric_limits<std::streamsize>::max()` é o maior valor que esse tipo comporta — na prática, "descarte quantos caracteres for preciso, até achar o `\n`".
- Por que não um número fixo, tipo `ignore(100, '\n')`? Porque você não sabe quanto lixo o usuário digitou. Se sobrar coisa no buffer, o próximo `>>` lê a sobra em vez de esperar entrada nova.
- Precisa de `#include <limits>`.

### O erro conceitual: EOF não é input inválido

Esse combo serve pra **erro de formato recuperável**: o usuário digitou letra onde se esperava número, o dado ruim ainda está no buffer, você descarta e pede de novo.

**EOF é outra natureza de evento.** Não é "veio errado", é "não vem mais nada". O `clear()` apaga o `eofbit`, mas não faz aparecer dado que não existe. Se você tratar EOF como erro recuperável e voltar pro loop, o próximo `getline` bate em EOF de novo, instantaneamente — e vira **loop infinito** cuspindo o prompt na tela.

> No projeto: era exatamente o bug do Ctrl+D. A correção foi checar `eof()` **antes** de `fail()` e, nesse caso, não limpar nada — apenas sinalizar que é hora de sair (veja §14).

### Detalhe do `getline`

Com `std::getline` não existe "formato errado" — ele aceita qualquer sequência de caracteres. Então, na prática, um `getline` que falha **falhou por EOF**. É por isso que, num programa que lê só com `getline`, `fail()` e `eof()` acabam apontando pra mesma situação.

---

## 10. String streams (`<sstream>`)

Funcionam como um `cout`/`cin`, mas lendo/escrevendo numa **string** em memória (não na tela). Jeito idiomático de converter tipos em C++.

- `std::ostringstream` → escreve nele com `<<`, depois extrai com `.str()`. Serve pra **número → string**.
- `std::istringstream` → carrega uma string, extrai com `>>`. Serve pra **string → número**.

```cpp
// número -> string
std::ostringstream oss;
oss << index;
std::string str_index = oss.str();   // "42"

// string -> número (com validação!)
std::istringstream iss(text);
int result;
if (iss >> result && iss.eof())      // extraiu um int E chegou ao fim (sem lixo tipo "5abc")
    // válido
```

- `.str()` → devolve o conteúdo do stream como `std::string`.
- `iss.eof()` → informa se o stream **chegou ao fim**. Combinado com `iss >> result`, garante que a string era *só* um número, sem sobras.

> `EOF` (maiúsculo) é a **constante** "end of file"; `.eof()` é o **método** que checa se chegou lá.

> ⚠️ Não confundir: `iss.eof()` fala do fim de **uma string em memória** — é um truque de validação, nada a ver com teclado. `cin.eof()` fala do fim da **entrada real** (Ctrl+D). Mesmo nome de método, objetos e significados diferentes. Veja §9.

---

## 11. `<iomanip>` — manipuladores de formato

Controlam como o stream formata a saída.

- `std::setw(n)` → largura mínima de `n` caracteres (só **preenche** com espaço se for menor; **não trunca** se for maior).
- `std::right` → alinha à direita dentro dessa largura.

```cpp
result << std::right << std::setw(10) << value;  // "       Ana" (10 chars)
```

> Como `setw` não trunca sozinho, no projeto usei `substr(0, 9) + "."` pra cortar textos longos manualmente.

> ⚠️ Tanto o `setw` quanto o `substr` trabalham em **bytes**, não em caracteres. Com texto ASCII dá na mesma; com acento ou emoji, o alinhamento quebra. Veja §12.

---

## 12. UTF-8 e a ilusão do `length()`

`std::string::length()` conta **bytes**, não caracteres. Em ASCII puro os dois números coincidem — mas acento e emoji ocupam mais de um byte, e aí a conta desanda:

| Texto | Caracteres | Bytes |
|---|---|---|
| `JOSE` | 4 | 4 |
| `JOSÉ` | 4 | **5** — o `É` ocupa 2 |
| `MONA💅` | 5 | **8** — o emoji ocupa 4 |

Como `setw(10)` também conta bytes, duas strings visualmente do mesmo tamanho terminam em colunas diferentes:

```
      JOSE|     ← 10 bytes, 10 colunas na tela
     JOSÉ|      ← 10 bytes, 9 colunas na tela  ← desalinhado
```

E o `substr(0, 9)` pode cortar **no meio** de um caractere multi-byte, deixando um byte órfão que o terminal exibe como `�`.


> `length()` e `substr` do `std::string` trabalham em bytes, não em caracteres, então acento e emoji desalinham a coluna. Pra corrigir, eu teria que contar code points UTF-8 em vez de bytes. E mesmo assim emoji continuaria torto, porque ocupa **duas colunas** no terminal —> isso exigiria `wcwidth()`, que é POSIX, não C++98.

Dois argumentos a favor de deixar como está:

- A régua de avaliação diz, na seção do SEARCH: *"A formatação da saída pode ser diferente, não importa."*
- A mesma seção diz que o foco é **usar os iomanips do C++** — e uma correção manual de UTF-8 justamente elimina o `setw`, andando na direção contrária do que se pede.

---

## 13. Getters e setters

- **Getter**: lê um atributo privado de fora da classe (`const`).
- **Setter**: escreve num atributo privado de fora da classe.

Padrão pra preencher um objeto aos poucos: construtor vazio + setters chamados um a um (útil quando os dados chegam em momentos diferentes, ex: input campo a campo).

---

## 14. Sinalizando "sair" sem poluir o valor de retorno

Problema real que apareceu no `validateField`: a função precisa comunicar **duas** coisas — o texto que o usuário digitou **e** "o usuário apertou Ctrl+D e quer sair" — mas só tem um tipo de retorno (`std::string`).

### Duas tentativas que não funcionam

**String sentinela.** Reservar um valor especial (uma mensagem, um `"__QUIT__"`) pra significar "sair". O problema é que qualquer string reservada é, em tese, um dado que o usuário poderia digitar — o canal de dados e o canal de controle ficam misturados no mesmo lugar.

**`return NULL`.** `std::string` **não é ponteiro** — não existe "string nula". O `NULL` acaba convertido pra `const char *`, chamando o construtor `std::string(const char *)` com um ponteiro nulo, o que é **comportamento indefinido**: pode segfaultar, pode lançar exceção, pode parecer funcionar hoje e quebrar amanhã. Não dá pra construir lógica em cima disso.

### A solução: separar os canais

Parâmetro de saída por referência — o retorno carrega o **dado**, o parâmetro carrega o **controle**:

```cpp
static std::string validateField(std::string prompt, bool &quit);
```

E quem chama precisa checar o sinal **antes** de usar o valor:

```cpp
std::string value = validateField(BOLD + PEACH + questions[i] + RESET + LILAC, quit);
if (quit)
    return ;                       // nem toca no `value`, não salva contato pela metade
contact.SetField(fields[i], value);
```

A alternativa mais elegante seria uma **exceção** (`throw` no `validateField`, `catch` lá em cima), que dispensa carregar o flag por toda a cadeia de chamadas — mas exceções só entram formalmente a partir do módulo 08.

> Ideia geral pra levar adiante: quando uma função precisa comunicar duas informações de naturezas diferentes, mande cada uma por um canal diferente. Espremer as duas no mesmo lugar sempre acaba gerando um valor "mágico" que uma hora colide com dado de verdade.

### Bônus: código duplicado diverge

O primeiro `validateField` tinha **duas** leituras — uma antes do `while` e outra dentro dele. Toda vez que eu consertava uma, esquecia de espelhar na outra, e o prompt aparecia duplicado no Ctrl+D. A solução foi reestruturar pra um **loop único** com saídas explícitas, onde o prompt aparece uma vez só no código e não há como as cópias divergirem.

---

## 15. Conexão com o projeto (cpp00 / PhoneBook)

Onde cada conceito apareceu na prática:

| Conceito | Onde usei |
|----------|-----------|
| `.hpp`/`.cpp` + `::` | Toda implementação de método (`Contact::`, `PhoneBook::`) |
| `private` + getters/setters | `Contact`: atributos privados, `SetField` + 5 getters |
| Método auxiliar privado | `formatRow` — só usado internamente pelo `listContacts` |
| `enum` dentro da classe | `Contact::e_field` pra identificar qual campo o `SetField` preenche |
| `switch/case` | `Contact::SetField` — escolher qual atributo receber o valor |
| `const` | Todos os getters de `Contact` |
| `static const` de classe | `PhoneBook::MAX_CONTACTS` — tamanho do array e limite da rotação |
| `getline` pra tudo | Leitura de comando e dos 5 campos (evita bug do buffer) |
| Validação "não vazio" | `validateField()` — repete o prompt enquanto a string for vazia |
| `eof()` vs `fail()` | `handleInputFailure()` — distinguir Ctrl+D de erro recuperável |
| `bool &` como sinal de controle | `validateField(prompt, quit)` — avisar que o usuário quer sair |
| Arrays paralelos | `addContact` — `questions[]` + `fields[]` no lugar de um `switch` de 5 casos |
| `ostringstream` | `formatRow` — converter índice `int` → `std::string` |
| `istringstream` + `.eof()` | `parseIndex` — validar que o índice é um número puro |
| `setw`/`right` + `substr` | `formatColumn` — colunas de 10 chars alinhadas/truncadas |
| Operador `%` | `contacts[count % MAX_CONTACTS]` — rotação circular (substituir o mais antigo) |
| Referência (`&`) | `parseIndex(std::string, int &result)` — "devolver" 2 coisas |
| "Include what you use" | Ajuste final de dependências em todos os arquivos |

---

## Dúvidas / a aprofundar

- [ ] Templates e function overloading (vistos de raspão, formalizados em módulos futuros).
- [ ] Forma Canônica Ortodoxa (a partir do módulo 02).
- [ ] Exceções como mecanismo de controle de fluxo (módulo 08+) — a alternativa ao `bool &quit` da §14.
- [ ] Largura de exibição de caracteres (`wcwidth`) — o que faltaria pra alinhar emoji de verdade (§12).
