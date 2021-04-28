package Models;

import org.json.simple.JSONObject;

public class cocodrilo extends ObjetosJuego{
	
	
	public boolean direccionY=false;
	public int type;
	public ZonaDetectable camino;
	
	

	public cocodrilo(int nombre,int posicionX,int posicionY,int size,ZonaDetectable liana){
		super(posicionX,posicionY,size);
		this.posX=liana.posX;
		this.posY=liana.posY+10;
		this.type=nombre;
		this.camino=liana;
		this.direccionY=false;

	}

	
	public void move() {
		int length=25;
		int velocity=5;
		//true arriba false abajo
		if(this.type==1) {
			if(posY <= camino.posY) direccionY=false;
			if(posY + length > camino.posY+camino.size) direccionY=true;
		}
		
		if(direccionY) posY-=velocity;
		else posY+=velocity;		
		

		
		
	}

	@Override
	public String toJsonString() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("direccionY", false);
		obj.put("direccionX", true);
		obj.put("direccionY", direccionY);
		
		return obj.toJSONString();
	}
	@Override
	public JSONObject toJsonObj() {
		JSONObject obj = new JSONObject();
		obj.put("posY", posY);
		obj.put("posX", posX);
		obj.put("direccionY", false);
		obj.put("direccionX", true);
		obj.put("type", type);
		obj.put("size", size);
		return obj;
	}
	
}