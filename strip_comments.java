public class strip_comments {
    public static String stripComments(String input, String[] markers) {
        String[] lines = input.split("\\n");
        String line = "";
        
        for (int i = 0; i < lines.length; i++) {
            line = lines[i];
            for (String marker : markers) {
                int commentIndex = line.indexOf(marker);
                if (commentIndex != -1) {
                    line = line.substring(0, commentIndex);
                }
            }
            line = line.replaceAll("\\s+$", "");
            lines[i] = line;
        }
        String output = String.join("\n", lines);;

        return output;
    }
}
