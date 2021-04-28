package Code;


import Models.PlayerData;
import Models.ZonaDetectable;
import Models.cocodrilo;
import estructurasDatos.lista;
import Models.Fruta;
import Models.GameData;
import java.lang.Math;


public class GameStateController {

	private static GameStateController controller= new GameStateController();
	public  GameData gameData;
	
	
	private GameStateController () {
		gameData= new GameData();
	
	}
	
	public  String getGameData() {
		
		return gameData.toJson();
	}
	

	public static GameStateController getInstance() {

		return controller;
	}
	/**
	 * @def moves the monkey
	 * @param x
	 * @param y
	 */
	public  void moverMono(int x, int y) {
		PlayerData data=gameData.getPlayerData();
		int size=data.getSize();
		int newX=data.posX+x;
		int newY=data.posY+y;
		
		if((newX>0 & newX<572 & newY >5 & newY < 565) && verifyrPlatformColl(newX,newY,size,data.posX,data.posY)) {
			data.posX=newX;
			data.posY=newY;
			verifyFruitsColl(newX,newY,size);
			verifyEnemyColl(newX,newY,size);
			verifyAguaColl(newX,newY,size);
			verifylianasColl(newX,newY,size);
		}
		
	}
	
	public void jump( int velocity) {
		
		PlayerData data=gameData.getPlayerData();
		if(data.isGrab()) {
			moverMono(0,-velocity);
		}
		else {
			if(data.CanJump()) {
				moverMono(0,-5*velocity);
				data.setCanJump(false);
			}
		}
		
	}
	
	/**
	 * @def verifies collisions with enemies
	 * @param newX
	 * @param newY
	 * @param size
	 */
	public void verifyEnemyColl(int newX, int newY,int size) {
		lista<cocodrilo> lagartos=gameData.getCocodrilosObj();
		for(int i=0; i< lagartos.size(); i++) {
			cocodrilo lagartillo=lagartos.get(i);
			int pX=lagartillo.posX;
			int pY=lagartillo.posY;
			int l =lagartillo.getSize();
		    float h=15;
			if(((newX+size)<=pX || (newX>=(pX+l))) )
				continue;
			else {
				if(((newY>=(pY+h))||(newY+size-h)<=pY)) 
					continue;
				else{
					lagartillo.posX=1000000;
					gameData.setCocodrilosObj(lagartos);
					gameData.getPlayerData().vidas-=1;
					
					if(gameData.getPlayerData().vidas<=0) {
						gameData.reset();
					}
					}	
				}
		}
		
	}
	public void verifyAguaColl(int newX, int newY,int size){
        if(newY>=561){
            gameData.getPlayerData().vidas--;
            if(gameData.getPlayerData().vidas<=0) {
                gameData.reset();
            }else {
                gameData.getPlayerData().setPosiX(12);
                gameData.getPlayerData().setPosiY(502);
            }
        }
    }
	/**
	 * @def verifies collisions with fruits
	 * @param newX
	 * @param newY
	 * @param size
	 */
	public void verifyFruitsColl(int newX, int newY,int size) {
		lista<Fruta> frutas=gameData.getFrutasObj();
		for(int i=0; i< frutas.size(); i++) {
			Fruta frutilla=frutas.get(i);
			int pX=frutilla.posX;
			int pY=frutilla.posY;
			int l =frutilla.getSize();
		    float h=5;
			if(((newX+size)<=pX || (newX>=(pX+l))) )
				continue;
			else {
				if(((newY>=(pY+h))||(newY+size-h)<=pY)) 
					continue;
				else{
					
					frutilla.posX=1000000;
					gameData.setFrutasObj(frutas);
					gameData.getPlayerData().puntuacion+=frutilla.getPuntos();
					}	
				}
		}
		
	}
	public void verifylianasColl(int newX, int newY,int size) {
		PlayerData data=gameData.getPlayerData();
		lista<ZonaDetectable> lianas =gameData.getLianasObj();
		
		for(int i=0; i< lianas.size(); i++) {
			ZonaDetectable liana=lianas.get(i);
			int pX=liana.posX;
			int pY=liana.posY;
			int l =liana.getSize();
		    float h=5;
		    float tolerance=size;

		    if(Math.abs(newX+size-pX)<tolerance){
	
				if(Math.abs(newY+size-(pY+l))<tolerance) {

					data.setGrab(true);					
					return;
			
				}	
		    }

			
		}
		data.setGrab(false);

	}
	
	/**
	 * @def verifies collisions with platforms
	 * @param newX
	 * @param newY
	 * @param size
	 * @return boolean canIwalt To this position? 
	 */
	public boolean verifyrPlatformColl(int newX, int newY,int size,int oldX, int oldY) {
		
		lista<ZonaDetectable> plataformas =gameData.getPlataformasObj();
		

		for(int i=0; i< plataformas.size(); i++) {
			ZonaDetectable plataforma=plataformas.get(i);
			int pX=plataforma.posX;
			int pY=plataforma.posY;
			int l =plataforma.getSize();
		    float h=5;
		    float tolerance=6;
		    
		    if(((oldX+size)>pX && (oldX<(pX+l)))){
		    	
				if(Math.abs((oldY+size)-(pY+h))<tolerance && oldY<pY) {
					PlayerData data=gameData.getPlayerData();

					data.setCanJump(true);					
			
				}	
		    }

			if(((newX+size)<=pX || (newX>=(pX+l))) )
				continue;
			else {
				if(((newY>=(pY+h))||(newY+size-h)<=pY)) 
					continue;
				else
					return false;
					
				
			}				
		}
		return true;

	}

}
