import com.sun.xml.internal.messaging.saaj.util.ByteOutputStream
import java.io.{File, FileOutputStream}
import java.net.URL
import java.util.regex.Pattern
import java.util.Scanner

object Appp  {

    //case class PageLink(URL : String)
    //case class ImageLink(URL : String)
    case class StoredPage (URL : String, page_html : String, links : List[String], images : List[String])

    class Crawler {
        def openResourceInputStream(url : String) = {
            val connection = new URL(url).openConnection()
            connection.setRequestProperty("User-Agent", "Mozilla/5.0 (compatible;)")
            connection.connect()
            connection.getInputStream
        }
        val hrefPattern = Pattern.compile("""http:\/\/[A-Za-z0-9-_]+\.[A-Za-z0-9-_:%&\?\/.=]+""")
        val imagePattern = Pattern.compile("(src|href)[^><\"]*\"([^\"\']*\\.(gif|jpg|png))\"")

        def grabUrl(url : String) = {
            val pageScanner = new Scanner(openResourceInputStream(url))
            def getPage(res : String = "") : String = {
                if (pageScanner.hasNextLine) {
                    getPage(res + pageScanner.nextLine())
                }
                else {
                    res
                }
            }

            val raw_page = getPage()
            val href_matcher = hrefPattern.matcher(raw_page)
            val image_matcher = imagePattern.matcher(raw_page)

            def getHref(res : List[String] = List[String]()) : List[String] = {
                if (href_matcher.find()) {
                    getHref(res :+ href_matcher.group(0).toString())
                }
                else {
                    res
                }
            }
            def getImages(res : List[String] = List[String]()) : List[String] = {
                if (image_matcher.find()) {
                    getHref(res :+ image_matcher.group(2).toString())
                }
                else {
                    res
                }
            }

            val hrefs = getHref()
            val images = getImages()
            StoredPage(url, "", hrefs, images)
            //getHref()
        }

    }
    
    def main(args : Array[String]) = {
        val crawler = new Crawler()
        println(crawler.grabUrl("http://ya.ru"))
        //val sp = new StoredPage("Me", "So")
        //println(sp.page_html)
    }

}
