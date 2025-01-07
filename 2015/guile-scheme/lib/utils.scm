(define-module (utils))

(use-modules
 (ice-9 textual-ports))

(define-public read-all-lines
  (lambda* (file #:key (encoding "utf-8"))
    (call-with-input-file file
      (lambda (port)
        (get-string-all port))
      #:encoding encoding)))
