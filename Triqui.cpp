//librerias
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <limits>
#include<string.h>

using namespace std;

//Jose Daniel Nino Munoz

//Declaracion de estructuras
struct Jugador{
	string nombreJugador;
	char simboloJugador;
};

struct Juego{
	int n;
	int** mapa;
	int cantJugadores;
	Jugador* jugador;
	int indiceGanador;
};

struct Campeonato{
	Juego* partidas;
	int cantPartidas;
};

//Declaracion de funciones
//informacion del juago
Juego infoRonda();
//crear mapa
int** mapa(int n);
//info jugadores
Jugador* jugadores(int n);
//imprimir mapa
void printta(int** tabla, int n,char f,char s);
//juego
void jugar(Juego juego);
//definir ganador
int definirGanador(int** mapa,int n);
//imprimir ganador
void printGanador(int indiceGanador,Jugador* jugador);

//info jugadores
Jugador* jugadores(int n){
    Jugador* vec=new Jugador [n];
    for(int i=0;i<n;i++){
		cout<<"Ingrese el nombre del jugador "<<i+1<<endl;
		cin>>(vec+i)->nombreJugador;
        cout<<"Ingrese el simbolo del jugador "<<i+1<<endl;
		cin>>(vec+i)->simboloJugador;
    }
    return vec;
}

//crear mapa
int** mapa(int n){
    int** tabla=new int*[n];
    for(int i=0;i<n;i++){
        *(tabla+i)=new int [n];
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            *(*(tabla+i)+j)=-1;
        }
    }
    
    return tabla;
}
//informacion del juago
Juego infoRonda(){
    Juego partidas;
    partidas.cantJugadores=2;
    partidas.indiceGanador=-1;
    cout<<"Ingresar tamano del tablero"<<endl;
    cin>>partidas.n;
    partidas.mapa=mapa(partidas.n);
    partidas.jugador=jugadores(partidas.cantJugadores);
	jugar(partidas);
    return partidas;
}
void printta(int** tabla, int n,char f,char s){

    for(int i=0;i<n;i++){
        cout<<" | ";
        for(int j=0;j<n;j++){
            if(*(*(tabla+i)+j)==-1)
					cout<<"  | ";
			else if(*(*(tabla+i)+j)==1)
					cout<<f<<" | ";
			else if(*(*(tabla+i)+j)==2)
					cout<<s<<" | ";
            }
        cout<<endl;
    }
    cout<<endl;
    return;
}
//juego
void jugar(Juego juego){
	int cont=0, j, Ganador=-1;
	do{
		
		system("cls");
		cout<<Ganador<<endl;
		bool f=true;
		int x,y;
		cont++;
		printta(juego.mapa,juego.n,(juego.jugador+0)->simboloJugador,(juego.jugador+1)->simboloJugador);
		do{
			if(cont%2==0)
				j=2;
			else
				j=1;
			cout<<"Jugador "<<j<<endl;
			cout<<"Ingrese las cordenadas de la jugada"<<endl;
			cout<<"X: ";
			cin>>x;
			cout<<endl;
			cout<<"Y: ";
			cin>>y;
			cout<<endl;
			if(*(*(juego.mapa+x-1)+y-1)==1||*(*(juego.mapa+x-1)+y-1)==2){
                system("cls");
			    cout<<"El espacio elegido ya esta ocupado"<<endl;
			    cout<<"                                          Presione ENTER"<< endl;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				system("cls");
				printta(juego.mapa,juego.n,(juego.jugador+0)->simboloJugador,(juego.jugador+1)->simboloJugador);
			}
			else{
				*(*(juego.mapa+x-1)+y-1)=j;
				juego.indiceGanador=definirGanador(juego.mapa,juego.n);
				f=false;
			}
		}while(f);
		system("cls");
		printGanador(juego.indiceGanador,juego.jugador);
	}while(juego.indiceGanador==-1&&cont!=(juego.n*juego.n));
    return;
}

int definirGanador(int** mapa,int n){
	int contador=0;
	for(int z=1;z<3;z++){
        for(int i=0;i<n;i++){
        	for(int j=0;j<n;j++){
            	if(*(*(mapa+i)+j)==z)
            	    contador++;
        	}
			if(contador==n)
		    	return z;
        	contador=0;
    	}
    	
    	for(int j=0;j<n;j++){
        	for(int i=0;i<n;i++){
            	if(*(*(mapa+i)+j)==z)
            	    contador++;
        	}
			if(contador==n)
		    	return z;
        	contador=0;
    	}

		for(int i=0;i<n;i++){
            	if(*(*(mapa+i)+i)==z)
            	    contador++;
        	}
			if(contador==n)
		    	return z;
        	contador=0;

			for(int j=0;j<n;j++){
				if(*(*(mapa+j)+(n-1-j))==z)
        	    	contador++;
        	}
			if(contador==n)
		    	return z;
            contador=0;
	}
	return -1;
}

void printGanador(int indiceGanador,Jugador* jugador){
	
	switch (indiceGanador){
		case 1:
            cout<<"El ganador del juego es ";
            cout<<(jugador+0)->nombreJugador<<endl;
			break;
		case 2:
            cout<<"El ganador del juego es ";
            cout<<(jugador+1)->nombreJugador<<endl;
			break;
		default:
            cout<<"EMPATE"<<endl;
	}
}

//main
int main(){
	Campeonato* miCampeonato;
	miCampeonato=new Campeonato[1];
	miCampeonato->cantPartidas=1;
	*(miCampeonato->partidas)=infoRonda();
    cout<<"                                          Presione ENTER"<< endl;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	delete[]miCampeonato;
}
