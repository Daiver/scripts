
twiddle estimate p dp tol = twid estimate p dp tol (estimate p)
    where 
        twid estimate p dp tol err 
            | err < tol = p
            | otherwise = optimizeOne p
        optimizeOne p = p ++ [321]

est l = 0.00001

work l = twiddle est l [0.1 | x <- l] 0.00001

main = do
    (putStrLn . show . work) ([1, 2, 3])
