package Code;


import Models.PlayerData;
import Models.ZonaDetectable;
import Models.cocodrilo;
import estructurasDatos.lista;
import Models.Fruta;
import Models.GameData;

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
	
	public  void moverMono(int x, int y) {
		PlayerData data=gameData.getPlayerData();
		int size=data.getSize();
		int newX=data.posX+x;
		int newY=data.posY+y;
		
		if((newX>0 & newX<572 & newY >5 & newY < 565) && verifyrPlatformColl(newX,newY,size)) {
			data.posX=newX;
			data.posY=newY;
			verifyFruitsColl(newX,newY,size);
			verifyEnemyColl(newX,newY,size);
		}
		
	}
	
	
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
	
	
	public void verifyFruitsColl(int newX, int newY,int size) {
		lista<Fruta> frutas=gameData.getFrutasObj();
		for(int i=0; i< frutas.size(); i++) {
			Fruta frutilla=frutas.get(i);
			int pX=frutilla.posX;
			int pY=frutilla.posY;
			int l =frutilla.getSize();
		    float h=15;
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
	
	public boolean verifyrPlatformColl(int newX, int newY,int size) {
		
		lista<ZonaDetectable> plataformas =gameData.getPlataformasObj();
		

		for(int i=0; i< plataformas.size(); i++) {
			ZonaDetectable plataforma=plataformas.get(i);
			int pX=plataforma.posX;
			int pY=plataforma.posY;
			int l =plataforma.getSize();
		    float h=15;
		    
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
