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

result n m a = closer n a * closer m a
    where 
        closer n a = n `div` a + ntail n a
        ntail n a 
            | n `mod` a > 0 = 1
            | otherwise = 0

work l = result (l!!0) (l!!1) (l!!2)

main = do
    src <- getLine--readNum
    putStrLn $ show (work (map strToInt ( splitStr src ' ')))

