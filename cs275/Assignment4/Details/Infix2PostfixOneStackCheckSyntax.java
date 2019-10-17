/*
   Convert fully parenthesized infix expressions to postfix.
   This algorithm uses one stack for operators.

   This version of the program does a better job of checking
   for correct syntax of the infix expressions.

   This is the algorithm from page 349 of the textbook.
*/
import java.util.StringTokenizer;
import java.util.Stack;

public class Infix2PostfixOneStackCheckSyntax
{

   public static String infix2Postfix(String infix)
   {
      Stack<String> operators = new Stack<String>();
      Stack<String> operands  = new Stack<String>();
      StringTokenizer st = new StringTokenizer(infix);
      String result = "";

      while (st.hasMoreTokens())
      {
         String token = st.nextToken();
         if ( token.equals("(") )
         {
            operators.push( token );
         }
         else if ( token.equals("+")
                || token.equals("-")
                || token.equals("^")
                || token.equals("*")
                || token.equals("/")
                || token.equals("%") )
         {
            operators.push( token );
         }
         else if ( token.equals(")") )
         {
            String op = operators.pop();
            result = result + " " + op;
            // after popping the operator, there must
            // be a left parenthesis on the stack
            String check = operators.pop();
            if ( !check.equals("(") )
               throw new IllegalArgumentException("misplaced parenthesis");
         }
         else // must be a number
         {
            result = result + " " + token;
         }
      }
      return result;
   }//infix2Postfix()



   public static void main(String[] args)
   {
      String[] expressions = {
                               "( 2 + ( 5 * 5 ) )",
                               "( ( 2 + 5 ) * 5 )",
                               "( ( ( 3 + 5 ) * 4 ) - 9 )",
                               "( ( ( 1 + 3 ) ^ 4 ) * ( 2 ^ 3 ) )",
                               "( ( ( 32 * 41 ) / 16 ) + ( 12 * 10 ) )"
                             };

      for (int i = 0; i < expressions.length; i++)
      {
         String result = infix2Postfix( expressions[i] );
         System.out.println( expressions[i] + " ==> " + result );
      }
   }//main()

}