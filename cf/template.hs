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


main = do
    src <- getLine--readNum
    putStrLn $ show (work (map strToInt ( splitStr src ' ')))

