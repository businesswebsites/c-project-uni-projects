#include <stdio.h>
#include <stdlib.h>
#include<string.h>

struct wert {
    long posX;
    long posY;
    int color;
    int deleteThis;
};

int main()
{

    char zeile[255];
    char* pointerZeile;
    struct wert token;
    struct wert* feld;
    long ret = 0;
    feld = malloc(sizeof(struct wert));
    char* restZeile;
    char* restZeile2;

    while ((pointerZeile = fgets(zeile, sizeof(zeile), stdin)) != NULL) {
            int abbr = 0;
            int yey = 0;
        for(int zy = 0; zy < 255; zy++){
            if(pointerZeile[zy] == 10){
                break;
            }
            if((pointerZeile[zy] >= 0 && pointerZeile[zy]< 10)){
                break;
            }
            if((pointerZeile[zy] >= 0 && pointerZeile[zy]< 10) || (pointerZeile[zy] > 10 && pointerZeile[zy] < 32) || (pointerZeile[zy] >32 && pointerZeile[zy] < 45) || (pointerZeile[zy] > 45 && pointerZeile[zy]< 48) || (pointerZeile[zy] >= 58 && pointerZeile[zy]<=127)){
                yey++;
                break;
            }
            yey++;

        }
		
		if (zeile[0] == '\n'){
			fprintf(stderr,"Abbruch leere Zeile.");
			free(feld);
			return 1;
		}

        for(int xy = 0; xy < yey ; xy++){
			if(pointerZeile[xy] == 0){
				fprintf(stderr,"Abbruch ungueltiges Symbol. 0-9\n");
				free(feld);
				return 1;
			}
			if(pointerZeile[xy] == '\x00'){
				fprintf(stderr,"Abbruch ungueltiges Symbol.\n");
				free(feld);
				return 1;
			}
            if(pointerZeile[xy] >=0 && pointerZeile[xy] <10 ){
                fprintf(stderr,"Abbruch ungueltiges Symbol. 0-9\n");
				free(feld);
                return 1;
            }
            if(pointerZeile[xy] > 10 && pointerZeile[xy] < 32){
                fprintf(stderr,"Abbruch ungueltiges Symbol. 11-32\n");
				free(feld);
                return 1;
            }
            if(pointerZeile[xy] >32 && pointerZeile[xy] < 45){
                fprintf(stderr,"Abbruch ungueltiges Symbol. 32-44\n");
				free(feld);
                return 1;
            }
            if(pointerZeile[xy] > 45 && pointerZeile[xy]< 48){
                fprintf(stderr,"Abbruch ungueltiges Symbol.46-47\n");
				free(feld);
                return 1;
            }
            if(pointerZeile[xy] >= 58 && pointerZeile[xy]<=127){
                fprintf(stderr,"Abbruch ungueltiges Symbol. 58-127\n");
				free(feld);
                return 1;
            }
            if(pointerZeile[xy]>47 && pointerZeile[xy]<58 &&pointerZeile[xy+1] == ' ' && abbr == 0){
                abbr++;
                continue;
            }
            if((pointerZeile[xy]>47 && pointerZeile[xy]<58 && abbr == 1) /*|| (pointerZeile[xy] == '-' &&pointerZeile[xy-1] == ' ' && abbr == 1)*/){
                abbr++;
                continue;
            }
            if((pointerZeile[xy]>47 && pointerZeile[xy]<58 && pointerZeile[xy-1] == ' ' && abbr == 2) || (pointerZeile[xy] == '-' &&pointerZeile[xy-1] == ' ' && abbr == 2)){
                abbr++;
            }

        }
        if(abbr < 2){
            fprintf(stderr,"Abbruch: nur eine oder keine Zahl pro Zeile.");
			free(feld);
            return 1;
        }
        if(abbr > 2){
            fprintf(stderr,"Abbruch: mehr als 2 Zahlen pro Zeile");
			free(feld);
            return 1;
        }

        ret++;
        if (pointerZeile == NULL) {
            printf("\n EOF \n");
        }
        else {
            token.color = strtol(pointerZeile, &restZeile, 10);

			if(token.color == 65536){
				fprintf(stderr,"Abbruch Farbe.");
				free(feld);
				return 1;
			}
			if(token.color == 4294967296){
				fprintf(stderr,"Abbruch Farbe.");
				free(feld);
				return 1;
			}
			
            //Abbruch wenn Farbe groesser als 254
            if(token.color > 254){
                fprintf(stderr,"Abbruch Farbe");
				free(feld);
                return 1;
            }
            if(token.color < 0){
                fprintf(stderr,"Abbruch Farbe");
				free(feld);
                return 1;
            }

            token.posX = strtol(restZeile, &restZeile2, 10);
			
			//fehlermeldung wenn zahl < -10^9
			
			if(token.posX < -1000000000){
				fprintf(stderr,"Abbruch Zahl zu klein.");
				free(feld);
				return 1;
			}
			
			//fehlermeldung wenn zahl > 10^9
			if(token.posX > 1000000000){
				fprintf(stderr,"Abbruch Zahl zu gross.");
				free(feld);
				return 1;
			}
			//fehlermeldung wenn position bei 2^32 oder groesser
			if(token.posX >= 4294967296){
				fprintf(stderr,"Abbruch Zahl zu gross.");
				free(feld);
				return 1;
			}
			//fehlermeldung wenn farbe bei 2^32 oder groesser
			if(token.color >= 4294967296){
				fprintf(stderr,"Abbruch Farbe zu gross.");
				free(feld);
				return 1;
			}
			
            //ueberpruefen ob die eingelesene Zeile mehr als 2 Zahlen enthaelt
            long bla = strtol(restZeile2, &restZeile2, 10);
            //bla += 1;
            if(bla != 0){
				free(feld);
                return 1;
            }
            //sortieren der xPos
            long maxIndex = 0;
            for (long index = 0; index < ret-1; index++) {
                if (token.posX >= feld[index].posX) {
                    maxIndex++;
                }
                else
                {
                    break;
                }
            }

            //hier noch for-schleife die nach kleinsten y in spalte guckt
            long lowestRow = -1;
            for (int a = 0; a < ret - 1; a++) {
                if (feld[a].posX == token.posX) {
                    if (feld[a].deleteThis<1)
                    {
                        lowestRow++;
                    }
                }
                else if (feld[a].posX > token.posX)
                {
                    break;
                }
            }
            //tokens nach rechts schieben wenn neuer token eingefügt wird
            if (maxIndex<ret-1)
            {
                memmove(&feld[maxIndex + 1], &feld[maxIndex], (ret -1 - maxIndex) * sizeof(struct wert));
            }
            //Jeder token.deleteThis zu Beginn auf 0 gesetzt, da er noch nicth markiert ist
            token.posY = lowestRow+1;
            token.deleteThis = 0;
            feld[maxIndex] = token;
            //feld sortieren nach posX

            int hoch = 1;
            int diagHoch = 1;
            int diagRunter = 1;
            int runter = 1;
            long hochBuffer[2];
            long diagHochBuffer[2];
            long diagRunterBuffer[2];
            long runterBuffer[2];
            int checkAgain = 1;

            while (checkAgain == 1) {
                for (long u = 0; u < ret; u++) {
                    for (long h = u + 1; h < ret; h++) {

                        //hat die angeschaute position bereits ein geändertes Feld dann ist keine Überprüfung mehr notwendig
                        if (feld[h].color > 254) {
                            continue;
                        }
                        //hier wird waagerecht nach viererreihen gesucht
                        if ((feld[u].posX + hoch == feld[h].posX) && (feld[u].posY == feld[h].posY) && (feld[u].color == feld[h].color)) {
                            hoch++;
                            //die ersten 2 gefundenen werden im hochbuffer gespeichert
                            if (hoch <= 3) {
                                hochBuffer[hoch - 2] = h;
                            }
                            else if (hoch == 4) {
                                feld[u].deleteThis = 1;
                                feld[h].deleteThis = 1;
                                feld[hochBuffer[0]].deleteThis = 1;
                                feld[hochBuffer[1]].deleteThis = 1;
                                
                            }
                            else {
                                feld[h].deleteThis = 1;
                            }
                        }
                        //hier wird diagonal nach rechts oben gesucht
                        if ((feld[u].posX + diagHoch == feld[h].posX) && (feld[u].posY + diagHoch == feld[h].posY) && (feld[u].color == feld[h].color)) {
                            diagHoch++;

                            if (diagHoch <= 3) {
                                diagHochBuffer[diagHoch - 2] = h;
                            }
                            else if (diagHoch == 4) {
                                feld[u].deleteThis = 1;
                                feld[h].deleteThis = 1;
                                feld[diagHochBuffer[0]].deleteThis = 1;
                                feld[diagHochBuffer[1]].deleteThis = 1;
                               
                            }
                            else {
                                feld[h].deleteThis = 1;
                            }
                        }
                        //hier wird diagonal nach rechts unten gesucht
                        if ((feld[u].posX + diagRunter == feld[h].posX) && (feld[u].posY - diagRunter == feld[h].posY) && (feld[u].color == feld[h].color)) {
                            diagRunter++;

                            if (diagRunter <= 3) {
                                diagRunterBuffer[diagRunter - 2] = h;
                            }
                            else if (diagRunter == 4) {
                                feld[u].deleteThis = 1;
                                feld[h].deleteThis = 1;
                                feld[diagRunterBuffer[0]].deleteThis = 1;
                                feld[diagRunterBuffer[1]].deleteThis = 1;
                                
                            }
                            else {
                                feld[h].deleteThis = 1;
                            }
                        }
                        //hier wird senkrecht nach unten gesucht
                        if ((feld[u].posX == feld[h].posX) && (feld[u].posY + runter == feld[h].posY) && (feld[u].color == feld[h].color)) {
                            runter++;

                            if (runter <= 3) {
                                runterBuffer[runter - 2] = h;
                            }
                            else if (runter == 4) {
                                feld[u].deleteThis = 1;
                                feld[h].deleteThis = 1;
                                feld[runterBuffer[0]].deleteThis = 1;
                                feld[runterBuffer[1]].deleteThis = 1;
                            }
                            else {
                                feld[h].deleteThis = 1;
                            }
                        }
                    }
                    hoch = 1;
                    runter = 1;
                    diagHoch = 1;
                    diagRunter = 1;
                }// hier u schleife ende

                checkAgain = 0;
                for (int a = 0; a < ret; a++) {
                    if (feld[a].deleteThis > 0) {
                        checkAgain = 1;  //wenn eine Reihe gefunden wurde, wird es auf 1 gesetzt damit noch einmal durchgeschaut wird
                        long posX = feld[a].posX;
                        memmove(&feld[a], &feld[a+1], (ret - 1 - a) * sizeof(struct wert));// bewege alle Tokens eine Position nach rechts

                        ret--;
                        for (int t = a; t < ret; t++) { // ändere die Y-Position von nachrutschenden Tokens

                            if (feld[t].posX == posX) {

                                feld[t].posY -= 1;
                            }
                            else if (feld[t].posX > posX)
                            {
                                break;
                            }

                        }
                        a--; // verkleinern, um zu verhindern, dass a überschrieben wird
                    }

                }
            }
            feld = realloc(feld, (ret + 1) * sizeof(struct wert));
        }
    }

    for (long i = 0; i < ret; i++)
    {
	        fprintf(stdout, "%d %ld %ld\n",feld[i].color, feld[i].posX, feld[i].posY);
    }
    free(feld);
    return 0;
}
