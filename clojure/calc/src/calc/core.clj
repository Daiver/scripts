(ns calc.core)
(defn -main
    [& args]
    (let [[a b c] args]
        (println 
            (
                (resolve (symbol a)) 
                (read-string b) 
                (read-string c)
            )
        )
    )
)
