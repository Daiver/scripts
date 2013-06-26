import Data.Char

splitStr::String -> Char -> [String]
splitStr [] spliter = [""]
splitStr (x:xs) spliter  
    | x == spliter = "" : rest
    | otherwise = (x : head rest) : tail rest
    where 
        rest = splitStr xs spliter

strToInt :: String -> Integer
strToInt s = read s

changeonce [] = []
changeonce (x:[]) = x:[]
changeonce (x:xs) 
    | x == 'B' && head xs == 'G' = head xs : x : (changeonce $ tail xs)
    | otherwise =  x : changeonce xs

process l 0 = l
process l n = process (changeonce l) (n - 1)

main = do
    nums <- getLine
    queue <- getLine
    putStrLn $ process queue ((map strToInt ( splitStr nums ' '))!!1) 

