//object hw3 {
    trait DiscountPerson {
 
     def isDiscountApplied() : Boolean
 
     def discountAmount() : Double = 10.5
 
   }

   class Person(age: Int) extends DiscountPerson {
     
      var myAge: Int = age
  
      def isDiscountApplied() = myAge > 60
 
   }

   object DiscountTraitTest extends App {
  
     val seniorPerson = new Person(65)
  
     if( seniorPerson.isDiscountApplied() ) 
        println(seniorPerson.discountAmount())
   }

   //def main(args:Array[String]) {
   //     println("hw3:\n")
   //}
//}
