public class Q2 {
    public static void main(String[] args) {
        int[] array = {3, 0, 0, 4, 7, 9, 0, 0, 0, 0, 11, 15, 0, 19, 20, 0, 0, 31, 40, 0};
        System.out.println(kAlmostSearch(array,9));
        System.out.println(kAlmostSearch(array,31));
        System.out.println(kAlmostSearch(array,30));
    }
    public static int kAlmostSearch (int [] a, int num){
        int l = 0;
        int r = a.length;
        while(l<=r){
            int m = l + (r-l)/2;
            if(a[m] == num){
                return m;
            }
            while(a[m] ==0 && m>l){
                m--;
                if(a[m] == num){
                    return m;
                }
            }
            if(a[m] > num){
                r = m-1;
            } else if(a[m] < num){
                l = m+1;
            } 
        }
        return -1;
    }
}
