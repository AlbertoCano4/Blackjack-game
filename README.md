# ♠️ Blackjack Game 🃏

Este proyecto es una aplicación de consola para jugar al Blackjack, desarrollada en C++. Permite a un jugador enfrentarse a un crupier (controlado por la IA), gestionar sus estadísticas de juego y guardar su progreso en un archivo. Fue creado como un proyecto universitario para el "Doble Grado en Ingeniería Informática y ADE".

---

## 🛠️ Tecnologías utilizadas

* **C++**: Lenguaje de programación principal del juego.
* **Structs**: Se usaron para crear estructuras de datos para `Cartas`, `Jugador` y `DatosPartida`, lo que permite una gestión eficiente de la información del juego.
* **Manejo de archivos (`fstream`)**: Implementado para leer y escribir los datos de los jugadores en un archivo de texto (`jugadores.txt`), lo que permite que los perfiles (victorias, derrotas, saldo) persistan entre sesiones.
* **Librería estándar (`iostream`, `string`, `cstdlib`)**: Utilizada para operaciones básicas de entrada/salida, manipulación de cadenas de texto y generación de números aleatorios para barajar las cartas.

---

## ✨ Características

* **Perfiles de jugador**: Los jugadores pueden crear un perfil con un nombre de usuario único. El juego rastrea sus victorias, derrotas y un contador especial para las victorias con Blackjack.
* **Datos persistentes**: Toda la información del jugador se guarda en un archivo (`jugadores.txt`), por lo que el progreso no se pierde al cerrar el juego.
* **Sistema de apuestas**: El juego incluye un sistema sencillo de apuestas en el que los jugadores pueden apostar parte de su saldo.
* **Gestión de saldo**: Los jugadores pueden consultar su saldo actual y recargar la cuenta.
* **Reglas del juego**: El menú principal permite ver las reglas oficiales del Blackjack.
* **Jugabilidad interactiva**: El juego le pregunta al jugador si quiere una carta más ("pedir") o plantarse, calcula los puntos y determina al ganador.
* **IA del crupier**: El turno del crupier es automático, y este pide cartas hasta que su puntuación es 17 o más.
* **Lógica de desempate**: En caso de empate en puntos, el juego usa el número de cartas para decidir al ganador, añadiendo una capa de estrategia.

---

## 🚀 Guía de inicio

Sigue estos sencillos pasos para tener una copia local del proyecto y ejecutarlo.

### Requisitos

* Un compilador de C++ (ej. g++, clang++).

### Instalación

1.  Clona el repositorio en tu máquina local:
    ```bash
    git clone [https://github.com/tu-usuario/nombre-del-repositorio.git](https://github.com/tu-usuario/nombre-del-repositorio.git)
    ```
2.  Navega hasta el directorio del proyecto:
    ```bash
    cd nombre-del-repositorio
    ```
3.  Compila el código fuente con un compilador de C++:
    ```bash
    g++ -o blackjack MAIN3.cpp
    ```

### Cómo jugar

1.  Ejecuta el programa compilado desde tu terminal:
    ```bash
    ./blackjack
    ```
2.  El juego te pedirá un nombre de usuario. Si es la primera vez que juegas, se creará un perfil nuevo con un saldo inicial.
3.  Usa el menú principal para elegir entre las opciones:
    * **1. JUGAR**: Inicia una nueva partida de Blackjack.
    * **2. VER INFORMACIÓN DE TODOS LOS JUGADORES**: Muestra una lista de todos los jugadores registrados y sus estadísticas.
    * **3. VER INFORMACIÓN JUGADOR**: Revisa las estadísticas de un jugador específico (el tuyo o de otro).
    * **4. SALDO**: Gestiona tu saldo de juego.
    * **5. REGLAS DEL JUEGO**: Lee las reglas del juego.
    * **6. INICIAR SESIÓN DE OTRO JUGADOR**: Cambia a otro perfil de jugador sin tener que reiniciar el programa.
    * **0. SALIR**: Sal del juego y guarda tu progreso.

---

## 👨‍💻 Autor

**Alberto Cano Moreno**

* **Universidad**: CUNEF, Doble Grado en Ingeniería Informática y ADE
  
