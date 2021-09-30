/* la fonction plus(int, int) revoie la somme de ses paramètres */
int plus(int a, int b){
    return a+b;
}

int main
    (void) {
        printf("%d\n", plus(4, 7));
        getchar(); // getchar() attend un retour chariot
        return 0;
    }