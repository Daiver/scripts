operate2::String -> String
operate2 str = "Haskell Hello too " ++ str

splitStr::String -> Char -> [String]
splitStr [] spliter = [""]
splitStr (x:xs) spliter  
    | x == spliter = "" : rest
    | otherwise = (x : head rest) : tail rest
    where 
        rest = splitStr xs spliter

reverse2 [] = []
reverse2 [x] = [x]
reverse2 lst = last lst :  reverse2 (init lst) 

connect [] = []
connect lst = head lst ++ "\n" ++ connect (tail lst)

operate str = connect( reverse ( splitStr str '\n'))

main = do
    src <- readFile "input"
    --print $ reverse2 "hello my name is" 
    writeFile "output" (operate src)
