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
            
            var keyWords = new scala.collection.mutable.HashMap[String, Int]()//TODO: FIX IT
            for(word <- raw_page.split(" ")) {
                keyWords.put(word, 1)
            }
            val hrefs = getHref().filter(!_.endsWith(".png")).filter(!_.endsWith(".ico")).filter(!_.endsWith(".jpg"))


            val images = getImages()
            StoredPage(url, "", keyWords, hrefs, images)
        }
    }

    def search(query : String, pages : List[StoredPage]) = {
        val keyWords = query.split(" ")
        def filterFunc(page : StoredPage, words : Array[String]) : Boolean = {
            if (words.length == 0) {
                return true
            }
            else {
                if (! page.keyWords.contains(words.head)) false
                else (filterFunc(page, words.tail))
            }
        }
        pages.filter((x:StoredPage) => filterFunc(x, keyWords))
    }
    
    def main(args : Array[String]) = {
        println("Searching with " + args(0))
        val crawler = new Crawler()
        var pages = List[StoredPage]()

        val major_url = "http://habrahabr.ru"
        println("Start grabing " + major_url)
        def walker(url : String, depth : Int) : StoredPage = {
            val page = crawler.grabUrl(url)
            println("walking page url " + page.URL + "  num of hrefs " + page.links.length)
            pages ::= page
            if (depth < 1)
                page.links.filter(_.startsWith(major_url)).foreach((x:String) => {
                    try {    
                        walker(x, depth+1)
                    } catch {
                        case e: Exception => println(e)
                    }
                })
            page
        }
        walker(major_url, 0)
        println("Start search")
        search(args(0), pages).foreach((x:StoredPage) => println(x.URL))
    }

}
