import java.util.*; 
import java.io.*;

  public static String searching_letters_in_words (String str) {
     String[] words = str.split("\\s+");
     String result = "-1";
     int countOcc = 0;

     for (int i = 0; i < words.length; i++) {
       String word = words[i];
       int[] occurs = new int[26];
       int reapetedLetters = 0;

       for (int j = 0; j < word.length(); j++) {
         char cr = Character.toLowerCase(word.charAt(j));
         
         if (cr >= 'a' && cr <= 'z') {
           occurs[cr - 'a']++;
           if (occurs[cr - 'a'] == 2) {
             reapetedLetters++;
           }
         }
       }

       if (reapetedLetters > countOcc) {
         result = word;
         countOcc = reapetedLetters;
       }
     }
    
    return result;
  }
