
object App {
    def twiddle(foo : (Array[Float]) => Float, initial_params : Array[Float], tol : Float) = {
        var params = initial_params.clone()
        params(0) += 10
    }

    def main (args : Array[String]) = {
        println("....")
    }
}
