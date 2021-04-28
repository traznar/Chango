package Code;
import java.util.Scanner;

import Models.cocodrilo;
public class JugadorSecundario extends Thread{
	
	public Servidor Serv;
	public JugadorSecundario(){}
    public void run(){
    	while(true){
    		System.out.println("->:");
    		Scanner myObj = new Scanner(System.in);
    		String name = myObj.nextLine().toLowerCase();
    		parcearText(name);
    	}
    }
    public void parcearText(String text){
    	String[] arr = text.split(" ");
    	if( (arr.length<3) && (arr.length>1) ){
    		String res=arr[1];
			String[] arrRes = res.split(",");
    		if( arr[0].equals("cocodrilo") ){
    			Serv.makeCocodrilo(Integer.parseInt(arrRes[2]), Integer.parseInt(arrRes[3]), Integer.parseInt(arrRes[4]));
    		}else if( arr[0].equals("fruta") ){
    			Serv.doFruta(Integer.parseInt(arrRes[2]), Integer.parseInt(arrRes[3]), Integer.parseInt(arrRes[4]));
    		}else{
    			System.out.println("Eliminar fruta");
    		}
    	}else{
    		System.out.println("error");
    	}
    }
}

//cocodrilo (,192.168.0.15,1,20,200,)
//fruta (,192.168.0.15,1,20,200,)