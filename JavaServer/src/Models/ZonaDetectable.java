package Models;

import org.json.simple.JSONObject;

/*
 * Es para tener las zonas de las lianas o plataformas 
 */
public class ZonaDetectable extends ObjetosJuego{
	
	public boolean interactuable;
	public ZonaDetectable(int posicionX,int posicionY,int size,boolean interactuable){
		super(posicionX,posicionY,size);
		
		this.interactuable=interactuable;
	}
	public String toJson() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);

		obj.put("interactuable", interactuable);
		return obj.toJSONString();
	}
}
