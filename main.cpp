#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Cryptage {
private:
    string fichiersource;
    string fichierdestination;
    string mot;
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
    string chiffrementCesar(int decalage) {
        string resultat = "";
        for (char c : mot) {
            if (isupper(c)) {
                resultat += char((c - 'A' + decalage) % 26 + 'A');
            } else if (islower(c)) {
                resultat += char((c - 'a' + decalage) % 26 + 'a');
            } else {
                resultat += c;
            }
        }
        mot = resultat;
        return mot;
    }

    string DechiffrementCesar(int decalage) {
        string resultat = "";
        for (char c : mot) {
            if (isupper(c)) {
                // Décale les majuscules en sens inverse
                resultat += char((c - 'A' - decalage + 26) % 26 + 'A');
            } else if (islower(c)) {
                // Décale les minuscules en sens inverse
                resultat += char((c - 'a' - decalage + 26) % 26 + 'a');
            } else {
                // Conserve les autres caractères (espaces, ponctuation)
                resultat += c;
            }
        }
        mot = resultat;
        return mot;
    }

    string TrucXOR(char cle) {
        string resultat = "";
        for (char c : mot) {
            resultat += (c ^ cle);
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
            Chiffrement(3, 'F');
        }
        if (niveauCryptage == 5) {
            cout << "merci de rentrer le niveau de Chiffrement/Dechiffrement : " << endl;
            cout << "niveau 1 : Dechiffrement Cesar " << endl;
            cout << "niveau 2 : Dechiffrement XOR " << endl;
            cout << "niveau 3 : Dechiffrement Cesar & XOR " << endl;
            cin >> niveauCryptage;
            Dechiffrement(3, 'F');
        }

    }

    void Chiffrement(int decalage, char cle) {
        recupfichier();
        if(niveauCryptage == 1) {
            chiffrementCesar(decalage);
        }
        if(niveauCryptage == 2) {
            TrucXOR(cle);
        }
        if(niveauCryptage == 3) {
            chiffrementCesar(decalage);
            TrucXOR(cle);
        }
        Ecriture();
    }

    void Dechiffrement(int decalage, char cle) {
        recupfichier();
        if(niveauCryptage == 1) {
            DechiffrementCesar(decalage);
        }
        if(niveauCryptage == 2) {
            TrucXOR(cle);
        }
        if(niveauCryptage == 3) {
            TrucXOR(cle);
            DechiffrementCesar(decalage);
        }
        Ecriture();
    }
};

int main() {
    Cryptage a("C:/Users/jujuk/CLionProjects/Prosit2/fichiertexte.txt", "C:/Users/jujuk/CLionProjects/Prosit2/fichierdestination.txt");
    a.DemandeUtilisateur();
    return 0;
}
