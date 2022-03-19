public class CppLibrary2 {
    private native void print();

    public static void main(String[] args) {
        CppLibrary2 cppLibrary2 = new CppLibrary2();
        cppLibrary2.print();
    }

    static {
        System.loadLibrary("CppLibrary2");
    }
}
