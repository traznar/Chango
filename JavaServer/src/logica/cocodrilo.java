package logica;

public class cocodrilo extends ObjetosJuego{
	
	public boolean direccionX;
	public boolean direccionY;
	public String nombre;
	
	public cocodrilo(String nombre,int posicionX,int posicionY,int size){
		super(posicionX,posicionY,size);
		this.nombre=nombre;
		this.direccionX=false;
		this.direccionY=false;
		definirTypo(nombre);
	}
	public void definirTypo(String nombre){
		if(nombre.equals("rojo")){
			this.direccionY=true;
		}else{
			this.direccionX=true;
		}
	}
	
}