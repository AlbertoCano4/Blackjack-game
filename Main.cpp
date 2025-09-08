//
//  Práctica 3 BlackJack (V2)
//  CUNEF
//  ADEINF-A
//  Doble Grado en Ingenieria Informática y ADE
//  Created by Alberto Cano Moreno on 27/10/22.
//
#include <iostream>
#include <fstream> //Abrir, cerrar y guardar archivos
#include <string>
#include <cstdlib> //Para rand y srand
#include <cstdio>

using namespace std;

typedef struct {
    int ncartas[40]; // El número de cartas debe inicializarse en 40
    int contadorcartas;
}Cartas;

typedef struct {
    string nickjugador;
    int numerodevictorias;
    int numvictoriasconblackjack;
    int numerodederrotas;
    float saldodisponible;
}Jugador;

typedef struct {
    int contadorjugadores;
    Jugador lista[100];
}DatosPartida;

//PROTOTIPOS DE FUNCIONES:
//función encargada de mostrar el menú por pantalla, comprobar que la opción
//escogida sea válida, y devolver la opción escogida
int menu();
//en esta función se desarrolla el turno del jugador, devuelve la puntuación total del jugador
int juegaHumano(Cartas &mazo, Cartas &cartasJugador);
//en esta función se desarrolla el turno del Crupier, devuelve la puntuación total
//del Crupier
int juegaCrupier(Cartas &mazo, Cartas &cartasCrupier);
//función que, dada una mano de cartas calcula los puntos de las cartas de la mano de acuerdo a las reglas del juego
int calculaPuntos(Cartas mano);
//saca una carta del mazo y devuelve su valor
int sacarCartaMazo(Cartas &mazo);
//esta función calcula el ganador de la partida teniendo en cuenta la puntuación y, en caso de empate, el número de cartas de cada uno
int ganador(int puntosJugador, int puntosCrupier, int numCartasJugador, int numCartasCrupier);

//PROTOTIPOS DE PROCEDIMIENTOS:
//dado un mazo de cartas creado, inicializa los valores en orden con los 40 valores de la baraja española
void inicializaMazo(Cartas &mazo);
//dado un mazo de cartas, las mezcla aleatoriamente
void barajar(Cartas &mazo);
// aquí se desarrolla la acción principal del juego
void juegoBlackjack(DatosPartida &d, Jugador &j);
//añade una carta a la mano de cartas
void annadeCarta(Cartas &mano, int carta);
//muestra el mazo de cartas por pantalla
void muestraMazo(Cartas cartas);
//muestra el texto de las reglas de juego por pantalla
void muestraReglas();

// Versión 2:
// devuelve los datos del jugador con el nick especificado
// Si no existe, se crea un nuevo jugador
Jugador iniciarSesion(DatosPartida &d, string nick);
// busca al jugador con el nick especificado y devuelve un entero indicando su posición en la lista. Si no lo encuentra, devuelve -1
int buscaJugador(DatosPartida &d, string nick);
// carga los datos de los jugadores del archivo "jugadores.txt"
void cargaDatos(DatosPartida &d);
// permite consultar y recarggar el saldode un jugador
void gestionSaldo(DatosPartida &d, Jugador &j);
// muestra la información del jugador con el nick especificado
void muestraInfo(DatosPartida d, string nick);
// muestra la información de todos los jugadores registrados
void infoJugadores(DatosPartida d);
// actualiza la lista de jugadores con los datos del jugador j, si no existe lo añade a la lista
void actualizaJugador(DatosPartida &d, Jugador &j);
// añade un nuevo jugador a la lista. Si no cabe, muestra un mensaje de error
void guardaJugador(DatosPartida &d, Jugador &j);
// guarda los datos de todos los jugadores registrados en el archivo "jugadores.txt"
void guardaDatos(DatosPartida &d);

int menu (){ // Se muestran las opciones que puede elegir el jugador.
    cout << "\n------------------------------------------" << endl;
    cout << "    BIENVENIDO A LA MESA DE BLACKJACK"<< endl;
    cout << "------------------------------------------" << endl;
    cout << "1. JUGAR \n2. VER INFORMACIÓN DE TODOS LOS JUGADORES \n3. VER INFORMACIÓN JUGADOR \n4. SALDO "<< endl;
    cout << "5. REGLAS DEL JUEGO \n6. INICIAR SESIÓN DE OTRO JUGADOR \n0. SALIR \nELIGE UNA OPCIÓN:\n" << endl;
    return 0;
}

void muestraReglas(){ // Si en el menu se elige la opcion se muestran las reglas del Blackjack.
    cout << "\nREGLAS DEL BLACKJACK:" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "Antes de comenzar la partida, has de hacer tu apuesta." << endl;
    cout << "Si no tienes suficiente saldo, puedes recargarlo eligiendo la opción 4 del menu." << endl;
    cout << "Al principio, los dos jugadores obtienen dos cartas." << endl;
    cout << "En tu turno, elegiras si quieres una carta más o quieres plantarte." << endl;
    cout << "El ganador de la partida será el que más se aproxime a 21 sin pasarse." << endl;
    cout << "Las cartas numéricas suman su valor, las figuras suman 10 y el As vale 11 o 1."<< endl;
    cout << "La mejor jugada es el Blackjack: conseguir 21 con dos cartas, un As y un 10." << endl;
    cout << "Un blackjack gana sobre un 21 conseguido con más de dos cartas." << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    cout << "volviendo al menu..." << endl;
}

void inicializaMazo(Cartas &mazo){ // Crea el mazo.
    
    for (int i=0; i < 40; i++){ // Se repite tantas veces como número de cartas que tiene la baraja.
        int eleccion = i % 10; // Solo tenemos en cuenta el resto de la división de la posción del array entre 10.
        if (eleccion < 7){
        // Los números del resto que sean menores de 7 en el array
        // Se les debe sumar 1 ya que el array empieza en 0
        // La posicion 0 del array debe corresponder al as, la posición 1 a la carta dos 2...
            mazo.ncartas[i] = eleccion +1;}
        else if (eleccion == 7){ // El siete debe ser como la carta diez en el array
            mazo.ncartas[i] = eleccion +3;}
        else if (eleccion == 8){ // El ocho debe ser como la carta once en el array
            mazo.ncartas[i] = eleccion +3;}
        else if (eleccion == 9){ // El nueve debe ser como la carta doce en el array
            mazo.ncartas[i] = eleccion +3;}
        mazo.contadorcartas++; // Se suma una carta al contador para saber cuales han salido
    }
}

void muestraMazo(Cartas cartas){ // Muestra el mazo
    for (int i=0; i < cartas.contadorcartas; i++){
        cout << cartas.ncartas[i] << "  ";} // Una vez inicializado el mazo, enseña las 40 cartas
}

void barajar(Cartas &mazo){ // Baraja las cartas
    int barajar = 0;
    for (int carta = 0; carta <= mazo.contadorcartas; carta++){
        int valordecarta = rand()%40; // Se hace sobre 40 al existir 40 cartas en la baraja
        int tipocarta = rand()%4; // Se hace sobre 4 porque existen 4 tipos de cartas
        barajar = mazo.ncartas[valordecarta];
        mazo.ncartas[valordecarta] = mazo.ncartas[tipocarta];
        mazo.ncartas[tipocarta] = barajar; // Se mezclan las cartas
        }
}

int sacarCartaMazo(Cartas &mazo){ // Saca la primera carta del mazo una vez barajado.
    int primeracarta = mazo.ncartas[0];
    for(int cartas = 0; cartas < 40; cartas++){
        // Recorremos las 40 posiciones de array, que equivalen a las 40 cartas del mazo.
        if (cartas == 39){
            mazo.ncartas[cartas] = 0;
        //Cuando se hayan recorrido las 39 posiciones del array el valor del mazo es igual a 0,
        //ya que no quedaran más cartas por recorrer.
        }
        else{
        // Como el array empieza en 0, por cada posición que se recorra se le debe sumar un punto para que ninguna carta sea 0
            mazo.ncartas[cartas] = mazo.ncartas[cartas + 1]; }
    }
    return primeracarta; // Va sacando las cartas en orden
}

void annadeCarta(Cartas &mano, int carta) { // Añade una carta al jugador/crupier cuando sea necesario
    mano.ncartas[mano.contadorcartas] = carta;
    // "carta" recibe un valor que corresponde con la carta
    // que toca que se le añada al jugador o al crupier.
    mano.contadorcartas++;
    // Cada vez que salga una carta se le ira sumando al contador para saber cuantas han salido del mazo.
}

void juegoBlackjack(DatosPartida &d, Jugador &j){ // Se ejecuta cuando el jugador quiere jugar.
    
    Cartas mazo; // Dentro de Cartas se guarda el mazo.
    mazo.contadorcartas = 0; // En la mesa debe haber 0 cartas al principio.
    
    Cartas cartasjugador; // Cartas guarda las cartas del jugador.
    cartasjugador.contadorcartas = 0; // El jugador debe tener 0 cartas antes de añadir alguna
    Cartas cartasCrupier; // Cartas guarda las cartas del crupier.
    cartasCrupier.contadorcartas = 0;// El Crupier debe tener 0 cartas antes de añadir alguna.
    inicializaMazo(mazo); // Llamamos a la función que crea el mazo.
    barajar(mazo); // Llamamos a la función que baraja las cartas para que salgan desordenadas.
    
    double bet = 0; // Guarda la apuesta que hace el jugador
    do {
        cout << "¿Cuánto dinero quieres apostar? Tienes " << j.saldodisponible << " €" << endl;
        cout << "Cuánto quieres apostar: " << endl;
        cin >> bet;
        
        if (bet > j.saldodisponible){
            cout << "No puedes apostar, tu saldo es inferior a la apuesta" << endl;
            cout << "REDUZCA SU APUESTA" << endl;
            cout << endl;
        }
    }while (bet > j.saldodisponible);
    // Si la apuesta está por encima del saldo, el programa vuelve a preguntarte por la apuesta
    // Que quieres hacer hasta que este por debajo del saldo disponible del jugador elejido
    // La apuesta se realiza antes de que repartan las cartas
    
    for (int i = 0; i<2; i++){//repartimos al jugador sus dos cartas iniciales.
        annadeCarta(cartasjugador, sacarCartaMazo(mazo)); }
    for (int i = 0; i<2; i++){ //repartimos al crupier sus dos cartas iniciales.
        annadeCarta(cartasCrupier, sacarCartaMazo(mazo)); }
    
    cout << endl << "Se han repartido las cartas." << endl;
    cout << "La primera carta del crupier es un " << cartasCrupier.ncartas[0] << endl;
    // La primera carta del mazo barajado le pertenece al crupier, la cual se debe mostrar.
    // Después de enseñar la primera carta del crupier se ejecuta la función en la que juega el jugador.
    int puntosJugador = juegaHumano(mazo, cartasjugador);
    // puntosJugador guarda los puntos que se han obtenido en la funcion juegaHumano.
    int numCartasJugador = cartasjugador.contadorcartas;
    //Por cada carta que se lleve el jugador se le resta a la baraja.
    
    if (puntosJugador > 21)
    {
        cout << "Te pasas de 21. \n¡Pierdes! \nCartas Crupier: ";
        muestraMazo(cartasCrupier) ;
        cout << "\n¡Gana el crupier!" << endl;
        // Cuando pides cartas pero te pasas de 21, se muestran las 2 cartas del crupier.
        j.saldodisponible = j.saldodisponible - bet; // Resta la apuesta al saldo
        j.numerodederrotas++; // Se le añade una derrota al contador de derrotas
        guardaDatos(d); // Guarda la derrota y el saldo del jugador
    }
    else
    {
        // Cuando el Jugador decide no recibir más cartas comienza a jugar el crupier
        int puntosCrupier = juegaCrupier(mazo, cartasCrupier);
        // puntosCrupier guarda los puntos que se han obtenido en la funcion juegaCrupier
        int numCartasCrupier = cartasCrupier.contadorcartas;
        //Por cada carta que se lleve el crupier se le resta a la barja
        if(puntosCrupier > 21)
        {
            //Cuando termina tu turno por tu propia decisión y el crupier añadiendo cartas se pasa de 21 ganas automaticamente.
            cout << "El crupier se pasa de 21." << endl;
            cout << "¡Has Ganado!" << endl;
            j.saldodisponible = j.saldodisponible + bet;
            // En caso de victoria el saldo del jugador será igual al que tenía antes de apostar
            // más el dinero que apostó
            j.numerodevictorias++; // Se suma una victoria
            guardaDatos(d); // Se guardan los datos
            actualizaJugador(d,j); // Se actualizan las victorias y el saldo del jugador
        }
        else
        {
            // Si el crupier no pierde por pasarse de 21 se ejecuta la función que decide quien gana
            int win = ganador (puntosJugador, puntosCrupier, numCartasJugador, numCartasCrupier);
            // Dependiendo de que resultado de la funcion ganador se mostrará quien gana
                if (win == 1){ // Cuando la variable ganador devuelve 1 has ganado la partida.
                    if (puntosJugador == 21 && numCartasJugador == 2){
                        cout << "El jugador tiene BLACKJACK" << endl;
                        cout << "¡Has ganado!" << endl;
                        j.saldodisponible = j.saldodisponible + bet; // Igual que en la línea 239 y 240
                        j.numerodevictorias++;
                        j.numvictoriasconblackjack++;
                        // Cuando Obtienes la victoria con blackjack, es decir, cuando con 2 cartas obtienes 21
                        // Se suma al contador de victorias con blackjack
                        guardaDatos(d);
                    }
                    else{ // Cuando no ganas con tres o más cartas
                        cout << "¡Has ganado!" << endl;
                        j.saldodisponible = j.saldodisponible + bet;
                        j.numerodevictorias++;
                        guardaDatos(d);
                    }
                }
                else if (win == -1){// Cuando la variable ganador devuelve -1 has perdido la partida.
                    if (puntosCrupier == 21 && numCartasCrupier == 2){
                        cout << "El Crupier tiene BLACKJACK" << endl;
                        cout << "¡Gana el crupier!" << endl;
                    }
                    else{
                        cout << "¡Gana el crupier!" << endl;
                    }
                    j.saldodisponible = j.saldodisponible - bet;
                    // En caso de derrota el saldo del jugador será igual al que tenía antes de apostar
                    // menos el dinero que apostó
                    j.numerodederrotas++;
                    guardaDatos(d);
                }
                else if (win == 0){
                    // Cuando la variable ganador devuelve 0 es porque tienen el mismo nº de puntos y cartas.
                    cout << "Ambos jugadores teneis el mismo número de cartas y puntos, por lo que existe un empate total" << endl;
                    // Cuando se obtiene empate ni se suman ni se restan (Victorias o Derrotas) y tampoco se le resta saldo al jugador
                }
            }
        }
    }

int calculaPuntos(Cartas mano){ // Calcula los puntos de las cartas.
    
    int points = 0; // "points" guarda el valor de las cartas como puntos.
    int as = 0; //Se crea la variable "as" para poder decidir que valor tiene el as si 11 o 1.
    for (int i = 0; i < mano.contadorcartas; i++){
        // Da valor solamente a las cartas que ya han salido de la baraja
        if (mano.ncartas[i] >= 2 && mano.ncartas[i] <= 10){
            points += mano.ncartas[i];
        // Cuando el valor de la carta sea entre 2 y 10, los puntos que sume será igual al valor de su carta.
        }
        
        else if (mano.ncartas[i] == 11 || mano.ncartas[i] == 12){
            points += 10;
        // Cuando el valor de las cartas sea 11 o 12, los puntos de esas cartas deben ser 10.
        }
        else{
            as++;
            points = points + 11;
        // Cuando la carta sea un 1, esta debe valer 11 puntos.
        }
    }
    for(int i = 0; i<as ; i++){
        // Cuando salgan dos ases uno debe valer 1 y el otro 11 para no sumar 22.
        // As empieza en 0 y cada vez que salga uno habrá que ver su valor.
        // Este valor será el que más convenga al jugador/Crupier.
        if (points > 21) {
            points = points - 10;
        // Cuando el as vale 11 y hace que el jugador/Crupier se pase de 21, el As pasa a valer 1 punto.
        }
    }
    return points; // Devuelve los puntos obtenidos.
}

int juegaHumano(Cartas &mazo, Cartas &cartasJugador){ // Función en la que juega el jugador.
    
    cout << "----------------- \nTurno del jugador \n-----------------" << endl;
    
    int points; // Para guardar los puntos obtenidos por el jugador en la función "calcularpuntos".
    string seguir; // Para seguir pidiendo cartas o parar.
    
    int numCartasJugador = 0; // El jugador comienza la partida con 0 cartas.
    cout << "Tus cartas: ";
    muestraMazo(cartasJugador);
    //Guarda los puntos del jugador después de haberlos calculado en la función
    //que calcula los puntos de las cartas "calcularPuntos".
    points = calculaPuntos(cartasJugador); // Guarda los puntos del jugador.
    cout << "\t\t\tPuntos: " << points << endl;
    // Aquí muestra los puntos del jugador.
    
    do{
        if (points < 21){
            cout << "Tienes " << points << " Puntos, Quieres plantarte? " << endl;
            cout << "Escriba 'no' para seguir y 'si' para plantarte:" << endl;
            cin >> seguir;
            if (seguir == "no"){
                cout << "Tus cartas: ";
                annadeCarta(cartasJugador, sacarCartaMazo(mazo));
                // Cada vez que el jugador quiera añadir una carta llamamos a la funcion annadeCarta
                // para que saque una carta del mazo y se la añada al jugador.
                muestraMazo(cartasJugador); // Enseña todas las cartas del jugador.
                points = calculaPuntos(cartasJugador); // Explicado en las línea 218, 219 y 220.
                cout << "\t\t\tPuntos: " << points << endl; // Aquí muestra los puntos del jugador.
                numCartasJugador++;
                // Se añade una carta a la variable donde se guarda el número de cartas del jugador.
            }
        }
    }while (seguir != "si" && points <= 20);
    // Se ejecutará siempre que el jugador diga que no quiere más cartas o estas sumen 21 o más.
    return (calculaPuntos(cartasJugador));
    // Devuelve los puntos del jugador que se han calculado en la función calcular puntos.
}
    
int juegaCrupier(Cartas & mazo, Cartas & cartasCrupier){ // Función en la que juega el crupier.
    
    cout << "----------------- \nTurno del Crupier \n-----------------" << endl;
    int points; // Para guardar los puntos obtenidos por el Crupier en la función "calcularpuntos"
    
    do{
        int numCartasCrupier = 0; // El crupier comienza la partida con 0 cartas.
        cout << "Cartas Crupier: ";
        muestraMazo(cartasCrupier);// Guarda las cartas del crupier y las enseña.
        points = calculaPuntos(cartasCrupier);
        //Guarda los puntos del crupier despues de haberlos calculado en la función
        //que calcula los puntos de las cartas "calcularPuntos".
        cout << "El crupier ha sumado " << points << " Puntos" << endl;
        // Aquí muestra los puntos obtenidos por el crupier.
   
        if (points <= 16){
            // Si después de sacar las dos primeras cartas del crupier estas no suman más de 16.
            // Se añadiran el número de cartas necesario para que el crupier sume más de 16 puntos.
            // Aunque se puede pasar de 21 puntos y perder.
            cout << "El crupier saca otra carta" << endl;
            annadeCarta(cartasCrupier, sacarCartaMazo(mazo));
            // Cada vez que el Crupier tenga que añadir una carta llamamos a la funcion annadeCarta
            // para que saque una carta del mazo y se la añada al crupier.
            cout << "Cartas Crupier: ";
            muestraMazo(cartasCrupier); // Enseña todas las cartas del crupier.
            numCartasCrupier++;
            // Se añade una carta a la variable donde se guarda el número de cartas del crupier.
        }
        else if (points >= 17){
            cout << "El crupier ha sumado " << points << " Puntos" <<endl;;
            // Cuando el crupier suma más de 17 puntos se muestran sus puntos y ya no pide más cartas.
        }
    }while (points <= 16);
    // Se ejecutará siempre que los puntos del crupier sean inferiores a 16.
    return (calculaPuntos(cartasCrupier));
    // Devuelve los puntos del crupier que se han calculado en la función calcular puntos.
}

int ganador(int puntosJugador, int puntosCrupier, int numCartasJugador, int numCartasCrupier){
    // Elige según varias variables el ganador de la partida.
   
    int win = 0;
    // iniciamos la variable que determina si ganas o pierdas en empate.
    cout << "----------------------------- \n      Puntuación final \n-----------------------------" << endl;
    cout << "Crupier: " << puntosCrupier << "\tJugador: " <<puntosJugador << endl;
    
    if (puntosJugador > puntosCrupier){
        // Cuando los puntos del jugador son mayores que los del crupier gana el jugador.
        win = 1;
    }
    else if (puntosCrupier > puntosJugador){
        // Cuando los puntos del crupier son mayores que los del jugador gana el crupier.
        win = -1;
    }
    else if ( puntosCrupier == puntosJugador){
        // Cuando los puntos del crupier y los del jugador son iguales se desempatará,
        // teniendo en cuenta quien ha obtenido más cartas.
        cout << "Existe un empate, vamos a analizar el numero de cartas de cada jugador..." << endl;
    
        if (numCartasJugador > numCartasCrupier){
            // Si el nº de cartas del jugador es mayor que las del crupier para obtener los mismos puntos pierdes.
            win = -1;
        }
        else if (numCartasCrupier > numCartasJugador){
            // Si el nº de cartas del crupier es mayor que las del jugador para obtener los mismos puntos ganas.
            win = 1;
        }
        else{
            // Si se obtienen el mismo nº de cartas para llegar a la misma cantidad de puntos hay un empate total.
            win = 0;
        }
    } return win; // Devuelve quien ha ganado.
}

Jugador iniciarSesion(DatosPartida &d, string nick){

    int i;
    i = buscaJugador (d, nick);
    // i nos indica la posición del jugador
    Jugador j;
    // La estructura de jugador se guarda en j
    
    if (i == -1){ // Si el jugador no se ha registrado todavía, se le crea un nuevo perfil
        if(d.contadorjugadores == 100)
        { // Pero si el espacio ya se ha llenado no nos permitirá crear ningún jugador nuevo
            cout << "Lo siento pero el espacio de jugadores se ha llenado" << endl;
            j.saldodisponible = -1;
            // Como el saldo de este jugador es de -1 nunca podrá jugar
            // Simplemente podrá ver la información de los jugadores
        }
        else if (d.contadorjugadores < 100){
            // Cuando el nº de jugadores registrados sea menor que 100
            // Se podrán guardan nuevos jugadores
            cout << "El jugador no esta en nuestra base de datos" << endl;
            cout << "Creando un nuevo usuario..." << endl;
            // Crea al usuario con el nick con el que se inicío sesión
            j.nickjugador = nick;
            j.numerodevictorias = 0; // Inicializamos sus victorias a 0
            j.numvictoriasconblackjack = 0; // Inicializamos sus victorias con BlackJack a 0
            j.numerodederrotas= 0; // Inicializamos sus derrotas a 0
            j.saldodisponible = 100; // Inicializamos su saldo con 100
            guardaJugador(d, j); // Guarda el jugador en el archivo
            cout << "BIENVENIDO " << j.nickjugador << "." << endl;
            //Da la Bienvenida al nuevo jugador
        }
    }
    else{ // Si el jugador con el que se ha iniciado la sesión ya existe
        j = d.lista[i]; // Carga los datos del archivo y los guarda en la estructura de datos
        cout << "BIENVENIDO " << j.nickjugador << endl;
        //Da la Bienvenida al jugador.
    }
    return j; // Nos devuelve los datos del jugador, almacenados en la variable j
    // Estos datos pueden ser los del archivo porque el jugador ya ha sido creado
    // O los de un jugador nuevo.
}

int buscaJugador(DatosPartida &d, string nick){
    int posicion_jugador = -1;
    // Iniciamos esta variabable en -1, esto indica que el jugador no ha sido registrado
    for (int i = 0; i < d.contadorjugadores; i++){
        // Sin embargo, si este bucle encuentra al jugador
        // La función nos devolvera la posción en el archivo del jugador con el que hemos iniciado la sesión
        if(d.lista[i].nickjugador == nick){
            posicion_jugador = i;
            // La Variable que indica la posicion del jugador pasa a ser i y queda guardado su posicón
            i = d.contadorjugadores;
            // Hacemos que i sea igual al nº total de jugadores registrados para salir del bucle
        }
    }
    return posicion_jugador;
    // Valor de la función buscaJugador que nos devuelve la posición
    // Del jugador o si existe el jugador o no
}

void cargaDatos(DatosPartida &d){
    ifstream archivo; // Declaramos variable de tipo archivo para poder abrirlo
    
    archivo.open("jugadores.txt"); // Abrimos el archivo
    
    if(archivo.is_open()){
        // Si el archivo se abre
        archivo >> d.contadorjugadores;
        // La primera línea del archivo nos muestra los jugadores registrados
        for(int i = 0; i < d.contadorjugadores; i++){
            // Carga los datos de todos los jugadores registrados en el archivo
            archivo >> d.lista[i].nickjugador;
            archivo >> d.lista[i].numerodevictorias;
            archivo >> d.lista[i].numvictoriasconblackjack;
            archivo >> d.lista[i].numerodederrotas;
            archivo >> d.lista[i].saldodisponible;
        }
    }
    else{ // Si el archivo no pudo abrirse nos avisa.
        cout << "El Archivo 'jugadores.txt' No Se Ha Podido Abrir. " << endl;
    }
    archivo.close(); // Cerramos el archivo
}

void gestionSaldo(DatosPartida &d, Jugador &j){
    
    int opcion;
    do{
    // Menu del gestiona saldo
    cout << "\n----------------------------" << endl;
    cout << "      GESTIÓN DE SALDO" << endl;
    cout << "----------------------------" << endl;
    cout << "1. Consulta Saldo Disponible \n2. Recarga \n0. Salir" << endl;
    cout << "Elige Una Opción: " ;
    cin >> opcion;
    
        if (opcion == 1){ // Nos muestra el saldo del jugador con el que iniciamos sesión
            cout << "Tienes " << j.saldodisponible << " € De Saldo Disponible" << endl;
        }
        else if (opcion == 2){ // Recargamos nuestro saldo y nos suma 100€
            if (j.saldodisponible >= 0){
                cout << "RECARGANDO SALDO..." << endl;
                j.saldodisponible += 100; // Al saldo que teniamos nos suma 100€.
                //Aunque tengamos 1000€ lo hará siempre que se lo pidamos
                cout << "Vuelves a tener " << j.saldodisponible ;
                cout << " € De Saldo Disponible. \nRECUERDA JUGAR CON RESPONSABILIDAD" << endl;
                guardaDatos(d);
                actualizaJugador(d, j);
            }
            else if (j.saldodisponible == -1){
                
                cout << "\nEste jugador no se ha podido registrar en el archivo porque ya está lleno" << endl;
                cout << "Por tanto no puede recargar su saldo" << endl;
                cout << "Vuelva a iniciar el programa con un NICK que si se encuentre en el archivo" << endl;
            }
        }
        else if (opcion == 0){ // Nos devuelve al menu
            cout << "Regresando al menu principal..." << endl;
        }
    }while (opcion != 0);
}

void muestraInfo(DatosPartida d, string nick){
    
    int posicionjugador;
    posicionjugador = buscaJugador(d, nick);
    // La posución del jugador es la misma que la del jugador con la que se inicia sesión.
    int opcion;
    do{
        cout << "\n-----------------------------------------------" << endl;
        cout << "¿De Qué Jugador Quieres Conocer La Información?" << endl;
        cout << "-----------------------------------------------" << endl;
        cout << "1. Mis Datos" << endl; // Muestra los datos del jugador con el que iniciamos sesión
        cout << "2. Otro Jugador" << endl;
        // (No se pedía en esta práctica pero me sirvió para preparar el examen final,
        // Y así es un programa más completo).
        cout << "0. Salir" << endl; // Nos devuelve al menu
        cout << "Que opción elige: " ;
        cin >> opcion;
        
    if (opcion == 1){
        if(posicionjugador == -1)
        {
            // Si al buscar el jugador nos devuelve -1, significa que el jugador no se ha registrado
            cout << "El jugador no se encuentra en la lista de jugadores" << endl;
        }
        else{
            cout << "\n-----------------------------------------------" << endl;
            cout << "\t\t\tINFORMACIÓN DE " << d.lista[posicionjugador].nickjugador << endl;
            cout << "-----------------------------------------------" << endl;
            // Muestra los datos del jugador con el que iniciamos sesión
            cout << "\nNúmero De Partidas Ganadas " << d.lista[posicionjugador].numerodevictorias << endl;
            cout << "Número De Victorias Con BlackJack: " << d.lista[posicionjugador].numvictoriasconblackjack << endl;
            cout << "Número De Derrotas " << d.lista[posicionjugador].numerodederrotas << endl;
            cout << "Saldo Disponible: " << d.lista[posicionjugador].saldodisponible << " €" << endl;
            cout << "Ocupas La Línea " << posicionjugador + 2 << " En el archivo 'jugadores.txt'" << endl;
        }
    }
    else if (opcion == 2){
        ifstream archivo; // Declaramos variable de tipo archivo para poder abrirlo
        string encontrarjugador; // Variable declarada para encontrar un jugador en concreto
        
        archivo.open("jugadores.txt"); // Abrimos el archivo
        if(archivo.is_open()) // Si el archivo esta abierto se ejecuta
        {
            cout << "¿De Quién Quieres Conocer Los Datos?: ";
            cin>>encontrarjugador;
            
            bool encontrado = false;
            // Creamos una variable booleana que la inicializaremos en false
            // Esto significa que no ha sido encontrado el jugador que buscabamos
            
            for (int i = 0; i<d.contadorjugadores; i++){ // Bucle que se repitirá tantas veces como jugadores se hayan registrado
                if(d.lista[i].nickjugador == encontrarjugador){
                    // Si el nombre introducido corresponde con un jugador del archivos nos muestra sus datos
                    encontrado = true;
                    // Si después de recorrer el bucle el nick que puso el jugaodor corresponde con el de algún jugador del archivo
                    // La Variable booleana pasa a true y nos mostrará los datos del jugador que buscabamos
                    if (encontrado == true){
                        cout << "\n----------------------------------" << endl;
                        cout << "\tINFORMACIÓN DE " << encontrarjugador << endl;
                        cout << "----------------------------------" <<endl;
                        cout << "\nNúmero De Partidas Ganadas: " << d.lista[i].numerodevictorias << endl;
                        cout << "Número De Victorias Con BlackJack: " << d.lista[i].numvictoriasconblackjack << endl;
                        cout << "Número De Derrotas " << d.lista[i].numerodederrotas << endl;
                        cout << "Saldo Disponible: " << d.lista[i].saldodisponible << " €" << endl;
                        cout << "Ocupa La Línea " << i+2 << " En el archivo 'jugadores.txt'" << endl;
                        cout<<endl;
                    }
                }
            }
                if (encontrado == false){
                    // Si el bucle no encuentra al jugador la variable booleana permanece en 0 y muestra un mensaje por pantalla
                    cout << "\nLo Siento Pero el Jugador '"<< encontrarjugador << "' NO Se Ha Registrado Todavía." << endl;
                    cout << "Vuelva al Menu Principal y Pulse la tecla 6" << endl;
                    cout << "Para iniciar sesión con otro jugador." << endl;
                }
        }
        else{ // Si el archivo no pudo abrirse nos avisa.
            cout << "El Archivo 'jugadores.txt' No Se Ha Podido Abrir. " << endl;
        }
        archivo.close(); // Cerramos el archivo
    }
    else if (opcion == 0){ // Volvemos al menu
        cout << "Regresando al menu principal..." << endl;
    }
    } while (opcion != 0);
}

void infoJugadores(DatosPartida d){
    
    cout << "\n----------------------------------" << endl;
    cout << "INFORMACIÓN DE TODOS LOS JUGADORES" << endl;
    cout << "----------------------------------" << endl;
    
    ifstream archivo;
    archivo.open("jugadores.txt"); // Abrimos el archivo de texto para ver los datos de todos los jugadores
    
    cout << "Se han registrado una cantidad total de: " << d.contadorjugadores << " Jugadores" << endl;
    cout << "Todavía se pueden registrar: " << 100 - d.contadorjugadores  << " Jugadores" << endl;
    cout << endl; // No dice cuantos jugadores podemos registrar y Cuantos nos huecos quedan disponibles
    
    if(archivo.is_open())
    { // Si el archivo se abre
        for (int i=0; i < d.contadorjugadores; i++){
            // Repetimos el bucle el mismo nº de veces que nº de jugadores registrados
            // Para ver los datos de todos los jugadores
            cout << i+1 <<".  Los Datos Almacenados Del Jugador '" << d.lista[i].nickjugador << "' Son Los Siguientes: " <<endl;
            cout << "\tNúmero De Partidas Ganadas: " << d.lista[i].numerodevictorias << endl;
            cout << "\tNúmero De Victorias Con BlackJack: " << d.lista[i].numvictoriasconblackjack << endl;
            cout << "\tNúmero De Partidas Perdidas: " << d.lista[i].numerodederrotas << endl;
            cout << "\tSaldo Disponible: " << d.lista[i].saldodisponible << " €" << endl;
            cout << endl;
            // Muestra el nombre del jugador y sus datos
        }
    }
    else{ // Si el archivo no pudo abrirse nos avisa.
        cout << "El Archivo 'jugadores.txt' No Se Ha Podido Abrir. " << endl;
    }
    archivo.close(); // Se cierra el archivo.
}

void actualizaJugador(DatosPartida &d, Jugador &j){
    string nick;
    // Buscamos al jugador en la base de datos
    int k;
    k = buscaJugador (d, j.nickjugador);
     // K nos devuelve la posicion del jugador registrado con el que hemos iniciado la sesión.
     // Siempre que esa posición no sea -1, ya que en ese caso el jugador está registrado en la lista.
    if (k != -1){
        d.lista[k] = j; // Se actualizan en la lista los datos del jugador.
    }
}

void guardaJugador(DatosPartida &d, Jugador &j){
    
    if (d.contadorjugadores < 100){
        // En este caso todavía no se ha registrado el nº total de jugadores.
        d.contadorjugadores++; // Añade un jugador al contador
        int a;
        a = d.contadorjugadores -1; // Al registrarse un jugador el espacio se reduce 1
        d.lista[a] = j; // Se guarda en la lista el nuevo jugador
    }
    else if(d.contadorjugadores == 100)
        // El nº maxásimo de jugadores que se pueden registrar son 100.
        // Cuando la lista se completa nos indica que el espacio está lleno
    {
        cout << "Lo siento pero el espacio de jugadores se ha llenado" << endl;}
}

void guardaDatos(DatosPartida &d){
    
    ofstream archivo; // Declara una variable de tipo archivo
    
    archivo.open("jugadores.txt"); // Abre y crea un archivo de texto
    if (archivo.is_open()){ // Si el archivo esta abierto
        //En la primera linea mostrara el nº de jugadores registrados
        archivo << d.contadorjugadores << endl;
        
        for (int i = 0; i < d.contadorjugadores; i++){
            // Bucle que genera el midmo nº de lineas que el nº de jugadores registrados.
            // Cada jugador tiene su propia línea
            archivo << d.lista[i].nickjugador << "   "; // Muestra el nick
            archivo << d.lista[i].numerodevictorias << "   "; // Muestra el nº de Victorias
            archivo << d.lista[i].numvictoriasconblackjack << "   "; // Muestra el nº de Victorias con BlackJack
            archivo << d.lista[i].numerodederrotas << "   "; // Muestra el nº de derrotas
            archivo << d.lista[i].saldodisponible << "   "; // Muestra el saldo del jugador
            archivo << endl;
            // Pasa a la siguiente línea del archivo
        }
    }
    else{ // Si el archivo no pudo abrirse nos avisa.
        cout << "El Archivo 'jugadores.txt' No Se Ha Podido Abrir. " << endl;
    }
    archivo.close(); // Se cierra el archivo.
}

int main()
{
    int opcion;
    string nick; // variable que juarda los jugadores jugadores.
    Jugador j; // Dentro de Jugador se guardan los datos de cada jugador.
    DatosPartida d; // // Dentro de DatosPartida se guardan los datos de cada partida jugada.
        
    cargaDatos(d); // Recupera los datos de las partidas que ya se han jugado y se guardan en el archivo.
    
    cout << "INTRODUCE TU NICK: ";
    cin >> nick;
    j = iniciarSesion(d, nick);
    // Cuando nos pregunta por el nick nos lleva a la función de Iniciar sesion.
    // Si ese jugador ya existe carga sus datos y si juega partidas se actualizan
    // En cambio, si no se ha creado genera uno nuevo y si juega partidas se actualizan sus datos.
    
    // Bucle do/while para que se repita siempre que se acabe la partida,
    // se muestren las reglas o se seleccione 0 para finalizar el programa.
    do {
        menu();
        cin >> opcion;
        
        if (opcion == 1){
            if (j.saldodisponible > 0){
                srand((unsigned int)time(0)); //Randomiza las cartas
                juegoBlackjack(d,j);
                actualizaJugador(d, j);} // Después de acabar la partida actualiza los datos del jugador
    
            else if (j.saldodisponible == 0){ // Si tu saldo es 0 te regresa al menu
                cout << "Su saldo disponible es de " << j.saldodisponible << " €" << endl;
                cout << "Debe recargar el saldo, pulsando la opcion 4." << endl;
                cout << "Volviendo al menu..." << endl;
            }
        }
        else if (opcion == 2){ // Muestra la info de todos los jugadores
            infoJugadores(d);
        }
        else if (opcion == 3){
            // Te permite ver la info del jugador con quien iniciaste sesion
            // U otro que se encuentre en el archivo
            muestraInfo(d,nick);
        }
        else if (opcion == 4){ // Podemos ver nuestro saldo y recargarlo
            gestionSaldo(d,j);
        }
        else if (opcion == 5){ // Muestra las reglas de como jugar al BlackJack
            muestraReglas();
        }
        else if (opcion == 6){ // Nos permite iniciar Sesion sin salirnos del programa con un nuevo jugador
            cout << "INTRODUCE TU NICK: ";
            cin >> nick;
            j = iniciarSesion(d, nick);
        }
        else if (opcion == 0){ // Pulsar 0 para que el programa se cierre y se guarden los datos
            guardaDatos(d);         // Si creamos un jugador nuevo lo guarda
            actualizaJugador(d, j); // Después de acabar la partida actualiza los datos del jugador
            cout << "Ha sido un placer, hasta la próxima." << endl;
        }
        else{
            cout << "Esa no es una opcion valida, vuelva a seleccionar una que sea valida.";
        }
    } while (opcion != 0); // Se ejecutara esta opción siempre que la opcion no sea 0
    
    return 0;
}
