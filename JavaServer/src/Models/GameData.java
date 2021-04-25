package Models;

import org.json.simple.JSONArray;
import org.json.simple.JSONObject;
import java.util.*;
public class GameData {
	
	private String gameState;	
	private PlayerData playerData;
	private ArrayList<ZonaDetectable> lianasObj;
	private ArrayList<Fruta> frutasObj;
	private ArrayList<cocodrilo> cocodrilosObj;
	private ArrayList<ZonaDetectable> plataformasObj;
	private DKMario dkMario;
	 
	
	public GameData() {
		gameState="initialize";
		playerData= new PlayerData(0,0,1);
		lianasObj= new  ArrayList<ZonaDetectable>();
		plataformasObj=new  ArrayList<ZonaDetectable>();
		cocodrilosObj=new  ArrayList<cocodrilo>();
		frutasObj=new  ArrayList<Fruta>();
		
		dkMario = new DKMario(0,0,1);
	}
	
	@SuppressWarnings("unchecked")
	
	public String toJson() {
		
		
			JSONArray lianasj   = new JSONArray();
			JSONArray frutasj      = new JSONArray();
			JSONArray cocodrilosj  = new JSONArray();
			JSONArray plataformasj = new JSONArray();
			
			for(int i =0;i<lianasObj.size();i++) 
				lianasj.add(lianasObj.get(i).toJson());
			
			for(int i =0;i<frutasObj.size();i++) 
				frutasj.add(frutasObj.get(i).toJson());
			
			for(int i =0;i<cocodrilosObj.size();i++) 
				cocodrilosj.add(cocodrilosObj.get(i).toJson());
			
			for(int i =0;i<plataformasObj.size();i++) 
				plataformasj.add(plataformasObj.get(i).toJson());
		
			JSONObject obj = new JSONObject();
			
			obj.put("gameState", gameState);
			obj.put("playerData", playerData.toJson());
			obj.put("plataformas", plataformasj);
			
			obj.put("lianas", lianasj);
			obj.put("frutas", frutasj);
			obj.put("cocodrilos", cocodrilosj);
			
			obj.put("DK", dkMario.toJson());

			
		return obj.toJSONString();
		
	}
	
}
