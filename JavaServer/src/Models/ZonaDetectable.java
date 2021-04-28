package Models;

import org.json.simple.JSONObject;

/*
 * Es para tener las zonas de las lianas o plataformas 
 */
public class ZonaDetectable extends ObjetosJuego{
	

	public ZonaDetectable(int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);

	}
	public String toJsonString() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);

		return obj.toJSONString();
	}
	@Override
	public JSONObject toJsonObj() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		
		obj.put("size", size);
		return obj;
	}

}
