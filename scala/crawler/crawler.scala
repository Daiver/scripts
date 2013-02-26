import com.sun.xml.internal.messaging.saaj.util.ByteOutputStream
import java.io.{File, FileOutputStream}
import java.net.URL
import java.util.regex.Pattern
import java.util.Scanner

object App {
    def openResourceInputStream(url: String) = {
        val connection = new URL(url).openConnection()
        connection.setRequestProperty("User-Agent", "Mozilla/5.0 (compatible;)")
        connection.connect()
        connection.getInputStream
    }

    def grabPage(pageScanner : Scanner)= {
        var res = ""
        while (pageScanner.hasNextLine) {
            res += pageScanner.nextLine()
        }
        res
    }

    def getHref(str : String) = {
        //val imagePattern = Pattern.compile("(src|href)[^><\"]*\"([^\"\']*\\.(gif|jpg|png|html))\"")
        val imagePattern = Pattern.compile("""http:\/\/[A-Za-z0-9-_]+\.[A-Za-z0-9-_:%&\?\/.=]+""")
        val matcher = imagePattern.matcher(str)
        while(matcher.find()) {
            println(matcher.group(0))
        }
    }

    def main(args : Array[String]) = {

        val pageScanner = new Scanner(openResourceInputStream("http://habrahabr.ru"))
        val page = grabPage(pageScanner)
        println(getHref(page))

        //println(conn.getInputStream())
        //println(XML.load(conn.getInputStream))
    }
}
