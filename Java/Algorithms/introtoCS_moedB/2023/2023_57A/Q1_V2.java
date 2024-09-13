/**
 * Q1_V2
 */
public class Q1_V2 {
	public static void main(String[] args) {
		
	}

	public static int selectedPrimes(int num, int x){
		return selectedPrimes(num, x, 2);
	}
	public static int selectedPrimes(int num, int x, int currPrime){
		// base case
		if(num < currPrime || num==1){
			return 0;
		}
		// recursive step
		int curPower = findDivisorPower(num,currPrime);
		int nextPrime = nextPrime(currPrime);
		if(curPower == x){
			System.out.println(x);
			int value = (int) Math.pow(currPrime , curPower);
			return 1 + selectedPrimes(num/value,x, nextPrime);
		}
		return selectedPrimes(num,x, nextPrime);
	}

	public static int findDivisorPower(int target, int base){
		// this function will return the biggest power of base that divides target without a remainder.
		// it's guranteed that said number will be the correct number, because number theory
		if(target % base ==0 && target!=1){
			return 1 + findDivisorPower(target/base , base);
		} else{
			return 0;
		}
		
	}

	public static int nextPrime(int currPrime) {
		int next = currPrime + 1;

		while (!isPrime(next)) {
			next++;
		}

		return next;
	}

	private static boolean isPrime(int num) {
		if (num < 2) return false;
		for (int i = 2; i <= Math.sqrt(num); i++) {
			if (num % i == 0) return false;
		}
		return true;
	}
}
