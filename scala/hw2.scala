object HelloWorld2{
    def min(x:Int, y:Int) = {
        if (x < y) x
        else y
    }

    def main(args:Array[String]){
        val msg = "HelloWorld"
        val res = this.min(22, 17)
        val faces = List("me", "you", "we")
        val List(a, b, c) = faces
        println(a, b, c, faces)
    }
}

