package Models;

import org.json.simple.JSONObject;

public class Fruta extends ObjetosJuego{
	public static int puntos;
	
	public Fruta(int posicionX,int posicionY,int size, int pts){
		super(posicionX,posicionY,size);
		
		this.puntos=pts;
	}
	public int getPuntos(){
		return puntos;
	}
	@Override
	public String toJson() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("size", size);
		return obj.toJSONString();
	}
}
