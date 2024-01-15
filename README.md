El juego utiliza la programación orientada a objetos en C++, dividiendo las responsabilidades entre las clases TicTacToe, HumanPlayer, y ComputerPlayer. 
En el constructor de TicTacToe, se inicializa el tablero y se elige aleatoriamente si el jugador humano es el ratón o el gato. El juego sigue un bucle principal en el método start(), donde los jugadores humanos y de computadora toman turnos para hacer movimientos en el tablero.
La clase HumanPlayer maneja la entrada del usuario, asegurándose de que el movimiento sea válido. 
La clase ComputerPlayer utiliza el algoritmo minimax para tomar decisiones estratégicas y decidir el mejor movimiento para el gato.
La verificación de ganadores y empates se realiza en el método verificar_ganador(), donde se muestra un mensaje en la computadora.
