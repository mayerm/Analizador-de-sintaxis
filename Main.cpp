#include <iostream>
#include <cstdlib>
#include <cctype>
#include <stdio.h>
#include <string.h>

using namespace std;
struct nodo
{
    char nro[30];
    struct nodo *sgte;
};
struct cola
{
    nodo *delante;
    nodo *atras  ;
};
enum Estado {INICIO, Q1, Q2, Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, FINAL, ERROR};
Estado Reconocer(const string& inputString);
void encolar( struct cola &q, char valor [30]);
int main ()
{
struct cola q,aux;
    q.delante = NULL;
    q.atras   = NULL;
    char dato[30];
    int i=1,f=0,cant, cont;
    cout<<"Integrese sus lineas de programacion:"<<endl
        <<"                                     Ejemplo: if(a<b)"<<endl
        <<"                                              {"<<endl
        <<"                                                 algo;"<<endl
        <<"                                              }"<<endl
        <<"                                              else"<<endl
        <<"                                              {"<<endl
        <<"                                                 algo;"<<endl
        <<"                                              }"<<endl;
    cin>>dato;
    do
    {
        if (dato[0]=='0')
            break;
        encolar( q, dato );
        cin>>dato;
        i++;
    }
    while(dato!="0");
    system("cls");
    char linea[30],palabras [i][30];
    struct nodo *aux2;
    aux2 = q.delante;
    while( aux2 != NULL )
   {
        strcpy (linea,aux2->nro);
        strcpy (palabras[f],linea);
        aux2 = aux2->sgte;
        f++;
    }
Estado ultimo = Reconocer(palabras[0]);
if (ultimo != FINAL)
{
    cout<<""<<palabras[0]<<"    Error De Sentencia"<<endl;
}
f=2;
if (palabras[1][0]=='{')
    {
        while (palabras[f][0]!='}'&& f<i-1)
        {
            cant= strlen(palabras[f]);
            if (palabras[f][cant-1]!=';')
            {
                cout<<""<<palabras[f]<<"    Falta punto y coma"<<endl;
            }
            f++;
        }
        if(f==i-1)
        {
            cout<<palabras[f]<<"    Luego de esta linea se esperaba cerrar llave"<<endl;
        }
    }
    else
    {
        cout<<palabras[1]<<"    Antes de esta linea se espera abrir llave"<<endl;
    }
    f++;
    if (palabras[f]=="else")
    {
        f++;
        if (palabras[f][0]=='{')
    {
        while (palabras[f][0]!='}'&& f<i-1)
        {
            cant= strlen(palabras[f]);
            if (palabras[f][cant-1]!=';')
            {
                cout<<""<<palabras[f]<<"    Falta punto y coma"<<endl;
            }
            f++;
        }
        if(f==i-1)
        {
            cout<<palabras[f]<<"    Luego de esta linea se esperaba cerrar llave"<<endl;
        }
    }
    else
    {
        cout<<palabras[1]<<"    Antes de esta linea se espera abrir llave"<<endl;
    }
    }
    return 0;
}


Estado Reconocer(const string& inputString)
{
unsigned int pos =0;
Estado actual = INICIO;
bool rechazada=false;
while (not rechazada and pos < inputString.length())
    {
        char simbolo = inputString[pos];
        switch (actual)
        {
            case INICIO:
                if (simbolo=='I'||simbolo=='i')
                {
                    actual = Q1;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q1:
                if (simbolo=='F'||simbolo=='f')
                {
                    actual = Q2;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q2:
                if (simbolo=='(')
                {
                    actual = Q3;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q3:
                if (isalpha(simbolo))
                {
                    actual = Q4;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q4:
                 if (isalpha(simbolo))
                {
                    actual = Q4;
                }
                else if(isdigit(simbolo))
                {
                    actual = Q4;
                }
                else if (simbolo=='<')
                {
                    actual= Q5;
                }
                else if (simbolo=='>')
                {
                    actual = Q6;
                }
                else if (simbolo=='!')
                {
                    actual= Q8;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q5:
                 if (isalpha(simbolo))
                {
                    actual = Q7;
                }
                else if (simbolo=='=')
                {
                    actual = Q10;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q6:
                 if (isalpha(simbolo))
                {
                    actual = Q7;
                }
                else if (simbolo=='=')
                {
                    actual = Q10;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q7:
                if (isalpha(simbolo))
                {
                    actual = Q7;
                }
                else if(isdigit(simbolo))
                {
                    actual = Q7;
                }
                else if (simbolo==')')
                {
                    actual= FINAL;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q8:
                if (simbolo=='=')
                {
                    actual = Q9;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q9:
                if (isalpha(simbolo))
                {
                    actual = Q7;
                }
                else
                {
                    rechazada= true;
                }
            break;
            case Q10:
                if (isalpha(simbolo))
                {
                    actual = Q7;
                }
                else
                {
                    rechazada= true;
                }
            break;
        }
        pos++;
        }
        if (rechazada)
        {
            return ERROR;
        }
        return actual;
    }
void encolar( struct cola &q, char valor [30] )
{
     struct nodo *aux = new(struct nodo);

     strcpy (aux->nro,valor);
     aux->sgte = NULL;

     if( q.delante == NULL)
         q.delante = aux;   
     else
         (q.atras)->sgte = aux;

     q.atras = aux;        

}
