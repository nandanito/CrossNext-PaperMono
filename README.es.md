# CrossNext para PaperMono

[English](README.md) · [Novedades y créditos](docs/crossnext-changes.md) · [Notas de PaperMono](docs/papermono.md)

> Este repositorio adapta [CrossNext](https://github.com/manuelx900/CrossNext) al
> **M5Stack PaperMono** y al PaperMono-Lite. Las funciones descritas son las de
> CrossNext y sus capturas se tomaron en el Xteink X4 Pro. Las compilaciones para
> PaperMono son nuevas y aún no se han verificado en el dispositivo; consulta las
> [notas de PaperMono](docs/papermono.md). Para el X4 Pro, instala
> [CrossNext original](https://github.com/manuelx900/CrossNext).

CrossNext reúne lectura, herramientas de estudio y juegos en pequeños dispositivos de tinta electrónica.
Lee un libro, guarda vocabulario, repasa flashcards, registra tu progreso y juega
sin cambiar de dispositivo. Elige entre Inicio con marco o carrusel y personaliza
sus accesos, los controles de lectura y tus fondos de pantalla.

Este fork está dirigido al **PaperMono y PaperMono-Lite** (ESP32-S3).
CrossNext parte de **CrossPlay 1.14.2**, con base **CrossPoint 1.6.5**.
Referencias adicionales: [CrossInk](https://github.com/uxjulia/CrossInk),
[CrossDiTo](https://github.com/dito94/CrossDiTo) y
[VCodex](https://github.com/franssjz/cpr-vcodex); consulta los
[créditos](docs/crossnext-changes.md) para distinguir código heredado de referencias.

La base de [CrossPlay](https://github.com/ma-r-s/crossplay) procede de
[CrossPoint Reader](https://github.com/crosspoint-reader/crosspoint-reader).
El lector y buena parte de los juegos y herramientas proceden de esos proyectos;
este fork adapta la interfaz, la navegación y los flujos de estudio.

![CrossNext para Xteink X4 Pro](docs/images/overview.png)

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

Instala **CrossNext-Resources.zip** en la microSD para usar PET.
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

## Archivos para instalar

Todavía no se ha publicado ninguna versión para PaperMono. Mientras tanto,
compila el entorno `papermono` desde las fuentes (consulta
[Compilar y contribuir](#compilar-y-contribuir)). PaperMono y PaperMono-Lite usan
la misma imagen.

Conserva una copia de la microSD antes de actualizar. Estas imágenes no son para
X4 Pro, X4 ni X3. Consulta [instalación y recuperación](docs/install.md) y las
[notas de PaperMono](docs/papermono.md) para la herramienta y los pasos.
En un PaperMono, **Ajustes → Dispositivo → Verificar actualizaciones** busca
versiones nuevas en los [GitHub Releases de este fork](https://github.com/nandanito/CrossNext-PaperMono/releases).
Se solicita confirmación antes de instalar la aplicación. Cada Release debe incluir
`firmware-papermono.bin` como archivo adjunto independiente; consulta
[la guía de instalación](docs/install.md#online-update-source).

`CrossNext-Resources.zip` contiene fuentes, diccionarios y los contenidos de
Aventura lectora, PET y The Intercept. Instala el paquete actualizado junto a
este firmware; uno anterior puede no incluir los contenidos de las apps nuevas.
Extrae sus carpetas en la raíz de la microSD y conserva sus avisos de
licencia. No contiene firmware ni sustituye tus libros o partidas.

`CrossNext-source.zip` contiene las fuentes limpias, pruebas y recursos necesarios
para desarrollar. Los ZIP de firmware y recursos son archivos para adjuntar a
una publicación; no se necesitan dentro del historial Git de las fuentes.

## Simulador local

En Windows sigue la [preparación del entorno](docs/simulator-windows.md) y abre
`Start-Simulator.cmd`. El navegador muestra el firmware de estas fuentes en
`http://127.0.0.1:8765/`. Incluye libros con sus avisos originales, estadísticas y
progreso ficticio en apps/juegos para capturas. Los ejemplos no son datos de tu
dispositivo. Consulta [el contenido de demostración](docs/simulator-showcase.md).

## Compilar y contribuir

Usa `papermono` para el dispositivo, `gh_release_papermono` para una imagen de
publicación y `simulator_x4_pro` para el simulador; no existe un simulador de
PaperMono. El código conserva otros entornos heredados, incluidos `x4pro` y
`sticky`. No uses `default`, que corresponde a otro chip.
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
