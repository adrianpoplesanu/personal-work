import com.sun.jna.Native;

public class NativeCodeRunner {
    private CppLibrary cppLibrary;

    public NativeCodeRunner() {
        //System.load(this.getClass().getResource("/Users/adrianpoplesanu/Documents/git-projects/personal-work/java/NativeProject2/bin/test.dylib").getFile());
        cppLibrary = Native.load("/Users/adrianpoplesanu/Documents/git-projects/personal-work/java/NativeProject2/bin/test.jnilib", CppLibrary.class);
    }

    public void test() {
        cppLibrary.test();
    }

    public static void main(String[] args) {
        NativeCodeRunner nativeCodeRunner = new NativeCodeRunner();
        nativeCodeRunner.test();
    }
}
