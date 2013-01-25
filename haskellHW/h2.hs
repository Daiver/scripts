--infinity lists
numesfrom n = n : numesfrom (n + 1)
natural = numesfrom 0
squares n = map (^2) (numesfrom n)

--define sub function
deepfun x y = f1 x + f2 y
    where 
        f1 x = x^2
        f2 x = 2 * f21 x
            where f21 x = x-1
--condition ????
condfunc1 x y 
        | x > y = "X > Y"
        | x < y = "X < Y"
        | x == y = "X == Y"

--listwork
somelist1 = [1, 2, 3, 8798966]
psomelist1 = tail somelist1
psomelist2 = head somelist1
psomelist3 = last somelist1
psomelist4 = init somelist1
--is element in list
findsample1 = elem 1 somelist1
findsample2 = elem 5 somelist1
findsample3 = 1 `elem` somelist1

--infix func
infixsample1 x y = x + y
infixsample1test = 5 `infixsample1` 4

--rangesample
rangesample1 = ['a' .. 'd']

--listwork2
condlist = [x**2 | x <- [-2..10], x > 2]
--from other resurse
boomBangs xs = [ if x < 10 then "BOOM!" else "BANG!" | x <- xs, odd x]   

main = do--putStrLn 34
    print (boomBangs [1..20])
    --print (take 9 (squares 0))
