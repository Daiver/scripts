(ns hello.core)

(defn abs [x] (if (< x 0) (- x) x))
(defn square [x] (* x x))
(defn average [x y] (/ (+ x y) 2.0))
(defn good_enough? [guess old_guess threshold] (< (abs (- guess old_guess)) threshold))
(defn ident [x] x)
(defn sum
    ([a b term next]
        (if (> a b)
            0
            (+ (term a)
                (sum (next a) b term next)
            )
        )
    )

    ([seq]
        (if (= (count seq) 0)
            0
            (+ (first seq) (sum (next seq)))
        )
    )

    ([]
        0
    )
)

(defn product
    [a b f next]
    (loop [i a res 1]
        (if (> i b)
            res
            (recur (next i) (* (f i) res))
        )
    )
)

(defn pi_num
    [n]
    (* 2
        (/ 
            (product 2 n #(* 1.0 % %) #(+ 2 %)) 
            (* (product 3 (dec n) #(* 1.0 % %) #(+ 2 %)) (inc n))

        )
    )
)

(defn fact [n] (product 1 n #(ident %) #(inc %)))

(defn -main
    ""
    [& args]
    (println "version" (clojure-version))
    (time (println (pi_num 160)))
    ;(println (fact 20))
    ;(println (product 1 5 #(ident %) #(inc %)))
)

(comment
    ;(println (sum 1 5 #(+ %1) #(+ %1 1)))
    ;(println (sum [1 2 3 4 5]))
    ;(println (cube_sqrt 75.))
    ;(println (sqrt_iter2 1.0 900.0 900.0))

    (defn good_enough? [guess x] (< (abs (- x (square guess))) 0.001))
    (defn sqrt_iter
        [guess x]
        (if (good_enough? guess x)
            guess
            (sqrt_iter (improve guess x) x)
        )
    )
    (defn useless_rec
        []
        (useless_rec)
    )

    (defn useless_param
        [x]
        100
    )

    (defn find_brackets
        [l s]
        (if (> (count s) 0)
            (concat l [(first s)] (find_brackets l (next s)))
            ""
        )
    )
    ;(println (sqrt_iter 1.0 900.0))
    ;(println (useless_param (useless_rec)))
    ;(println (abs -10))
    ;(println (abs 10))
    ;(println (average 10 5))
    ;(println (good_enough? 100.01 10))

    ;(def arg (first args))
    ;(println 
    ;    (find_brackets [] (first args))
    ;)
    ;(println (extract arg))
    ;(println (#(* 10 %1) 10))
    (comment
        (println "args count" (count args))
        ;(println  (next (next args)))
        (println 
            (filter #(> % 10)
                (map
                    #(* % 10)
                    (map read-string args)
                )
            )
        )
        (println
            (map
                #(int %1)
                (map 
                    #(+ %1 %2 ) '(1 2 3 4) '(2 2 2 2)
                )
            )
        )
        (.substring s (.indexOf s "(") (+ (.indexOf s ")") 1) )
    )
(defn improve [guess x] (average guess (/ x guess)))

(defn good_enough2? [guess old_guess] (< (abs (- guess old_guess)) 0.001))
(defn sqrt_iter2
    [guess old_guess x]
    (if (good_enough2? guess old_guess)
        guess
        (sqrt_iter2 (improve guess x) guess x)
    )
)
(defn cube_improve
    [guess x]
    (/ (+ (/ x (square guess)) (* 2 guess)) 3)
)

(defn cube_sqrt_iter
    [guess old_guess x]
    (if (good_enough? guess old_guess 0.001)
        guess
        (cube_sqrt_iter (cube_improve guess x) guess x)
    )
)

(defn cube_sqrt
    [x]
    (cube_sqrt_iter 1. x x)
)


)

