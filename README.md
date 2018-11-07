# SalonTV

Control de la Tele LG y el PC que nos sirve de centro multimedia.

El PC ("salon") se controla por diversos tipos de mandos.

La Tele recibe sus ordenes (on, off, vol+, vol-) desde un emisor IR basado en NodeMCU 1.0. 

## Software de control

- Codigo del emisor IR, en directorio "mando".

- EventGhost en PC. Configuracion interactiva, que se guarda con el backup de Salon en zeta.upv.es (G/SYNC/comun/eventGhost.xml). Usa el emisor IR para dar ordenes a la tele.

- Unified Remote ("UR") en PC, opcional, necesario para usar la app. UR. Configuración editando su configuración, que se guarda con el backup de Salon en zeta.upv.es (C/ProgramData/Unified Remote/Remotes/Custom/Salon). Usa el emisor IR para dar ordenes a la tele.

- App. movil "Unified Remote" opcional.

- App. movil "Automate" aún más opcional, para mejorar el uso de UR. Recomendable root en Android.

## Tipos de mandos en el PC

### Mando infrarrojo

Desaconsejado, porque confunde al receptor IR de la tele y se tiene que añadir un retraso de 0.2 segundos antes de enviar a la tele, lo que hace un poco más torpe el manejo.

### Mando RF o bluetooth

Como el Flymouse blanco o el teclado con touchpad. EventGhost detecta que el ordenador se despierta o duerme y enciende y apaga la tele en consecuencia. 

### App. movil

Despierta al PC usando Wake on LAN, enciende/apaga la tele hablando directamente con el emisor IR, y da otras ordenes a traves del servidor UR en el PC. 

Con la ayuda de la app. opcional Automate puede encender todo con un solo botón. Sin Automate, hay que pulsar varios botones para encender PC+TV.

## Software multimedia

- Windows Media Center para ver TDT usando los dos sintonizadores del PC.

- Kodi para pelis y series.
