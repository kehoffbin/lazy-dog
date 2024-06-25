# Hechle Overview
this is a loose specification of the Hechle programming language.
any remaining ambiguities are either
- be inferred by what was probably meant
- be amended to this document
- be resolved in the way most easily implemented

this is not a tutorial.

## Design Goals
Hechle is a statically typed and (impurely) functional.
A cross-compiler to C written in Haskell is undder construction.

language design is ultimately an act of compromise, so below is a list of priorities.
when in conflict, higher entries almost always trump lower ones.
1. **Pretty:** code should look good, according to my personal subjective taste. 
2. **Flat Flow:** avoid nesting. this includes parenthesis, (prefix) function calls, and indentation 
3. **Concise:** verbosity is evil. favour abstract short code, even if it might take longer to understand
4. **Abstract:** a good strong healthy dose of abstraction.
5. **Simple:** be conceptually as simple as possible, both in design and implementation
6. **Friendly:** have syntax that is easy to pick up by being similar to other languages
7. **Fast to Compile**: compilation should be as fast as possible
8. **Fast at Runtime:** don't be horribly inefficient
9. **Interoperable with C:** non-abstract data should be interoperable between C and Hechle 
10. **Predictable:** have predictable memory management
11. **Portable:** be portable across operating systems

# Values
## Basic Values
comments start with `--`. there are no multi-line or inline comments
```
-- this is a comment
```

names (aka identifiers) are in `snake_case`
```
my_cool_variable
deli2go
call_9_1_1
```
type names are in `PascalCase`
```
Str
Vector3D
```
(custom) operators consist of `#$%&*+,-./;<=>?@[\]^\{|}~`
```
+
<|>
```
character are written in single quotes, strings in double quotes
```
'x'
"hello world"
```
strings have normal C-style escape sequences.
string interpolation is done via `$_`, `$name` or `${expression}`.
expression may be multiline, otherwise strings must not be multiline.
raw strings start with `$@`
```
"line\nsecond line"
"I am $age years old. Next year, I'll be ${age+1} years old"
"The answer is ${
    some_complicated_calculation
}, how cool is that?"
"Really hacky${
} and abusive multiline string."
"$@raw string"
```
num literals are sequences of digits.
floating num literals contain a `.`.
`_` may be used as visual separator.
```
-- valid num literals:
123
1_000_000_000
4.0
1.000_001
-- invalid num literals:
.5
4.
4._0
1__000
-- valid number expressions, but not *just* num literals:
-4
3+2i
1.e24
1.e(-10)
-- valid expressions, but not numbers
_4
4_
3.to_string
```

## Functions and Tuples
tuples can be constructed via `,`
```
a, b, c
```
tuples are associative:
```
(a,b), c == a, (b, c) == a, b, c
(a) == a
```
if this is undesirable, you can box any value with `[_]`
```
[[a, b], c] /= [a,[b, c]] /= [a, b, c]
[a] /= a
```
functions can take multiple arguments and return multiple values.
to pass an argument to function, write it directly next to it.
this typically requires using `()` as delimiter
```
f(x)
f(x,y)
```
alternatively, if a space is given after a function,
the entire remainder of the expression is passed to the function
```
f x
f x, y
```
this only happens if `f` is not immediately followed by an operator
```
f, g
f + g
```
use the `.` operator for method-like syntax.
this can be mixed and matched freely with the above
```
x.add y
(x,y).add
add x, y
```
like all operators, `.` is left-associative:
```
1.add(2).square
-- 9
1.add 2.square
-- 5
```

## Operators
An operator is just a function whose name consists of special characters (see above).
All operators are binary and infix.

all operators are left-associative.
```
a / b /c == (a/b)/c
a ** b ** c == (a**b)**c
```
each operator has a (user-defined) precedence.
here is a list of common operators, ordered by precedence
```
.
+ -
* /
**
== /= < > <= >=
&& ||
,
```

## Partial Evaluation and Lambdas
in Hechle, functions are first-class citizens.
functions (including operators) can be partially evaluated to return another function
there is no distinction between a value and a function with zero arguments.
```
add 1
some_list.map(add 1)
```
functions can also be constructed as lambda expressions
```
x => add x, 1
```
alternatively, the blank `_` can also be used to create functions
```
add _, 1
```
left arguments go to the left and right arguments go to the right, ie
```
(1/) == x => 1/x
(/2) == x => x/2
1.divide_by == x => divide_by(1,x)
divide_by(2) == x => divide_by(x,2)
```

## Clauses
everything discussed so far were Expressions.
a Clause is generally a line of code like we saw above
although multiple clauses can be put on the same line
using `|` as separator
```
clause1 | clause2 | clause3
```
a Clause can just contain an Expression.
multiple such Clauses are combined via function composition
```
1
add 2
square
-- 9
```
a leading `,` can be used to instead combine them via tuples
```
1
,2
add
-- 3
```
if there are more values "on the stack" than a function needs,
then it will leave the remaining ones as is
```
1, 2, 3
mult
add
-- 1+(2*3)
```
in particular, for plain old values, the leading `,` is optional:
```
1
2
add
-- 3
```
the inside of parenthesis is an Expression, ie `(expression)`.
to cram a Clause-Block into an Expression, use indentation
```
a (
    clause1
    clause2
) b
```
alternatively, use `:`
```
f: clause1
    clause2
    clause3
== f (
    clause1
    clause2
    clause3
)
```
be careful though. if you do not use `:`,
the indent will be considered a tuple of expressions instead
```
exp1
    exp2
    exp3
== exp1 (exp2, exp3)
```
if `::` (followed by newline) is used instead of `:`, the indent is not necessary, ie
```
f::
clause1
clause2
```
is equivalent to
```
f:
    clause1
    clause2
```

# Modules
Modules are used to structure Hechle programs.

A Module is declared via
```
mod ModuleName:
    contents
```
or
```
mod ModuleName::
contents
```
Module Names are in `PascalCase`.

file names in Hechle are in `dash-case` and have the `.he` extension. 
```
mod FileName::
```
is implicitly added at the top, where FileName is the PascalCase-ified version of the file name.

if a module contains multiple submodules of the same name, they are joined

## Symbols
a Symbol represents a Value, a Type or a Module.
each Symbol belongs to a Module.
a Symbol is identified via its Module and a unique (within that Module)
Name, Type Name or Operator Name.

## Defintions
to add a symbol to a Module, use the `def` keyword.
the most basic form is
```
def name = expression
def TypeName = Type
```
but more elaborate `def`initions will be described below.

a submodule (which is also a Symol) is added via `mod`.

## Context
the Context of a Module is a list of Symbol definitons active within that Module.
you can only use a Symbol if it is in Context.

if a `Module` is in Context, and `symbol` is exported by the Module,
it can be referred to via `Module::symbol`.

## Prelude and Std
`Prelude` is a module whose contents are always implicitly imported.

`Std` is always implictly imported (but not its contents), it is the standard library module.


## Imports
if a `Module` is in Context and exports `symbol`, then
```
import Module::symbol
```
can be used to add `symbol` to the current Context.
```
mod SubModule:
    export five
    def five = 5

import SubModule::five
def ten = five+five
```
if `symbol` is a Module itself, its exports will (non-recursively) be added to the Context.

if two imports introduce name clashes, one might silently shadow the other if
it has higher precedence:
1. explicit import of a symbol
2. implicit import because parent module was explicitly imported
3. implicit import of Std
4. implicit import of Prelude
if both imports have the same precedence, the ambiguous name 
must be qualified by parent module.

imports can be made concise using tuple syntax
```
import Module::(some_thing, SubModule::another_thing)
```

## Exports
exports regulate which values can be imported by other modules.
not every Symbol that is available within the module is exported.

however, every `def` and every sub`mod`ule are always exported.
if this is undesirable, it is conventional to use a submodule named `Internal`.

to export a different symbol, use
```
export symbol
```

# Types
## Atomic Types and Number Types
an Atomic Type is a Type that cannot be constructed from other Types.

specifically, the Atomic Types of Hechle are the Number Types,
representing signed, unsigned and floating numbers of various sizes
```
Num8, Num16, Num32, Num64
UNum8, UNum16, UNum32, UNum64
FNum32, FNum64, FNum128
```

## Product Types (Tuples)
two Types `T` and `U` can be combined via `,` into their Product `T,U`.
if `x` is of Type `T` and `y` of Type `U`, the Tuple `x,y` is of Type `T,U`.

the Type Product is monoidal.
the identity element is called the Unit Type or Empty Type and can be written as `()`
```
(T,U), V == T, (U, V)
T,() == (),T == T
```

a Type `T` is called a Monotype if it represents a singlular value.
specifically, each Atomic Type is a Monotype.

a Multitype is a Product of Monotypes.
in particular, Monotypes are Multitypes.

instead of Multitype we sometimes also say Value Types because they are the only
kind of inhabited Type, ie representing data.

by (proper) Multitype we sometimes also mean non-mono Value Types.

## Boxed Types
we can turn a Multitype `T` into a Monotype `[T]` by boxing.
for example, `[Num32, FNum64, Num8]` is a Monotype.

even for Monotypes, `T` is distinct from `[T]`

## Function Types
given two Multitypes `T` and `U`, the Type `T->U` represents the Function Type from `T` to `U`.

## Union Types (Enums)
given two Monotypes `T` and `U`, the Type `T|U` is their Union.
`T|U` is a Monotype again.

unioning is associative and commutative. it does not however have a neutral element
```
T | (U | V) == (T | U) | V == T | U | V
T | U == U | T
```
two non-union Types are disjoint or identical. therefore
```
T | T == T
```
a value of `T` can be turned into a value of `T|U` via the builtin function `inject<T,U>`

a function `T->V` and a function `U->V` can be turned into a function `T|U -> V`
via the builtin `extend<T,U,V>`

