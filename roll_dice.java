import java.util.Iterator;
import java.util.Random;

public class roll_dice {
public static class Roll implements Iterable<Integer> {
    private int prv, now, clo;

    @Override
    public Iterator<Integer> iterator() {
        Random rnm = new Random();
        return new Iterator<Integer>() {

            @Override
            public boolean hasNext() {
                return prv + now + clo != 11;
            }

            @Override
            public Integer next() {
                clo = prv;
                prv = now;
                now = 1 + rnm.nextInt(6);
                return now;
            }
        };
    }
}

    public static void main(String[] args) {
        for (int turn = 0; turn < 10; ++turn) {
            for (Integer i : new Roll())
                System.out.print(i + " ");
            System.out.println();
        }
    }
}
