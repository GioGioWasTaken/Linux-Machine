public class recursion_6_V2{
  public static void main(String[] args) {
    
  }
  public boolean splitOdd10(int[] nums) {
    int total_sum = getSum(nums);
    splitOdd10Helper(nums, 0, total_sum,0);
  }

  public boolean splitOdd10Helper(int[] nums, int index,int total, int current ) {
    if(nums.length==index){
      if(current % 10 ==0 && (total-current)%2 !=0 ){
        return true;
      }
      return false;
    }
    return splitO

  }



public static int getSum(int start, int[] nums) {
    if (start == nums.length) {
      return 0;
  }
  return nums[start] + getSum(start + 1, nums);
}

}
