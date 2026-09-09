# Cheatsheet de defesa — cpp00

> Formato: **gatilho → resposta**. Detalhe completo está no `concepts.md`.

---

## Vocabulário

| Gatilho | Resposta |
|---|---|
| member attribute | variável declarada dentro da classe |
| member function | função declarada dentro da classe |
| `private` | só acessível de dentro da própria classe |
| `public` | acessível de fora |
| regra pra escolher | o que **sempre** só é usado dentro → `private`; o que precisa ser usado de fora → `public` |
| construtor | roda quando a classe é **instanciada**; lugar de inicializar atributos |
| destrutor `~` | roda quando o objeto é **destruído** (sai de escopo) |
| `this` | **ponteiro** pro próprio objeto — o `self` do Python; acessa atributos da própria instância |

---

## `const` e `static const`

| Gatilho | Resposta |
|---|---|
| `const` no fim do getter | promete que o método **não altera** atributo nenhum — compilador força |
| por que só nos getters | getters leem; setters precisam modificar |
| bônus | objeto `const` só aceita chamada de método `const` |
| `static const MAX_CONTACTS` | `static` = **da classe**, não de cada objeto; com valor inline vira **constante de compilação** |
| por que não `const` normal | `const` comum é por objeto e só existe em runtime → **não serve** como tamanho de array |
| pegadinha | tem que ser declarado **antes** do array (declaração de membro resolve nome na ordem) |

---

## Streams: estados

| Gatilho | Resposta |
|---|---|
| onde acha `ignore`/`clear` na doc | `cin` é instância de `istream`; métodos vêm por **herança**: `ios_base → ios → istream`. `ignore` em `istream`, `clear`/`fail`/`eof` em `ios` |
| `failbit` | última operação falhou → `cin.fail()` |
| `eofbit` | entrada acabou (Ctrl+D) → `cin.eof()` |
| Ctrl+D no `getline` | liga **as duas** flags |
| `clear()` | apaga as flags de erro |
| `ignore(max, '\n')` | descarta até achar `\n`; `numeric_limits<streamsize>::max()` = "quantos forem preciso" (`<limits>`) |
| **quando usar o combo** | só em **erro recuperável** (formato errado, lixo no buffer) |
| **por que NÃO no EOF** | EOF não é "veio errado", é "não vem mais nada". `clear()` apaga a flag mas não traz dado de volta → próximo `getline` falha na hora → **loop infinito** |
| por que `getline` e não `cin >>` | `getline` aceita espaço no meio (nome composto) e evita o `\n` sobrando no buffer |

---

## Conversões: **`atoi` vs `os/isstringstream`**

| Gatilho | Resposta |
|---|---|
| `int` → `string` | `ostringstream oss; oss << x; oss.str();` — `to_string` é C++11 ❌ |
| `string` → `int` | `istringstream iss(s); iss >> x && iss.eof();` |
| o que o `.eof()` garante ali | que a string era **só** o número, sem sobra |
| **por que não `atoi`** | `atoi` **não reporta erro** — não dá pra saber se deu certo |
| ↳ `atoi("abc")` | devolve `0`, **idêntico** a `atoi("0")` → indistinguível |
| ↳ `atoi("5abc")` | devolve `5`, ignora o lixo **calado** |
| ↳ overflow | comportamento indefinido |
| ↳ e ainda | é função **C**; o módulo pede abordagem C++ |
| meu jeito pega os 3 casos | `"abc"` → `>>` falha · `"5abc"` → `.eof()` falso · overflow → `failbit` |

---

## Onde cada coisa está no código

| Conceito | Onde |
|---|---|
| atributos privados + getters `const` | `Contact` |
| método auxiliar privado | `formatRow` (só o `listContacts` usa) |
| `enum` dentro da classe | `Contact::e_field` |
| `switch/case` | `Contact::SetField` |
| `static const` | `PhoneBook::MAX_CONTACTS` |
| `ostringstream` | `formatRow` (índice → string) |
| `istringstream` + `.eof()` | `parseIndex` |
| `setw`/`right` + `substr` | `formatColumn` (colunas de 10, alinhadas/truncadas) |
| `%` | `contacts[count % MAX_CONTACTS]` — rotação circular |
| referência `&` | `parseIndex(..., int &result)` e `validateField(..., bool &quit)` |
| arrays paralelos | `addContact` — `questions[]` + `fields[]` no lugar de um `switch` de 5 casos |

---

## O que vale eu oferecer (acima do exigido)

**Tratamento de Ctrl+D.** A régua só exige *"não segfaultar"* — não há comportamento esperado no subject. Eu fui além:

- distingo `eof()` de `fail()`: EOF é fim da entrada, não input inválido
- no EOF **não** chamo `clear()`/`ignore()` — não tem o que recuperar
- o "quero sair" viaja por um `bool &quit` **separado** do valor de retorno
- por quê separado: `std::string` não tem valor nulo; qualquer string sentinela colide com dado real, e `return NULL` numa função que devolve `std::string` é **comportamento indefinido**

**Loop único no `validateField`.** Antes tinha duas leituras duplicadas e o prompt saía dobrado — consertava uma cópia e esquecia a outra.

---

## ⚠️ Pontos fracos

| Gatilho | Resposta |
|---|---|
| coluna desalinha com acento/emoji | `length()`, `substr` e `setw` contam **bytes**, não caracteres |
| ↳ como consertaria | contar code points UTF-8 em vez de bytes |
| ↳ e o emoji | continuaria torto: ocupa **2 colunas** no terminal → precisaria de `wcwidth()`, que é POSIX, não C++98 |
| ↳ por que deixei | régua do SEARCH: *"a formatação da saída pode ser diferente, não importa"* — e o foco é usar **iomanips**, que a correção manual eliminaria |
| megaphone não maiúscula `ãé` | `toupper()` trabalha byte a byte, não entende UTF-8 — mesma raiz, não é exigido |
