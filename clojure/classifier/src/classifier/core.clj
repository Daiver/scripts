(ns classifier.core)
(use '[clojure.string :only (split triml)])
(use 'clojure.java.io)

(defn -main
    ""
    [& args]
    (println args)
    (def raw_data 
        (with-open [rdr (reader (first args))] 
            (doall (line-seq rdr))))

    (println raw_data)
)
