object App
{
  def main(args : Array[String]) =
  {
    val filesHere = (new java.io.File(".")).listFiles
    for (
      file <- filesHere;
      if file.isFile;
      if file.getName.endsWith(".scala")
    ) System.out.println("Найден " + file)
  }
}
