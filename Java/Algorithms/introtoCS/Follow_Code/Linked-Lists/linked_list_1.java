public class linked_list_1 {
	public static void main(String[] args) {
		IntNodeTwo(3);
		
	}	
}


class IntNodeTwo
{
	private int _num;
	private IntNodeTwo _next, _prev;
	public IntNodeTwo(int n) {
		_num = n;
		_next = null;
		_prev = null;
	}
	public int getNum() { return _num; }
	public IntNodeTwo getNext() { return _next; }
	public IntNodeTwo getPrev() { return _prev; }
	public void setNum (int n) { _num = n; }
	public void setNext (IntNodeTwo node) { _next = node; }
	public void setPrev (IntNodeTwo node) { _prev = node; }
}


public class IntListTwo
{
	private IntNodeTwo _head, _tail;
	public IntListTwo()
{
		_head = null;
		_tail = null;
	}

	public boolean what (int num)
{
		IntNodeTwo head = _head;
		IntNodeTwo tail = _tail;
		while (head != tail)
	{
			int headNum = head.getNum();
			int tailNum = tail.getNum();
			if (headNum == -1*num)
			head = head.getNext();
			else if (tailNum == -1*num)
			tail = tail.getPrev();
			else
		{
				int curr = head.getNum() + tail.getNum();
				if (curr == num)
				return true;
				else if (curr > num)
				tail = tail.getPrev();
				else
				head = head.getNext();
			}
		}
		return false;
	}
	public boolean something()
{
		IntNodeTwo head = _head;
		IntNodeTwo tail = _tail;
		while ((head.getNext() != tail) && (head.getNum() < 0))
	{
			if (what (-1*head.getNum()))
			return true;
			else
			head = head.getNext();
		}
		return false;
	}

}
