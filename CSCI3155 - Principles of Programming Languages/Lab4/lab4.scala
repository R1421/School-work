package jsy.student

import jsy.lab4.Lab4Like

object Lab4 extends jsy.util.JsyApplication with Lab4Like {
  import jsy.lab4.ast._
  import jsy.lab4.Parser
  
  /*
   * CSCI 3155: Lab 4
   * Derek Gorthy, Raymond Duncan
   * 
   * Collaborators: <Any Collaborators>
   */

  /*
   * Fill in the appropriate portions above by replacing things delimited
   * by '<'... '>'.
   * 
   * Replace the '???' expression with your code in each function.
   *
   * Do not make other modifications to this template, such as
   * - adding "extends App" or "extends Application" to your Lab object,
   * - adding a "main" method, and
   * - leaving any failing asserts.
   *
   * Your lab will not be graded if it does not compile.
   *
   * This template compiles without error. Before you submit comment out any
   * code that does not compile or causes a failing assert. Simply put in a
   * '???' as needed to get something that compiles without error. The '???'
   * is a Scala expression that throws the exception scala.NotImplementedError.
   */
  
  /* Collections and Higher-Order Functions */
  
  /* Lists */


  // Fails in the case that we have an unsorted list
  def compressRec[A](l: List[A]): List[A] = l match {
    case h1 @ (Nil | _ :: Nil) => h1
    case h1 :: (t1 @ (h2 :: _)) => if(h1 == h2) compressRec(t1) else { h1 :: compressRec(t1)}
  }

  // Same error as above
  def compressFold[A](l: List[A]): List[A] = l.foldRight(Nil: List[A]){
    (h, acc) => acc match {
      case ht @ (h2 :: _) if (h == h2) => acc
      case _ => h :: acc
    }
  }

  // Seems to work
  def mapFirst[A](l: List[A])(f: A => Option[A]): List[A] = l match {
    case Nil => Nil
    case h :: t => f(h) match {
      case None => h :: mapFirst(t)(f)
      case Some(i) => i :: t
    }
  }
  
  /* Trees */

  def foldLeft[A](t: Tree)(z: A)(f: (A, Int) => A): A = {
    def loop(acc: A, t: Tree): A = t match {
      case Empty => acc
      case Node(l, d, r) => /*f(foldLeft(l)(z)(f),d)*/ loop(f(loop(acc,l),d),r)
    }
    loop(z, t)
  }

  // An example use of foldLeft
  def sum(t: Tree): Int = foldLeft(t)(0){ (acc, d) => acc + d }

  // Create a tree from a list. An example use of the
  // List.foldLeft method.
  def treeFromList(l: List[Int]): Tree =
    l.foldLeft(Empty: Tree){ (acc, i) => acc insert i }

  def strictlyOrdered(t: Tree): Boolean = {
    val (b, _) = foldLeft(t)((true, None: Option[Int])){
      (acc,h) => acc match {
        case (false,_) => (false,None)
        case (_,None) => (true,Some(h))
        case (_,Some(p)) => if(p < h) (true,Some(h)) else (false,Some(h))
      }
    }
    b
  }

  /* Type Inference */

  // While this helper function is completely given, this function is
  // worth studying to see how library methods are used.
  def hasFunctionTyp(t: Typ): Boolean = t match {
    case TFunction(_, _) => true
    case TObj(fields) if (fields exists { case (_, t) => hasFunctionTyp(t) }) => true
    case _ => false
  }

  def typeof(env: TEnv, e: Expr): Typ = {
    def err[T](tgot: Typ, e1: Expr): T = throw StaticTypeError(tgot, e1, e)

    e match {
      case N(_) => TNumber
      case B(_) => TBool
      case Undefined => TUndefined
      case S(_) => TString
      case Var(x) => lookup(env,x)
      case Unary(Neg, e1) => typeof(env, e1) match {
        case TNumber => TNumber
        case tgot => err(tgot, e1)
      }
      case Unary(Not, e1) => typeof(env, e1) match {
        case TBool => TBool
        case tgot => err(tgot, e1)
      }
      case Binary(Seq, e1, e2) => typeof(env, e1); typeof(env, e2)
      case Binary(Plus, e1, e2) => (typeof(env, e1), typeof(env, e2)) match {
        case (TNumber, TNumber) => TNumber
        case (TString, TString) => TString
        case (tgot1, tgot2) => err(tgot1, e1)
      }
      case Binary(Minus | Times | Div, e1, e2) => (typeof(env, e1), typeof(env, e2)) match {
        case (TNumber, TNumber) => TNumber
        case (tgot1, tgot2) => err(tgot1, e1)
      }
      case Binary(Lt | Le | Gt | Ge, e1, e2) => (typeof(env, e1), typeof(env, e2)) match {
        case (TNumber, TNumber) => TBool
        case (TString, TString) => TBool
        case (tgot1, tgot2) => err(tgot1, e1)
      }
      case Binary(Eq | Ne, e1, e2) => {
        val t1 = typeof(env, e1)
        val t2 = typeof(env, e2)
        if (t1 == t2 && !hasFunctionTyp(t1)) TBool else err(t1, e1)
      }
      case Binary(And | Or, e1, e2) => (typeof(env, e1), typeof(env, e2)) match {
        case (TBool, TBool) => TBool
        case (tgot1, tgot2) => err(tgot1, e1)
      }
      case Print(e1) => typeof(env, e1); TUndefined
      case If(e1, e2, e3) => (typeof(env, e1), typeof(env, e2), typeof(env, e3)) match {
        case (TBool, t2, t3) => if (t2 == t3) t2 else err(t2, e3)
        case (tgot, _, _) => err(tgot, e1)
      }
      // Check
      case Decl(mode, x, e1, e2) => typeof(extend(env, x, typeof(env, e1)), e2)

      // CHECK
      case Call(e1, args) => typeof(env, e1) match {
        case TFunction(params, tret) if (params.length == args.length) =>
          (params zip args).foreach {
            case ((name, MTyp(_, typ)), ex) => if(typ != typeof(env, ex)) err(typ, ex)
          };
          tret
        case tgot => err(tgot, e1)
      }
      case Obj(fields) => TObj(fields.mapValues((exp: Expr) => typeof(env, exp)))
      case Function(p, params, tann, e1) => {
        // Bind to env1 an environment that extends env with an appropriate binding if
        // the function is potentially recursive.
        val env1 = (p, tann) match {
          /** *** Add cases here *****/
          case (Some(x),Some(t)) => extend(env, x, /*TFunction(params, t)*/t)
          case (None, _) => env
          case _ => err(TUndefined, e1)
        }
        // Bind to env2 an environment that extends env1 with bindings for params.
        val env2 = params.foldLeft(env1){ case (envacc, (xi,MTyp(_,ti))) => extend(envacc,xi,ti) }
        // Infer the type of the function body
        val t1 = typeof(env2, e1)
        // Check with the possibly annotated return type
        tann match {
          case Some(tcheck) => if (t1 == tcheck) () else err(t1, e1)
          case None => ()
        }

        TFunction(params,t1)
      }

      case GetField(e, f) => typeof(env, e) match {
        case TObj(tf) => tf.get(f) match {
          case Some(x) => x
          case None => err(typeof(env, e), e) // TUndefined instead of typeof
        }
        case _ => err(typeof(env, e), e)
      }
    }
  }
  
  /* Small-Step Interpreter */

  /*
   * Helper function that implements the semantics of inequality
   * operators Lt, Le, Gt, and Ge on values.
   *
   * We suggest a refactoring of code from Lab 2 to be able to
   * use this helper function in eval and step.
   *
   * This should the same code as from Lab 3.
   */
  def inequalityVal(bop: Bop, v1: Expr, v2: Expr): Boolean = {
    require(isValue(v1))
    require(isValue(v2))
    require(bop == Lt || bop == Le || bop == Gt || bop == Ge)
    (v1, v2) match {
      case (S(s1), S(s2)) => bop match {
        case Lt => s1 < s2
        case Le => s1 <= s2
        case Gt => s1 > s2
        case Ge => s1 >= s2
        case _ => throw new UnsupportedOperationException
      }
      case (N(n1), N(n2)) => bop match {
        case Lt => n1 < n2
        case Le => n1 <= n2
        case Gt => n1 > n2
        case Ge => n1 >= n2
        case _ => throw new UnsupportedOperationException
      }
      case _ => throw new UnsupportedOperationException
    }

  }

  /* This should be the same code as from Lab 3 */
  def iterate(e0: Expr)(next: (Expr, Int) => Option[Expr]): Expr = {
    def loop(e: Expr, n: Int): Expr = next(e,n) match {
      case None => e
      case Some(ep) => loop(ep,n+1)
    }
    loop(e0, 0)
  }

  /* Capture-avoiding substitution in e replacing variables x with esub. */
  def substitute(e: Expr, esub: Expr, x: String): Expr = {
    def subst(e: Expr): Expr = e match {
      case N(_) | B(_) | Undefined | S(_) => e
      case Print(e1) => Print(substitute(e1, esub, x))

      /** *** Cases from Lab 3 */
      case Unary(uop, e1) => Unary(uop, substitute(e1, esub, x))
      case Binary(bop, e1, e2) => Binary(bop, substitute(e1, esub, x), substitute(e2, esub, x))
      case If(e1, e2, e3) => If(substitute(e1, esub, x), substitute(e2, esub, x), substitute(e3, esub, x))
      case Var(y) => if (y == x) esub else Var(y)
      case Decl(mode, y, e1, e2) => if (y == x) Decl(mode, y, substitute(e1, esub, x), e2) else Decl(mode, y, substitute(e1, esub, x), substitute(e2, esub, x))

      /** *** Cases needing adapting from Lab 3 */
        // Check, needs improvement
      case Function(p, params, tann, e1) => {
        val e1p = params.foldLeft(e1) {
          (acc, h) => h match {
            case (xi, MTyp(m, t)) => if(x == xi) substitute(e1, esub, xi) else acc
          }
        }
        val e1pp  = p match {
          case Some(x1) => if(x == x1) substitute(e1p,esub,x1) else e1p
          case None => e1p
        }
        Function(p, params, tann, e1pp)
      }
        // Check
      case Call(e1, args) => Call(subst(e1), args.map(subst)) //Add in zip
      /***** New cases for Lab 4 */
      case Obj(fields) => Obj(fields.mapValues(v => subst(v)))
      case GetField(e1, f) => {
        if (x != f) {
          GetField(subst(e1), f)
        } else {
          e
        }
      }
    }

    val fvs = freeVars(esub)
    def fresh(x: String): String = if (fvs(x)) fresh(x + "$") else x
    subst(rename(e)(fresh))
  }

  /* Rename bound variables in e */
  def rename(e: Expr)(renameVar: String => String): Expr = {
    def ren(env: Map[String,String], e: Expr): Expr = {
      e match {
        case N(_) | B(_) | Undefined | S(_) => e
        case Print(e1) => Print(ren(env, e1))

        case Unary(uop, e1) => Unary(uop, ren(env, e1))
        case Binary(bop, e1, e2) => Binary(bop, ren(env, e1), ren(env, e2))
        case If(e1, e2, e3) => ???

        case Var(y) =>
          ???
        case Decl(mode, y, e1, e2) =>
          val yp = renameVar(y)
          ???

        case Function(p, params, pretty, e1) => {
          val (pp, envp): (Option[String], Map[String,String]) = p match {
            case None => ???
            case Some(x) => ???
          }
          val (paramsp, envpp) = params.foldRight( (Nil: List[(String,MTyp)], envp) ) {
            ???
          }
          ???
        }

        case Call(e1, args) => ???

        case Obj(fields) => ???
        case GetField(e1, f) => ???
      }
    }
    ren(Map.empty, e)
  }

  /* Check whether or not an expression is reduced enough to be applied given a mode. */
  def isRedex(mode: Mode, e: Expr): Boolean = mode match {
    case Const => if (isValue(e)) false else true
    case Name => false // All named expressions are not reduceable
  }

  /*def step(e: Expr): Expr = {
    require(!isValue(e), s"step: e ${e} to step is a value")
    e match {
      /* Base Cases: Do Rules */
      case Print(v1) if isValue(v1) => println(pretty(v1)); Undefined
        /***** Cases needing adapting from Lab 3. */
      case Unary(Neg, N(n1)) => N(-n1)
      case Unary(Not,B(b1)) => B(!b1)
      case Binary(Seq, v1, e2) if isValue(v1) => e2
      case Binary(bop @(Plus|Minus|Times|Div),N(n1),N(n2)) => bop match {
        case Plus => N(n1+n2)
        case Minus => N(n1-n2)
        case Times => N(n1*n2)
        case Div => N(n1/n2)
      }
      case Binary(Plus,S(s1),S(s2)) => S(s1+s2)
      case Binary(bop @(Lt|Le|Gt|Ge),N(n1),N(n2)) => bop match {
        case Lt => B(n1 < n2)
        case Le => B(n1 <= n2)
        case Gt => B(n1 > n2)
        case Ge => B(n1 >= n2)
      }
      case Binary(bop @(Lt|Le|Gt|Ge),S(s1),S(s2)) => bop match {
        case Lt => B(s1 < s2)
        case Le => B(s1 <= s2)
        case Gt => B(s1 > s2)
        case Ge => B(s1 >= s2)
      }
      case Binary(bop @(Eq|Ne),v1,v2) if (isValue(v1) && isValue(v2)) => bop match {
        case Eq => B(v1 == v2)
        case Ne => B(v1 != v2)
      }
      case Binary(And,B(true),e2) => e2
      case Binary(And,B(false),e2) => B(false)
      case Binary(Or,B(true),e2) => B(true)
      case Binary(Or,B(false),e2) => e2
      case If(B(true),e2,e3) => e2
      case If(B(false),e2,e3) => e3
      case Decl(mode,x,e1,e2) if(!isRedex(mode,e1)) => substitute(e2,e1,x)
        /***** More cases here */
      case Call(v1, args) if isValue(v1) =>
        v1 match {
          case Function(p, params, _, e1) => {
            val pazip: List[((String, MTyp), Expr)] = params zip args
            // Do Call, Do Call Rec
            /*if (pazip.forall({case ((p,(m,t),e1)) => !isRedex(m,e1)})) {
              val e1p = pazip.foldRight(e1) {
                (acc,h) => acc match {
                  case (h2 :: _) => ???
                }
              }
              p match {
                case None => ???
                case Some(x1) => ???
              }
            }
              // Search Call 2
            else {
              val pazipp = mapFirst(pazip) {
                ???
              }
              ???
            }*/
          ???
          }
          case _ => throw StuckError(e)
        }
      case GetField(v1,f) if (isValue(v1)) => v1 match {
        case Obj(fields) => fields.get(f) match {
          case Some(v) => v
          case None => Undefined
        }
      }
      /* Inductive Cases: Search Rules */
      case Print(e1) => Print(step(e1))


        /***** SEARCH RULES *******/

      case Unary(uop, e1) => Unary(uop,step(e1))
      case Binary(bop, v1, e2) if(isValue(v1)) => Binary(bop,v1,step(e2))
      case Binary(bop, e1, e2) => Binary(bop, step(e1),e2)
      case If(e1,e2,e3) => If(step(e1),e2,e3)
      case Decl(mode,x,e1,e2) if(isRedex(mode,e1)) => Decl(mode,x,step(e1),e2)
      case Obj(fields) => Obj(fields.mapValues((e) => step(e)))
      case GetField(e1,f) => GetField(step(e1),f)
        /***** New cases for Lab 4. */

      /* Everything else is a stuck error. Should not happen if e is well-typed.
       *
       * Tip: you might want to first develop by comment out the following line to see which
       * cases you have missing. You then uncomment this line when you are sure all the cases
       * that you have left the ones that should be stuck.
       */
      case _ => throw StuckError(e)
    }
  }*/
  def step(e: Expr): Expr = {
    require(!isValue(e), s"step: e ${e} to step is a value")
    e match {
      /* Base Cases: Do Rules */
      /***** Cases needing adapting from Lab 3. */
      case Unary(Neg, N(n)) => N(-n)
      case Unary(Not, B(b)) => B(!b)
      case Binary(Seq, v1, e2) if isValue(v1) => e2
      case Binary(Plus, v1, v2) if isValue(v1) && isValue(v2) => (v1, v2) match {
        case (N(n1), N(n2)) => N(n1 + n2)
        case (S(s1), S(s2)) => S(s1 + s2)
        case _ => throw new UnsupportedOperationException
      }
      case Binary(Minus, N(n1), N(n2)) => N(n1 - n2)
      case Binary(Times, N(n1), N(n2)) => N(n1 * n2)
      case Binary(Div, N(n1), N(n2)) => N(n1 / n2)
      case Binary(bop @(Lt|Le|Gt|Ge), v1, v2) if isValue(v1) && isValue(v2) && v1 == v2 => B(inequalityVal(bop,v1,v2))
      case Binary(bop @(Eq|Ne), v1, v2) if isValue(v1) && isValue(v2) => if(bop == Eq) B(v1 == v2) else B(v1 != v2)
      case Binary(And, B(b), e2) => if(b) e2 else B(false)
      case Binary(Or, B(b), e2) => if(b) B(true) else e2
      /***** More cases here */
      case Print(v1) if isValue(v1) => println(pretty(v1)); Undefined
      case If(B(b),e2,e3) => if(b) e2 else e3
      case Decl(mode,x,e1,e2) if !isRedex(mode,e1) => substitute(e2,e1,x)
      case Call(v1, args) if isValue(v1) =>
        v1 match {
          case Function(p, params, _, e1) => {
            val pazip = params zip args
            //DoCall and DoCallRec
            if (pazip.forall{ case ((s,MTyp(m,t)),exp) => !isRedex(m,exp) }) {
              val e1p = pazip.foldRight(e1) {
                (h,acc) => h match {
                  case ((x,MTyp(m,t)),exp) => substitute(acc,exp,x)
                }
              }
              p match {
                case None => e1p
                case Some(x1) => substitute(e1p,v1,x1)
              }
            }
            //SearchCall2
            else {
              val pazipp = mapFirst(pazip) {
                case ((x,MTyp(m,t)),exp) => if(isRedex(m,exp)) Some((x,MTyp(m,t)),step(exp)) else None
              }
              val (_,argsp) = pazipp.unzip
              Call(v1,argsp)
            }
          }
          case _ => throw StuckError(e)
        }
      /***** New cases for Lab 4. */
      case GetField(v1,f) if isValue(v1) => v1 match {
        case Obj(fields) => fields.get(f) match {
          case Some(v) => v
          case None => Undefined
        }
        case _ => throw new UnsupportedOperationException
      }
      /* Inductive Cases: Search Rules */
      /***** Cases from Lab 3. */
      case Unary(uop, e1) => Unary(uop,step(e1))
      case Binary(bop, e1, e2) => if(isValue(e1)) Binary(bop, e1, step(e2)) else  Binary(bop, step(e1), e2)
      case Print(e1) => Print(step(e1))
      case If(e1,e2,e3) => If(step(e1),e2,e3)
      case Decl(mode,x,e1,e2) if isRedex(mode,e1) => Decl(mode,x,step(e1),e2)
      /***** More cases here */
      /***** Cases needing adapting from Lab 3 */
      case Call(e1, args) => Call(step(e1),args)
      case Obj(fields) => Obj(fields.mapValues((e) => step(e)))
      case GetField(e1,f) => GetField(step(e1),f)
      /***** New cases for Lab 4. */

      /* Everything else is a stuck error. Should not happen if e is well-typed.
       *
       * Tip: you might want to first develop by comment out the following line to see which
       * cases you have missing. You then uncomment this line when you are sure all the cases
       * that you have left the ones that should be stuck.
       */
      case _ => throw StuckError(e)
    }
  }
  
  
  /* External Interfaces */
  
  //this.debug = true // uncomment this if you want to print debugging information
  this.keepGoing = true // comment this out if you want to stop at first exception when processing a file
}

