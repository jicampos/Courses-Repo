/* Lesson learned from CS 275 Assignment 4
 * using the method peek() from stack will throw
 * 'EmptyStackException' if stack is empty
 */
import java.util.Stack;

public class StackTest {
 
  public static void main(String[] args) {
  
    Stack<Integer> num = new Stack<Integer>();
    
    num.push(4);
    
    System.out.println(num.pop() );
    System.out.println(num.peek() );
  
  }
  
}