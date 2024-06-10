#include <iostream>
#include <chrono>
#include <cstring>

#include "moveTree.h"
#include "input_to_move_vector.h"
#include "move_vector_to_output.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define BUFSPACE 1024
int errno;

// https://stackoverflow.com/questions/19555121/how-to-get-current-timestamp-in-milliseconds-since-1970-just-the-way-java-gets

// Wycinki kodu odnoszące się do gry sieciowej zaczerpnięte z:
// https://kcir.pwr.edu.pl/~witold/pamsi/checkers_client.c

int main(int argc, char* argv[]) {

    checkersBoard board;
    moveTree* tree = nullptr;

    std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    auto shuffle_seed = ms.count();

    bool GUI = false;
    team turn;
    int depth = 0;

    std::string ip_port = "localhost";
    std::string ip_address = "12345";


    if(argc >= 4)
    {
        if(std::strcmp(argv[1], "GUI") == 0)
            GUI = true;
        else if(std::strcmp(argv[1], "NET") == 0)
            GUI = false;
        else
            throw std::invalid_argument("Invalid interface");

        if(std::strcmp(argv[2], "BLACK") == 0)
        {
            turn = BLACK;
            board.set_player(BLACK);
            board.set_enemy(WHITE);
        }
        else if(std::strcmp(argv[2], "WHITE") == 0)
        {
            turn = WHITE;
            board.set_player(WHITE);
            board.set_enemy(BLACK);
        }
        else
            throw std::invalid_argument("Invalid turn");

        depth = std::stoi(argv[3]);
    }
    if(argc >= 5)
    {
        shuffle_seed = std::stoi(argv[4]);
    }
    if(argc >= 7)
    {
        ip_address = argv[5];
        ip_port = argv[6];
    }

    srand(shuffle_seed);


    board.board_display(); std::cout << std::endl;
    while(true)
    {
        if(GUI)
        {
            if(turn == BLACK)
            {
                if(!(board.get_turn() % 2))
                {
                    std::cout << "Ruch czarnego: "; std::cout << std::endl;
                    delete tree;
                    tree = new moveTree(board);
                    auto move = tree->get_minimax_move(depth, true);
                    board.play_turn(move, board.get_player());
                    board.board_display(); std::cout << std::endl;
                }
                else
                {
                    std::cout << "Ruch bialego: ";
                    std::string input;
                    std::cin >> input; std::cout << std::endl;
                    auto move = input_to_move_vector(input);
                    board.play_turn(move, board.get_enemy());
                    board.board_display(); std::cout << std::endl;
                }
            }
            else
            {
                if(!(board.get_turn() % 2))
                {
                    std::cout << "Ruch czarnego: ";
                    std::string input;
                    std::cin >> input; std::cout << std::endl;
                    auto move = input_to_move_vector(input);
                    board.play_turn(move, board.get_enemy());
                    board.board_display(); std::cout << std::endl;
                }
                else
                {
                    std::cout << "Ruch bialego: "; std::cout << std::endl;
                    delete tree;
                    tree = new moveTree(board);
                    auto move = tree->get_minimax_move(depth, true);
                    board.play_turn(move, board.get_player());
                    board.board_display(); std::cout << std::endl;
                }
            }
        }
        else
        {
            char buf[BUFSPACE];
            int serv_sock, n, nr_ruchu;
            struct sockaddr_in serv_addr;
            struct hostent *serv_hostent;

            serv_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (serv_sock < 0)
            {
                perror("socket");
                exit(errno);
            }

            serv_hostent = gethostbyname(argv[5]);
            if (serv_hostent == 0)
            {
                fprintf(stderr, "%s: nieznany adres IP %s\n", argv[0], argv[5]);
                exit(-1);
            }

            serv_addr.sin_family = AF_INET;
            memcpy(&serv_addr.sin_addr, serv_hostent->h_addr, serv_hostent->h_length);
            serv_addr.sin_port = htons(atoi(argv[6]));

            printf("Laczymy sie z serwerem ...\n");
            if (connect(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
                perror("connect");
                exit(-1);
            }

            printf("Polaczenie nawiazane, zaczynamy gre ...\n");

            while(true)
            {
                if(turn == BLACK)
                {
                    if(!(board.get_turn() % 2))
                    {
                        delete tree;
                        tree = new moveTree(board);
                        auto move = tree->get_minimax_move(depth, true);
                        board.play_turn(move, board.get_player());
                        for(int moveIter = 0; moveIter<move.size(); moveIter++)
                        {
                            move[moveIter] = move[moveIter] + 1;
                        }
                        std::string moveString = move_vector_to_output(move);
                        if(write(serv_sock, moveString.c_str(), strlen(moveString.c_str())) < 0)
                        {
                            perror("write");
                            exit(errno);
                        }
                    }
                    else
                    {
                        std::string moveInput;
                        n=read(serv_sock, buf, sizeof buf);
                        if (n<0) {
                            perror("read");
                            exit(errno);
                        }
                        if (n==0) { // pusty komunikat = zamkniete polaczenie
                            exit(0);
                        }
                        buf[n] = 0;
                        moveInput = buf;
                        auto move = input_to_move_vector(moveInput);
                        for(int moveIter = 0; moveIter<move.size(); moveIter++)
                        {
                            move[moveIter] = move[moveIter] - 1;
                        }
                        board.play_turn(move, board.get_enemy());
                    }
                }
                else
                {
                    if(!(board.get_turn() % 2))
                    {
                        std::string moveInput;
                        n=read(serv_sock, buf, sizeof buf);
                        if (n<0) {
                            perror("read");
                            exit(errno);
                        }
                        if (n==0) {  //pusty komunikat = zamkniete polaczenie
                            exit(0);
                        }
                        buf[n] = 0;
                        moveInput = buf;
                        auto move = input_to_move_vector(moveInput);
                        for(int moveIter = 0; moveIter<move.size(); moveIter++)
                        {
                            move[moveIter] = move[moveIter] - 1;
                        }
                        board.play_turn(move, board.get_enemy());

                    }
                    else
                    {
                        delete tree;
                        tree = new moveTree(board);
                        auto move = tree->get_minimax_move(depth, true);
                        board.play_turn(move, board.get_player());
                        for(int moveIter = 0; moveIter<move.size(); moveIter++)
                        {
                            move[moveIter] = move[moveIter] + 1;
                        }
                        std::string moveString = move_vector_to_output(move);
                        if(write(serv_sock, moveString.c_str(), strlen(moveString.c_str())) < 0)
                        {
                            perror("write");
                            exit(errno);
                        }

                    }
                }
            }
        }
    }


    return 0;
}
