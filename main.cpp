#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Cryptage {
private:
    string fichiersource;
    string fichierdestination;
    string mot;
    char cleDeChiffrement;
    int decalageCesar;
    int niveauCryptage;


    // Lecture du contenu du fichier source
    string recupfichier() {
        ifstream fichier(fichiersource); // ouverture en mode lecture
        string ligne;
        mot = ""; // Initialiser mot pour stocker tout le contenu

        if (fichier) {
            while (getline(fichier, ligne)) {
                mot += ligne + "\n"; // Concaténer chaque ligne avec un saut de ligne
            }
            fichier.close();
        } else {
            cerr << "Erreur : le fichier source ne s'ouvre pas." << endl;
        }
        return mot;
    }

    // Écriture dans le fichier de destination
    void Ecriture() {
        ofstream fichier(fichierdestination); // ouverture en mode écriture

        if (fichier) {
            fichier << "Message chiffré :" << mot << endl;
            fichier.close();
        } else {
            cerr << "Erreur : le fichier de destination ne s'ouvre pas." << endl;
        }
    }

    // Méthode de chiffrement César
    string chiffrementCesar() {
        string resultat = "";
        for (char c : mot) {
            if (isupper(c)) {
                resultat += char((c - 'A' + decalageCesar) % 26 + 'A');
            } else if (islower(c)) {
                resultat += char((c - 'a' + decalageCesar) % 26 + 'a');
            } else {
                resultat += c;
            }
        }
        mot = resultat;
        return mot;
    }

    string DechiffrementCesar() {
        string resultat = "";
        for (char c : mot) {
            if (isupper(c)) {
                resultat += char((c - 'A' - decalageCesar + 26) % 26 + 'A');
            } else if (islower(c)) {
                resultat += char((c - 'a' - decalageCesar + 26) % 26 + 'a');
            } else {
                resultat += c;
            }
        }
        mot = resultat;
        return mot;
    }

    string TrucXOR() {
        string resultat = "";
        for (char c : mot) {
            resultat += (c ^ cleDeChiffrement);
        }
        mot = resultat;
        return mot;
    }

public:
    Cryptage(string fichiersource, string fichierdestination)
            : fichiersource(fichiersource), fichierdestination(fichierdestination) {}

    bool DemandeUtilisateur() {
        cout << "Voulez vous Chiffrer ou Dechiffrer ? 4/5" << endl;
        cin >> niveauCryptage;
        if (niveauCryptage == 4) {
            cout << "merci de rentrer le niveau de Chiffrement/Dechiffrement : " << endl;
            cout << "niveau 1 : Chiffrement Cesar " << endl;
            cout << "niveau 2 : Chiffrement XOR " << endl;
            cout << "niveau 3 : Chiffrement Cesar & XOR " << endl;
            cin >> niveauCryptage;
            Chiffrement();
        }
        if (niveauCryptage == 5) {
            cout << "merci de rentrer le niveau de Chiffrement/Dechiffrement : " << endl;
            cout << "niveau 1 : Dechiffrement Cesar " << endl;
            cout << "niveau 2 : Dechiffrement XOR " << endl;
            cout << "niveau 3 : Dechiffrement Cesar & XOR " << endl;
            cin >> niveauCryptage;
            Dechiffrement();
        }

    }

    void Chiffrement() {
        recupfichier();
        if(niveauCryptage == 1) {
            cout << "Indiquer le nombre de decalge Cesar pour le chiffrement" << endl;
            cin >> decalageCesar;
            chiffrementCesar();
        }
        if(niveauCryptage == 2) {
            cout << "Indiquer la cle de chiffrement Xor" << endl;
            cin >> cleDeChiffrement;
            TrucXOR();
        }
        if(niveauCryptage == 3) {
            cout << "Indiquer le nombre de decalge Cesar" << endl;
            cin >> decalageCesar;
            cout << "Indiquer la cle de chiffrement Xor" << endl;
            cin >> cleDeChiffrement;
            chiffrementCesar();
            TrucXOR();
        }
        Ecriture();
    }

    void Dechiffrement() {
        recupfichier();
        if(niveauCryptage == 1) {
            cout << "Indiquer le nombre de decalge Cesar pour le Dechiffrement" << endl;
            cin >> decalageCesar;
            DechiffrementCesar();
        }
        if(niveauCryptage == 2) {
            cout << "Indiquer la cle de chiffrement Xor" << endl;
            cin >> cleDeChiffrement;
            TrucXOR();
        }
        if(niveauCryptage == 3) {
            cout << "Indiquer le nombre de decalge Cesar" << endl;
            cin >> decalageCesar;
            cout << "Indiquer la cle de chiffrement Xor" << endl;
            cin >> cleDeChiffrement;
            TrucXOR();
            DechiffrementCesar();
        }
        Ecriture();
    }
};

int main() {
    Cryptage a("C:/Users/jujuk/CLionProjects/Prosit2/fichiertexte.txt", "C:/Users/jujuk/CLionProjects/Prosit2/fichierdestination.txt");
    a.DemandeUtilisateur();
    return 0;
}
