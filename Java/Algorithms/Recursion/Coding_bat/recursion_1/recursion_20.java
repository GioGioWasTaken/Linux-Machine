public class recursion_20 {
    public String endX(String str) {
        return endXHelper(str, 0);
    }

    public String endXHelper(String str, int countX) {
        if (str.length() == 0) {
            // Construct the string of 'x' characters recursively
            return buildXString(countX);
        } else {
            if (str.charAt(0) == 'x') {
                // Increment countX and proceed with the rest of the string
                return endXHelper(str.substring(1), ++countX);
            } else {
                // Append current character and recursively process the rest
                return str.charAt(0) + endXHelper(str.substring(1), countX);
            }
        }
    }

    // Helper method to construct a string of 'x' characters of length countX
    public String buildXString(int countX) {
        if (countX == 0) {
            return "";
        }
        return "x" + buildXString(countX - 1);
    }
}
