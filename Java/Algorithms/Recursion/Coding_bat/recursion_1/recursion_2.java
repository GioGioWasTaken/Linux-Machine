class recursion_2{
  public static void main(String[] args) {
    
  }
  public int bunnyEars(int bunnies) {
    if(bunnies==0){
      return 0;
    }
    return bunnyEars(bunnies-1) +2;
  }
}
