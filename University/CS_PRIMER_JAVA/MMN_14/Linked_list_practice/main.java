class Node {
    int data;
    Node next;

    public Node(int data) {
        this.data = data;
        this.next = null;
    }
}

class Main {
    public static void main(String[] args) {
        // Create a linked list for testing
        Node head = new Node(2);
        head.next = new Node(3);
        head.next.next = new Node(3);
        head.next.next.next = new Node(3);
        
        // Test the method
        Main main = new Main();
        int result = main.maxEqualValue(head);
        System.out.println("Max length of equal value sequence: " + result);
    }

    public int maxEqualValue(Node head) {
        if (head == null || head.next == null) {
            return 0;
        } else {
            int currentValue = head.data;
            int nextValue = head.next.data;
            int length = 1;
            if (currentValue == nextValue) {
                length = 1 + maxEqualValue(head.next);
            }
            return Math.max(length, maxEqualValue(head.next));
        }
    }
}
