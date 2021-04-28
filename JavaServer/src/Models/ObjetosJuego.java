package Models;

import org.json.simple.JSONObject;

public abstract class ObjetosJuego {
	public float posX;
	public float posY;
	protected int size;
	
	
	public ObjetosJuego(int posiX,int posiY,int size){
		this.posX=posiX;
		this.posY=posiY;
		this.size=size;
	}
	public float getPosiX(){
		return posX;
	}
	public float getPosiY(){
		return posY;
	}
	public int getSize(){
		return size;
	}
	public void setPosiXY(int posiX,int posiY,int size){
		this.posX=posiX;
		this.posY=posiY;
		this.size=size;
	}
	public void setPosiY(int posiY){
		this.posY=posiY;
	}
	public void setPosiX(int posiX){
		this.posX=posiX;
	}
	public void setSize(int size){
		this.size=size;
	}
	public float getPosiTotalX(){
		return (posX+size);
	}
	public float getPosiTotalY(){
		return (posY+size);
	}	
	/**
	 * @def convert the object to json string
	 * @return json string
	 */
	public abstract String toJsonString(); 
	/**
	 * @def convert the object to json object
	 * @return
	 */
	public abstract JSONObject toJsonObj(); 
}
