#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "funciones.h"

int main(void)
{	
    char *inputBuffer;
    char recurso[80];
    char siguiente[80];
    char *info;
    //int estado;
    FILE *fs;
    char comsinfo[5][80]= {"testparm -s ",
	                   "| sed -e '/",/*SIGUIENTE*/ 
	                   "/,$d' ",
			   "| sed -s -n '/",/*RECURSO*/
	                   "/,$p'"};
    int tcominfo;
    char *cominfo;

    inputBuffer = entrada();
    separar(recurso,inputBuffer,'[');
    separar(recurso,inputBuffer,'[');
    separar(siguiente,inputBuffer,'&');

    tcominfo = strlen(comsinfo[0]) + strlen(comsinfo[1]) + strlen(comsinfo[2])
	     + strlen(comsinfo[1]) + strlen(comsinfo[2]) + strlen(recurso) 
	     + strlen(siguiente);
    cominfo = malloc(tcominfo);
    if(strcmp(siguiente,"")!=0)
    	sprintf(cominfo,"%s%s%s%s%s%s%s",comsinfo[0], comsinfo[1],siguiente,comsinfo[2]
	 	       ,comsinfo[3],recurso,comsinfo[4]);
    else
        sprintf(cominfo,"%s%s%s%s",comsinfo[0],comsinfo[3],recurso,comsinfo[4]);
    printf ("Content-type:text/html\n\n");
    printf("<TITLE>Editando [%s</TITLE>\n",recurso);
    //printf("<head>\n<meta charset=\"utf-8\">\n</head>");
    //printf("<p>%s<p>",cominfo);   
    // Cambiando nuevo ID y GID
    if((setuid(0)) < 0) printf("\n<br>setuid: operacion no permitida\n");
    if((setgid(0)) < 0) printf("\n<br>setgid: operacion no permitida\n");
    
    printf("<h5> Informacion del recurso [%s</h5>\n",recurso);
    printf("<textarea id=\"info\" name=\"info\" rows=7 cols=65>\n");
    
    fs = abrir(cominfo);
    if(fs != NULL){
    	info  = (char *) malloc(2048*sizeof(char));
	while(fgets(info, 2048*sizeof(char), fs) != NULL)
	{   
    	    printf(info);
    	}
    }
    cerrar(fs);
    printf("\n</textarea>\n");
    
    printf("<h5>Opciones a editar</h5>");
    printf("<FORM ACTION=\"edit3\" METHOD=\"POST\">\n");	
    printf("<input type=\"hidden\" name=\"name\" value=\"%s\" %s",recurso,"/>\n");
    printf("<input type=\"hidden\" name=\"sgte\" value=\"%s\" %s",siguiente,"/>\n");
    printf("Solo lectura: <select name=\"read only\"><br>\n");
    printf("<option value="">mantener\n");
    printf("<option value=\"yes\">SI\n");
    printf("<option value=\"no\">NO\n");
    printf("</select><br>\n");
    printf("Directorio: <INPUT name=\"dir\"><br>\n");
    printf("Nuevo nombre: <INPUT name=\"newname\"><br>\n ");
    printf("Borrar: <select name=\"borrar\"><br>\n");
    printf("<option value=\"NO\">NO\n");
    printf("<option value=\"SI\">SI\n");
    printf("</select><br>\n");    
    printf("<INPUT type=\"SUBMIT\" VALUE=\"Aplicar\">\n");
    printf("</FORM>");
    return 0;
}
