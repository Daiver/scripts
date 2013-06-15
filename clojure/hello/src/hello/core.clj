(ns hello.core)

(defn square [x] (* x x))
(defn abs [x] (if (< x 0) (- x) x))
(defn good_enough? [guess x] (< (abs (- x (square guess))) 0.001))
(defn good_enough2? [guess old_guess] (< (abs (- guess old_guess)) 0.001))

(defn average 
    [x y]
    (/ (+ x y) 2.0)
)

(defn improve
    [guess x]
    (average guess (/ x guess))
)

(defn sqrt_iter
    [guess x]
    (if (good_enough? guess x)
        guess
        (sqrt_iter (improve guess x) x)
    )
)

(defn sqrt_iter2
    [guess old_guess x]
    (if (good_enough2? guess old_guess)
        guess
        (sqrt_iter2 (improve guess x) guess x)
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

(defn -main
    ""
    [& args]
    (println "version" (clojure-version))
    (println (sqrt_iter2 1.0 900.0 900.0))
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
)

(defn find_brackets
    [l s]
    (if (> (count s) 0)
        (concat l [(first s)] (find_brackets l (next s)))
        ""
    )
)

