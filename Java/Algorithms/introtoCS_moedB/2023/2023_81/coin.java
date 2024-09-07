public class coin{
	public static void main(String[] args){
		int[] coins = {1,2,5};
		int amount = 11;
		System.out.println(
			coinChange(coins,amount )
		);
	}
	public static int coinChange(int[] coins, int target){
		int res = coinChange(coins,target, 0, 0);
		if(res == Integer.MAX_VALUE){
			return -1;
		} else{
			return res;
		}
	}


	public static int coinChange(int[] coins,int target, int index, int count){
		if(index > coins.length-1){
			return Integer.MAX_VALUE;
		}
		if(target<0){
			return Integer.MAX_VALUE;
		}
		if(target==0){
			return count;
		}
		return Math.min(coinChange(coins,target-coins[index],index, count+1) , coinChange(coins,target,index + 1, count));
	}
}
