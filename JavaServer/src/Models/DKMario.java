package Models;

import org.json.simple.JSONObject;

public class DKMario extends ObjetosJuego{
	private String animation;
	public DKMario(int posiX,int posiY,int size){
		super(posiX,posiY,size);
	}
	@Override
	public String toJson() {
		JSONObject obj = new JSONObject();
		obj.put("posX", posX);
		obj.put("posY", posY);
		obj.put("size", size);
		obj.put("animation", animation);
		return obj.toJSONString();
	}
}
