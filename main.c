#include <stdio.h>
#include <stdlib.h>
#include "gestion.h"

int main(void) {

    FILE *catalogue = fopen("catalogue.txt","a");
    FILE *utilisateurs = fopen("membres.txt","a");
    
    initialisation();
    menu_choix(catalogue,utilisateurs);

    return 0;
}