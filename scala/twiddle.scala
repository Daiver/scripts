
object App {

    def func(p : Array[Float]) = {
        10 - p(0)*2 + p(1)*3 + p(2)
    }

    def twiddle(foo : (Array[Float]) => Float, initial_params : Array[Float], tol : Float) = {
        var params = initial_params.clone()
        var diff_params = Array.fill(initial_params.length){0.0f}
        params(0) += 10

        params.toList
    }

    def main (args : Array[String]) = {
        println(twiddle(func, Array(0, 0, 0), 0.001f))
    }
}
