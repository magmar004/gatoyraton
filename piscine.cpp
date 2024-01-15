#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class TicTacToe {
public:
    // inicialización del juego con un tablero y asignación aleatoria de roles para el ratón y el gato.
    TicTacToe() {
        tabla = std::vector<char>(9, '-');
        if (rand() % 2 == 1) {
            humanPlayer = "…ᘛ⁐̤ᕐᐷ";
            botPlayer = "/ᐠơ ﻌ ơᐟ/";
        } else {
            humanPlayer = "…ᘛ⁐̤ᕐᐷ";
            botPlayer = "/ᐠơ ﻌ ơᐟ/";
        }
    }

    // mostrar el estado actual del tablero.
    void mostrar_tabla() {
        std::cout << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "  " << tabla[0 + (i * 3)] << " | " << tabla[1 + (i * 3)] << " | " << tabla[2 + (i * 3)] << std::endl;
            std::cout << std::endl;
        }
    }

    // verificar si el tablero está lleno.
    bool tabla_llena(const std::vector<char>& posicion) {
        return std::find(posicion.begin(), posicion.end(), '-') == posicion.end();
    }

    // verificar si un jugador ganó.
    bool jugador_gana(const std::vector<char>& posicion, char jugador) {
        if (posicion[0] == posicion[1] && posicion[1] == posicion[2] && posicion[2] == jugador) return true;
        if (posicion[3] == posicion[4] && posicion[4] == posicion[5] && posicion[5] == jugador) return true;
        if (posicion[6] == posicion[7] && posicion[7] == posicion[8] && posicion[8] == jugador) return true;
        if (posicion[0] == posicion[3] && posicion[3] == posicion[6] && posicion[6] == jugador) return true;
        if (posicion[1] == posicion[4] && posicion[4] == posicion[7] && posicion[7] == jugador) return true;
        if (posicion[2] == posicion[5] && posicion[5] == posicion[8] && posicion[8] == jugador) return true;
        if (posicion[0] == posicion[4] && posicion[4] == posicion[8] && posicion[8] == jugador) return true;
        if (posicion[2] == posicion[4] && posicion[4] == posicion[6] && posicion[6] == jugador) return true;

        return false;
    }

    // verificar el ganador o si hay un empate y mostrar mensajes.
    void verificar_ganador() {
        if (jugador_gana(tabla, humanPlayer)) {
            system("cls");
            std::cout << "   El " << humanPlayer << " logró escapar!" << std::endl;
        } else if (jugador_gana(tabla, botPlayer)) {
            system("cls");
            std::cout << "   El " << botPlayer << " atrapó al ratón :(" << std::endl;
        } else if (tabla_llena(tabla)) {
            system("cls");
            std::cout << "  El " << botPlayer << " atrapó al ratón :( !" << std::endl;
        }
    }

    // inicia el juego con los jugadores humano y de computadora tomando turnos hasta que haya un ganador o empate.
    void start() {
        ComputerPlayer bot(botPlayer);
        HumanPlayer human(humanPlayer);
        while (true) {
            system("cls");
            std::cout << "   Turno del " << humanPlayer << std::endl;
            mostrar_tabla();

            // turno del humano
            int puntaje = human.human_move(tabla);
            tabla[puntaje] = humanPlayer;
            verificar_ganador();

            // turno del robot
            puntaje = bot.machine_move(tabla);
            tabla[puntaje] = botPlayer;
            verificar_ganador();
        }

        // mostrar la tabla.
        std::cout << std::endl;
        mostrar_tabla();
    }

private:
    std::vector<char> tabla;
    std::string humanPlayer;
    std::string botPlayer;

    // clase para manejar las acciones del jugador humano.
    class HumanPlayer {
    public:
        HumanPlayer(const std::string& letter) : letter(letter) {}

        // solicitar entrada al usuario y validar si la casilla está disponible.
        int human_move(const std::vector<char>& state) {
            int puntaje;
            while (true) {
                std::cout << "Ingrese el número de la casilla (1-9): ";
                std::cin >> puntaje;
                std::cout << std::endl;
                if (state[puntaje - 1] == '-') {
                    break;
                }
            }
            return puntaje - 1;
        }

    private:
        std::string letter;
    };

    // clase para manejar las acciones del jugador de computadora.
    class ComputerPlayer {
    public:
        ComputerPlayer(const std::string& letter) : botPlayer(letter) {
            humanPlayer = (letter == "/ᐠơ ﻌ ơᐟ/") ? "…ᘛ⁐̤ᕐᐷ" : "/ᐠơ ﻌ ơᐟ/";
        }

        // determinar qué jugador (ratón o gato) tiene más lugares en el tablero.
        std::string players(const std::vector<char>& posicion) {
            int raton = 0;
            int gato = 0;
            for (char letter : posicion) {
                if (letter == '…ᘛ⁐̤ᕐᐷ') {
                    raton++;
                }
                if (letter == "/ᐠơ ﻌ ơᐟ/") {
                    gato++;
                }
            }

            if (humanPlayer == "…ᘛ⁐̤ᕐᐷ") {
                return (raton == gato) ? "…ᘛ⁐̤ᕐᐷ" : "/ᐠơ ﻌ ơᐟ/";
            } else if (humanPlayer == "/ᐠơ ﻌ ơᐟ/") {
                return (raton == gato) ? "/ᐠơ ﻌ ơᐟ/" : "…ᘛ⁐̤ᕐᐷ";
            }
        }

        // obtener las posiciones disponibles en el tablero.
        std::vector<int> actions(const std::vector<char>& posicion) {
            std::vector<int> posibles_jugadas;
            for (int i = 0; i < posicion.size(); ++i) {
                if (posicion[i] == '-') {
                    posibles_jugadas.push_back(i);
                }
            }
            return posibles_jugadas;
        }

        // generar un nuevo estado del tablero después de realizar una acción.
        std::vector<char> result(const std::vector<char>& posicion, int action) {
            std::vector<char> nueva_posicion = posicion;
            std::string player = players(posicion);
            nueva_posicion[action] = player[0];
            return nueva_posicion;
        }

        // verificar si se alcanzó un estado final del juego.
        bool terminal(const std::vector<char>& posicion) {
            return jugador_gana(posicion, "…ᘛ⁐̤ᕐᐷ") || jugador_gana(posicion, "/ᐠơ ﻌ ơᐟ/");
        }

        // realizar el algoritmo minimax para tomar decisiones estratégicas para el gato.
        int minimax(const std::vector<char>& posicion, std::string player) {
            std::string max_player = humanPlayer;
            std::string min_player = (player == "…ᘛ⁐̤ᕐᐷ") ? "/ᐠơ ﻌ ơᐟ/" : "…ᘛ⁐̤ᕐᐷ";

            if (terminal(posicion)) {
                return (min_player == max_player) ? 1 * (actions(posicion).size() + 1) : -1 * (actions(posicion).size() + 1);
            } else if (tabla_llena(posicion)) {
                return 0;
            }

            if (player == max_player) {
                int mejor_puntaje = -std::numeric_limits<int>::infinity();
                for (int posibles_jugadas : actions(posicion)) {
                    std::vector<char> nueva_posicion = result(posicion, posibles_jugadas);
                    int sim_score = minimax(nueva_posicion, min_player);

                    if (sim_score > mejor_puntaje) {
                        mejor_puntaje = sim_score;
                    }
                }
                return mejor_puntaje;
            } else {
                int mejor_puntaje = std::numeric_limits<int>::infinity();
                for (int posibles_jugadas : actions(posicion)) {
                    std::vector<char> nueva_posicion = result(posicion, posibles_jugadas);
                    int sim_score = minimax(nueva_posicion, min_player);

                    if (sim_score < mejor_puntaje) {
                        mejor_puntaje = sim_score;
                    }
                }
                return mejor_puntaje;
            }
        }

        // método para que la computadora realice su movimiento utilizando el algoritmo minimax.
        int machine_move(const std::vector<char>& posicion) {
            int mejor_puntaje = -std::numeric_limits<int>::infinity();
            int mejor_movimiento = -1;

            for (int posibles_jugadas : actions(posicion)) {
                std::vector<char> nueva_posicion = result(posicion, posibles_jugadas);
                int sim_score = minimax(nueva_posicion, botPlayer);

                if (sim_score > mejor_puntaje) {
                    mejor_puntaje = sim_score;
                    mejor_movimiento = posibles_jugadas;
                }
            }

            return mejor_movimiento;
        }

    private:
        std::string botPlayer;
        std::string humanPlayer;
    };
};

// función principal que inicia el juego.
int main() {
    TicTacToe tic_tac_toe;
    tic_tac_toe.start();

    return 0;
}
