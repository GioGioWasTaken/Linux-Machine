/**
 * gsClump
 */
public class gsClump {

  public boolean groupSumClump(int start, int[] nums, int target) {
    if(nums.length==start){
      if(target==0){
        return true;
      } else{
        return false;
      }
    }
    int counter = 1;
    int current = start+1;
    while(current <nums.length && nums[start]==nums[current]){
      counter++;
      current++;
    }

    return groupSumClump(start+counter,nums,target-counter*nums[start]) ||  groupSumClump(start + counter,nums,target);

  }

}
