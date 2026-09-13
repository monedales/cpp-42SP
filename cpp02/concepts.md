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

## 7. Deslocamento de bits (`<<`/`>>`) pra escalar o valor fixo

```cpp
this->value = i_num * (1 << fractBits);   // int -> fixed: escala pra cima
return (this->value >> this->fractBits);  // fixed -> int: escala pra baixo, trunca a fração
```

`<<` desloca bits pra esquerda, equivalente a multiplicar por `2^n`. `>>` desloca pra direita, equivalente a dividir por `2^n` (descartando o resto — por isso `toInt()` trunca em vez de arredondar). Usei `i_num * (1 << fractBits)` em vez de `i_num << fractBits` direto porque deslocar um `int` **negativo** com `<<` é comportamento indefinido em C++98; multiplicar por um número positivo não tem esse problema.

---

## 8. Float ↔ Fixed: multiplicar/dividir pelo fator de escala

```cpp
this->value = static_cast<int>(roundf(f_num * (1 << this->fractBits)));  // float -> fixed
return (static_cast<float>(this->value) / (1 << this->fractBits));        // fixed -> float
```

Não dá pra usar `<<`/`>>` num `float` (são operadores de bits, só existem pra tipos inteiros), então a conversão vira multiplicação/divisão de verdade. Como multiplicar um float pelo fator de escala pode não dar um número inteiro exato, `roundf` arredonda antes de converter pra `int` com `static_cast`. Lendo de dentro pra fora: primeiro escala, depois arredonda, depois converte de tipo.

---

## 9. `operator<<` precisa ser função livre, não método

```cpp
std::ostream &operator<<(std::ostream &o, const Fixed &f)
{
    o << f.toFloat();
    return o;
}
```

Como método da classe, `Fixed` teria que estar do lado esquerdo do `<<` (`fixed.operator<<(...)`) — mas quem fica à esquerda na prática é o `std::cout`. Por isso a função vive fora da classe (declarada no `.hpp` depois do `};`), usando só os métodos públicos do `Fixed` (`toFloat()`), sem precisar de `friend`. Retorna `std::ostream&` pelo mesmo motivo do `operator=` retornar `Fixed&`: permitir encadear (`std::cout << a << std::endl;`).

---

## 10. Palavra reservada como nome de parâmetro

`float`, `int`, `class` etc. são palavras-chave da linguagem — não podem ser usadas como nome de variável ou parâmetro (ex: `const Fixed &float` não compila). Erro fácil de cometer quando o nome "óbvio" pro parâmetro é justamente o tipo que ele representa.

---

## 11. Métodos estáticos: sem `this`, e `static` só aparece no `.hpp`

```cpp
// .hpp
static Fixed &min(Fixed &a, Fixed &b);

// .cpp — sem static, só Fixed::
Fixed &Fixed::min(Fixed &a, Fixed &b) { ... }
```

Método estático pertence à classe, não a um objeto — chama-se `Fixed::min(a, b)`, sem instância na frente, e não existe `this` dentro dele. `static` não é parte do "tipo" da função (diferente do `const` no final de método, que muda a assinatura), é só uma instrução de como ela é chamada — por isso não se repete na definição fora da classe.

---

## 12. Duas versões (const/não-const) pra preservar mutabilidade do retorno

```cpp
static Fixed &min(Fixed &a, Fixed &b);                     // aceita e devolve não-const
static const Fixed &min(const Fixed &a, const Fixed &b);   // aceita e devolve const
```

Se só existisse a versão `const`, chamar `min` com dois `Fixed` não-const ainda funcionaria (conversão implícita pra `const`), mas o retorno seria `const Fixed&` — perdendo a possibilidade de modificar o resultado depois, mesmo os originais não sendo `const`. Ter as duas versões garante que a "constância" de entrada se mantém na saída.

---

## 13. O "menor ϵ representável" é só +1 no valor cru

```cpp
this->value += 1;   // ++, epsilon
this->value -= 1;   // --
```

Como `value` já é o número real multiplicado por `2^fractBits`, cada unidade inteira dele vale `1/2^fractBits` no mundo real (aqui, `1/256`). Por isso o menor incremento representável não precisa de cálculo nenhum — é literalmente somar `1` ao inteiro cru. Testado e confirmado: `++a` a partir de `0` deu `0.00390625`, que é `1/256`.

---

## 14. Pré vs pós incremento: assinatura e tipo de retorno

```cpp
Fixed &Fixed::operator++(void);   // pré: ++a — modifica e retorna o próprio objeto (referência)
Fixed  Fixed::operator++(int);    // pós: a++ — guarda cópia do valor antigo, modifica o original, retorna a cópia
```

O `int` no pós-incremento nunca é usado — existe só pra dar uma assinatura diferente da versão pré, permitindo o compilador escolher a certa. A diferença de tipo de retorno reflete o que cada um "significa": `++a` já é o valor novo (por isso retorna referência ao próprio objeto), enquanto `a++` precisa devolver o valor de **antes** da mudança (por isso precisa copiar antes de modificar, e retorna por valor, não por referência — devolver referência pra uma cópia local que vai morrer ao sair da função seria um dangling pointer).

---

## Dúvidas / a aprofundar

- [ ] Revisitar a decisão do construtor de cópia delegar pro `operator=` quando aparecer a primeira classe com memória alocada dinamicamente.
