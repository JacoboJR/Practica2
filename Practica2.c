#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int descriptorFile;
	char buffer[256];
	char *buffer_Ptr = &(buffer[0]);
	int nbytes;
	int dir;
	char nuevo[20];
	char direccion[50] = "./";
	DIR *directorio;
	FILE *archivo;
	struct dirent *dirInfo;
	int band = 0;
	struct stat archInfo;

	if(argc < 3)
	{
		printf("Necesito un nombre de directorio y un nombre de archivo");
		return 1;
	}

	dir = mkdir(argv[1], 0777);
	if(dir == -1)
	{
		printf("Deme otro nombre para el directorio: ");
		scanf("%s", nuevo);
		argv[1] = nuevo;
		mkdir(argv[1], 0777);
	}
	else
	{
		printf("directorio creado\n");
	}

	strcat(direccion, argv[1]);
	directorio = opendir(direccion);
	if(!directorio)
	{
		printf("No pude abrir el directorio");
		return -1;
	}
	dirInfo = readdir(directorio);
	while(dirInfo != NULL)
	{
		if(strcmp(dirInfo->d_name, argv[2]) == 0)
		{
			band = 1;//El nombre del archivo ya existe
		}
		dirInfo = readdir(directorio);
	}
	closedir(directorio);

	if(band == 1)
	{
		printf("Dame otro nombre para el archivo");
		scanf("%s", nuevo);
                argv[2] = nuevo;
	}

	strcat(direccion, "/");
	strcat(direccion, argv[2]);
	strcat(direccion, ".txt");

	creat(direccion, 0777);
	descriptorFile = open(direccion, O_WRONLY);
	if(descriptorFile == -1)
	{
		printf("No pude abrir el archivo\n");
		return -1;
	}
	else
	{
		printf("Exito al abrir el archivo\n");
	}
	sprintf(buffer_Ptr, "%s", "Santiago Serratos Mendoza\nEduardo Bernal Figa\nJacobo Jimenez Rangel\nRoberto Migranas Ceja");
	nbytes = write(descriptorFile, buffer_Ptr, strlen(buffer));
	if(nbytes == -1)
	{
		printf("No pude abrir el archivo\n");
	}
	else
	{
		printf("Archivo escrito con exito\n\n");
	}
	close (descriptorFile);

	int sl = symlink(argv[1], argv[2]);
        if(sl == 0)
        {
                printf("Soft link creado\n");
        }

	int l = link(direccion, "./link");
	if(l == 0)
	{
		printf("Hard link creado\n\n");
	}

	stat(direccion, &archInfo);
	printf("inodo: %ld\n",archInfo.st_ino);
	printf("tamaño en bytes: %ld\n",archInfo.st_size);
	printf("numero de enlaces al archivo: %ld\n\n",archInfo.st_nlink);

	printf("ID del dispositivo: %ld\n",archInfo.st_dev);
	printf("proteccion: %d\n",archInfo.st_mode);
	printf("user ID: %d\n",archInfo.st_uid);
	printf("group ID: %d\n",archInfo.st_gid);
	printf("ID del dispositivo: %ld\n",archInfo.st_rdev);
	printf("Tamaño del bloque: %ld\n",archInfo.st_blksize);
	printf("Numero de bloques de 512B: %ld\n",archInfo.st_blocks);
	printf("Hora del ultimo acceso: %ld\n",archInfo.st_atime);
	printf("Hora de la ultima modificacion: %ld\n",archInfo.st_mtime);
	printf("Hora del ultimo cambio de estado: %ld\n",archInfo.st_ctime);
	return 0;
}
