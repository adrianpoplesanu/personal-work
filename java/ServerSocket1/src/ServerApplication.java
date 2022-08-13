import java.io.BufferedInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerApplication {
    //private String address = "127.0.0.1";
    private int port = 9090;

    private class Worker implements Runnable {

        @Override
        public void run() {
            System.out.println("something happened");
        }
    }

    private void loop() throws IOException {
        ServerSocket server = new ServerSocket(port);

        while(true) {
            Socket socket = server.accept();

            DataInputStream in = new DataInputStream(
                    new BufferedInputStream(socket.getInputStream()));

            String command = in.readUTF();
            while(true) {
                System.out.println(command);
                try {
                    command = in.readUTF();
                } catch(Exception e) {
                    break;
                }
            }

            socket.close();
            in.close();
        }
    }

    public static void main(String[] args) throws IOException {
        ServerApplication serverApplication = new ServerApplication();
        serverApplication.loop();
    }
}
