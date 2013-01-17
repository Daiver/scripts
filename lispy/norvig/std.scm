(define (newline) (display "\n"))
(define (exit) (pyeval "exit()"))
(define (print x) (display (+ (tostr x) "\n")))
