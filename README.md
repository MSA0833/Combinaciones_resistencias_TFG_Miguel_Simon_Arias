# Resistor Calculator

## ¿Cuál es el propósito de este código?

Este código sirve para encontrar la mejor combinación posible de dos resistencias eléctricas a partir de una lista de resistencias disponibles y unos valores objetivo (targets). La combinación puede ser en serie o en paralelo, y se prueba tanto en configuración de estrella como en triángulo. El objetivo es encontrar el valor de resistencia resultante que sea mayor o igual al valor objetivo y que esté lo más cerca posible de él.

En otras palabras, el programa:
- Lee una lista de resistencias disponibles desde un archivo (`resistors.txt`).
- Lee una lista de valores objetivo desde otro archivo (`targets.txt`).
- Calcula las combinaciones y muestra cuál es la mejor opción para cada valor objetivo.

## ¿Qué hace cada fichero?

- **main.c**:  
  Código fuente del programa (en lenguaje C). Aquí se implementa la lógica para:
  - Leer las resistencias del archivo `resistors.txt`.
  - Leer los valores objetivo del archivo `targets.txt`.
  - Probar todas las combinaciones (serie/paralelo y estrella/triángulo).
  - Encontrar la mejor aproximación.
  - Imprimir los resultados en una tabla.

- **resistors.txt**:  
  Contiene una lista de valores de resistencias eléctricas, una por línea.  
  Ejemplo:
  ```
  220
  110
  73
  55
  ...
  ```

- **targets.txt**:  
  Contiene una lista de valores objetivo, uno por línea.  
  Ejemplo:
  ```
  41.63
  21.57
  14.85
  ...
  ```

## ¿Cómo obtener el código con Git?

**Requisitos**:  
- Tener instalado Git. Si no lo tienes, descárgalo de [https://git-scm.com/](https://git-scm.com/) y sigue las instrucciones de instalación.

Una vez instalado Git, abre una terminal o consola de comandos y escribe:

```bash
git clone https://github.com/MSA0833/Combinaciones_resistencias_TFG_Miguel_Simon_Arias.git
```

Esto descargará todos los archivos del proyecto des del repositorio de github a una carpeta en tu ordenador.

## ¿Cómo compilar el código?

**Requisitos**:  
- Tener un compilador de C instalado.
  - En Linux o macOS normalmente ya viene instalado (`gcc`).
  - En Windows puedes instalar MinGW o usar WSL (Windows Subsystem for Linux).

Una vez que tengas el compilador, entra a la carpeta del proyecto (por ejemplo, si se llama `resistors-combination`):

```bash
cd resistors-combination
```

Compila con:

```bash
gcc -o programa main.c -Wall -O2
```

- `gcc` es el compilador.
- `-o programa` indica el nombre del ejecutable que se va a generar.
- `main.c` es el archivo fuente con el código.
- `-Wall` activa las advertencias del compilador (útil para evitar errores).
- `-O2` optimiza el código.

## ¿Cómo ejecutar el programa?

Asegúrate de tener `resistors.txt` y `targets.txt` en la misma carpeta donde está el ejecutable `programa`.

En Linux o macOS:

```bash
./programa
```

En Windows (si usas CMD o PowerShell):

```bash
programa
```
o
```bash
.\programa.exe
```

El programa leerá las resistencias desde `resistors.txt` y los valores objetivo desde `targets.txt`, luego mostrará una tabla con las mejores combinaciones encontradas.

## Resumen de pasos

1. Instala Git y un compilador de C.
2. Clona el repositorio:
   ```bash
   git clone https://github.com/MSA0833/Combinaciones_resistencias_TFG_Miguel_Simon_Arias.git
   ```
3. Entra en la carpeta del proyecto:
   ```bash
   cd Combinaciones_resistencias_TFG_Miguel_Simon_Arias
   ```
4. Compila el programa:
   ```bash
   gcc -o programa main.c -Wall -O2
   ```
5. Asegúrate de tener `resistors.txt` y `targets.txt` en la misma carpeta.
6. Ejecuta el programa:
   ```bash
   ./programa
   ```

## Cómo ejecutar el programa sin instalar Git ni un compilador de C

1. **Abre el repositorio en GitHub**: Ve al siguiente enlace [GitHub Repository](https://github.com/MSA0833/Combinaciones_resistencias_TFG_Miguel_Simon_Arias/tree/main) y haz clic en el botón **Code**.

2. **Inicia Codespaces**:  
   - Aparecerá un menú desplegable; selecciona la opción **Codespaces**.  
   - Crea un nuevo Codespace y espera a que se inicie un entorno de desarrollo integrado (IDE) en la nube.

3. **Compila el programa**:  
   Una vez en el IDE, ejecuta el siguiente comando en la terminal para compilar el programa:  
   ```bash
   gcc -o programa main.c -Wall -O2
   ```

4. **Modifica los archivos necesarios**:  
   Edita los archivos `resistors.txt` y `targets.txt` según tus necesidades.

5. **Ejecuta el programa**:  
   Usa el siguiente comando para ejecutar el programa:  
   ```bash
   ./programa
   ```
---

## Guía de Usuario (Detalles adicionales)

Esta sección explica con mayor detalle la función de cada fichero y cómo prepararlos.

### Ficheros utilizados por el programa

1. **main.c**  
   - Aquí está todo el código fuente.
   - No necesitas modificarlo a menos que desees cambiar la lógica interna.
   - El programa, al ejecutarse, leerá las listas de resistencias y objetivos, probará las combinaciones y mostrará los resultados.

2. **resistors.txt**  
   - Aquí debes poner la lista de resistencias disponibles.
   - Una resistencia por cada línea (por ejemplo: 220, 110, 73, 55...).
   - El programa tomará estos valores y los usará para generar las combinaciones.

3. **targets.txt**  
   - Aquí pones la lista de valores objetivo (los valores que quieres conseguir con la combinación de resistencias).
   - Una línea para cada valor (por ejemplo: 41.63, 21.57, etc.).
   - El programa intentará encontrar, para cada valor objetivo, la combinación que esté igual o por encima de él y más cercana posible.

### Preparación de los Ficheros

- Crea o modifica `resistors.txt` y `targets.txt` con los valores que quieras.
- No es necesario cambiar `main.c` si no quieres alterar la lógica.
- Asegúrate de tener todos estos archivos en la misma carpeta.

### Ejemplo de contenido de `resistors.txt`:

```  
220
110
73
55
44
...
```

### Ejemplo de contenido de `targets.txt`:

```
41.63
21.57
14.85
...
```

El programa leerá estos ficheros, procesará las combinaciones y mostrará los resultados por pantalla.
