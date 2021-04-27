package Models;

import org.json.simple.JSONObject;

public abstract class ObjetosJuego {
	public int posX;
	public int posY;
	protected int size;
	
	
	public ObjetosJuego(int posiX,int posiY,int size){
		this.posX=posiX;
		this.posY=posiY;
		this.size=size;
	}
	public int getPosiX(){
		return posX;
	}
	public int getPosiY(){
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
	public int getPosiTotalX(){
		return (posX+size);
	}
	public int getPosiTotalY(){
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
