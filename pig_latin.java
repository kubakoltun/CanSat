public class pig_latin {
    public static String pigIt(String str) {
        String[] words = str.split(" ");
        String[] newWords = new String[words.length];
        char holdString = ' ';

        for (int j = 0; j < words.length; j++) {
          newWords[j] = "";
            
            for (int i = 0; i < words[j].length(); i++) {
                if (i == 0) {
                    holdString = words[j].charAt(i);
                } else {
                    newWords[j] += words[j].charAt(i);
                }

                if (i == words[j].length()-1) {
                    newWords[j] += holdString;
                  if (Character.isLetter(words[j].charAt(i))) {
                    newWords[j] += "ay";
                  }
                }
            }
        }

        return String.join(" ", newWords);
    }
}
