(ns classifier.core)
(use '[clojure.string :only (split triml lower-case)])
(use 'clojure.java.io)

(defn read_data_from_file [fname]
    (map #(split % #"\s") (with-open [rdr (reader fname)] 
        (doall (line-seq rdr)))))

(defn do-to-map [amap keyseq f]
    (reduce #(assoc %1 %2 (f (%1 %2))) amap keyseq))

(defn dicts_from_data [raw_data]
    (let [data (group-by #(first %) raw_data)]
        (do-to-map
            data (keys data) 
                (fn [x] (map #(rest %) x)))))
        

(defn -main
    ""
    [& args]
    (println args)
    (def raw_data (read_data_from_file (first args)))

    (println (dicts_from_data raw_data))
)
