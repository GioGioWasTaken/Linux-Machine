import jdk.internal.org.jline.terminal.TerminalBuilder.SystemOutput;

public class Q1 {
  public static void main(String[] args) {
  }

  public static int cheapRt(int[] stations, int step1, int step2, int limit) {
    return cheapRt(stations, step1, step2, limit, 0, 0, "");
  }

  public static int cheapRt(int[] stations, int step1, int step2, int limit,
      int index, int sum, String route) {
    if (index == stations.length - 1) {
      route += " =" + index;
      System.out.println(route);
      sum += stations[index];
      return sum;
    }
    if (limit > 0) {
      int Option1 = Integer.MAX_VALUE;
      if (index + move2 <= stations.length - 1) {
        Option1 = cheapRt(stations, step1, step2, limit - 1, index + step2,
            sum + stations[index], route + " " + index);
      }
      int Option2 = cheapRt(stations, step1, step2, limit, index + step1,
          sum + stations[index], route + " " + index);
      return Math.min(Option1, Option2);
    } else {
      return cheapRt(stations, step1, step2, limit, index + step1,
          sum + stations[index], route + " " + index);
    }
  }
}
