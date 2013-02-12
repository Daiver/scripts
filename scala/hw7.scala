object MyApp {
    def my_constr(f: => Unit) =  {
        Console.println("Before f...")
        f
        Console.println("After f...")
    }

    def tst() = {
        Console.println("i'm 'f'")
    }

    def While(condition : ()=>Boolean) = {
    }

    def main(args:Array[String]) = {
        my_constr {
            tst()
        }
    }
}
