#include<iostream>
#include<string>
using namespace std;

// Lista dei prototipi delle funzioni che verranno implementate sotto il main
void inizializzaGriglia(char griglia[][7], int dim);
string chiediNomeGiocatore1();
string chiediNomeGiocatore2();
void stampaGriglia(char griglia[][7], int dim);
void chiediRigaColonna(string giocatore, char&scelta_riga_colonna, char &scelta_direzione, int &scelta_numero_riga_colonna);
void AggiornaGriglia(char griglia[][7], int dim,char&scelta_riga_colonna, char &scelta_direzione, int &scelta_numero_riga_colonna,char turno,bool &rifare);
// ... da aggiungere quelle fatte da voi
bool piena(char griglia[][7],int dim);
int vittoria_colonna(char g[7][7],int dim1,int dim2,char turno);
bool scorri_colonne(char g[7][7],int dim1,int dim2,char turno);
int vittoria_riga(char g[7][7], int dim1,int dim2,char turno);
bool scorri_righe(char g[7][7],int dim1,int dim2,char turno);
bool vittoria_diagonale1(char g[7][7],int x,int y,char turno);
bool vittoria_diagonale2(char g[7][7],int x,int y,char turno);
bool diagonali_minori1(char g[7][7], int x, int y, char turno);
bool diagonali_minori2(char g[7][7], int x, int y, char turno);
bool diagonali_minori3(char g[7][7], int x, int y, char turno);
bool diagonali_minori4(char g[7][7], int x, int y, char turno);
bool diagonali_minori5(char g[7][7], char turno);

int main(){


	// Griglia e dimensioni
	const int dim = 7;
	char griglia[dim][dim];

	// Giocatori
	string giocatore1;
	string giocatore2;

	// Stato del gioco
	bool fine=false;
	bool rifare=false;

	// Turno attuale: 'x' oppure 'o'
	char turno = 'x';

	// Scelta riga/colonna del giocatore
	char scelta_riga_colonna;
	// Scelta direzione
	char scelta_direzione;
	// Scelta del numero di riga/colonna
	int scelta_numero_riga_colonna;


	// Vincitore: ' ' -> pari, 'x' -> giocatore 1, 'o' -> giocatore 2
	char vincitore =' ';

	// 1) Pulisco la griglia la prima volta inserendo tutti caratteri vuoti
	inizializzaGriglia(griglia, dim);

	// 2) Inizializzare i nomi dei giocatori

	giocatore1= chiediNomeGiocatore1();
	giocatore2= chiediNomeGiocatore2();
	// 3) Stampare la griglia completa
    stampaGriglia(griglia, dim);
	// Finché il gioco non è finito continua a far giocare i 2 giocatori
	while(fine==false){
		// 4) Chiedi la mossa al giocatore
		string giocatore;
		if(turno == 'x'){

			giocatore=giocatore1;
		}
		else{

			giocatore=giocatore2;
			}
        //	chiediRigaColonna(giocatore, scelta_riga_colonna, scelta_direzione, scelta_numero_riga_colonna);
        chiediRigaColonna(giocatore,scelta_riga_colonna,scelta_direzione,scelta_numero_riga_colonna);
		// 5) Aggiorno la stato griglia (eseguo lo shift)
        AggiornaGriglia(griglia,dim,scelta_riga_colonna,scelta_direzione,scelta_numero_riga_colonna,turno,rifare);
        while(rifare==true){
        	chiediRigaColonna(giocatore,scelta_riga_colonna,scelta_direzione,scelta_numero_riga_colonna);
        	AggiornaGriglia(griglia,dim,scelta_riga_colonna,scelta_direzione,scelta_numero_riga_colonna,turno,rifare);
		}

		// 3) Stampare la griglia completa
		 stampaGriglia(griglia, dim);
		// 6) Controllo se la griglia è piena
        bool controllo=piena(griglia,dim);
        if(controllo==true){
        	cout<<"La griglia e' piena."<<endl;
            fine=true;
		} 
	
		
		// 7) Controllo eventuale vittoria
		//Controllo colonne
		if(scorri_colonne(griglia, dim-1, dim-1, turno)){
			vincitore=turno;
			fine=true;
		}

		
		//Controllo righe
		if(fine!=true){
			if(scorri_righe(griglia, dim-1, dim-1, turno)){
				vincitore=turno;
				fine=true;
			}
		}

		
		
		//Controllo diagonali
		if(fine!=true){
			if(vittoria_diagonale1(griglia, 0, 6, turno)){
				vincitore=turno;
				fine=true;
			}
		}
		
		if(fine!=true){
			if(vittoria_diagonale2( griglia, 0, 0, turno)){
				vincitore=turno;
				fine=true;
			}
		}
		
		if(fine!=true){
			if(diagonali_minori1(griglia, 0, 1,turno)){
				vincitore=turno;
				fine=true;
			}
	    }
	    
	    if(fine!=true){
			if(diagonali_minori2(griglia, 1, 0, turno)){
				vincitore=turno;
				fine=true;
			}
		}
		
	    if(fine!=true){
	    	if(diagonali_minori3(griglia, 5, 0, turno)){
	    		vincitore=turno;
	    		fine=true;
			}
		}
	    
	    if(fine!=true){
	    	if(diagonali_minori4(griglia, 6, 1, turno)){
	    		vincitore=turno;
	    		fine=true;
			}
		}
	    
	    if(fine!=true){
	    	if(diagonali_minori5(griglia, turno)){
	    		vincitore=turno;
	    		fine=true;
			}
		}

		// 8) Cambia il turno
		if(turno=='o' && rifare==false)
            turno='x';
        else
            turno='o';
	}

	// 9) Mostra vincitore
	switch(vincitore){
    		case 'x':
    			cout<<"Ha vinto: "<<giocatore1;
			    break;
			case 'o':
				cout<<"Ha vinto: "<<giocatore2;
				break;
			case ' ':
				cout<<"Pareggio";
				break; 
		}
}

// -------------------- IMPLEMENTAZIONE DELLE FUNZIONI --------------------

// 1) Pulisco la griglia la prima volta inserendo tutti caratteri vuoti
void inizializzaGriglia(char griglia[][7], int dim){

	for(int i=0; i<dim; i++){
		for(int j=0; j<dim; j++){
			griglia[i][j]=' ';
		}
	}
}

// 2) Inizializzare i nomi dei giocatori
	string chiediNomeGiocatore1(){
	string giocatore;
	cout<<"Inserire il nome del giocatore 1: "<<endl;
	cin>>giocatore;
	return giocatore;

}
string chiediNomeGiocatore2(){
	string giocatore;
	cout<<"Inserire il nome del giocatore 2: "<<endl;
	cin>>giocatore;
	return giocatore;

}


// 3) Stampare la griglia completa

void stampaGriglia(char griglia[][7], int dim){
	cout<<"\t"<<"     0       1       2       3       4       5       6   "<<endl;
	
	for(int i=0;i<7;i++){
		cout<<"\t"<<" ---------------------------------------------------------"<<endl;
		cout<<"        "<<" |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |"<<endl;
		cout<<"       "<<i<<" |   "<<         griglia[i][0]     <<"   |   "<<   griglia[i][1]     <<"   |   "<<   griglia[i][2]     <<"   |   "<<   griglia[i][3]     <<"   |   "<<   griglia[i][4]   <<"   |   "<<   griglia[i][5]     <<"   |   "<<   griglia[i][6]     <<"   |"<<endl;
		cout<<"        "<<" |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |   "<<"    |"<<endl;
	}
	cout<<"\t"<<" ---------------------------------------------------------"<<endl;
}
// 4) Chiedi la mossa al giocatore
void chiediRigaColonna(string giocatore, char&scelta_riga_colonna, char &scelta_direzione, int &scelta_numero_riga_colonna){
	cout<<giocatore<<" vuoi inserire la biglia in una riga o in una colonna (r/c): ";
	cin>>scelta_riga_colonna;
	while(scelta_riga_colonna!='r' && scelta_riga_colonna!='c'){
		cout<<giocatore<<" vuoi inserire la biglia in una riga o in una colonna (r/c): ";
		cin>>scelta_riga_colonna;
	}

	// chiedi in quale riga o in quale colonna vuole giocare
	if(scelta_riga_colonna=='r'){
		cout<<giocatore<<" quale riga vuoi selezionare (0-6): ";
		cin>>scelta_numero_riga_colonna;
		
		while(scelta_numero_riga_colonna<0 || scelta_numero_riga_colonna>6){
			cout<<giocatore<<" quale riga vuoi selezionare (0-6): ";
			cin>>scelta_numero_riga_colonna;
		}
		
	}else{
		cout<<giocatore<<" quale colonna vuoi selezionare (0-6): ";
	    cin>>scelta_numero_riga_colonna;
	    while(scelta_numero_riga_colonna<0 || scelta_numero_riga_colonna>6){
			cout<<giocatore<<" quale riga vuoi selezionare (0-6): ";
			cin>>scelta_numero_riga_colonna;
		}
	}

	// chiedi se da destra o da sinistra/ alto o basso
	if(scelta_riga_colonna=='r'){
		cout<<giocatore<<" vuoi inserire da destra o da sinistra (s/d): ";
		cin>>scelta_direzione;
		while(scelta_direzione!='s' && scelta_direzione!='d'){
		cout<<giocatore<<" vuoi inserire da destra o da sinistra (s/d): ";
		cin>>scelta_direzione;
		}
	}else{
		cout<<giocatore<<" vuoi inserire dall'alto o dal basso (a/b): ";
	    cin>>scelta_direzione;
	    while(scelta_direzione!='a' && scelta_direzione!='b'){
	    	cout<<giocatore<<" vuoi inserire dall'alto o dal basso (a/b): ";
	        cin>>scelta_direzione;
		}
	}
}


// 5) Aggiorno la griglia
void AggiornaGriglia(char griglia[][7], int dim,char&scelta_riga_colonna, char &scelta_direzione, int &scelta_numero_riga_colonna,char turno,bool &rifare){
	int numero= scelta_numero_riga_colonna-1;
	int d=0,c=0;
    int j=0;
    int i=0;
    rifare=false;

    //Se devo inserire dal lato sinistro
	if(scelta_riga_colonna=='r'){       //se inserisco sulla riga
		if (scelta_direzione=='s'){         //Se inserisco da sinistra

            //Shifto tutti di uno se non è piena
            while(griglia[scelta_numero_riga_colonna][j]!=' '&& j< dim){
                j++;
            }

            if(j>=dim){
                cout<<"La riga è piena"<<endl;
                rifare=true;
                return;
            }

            for(int c=j;c>0;c--){
                griglia[scelta_numero_riga_colonna][c]=griglia[scelta_numero_riga_colonna][c-1];
            }

            //e inserisco il nuovo elemento
            griglia[scelta_numero_riga_colonna][0]=turno;

        //Se devo inserire dal lato destro
        }else{
            j=6;
            while(griglia[scelta_numero_riga_colonna][j]!=' '&& j>=0){
                j--;
            }
            //Se non trovo una cella nulla nella riga..
            if(j<0){
                cout<<"La riga è piena"<<endl;
                rifare=true;
                return;
            }

            //shifto tutte le caselle di 1
            for(int c=j;c<6;c++){
                griglia[scelta_numero_riga_colonna][c]=griglia[scelta_numero_riga_colonna][c+1];
            }

            //e inserisco il nuovo elemento
            griglia[scelta_numero_riga_colonna][6]=turno;
        }

    //Se devo inserire in colonna
	}else{
        //se inserisco da sopra
        if (scelta_direzione=='a'){
            while(griglia[j][scelta_numero_riga_colonna]!=' '&& j< dim){
                j++;
            }

            if(j>=dim){
                cout<<"La colonna è piena"<<endl;
                rifare=true;
                return;
            }

            for(int c=j;c>0;c--){
                griglia[c][scelta_numero_riga_colonna]=griglia[c-1][scelta_numero_riga_colonna];
            }

            griglia[0][scelta_numero_riga_colonna]=turno;

        //Se devo inserire da sotto
        }else{
            j=6;
            while(griglia[j][scelta_numero_riga_colonna]!=' '&& j>=0){
                j--;
            }
            //Se non trovo una cella nulla nella colonna..
            if(j<0){
                cout<<"La colonna è piena"<<endl;
                rifare=true;
                return;
            }

            //shifto tutte le caselle di 1
            for(int c=j;c<6;c++){
                griglia[c][scelta_numero_riga_colonna]=griglia[c+1][scelta_numero_riga_colonna];
            }

            //e inserisco il nuovo elemento
            griglia[6][scelta_numero_riga_colonna]=turno;
        }
	}
}







// 6) Controllo se la griglia è piena
bool piena(char griglia[][7],int dim){
    for(int i=0;i<dim;i++)
        for(int j=0;j<dim;j++)
            if(griglia[i][j]==' ')
                return false;

    return true;

}

// 7) Controllo eventuale vittoria 

int vittoria_colonna(char g[7][7],int dim1,int dim2,char turno){
	if(dim1==0){
		return 1;
	}
	if(g[dim1][dim2]==g[dim1-1][dim2] && g[dim1][dim2]!=' ' && g[dim1][dim2]==turno){
		return 1+vittoria_colonna(g,dim1-1,dim2,turno);
	}
	return vittoria_colonna(g,dim1-1,dim2,turno);
}

bool scorri_colonne(char g[7][7],int dim1,int dim2,char turno){
	if(dim2==0){
		return false;
	}
	if(vittoria_colonna(g,dim1,dim2,turno)>=5){
		return true;
	}
	return scorri_colonne(g,dim1,dim2-1,turno);
}


int vittoria_riga(char g[7][7], int dim1,int dim2,char turno){
	if(dim2==0){
		return 1;
	}
	if(g[dim1][dim2]==g[dim1][dim2-1] && g[dim1][dim2-1]!=' ' && g[dim1][dim2]==turno){
		return 1+vittoria_riga(g,dim1,dim2-1,turno);
	}
	return vittoria_riga(g,dim1,dim2-1,turno);
	
}


bool scorri_righe(char g[7][7],int dim1,int dim2,char turno){
	if(dim1==0){
		return false;
	}
	if(vittoria_riga(g,dim1,dim2,turno)>=5){
		return true;
	}
	return scorri_righe(g,dim1-1,dim2,turno);
}

 
bool vittoria_diagonale1(char g[7][7],int x,int y,char turno){
	if(x>2){
		return false;
	}
	
	if(g[x][y]==turno && g[x+1][y-1]==turno && g[x+2][y-2]==turno && g[x+3][y-3]==turno && g[x+4][y-4]==turno){
		return true;
	}
	
	return vittoria_diagonale1(g,x+1,y-1,turno);
}


bool vittoria_diagonale2(char g[7][7],int x,int y,char turno){
	if(x>2){
		return false;
	}
	if(g[x][y]==turno && g[x+1][y+1]==turno && g[x+2][y+2]==turno && g[x+3][y+3]==turno && g[x+4][x+4]==turno){
		return true;
	}
	
	return vittoria_diagonale2(g,x+1,y+1,turno);
}

 
bool diagonali_minori1(char g[7][7], int x, int y, char turno){
	
	if(x>1){
		return false;
	}
	
	if(g[x][y]==turno && g[x+1][y+1]==turno && g[x+2][y+2]==turno && g[x+3][y+3]==turno && g[x+4][y+4]==turno){
		return true; 
	}
	return diagonali_minori1(g,x+1, y+1, turno);
	
}

bool diagonali_minori2(char g[7][7], int x, int y, char turno){
	
	if(y>1){
		return false;
	}
	if(g[x][y]==turno && g[x+1][y+1]==turno && g[x+2][y+2]==turno && g[x+3][y+3]==turno && g[x+4][y+4]==turno){
		return true;
	}
	return diagonali_minori2(g, x+1, y+1, turno);
}

bool diagonali_minori3(char g[7][7], int x, int y, char turno){
	
	if(y>1){
		return false;
	}
	
	if(g[x][y]==turno && g[x-1][y+1]==turno && g[x-2][y+2]==turno && g[x-3][y+3]==turno && g[x-4][y+4]==turno){
		return true; 
	}
	return diagonali_minori3(g,x-1, y+1, turno);
	
}

bool diagonali_minori4(char g[7][7], int x, int y, char turno){
	
	if(y>2){
		return false;
	}
	
	if(g[x][y]==turno && g[x-1][y+1]==turno && g[x-2][y+2]==turno && g[x-3][y+3]==turno && g[x-4][y+4]==turno){
		return true; 
	}
	return diagonali_minori4(g,x-1, y+1, turno);
	
}

bool diagonali_minori5(char g[7][7], char turno){
	if(g[0][4]==turno && g[1][3]==turno && g[2][2]==turno && g[3][1]==turno && g[4][0]==turno || g[2][6]==turno&& g[3][5]==turno && g[4][4]==turno && g[5][3]==turno && g[6][2]==turno || g[2][0]==turno && g[3][1]==turno && g[4][2]==turno && g[5][3]==turno && g[6][4]==turno || g[0][2]==turno && g[1][3]==turno && g[2][4]==turno && g[3][5]==turno && g[4][6]==turno){
		return true;
	}else{
		return false;
	}
}




// 8) Cambia il turno

// 9) Mostra vincitore

// 9) Mostra vincitore
