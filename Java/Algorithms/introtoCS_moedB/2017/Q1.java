public class Q1 {
    public static void main(String[] args) {
        int[][] mat = {
            {1, 5, 7},
            {3, 2, 9},
            {1, 2, 3}
        };
        int[] arr = {7, 2, 3};
        System.out.println("True: " + covers(mat, arr, 2));
        System.out.println("False: " + covers(mat, arr, 1));
    }

    public static boolean covers(int[][] mat, int[] arr, int k) {
        return covers(mat, arr, k, 0);
    }

    public static boolean covers(int[][] mat, int[] arr, int k, int curr_line) {
        // If no elements left to cover, return true
        if (arr.length == 0) {
            return true;
        }

        // If out of lines or k is negative, return false
        if (curr_line >= mat.length || k < 0) {
            return false;
        }

        // Try to cover the array using the current line
        boolean coveredByCurrentLine = isInLine(arr, mat[curr_line], 0);

        // Try to cover with this line or without this line
        return coveredByCurrentLine || covers(mat, arr, k - 1, curr_line + 1) ||
               covers(mat, arr, k, curr_line + 1);
    }

    public static boolean isInLine(int[] arr, int[] arr2, int index) {
        // Base case: if we have reached the end of the array
        if (index == arr.length) {
            return true;
        }

	if(arr[index] == -1){
		// -1 means it was already found.
		return isInLine(arr, arr2, index + 1);
	}

        // Check if arr[index] exists in arr2
        boolean found = existsInArray(arr[index], arr2);

	if(found){
		arr[index] = -1;
	}

        // Recursively check the rest of the array
        return found && isInLine(arr, arr2, index + 1);
    }

    // Helper function to check if a value exists in arr2
    public static boolean existsInArray(int value, int[] arr2) {
        for (int i : arr2) {
            if (i == value) {
                return true;
            }
        }
        return false;
    }
}
