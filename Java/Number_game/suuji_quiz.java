/*
 * This is Suujiquiz, a game to help Japanese learners practice converting
 * numbers from their kanji representations to Hindu-Arabic numerals quickly in
 * their heads.
 */

import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;

class Counter {
  private static final Map<Integer, String> KANJI_MAP =
      new HashMap<Integer, String>() {
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

  public static String countNum(long num) {
    StringBuilder res = new StringBuilder();
    int man = (int)(num / 10000);
    num %= 10000;
    int sen = (int)(num / 1000);
    num %= 1000;
    int hyaku = (int)(num / 100);
    num %= 100;
    int jyuu = (int)(num / 10);
    num %= 10;
    int ichi = (int)num;

    if (man > 0) {
      appendKanjiDigit(res, man / 1000, "千");
      appendKanjiDigit(res, (man / 100) % 10, "百");
      appendKanjiDigit(res, (man / 10) % 10, "十");
      if (man % 10 == 0) {
        res.append("万");
      } else {
        appendKanjiDigit(res, man % 10, "万");
      }
    }

    appendKanjiDigit(res, sen, "千");
    appendKanjiDigit(res, hyaku, "百");
    appendKanjiDigit(res, jyuu, "十");
    appendKanjiDigit(res, ichi, "");

    return res.toString();
  }

  private static void appendKanjiDigit(StringBuilder res, int digit,
                                       String suffix) {
    if (digit > 0) {
      res.append(KANJI_MAP.get(digit)).append(suffix);
    }
  }
}

interface RandomVisitor {
  int visit();
}

class HundredThousandRandomVisitor implements RandomVisitor {
  @Override
  public int visit() {
    Random random = new Random();
    return random.nextInt(100000, 999999);
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

class RandomGenerator {
  static int generateRandom(RandomVisitor visitor) { return visitor.visit(); }
}

class Main {
  public static void main(String[] args) {
    Scanner scanner = new Scanner(System.in);
    boolean shouldContinue = true;

    while (shouldContinue) {
      System.out.println("Choose a mode: 1. Hundred Thousand, 2. Ones "
                         + "Million, 3. Tens Million, 0. Exit");
      int mode = scanner.nextInt();

      switch (mode) {
      case 1:
        playGame(new HundredThousandRandomVisitor(), scanner);
        break;
      case 2:
        playGame(new OnesMillionRandomVisitor(), scanner);
        break;
      case 3:
        playGame(new TensMillionRandomVisitor(), scanner);
        break;
      case 0:
        shouldContinue = false;
        break;
      default:
        System.out.println("Invalid mode selected. Please try again.");
      }
    }

    scanner.close();
  }

  private static void playGame(RandomVisitor visitor, Scanner scanner) {
    int randomNumber = RandomGenerator.generateRandom(visitor);
    String kanjiRepresentation = Counter.countNum(randomNumber);
    System.out.println("Convert the following kanji to a number: \n" +
                       kanjiRepresentation);

    int userAnswer = scanner.nextInt();

    if (userAnswer == randomNumber) {
      System.out.println("Correct!");
    } else {
      System.out.println("Incorrect. The correct answer is: " + randomNumber);
    }
  }
}
