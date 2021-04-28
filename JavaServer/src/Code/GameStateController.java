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
	
	
   public void makeCocodrilo(int tipo,int x, int y,ZonaDetectable liana){
    	gameData.getCocodrilosObj().add(new cocodrilo(tipo,x,y,1,liana));
    }
    public void makeFruta(int puntaje,int x, int y){
    	gameData.getFrutasObj().add(new Fruta(x,y,10,puntaje));
    }
    public void deleteFruta(int cont){
    	gameData.getFrutasObj().get(cont).posX=1000;
    }
    public void makeLiana(int size,int x, int y){
		gameData.getLianasObj().add(new ZonaDetectable(x,y,size));
    }
	/**
	 * @def update all objects position
	 */
	public void updateObjsPosition() {
		gameData.update();
	}
	/**
	 * @def moves the monkey
	 * @param x
	 * @param y
	 */
	public  void moverMono(float x, float y) {
		PlayerData data=gameData.getPlayerData();
		float size=data.getSize();
		float newX=data.posX+x;
		float newY=data.posY+y;	
		if((newX>0 & newX<572 & newY >5 & newY < 565) && verifyrPlatformColl(newX,newY,size,data.posX,data.posY)) {
			data.posX=newX;
			data.posY=newY;
			verifyFruitsColl(newX,newY,size);
			verifyEnemyColl(newX,newY,size);
			verifyAguaColl(newX,newY,size);
			verifyGanador(newX,newY,size);
			verifylianasColl(newX,newY,size);
		}
		
	}
	
	/**
	 * @def make a jump movement
	 * @param velocity
	 */
	public void jump( float velocity) {
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
	public void verifyEnemyColl(float newX, float newY,float size) {
		lista<cocodrilo> lagartos=gameData.getCocodrilosObj();
		for(int i=0; i< lagartos.size(); i++) {
			cocodrilo lagartillo=lagartos.get(i);
			float pX=lagartillo.posX;
			float pY=lagartillo.posY;
			float l =lagartillo.getSize();
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
	
	/**
	 * @def verifies collisions with water
	 * @param newX
	 * @param newY
	 * @param size
	 */
	public void verifyAguaColl(float newX, float newY,float size){
        if(newY>=555){
            gameData.getPlayerData().vidas--;
            if(gameData.getPlayerData().vidas<=0) {
                gameData.reset();
            }else {
                gameData.getPlayerData().setPosiX(12);
                gameData.getPlayerData().setPosiY(502);
            }
        }
    }
	//fruta (,x100,y130,50,)  && ((newY+size>=1) && (newY+size<=100) )
	public void verifyGanador(float newX, float newY,float size){
		// && ((newX+size>=130) && (newX<=130))
		if( ((newY+size>=80)&&(newY<=80)) && ((newX+size>=130) && (newX<=130)) ){
			gameData.reset();
			System.out.print("Gano");
		}
	}
	
	/**
	 * @def verifies collisions with fruits
	 * @param newX
	 * @param newY
	 * @param size
	 */
	public void verifyFruitsColl(float newX, float newY,float size) {
		lista<Fruta> frutas=gameData.getFrutasObj();
		for(int i=0; i< frutas.size(); i++) {
			Fruta frutilla=frutas.get(i);
			float pX=frutilla.posX;
			float pY=frutilla.posY;
			float l =frutilla.getSize();
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
	/**
	 * @def verifies collisions with lianas and allow grabbing
	 * @param newX
	 * @param newY
	 * @param size
	 */
	public void verifylianasColl(float newX, float newY,float size) {
		PlayerData data=gameData.getPlayerData();
		lista<ZonaDetectable> lianas =gameData.getLianasObj();
		for(int i=0; i< lianas.size(); i++) {
			ZonaDetectable liana=lianas.get(i);
			float pX=liana.posX;
			float pY=liana.posY;
			float l =liana.getSize();
		    float tolerance=30;
		    if(((newX+size)>pX && (newX<(pX)))){
				if(((newY<=(pY+l))&&(newY)>=pY)) {
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
	public boolean verifyrPlatformColl(float newX, float newY,float size,float oldX, float oldY) {
		lista<ZonaDetectable> plataformas =gameData.getPlataformasObj();
		for(int i=0; i< plataformas.size(); i++) {
			ZonaDetectable plataforma=plataformas.get(i);
			float pX=plataforma.posX;
			float pY=plataforma.posY;
			float l =plataforma.getSize();
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
