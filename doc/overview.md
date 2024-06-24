# Hechle High-Level Overview
this is a high-level overview of the hechle programming language.
this document contains
* loose explanations
* and syntax examples
but not
* rigorous definitions
* nor any exact specification.
it is also not a tutorial.

Hechle is a statically typed and (impurely) functional.
A cross-compiler to C written in Haskell is undder construction.

## Design Goals
language design is ultimately an act of compromise.

Hechle can't do everything all at once, so below is a list of priorities.
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

## Basic Tokens
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
character are written in single quotes, strings in doulbe quotes
```
'x'
"hello world"
```
strings have normal C-style escape sequences.
string interpolation is done via `$_`, `$name` or `${expression}`
expression may be multiline, otherwise strings must not be multiline
raw strings start with `$@`
```
"line\nsecond line"
"I am $years old. Next year, I'll be ${years} old"
"The answer is ${
    some_complicated_calculation
}, how cool is that?"
"Really hacky${
} and abusive multiline string."
"$@raw string"
```
num literals are sequences of digits.
floating num literals contain a `.`.
`_` may be used as visual separators
```
-- valid num literals:
123
1_000_000_000
4.0
1.000_001
-- invalid num literals:
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
tuples are monoidal:
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
|
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

## Expressions and Clauses
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
the inside of parenthesis is an Expression, ie `(expression)`
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