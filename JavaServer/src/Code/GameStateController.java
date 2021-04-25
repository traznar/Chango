package Code;



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

}
