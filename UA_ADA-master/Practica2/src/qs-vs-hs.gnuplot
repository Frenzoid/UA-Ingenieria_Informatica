# Elvi Mihai Sabau Sabau - 51254875L

set terminal png

set xlabel "size of arrays"
set ylabel "millons of program steps"


set title  "Quick Sort"
set output "quickSort.png"
plot "qs-vs-hs.Msteps" using 1:2 with lines title "Random Arrays", \
      "qs-vs-hs.Msteps" using 1:4 with lines title "Sorted Arrays", \
      "qs-vs-hs.Msteps" using 1:6 with lines title "Reverse Sorted Arrays"


set title  "Heapsort"
set output "heapsort.png"
plot "qs-vs-hs.Msteps" using 1:3 with lines title "Random Arrays", \
      "qs-vs-hs.Msteps" using 1:5 with lines title "Sorted Arrays", \
      "qs-vs-hs.Msteps" using 1:7 with lines title "Reverse Sorted arrays"


f1(x)=a1 * x * log(x) + b1 * x + c1
f2(x)=a2 * x * log(x) + b2 * x + c2
set title  "Quicksort versus Heapsort (random arrays)"
set output "qs-vs-hs-RA.png"
fit f1(x) "qs-vs-hs.Msteps" using 1:2 via a1,b1,c1
fit f2(x) "qs-vs-hs.Msteps" using 1:3 via a2,b2,c2
plot "qs-vs-hs.Msteps" using 1:2 with lines title "Quicksort", \
      "qs-vs-hs.Msteps" using 1:3 with lines title "Heapsort", \
      f1(x) with lines title "fitting Quicksort time values to  nlog(n)+n", \
      f2(x) with lines title "fitting Heapsort time values to  nlog(n)+n"

f1(x)=a1 * x * log(x) + b1 * x + c1
f2(x)=a2 * x * log(x) + b2 * x + c2
set title  "Quicksort versus Heapsort (sorted arrays)"
set output "qs-vs-hs-SA.png"
fit f1(x) "qs-vs-hs.Msteps" using 1:4 via a1,b1,c1
fit f2(x) "qs-vs-hs.Msteps" using 1:5 via a2,b2,c2
plot "qs-vs-hs.Msteps" using 1:4 with lines title "Quicksort", \
      "qs-vs-hs.Msteps" using 1:5 with lines title "Heapsort", \
      f1(x) with lines title "fitting Quicksort time values to  nlog(n)+n", \
      f2(x) with lines title "fitting Heapsort time values to  nlog(n)+n"


f1(x)=a1 * x * log(x) + b1 * x + c1
f2(x)=a2 * x * log(x) + b2 * x + c2
set title  "Quicksort versus Heapsort (reverse-sorted arrays)"
set output "qs-vs-hs-RSA.png"
fit f1(x) "qs-vs-hs.Msteps" using 1:6 via a1,b1,c1
fit f2(x) "qs-vs-hs.Msteps" using 1:7 via a2,b2,c2
plot "qs-vs-hs.Msteps" using 1:6 with lines title "Quicksort", \
      "qs-vs-hs.Msteps" using 1:7 with lines title "Heapsort", \
      f1(x) with lines title "fitting Quicksort time values to  nlog(n)+n", \
      f2(x) with lines title "fitting Heapsort time values to  nlog(n)+n"

