import java.net.ServerSocket;
import java.net.Socket;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Main {

    public static void main(String args[]) throws Exception{

        //System.out.println("Aguardando conexão na porta 8080");

        //ExecutorService threadPool = Executors.newFixedThreadPool(1000);

        Server serv = new Server();



    }

}
