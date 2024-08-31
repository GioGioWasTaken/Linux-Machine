public class recursion_16 {

  public int array11(int[] nums, int index) {
    if(nums.length == index){
      return 0;
    }  else if(nums[index] == 11){
      return 1+ array11(nums,index+1);
    } else{
      return array11(nums,index+1);
    }

  }
}
