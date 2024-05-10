/*This is Suujiquiz, a program meant to help japanese learner convert numbers in
 * their head fast. */
import java.util.Random;

public class Counter {
  public String count_num(long num) {
    Map<Integer, String> KanjiMap = new HashMap<Integer, String>() {
      {
        put(1, "一");
        put(2, "二");
        put(3, "三");
        put(4, "四");
        put(5, "五");
        put(6, "六");
        put(7, "七");
        put(8, "八");
        put(9, "九");
      }
    };
    int man = num / 10000;
    num %= 10000;
    int hyaku = num / 100;
    num %= 100;
    int jyuu = num / 10;
    num %= 10;
    int ichi = num;

    String res = "";
    if (man / 1000 > 0) {
      res += KanjiMap.get(man / 1000) + "千";
      man / 1000;
    }
    if (man / 100 > 0) {
      res += KanjiMap.get(man / 100) + "百";
      man / 100;
    }

    if (man / 10 > 0) {
      res += KanjiMap.get(man / 10) + "十";
      man / 10;
    }

    if (man > 0) {
      res += KanjiMap.get(man) + "万";
    }
    res += KanjiMap.get(hyaku) + "百";
    res += KanjiMap.get(jyuu) + "十";
    res += KanjiMap.get(ichi);
  }
}
// Visitor interface
interface RandomVisitor {
  String print_num;
}
}

// Concrete visitors
class HundredThousandRandomVisitor implements RandomVisitor {
  @Override
  public String print_num(int num) {
    String res = Counter.count_num(num);
    System.out.println(res + "?");
  }

  public static void main(String[] args) {
    int num = random.nextInt(100000, 999999);
    print_num(num);
  }
}

class OnesMillionRandomVisitor implements RandomVisitor {
  @Override
  public int visit() {
    Random random = new Random();
    return random.nextInt(1000000, 9999999);
  }
}

class TensMillionRandomVisitor implements RandomVisitor {
  @Override
  public int visit() {
    Random random = new Random();
    return random.nextInt(10000000, 99999999);
  }
}

// Random class modified to accept visitor
class RandomGenerator {
  static int generateRandom(RandomVisitor visitor) { return visitor.visit(); }
}

public class Main {
  public static void main(String[] args) {
    // Usage examples
    HundredThousandRandomVisitor hundredThousandVisitor =
        new HundredThousandRandomVisitor();
    int hundredThousandRandom =
        RandomGenerator.generateRandom(hundredThousandVisitor);
    System.out.println("Hundred Thousand Random: " + hundredThousandRandom);

    OnesMillionRandomVisitor onesMillionVisitor =
        new OnesMillionRandomVisitor();
    int onesMillionRandom = RandomGenerator.generateRandom(onesMillionVisitor);
    System.out.println("Ones Million Random: " + onesMillionRandom);

    TensMillionRandomVisitor tensMillionVisitor =
        new TensMillionRandomVisitor();
    int tensMillionRandom = RandomGenerator.generateRandom(tensMillionVisitor);
    System.out.println("Tens Million Random: " + tensMillionRandom);
  }
}
