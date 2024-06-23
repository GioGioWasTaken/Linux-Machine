public class generatePW {
    private static final String password = "cat"; // Example password

    public static String findPassword(int length, String current) {
        if (current.equals(password)) {
            return current;
        }
        if (current.length() >= length) {
            return null;
        }

        return tryNextCharacter(length, current, 'a');
    }

    private static String tryNextCharacter(int length, String current, char c) {
        if (c > 'z') {
            return null;
        }

        String result = findPassword(length, current + c);
        if (result != null) {
            return result;
        }

        return tryNextCharacter(length, current, (char) (c + 1));
    }

    public static void main(String[] args) {
        int length = 3; // Example length
        String foundPassword = findPassword(length, "");
        if (foundPassword != null) {
            System.out.println("Password found: " + foundPassword);
        } else {
            System.out.println("Password not found");
        }
    }
}
