object Functionlistic {
    def main(args : Array[String]) = {
        args.filter((arg:String)=>arg.startsWith("k")).foreach((x)=>println(x))
    }
}
