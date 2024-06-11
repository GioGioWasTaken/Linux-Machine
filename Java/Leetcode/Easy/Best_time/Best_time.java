class Solution {
  public int maxProfit(int[] prices) {
    if (prices.length == 0) {
      return 0;
    } // we don't want an out of bounds check.
    int maxProfit = 0; // we can also just not buy, so the minimum amount we can
                       // profit every day is 0.
    int l = 0;
    int r = l + 1;
    while (r < prices.length) {
      if (prices[r] < prices[l]) {
        l = r;
        r = l + 1;
      } else {
        int profit = prices[r] - prices[l];
        maxProfit = Math.max(maxProfit, profit);
        r++;
      }
    }
    return maxProfit;
  }
}
