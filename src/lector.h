#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>

struct entrada_particion
{
    uint8_t estado;
    uint8_t chs_inicio[3];
    uint8_t tipo;
    uint8_t chs_fin[3];
    uint32_t lba_inicio;
    uint32_t sectores;
} __attribute__((packed));

struct mbr
{
    uint8_t codigo_arranque[446];
    struct entrada_particion particiones[4];
    uint16_t firma;
} __attribute__((packed));
struct mbr mi_mbr;
int leer_tabla(const char* ruta_img)
{
    char buffer[4096];
    ssize_t n;
    int fd_img = open(ruta_img, O_RDONLY);
    if (fd_img == -1)
    {
        perror("open dispositivo");
        return -1;
    }

    n = read(fd_img, &mi_mbr, 512);
    if (n != 512)
    {
        printf("Error: no se pudieron leer 512 bytes (leídos: %zd)\n", n);
        close(fd_img);
        return -1;
    }

    if (mi_mbr.firma != 0xAA55)
    {
        printf("No es una tabla de particiones válida (firma: 0x%04X)\n", mi_mbr.firma);
        close(fd_img);
        return -1;
    }

    for (int i = 0; i < 4; i++)
    {
        if (mi_mbr.particiones[i].tipo == 0)
        {
            continue;
        }

        printf("Particion %d:\n", i + 1);
        printf("  Tipo: 0x%02X\n", mi_mbr.particiones[i].tipo);
        printf("  Estado: 0x%02X\n", mi_mbr.particiones[i].estado);
        printf("  LBA Inicio: %u\n", mi_mbr.particiones[i].lba_inicio);
        printf("  Sectores: %u\n", mi_mbr.particiones[i].sectores);
        printf("  Tamano: %u MB\n", (mi_mbr.particiones[i].sectores * 512) /(1024 * 1024));
    }

    close(fd_img);
    return 0;
}