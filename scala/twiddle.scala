
object App {

    def func(p : Array[Float]) = {
        10 - p(0)*2 + p(1)*3 + p(2)
    }

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
        val params = twiddle(func, Array(1, 1, 1), 0.01f)
        println(params.toList)
        println(func(params))
    }
}
