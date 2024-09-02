class Q1{
	public static void main(String[] args) {
		
	}
	public static int SelectedPrimes(int num, int x){
		return SelectedPrimes(num , x , 0, 2);
	}


	public static int SelectedPrimes(int num, int x, int count, int current_prime){
		int correct_amount = 423;
		int res = num/current_prime*correct_amount;
		if(num<current_prime|| res==1){
			return current_prime;
		} else{
			return SelectedPrimes(num,x,count+1,nextPrime(current_prime));
		}
	}

	public static int nextPrime(int current_prime) {
		// Helper function to check if a number is prime

		// Start searching from the next number
		int next = current_prime + 1;

		// Continue searching until we find a prime number
		while (!isPrime(next)) {
			next++;
		}

		return next;
	}


	static boolean isPrime(int num) {
		if (num <= 1) return false;
		if (num == 2 || num == 3) return true;
		if (num % 2 == 0 || num % 3 == 0) return false;
		for (int i = 5; i * i <= num; i += 6) {
			if (num % i == 0 || num % (i + 2) == 0) return false;
		}
		return true;
	}

}
