def abs(n: Double): Double = {
  if (n >= 0) n else n - 2*n
}

val n = args(0).toDouble
println(abs(n))
