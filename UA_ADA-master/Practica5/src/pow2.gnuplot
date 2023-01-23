# Elvi Mihai Sabau Sabau - 51254875L

set terminal png
set output "pow2.png"

set xlabel "n"
set ylabel "Amount of recursive calls"

set title "Time complexity of different implementations the Pow(2,n) function."
plot "pow2.log" using 1:2 with lines title "T(n) = 2 T(n-1)", \
	 "pow2.log" using 1:3 with lines title "T(n) = T(n/2) * T(n/2)",\
	 "pow2.log" using 1:4 with lines title "T(n) = T(n/2)^2"