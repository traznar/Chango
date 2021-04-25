package Models;

import org.json.simple.JSONObject;

public class PlayerData extends ObjetosJuego{
	
	public int puntuacion;
	public int vidas;
	public String animation;
	
	public PlayerData(int posiX,int posiY,int size){
		super(posiX,posiY,size);
		this.puntuacion=0;
		this.vidas=3;
	}
	public String toJson() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("size", size);
		obj.put("puntuacion", puntuacion);
		obj.put("vidas", vidas);
		obj.put("animation", animation);
		
		return obj.toJSONString();

	}
}
