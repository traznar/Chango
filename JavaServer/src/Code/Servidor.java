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
    private GameStateController controller;
    int velocity= 10;
    public void print(String message) {
    	System.out.println(message + "\n");
    }
    public Servidor() {
    	processCalls();
    }
    
  
    /**
     * @def processCalls do the server is listenning for connections, respond to request and process client data
     * @param servidor
     */
    public void processCalls() {
    	  try {
              ServerSocket servidor= new ServerSocket(port); //intenta hacer la conexion
              print("Server iniciado");
              controller=GameStateController.getInstance(); 
          

              while (true) {
                  Socket puenteS = servidor.accept();
                  if(puenteS.getInetAddress()!=null){
                  	
                      InetAddress location=  puenteS.getInetAddress();
                      String IpRemota = location.getHostAddress();
                  }

                  // Aca leo la info que me envio el cliente, por el momento solo tiene un readline, pero deberia iterarse mas tarde
                  
                  InputStreamReader streamReader= new InputStreamReader(puenteS.getInputStream());
                  BufferedReader reader= new BufferedReader(streamReader);
                  
                  	
                  
                  puenteS.getOutputStream().write((controller.getGameData()+ "\n").getBytes());  
                  String value= reader.readLine();
                  //print(value);
                  procesClientRequest(value);
                  gravityAction();
         
                  

                  reader.close();
                  puenteS.close();
              }
          } catch (IOException e) {
              e.printStackTrace();
          }
    }
    /**
     * @def simulate gravity action
     */
    public void gravityAction() {
    	controller.moverMono(0, velocity);
    }
    
    /**
     * @def process the client request
     * @param request
     */
    public void procesClientRequest(String request){
    	
    	
        if(request.compareTo("up")==0)
            	controller.jump(-5*velocity);      	
        if(request.compareTo("down")==0)  
        	controller.moverMono(0, velocity);
        if(request.compareTo("left")==0)  
        	controller.moverMono(-velocity, 0);
        if(request.compareTo("rigth")==0)  
        	controller.moverMono(velocity, 00);
        	
    }

}
