import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.net.Socket;

public class ClientApplication {


    public static void main(String args[]) throws IOException {
        Socket socket = new Socket("127.0.0.1", 9090);
        DataInputStream input  = new DataInputStream(System.in);
        DataOutputStream out = new DataOutputStream(socket.getOutputStream());

        out.writeUTF("caca maca");

        input.close();
        out.close();
        socket.close();
    }
}
