public class Q4 {
	public static void main(String[] args) {
		A y1 = new B(100);
		B y2 = new B(100);
		B y3 = new B(20);
		A z1 = new C();
		C z2 = new C();
		// System.out.println(y1.foo(y2));
		// System.out.println(y2.foo(y1));
		System.out.println(y3.getNum());
		System.out.println (y1.foo(y3));
		System.out.println (y3.foo(y1));
	}
}


class A
{
	private int _num;
	public A(int num) {
		_num = num;
	}
	public int getNum() {
		return _num;
	}
	public boolean foo(A a) {
		System.out.println("Afoo");
		System.out.println("I'm num " + _num);
		System.out.println("I'm the passed num " + a._num);
		return _num >= 2*a._num;
	}
} //end of class A
//---------------------------------------------------------------------------------------------------------//
class B extends A
{
	public B(int num) {
		super(num);
	}
	public boolean foo(B b) {
		System.out.println("BBfoo");
		return getNum() == b.getNum();
	}
	public boolean foo(C c) {
		System.out.println("BCfoo");
		return getNum() == c.getNum();
	}
} //end of class B
//---------------------------------------------------------------------------------------------------------//
class C extends A
{
	private int _num2;
	public C() {
		super (20);
		_num2 = 20;
	}
	public boolean foo(A a)
{
		System.out.println("Cfoo");
		if (!(a instanceof C))
		return false;
		C c = (C)a;
		return _num2 == c._num2;
	}
} // end of class C
//---------------------------------------------------------------------------------------------------------
