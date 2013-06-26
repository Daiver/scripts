(ns classifier.core)
(use '[clojure.string :only (split triml lower-case)])
(use 'clojure.java.io)

(defn read_data_from_file [fname]
    (map #(split % #"\s") (with-open [rdr (reader fname)] 
        (doall (line-seq rdr)))))

(defn -main
    ""
    [& args]
    (println args)
    (def raw_data (read_data_from_file (first args)))

    (println (first raw_data))
)
