import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class diff_lett_words {
    public static void main(String[] args) {
        String book = "schultz_sklepy_cynamonowe_UTF8.txt";
        //String book = "melville_moby_dick.txt";
        //String book = "tekst_test.txt";
        int minLen = 5;
        try (Stream<String> lines =
                     Files.lines(Paths.get(book)))

        {
            Map<Integer,List<String>> map =
                    lines
                        .flatMap(line -> Stream.of(line.split(" ")))
                        .map(e -> e.replaceAll("[.,-]", ""))
                        .filter(e -> {
                            e = e.toLowerCase();
                                if (e.length() >= minLen) {
                                    return e.length() == e.chars().distinct().toArray().length;
                                }
                                return false;
                            })
                        .sorted()
                        .distinct()
                        .collect(Collectors.groupingBy(String::length));

            List<Integer> lastTwo =
                    map.keySet().stream().sorted()
                    .collect(Collectors.toList());
            System.out.println("Two lists of the longest " +
                    "words with all letters different:");
            int len = lastTwo.get(lastTwo.size()-2);
            System.out.println("length " + len + ": " +
                    map.get(len));
            len = lastTwo.get(lastTwo.size()-1);
            System.out.println("length " + len + ": " +
                    map.get(len));
        }

        catch(IOException e) {
            System.out.println("Something wrong...");
            e.printStackTrace();
            System.exit(1);
        }
    }
}
