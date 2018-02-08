def repeat(s: String, n: Int): String = {
  if (n == 1) s else repeat(s, n-1) + s
}

val s = args(0)
val n = args(1).toInt
println(repeat(s,n))
