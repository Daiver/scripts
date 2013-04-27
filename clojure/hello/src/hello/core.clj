(ns hello.core)

(defn find_brackets
    [l s]
    (if (> (count s) 0)
        (concat l [(first s)] (find_brackets l (next s)))
        ""
    )
)


(defn -main
    ""
    [& args]
    (println "version" (clojure-version))
    (def arg (first args))
    (println 
        (find_brackets [] (first args))
    )
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

