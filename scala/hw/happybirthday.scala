object app {
    def main(args : Array[String]) = {
        (1 to 4).map { i => "Happy Birthday " + (if (i == 3) "dear " + (if (args.length < 1) "Name" else args(0)) else "to You") }.map ( println )
    }
}

