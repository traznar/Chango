package Code;
import java.util.Scanner;

import Models.Fruta;
import Models.cocodrilo;
public class JugadorSecundario extends Thread{
	int cont=0;
	public GameStateController controller;
	public JugadorSecundario(GameStateController c){
		controller=c;
	}
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
    		String key=arr[0];
			String[] arrRes = res.split(",");
			switch(key){
				case "cocodrilo":
	    			controller.makeCocodrilo(Integer.parseInt(arrRes[1]), Integer.parseInt(arrRes[2]), Integer.parseInt(arrRes[3]),
	    			controller.gameData.getLianasObj().get(Integer.parseInt(arrRes[4])));
				case "fruta":
					if( Integer.parseInt(arrRes[4])==0){
						controller.makeFruta(Integer.parseInt(arrRes[1]), Integer.parseInt(arrRes[2]), Integer.parseInt(arrRes[3]));
					}else {
						controller.deleteFruta(cont);
						cont++;
					};			
			}
    	}else{
    		System.out.println("error de sintaxis: revise el manual de usuario");
    	}
    }
}

//cocodrilo (,1,20,200,1,)
//fruta (,100,130,500,0,)