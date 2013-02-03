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

process "" "" = ""
process s1 s2 
    | (take 1 s1) == (take 1 s2) = "0" ++ next
    | otherwise = "1" ++ next
    where next = process (drop 1 s1) (drop 1 s2)

main = do
    src <- getLine--readNum
    src2 <- getLine
    putStrLn $ process src src2

