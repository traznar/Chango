package Models;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

import estructurasDatos.lista;

import java.util.*;
public class GameData {
	
	private String gameState;	
	private PlayerData playerData;
	private lista<ZonaDetectable> lianasObj;
	private lista<Fruta> frutasObj;
	private lista<cocodrilo> cocodrilosObj;
	private lista<ZonaDetectable> plataformasObj;
	private DKMario dkMario;
	 
	
	public GameData() {
		reset();
	}
	/**
	 * @def reset initializes all objects coordinates
	 */
	public void reset() {
		gameState="initialize";
		playerData= new PlayerData(12,502,48);
		lianasObj= new  lista<ZonaDetectable>();
		plataformasObj=new  lista<ZonaDetectable>();
		cocodrilosObj=new  lista<cocodrilo>();
		frutasObj=new  lista<Fruta>();
		dkMario = new DKMario(0,55,1);
		
		plataformasObj.add(new ZonaDetectable(40,400,150));
		plataformasObj.add(new ZonaDetectable(0,550,150));
		plataformasObj.add(new ZonaDetectable(500,500,150));
		plataformasObj.add(new ZonaDetectable(300,300,150));
		plataformasObj.add(new ZonaDetectable(0,100,320));
		plataformasObj.add(new ZonaDetectable(420,190,150));
		
		frutasObj.add(new Fruta(100,150,10,100));
		frutasObj.add(new Fruta(200,550,10,100));
		frutasObj.add(new Fruta(150,200,10,100));
		
		cocodrilosObj.add(new cocodrilo(0,10,200,1));//azul 0 y rojo 1
		cocodrilosObj.add(new cocodrilo(0,70,300,1));
		cocodrilosObj.add(new cocodrilo(1,300,200,1));
		cocodrilosObj.add(new cocodrilo(1,100,700,1));
		
		lianasObj.add(new ZonaDetectable(40 ,400,150));
		lianasObj.add(new ZonaDetectable(190,400,200));
		lianasObj.add(new ZonaDetectable(230,100,380));
		lianasObj.add(new ZonaDetectable(330,0,280));
	
	}
	@SuppressWarnings("unchecked")
	/**
	 * @def converts gameData to Json format
	 * @return
	 */
	public String toJson() {
		
		
			JSONArray lianasj      = new JSONArray();
			JSONArray frutasj      = new JSONArray();
			JSONArray cocodrilosj  = new JSONArray();
			JSONArray plataformasj = new JSONArray();
			
			for(int i =0;i<lianasObj.size();i++) 
				lianasj.add(lianasObj.get(i).toJsonObj());
			
			for(int i =0;i<frutasObj.size();i++) 
				frutasj.add(frutasObj.get(i).toJsonObj());
			
			for(int i =0;i<cocodrilosObj.size();i++) 
				cocodrilosj.add(cocodrilosObj.get(i).toJsonObj());
			
			for(int i =0;i<plataformasObj.size();i++) 
				plataformasj.add(plataformasObj.get(i).toJsonObj());
		
			JSONObject obj = new JSONObject();
			
			obj.put("gameState", gameState);
			obj.put("playerData", playerData.toJsonString());
			obj.put("plataformas", plataformasj.toJSONString());
			
			obj.put("lianas", lianasj.toJSONString());
			obj.put("frutas", frutasj.toJSONString());
			obj.put("cocodrilos", cocodrilosj.toJSONString());
			
			obj.put("DK", dkMario.toJsonString());

			
		return obj.toJSONString();
		
	}
	public String getGameState() {
		return gameState;
	}

	public void setGameState(String gameState) {
		this.gameState = gameState;
	}

	public PlayerData getPlayerData() {
		return playerData;
	}

	public void setPlayerData(PlayerData playerData) {
		this.playerData = playerData;
	}

	public lista<ZonaDetectable> getLianasObj() {
		return lianasObj;
	}

	public void setLianasObj(lista<ZonaDetectable> lianasObj) {
		this.lianasObj = lianasObj;
	}

	public lista<Fruta> getFrutasObj() {
		return frutasObj;
	}

	public void setFrutasObj(lista<Fruta> frutasObj) {
		this.frutasObj = frutasObj;
	}

	public lista<cocodrilo> getCocodrilosObj() {
		return cocodrilosObj;
	}

	public void setCocodrilosObj(lista<cocodrilo> cocodrilosObj) {
		this.cocodrilosObj = cocodrilosObj;
	}

	public lista<ZonaDetectable> getPlataformasObj() {
		return plataformasObj;
	}

	public void setPlataformasObj(lista<ZonaDetectable> plataformasObj) {
		this.plataformasObj = plataformasObj;
	}

	public DKMario getDkMario() {
		return dkMario;
	}

	public void setDkMario(DKMario dkMario) {
		this.dkMario = dkMario;
	}
	
}
