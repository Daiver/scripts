object Functionlistic {
    def main(args : Array[String]) = {
        args.filter((arg)=>arg.startsWith("k")).foreach((x)=>println(x))
    }
}
