import com.sun.xml.internal.messaging.saaj.util.ByteOutputStream
import java.io.{File, FileOutputStream}
import java.net.URL
import java.util.regex.Pattern
import java.util.Scanner
import java.security.MessageDigest

object Appp  {

    case class StoredPage (URL : String, page_html : String, keyWords : scala.collection.mutable.HashMap[String, Int], links : List[String], images : List[String], hash : Array[Byte])
    def md5(s: String) = {
        MessageDigest.getInstance("MD5").digest(s.getBytes)
    }
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
            val hrefs = getHref().filter((x : String) => !(x.endsWith(".jpg") || x.endsWith(".ico") || x.endsWith(".png") || x.endsWith(".gif")))
            //val images = getImages()
            val images = List[String]()
            StoredPage(url, "", keyWords, hrefs, images, md5(raw_page))
        }
    }

    def search(query : String, pages : scala.collection.mutable.HashMap[String, StoredPage]) = {
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
        pages.filter((x : (String, StoredPage)) => filterFunc(x._2, keyWords)).values
    }
    
    def main(args : Array[String]) = {
        println("Searching with " + args(0))
        def grabHost(major_url : String, max_depth : Int = 1) = {
            val crawler = new Crawler()
            //var pages = List[StoredPage]()
            var pages = scala.collection.mutable.HashMap[String, StoredPage]()
            println("Start grabing " + major_url)
            def walker(url : String, depth : Int) : Unit = {
                if (!pages.contains(url)) {
                    val page = crawler.grabUrl(url)
                    println(pages.size  + " walking page url " + page.URL + "  num of hrefs " + page.links.length + " hash " + page.hash.toList)
                    pages.put(url, page)
                    if (depth < max_depth)
                        page.links.filter(_.startsWith(major_url)).par.foreach((x:String) => {
                            try {    
                                walker(x, depth+1)
                            } catch {
                                case e: Exception => println(e)
                            }
                        })
                }
            }
            walker(major_url, 0)
            pages
        }
        val major_url = "http://habrahabr.ru/"
        val pages = grabHost(major_url, 2)
        println("Start search")
        search(args(0), pages).foreach((x:StoredPage) => println(x.URL))
    }
}
