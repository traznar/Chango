package Models;

import org.json.simple.JSONObject;

public class cocodrilo extends ObjetosJuego{
	
	public boolean direccionX;
	public boolean direccionY;
	public int type;
	
	public cocodrilo(int nombre,int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);
		this.type=nombre;
		this.direccionX=false;
		this.direccionY=false;
		//definirTypo(nombre);
	}
	public void definirTypo(String nombre){
		if(nombre.equals("rojo")){
			this.direccionY=true;
		}else{
			this.direccionX=true;
		}
	}

	@Override
	public String toJsonString() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
	
		obj.put("direccionX", direccionX);
		obj.put("direccionY", direccionY);
		
		return obj.toJSONString();
	}
	@Override
	public JSONObject toJsonObj() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("type", type);
		obj.put("size", size);
		return obj;
	}
	
}