(ns rcr.core)

(defn parse-num [s]
    (try (Integer/parseInt s)
        (catch NumberFormatException nfe 
            (try (Float/parseFloat s) 
                (catch NumberFormatException nfe s)))))

(defn process-numeric-tokens [tokens]
    (map #(parse-num %) tokens))

(defn make_tokens
    [s]
    (clojure.string/split (clojure.string/replace (clojure.string/replace s #"\(" " ( ") #"\)" " ) ") #"\s"))

(defn execute
    [arg]
    (println arg)
    (println (type arg) )
    (if 
        ;(= (type arg) (type '( "" ) ))
        (= (type arg) clojure.lang.LazySeq)
        (apply (resolve (symbol (first arg))) (map execute (rest arg))) 
        arg))

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
    ;(println (make_tokens "1 23(456) 45"))
    ;(println (make_tree (make_tokens "1 23 45 (8 ((qwe r) t (123 (no hope) (no changes) )) 7) (1) 32 3")))
    (def s "+ (* 20 3) 5")
    (let [[tree count] (make_tree (process-numeric-tokens (make_tokens s)))]
        (println tree)
        (println (execute tree))
    )
    ;(println (execute '("+" 1  ("*" 3 5))))
)
