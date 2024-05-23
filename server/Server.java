import java.io.*;
import java.net.*;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;

public class Server {
    public static void main(String args[]) throws Exception {
        String fromClient;
        String toClient;

        ServerSocket server = new ServerSocket(8080);
        System.out.println("Aguardando conexão na porta 8080");

        boolean run = true;
        while(run) {
            Socket client = server.accept();
            System.out.println("Conexão efetuada na porta 8080");
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));
            PrintWriter out = new PrintWriter(client.getOutputStream(),true);

            fromClient = in.readLine();
            System.out.println("recebido do cliente: " + fromClient);

            if(fromClient.equals("/produtosLista")) {

                try{

                    Object obj = new JSONParser().parse(new FileReader("utils/cadastroProdutos.json"));

                    // typecasting obj to JSONObject
                    JSONObject jo = (JSONObject) obj;

                    JSONObject json = (JSONObject) obj;

                    System.out.println("enviado json");
                    out.println(json);
                }
                catch(Exception e){
                    System.out.println(e);
                }
            }
            if(fromClient.equals("/visualizarCarrinho")) {
                toClient = "Carrinho vazio";
                System.out.println("enviado carrinho vazio");
                out.println(toClient);
            }
            else {
                toClient = fromClient;
                out.println(toClient);
                System.out.println("send "+toClient);
                if(fromClient.equals("Bye")) {
                    toClient = "Tchau";
                    System.out.println("send Tchau");
                    out.println(toClient);
                    client.close();
                    run = false;
                    System.out.println("socket closed");
                }
            }

        }
        System.exit(0);
    }
}