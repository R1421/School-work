def xor(a: Boolean, b: Boolean): Boolean = {
  if (a == b) false else true
}

val a: Boolean = true
val b: Boolean = false
println("True False:  " + xor(a,b))
println("False True:  " + xor(b,a))
println("True True:   " + xor(a,a))
println("False False: " + xor(b,b))
