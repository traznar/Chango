package Code;

import java.io.BufferedInputStream;
import java.io.BufferedReader;
import java.io.DataInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.ObjectInputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;

public class Servidor {
	
    private int port = 8081;
    private Socket socket ;
    private ServerSocket serverSocket;
    private BufferedInputStream bis ;
    private DataInputStream dis ;

    public void print(String message) {
    	System.out.println(message + "\n");
    }
    public Servidor() {

        try {
        	
            ServerSocket servidor= new ServerSocket(port); //intenta hacer la conexion
            print("Server iniciado");

            while (true) {
                Socket puenteS = servidor.accept();
                if(puenteS.getInetAddress()!=null){
                	print("Cliente nuevo!");
                    InetAddress location=  puenteS.getInetAddress();
                    String IpRemota = location.getHostAddress();
                }

                // Aca leo la info que me envio el cliente, por el momento solo tiene un readline, pero deberia iterarse mas tarde
                
                InputStreamReader streamReader= new InputStreamReader(puenteS.getInputStream());
                BufferedReader reader= new BufferedReader(streamReader);
                puenteS.getOutputStream().write("Hola cliente \n".getBytes());
                
                //String value= reader.readLine();
                //print("@ Mensaje del cliente: "+ value);
                
                //cierro el socket y el reader
                reader.close();
                puenteS.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}
