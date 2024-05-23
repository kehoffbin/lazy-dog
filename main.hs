{-# language LambdaCase #-}
import Control.Monad

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
join pp = Parser $ \str -> do
    (p, rest) <- parse pp str
    parse p rest

instance Monad Parser where
    x >>= f = Main.join(fmap f x)


-- parses any single character
any_char :: Parser Char
any_char = Parser $ \case
        "" -> Nothing
        c:rest -> Just(c, rest)

-- parse p, but only if the result matches pred
when :: Parser a -> (a -> Bool) -> Parser a
when p pred = Parser $ \str -> do
    (x, rest) <- parse p str
    if pred x 
        then pure (x, rest)
        else Nothing

main = putStrLn $ show $ parse any_char "hello world"