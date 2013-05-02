(ns hello2.core)

(defn lazy-seq-fibo  ; (1-я строка)
  ([] ; (2-я строка)
     (concat [0 1] (lazy-seq-fibo 0N 1N))) ; (3-я строка)
  ([a b] ; (4-я строка)
     (let [n (+ a b)]                    ; (5-я строка)
       (lazy-seq                         ; (6-я строка)
        (cons n (lazy-seq-fibo b n)))))) ; (7-я строка)

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
    (println (take 500 (lazy-seq-fibo)))
    (println (take 900 (lazy-seq-fibo)))
    ;(println (foo 8))
    ;(println args)

)
