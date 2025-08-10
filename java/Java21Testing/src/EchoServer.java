import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ServerSocket;
import java.net.Socket;

public class EchoServer {
    public static void main(String[] args) throws IOException {
        if (args.length != 1) {
            System.err.println("Usage: java EchoServer <port>");
            System.exit(1);
        }

        int portNumber = Integer.parseInt(args[0]);
        try (ServerSocket serverSocket = new ServerSocket(portNumber)) {
            System.out.println("EchoServer listening on port " + portNumber);

            while(true) {
                Socket clientSocket = serverSocket.accept();

                Thread.ofVirtual().start(() -> {
                   try (
                       PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                       BufferedReader in = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
                   ) {
                       String inputLine;
                       while((inputLine = in.readLine()) != null) {
                           System.out.println("Received: " + inputLine);
                           out.println("Echo: " + inputLine);
                           out.flush();
                       }
                   } catch (IOException e) {
                       e.printStackTrace();
                   } finally {
                       try {
                           System.out.println("closing connection");
                           clientSocket.close();
                       } catch (IOException e) {
                           e.printStackTrace();
                       }
                   }
                });
            }
        } catch (IOException e) {
            System.out.println("Exception listening on port " + portNumber + " or listening for  connection");
            System.out.println(e.getMessage());
        }
    }
}
