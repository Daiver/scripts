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
                (sum (next a) b term next))))
    ([seq]
        (if (= (count seq) 0)
            0
            (+ (first seq) (sum (next seq))))))

(defn product
    [ a b f next]
    (loop [i a res 1]
        (if (> i b)
            res
            (recur (next i) (* (f i) res)))))

(defn deriv
    [g dx]
    #(/ (- (g (+ dx %)) (g %)) dx))

(defn gcd 
    [a b]
    (if (= b 0)
        a
        (gcd b (mod a b))))

(defrecord Tree [value left right])

(defn depth_walk_tree [tree functor]
    (concat
        (list (functor (:value tree)))
        (if (:left tree) (depth_walk_tree (:left tree) functor))
        (if (:right tree) (depth_walk_tree (:right tree) functor))))

(defn count_tree
    [tree]
    (+
        1
        (if-not (:left tree) 0 (count_tree (:left tree)))
        (if-not (:right tree) 0 (count_tree (:right tree)))))

(defn acc_n [op init seq]
    (if (empty? (first seq))
        nil
        (let [splice (fn [splitf seq](reverse (reduce #(cons (splitf %2) %1) (list) seq)))]
            (cons 
                (reduce op init (splice first seq))
                (acc_n op init (splice rest seq))))))

(defn dot_scalar [m1 m2]
    (reduce + (map * m1 m2)))

(defn dot_mat_vec [m v]
    (map #(dot_scalar v %) m))

(defn transpose [m]
    (map reverse (acc_n #(cons %2 %1) (list) m)))

(defn dot_mat_mat [m1 m2]
    (let [cols (transpose m2)]
        (map #(dot_mat_vec cols %) m1)))

(defn -main
    ""
    [& args]
    (println "version" (clojure-version))
    (println (dot_scalar [1 2 3] [4 5 6]))
    (println (dot_mat_vec [[1 2 3] [5 6 7] [10 10 10]] [4 5 6]))
    (println (acc_n + 0 [[1 2 3] [3 4 5]]))
    (def m1 [[1 2 3] [4 5 6] [7 8 9]])
    (def m2 [[1 2 3] [4 5 6] [7 8 9]])
    (println (transpose m1))
    (println (dot_mat_mat m1 m2))
    ;(println (square_sum (list (list 1 2) (list 3 (list 5 7)))))
    ;(println (my_map #(+ % 1) [5 1 2 3]))
    ;(println (append [1 2 3 4 5] [6 7 8]))
    ;(println (my_own_length [5 2 3 4 42232 232]))
    ;(println (horner 2 [1 3 0 5 0 1]))
    ;(println (subset (list 1 2 3)))
    ;(def tree (Tree. 1 (Tree. 2 (Tree. 0 nil nil) (Tree. 90 nil nil)) (Tree. 3 nil (Tree. 10 nil nil)) ))
    ;(println (depth_walk_tree tree #(+ % 1) ))
    ;(println (count_tree tree))
    ;(println (depth_walk_tree tree #(ident %)))
    ;(println (reverse_list [1 2 3 4 5 6]))
    ;(def x (make_interval 5 10))
    ;(def y (make_interval 5 8))
    ;(println x y (add_int x y) (mul_int x y) (div_int x y) (sub_int x y))
    ;(def x (make_rat 15 30))
    ;(println x (denom x) (numer x))
    ;(println ((deriv #(square %) 0.0001) 10))
    ;(time (println (zero_search #(+ 5 %1) -10 10 )))
    ;(time (println (pi_num 160)))
)

(comment
    (defn make_rat
        [n d]
        (let [g (gcd n d)]
            (cons (/ n g) [(/ d g)])))

    (defn numer
        [rat]
        (first rat))

    (defn denom
        [rat]
        (second rat))

     (defn zero_search
        [f left right]
        (let [mid (average left right)]
            (if (good_enough? left right 0.001)
                mid
                (let [f_value (f mid)]
                    (cond
                        (pos? f_value) (zero_search f left mid)
                        (neg? f_value) (zero_search f mid right)
                        (zero? f_value) mid)))))

    ;(println (fact 20))
    ;(println (product 1 5 #(ident %) #(inc %)))
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
(comment
    (defn make_interval
        [lo hi]
        (cons lo [hi]))

    (def lo_int first)
    (def hi_int second)

    (defn add_int [a b] (make_interval (+ (lo_int a) (lo_int b)) (+ (hi_int a) (hi_int b))))
    (defn mul_int [a b] (make_interval (* (lo_int a) (lo_int b)) (* (hi_int a) (hi_int b))))
    (defn div_int [a b] (mul_int a (make_interval (/ 1.0 (lo_int b)) (/ 1.0 (hi_int b)))))
    (defn sub_int [a b] (add_int a (make_interval (- (lo_int b)) (- (hi_int b)))))

    (defn ifl 
        [n lst]
        (loop [innerlist lst i 0]
            (if (= i n)
                (first innerlist)
                (recur (rest innerlist) (inc i)))))

    (defn reverse_list 
        [lst]
        (loop [innerlist lst newlst (list)]
            ;(println innerlist newlst)
            (if (= 0 (count innerlist))
                newlst
                (recur (rest innerlist) (cons (first innerlist) newlst))      
            )
        )
     (defrecord Mobile [left right])
    (defrecord Branch [length structure])

    (defn total_weight
        [mobile]
        (if (= (type 1) (type mobile))
            mobile
            (+
                (total_weight (:structure (:left mobile)))
                (total_weight (:structure (:right mobile))))))

    (defn is_balanced?
        [mobile]
        (if (= (type 1) (type mobile))
            true
            (and
                (is_balanced? (:structure (:left mobile)))
                (is_balanced? (:structure (:right mobile)))
                (=
                    (* 
                        (total_weight (:structure (:left mobile)))
                        (:length (:left mobile))
                    )
                    (* 
                        (total_weight (:structure (:right mobile)))
                        (:length (:right mobile)))))))

    (defn enumerate_tree_list
        [tree]
        (cond (nil? tree) nil
            (not (= (type tree) (type (list 1)))) (list tree)
            (= (count tree) 2) 
                (concat 
                    (enumerate_tree_list (first tree)) (enumerate_tree_list (second tree)))))

    (defn square_sum [set] (reduce + (map square (filter odd? (enumerate_tree_list set) ))))
    (defn my_map [p set] (reduce #(concat %1 (list (p %2))) nil set))
    (defn append [seq1 seq2] (reduce #(cons %2 %1) seq2 (reverse seq1)))
    (defn my_own_length [set] (reduce (fn [x y] (+ 1 x)) 0 set))
    (defn horner [x coeff_seq] (reduce #(+ %1 (* x %2)) 0 coeff_seq))
       )
)
