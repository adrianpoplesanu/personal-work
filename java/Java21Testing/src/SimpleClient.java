import java.io.*;
import java.net.Socket;

public class SimpleClient {
    public static void main(String argsp[]) throws IOException {
        Socket socket = new Socket("127.0.0.1", 8082);
        InputStream in = socket.getInputStream();
        PrintWriter pw = new PrintWriter(socket.getOutputStream());
        pw.println("buna dimineata!");
        pw.flush();
        byte[] buffer = new byte[1024];
        int read;
        while((read = in.read(buffer)) != -1) {
            String output = new String(buffer, 0, read);
            System.out.print(output);
            System.out.flush();
            break; // this breaks after the first read from server, for a continuous back and forth between client and server comment this
        }
        try {
            System.out.println("closing connection");
            socket.close();
        } catch(IOException e) {
            System.out.println(e);
        }
    }
}
