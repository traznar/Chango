package logica;

public class frutas extends ObjetosJuego{
	public static int puntos;
	
	public frutas(int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);
		this.puntos=100;
	}
	public int getPuntos(){
		return puntos;
	}
}
