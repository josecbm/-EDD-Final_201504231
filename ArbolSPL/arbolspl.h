#ifndef ARBOLSPL_H
#define ARBOLSPL_H
#define TRUE 1
#define FALSE 0
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _nodo {
   int dato;
   struct _nodo *derecho;
   struct _nodo *izquierdo;
   struct _nodo *padre;
} tipoNodo;

typedef tipoNodo *pNodo;
typedef tipoNodo *Arbol;

int Vacio(Arbol r){
    return r==NULL;
}
int EsHoja(pNodo r){
    return !r->derecho && !r->izquierdo;
}

int Insertar(Arbol *a, int dat) {
   pNodo padre = NULL; /* (1) */
   pNodo raiz = *a;  /* (2) */

   while(!Vacio(raiz) && dat != raiz->dato) {  /* (3) */
      padre = raiz;
      if(dat < raiz->dato) raiz = raiz->izquierdo;  /* (3-a) */
      else if(dat > raiz->dato) raiz = raiz->derecho; /* (3-b) */
   }

   if(!Vacio(raiz)) return;  /* (4) */
   if(Vacio(padre)) {  /* (5) */

      (*a) = (Arbol)malloc(sizeof(tipoNodo));
      (*a)->dato = dat;
      (*a)->izquierdo = (*a)->derecho = NULL;
       return 1;
   }
   else if(dat < padre->dato) { /* (6) */
      raiz = (Arbol)malloc(sizeof(tipoNodo));
      padre->izquierdo = raiz;
      raiz->dato = dat;
      padre->izquierdo->padre = padre;
      raiz->izquierdo = raiz->derecho = NULL;
      //balancear(a,&((*padre)).izquierdo);
      return 1;
   }
   else if(dat > padre->dato) { /* (7) */
      raiz = (Arbol)malloc(sizeof(tipoNodo));
      padre->derecho = raiz;
      raiz->dato = dat;
      padre->derecho->padre= padre;
      raiz->izquierdo = raiz->derecho = NULL;
      //balanceo padre der
      //balancear(a,&((*padre)).derecho);
      return 1;
  }
}

void balancear(Arbol *raiz , pNodo *a){
    if((*a) == raiz ){
        return;
    }else if((*a)->padre->izquierdo==(*a) ){//zig
        pNodo A = (*a)->padre;
        pNodo B = (*a);
        pNodo C = (*a)->izquierdo;
        pNodo D = (*a)->derecho;
        pNodo E = (*a)->padre->derecho;
        B->izquierdo = C;
        B->derecho = A;
        A->izquierdo = D;
        A->derecho = E;
        if(A->padre!=NULL && A->padre->izquierdo == A){
            A->padre->izquierdo=B;
        }
        else if(A->padre!=NULL && A->padre->derecho == A){
                A->padre->derecho = B;
            }
        B->padre = A->padre;
        if(C!=NULL){
            C->padre = B;

        }
        A->padre = B;
        if(D!=NULL){
            D->padre = A;
        }
        if(E!=NULL){
            E->padre = A;
        }
        if(A == raiz){
            raiz = B;
        }
        if(a!=raiz){
          // printf()     "asdf";
              //  balanceo
            balancear(raiz,&((*a)));
            //
         }

    }else if((*a)->padre->derecho == (*a)){
        pNodo A = (*a);
        pNodo B = (*a)->padre;
        pNodo C = (*a)->padre->izquierdo;
        pNodo D = (*a)->izquierdo;
        pNodo E = (*a)->derecho;
        A->derecho = E;
        A->izquierdo = B;
        B->izquierdo = C;
        B->derecho = D;
        if(B->padre!=NULL && B->padre->derecho ==B){
            B->padre->izquierdo = A;

        }
        else if(B->padre!=NULL && B->padre->derecho ==B){
            B->padre->derecho = A;
        }

        A->padre = B->padre;
        B->padre = A;
        if(E!=NULL){
            E->padre = A;
        }
        if(C!=NULL){
            C->padre = B;
        }
        if(D!=NULL){
            D->padre = B;
        }
        if(B==raiz){
            raiz = A;
        }
        if((*a)!=raiz){
           balancear(raiz,&((*a)));
        }
    }
}
void Borrar(Arbol *a, int dat) {
   pNodo padre = NULL; /* (1) */
   pNodo raiz;
   pNodo nodo;
   int aux;

   raiz = *a;
   while(!Vacio(raiz)) { /* Búsqueda (2) else implícito */
      if(dat == raiz->dato) { /* (3) */
         if(EsHoja(raiz)) { /* (3-a) */
            if(padre)/* (3-a-i caso else implícito) */
               if(padre->derecho == raiz) padre->derecho = NULL;  /* (3-a-ii) */
               else if(padre->izquierdo == raiz) padre->izquierdo = NULL; /* (3-a-iii) */
            free(raiz); /* (3-a-iv) */
            raiz = NULL;
            return;
         }
         else { /* (3-b) */
            /* Buscar nodo */
            padre = raiz; /* (3-b-i) */
            if(raiz->derecho) {
               nodo = raiz->derecho;
               while(nodo->izquierdo) {
                  padre = nodo;
                  nodo = nodo->izquierdo;
               }
            }
            else {
               nodo = raiz->izquierdo;
               while(nodo->derecho) {
                  padre = nodo;
                  nodo = nodo->derecho;
               }
            }
            /* Intercambio */
            aux = raiz->dato; /* (3-b-ii) */
            raiz->dato = nodo->dato;
            nodo->dato = aux;
            raiz = nodo;
         }
      }
      else {
         padre = raiz;
         if(dat > raiz->dato){
              raiz = raiz->derecho; /* (4) */
              //balancear(padre->derecho);
         }  else if(dat < raiz->dato){
             raiz = raiz->izquierdo; /* (5) */
             //balancear(raiz->izquierda);
         }
      }
   }
}


void PreOrden(Arbol a, void (*func)(int*)) {
   func(&(a->dato)); /* Aplicar la función al dato del nodo raiz */
   if(a->izquierdo) PreOrden(a->izquierdo, func); /* Subárbol izquierdo */
   if(a->derecho) PreOrden(a->derecho, func);     /* Subárbol derecho */
}
void Mostrar(int *d)
{
   printf("%d, ", *d);
}
char* graficar(Arbol* arbol){
    char* retorno = (char*)calloc(255, sizeof(char));
    char* grafo = "\n digraph grafo {\n node [style=filled]; label = \"Arbol SPL\"; color=blue \n";
    GraficarArbol(arbol,&grafo);
    FILE *file;
    file = fopen("/home/josesito/Documents/arb.txt", "w+");
    fputs(grafo, file);
    fputs("}", file);
    fclose(file);
    system("dot -Tpng /home/josesito/Documents/arb.txt -o  /home/josesito/Documents/arb.png");
  //  system("xdg-open /home/josesito/Documents/arb.png");
    return grafo;
}

void GraficarArbol(Arbol* raiz, char** retorno){
    if((*raiz) != NULL){
        GraficarArbol(&((*raiz)->izquierdo),retorno);

        if((*raiz)->izquierdo!=NULL){
            char* cad1;
            cad1 = (char*)calloc(255, sizeof(char));
            sprintf(cad1,"%d",(*raiz)->dato);
            char* cad2 =  (char*)calloc(255, sizeof(char));
            sprintf(cad2,"%d",(*raiz)->izquierdo->dato);

            char* gr = (char*)calloc(255, sizeof(char));
            strcat(gr, *retorno);
            strcat(gr, cad1);
            strcat(gr, "->");
            strcat(gr, cad2);
            strcat(gr, "\n ");
            *retorno = gr;
        }
        if((*raiz)->derecho!=NULL){
            char* cad1 =  (char*)calloc(255, sizeof(char));
            sprintf(cad1,"%d",(*raiz)->dato);
            char* cad2 =  (char*)calloc(255, sizeof(char));
            sprintf(cad2,"%d",(*raiz)->derecho->dato);

            char* gr = (char*)calloc(255, sizeof(char));

            strcat(gr, *retorno);
            strcat(gr, cad1);
            strcat(gr, "->");
            strcat(gr, cad2);
            strcat(gr, "\n ");
            *retorno = gr;
        }
        GraficarArbol(&((*raiz)->derecho),retorno);
    }
}
int Buscar(Arbol *a, int dat) {
   pNodo nodo = *a;
   pNodo aux = *a;
   while(!Vacio(nodo)) {
      if(dat == nodo->dato){
//         raiz->izquierdo = (*a)->izquierdo;
//         raiz->izquierdo = raiz->padre;
//         (*a) = raiz;
          //zig
            pNodo* padre = nodo->padre;
            if(&((*padre)->izquierdo)!=NULL){
                (*padre)->izquierdo = nodo->derecho;
                (*padre)->padre = nodo;
            }

            nodo->derecho = padre;

            (*a) = nodo;


             aux->derecho = (*a);
             (*a)->izquierdo = nodo->derecho;
             nodo->derecho =aux->derecho;
             (*a) = nodo;

          return dat;
      }/* dato encontrado  (2) */
      else if(dat < nodo->dato) nodo = nodo->izquierdo;  /* (3) */
      else if(dat > nodo->dato) nodo = nodo->derecho; /* (4) */
   }
   return 0; /* No está en árbol (1) */
}

#endif // ARBOLSPL_H
