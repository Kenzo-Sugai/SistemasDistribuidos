import java.io.*;
import java.net.*;
import java.time.format.*;
import java.util.*;
import java.time.*;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import org.json.simple.parser.*;

public class Server  {

    public Server() throws IOException {
        ServerSocket server = new ServerSocket(8080);

        ExecutorService threadPool = Executors.newFixedThreadPool(1000);
        while(true) {
            Socket client = server.accept();
            //System.out.println("Conexão efetuada na porta 8080");
            threadPool.execute(() -> run(client));
            //run(client);
        }
    }

    public void criarCarrinho(String fromClient, String toClient, PrintWriter out){

        String param = fromClient.replace("/criarCarrinho ", "");
        //System.out.println(param);
        try {
            JSONParser parser = new JSONParser();
            JSONObject json = (JSONObject) parser.parse(param);
            Object Usuario = json.get("usuario");
            toClient = "Criado carrinho para o usuario" + Usuario;
            String pathname = "carrinhos\\" + Usuario + ".txt";
            File fileObj = new File(pathname);
            //System.out.println(fileObj.getName());

            out.println(toClient);


        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void visualizarExtrato(String fromClient, String toClient, PrintWriter out) throws FileNotFoundException {
        File FileObj = new File("extrato.txt");

        if (FileObj.exists()) {

            Scanner input = new Scanner(FileObj);

            String response = "";

            while (input.hasNextLine()) {
                String data = input.nextLine();

                response += (data + '\n');
            }

            input.close();

            out.println(response);
        } else {
            out.println("Sem extrato disponivel");
        }
    }

    public void listaProdutos(String fromClient, String toClient, PrintWriter out) {
        try {

            Object obj = new JSONParser().parse(new FileReader("utils/cadastroProdutos.json"));

            JSONObject jo = (JSONObject) obj;

            JSONObject json = (JSONObject) obj;

            //System.out.println("enviado json");
            out.println(json);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void visualizaCarrinho(String fromClient, String toClient, PrintWriter out) throws ParseException, FileNotFoundException {
        String param = fromClient.replace("/visualizarCarrinho ", "");

        JSONParser parser = new JSONParser();
        JSONObject json = (JSONObject) parser.parse(param);

        Object Usuario = json.get("usuario");
        String pathname = "carrinhos\\" + Usuario + ".txt";
        File FileObj = new File(pathname);

        if (FileObj.exists()) {

            int linhas = 0;
            toClient = "";

            Scanner input = new Scanner(FileObj);
            while (input.hasNextLine()) {
                linhas += 1;

                String data = input.nextLine();

                String Produto = data.substring(0, 5);
                int Quantidade = Integer.parseInt(data.substring(6, data.length()));

                String prod = "Produto: " + Produto + " | Quantidade: " + Quantidade + '\n';

                //System.out.println(prod);

                toClient += prod;
            }

            if (linhas == 0) {
                toClient = "Carrinho vazio";
            }

            input.close();

            out.println(toClient);
        } else {
            out.println("Carrinho vazio");
        }
    }

    public synchronized void adicionarCarrinho(String fromClient, String toClient, PrintWriter out){
        String param = fromClient.replace("/adicionarCarrinho ", "");
        //System.out.println(param);
        try {
            JSONParser parser = new JSONParser();
            JSONObject json = (JSONObject) parser.parse(param);

            toClient = "Adicionado produto " + json.get("id") + " com quantidade: " + json.get("quantidade");

            Object Usuario = json.get("usuario");
            String pathname = "carrinhos\\" + Usuario + ".txt";
            String texto = json.get("id") + " " + json.get("quantidade");

            synchronized (this) {
                FileWriter objWriter = new FileWriter(pathname, true);
                BufferedWriter objBuffer = new BufferedWriter(objWriter);
                objBuffer.write(texto);
                objBuffer.newLine();
                objBuffer.close();
                objWriter.close();
            }
            out.println(toClient);
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public synchronized void finalizarCompra(String fromClient, String toClient, PrintWriter out) {


        String param = fromClient.replace("/finalizarCompra ", "");

        try {

            JSONParser parser = new JSONParser();
            JSONObject json = (JSONObject) parser.parse(param);

            Object Usuario = json.get("usuario");
            String pathname = "carrinhos\\" + Usuario + ".txt";
            File Carrinho = new File(pathname);

            JSONObject cadastroJson = readJson(parser); // json temporario para escrita

            synchronized (this) {

                String extratoTexto = "";

                Scanner input = new Scanner(Carrinho);
                while (input.hasNextLine()) {
                    String data = input.nextLine();
                    String Produto = data.substring(0, 5);
                    int Quantidade = Integer.parseInt(data.substring(6, data.length()));

                    // captura APENAS o produto
                    JSONObject ProdutoJson = (JSONObject) cadastroJson.get("Prod-" + Produto);
                    long QuantidadeAtual = (long) ProdutoJson.get("Estoque"); // captura estoque atual do json
                    long QuantidadeFinal = QuantidadeAtual - Quantidade;
                    if (QuantidadeFinal >= 0) { // verifica se ainda existe quantidade disponível

                        System.out.println(Usuario+" Comprou o produto "+Produto);

                        ProdutoJson.put("Estoque", QuantidadeFinal);
                        String texto =
                                Usuario + " " +
                                        Produto + " " +
                                        Quantidade + " " +
                                        ProdutoJson.get("Nome") + " " + '\n';

                        extratoTexto += texto;
                    } else {
                        System.out.println("ERRO! " + Usuario + ": Produto " + Produto + " fora do estoque");
                    }
                }
                input.close();

                writejson(cadastroJson);
                writeExtrato(extratoTexto);
            }

            Carrinho.delete();

            toClient = "Compra finalizada!";

            out.println(toClient);

        } catch (Exception e) {
            System.out.println(e);
        }

    }

    public synchronized JSONObject readJson(JSONParser parser) throws IOException, ParseException {

        FileReader reader = new FileReader("utils/cadastroProdutos.json");
        JSONObject jsonObject = (JSONObject) parser.parse(reader);
        reader.close();

        return jsonObject;


    }

    public synchronized void writejson(JSONObject jsonObject) throws IOException {

        FileWriter writer = new FileWriter("utils/cadastroProdutos.json");
        writer.write(jsonObject.toJSONString());
        writer.close();

    }

    public synchronized void writeExtrato(String texto) throws IOException {

        FileWriter objWriter = new FileWriter("extrato.txt", true);
        BufferedWriter objBuffer = new BufferedWriter(objWriter);

        objBuffer.write(texto);

        objBuffer.close();
        objWriter.close();

    }

    public synchronized BufferedReader bufferedReaderSync(Socket client) throws IOException {

        return new BufferedReader(new InputStreamReader(client.getInputStream()));

    }

    public void run(Socket client) {

        try {

            String fromClient;
            String toClient = "";

            BufferedReader in = bufferedReaderSync(client);
            PrintWriter out = new PrintWriter(client.getOutputStream(), true);

            fromClient = in.readLine();
            System.out.println("recebido do cliente: " + fromClient);

            if (fromClient.contains("/criarCarrinho")) {
                criarCarrinho(fromClient, toClient, out);
            } else if (fromClient.equals("/visualizarExtrato")) {
                visualizarExtrato(fromClient, toClient, out);
            } else if (fromClient.equals("/produtosLista")) {
                listaProdutos(fromClient, toClient, out);
            } else if (fromClient.contains("/visualizarCarrinho")) {
                visualizaCarrinho(fromClient, toClient, out);
            } else if (fromClient.contains("/adicionarCarrinho")) {
                adicionarCarrinho(fromClient, toClient, out);
            } else if (fromClient.contains("/finalizarCompra")) {
                finalizarCompra(fromClient, toClient, out);
            } else {
                toClient = fromClient;
                out.println(toClient);
                System.out.println("send " + toClient);
                if (fromClient.equals("Bye")) {
                    toClient = "Tchau";
                    System.out.println("send Tchau");
                    out.println(toClient);
                    client.close();
                    System.out.println("socket closed");
                }
            }


        } catch (Exception e) {
            System.out.println(e);
        }
    }
}
