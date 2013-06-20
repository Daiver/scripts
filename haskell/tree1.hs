import Data.List

data Tree a = Empty | Leaf a | Node a (Tree a) (Tree a) deriving (Eq, Ord, Show)

treeFromList [] = Empty
treeFromList (x:[]) = Leaf x
treeFromList (x:xs) = Node x 
                        (treeFromList (filter (<x) xs))
                        (treeFromList (filter (>x) xs))


main = do
    print $ treeFromList [4, 5, 1, 2, 9, 8]
