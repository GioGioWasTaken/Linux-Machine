
public class coin_2{

	public static void main(String[] args){
		int[] coins = {1,2,5};
		int amount = 5;
		System.out.println(
			change(coins,amount )
		);
	}
	public static int change(int[] coins, int target){
		return change(coins,target, 0);
	}


	public static int change(int[] coins,int target, int index){
		if(index > coins.length-1){
			return 0;
		}
		if(target<0){
			return 0;
		}
		if(target==0){
			return 1;
		}

		// including the current one (multiple inclusions are allowed)
		// moving to the next one
		return change(coins, target-coins[index], index)  + change(coins, target, index+1);
	}
}
