import java.io.*;

class _a {
    public static void main(String[] args) throws FileNotFoundException {
        if (args.length > 0) {
            System.setOut(new PrintStream(new FileOutputStream(args[0])));
        }
        System.out.println("version " + liba.VERSION);
        System.out.println(liba.isqrt(1));
        System.out.println(liba.rsqrt(1));
    }
}
