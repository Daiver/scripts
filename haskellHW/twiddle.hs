import Data.List
replaceAtIndex n item ls = a ++ (item:b) where (a, (_:b)) = splitAt n ls
enumerate = zip [0..]
twiddle estimate p dp tol = twid estimate (zip3 p dp [estimate p | _ <- p]) tol (estimate p)
    where 
        twid estimate pp tol err --pp - packed params
            | err < tol = p
            | otherwise = twid estimate (map optimizeOne (enumerate pp)) tol err
            where 
                optimizeOne (i, (par, dpar, err))
                    | estimate (replaceAtIndex i (par + dpar) p) < err = (par + dpar, dpar*1.1, estimate (replaceAtIndex i (par + dpar) p))
                    | estimate (replaceAtIndex i (par - dpar) p) < err = (par - dpar, dpar*1.1, estimate (replaceAtIndex i (par - dpar) p))
                    | otherwise = (par, dpar*0.9, err)


est l = 0.00001

work l = twiddle est l [0.1 | x <- l] 0.00001

main = do
    (putStrLn . show . work) ([1, 2, 3])
