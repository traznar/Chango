package Models;

import org.json.simple.JSONObject;

public class DKMario extends ObjetosJuego{
	private String animation;
	public DKMario(int posiX,int posiY,int size){
		super(posiX,posiY,size);
	}
	@Override
	public String toJsonString() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);

		obj.put("animation", animation);
		return obj.toJSONString();
	}
	@Override
	public JSONObject toJsonObj() {
		// TODO Auto-generated method stub
		return null;
	}
}
