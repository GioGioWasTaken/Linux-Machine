
/**
 * Q1
 */
public class Q1 {
    public static void main(String[] args) {
        System.out.println(
            edit("sunday", "saturday")
        );
    }

    
public static int edit(String str1, String str2) {
        return edit(str1,str2, 0, 0);
    }
public static int edit(String str1, String str2, int index, int count) {
    // Base cases
    if (index == str2.length()) return count + (str1.length() - str2.length()); // Delete remaining characters in str1
    if (str1.equals(str2)) return count;
    if (index >= str1.length()) return count + (str2.length() - index); // Insert remaining characters of str2
    
    // If characters are different, consider all operations
    if (index < str1.length() && str1.charAt(index) != str2.charAt(index)) {
        // Insert character at index
        String insertChar = str1.substring(0, index) + str2.charAt(index) + str1.substring(index);
        int insertOption = edit(insertChar, str2, index + 1, count + 1);
        
        // Delete character at index
        String deleteChar = str1.substring(0, index) + str1.substring(index + 1);
        int deleteOption = edit(deleteChar, str2, index, count + 1); // Index stays same as the next character moves to current position
        
        // Replace character at index
        String replaceChar = str1.substring(0, index) + str2.charAt(index) + str1.substring(index + 1);
        int replaceOption = edit(replaceChar, str2, index + 1, count + 2);
        
        return Math.min(Math.min(insertOption, deleteOption), replaceOption);
    } else {
        // If characters are the same, move to the next character
        return edit(str1, str2, index + 1, count);
    }
}



}
