package Models;

import org.json.simple.JSONObject;

/*
 * Es para tener las zonas de las lianas o plataformas 
 */
public class ZonaDetectable extends ObjetosJuego{
	public String nombre;
	public boolean interactuable;
	public ZonaDetectable(String nombre,int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);
		this.nombre=nombre;
	}
	public String toJson() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("size", size);
		obj.put("nombre", nombre);
		obj.put("interactuable", interactuable);
		return obj.toJSONString();
	}
}
