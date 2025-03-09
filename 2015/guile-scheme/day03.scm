(add-to-load-path "./2015/guile-scheme/lib/")

(use-modules (srfi srfi-1)
             (srfi srfi-64)
             (utils)
             (ice-9 match))

(define (stepper input-str n-people)
  (define visited (make-hash-table))
  (define cur-pos (list 0 0))
  (hash-set! visited (list-copy cur-pos) 1)
  (string-for-each (lambda (ch)
                     (match ch
                       [#\^ (list-set! cur-pos 1 (+ (second cur-pos) 1))]
                       [#\v (list-set! cur-pos 1 (- (second cur-pos) 1))]
                       [#\< (list-set! cur-pos 0 (- (first cur-pos) 1))]
                       [#\> (list-set! cur-pos 0 (+ (first cur-pos) 1))]
                       [_ 0]
                       )

                     (let ([entry (hash-create-handle! visited (list-copy cur-pos) 0)])
                       (set-cdr! entry (+ (cdr entry) 1))))
                   input-str)
  (hash-count (const #t) visited)
  )


(define (part-one input-str)
  (stepper input-str 1))


(let ([input-str (read-all-lines "./2015/inputs/day03.txt")])
  (display
   (string-append "Part 1: " (number->string (part-one input-str)) "\n"))
  )

(test-begin "day03-tests")

(test-eq "part-one-single"
  2
  (part-one ">"))

(test-eq "part-one-simple-one"
  4
  (part-one "^>v<"))

(test-eq "part-one-simple-two"
  2
  (part-one "^v^v^v^v^v"))

(test-end "day03-tests")
