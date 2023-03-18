public class StripComments {
    //does not work properly yet
    public static String stripComments(String input, String[] markers) {
        String[] lines = input.split("\n");
        for (int i = 0; i < lines.length; i++) {
            String line = lines[i];
            for (String marker : markers) {
                int commentIndex = line.indexOf(marker);
                if (commentIndex != -1) {
                    line = line.substring(0, commentIndex);
                }
            }
            line = line.replaceAll("\\s+$", "");
            lines[i] = line;
        }

        StringBuilder outputBuilder = new StringBuilder();
        for (int i = 0; i < lines.length; i++) {
            String line = lines[i];
            if (line.trim().length() > 0 || i == lines.length - 1) {
                outputBuilder.append(line);
                if (i < lines.length - 1) {
                    outputBuilder.append("\n");
                }
            }
        }

        String output = outputBuilder.toString();
        return output;
    }
}
