{-# language LambdaCase #-}
import Parser
import Token

import Control.Monad (Monad)
import Control.Applicative
import Text.Pretty.Simple

data Value =
    TokenValue Token
    | TupleValue [Value]
    | FnValue Value [Value]
    deriving (Show)

unwrap :: Value -> [Value]
unwrap (TupleValue vs) = vs 
unwrap v = [v]

instance Semigroup Value where
    (<>) a b = TupleValue $ (unwrap a) ++ (unwrap b)

instance Monoid Value where
    mempty = TupleValue []

value :: Parser Value
value = as_value <$> node

as_value :: Node -> Value
as_value Empty = TupleValue []

as_value (Node (TokenValue (Symbol ",")) left right) =
    (as_value left) <> (as_value right)

as_value (Node head left right) =
    FnValue head (unwrap ((as_value left) <> (as_value right)))


node :: Parser Node
node = (foldl append Empty)
    <$> many clause_bit

clause_bit :: Parser Value
clause_bit = 
    ((keyword "(") *> value <* (keyword ")"))
    <|> (TokenValue <$> token)


-- a binary tree with a Value in each node
data Node =
    Empty
    | Node Value Node Node
    deriving (Show)

-- appends a value to this tree
-- trumping values go towards the root
append :: Node -> Value -> Node
append Empty value = 
    Node value Empty Empty

append node@(Node head left right) value =
    if value `trumps` head then
        Node value node Empty
    else
        Node head left (right `append` value)

-- whether or not one value trumps another,
-- ie has lower precedence
trumps :: Value -> Value -> Bool
trumps (TokenValue (Symbol ",")) _ = True
trumps _ _ = False

main = do
    file <- readFile "test.he"
    pPrint $ parse (value) file
