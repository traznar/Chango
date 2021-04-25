package Models;

import estructurasDatos.lista;

public class Administrador {
	PlayerData jugador;
	lista<Fruta> frutas;
	lista<cocodrilo> cocodrilos;
	
	public Administrador(int posiX,int posiY,int size){
		jugador=new PlayerData(posiX,posiY,size);
		frutas=new lista();
		cocodrilos=new lista();
	}
}
