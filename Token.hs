module Token (
    Token(..),
    token,
    ws,
    name,
    typeName,
    numLit,
    symbol,
    keyword
) where

import Parser

import Control.Monad (Monad)
import Control.Applicative
import Data.Char

-- a token
data Token =
    Name String
    | TypeName String
    | NumLit String
    | Symbol String
    deriving (Show, Eq)

-- parse a token
token :: Parser Token
token = ws *> (
    name
    <|> typeName
    <|> numLit
    <|> symbol
    )

ws :: Parser ()
ws = const() <$> (many $ any_char `when` ((== ' ') <||> (== '\t')))

-- parses a name ie an identifier
name :: Parser Token
name = fmap Name $ (:)
    <$> (any_char `when` isAsciiLower)
    <*> (many $ any_char `when` (isAsciiLower <||> isDigit <||> (=='_')))

-- parses a type name
typeName :: Parser Token
typeName = fmap TypeName $ (:)
    <$> (any_char `when` isAsciiUpper)
    <*> (many $ any_char `when` (isAsciiUpper <||> isAsciiLower <||> isDigit))

-- parses a number literal
-- still keep it in string form
-- since we do not know what size the string is gonna have
-- besides, we want to embed the number literal in C code,
-- so making it a number wouldn't be beneficial
numLit :: Parser Token
numLit = fmap NumLit $ some $ any_char `when` isDigit

symbol :: Parser Token
symbol = fmap Symbol $ some $ any_char `when` (flip elem "+-*/,")

-- parses iff keyword is matched
keyword :: String -> Parser ()
keyword s = const() <$> (ws *> string s)
