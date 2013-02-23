
object App {

    def twiddle(foo : (Array[Float]) => Float, initial_params : Array[Float], tol : Float) = {
        var params = initial_params.clone()
        var diff_params = Array.fill(initial_params.length){1.0f}
        var best_error = foo(params)
        while (foo(params).abs > tol) {
            for(i <- (0 to params.length - 1))
            {
                params(i) += diff_params(i)
                val error = foo(params)
                if (error < best_error) {
                    diff_params(i) *= 1.1f
                    best_error = error
                } else {
                    params(i) -= 2*diff_params(i)
                    val error = foo(params)
                    if (error < best_error) {
                        diff_params(i) *= 1.1f
                        best_error = error
                    } else {
                        params(i) += diff_params(i)
                        diff_params(i) *= 0.9f
                    }

                }

            }
        }
        params
    }

    def main (args : Array[String]) = {
        val pol = (p : Array[Float]) => 2*p(0) + 3*p(1) + p(2)
        val params = twiddle((p : Array[Float] )=> (10 - pol(p)).abs, Array(0, 0, 0), 0.01f)
        println(params.toList)
        println(pol(params))
    }
}
