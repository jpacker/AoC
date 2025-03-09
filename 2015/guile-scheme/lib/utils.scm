(define-module (utils))

(use-modules
 (ice-9 textual-ports)
 (ice-9 match)
 (srfi srfi-64))

(define-public read-all-lines
  (lambda* (file #:key (encoding "utf-8"))
    (call-with-input-file file
      (lambda (port)
        (get-string-all port))
      #:encoding encoding)))

(define-public (make-n-copies lst n)
  (let loop ([remaining-n (- n 1)] [acc lst])
    (match remaining-n
      [0 acc]
      [k (loop (- k 1) (append acc lst))])))

(test-begin "utils")

(test-equal "n-copies 3"
  '(1 2 3 1 2 3 1 2 3)
  (make-n-copies '(1 2 3) 3))

(test-end "utils")
