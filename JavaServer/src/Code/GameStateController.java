package Code;


import Models.PlayerData;
import Models.ZonaDetectable;
import estructurasDatos.lista;
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
		
		int newX=data.posX+x;
		int newY=data.posY+y;
		
		if((newX>0 & newX<572 & newY >5 & newY < 565) && verifyrPlatformColl(newX,newY,data.getSize())) {
			data.posX=newX;
			data.posY=newY;
		}
		
	}
	
	public boolean verifyrPlatformColl(int newX, int newY,int size) {
		
		lista<ZonaDetectable> plataformas =gameData.getPlataformasObj();
		

		for(int i=0; i< plataformas.size(); i++) {
			
			ZonaDetectable plataforma=plataformas.get(i);
			int pX=plataforma.posX;
			int pY=plataforma.posY;
			int l =plataforma.getSize();
		    float tolerance=0.5f;
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
