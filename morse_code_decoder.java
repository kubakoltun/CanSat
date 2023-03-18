import java.util.HashMap;

public class MorseCodeDecoder {
  public static String decode(String morseCode) {
    HashMap<String, String> morseCodeTable = new HashMap<String, String>() {{
      put(".-", "A");
      put("-...", "B");
      put("-.-.", "C");
      put("-..", "D");
      put(".", "E");
      put("..-.", "F");
      put("--.", "G");
      put("....", "H");
      put("..", "I");
      put(".---", "J");
      put("-.-", "K");
      put(".-..", "L");
      put("--", "M");
      put("-.", "N");
      put("---", "O");
      put(".--.", "P");
      put("--.-", "Q");
      put(".-.", "R");
      put("...", "S");
      put("-", "T");
      put("..-", "U");
      put("...-", "V");
      put(".--", "W");
      put("-..-", "X");
      put("-.--", "Y");
      put("--..", "Z");
      put(".----", "1");
      put("..---", "2");
      put("...--", "3");
      put("....-", "4");
      put(".....", "5");
      put("-....", "6");
      put("--...", "7");
      put("---..", "8");
      put("----.", "9");
      put("-----", "0");
      put("...---...", "SOS");
      put("-.-.--", "!");
      put(".-.-.-", ".");
      put("--..--", ",");
    }};

    StringBuilder sb = new StringBuilder();
    String[] words = morseCode.trim().split(" {3}"); 
    for (String word : words) {
      String[] letters = word.split(" "); 
      for (String letter : letters) {
        sb.append(morseCodeTable.get(letter)); 
      }
      sb.append(" "); 
    }

    return sb.toString().trim();
  }
}
