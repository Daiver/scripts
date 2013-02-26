import scala.xml.Elem
import scala.xml.Node
import scala.collection.mutable.Queue
import scala.xml.Text
import scala.xml.PrettyPrinter
import scala.xml._
import java.net.URL

/*
object Reader {
    def loadXML = {
        val parserFactory = new org.ccil.cowan.tagsoup.jaxp.SAXFactoryImpl
        val parser = parserFactory.newSAXParser()
        val source = new org.xml.sax.InputSource("http://www.randomurl.com")
        val adapter = new scala.xml.parsing.NoBindingFactoryAdapter      
        val feed = adapter.loadXML(source, parser)
        feed
    }
}
*/

object App {
    def main(args : Array[String]) = {

        println("!")
        val url = new URL("http://google.com")
        val conn = url.openConnection
        //println(conn.getInputStream())
        println(XML.load(conn.getInputStream))
    }
}
