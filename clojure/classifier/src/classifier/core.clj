(ns classifier.core)
(use '[clojure.string :only (split triml lower-case)])
(use 'clojure.java.io)

(defn values [d] (map #(d %) (keys d)))

(defn read_data_from_file [fname]
    (let [lines (with-open [rdr (reader fname)] 
                (doall (line-seq rdr)))]
        (map #(-> % lower-case (split #"\s")) lines)))

(defn do-to-map 
    ([m keyseq f] (reduce #(assoc %1 %2 (f (%1 %2))) m keyseq))
    ([m f] (do-to-map m (keys m) f)))

(defn process_words [x]
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
        (do-to-map #(-> % count float)) (do-to-map #(/ % (count raw_data)))))

(defn -main
    ""
    [& args]
    (println args)
    (def raw_data (read_data_from_file (first args)))
    (def feat_freq (dicts_from_data raw_data))
    (def classes (keys feat_freq))
    (println "classes" classes)
    (println (classes_freq_from_data raw_data))
    (println "end")
)
