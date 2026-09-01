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

---

## 9. String streams (`<sstream>`)

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
- `iss.eof()` → método que informa se o stream **chegou ao fim** (end of file). Combinado com `iss >> result`, garante que a string era *só* um número, sem sobras.

> `EOF` (maiúsculo) é a **constante** "end of file"; `.eof()` é o **método** que checa se chegou lá.

---

## 10. `<iomanip>` — manipuladores de formato

Controlam como o stream formata a saída.

- `std::setw(n)` → largura mínima de `n` caracteres (só **preenche** com espaço se for menor; **não trunca** se for maior).
- `std::right` → alinha à direita dentro dessa largura.

```cpp
result << std::right << std::setw(10) << value;  // "       Ana" (10 chars)
```

> Como `setw` não trunca sozinho, no projeto usei `substr(0, 9) + "."` pra cortar textos longos manualmente.

---

## 11. Getters e setters

- **Getter**: lê um atributo privado de fora da classe (`const`).
- **Setter**: escreve num atributo privado de fora da classe.

Padrão pra preencher um objeto aos poucos: construtor vazio + setters chamados um a um (útil quando os dados chegam em momentos diferentes, ex: input campo a campo).

---

## 12. Conexão com o projeto (cpp00 / PhoneBook)

Onde cada conceito apareceu na prática:

| Conceito | Onde usei |
|----------|-----------|
| `.hpp`/`.cpp` + `::` | Toda implementação de método (`Contact::`, `PhoneBook::`) |
| `private` + getters/setters | `Contact`: atributos privados, `SetField` + 5 getters |
| `enum` dentro da classe | `Contact::e_field` pra identificar qual campo o `SetField` preenche |
| `switch/case` | Escolher pergunta/campo no `addContact` |
| `const` | Todos os getters de `Contact` |
| `getline` pra tudo | Leitura de comando e dos 5 campos (evita bug do buffer) |
| Validação "não vazio" | `validateField()` — `while (value.empty())` |
| `ostringstream` | `formatRow` — converter índice `int` → `std::string` |
| `istringstream` + `.eof()` | `parseIndex` — validar que o índice é um número puro |
| `setw`/`right` + `substr` | `formatColumn` — colunas de 10 chars alinhadas/truncadas |
| Operador `%` | `contacts[count % 8]` — rotação circular (substituir o mais antigo) |
| Referência (`&`) | `parseIndex(std::string, int &result)` — "devolver" 2 coisas |
| "Include what you use" | Ajuste final de dependências em todos os arquivos |

---

## Dúvidas / a aprofundar

- [ ] Templates e function overloading (vistos de raspão, formalizados em módulos futuros).
- [ ] Forma Canônica Ortodoxa (a partir do módulo 02).
