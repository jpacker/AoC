(add-to-load-path "./2015/guile-scheme/lib/")

(use-modules (srfi srfi-1)
             (srfi srfi-64)
             (utils)
             (ice-9 match))

(define (helper lines fn)
  (fold (lambda (line acc)
          (let ([nums (map string->number (string-split line #\x))])
            (+ acc
               (match nums
                 ((l w h) (fn l w h))
                 (_ 0)))))
        0
        lines))

(define (part-one lines)
  (helper lines
          (lambda (l w h)
            (let* ([one (* l w)]
                   [two (* w h)]
                   [three (* l h)]
                   [extra (min one two three)])
              (+ (* 2 one) (* 2 two) (* 2 three) extra)))))

(define (part-two lines)
  (helper lines
          (lambda (l w h)
            (let* ([szs (sort (list l w h) <)]
                   [shortest (first szs)]
                   [next-shortest (second szs)])
              (+ (+ shortest shortest) (+ next-shortest next-shortest) (* l w h))))))

(let* ([input-str (read-all-lines "./2015/inputs/day02.txt")]
       [lines (string-split input-str char-set:whitespace)])
  (display
   (string-append "Part 1: " (number->string (part-one lines)) "\n"))
  (display
   (string-append "Part 2: " (number->string (part-two lines)) "\n\n")))

(test-begin "day02-test")

(test-eq "part-one-first"
  58
  (part-one '("2x3x4")))

(test-eq "part-one-first-twice"
  (* 2 58)
  (part-one '("2x3x4" "2x3x4")))

(test-eq "part-two-first"
  34
  (part-two '("2x3x4")))

(test-eq "part-two-other"
  14
  (part-two '("1x1x10")))


(test-end "day02-test")
