
class IntNode {
    private int _value;
    private IntNode _next;

    public IntNode(int val, IntNode n) {
        _value = val;
        _next = n;
    }

    public int getValue() {
        return _value;
    }

    public IntNode getNext() {
        return _next;
    }

    public void setValue(int val) {
        _value = val;
    }

    public void setNext(IntNode n) {
        _next = n;
    }
}

class IntList {
    private IntNode _head;

    public IntList() { _head = null; }
    public IntList(IntNode node) { _head = node; }

    public IntList secret(int k) //k is a positive integer
    {
        IntNode current = _head;
        for (int i = 0; i < k; i++) {
            IntNode j = current;
            while (j != null) {
                if (j.getValue() % k == i) {
                    int temp = j.getValue();
                    j.setValue(current.getValue());
                    current.setValue(temp);
                    current = current.getNext();
                }
                j = j.getNext();
            }
        }
        return new IntList(_head);
    }

	public void printList() {
		IntNode current = _head;
		while (current != null) {
			System.out.print(current.getValue() + " ");
			current = current.getNext();
		}
		System.out.println();
	}
	public void addToFront(int value) {
		_head = new IntNode(value, _head);
	}
}


public class Q4{
	public static void main(String[] args) {
		int[] values = {38, 6, 14, 133, 402, 20};
		IntList myList = createListWithValues(values);
		myList.secret(998);
		myList.printList();
	}





	public static IntList createListWithValues(int[] values) {
		IntList list = new IntList();
		for (int i = values.length - 1; i >= 0; i--) {
			list.addToFront(values[i]);
		}
		return list;
	}



}
