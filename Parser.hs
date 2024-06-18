{-# language LambdaCase #-}
module Parser (
    Parser,
    parse,  -- only use at the end of parsing
    when,
    any_char,
    char,
    string,
    (<||>),
    (<&&>),
    some_sep_by,
    many_sep_by
) where

import Control.Monad (Monad)
import Control.Applicative
import Data.Char

-- parses start of a string
-- if successful, returns some a and the remainder of the string
newtype Parser a = Parser {parse :: String -> Maybe(a, String)}

instance Functor Parser where
    fmap f p = Parser $ \str -> do
        (x, rest) <- parse p str
        pure (f x, rest)

instance Applicative Parser where
    pure x = Parser $ \str -> Just(x, str)
    pf <*> p = Parser $ \str -> do
        (f, rest) <- parse pf str
        parse( f <$> p) rest

join :: Parser (Parser a) -> Parser a
join pp = Parser $ \str ->
    (parse pp str) >>= (uncurry parse)

instance Monad Parser where
    x >>= f = join(fmap f x)

instance Alternative Parser where
    empty = Parser $ const Nothing
    p1 <|> p2 = Parser $ \str -> 
        case parse p1 str of
            Just(x, rest) -> Just(x, rest)
            Nothing -> parse p2 str

-- parses any single character
any_char :: Parser Char
any_char = Parser $ \case
        "" -> Nothing
        c:rest -> Just(c, rest)

-- parses if p parses and the result satisfies pred
when :: Parser a -> (a -> Bool) -> Parser a
when p pred = do
    x <- p
    if pred x
        then pure x
        else empty

-- parse the specific character c
char :: Char -> Parser Char
char c = any_char `when` (== c)

-- parse a specific string
string :: String -> Parser String
string "" = pure ""
string (c:str) = (:) <$> char c <*> string str

-- lift the boolean operators to work on properties
(<||>) :: (a-> Bool) -> (a->Bool) -> (a-> Bool)
(<||>) = liftA2 (||)

(<&&>) :: (a-> Bool) -> (a->Bool) -> (a-> Bool)
(<&&>) = liftA2 (&&)


-- like some and many, but with a delim interspersed
some_sep_by :: Parser a -> Parser b -> Parser [a]
some_sep_by item delim = (:)
    <$> item
    <*> (many $ delim *> item)

many_sep_by :: Parser a -> Parser b -> Parser [a]
many_sep_by item delim = (fmap concat) $ optional $ (some_sep_by item delim)