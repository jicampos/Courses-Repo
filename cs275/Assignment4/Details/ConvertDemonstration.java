// FILE: ConvertDemonstration.java
// This program reads fully parenthesized arithmetic expressions
// and converts them to postfix notation.

// This program is based on the EvaluateDemonstration.java program from
// Section 6.2. This program uses the same algorithm as EvaluateDemonstration.java
// but instead of evaluating sub expressions and pushing the result onto the operand
// stack, this program just converts each sub expression into postfix, and pushes
// the postfix notation (as a String) onto the operand stack.

// The algorithm used here is NOT the algorithm described in the book on pages 348-349.

import java.util.Stack;
import java.util.Scanner;
import java.util.regex.Pattern;

public class ConvertDemonstration
{

   public static void main(String[ ] args)
   {
      Scanner stdin = new Scanner(System.in);
      String expression;
      String answer;

      System.out.println("Please type an arithmetic expression made from");
      System.out.println("unsigned numbers and the operations + - * /.");
      System.out.println("The expression must be fully parenthesized.");

      do
      {
         System.out.print("Your expression: ");
         expression = stdin.nextLine( );
         try
         {
            answer = infix2postfix(expression);
            System.out.println("The result is " + answer);
         }
         catch (Exception e)
         {
            System.out.println("Error." + e.toString( ));
         }
      }
      while (query(stdin, "Another string?"));

      System.out.println("All numbers are interesting.");
   }


   public static boolean query(Scanner input, String prompt)
   {
      String answer;

      System.out.print(prompt + " [Y or N]: ");
      answer = input.nextLine( ).toUpperCase( );
      while (!answer.startsWith("Y") && !answer.startsWith("N"))
      {
         System.out.print("Invalid response. Please type Y or N: ");
         answer = input.nextLine( ).toUpperCase( );
      }

      return answer.startsWith("Y");
   }


   public static String infix2postfix(String s)
   // Precondition: The string is a fully parenthesized arithmetic expression
   // formed from non-negative numbers, parentheses, and the four operations
   // +, -, *, and /.
   // Postcondition: The string has been evaluated and the value returned.
   // Exceptions: Can throw an NumberFormatException if the expression contains
   // characters other than digits, operations, parentheses and whitespace.
   // Can throw IllegalArgumentException if the input line is an
   // illegal expression, such as unbalanced parentheses or a division by zero.
   {
      Scanner input = new Scanner(s);
      Stack<String> operands = new Stack<String>( );
      Stack<Character> operations = new Stack<Character>( );
      String next;
      char first;

      while (input.hasNext( ))
      {
         if (input.hasNext(UNSIGNED_DOUBLE))
         {
            next = input.findInLine(UNSIGNED_DOUBLE);
            operands.push(next);
         }
         else
         {
            next = input.findInLine(CHARACTER);
            first = next.charAt(0);

            switch (first)
            {
               case '+': // Addition
               case '-': // Subtraction
               case '*': // Multiplication
               case '/': // Division
                  operations.push(first);
                  break;
               case ')': // Right parenthesis
                  evaluateStackTops(operands, operations);
                  break;
               case '(': // Left parenthesis
                  break;
               default : // Illegal character
                  throw new IllegalArgumentException("Illegal character");
            }
         }
      }
      if (operands.size( ) != 1)
         throw new IllegalArgumentException("Illegal input expression");
      return operands.pop( );
   }


   public static void evaluateStackTops(Stack<String> operands,
                                        Stack<Character> operations)
   // Precondition: The top of the operations stack contains +, -, *, or /, and
   // the numbers stack contains at least two numbers.
   // Postcondition: The top two numbers have been popped from the numbers stack, and the
   // top operation has been popped from the operations stack. The two numbers have been
   // combined using the operation (with the second number popped as the left operand).
   // The result of the operation has then been pushed back onto the numbers stack.
   // Exceptions: Throws an IllegalArgumentException if the stacks are illegal or if the
   // operation results in a division by zero.
   {
      String operand1, operand2;

      // Check that the stacks have enough items, and get the two operands.
      if ((operands.size( ) < 2) || (operations.isEmpty( )))
         throw new IllegalArgumentException("Illegal expression");
      operand2 = operands.pop( );
      operand1 = operands.pop( );

      // Carry out an action based on the operation on the top of the stack.
      switch (operations.pop( ))
      {
         case '+': operands.push(operand1 + " " + operand2 + " + ");
                   break;
         case '-': operands.push(operand1 + " " + operand2 + " - ");
                   break;
         case '*': operands.push(operand1 + " " + operand2 + " * ");
                   break;
         case '/': operands.push(operand1 + " " + operand2 + " / ");
                   break;
         default : throw new IllegalArgumentException("Illegal operation");
      }
   }

   // These patterns are from Appendix B of Data Structures and Other Objects.
   // They may be used in hasNext and findInLine to read certain patterns
   // from a Scanner.
   public static final Pattern CHARACTER =
     Pattern.compile("\\S.*?");
   public static final Pattern UNSIGNED_DOUBLE =
     Pattern.compile("((\\d+\\.?\\d*)|(\\.\\d+))([Ee][-+]?\\d+)?.*?");
}