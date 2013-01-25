numesfrom n = n : numesfrom (n + 1)
natural = numesfrom 0
squares n = map (^2) (numesfrom n)
deepfun x y = f1 x + f2 y
    where 
        f1 x = x^2
        f2 x = 2 * f21 x
            where f21 x = x-1

condfunc1 x y 
        | x > y = "X > Y"
        | x < y = "X < Y"
        | x == y = "X == Y"

somelist1 = [1, 2, 3, 8798966]
psomelist1 = tail somelist1
psomelist2 = head somelist1
psomelist3 = last somelist1
psomelist4 = init somelist1
main = do--putStrLn 34
    print psomelist4
    --print (take 9 (squares 0))
