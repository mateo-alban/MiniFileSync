# MiniFileSync

Sistema de sincronización automática de archivos desarrollado en lenguaje C utilizando conceptos de Sistemas Operativos.

El proyecto implementa un servicio que monitorea un directorio, detecta cambios en archivos y realiza copias automáticas hacia un directorio de respaldo utilizando procesos, pipes y comunicación entre componentes.


## Características

- Monitoreo automático de directorios.
- Detección de modificaciones mediante información del sistema de archivos (`stat`).
- Copia automática de archivos modificados.
- Procesos Worker para realizar tareas de sincronización.
- Comunicación entre procesos mediante pipes.
- Ejecución como daemon en segundo plano.
- Control del servicio mediante PID.
- Sistema de logs.
- Estadísticas de funcionamiento.
- Adicional: El directorio backu se llama asi por que a la hora de crearlo no admitia el nombre por alguna razon


# Arquitectura del proyecto

MiniFileSync/
-- src/
|
-- main.c
| Punto de entrada del programa.
│
-- daemon.c / daemon.h
│ Manejo del proceso daemon.
│
-- monitor.c / monitor.h
│ Encargado de revisar cambios en el directorio.
│
-- scanner.c / scanner.h
│ Escaneo de archivos utilizando llamadas del sistema.
│
-- worker.c / worker.h
│ Procesos encargados de copiar archivos.
│
-- process.c / process.h
│ Creación y comunicación con procesos Worker.
│
-- copy.c / copy.h
│ Implementación de copia de archivos.
│
-- stats.c / stats.h
│ Manejo de estadísticas.
│
-- logger.c / logger.h
│ Registro de eventos.
│
-- pid.c / pid.h
│ Control del identificador del daemon.
│
-- control.c / control.h

# Funcionamiento

El flujo del sistema es:

Directorio test/
||
Worker
||
Detecta los cambios
||
Pipe
||
Worker
||
Copia Archivo
||
Directiro backu/

# Compilación

El proyecto utiliza un Makefile.

Para compilar:

```bash
make

Lo que genera el ejecutable es: ./minisync
Dejar el servicio: ./minisync stop o ^C ^c

#Prueba de sinronizacion

test/archivo1.txt
||
||
backu/archivo1.txt

# Componentes de Sistemas Operativos Utilizados

## Procesos

El sistema utiliza procesos independientes para ejecutar las tareas de sincronización.

El proceso principal se encarga de iniciar el servicio, crear el monitor y administrar los Workers encargados de realizar las copias.

Funciones utilizadas:

- fork()  
  Permite crear nuevos procesos Worker independientes.

- wait()  
  Permite controlar la finalización de procesos hijos.

- kill()  
  Permite enviar señales para detener el servicio daemon.

---

## Comunicación entre procesos

La comunicación entre el proceso monitor y los Workers se realiza mediante pipes.

El monitor detecta cambios en los archivos y envía la ruta del archivo modificado a los Workers para que realicen la copia correspondiente.

Funciones utilizadas:

- pipe()  
  Creación del canal de comunicación entre procesos.

- write()  
  Envío de información desde el monitor hacia los Workers.

- read()  
  Recepción de información por parte de los Workers.

---

## Sistema de archivos

El proyecto interactúa directamente con el sistema de archivos de Linux para monitorear directorios y obtener información de los archivos.

Se utiliza información como:

- Nombre del archivo.
- Tamaño.
- Fecha de modificación.
- Tipo de archivo.

Funciones utilizadas:

- opendir()  
  Apertura de directorios.

- readdir()  
  Lectura de entradas dentro del directorio.

- stat()  
  Obtención de información del archivo.

- open()
  Apertura de archivos.

- read() y write()  
  Lectura y escritura de datos durante la copia.



## Daemon

MiniFileSync puede ejecutarse como un servicio en segundo plano mediante un proceso daemon.

El daemon permite que el sistema continúe funcionando aunque la terminal donde fue iniciado se cierre.

Características implementadas:

- Separación del proceso principal mediante fork().
- Creación de una nueva sesión con setsid().
- Ejecución independiente del usuario.
- Archivo PID para identificar el proceso activo.

Funciones utilizadas:

- fork()
- setsid()
- chdir()
- dup2()



## Concurrencia

El sistema utiliza múltiples procesos Worker para realizar copias de archivos de manera concurrente.

Esto permite distribuir las tareas de sincronización y evitar que el monitor se bloquee mientras se realizan operaciones de copia.

Mecanismos utilizados:

- Procesos independientes.
- Pipes para comunicación.
- Sincronización mediante llamadas del sistema.

---

## Manejo de señales

El programa utiliza señales del sistema operativo para controlar eventos importantes.

Ejemplo:

- Detención del daemon mediante `SIGTERM`.
- Liberación de recursos antes de finalizar el proceso.

Funciones utilizadas:

- signal()
- kill()


## Registro de eventos (Logging)

El sistema cuenta con un módulo de registro que almacena información sobre las operaciones realizadas.

Los eventos registrados incluyen:

- Archivos sincronizados.
- Operaciones realizadas.
- Errores durante la ejecución.

El mecanismo utilizado es:

- FIFO (named pipe) para comunicación entre procesos.
- Escritura de mensajes de log.



## Estadísticas del sistema

MiniFileSync mantiene estadísticas sobre el funcionamiento del servicio:

- Cantidad de archivos copiados.
- Total de bytes transferidos.
- Número de errores.

Estas métricas permiten evaluar el rendimiento y comportamiento del sistema durante la sincronización.


## Resumen de llamadas al sistema utilizadas

| Función | Uso |
|--------|-----|
| fork() | Creación de procesos |
| pipe() | Comunicación entre procesos |
| read() | Lectura de datos |
| write() | Escritura de datos |
| open() | Apertura de archivos |
| stat() | Información del sistema de archivos |
| opendir() | Apertura de directorios |
| readdir() | Lectura de directorios |
| kill() | Envío de señales |
| signal() | Manejo de señales |
| setsid() | Creación del daemon |
| mmap() | Memoria compartida |