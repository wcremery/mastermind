#include <iostream>
#include <ctime>

// pour les nombres aléatoires
#include <random>
#include <cstring> // strlen


// ======================================================================
// Couleur au hasard
std::uniform_int_distribution<int> distribution;
std::default_random_engine generateur(time(NULL)); /* NOT using std::random_device since not
													* all compilers seems to support it :-( */

char tirer_couleur()
{
	static const char* const couleurs = ".RGBCYM";
	static const int nb = strlen(couleurs) - 1;

	return couleurs[distribution(generateur,
		std::uniform_int_distribution<int>::param_type{ 0, nb })];
}

// ======================================================================
char poser_question()
{
	char lu(' ');
	std::cout << "Entrez une couleur : ";
	std::cin >> lu;
	return lu;
}

// ---- prototype -------------------------------------------------------
bool couleur_valide(char c);

// ======================================================================
char lire_couleur()
{
	char lu(poser_question());
	while (not couleur_valide(lu)) {
		std::cout << "'" << lu << "' n'est pas une couleur valide." << std::endl;
		std::cout << "Les couleurs possibles sont : ., R, G, B, C, Y ou M." << std::endl;
		lu = poser_question();
	}
	return lu;
}

// ======================================================================
void afficher_couleurs(char c1, char c2, char c3, char c4)
{
	std::cout << ' ' << c1 << ' ' << c2 << ' ' << c3 << ' ' << c4;
}

// ======================================================================
void afficher(int nb, char c)
{
	while (nb-- > 0) {
		std::cout << c;
	}
}

// ---- prototype -------------------------------------------------------
void afficher_reponses(char c1, char c2, char c3, char c4,
	char r1, char r2, char r3, char r4);

// ======================================================================
void afficher_coup(char c1, char c2, char c3, char c4,
	char r1, char r2, char r3, char r4)
{
	afficher_couleurs(c1, c2, c3, c4);
	std::cout << " : ";
	afficher_reponses(c1, c2, c3, c4,
		r1, r2, r3, r4);
	std::cout << std::endl;
}

// ======================================================================
void message_gagne(int nb_coups)
{
	std::cout << "Bravo ! Vous avez trouvé en " << nb_coups << " coups." << std::endl;
}

// ======================================================================
void message_perdu(char c1, char c2, char c3, char c4)
{
	std::cout << "Perdu :-(" << std::endl;
	std::cout << "La bonne combinaison était : ";
	afficher_couleurs(c1, c2, c3, c4);
	std::cout << std::endl;
}

/*****************************************************
 * Compléter le code �  partir d'ici
 *****************************************************/

 // ======================================================================
bool couleur_valide(char c)
{
	switch (c)
	{
	case '.':
	case 'R':
	case 'G':
	case 'B':
	case 'C':
	case 'Y':
	case 'M':
		return true;
	default:
		return false;
	}
}

// ======================================================================
bool verifier(const char& c1, char& c2, int& score)
{
	bool verifier{ false };

	if (c1 == c2) 
	{ 
		++score; 
		verifier = true; 
	}
	c2 = 'x';

	return verifier;
}

// ======================================================================
void apparier(const char& cp, char& cr1, char& cr2, char& cr3, int& N)
{
	if (verifier(cp, cr1, N) || verifier(cp, cr2, N) || verifier(cp, cr3, N)) return;
}

// ======================================================================
void afficher_reponses(char c1, char c2, char c3, char c4,
	char r1, char r2, char r3, char r4)
{
	int nbCorrectes{ 0 }, nbPresentes{ 0 }, nbFausses{ 0 }, score{ 0 }, N{ 0 };
	
	// couleur 1
	if (verifier(c1, r1, score)) ++nbCorrectes;
	else
	{
		apparier(c1, r2, r3, r4, N);
		if (N != 0)
		{
			++nbPresentes;
			N = 0;
		}
		else ++nbFausses;
	}

	// couleur 2
	if (verifier(c2, r2, score)) ++nbCorrectes;
	else
	{
		apparier(c2, r1, r3, r4, N);
		if (N != 0)
		{
			++nbPresentes;
			N = 0;
		}
		else ++nbFausses;
	}

	// couleur 3
	if (verifier(c3, r3, score)) ++nbCorrectes;
	else
	{
		apparier(c3, r1, r2, r4, N);
		if (N != 0)
		{
			++nbPresentes;
			N = 0;
		}
		else ++nbFausses;
	}

	// couleur 4
	if (verifier(c4, r4, score)) ++nbCorrectes;
	else
	{
		apparier(c4, r1, r2, r3, N);
		if (N != 0)
		{
			++nbPresentes;
			N = 0;
		}
		else ++nbFausses;
	}

	// affichage
	afficher(nbCorrectes, '#');
	afficher(nbPresentes, '+');
	afficher(nbFausses, '-');
}

// ======================================================================
bool gagne(char c1, char c2, char c3, char c4,
	char r1, char r2, char r3, char r4)
{
	return (c1 == r1 && c2 == r2 && c3 == r3 && c4 == r4);
}

// ======================================================================
void jouer(int coupMax = 8)
{
	int nbCoup{ 0 };
	char r1{ tirer_couleur() }, r2{ tirer_couleur() }, r3{ tirer_couleur() }, r4{ tirer_couleur() };
	char c1{ 'x' }, c2{ 'x' }, c3{ 'x' }, c4{ 'x' };

	do
	{
		c1 = lire_couleur();
		c2 = lire_couleur();
		c3 = lire_couleur();
		c4 = lire_couleur();

		afficher_coup(c1, c2, c3, c4, r1, r2, r3, r4);
		++nbCoup;
	} while (!gagne(c1, c2, c3, c4, r1, r2, r3, r4) && nbCoup < coupMax);

	if (nbCoup >= coupMax) message_perdu(r1, r2, r3, r4);
	else message_gagne(nbCoup);
}

/*******************************************
 * Ne rien modifier après cette ligne.
 *******************************************/

int main()
{
	jouer();
	return 0;
}
