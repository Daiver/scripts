(ns classifier.core)
(use '[clojure.string :only (split triml lower-case)])
(use 'clojure.java.io)

(defn values [d] (map #(d %) (keys d)))

(defn read_data_from_file [fname]
    (let [lines (with-open [rdr (reader fname)] 
                (doall (line-seq rdr)))]
        (map #(-> % lower-case (split #"\s")) lines)))

(defn do-to-map 
    ([m keyseq f] (reduce #(assoc %1 %2 (f %2 (%1 %2))) m keyseq))
    ([m f] (do-to-map m (keys m) f)))

(defn process_words [key x]
    (->> x 
        (map #(rest %)) 
        (apply concat)
        frequencies))

(defn dicts_from_data [raw_data]
    (let [data (group-by #(first %) raw_data)]
        (do-to-map data
            process_words)))

(defn classes_freq_from_data [raw_data]
    (-> (group-by first raw_data) 
        (do-to-map #(-> %2 count float)) (do-to-map #(/ %2 (count raw_data)))))

(defn feat_freq_from_data [raw_data dct]
    (let
        [cls_count (-> (group-by first raw_data) (do-to-map #(-> %2 count float)))]
        (do-to-map dct 
            (fn [key value] (do-to-map value #(/ %2 (cls_count key)))))))

(defn activate [classes_freq feat_freq feats]
    (apply min-key 
        (fn [cls]
            (+ (- (Math/log (classes_freq cls)))
                (apply + 
                    (map 
                        #(- (Math/log 
                            (if (nil? (-> feat_freq (get cls) (get %))) 0.0000001 (-> feat_freq (get cls) (get %)))))
                        feats))))
        (keys classes_freq)))

(defn tst [classes_freq feat_freq raw_data]
    (map 
        (fn [smpl]
            (.equals (first smpl) (activate classes_freq feat_freq (rest smpl))))
        raw_data))

(defn -main
    ""
    [& args]
    (println args)
    (def raw_data (read_data_from_file (first args)))
    (def feat_freq_dict (dicts_from_data raw_data))
    (def classes (keys feat_freq_dict))
    (def classes_freq (classes_freq_from_data raw_data))
    (def feat_freq (feat_freq_from_data raw_data feat_freq_dict))
    ;(def sample (rest (first raw_data)))
    (println (group-by true? (tst classes_freq feat_freq raw_data)))
    ;(println sample)
    ;(println (activate classes_freq feat_freq sample))
    ;(println classes_freq feat_freq)
    (println "end")
)
