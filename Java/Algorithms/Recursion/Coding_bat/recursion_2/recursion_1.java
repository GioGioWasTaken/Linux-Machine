public class recursion_1 {
  public boolean groupSum(int start, int[] nums, int target) {
    if(start==nums.length){
      if(target!=0){
        return false;
      } else{
        return true;
      }
    }
    return groupSum(start+1,nums,target-nums[start]) || groupSum(start+1,nums,target);

  }
}
