def sqrtStep(c: Double, x0: Double): Double = {
  /*val fx = x0 * x0 - c
  val fxp = 2 * x0
  x0-fx/fxp
  */

  x0-(x0*x0-c)/(2*x0)
}

def sqrtN(c: Double, x0: Double, n: Int): Double = {
  require (c >= 0)
  if (n == 1) sqrtStep(c,x0) else {
    val x = sqrtN(c,x0,n-1)
    sqrtStep(c,x)
  }
}

def sqrtNwhile(c: Double, x0: Double, n: Int): Double = {
  var x = x0
  var i = 0
  while(i < n) {
    x = x-(x*x-c)/(2*x)
    i += 1
  }
  x
}

def sqrtErr(c: Double, x0: Double, epsilon: Double): Double = {
  val x1 = sqrtStep(c,x0)
  if(abs(x1*x1-c) > epsilon) sqrtErr(c,x1,epsilon) else x1
}

def sqrtErrWhile(c: Double, x0: Double, epsilon: Double): Double = {
  var xcurr = x0
  var xprev = 0.0
  while (abs(xcurr*xcurr-c) > epsilon) {
    xprev = xcurr
    xcurr = sqrtStep(c, xcurr)
  }
  xcurr
}

def abs(x: Double): Double = {
  if (x >= 0) x else x-2*x
}

val c = args(0).toDouble
val x0 = args(1).toDouble
val n = args(2).toInt
val e = args(3).toDouble

//println("sqrtStep:\t" + sqrtStep(c, x0))
//println("sqrtNwhile:\t" + sqrtNwhile(c,x0,n))
//println("sqrtN:\t\t" + sqrtN(c,x0,n))
println("sqrtErrWhile:\t" + sqrtErrWhile(c,x0,e))
println("sqrtErr:\t" + sqrtErr(c,x0,e))
