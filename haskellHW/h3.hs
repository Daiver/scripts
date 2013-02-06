
--Composition
f x = x * 2
g x = x + 2

h = f . g



main = do
    (putStrLn . show . h) 100
