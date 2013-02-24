class Rational(r:Int, i:Int) {
    private def gcd(x:Int, y:Int): Int =
    {
        if (x==0) y
        else if (x<0) gcd(-x, y)
        else if (y<0) -gcd(x, -y)
        else gcd(y%x, x)
    }

    val numer = r/gcd(r, i)
    val denom = i/gcd(r, i)

    def +(that:Rational) = new Rational(numer*that.denom + that.numer*denom, denom * that.denom)
    override def toString() = "Rational:" + numer + "/" + denom 
}

object RationalTest extends App {
        val rat = new Rational(10, 1)
        val rat2 = new Rational(10, 1)
        Console.println(rat + rat2)
}
