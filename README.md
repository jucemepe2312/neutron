# Neutron 🧠
**Grabador de imágenes ISO en C puro para Linux.**

Neutron es una herramienta de terminal (TUI) escrita en C que permite grabar imágenes de disco (ISOs) en dispositivos USB de forma segura y sin depender de comandos externos como `dd`.

## ¿Qué hace diferente a Neutron?
- **Seguridad ante todo:** Filtra la lista de dispositivos leyendo `/sys/block/` para mostrar **solo memorias USB extraíbles** (verificando el archivo `removable`), evitando así que borres tu disco duro por accidente.
- **Lectura de MBR:** Antes de grabar, lee el sector de arranque (MBR) del USB para mostrar las particiones existentes y advertirte de lo que se va a borrar.
- **Bajo nivel:** Usa llamadas al sistema POSIX (`open`, `read`, `write`, `fsync`) para copiar los datos bloque por bloque, asegurando que la información llegue físicamente al dispositivo.

## Instalación y uso
*(Aquí pones cómo se compila, ej. gcc neutrontui.c -o neutron)*

## Requisitos
- Linux (funciona mejor en Arch/Manjaro).
- Permisos de superusuario (`sudo`) para escribir en `/dev/sdX`.
