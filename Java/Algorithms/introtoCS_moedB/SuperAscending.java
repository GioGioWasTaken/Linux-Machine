public static int findFirstMissing(int[] arr){
	// first we "psuedo-sort" the array
	int length = arr.length;
	for(int i = 0; i < length-1; i++){
		int value = arr[i];
		if(value > length || value <= 0){
			value = Integer.MAX_VALUE;
		} else{
			arr[value-1] = value;

		}
	}

	int currSmallest = 1;
	for(int i =0; i<length-1; i++){
		int value = arr[i];
		if(value==Integer.MAX_VALUE){
			continue;
		} else{
			if(value > currSmallest){
				return currSmallest;
			} else if(value == currSmallest){
				currSmallest++;
			}
		}
	}
}
