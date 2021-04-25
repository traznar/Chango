package logica;

public class playerData extends ObjetosJuego{
	
	public int puntuacion;
	public int vidas;
	public String animation;
	
	public playerData(int posiX,int posiY,int size){
		super(posiX,posiY,size);
		this.puntuacion=0;
		this.vidas=3;
	}
	
}
