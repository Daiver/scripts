(ns rcr.core)

(defn make_tokens
    [s]
    (clojure.string/split (clojure.string/replace (clojure.string/replace s #"\(" " ( ") #"\)" " ) ") #"\s"))

(defn make_tree
    [tokens]
    (loop [i 0 node ()]
        (if (= i (count tokens))
            [node i]
            (let [frst (nth tokens i)]
                ;(println node)
                (cond
                    (= frst \()
                    (let [[new_node cnt]  (make_tree (drop (inc i) tokens))]
                        (recur 
                            (+ i 1 cnt)
                            (concat node (list new_node))))
                    (= frst \))
                    [node (inc i)]
                    :default
                        (recur 
                            (+ i 1)
                            (concat node (list frst))))))))

(defn -main
    [& args]
    (println (make_tokens "1 23(456) 45"))
    (println (make_tree (make_tokens "1 23 45 (8 ((qwe r) t (123 (no hope) (no changes) )) 7) (1) 32 3")))
)
