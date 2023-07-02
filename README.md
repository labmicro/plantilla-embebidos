# Plantilla de Proyectos

-----

Plantilla de proyectos para trabajos prácticos de Sistemas Embebidos.

**Table of Contents**
- [Proyecto](#proyecto)
- [Forma de uso](#forma-de-uso)
- [License](#license)

## Proyecto

Creacion de capas de abstraccion a partir de un repositorio base.
- Separacion de la parte digital (digital) y del hardware (bsp)
- Implementacion con POO de dicha separacion
- Documentacion del proyecto (no funciona el comando make doc)

## Forma de uso

Para utilizar este repositorio deben:

1. Crear un fork del repositorio en la página de Github. Esto creará un repositorio independiente propiedad del alumno pero que comparte los primeros commits con este repositorio.

2. Clonar el repositorio usando la opción de incializar los submodulos. Si se hace por comandos se debe incluir el parámetro `–recurse-submodules` en el comando de clonación.

3. Configuracion:
- Extraer de muju el ".vscode" a la carpeta principal del proyecto.
- Llevar el openocd.cfg a "./muju/external/base/mcu/lpc4337-m4/openocd" (reemplazar).
- Reemplazar launch.json con la direccion "./muju/external/base/mcu/lpc4337-m4/openocd/openocd.cfg"

4. Comandos:
- make (compila)
- make download (carga en placa)

5. Debugger:
En caso de no funcionar el Debug, agregar en settings.json la linea "cortex-debug.gdbPath": "gdb-multiarch",

## License

This template is distributed under the terms of the [MIT](https://spdx.org/licenses/MIT.html) license.
