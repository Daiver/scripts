(ns hello.core)
(defn -main
    "I don't do a whole lot."
    [& args]
    (clojure-version)
    (println (count args))
    (println (args 1))
    (println 
        (filter #(> % 10)
            (map
                #(* % 10)
                (map read-string args)
            )
        )
    )
    ;(println
    ;    (map
    ;        #(int %1)
    ;        (map 
    ;            #(+ %1 %2 ) '(1 2 3 4) '(2 2 2 2)
    ;        )
    ;    )
    ;)
)

