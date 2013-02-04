import Data.Char

splitStr::String -> Char -> [String]
splitStr [] spliter = [""]
splitStr (x:xs) spliter  
    | x == spliter = "" : rest
    | otherwise = (x : head rest) : tail rest
    where 
        rest = splitStr xs spliter

readNum :: IO Integer
readNum = readLn

strToInt :: String -> Integer
strToInt s = read s

swaphead (x:[]) = x:[]
swaphead (x:xs) = head xs:x:tail xs

changeonce [] = []
changeonce (x:[]) = x:[]
changeonce (x:xs) 
    | x == 'B' && head xs == 'G' = head xs : x : (changeonce $ tail xs)
    | otherwise =  x : changeonce xs

process l 0 = l
process l n = process (changeonce l) (n - 1)

work s s2 = process s2 s

main = do
    src <- getLine--readNum
    src2 <- getLine--readNum
    putStrLn $ work ((map strToInt ( splitStr src ' '))!!1) src2

