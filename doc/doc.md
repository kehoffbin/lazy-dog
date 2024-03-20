# objects
a lazy-dog program is a stream of objects.

a token is any of the following:
* identifier
* type identifier
* symbol
* num literal
* string literal

tokens are also objects

objects can be concatenated

# types
```
	def:Type TypeIdentifier ArgList;
```

each object has a type.

bits of data:
* Data1, Data2, ...
* SystemSize

tokens:
* NumLiteral
* StringLiteral
* Identifier
* TypeIdentifier
* Symbol

tags:
* Num
* String
* Ptr<T>
* Boolean
* FnPtr<...>

monoids:
* Nothing
* Union<T,U>
* Cat<T,U>
* Enum<T,U>
* Struct<Identifier = Type>

x -> T casts value to Type
x ->? T checks if value can be cast to type
x ->! T tags x as T regardless of content. danger!
x : T asserts that x be of type T

# functions
builtins
all namespaced under co::

literals:
* parse Literal

pointer stuff:
* let
* call FnPtr Args
* fn-ptr Args { body }
* memb Struct const Identifier
* get Ptr
* free Ptr
* malloc Num

basic functions:
* add Num64 Num64
* ...
* print String

included headers (always Any):
* stdio::printf Any

branching
* if-then-else cond body body
* while cond body

# defs
```
def :Def
	_def
	Maybe<GenericArgs>
	Maybe< : TargetType>
	Pattern
	Substitution

def	:Substitution
	_; ;
def	:Substitution
	_-> replacement _; ;
def	:Substitution
	_-> { replacement } ;
def	:Substitution
	_-> _@ { macro } ;

def :Pattern;
def :Pattern PatternEntry;

def :PatternEntry Esc<Identifier>;
def :PatternEntry Symbol;
def :PatternEntry Type;
def :PatternEntry Identifier _: Type;
def :PatternEntry Identifier;
```

replace object matching pattern with substitution

escaped identifiers and sybmols are matched verbatim
otherwise tries to match sub object against Type
Identifier is variable in Substitution

macros are functions that process the tokens

must have either:
* target
* unescaped identifier
* symbol

() [] {} <> are matched in balance

defs are scoped by {}

# const
type Const

tokens in the source code are const

functions ConstFn unless:
* calls non const fn
* non const argument
* included from C
* uses pointer outside scope

ConstFn is not Const + FnPtr
