package logica;

public class ObjetosJuego {
	private int posiX;
	private int posiY;
	private int size;
	
	public ObjetosJuego(int posiX,int posiY,int size){
		this.posiX=posiX;
		this.posiY=posiY;
		this.size=size;
	}
	public int getPosiX(){
		return posiX;
	}
	public int getPosiY(){
		return posiY;
	}
	public int getSize(){
		return size;
	}
	public void setPosiY(int posiY){
		this.posiY=posiY;
	}
	public void setPosiX(int posiX){
		this.posiX=posiX;
	}
	public void setSize(int size){
		this.size=size;
	}
	public int getPosiTotalX(){
		return (posiX+size);
	}
	public int getPosiTotalY(){
		return (posiY+size);
	}	
}
