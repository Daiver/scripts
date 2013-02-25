import com.sun.xml.internal.messaging.saaj.util.ByteOutputStream
import java.io.{File, FileOutputStream}
import java.net.{URL, URLConnection}
import java.util.regex.Pattern
import java.util.Scanner
import scala.xml._

object App {
    def main(args : Array[String]) = {
        println("!")
        val url = new URL("http://friendfeed.com/api/feed/public?format=xml&num=100")
        val conn = url.openConnection
        println(XML.load(conn.getInputStream))
    }
}
