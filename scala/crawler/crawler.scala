import com.sun.xml.internal.messaging.saaj.util.ByteOutputStream
import java.io.{File, FileOutputStream}
import java.net.URL
import java.util.regex.Pattern
import java.util.Scanner

object Appp  {

    //case class PageLink(URL : String)
    //case class ImageLink(URL : String)
    case class StoredPage (URL : String, page_html : String, keyWords : scala.collection.mutable.HashMap[String, Int], links : List[String], images : List[String])

    class Crawler {
        def openResourceInputStream(url : String) = {
            val connection = new URL(url).openConnection()
            connection.setRequestProperty("User-Agent", "Mozilla/5.0 (compatible;)")
            connection.connect()
            connection.getInputStream
        }

        val hrefPattern = Pattern.compile("""http:\/\/[A-Za-z0-9-_]+\.[A-Za-z0-9-_:%&\?\/.=]+""")
        val imagePattern = Pattern.compile("(src|href)[^><\"]*\"([^\"\']*\\.(gif|jpg|png))\"")
        val bodyPattern = Pattern.compile("<script>(\\S+)</script>")

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
            
            //println(raw_page.split(" ")(1))
            var keyWords = new scala.collection.mutable.HashMap[String, Int]()
            for(word <- raw_page.split(" ")) {
               keyWords.put(word, 1)
            }
            val hrefs = getHref().filter(!_.endsWith(".png"))
            val images = getImages()
            StoredPage(url, "", keyWords, hrefs, images)
        }
    }
    
    def main(args : Array[String]) = {
        val crawler = new Crawler()
        println(crawler.grabUrl("http://ya.ru"))
    }

}
