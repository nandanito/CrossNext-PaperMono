# CrossNext para PaperMono

[English](README.md) · [Notas de PaperMono](docs/papermono.md) · [Instalación](docs/install.md) · [Novedades y créditos](docs/crossnext-changes.md)

Lectura, herramientas de estudio y juegos para el **M5Stack PaperMono** y el
PaperMono-Lite. Lee un libro, guarda vocabulario, repasa flashcards, registra tu
progreso y juega sin cambiar de dispositivo.

Es una adaptación de [CrossNext](https://github.com/manuelx900/CrossNext), que
parte de [CrossPlay 1.14.2](https://github.com/ma-r-s/crossplay) y
[CrossPoint 1.6.5](https://github.com/crosspoint-reader/crosspoint-reader), con el
FreeInk SDK. El lector, las apps y los juegos proceden de esos proyectos; este fork
añade lo que necesita el PaperMono. Referencias adicionales:
[CrossInk](https://github.com/uxjulia/CrossInk),
[CrossDiTo](https://github.com/dito94/CrossDiTo) y
[VCodex](https://github.com/franssjz/cpr-vcodex); consulta los
[créditos](docs/crossnext-changes.md). Para el Xteink X4 Pro, instala
[CrossNext original](https://github.com/manuelx900/CrossNext).

> [!NOTE]
> **Adaptación inicial.** En un PaperMono se han probado la instalación por USB,
> la microSD, la lectura, el paso de página y la salida de un libro. El resto del
> hardware aún se está comprobando; consulta la
> [lista de verificación](docs/papermono.md#hardware-verification).

![Pantallas de CrossNext](docs/images/overview.png)

## En el PaperMono

Ambos modelos usan el mismo firmware. El Lite no tiene NFC ni LoRa.

| Hardware | En este firmware |
| --- | --- |
| Pantalla (480 × 800) y táctil | Compatible |
| Dos botones laterales | Pasan página; mantenidos, cambian de capítulo |
| Botón de encendido | Una pulsación suspende y reactiva |
| Luz frontal | Brillo desde el gesto del borde superior; el tono no es ajustable |
| microSD | FAT32 o exFAT, con tabla de particiones MBR |
| Unidad USB | Compatible, aún sin probar en un PaperMono |
| Reloj (RX8130) | Compatible |
| Giroscopio (BMI270) | **Pasar página inclinando**, desactivado por defecto; aún sin probar |
| Micrófono, zumbador, LED RGB | Solo controladores del SDK; ninguna app los usa todavía |
| LoRa, NFC | No compatibles |

### Controles táctiles

El PaperMono no tiene botones de Inicio ni Atrás, así que se usan gestos:

| Acción | Gesto |
| --- | --- |
| Atrás | Desliza hacia la derecha desde el borde izquierdo |
| Inicio | Desliza hacia arriba desde el borde inferior |
| Salir de un libro | Desliza hacia arriba desde el borde inferior y elige **Más → Volver al menú Inicio** |
| Luz frontal | Desliza hacia abajo desde el borde superior |
| Pasar página | Toca o desliza en la página, o usa los botones laterales |

Dentro de un libro, el gesto del borde izquierdo vuelve una página y el del borde
inferior abre la hoja de Índice, Fuente, Diseño y Más del lector. Por eso para
salir de un libro hay que pasar por **Más**.

## Instalación

Todavía no hay versiones publicadas, así que compila e instala desde las fuentes.
La primera instalación debe hacerse por USB: también escribe la tabla de
particiones que necesita este firmware. Una actualización desde CrossPoint por
microSD o en línea no cabe.

1. Instala [PlatformIO](https://platformio.org/install/cli), clona este repositorio
   y compílalo una vez con `pio run -e papermono`. La primera compilación también
   instala las herramientas de grabación.
2. Conecta el PaperMono por USB-C y mantén pulsado el botón de encendido unos dos
   segundos, hasta que parpadee el LED rojo. Es el modo de descarga.
3. Haz una copia del firmware actual y guárdala en un lugar seguro:
   ```bash
   ~/.platformio/penv/bin/esptool --chip esp32s3 read-flash 0 0x1000000 papermono-backup.bin
   ```
4. Instala desde la carpeta del repositorio:
   ```bash
   pio run -e papermono -t upload
   ```
   Graba el cargador de arranque y la tabla de particiones además de la app. Si no
   se reinicia, pulsa dos veces el botón de encendido para apagarlo y una vez para
   encenderlo.

Para volver al firmware anterior, graba la copia en modo de descarga:
`~/.platformio/penv/bin/esptool --chip esp32s3 write-flash 0 papermono-backup.bin`.

Cuando haya versiones publicadas, **Ajustes → Dispositivo → Verificar
actualizaciones** instalará las nuevas desde los
[GitHub Releases de este fork](https://github.com/nandanito/CrossNext-PaperMono/releases),
con el archivo `firmware-papermono.bin` de cada versión. Consulta
[actualizaciones en línea](docs/install.md#online-update-source).

## Preparar la microSD

1. Formatea la tarjeta en **FAT32** (o exFAT) con tabla de particiones **Master
   Boot Record**. En un Mac, abre Utilidad de Discos, elige **Visualización →
   Mostrar todos los dispositivos**, selecciona la tarjeta y elige MS-DOS (FAT) y
   Master Boot Record. Con una tabla GUID, el arranque muestra "SD card error".
2. Descarga `CrossNext-Resources.zip` de las
   [versiones de CrossNext](https://github.com/manuelx900/CrossNext/releases),
   descomprímelo y copia sus **carpetas** a la raíz de la tarjeta. Contiene las
   fuentes del lector, los diccionarios y el contenido que necesitan Aventura
   lectora, PET y The Intercept.
3. Guarda tus libros en una carpeta como `/Books`. La biblioteca encuentra EPUB,
   TXT, Markdown y XTC/XTCH hasta cinco carpetas de profundidad, pero omite las
   carpetas de recursos (`apps`, `fonts`, `dictionaries`, `licenses`, `flashcards`,
   `sleep`, `wallpaper`, `wallpapers`) y todo lo que empiece por un punto.

También puedes añadir libros por Wi-Fi: abre **Enviar archivos**, conéctate a una
red y abre en el navegador la dirección que aparece. Calibre puede enviar libros
del mismo modo; consulta la [guía de usuario](USER_GUIDE.md#351-calibre-wireless-transfers).

## PET: tu compañero de lectura

PET convierte tu rutina de lectura en la historia de un compañero virtual.
Elige un huevo, ponle nombre y acompáñalo mientras crece con tus lecturas.

- **Estadísticas de lectura:** consulta el tiempo leído, los días de lectura
  y tus rachas.
- **Dificultad y metas:** adapta la dificultad de los cuidados y tu objetivo
  diario de lectura a tu rutina.
- **Cuidados diarios:** alimenta, limpia y cuida a tu mascota, atendiendo sus
  necesidades y su salud.
- **Juegos y cariño:** acaricia a tu compañero y juega a minijuegos para
  mejorar su ánimo.
- **Un hogar propio:** consigue muebles y adornos leyendo y decora su
  habitación a tu gusto.
- **Recuerdos y generaciones:** descubre recuerdos a medida que avanzas,
  sigue sus etapas de vida y consulta las generaciones anteriores.

![PET: estado, cuidados, hogar y recuerdos](docs/images/pet.png)

PET necesita `CrossNext-Resources.zip` en la microSD.
Consulta [la guía de PET](docs/apps/pet.md) y
[las novedades de v1.1.6](docs/releases/CrossNext-v1.1.6.md).

## Qué incluye

- Lectura de EPUB, texto, Markdown y cómics XTC/XTCH; biblioteca con portadas y archivos.
- Estadísticas, lecturas recientes y terminadas, calendario y aventura lectora.
- Flashcards desde archivos/Anki, repaso local con FSRS y Palabras desde diccionarios.
- Notas, tareas, hábitos, citas, fondos, reloj, calendario y Pomodoro.
- Juegos y campañas heredados de CrossPlay, con navegación adaptada a pantalla táctil.

Flashcards y Palabras tienen tamaños separados para pregunta/palabra y contenido,
de **10 a 18 pt**, y ajuste inteligente activado por defecto. El texto largo
mantiene paginación y se puede recorrer deslizando. Palabras distingue las
etiquetas Palabra, Definición y Oración de ejemplo. El botón físico de Pomodoro
inicia o pausa el temporizador.

La interfaz conserva el idioma guardado. En una instalación sin configuración
previa comienza en **inglés**; se puede elegir español en Ajustes > Idioma.


## En imágenes

Estas capturas son de CrossNext en el Xteink X4 Pro, que tiene la misma pantalla
de 480 × 800; el PaperMono muestra las mismas pantallas.

### Dos diseños de Inicio

![Dos diseños de Inicio](docs/images/appearances.png)

### Lecturas y estadísticas

![Lecturas y estadísticas](docs/images/statistics.png)

La sincronización opcional con **CrossPoint Sync** reúne el historial de tu cuenta y las nuevas lecturas locales en una sola vista de estadísticas. Lee sin conexión y usa el atajo junto a la batería para sincronizar estadísticas y posiciones de los libros a la vez. Cada libro de la microSD conserva la posición más adelantada entre el lector y tu cuenta. El icono solo aparece al configurar una cuenta compatible. Consulta la [guía de estadísticas](docs/reading-stats.md#crosspoint-sync).

### Juegos

![Juegos](docs/images/games.png)

### Apps y productividad

![Apps y productividad](docs/images/apps.png)

### Flashcards y Palabras

![Flashcards y Palabras](docs/images/study.png)

### Herramientas de lectura

![Herramientas de lectura](docs/images/reading.png)

### Más herramientas

![Más herramientas](docs/images/tools.png)

## Simulador local

En Windows sigue la [preparación del entorno](docs/simulator-windows.md) y abre
`Start-Simulator.cmd`. El navegador muestra el firmware de estas fuentes en
`http://127.0.0.1:8765/`. No hay simulador de PaperMono: simula el X4 Pro, que
ejecuta las mismas pantallas. Incluye libros con sus avisos originales, estadísticas y
progreso ficticio en apps/juegos para capturas. Los ejemplos no son datos de tu
dispositivo. Consulta [el contenido de demostración](docs/simulator-showcase.md).

## Compilar y contribuir

Usa `papermono` para el dispositivo, `gh_release_papermono` para una imagen de
publicación y `simulator_x4_pro` para el simulador. El código conserva otros
entornos heredados, incluidos `x4pro` y `sticky`. No uses `default`, que
corresponde a otro chip.
En el entorno de desarrollo configurado, ejecuta `./scripts_local/check.sh`
desde tu propio árbol de trabajo. En Windows consulta la guía del simulador.
Las automatizaciones heredadas de CrossPlay están limitadas a su repositorio original;
las versiones se publican manualmente.
Las compilaciones y pruebas del simulador no sustituyen las pruebas físicas de
orientación, entrada, memoria y persistencia antes de publicar una versión.

## Licencias

Se conservan [LICENSE](LICENSE), los créditos de CrossPoint, CrossPlay y FreeInk,
y los avisos de sus dependencias. Los recursos tienen sus propias licencias:
consulta `THIRD-PARTY-NOTICES.txt`, `SOURCES.json` y `licenses/` en el paquete de
microSD. Las portadas, libros, diccionarios y fuentes no cambian de licencia por
estar incluidos en CrossNext.

[Novedades de v1.1.6](docs/releases/CrossNext-v1.1.6.md)

## Apoya CrossNext

CrossNext lo desarrolla [manuelx900](https://github.com/manuelx900). Si quieres,
puedes apoyar a su autor y el desarrollo continuo de CrossNext en Ko-fi.

[![Apoyar en Ko-fi](site/assets/support-ko-fi.svg)](https://ko-fi.com/manuelx900)
