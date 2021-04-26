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
		gameState="initialize";
		playerData= new PlayerData(12,555,1);
		lianasObj= new  lista<ZonaDetectable>();
		plataformasObj=new  lista<ZonaDetectable>();
		cocodrilosObj=new  lista<cocodrilo>();
		frutasObj=new  lista<Fruta>();
		dkMario = new DKMario(0,55,1);
		
		/*plataformasObj.add(new ZonaDetectable(0,605,150,false));
		plataformasObj.add(new ZonaDetectable(500,500,150,false));
		plataformasObj.add(new ZonaDetectable(300,300,150,false));
		plataformasObj.add(new ZonaDetectable(0,100,150,false));
		plataformasObj.add(new ZonaDetectable(420,190,150,false));
		
		frutasObj.add(new Fruta(100,100,1,100));
		frutasObj.add(new Fruta(200,100,1,100));
		frutasObj.add(new Fruta(100,200,1,100));
		
		cocodrilosObj.add(new cocodrilo("a",10,200,1));
		cocodrilosObj.add(new cocodrilo("a",70,300,1));
		cocodrilosObj.add(new cocodrilo("r",300,200,1));
		cocodrilosObj.add(new cocodrilo("r",100,700,1));*/
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
