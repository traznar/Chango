package Models;

import org.json.simple.JSONObject;

public class PlayerData extends ObjetosJuego{
	
	public int puntuacion;
	public int vidas;
	public int animation;

	private boolean canJump=true;
	private boolean grab=false;
	
	public PlayerData(int posiX,int posiY,int size){
		super(posiX,posiY,size);
		this.puntuacion=0;
		this.vidas=3;
	}
	public String toJsonString() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("size", size);
		obj.put("puntuacion", puntuacion);
		obj.put("vidas", vidas);
		obj.put("animation", animation);
		
		return obj.toJSONString();

	}

	public boolean CanJump() {
		return canJump;
	}
	public void setCanJump(boolean canJump) {
		this.canJump = canJump;
	}
	@Override
	public JSONObject toJsonObj() {
		// TODO Auto-generated method stub
		return null;
	}
	public boolean isGrab() {
		return grab;
	}
	public void setGrab(boolean grab) {
		this.grab = grab;
	}
}
