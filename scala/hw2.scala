object HelloWorld{
    def min(x:Int, y:Int) = {
        if (x < y) x
        else y
    }
    def main(args:Array[String]){
        val msg = "HelloWorld"
        val res = this.min(22, 17)
        println(res)
    }
}

