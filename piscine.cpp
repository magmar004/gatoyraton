#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class TicTacToe {
public:
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

    void mostrar_tabla() {
        std::cout << std::endl;
        for (int i = 0; i < 3; ++i) {
            std::cout << "  " << tabla[0 + (i * 3)] << " | " << tabla[1 + (i * 3)] << " | " << tabla[2 + (i * 3)] << std::endl;
            std::cout << std::endl;
        }
    }

    bool tabla_llena(const std::vector<char>& posicion) {
        return std::find(posicion.begin(), posicion.end(), '-') == posicion.end();
    }

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

    void verificar_ganador() {
        if (jugador_gana(tabla, humanPlayer)) {
            system("cls");
            std::cout << "   El " << humanPlayer << " logro escapar!" << std::endl;
        } else if (jugador_gana(tabla, botPlayer)) {
            system("cls");
            std::cout << "   El " << botPlayer << " atrapo al raton :(" << std::endl;
        } else if (tabla_llena(tabla)) {
            system("cls");
            std::cout << "  El " << botPlayer << " atrapo al raton :( !" << std::endl;
        }
    }

    void start() {
        ComputerPlayer bot(botPlayer);
        HumanPlayer human(humanPlayer);
        while (true) {
            system("cls");
            std::cout << "   Turno del " << humanPlayer << std::endl;
            mostrar_tabla();

            // Humano
            int puntaje = human.human_move(tabla);
            tabla[puntaje] = humanPlayer;
            verificar_ganador();

            // Robot
            puntaje = bot.machine_move(tabla);
            tabla[puntaje] = botPlayer;
            verificar_ganador();
        }

        // Mostrar la tabla
        std::cout << std::endl;
        mostrar_tabla();
    }

private:
    std::vector<char> tabla;
    std::string humanPlayer;
    std::string botPlayer;

    class HumanPlayer {
    public:
        HumanPlayer(const std::string& letter) : letter(letter) {}

        int human_move(const std::vector<char>& state) {
            // Taking user input
            int puntaje;
            while (true) {
                std::cout << "Ingrese el numero de la casilla (1-9): ";
                std::cin >> puntaje;
                std::cout << std::endl;
                if (posicion[puntaje - 1] == '-') {
                    break;
                }
            }
            return puntaje - 1;
        }

    private:
        std::string letter;
    };

    class ComputerPlayer {
    public:
        ComputerPlayer(const std::string& letter) : botPlayer(letter) {
            humanPlayer = (letter == "/ᐠơ ﻌ ơᐟ/") ? "…ᘛ⁐̤ᕐᐷ" : "/ᐠơ ﻌ ơᐟ/";
        }

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

        std::vector<int> actions(const std::vector<char>& posicion) {
            std::vector<int> posibles_jugadas;
            for (int i = 0; i < posicion.size(); ++i) {
                if (posicion[i] == '-') {
                    posibles_jugadas.push_back(i);
                }
            }
            return posibles_jugadas;
        }

        std::vector<char> result(const std::vector<char>& posicion, int action) {
            std::vector<char> nueva_posicion = posicion;
            std::string player = players(posicion);
            nueva_posicion[action] = player[0];
            return nueva_posicion;
        }

        bool terminal(const std::vector<char>& posicion) {
            return jugador_gana(posicion, "…ᘛ⁐̤ᕐᐷ") || jugador_gana(posicion, "/ᐠơ ﻌ ơᐟ/");
        }

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

                    if (sim_score > best_score) {
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

int main() {
    TicTacToe tic_tac_toe;
    tic_tac_toe.start();

    return 0;
}
