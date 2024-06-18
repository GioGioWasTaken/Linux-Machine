import java.awt.List;
import java.lang.classfile.components.ClassPrinter.ListNode;

public class reverse_ll {
  class Solution {
    public ListNode reverseList(ListNode head) {
      if (head.next == null || head == null) {
        return head;
      }

      ListNode newHead = reverseList(head.next); // HI I'M NEWHEAD. I AM THE LAST NODE
      head.next.next = head; // HI I'M HEAD! IM THE VALUE THE FUNCTION BEFORE ME
                             // PASSED ON TO ME!
      head.next = null;
      return newHead;
    }
  }
}
