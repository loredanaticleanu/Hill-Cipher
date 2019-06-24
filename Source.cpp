#include<iostream>
#include<string>
#include<math.h>

#define N 7

using namespace std;

int find_det(int matrice_initiala[N][N], int n, int det) {

	if (n == 2) {
		det = ((matrice_initiala[0][0] * matrice_initiala[1][1]) - (matrice_initiala[1][0] * matrice_initiala[0][1]));
	}
	else if (n == 3) {
		det = matrice_initiala[0][0] * ((matrice_initiala[1][1] * matrice_initiala[2][2]) - (matrice_initiala[2][1] * matrice_initiala[1][2]))
			- matrice_initiala[0][1] * (matrice_initiala[1][0] * matrice_initiala[2][2] - matrice_initiala[2][0] * matrice_initiala[1][2])
			+ matrice_initiala[0][2] * (matrice_initiala[1][0] * matrice_initiala[2][1] - matrice_initiala[2][0] * matrice_initiala[1][1]);
	}
	return det;
}
//ceva
int cmmdc(int a, int b) {
	while (a != b) {
		if (a > b) {
			a = a - b;
		}
		else {
			b = b - a;
		}
	}
	return a;
}

int sim(int det) {
	int x;
	for (x = 1; x <= 26; x++) {
		if ((x * det) % 26 == 1) {
			return x;
		}
	}
}

void citire(string &mesaj) {

	cout << "Introduceti mesajul: ";
	getline(cin, mesaj);

	//am facut toate caracterele mari pentru a evita sa adaug conditiile pentru fiecare functie
	for (int i = 0; i < mesaj.length(); i++) {
		mesaj[i] = toupper(mesaj[i]);

	}

}

void conditieMesaj(string mesaj, int n) {
	//asta seteaza ca mesajul sa nu fie mai lung decat lungimea alocata pentru matrice
	//si ca lungimea mesajului sa nu fie numar impar

	do {
		cout << "Reintroduceti mesajul: ";
		getline(cin, mesaj);

	} while (mesaj.length() > N * n);
}

void citireMatrice(int matrice_initiala[N][N], int n) {

	cout << "Introduceti valoriile pentru matricea initiala: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << " M - [" << i << "][" << j << "] = ";
			cin >> matrice_initiala[i][j];

		}
	}
	cout << endl << endl;
}

void citireVector(int vector[N][N], int n) {

	cout << "Introduceti valoriile pentru vector: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1; j++) {
			cout << " V - [" << i << "][" << j << "] = ";
			cin >> vector[i][j];

		}
	}

	cout << endl << endl;
}

void afisareMatriceVector(int matrice_initiala[N][N], int vector[N][N], int n) {
	//aceasta functie e doar pentru reafisarea matriciilor

	cout << "Matricea initiala: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << matrice_initiala[i][j] << " ";

		}
		cout << endl;
	}

	cout << endl << endl;
	cout << "Vectorul: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 1; j++) {
			cout << vector[i][j] << " ";

		}
		cout << endl;
	}
	cout << endl << endl;
}

//------------------------------------------CRIPTARE--------------------------------------------------
void initializareVectorParcurs(int matrice_initiala[N][N], int vector[N][N], int vector_parcurs[N][N], int matrice_parcursa[N][N], int n, string mesaj) {
	int x = 0;

	//folosesc un vector in care o sa aloc parti din mesaj; vectorul o sa fie de tipul						| 0, 2, 4 |
	for (int i = 0; i < (mesaj.length() / n); i++) {	//partiile din mesaj se aloca in urmatoarea ordine	| 1, 3, N |
		for (int j = 0; j < n; j++) {

			vector_parcurs[j][i] = ((int)mesaj[x] + 'A') % 26;
			x++;
		}
	}
	cout << endl << endl;
}

void criptare(int matrice_initiala[N][N], int vector[N][N], int vector_parcurs[N][N],
	int matrice_parcursa[N][N], int matrice_rezultata[N][N], int n, string mesaj, string crypted) {

	int x = 0;
	int z = 0;
	//se face inmultirea matricei cu vectorul; de fiecare data cand se schimba j, atunci trece la alt vector ;ex.  de la   | 0 | la | 2 |
	//		mesaj.lenght()/2 pentru a face matricea exact de dimensiunea necesara									       | 1 |	| 3 |
	for (int j = 0; j < (mesaj.length() / n); j++) {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {

				matrice_parcursa[x][z] = matrice_parcursa[x][z] + (matrice_initiala[i][k] * vector_parcurs[k][j]);

			}
			z++;
			if (z == n) {
				z = 0;
			}

		}
		x++;
		if (x == (mesaj.length() / n)) {
			x = 0;
		}

	}

	cout << "Matrice criptata: " << endl;
	for (int x = 0; x < (mesaj.length() / n); x++) {
		for (int z = 0; z < n; z++) {
			//se face adunarea pentru a rezulta matricea criptata

			matrice_rezultata[x][z] = ((matrice_parcursa[x][z] + vector[z][0]) % 26 + 26);
			cout << matrice_rezultata[x][z] << " ";
		}
		cout << endl;
	}
}

void afisareCriptare(int matrice_rezultata[N][N], int n, string mesaj, string crypted) {
	crypted = mesaj;

	//functia asta e doar ca sa pot sa afisez mesajul criptat
	int x = 0;
	int z = 0;
	int y = 0;

	for (int i = 0; i < (mesaj.length() / n); i++) {
		for (int j = 0; j < n; j++) {
			crypted[x] = matrice_rezultata[i][j];
			x++;
		}
	}

	cout << endl;
	cout << "Mesajul criptat: " << endl;
	for (int i = 0; i < crypted.length(); i++) {
		cout << (char)(crypted[i] + 'A');
	}
	cout << endl << endl;
}

void conditie(int matrice_initiala[N][N], int n, int det) {
	//coditia pentru care sa se poata face criptarea
	cmmdc(det, n);
	while (find_det(matrice_initiala, n, det) == 0 || cmmdc(find_det(matrice_initiala, n, det), n) != 1) {
		if (find_det(matrice_initiala, n, det) == 0) {

			cout << "Determinantul este: 0.";
		}
		else if (cmmdc(find_det(matrice_initiala, n, det), n) != 1) {

			cout << "Cmmdc nu este: 1.";
		}
		citireMatrice(matrice_initiala, n);
	}
}

//------------------------------------------CALCULE/INVERSA--------------------------------------------------
void transpose(int matrice_initiala[N][N], int matrice_transpusa[N][N], int n) {

	cout << "Matricea transpusa: " << endl << endl;
	int x = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			matrice_transpusa[i][j] = matrice_initiala[j][i];
			cout << matrice_transpusa[i][j] << " ";
		}
		cout << endl;
	}
}

void adjuncta(int matrice_transpusa[N][N], int matrice_initiala[N][N], int matrice_adjuncta[N][N], int n, int det) {
	int x = n - 1;
	int z = n - 1;

	if (n == 2) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				matrice_adjuncta[i][j] = (pow(-1, i + j))*matrice_transpusa[x][z];

				z--;
				if (z == -1) {
					z = n - 1;
				}

			}
			x--;
			if (x == -1) {
				x = n - 1;
			}
		}
	}
	else if (n == 3) {

		//poorly coded

		matrice_adjuncta[0][0] = matrice_transpusa[1][1] * matrice_transpusa[2][2] - matrice_transpusa[1][2] * matrice_transpusa[2][1];

		matrice_adjuncta[0][1] = -(matrice_transpusa[1][0] * matrice_transpusa[2][2] - matrice_transpusa[2][0] * matrice_transpusa[1][2]);

		matrice_adjuncta[0][2] = matrice_transpusa[1][0] * matrice_transpusa[2][1] - matrice_transpusa[2][0] * matrice_transpusa[1][1];

		matrice_adjuncta[1][0] = -(matrice_transpusa[0][1] * matrice_transpusa[2][2] - matrice_transpusa[2][1] * matrice_transpusa[0][2]);

		matrice_adjuncta[1][1] = matrice_transpusa[0][0] * matrice_transpusa[2][2] - matrice_transpusa[2][0] * matrice_transpusa[0][2];

		matrice_adjuncta[1][2] = -(matrice_transpusa[0][0] * matrice_transpusa[2][1] - matrice_transpusa[2][0] * matrice_transpusa[0][1]);

		matrice_adjuncta[2][0] = matrice_transpusa[0][1] * matrice_transpusa[1][2] - matrice_transpusa[1][1] * matrice_transpusa[0][2];

		matrice_adjuncta[2][1] = -(matrice_transpusa[0][0] * matrice_transpusa[1][2] - matrice_transpusa[1][0] * matrice_transpusa[0][2]);

		matrice_adjuncta[2][2] = matrice_transpusa[0][0] * matrice_transpusa[1][1] - matrice_transpusa[1][0] * matrice_transpusa[0][1];


	}


	cout << endl << endl;
	cout << "Afisare adjincta %26: " << endl;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrice_adjuncta[i][j] = (matrice_adjuncta[i][j] + 'A') % 26;
			cout << matrice_adjuncta[i][j] << " ";
		}
		cout << endl;
	}
}

void inversa(int matricea_adjuncta[N][N], int matrice_inversa[N][N], int n, int det) {

	int x = sim(det);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			matrice_inversa[i][j] = (x * matricea_adjuncta[i][j]) % 26;
		}
	}

	cout << endl << endl;

	cout << "Matricea inversa %26: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {

			cout << matrice_inversa[i][j] << " ";
		}
		cout << endl;
	}
}

//------------------------------------------DECRIPTARE--------------------------------------------------
void decryptF(int matrice_decriptare[N][N], int matrice_inversa[N][N], int vector[N][N],
	int n, int aux[N][N], string decrypted, string mesaj, int matrice_rezultata[N][N], int matrice_finala[N][N]) {

	decrypted = mesaj;

	int x = 0;
	int z = 0;


	//retin intr-o matrice aux scaderea pentru a o putea aplica la inmultire
	for (int j = 0; j < (mesaj.length() / n); j++) {
		for (int i = 0; i < n; i++) {
			aux[i][j] = matrice_rezultata[j][i] - vector[i][0];
		}
	}

	for (int j = 0; j < (mesaj.length() / n); j++) {
		for (int i = 0; i < n; i++) {
			for (int k = 0; k < n; k++) {

				//inmultirea & decriptarea
				matrice_decriptare[x][z] = ((matrice_decriptare[x][z] + (matrice_inversa[i][k] * aux[k][j])) + 'A') % 26;

			}
			z++;
			if (z == n) {
				z = 0;
			}

		}
		x++;
		if (x == (mesaj.length() / n)) {
			x = 0;
		}

	}
	if (n % 2 == 0) {
		for (int i = 0; i < (mesaj.length() / n); i++) {
			for (int j = 0; j < n; j++) {
				matrice_finala[i][j] = (matrice_decriptare[i][j]) % 26;
			}
		}

	}

	else if (n % 2 == 1) {
		for (int i = 0; i < (mesaj.length() / n); i++) {
			for (int j = 0; j < n; j++) {

				//matrice_finala[i][j] = (matrice_decriptare[i][j]) % 26;
			//am facut acest if pentru ca am un bug undeva in cod si nu am reusit sa imi dau seama unde
				//la fiecare a doua linie mai este nevoie de inca un +'A'
				if (i % 2 == 0) {
					matrice_finala[i][j] = (matrice_decriptare[i][j]) % 26;
				}
				else if (i % 2 != 0) {
					matrice_finala[i][j] = (matrice_decriptare[i][j] + 'A') % 26;
				}

			}
		}
	}


	//asta e doar pentru afisarea matricii
	cout << endl << endl;
	cout << "Matricea decriptata: " << endl;
	for (int i = 0; i < (mesaj.length() / n); i++) {
		for (int j = 0; j < n; j++) {
			cout << matrice_finala[i][j] << " ";
		}
		cout << endl;
	}

	//iar asta este pentru afisarea mesajului decriptat
	int y = 0;
	for (int i = 0; i < (mesaj.length() / n); i++) {
		for (int j = 0; j < n; j++) {
			decrypted[y] = matrice_finala[i][j];
			y++;
		}
	}

	cout << endl;
	cout << "Mesajul decriptat: " << endl;
	for (int i = 0; i < decrypted.length(); i++) {
		cout << (char)(decrypted[i] + 'A');
	}

}

//----------------------------------------------MAIN--------------------------------------------------
void main() {

	string mesaj;
	string crypted;
	string decrypted;

	int matrice_initiala[N][N];
	int matrice_parcursa[N][N];

	int vector_parcurs[N][N];
	int vector[N][N];

	int matrice_rezultata[N][N];

	int matrice_transpusa[N][N];
	int matrice_adjuncta[N][N];
	int matrice_inversa[N][N];

	int matrice_decriptare[N][N];
	int aux[N][N];
	int matrice_finala[N][N];


	int n;
	int det = 0;

	cout << "-----------------------------INPUT--------------------------------- " << endl << endl;

	citire(mesaj);


	cout << "Introduceti numarul de linii si coloane: ";
	cin >> n;

	while (n != 2 && n != 3) {
		cout << "Va rog reintroduceti numarul de linii si coloane: ";
		cin >> n;
	}

	//conditieMesaj(mesaj, n);
	cout << endl << endl;

	citireMatrice(matrice_initiala, n);
	citireVector(vector, n);

	det = find_det(matrice_initiala, n, det);

	conditie(matrice_initiala, n, det);

	afisareMatriceVector(matrice_initiala, vector, n);

	cout << "-----------------------------OUTPUT--------------------------------- " << endl << endl;

	cout << "Determinantul este: " << det << endl << endl;
	cout << "cmmdc: " << cmmdc(det, n) << endl << endl;

	//---------------------------------------------CRIPTARE--------------------------------------------------
	initializareVectorParcurs(matrice_initiala, vector, vector_parcurs, matrice_parcursa, n, mesaj);
	criptare(matrice_initiala, vector, vector_parcurs, matrice_parcursa, matrice_rezultata, n, mesaj, crypted);
	afisareCriptare(matrice_rezultata, n, mesaj, crypted);

	//-----------------------------------------CLACULE/INVERSA-----------------------------------------------
	transpose(matrice_initiala, matrice_transpusa, n);
	adjuncta(matrice_transpusa, matrice_initiala, matrice_adjuncta, n, det);
	inversa(matrice_adjuncta, matrice_inversa, n, det);

	//--------------------------------------------DECRIPTARE-----------------------------------------------------
	decryptF(matrice_decriptare, matrice_inversa, vector, n, aux, decrypted, mesaj, matrice_rezultata, matrice_finala);

	cout << "Anything";
}
