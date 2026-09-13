# C++ — Conceitos (Módulo 02)

> Notas de estudo e referência. Tema do módulo: polimorfismo ad-hoc, sobrecarga de operadores e a Forma Canônica Ortodoxa (OCF). Padrão: C++98.

---

## 1. Forma Canônica Ortodoxa (OCF)

A partir do módulo 02, toda classe deve implementar essas quatro funções membro, a menos que o exercício diga o contrário:

- Construtor padrão
- Construtor de cópia
- Operador de atribuição de cópia (`operator=`)
- Destrutor

O código da classe é sempre dividido em dois arquivos: o `.hpp` com a definição (só assinaturas, sem implementação), e o `.cpp` com a implementação. Colocar implementação de função dentro do header (exceto templates) zera o exercício.

---

## 2. Construtor de cópia vs `operator=`: como distinguir

A pergunta certa: **o objeto do lado esquerdo já existe antes dessa linha rodar?**

```cpp
Fixed b(a);   // b NÃO existe ainda -> está sendo criado e copiado ao mesmo tempo -> construtor de cópia
Fixed c;      // c é criado (vazio)
c = b;        // c JÁ EXISTE -> está sendo sobrescrito -> operator=
```

---

## 3. `static const int` como membro: declarar vs definir

Um membro `static const int` (ex: bits fracionários do `Fixed`) pode ser escrito de duas formas:

```cpp
// Opção A — declarar no .hpp, definir no .cpp (mais seguro em C++98)
static const int fractBits;          // .hpp
const int Fixed::fractBits = 8;      // .cpp

// Opção B — inicializar direto no .hpp
static const int fractBits = 8;      // .hpp, sem definição no .cpp
```

B funciona pra tudo que só usa o valor em tempo de compilação (deslocamento de bits, por exemplo). Mas em C++98, se em algum momento você passar `fractBits` por referência ou pegar o endereço dele, a Opção B dá erro de linkagem por faltar uma definição "de verdade" em algum `.cpp`. A Opção A nunca tem esse problema, só custa uma linha extra.

---

## 4. Construtor de cópia delegando pro `operator=`

```cpp
Fixed::Fixed(const Fixed &src)
{
    *this = src;   // chama o operator= por dentro
}
```

Vantagem: não duplica a lógica de copiar, só existe um lugar que sabe copiar os dados.

Cuidado pra mais pra frente: isso é seguro aqui porque `Fixed` só tem um `int`. Quando uma classe tiver memória alocada dinamicamente, o `operator=` normalmente libera a memória antiga antes de copiar a nova — e dentro de um construtor não existe "memória antiga" ainda, então delegar pode acabar liberando um ponteiro não inicializado. Nesse cenário futuro, o certo é o construtor de cópia copiar os dados direto, sem chamar o `operator=`.

---

## 5. `operator=` por dentro

```cpp
Fixed &Fixed::operator=(const Fixed &src)
{
    if (this != &src)
        this->value = src.value;
    return *this;
}
```

| Parte | O que é / faz |
|---|---|
| `Fixed &` (retorno) | referência ao próprio objeto, não uma cópia nova |
| `(const Fixed &src)` | o lado direito do `=`; `const` porque só lê, `&` pra não copiar à toa |
| `this != &src` | checagem de autoatribuição (`c = c`); inofensivo aqui, mas vira hábito essencial quando há memória dinâmica envolvida |
| `this->value = src.value` | a cópia de verdade |
| `return *this` | desreferencia o ponteiro `this` e devolve o objeto atual, permitindo encadear `a = b = c;` |

Rastreando com `c = b;`: isso equivale a `c.operator=(b);`. Dentro da função, `this` aponta pra `c` e `src` é `b`.

---

## 6. `const` em parâmetro por valor não é igual a `const &`

```cpp
void setRawBits(int const raw);   // const aqui é diferente do const & do cpp01
```

Isso não é uma referência constante (como `const std::string &` do cpp01, que evita cópia E impede modificar o original). Aqui `raw` já é uma cópia local — o `const` só promete, pro código dentro da própria função, que essa cópia não vai ser reatribuída. Não afeta quem chama a função nem o que ela recebe.

---

## Dúvidas / a aprofundar

- [ ] Revisitar a decisão do construtor de cópia delegar pro `operator=` quando aparecer a primeira classe com memória alocada dinamicamente.
