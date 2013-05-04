(ns rcr.core)

(defn make_tree
    [tokens]
    (loop [i 0 node ()]
        (if (= i (count tokens))
            [node i]
            (let [frst (nth tokens i)]
                (println node)
                (cond
                    (= frst \()
                    (let [[new_node cnt]  (make_tree (drop (inc i) tokens))]
                        (recur 
                            (+ i 1 cnt)
                            (concat node (list new_node))
                        )
                    )
                    (= frst \))
                    [node (inc i)]
                    :default
                        (recur 
                            (+ i 1)
                            (concat node (list frst))
                        )
                )
            )
        )
    )
)

(defn -main
    [& args]
    (println args)
    (println (make_tree "1 23 45 (8 ((qwe r) t) 7) (1) 32 3"))
)
