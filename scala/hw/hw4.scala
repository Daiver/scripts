object Tmr
{
    def time_work(callback : () => Unit, timeout:Int) = {
        while(true) {
            callback()
            Thread.sleep(timeout)
        }
    }

    def test_callback() = {
        println("Wow")
    }

    def main(args : Array[String]) = {
        println("HW!")
        time_work(() => println("So... :)"), 100)
    }
}
