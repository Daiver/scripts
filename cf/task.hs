
cutPatt patt str
    | take 3 str == patt = cutPatt patt (drop 3 str) 
    | otherwise = str

cutFirst = cutPatt "WUB"

cutLast str = reverse (cutPatt "BUW" (reverse str))

cutMiddle [] = []
cutMiddle str 
    | take 3 str == "WUB" = " " ++ (cutMiddle $ drop 3 str)
    | otherwise = head str : (cutMiddle $ tail str)

main = do
    src <- getLine
    putStrLn $ cutMiddle $ cutFirst $ cutLast src--"WUBWEWUBAREWUBWUBTHEWUBCHAMPIONSWUBMYWUBFRIENDWUB"
