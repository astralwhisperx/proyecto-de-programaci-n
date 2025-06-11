#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

struct Persona {
    char nombre[50];
    char pista[100];
};

struct Objeto {
    char nombre[50];
    char pista[100];
};

struct Equipo {
    char nombre[50];
};

void agregarPersona() {
    FILE* f = fopen("personas.dat", "ab");
    if (!f) return;
    Persona p;
    printf("Nombre: ");
    fgets(p.nombre, sizeof(p.nombre), stdin);
    p.nombre[strcspn(p.nombre, "\n")] = 0;
    printf("Pista: ");
    fgets(p.pista, sizeof(p.pista), stdin);
    p.pista[strcspn(p.pista, "\n")] = 0;
    fwrite(&p, sizeof(Persona), 1, f);
    fclose(f);
}

void agregarObjeto() {
    FILE* f = fopen("objetos.dat", "ab");
    if (!f) return;
    Objeto o;
    printf("Nombre: ");
    fgets(o.nombre, sizeof(o.nombre), stdin);
    o.nombre[strcspn(o.nombre, "\n")] = 0;
    printf("Pista: ");
    fgets(o.pista, sizeof(o.pista), stdin);
    o.pista[strcspn(o.pista, "\n")] = 0;
    fwrite(&o, sizeof(Objeto), 1, f);
    fclose(f);
}

void agregarEquipo() {
    FILE* f = fopen("equipos.dat", "ab");
    if (!f) return;
    Equipo e;
    printf("Nombre del equipo: ");
    fgets(e.nombre, sizeof(e.nombre), stdin);
    e.nombre[strcspn(e.nombre, "\n")] = 0;
    fwrite(&e, sizeof(Equipo), 1, f);
    fclose(f);
}

void jugarAdivinaQuien() {
    FILE* f = fopen("personas.dat", "rb");
    if (!f) { printf("Sin registros.\n"); return; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Persona);
    if (n == 0) { fclose(f); printf("Sin registros.\n"); return; }
    srand((unsigned)time(NULL));
    long pos = rand() % n;
    fseek(f, pos * sizeof(Persona), SEEK_SET);
    Persona p;
    fread(&p, sizeof(Persona), 1, f);
    fclose(f);
    char intento[50];
    printf("Pista: %s\n", p.pista);
    printf("Quien es? ");
    fgets(intento, sizeof(intento), stdin);
    intento[strcspn(intento, "\n")] = 0;
    if (strcmp(intento, p.nombre) == 0)
        printf("Correcto!\n");
    else
        printf("Incorrecto, era %s\n", p.nombre);
}

void jugarAdivinaCual() {
    FILE* f = fopen("objetos.dat", "rb");
    if (!f) { printf("Sin registros.\n"); return; }
    fseek(f, 0, SEEK_END);
    long n = ftell(f) / sizeof(Objeto);
    if (n == 0) { fclose(f); printf("Sin registros.\n"); return; }
    srand((unsigned)time(NULL));
    long pos = rand() % n;
    fseek(f, pos * sizeof(Objeto), SEEK_SET);
    Objeto o;
    fread(&o, sizeof(Objeto), 1, f);
    fclose(f);
    char intento[50];
    printf("Pista: %s\n", o.pista);
    printf("Cual es? ");
    fgets(intento, sizeof(intento), stdin);
    intento[strcspn(intento, "\n")] = 0;
    if (strcmp(intento, o.nombre) == 0)
        printf("Correcto!\n");
    else
        printf("Incorrecto, era %s\n", o.nombre);
}

void listarEquipos() {
    FILE* f = fopen("equipos.dat", "rb");
    if (!f) { printf("Sin equipos.\n"); return; }
    Equipo e;
    while (fread(&e, sizeof(Equipo), 1, f))
        printf("%s\n", e.nombre);
    fclose(f);
}

int main() {
    int op;
    do {
        printf("1) Agregar persona\n2) Agregar objeto\n3) Agregar equipo\n4) Jugar Adivina quien\n5) Jugar Adivina cual\n6) Ver equipos\n7) Salir\nOpcion: ");
        if (scanf("%d", &op)!=1) op=7;
        getchar();
        switch(op) {
            case 1: agregarPersona(); break;
            case 2: agregarObjeto(); break;
            case 3: agregarEquipo(); break;
            case 4: jugarAdivinaQuien(); break;
            case 5: jugarAdivinaCual(); break;
            case 6: listarEquipos(); break;
        }
    } while(op!=7);
    return 0;
}

