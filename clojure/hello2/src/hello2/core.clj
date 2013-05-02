(ns hello2.core)

(defn foo
    [arg]
    (cond
        (== arg 1) "A"
        (== arg 2) "B"
        (== arg 3) "C"
        :else "NOPE"
    )
)

(defn -main
    [& args]
    (println (foo 8))
    ;(println args)

)
