package logica;
/*
 * Es para tener las zonas de las lianas o plataformas 
 */
public class ZonaDetectable extends ObjetosJuego{
	public String nombre;
	
	public ZonaDetectable(String nombre,int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);
		this.nombre=nombre;
	}
	
}
