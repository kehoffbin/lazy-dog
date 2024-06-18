import Parser

import Control.Monad (Monad)
import Control.Applicative
import Data.Char
import Text.Pretty.Simple

-- an valueression
data Value =
    Name String
    | TypeName String
    | NumLit String
    deriving (Show, Eq)

-- parse an valueression
value :: Parser Value
value = ws *>
    name
    <|> typeName
    <|> numLit



ws :: Parser ()
ws = const() <$> (many $ any_char `when` ((== ' ') <||> (== '\t')))

-- parses a name ie an identifier
name :: Parser Value
name = fmap Name $  (:)
    <$> (any_char `when` isAsciiLower)
    <*> (many $ any_char `when` (isAsciiLower <||> isDigit <||> (=='_')))

-- parses a type name
typeName :: Parser Value
typeName = fmap TypeName $ (:)
    <$> (any_char `when` isAsciiUpper)
    <*> (many $ any_char `when` (isAsciiUpper <||> isAsciiLower <||> isDigit))

-- parses a number literal
-- still keep it in string form
-- since we do not know what size the string is gonna have
-- besides, we want to embed the number literal in C code,
-- so making it a number wouldn't be beneficial
numLit :: Parser Value
numLit = fmap NumLit $ some $ any_char `when` isDigit

data Clause =
    FnClause [Block]
    deriving Show

data Block =
    ValueBlock Value
    | ParenBlock Block
    deriving Show

clause :: Parser Clause
clause = fnClause

fnClause :: Parser Clause
fnClause = fmap FnClause $
    some ((optional ws) *> block)
    <* optional(char '\n')

block :: Parser Block
block = 
    valueBlock
    <|> parenBlock

valueBlock :: Parser Block
valueBlock = ValueBlock <$> value

parenBlock :: Parser Block
parenBlock = fmap ParenBlock $
    block `between` (char '(', char ')')

main = do
    -- file <- readFile "test.he"
    pPrint $ parse (name) "hello world"