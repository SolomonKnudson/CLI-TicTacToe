#ifndef TICTACTOETEST_H
#define TICTACTOETEST_H
#include <iostream>
#include <vector>
#include "tictactoe.h"
#include "board.h"
#include "player.h"

using Table = std::vector<std::vector<int>>;

//Std Vectors(good!)
Table makeTable(const int rows, const int cols)
{
    Table table{};
    for(int i{0}; i < rows; i++)
    {
        table.push_back(std::vector<int>{});
    }
    int count{1};
    for(auto& row : table)
    {
        for(int i{0}; i < cols; i++)
        {
            row.push_back(count++);
        }
    }
    return table;
}

void displayTable(const Table& table, const char key = 0)
{
    for(auto& row : table)
    {
        for(auto& col : row)
        {
            if(col == static_cast<int>(key))
            {
                std::cout << " " << static_cast<char>(col) << " ";
                continue;
            }
            std::cout << " " << col << " ";
        }
        std::cout << '\n';
    }
}

void changeTable(Table& table, const int tablePos, const char value)
{
    for(auto& row : table)
    {
        for(auto& col : row)
        {
            if(col == tablePos)
            {
                col = static_cast<int>(value);
            }
        }
    }
}

//Raw arrays(in this use case: Bad!)
void changeTable(int table[3][3], const int tablePos, const char value)
{
    for(int i{0}; i < 3; i++)
    {
        for(int j{0}; j < 3; j++)
        {
            if(table[i][j] == tablePos)
            {
                table[i][j] = static_cast<int>(value);
            }
        }
    }
}

void displayTable(const int table[3][3], char key = 0)
{
    for(int i{0}; i < 3; i++)
    {
        for(int j{0}; j < 3; j++)
        {
            if(table[i][j] == static_cast<int>(key))
            {
                std::cout << " " << static_cast<char>(table[i][j]) << " ";
                continue;
            }
            std::cout << " " << table[i][j] << " ";
        }
        std::cout << '\n';
    }
}






int main(int argc, char *argv[])
{
    Player playerX{-1};
    Player playerO{-2};

    Player playerX.setWins(99);
    Player playerO.setWins(999);

    displayStats(playerX, playerO, 999);
    std::cout << "|0000|\n|----|\n";

    //test sizes NOTE: should now work with dia testing
    int row{5};
    int colum{10};


    //Lat test
    Board latTest{};
    latTest.setBoard(row, colum);
    latTest.setLateralWin(1, playerX.mark());
    latTest.display(playerX.mark(), playerO.mark());
    if(latTest.isLateralWin(playerX.mark()))
    {
        std::cout << "Lat Win!\n";
    }

    //Vert test(3)
    Board vertTest{};
    vertTest.setBoard(row, colum);
    vertTest.setVerticalWin(2, playerX.mark());
    vertTest.display(playerX.mark(), playerO.mark());
    if(vertTest.isVerticalWin(playerX.mark()))
    {
        std::cout << "Vert Win!\n";
    }

    //Dia test
    Board diaTest{};
    diaTest.setBoard(4, 3);
    diaTest.coverBoardSlot(4, playerX.mark());
    diaTest.coverBoardSlot(8, playerX.mark());
    diaTest.coverBoardSlot(12, playerX.mark());
//    diaTest.coverBoardSlot(13, playerX.mark());
//    diaTest.coverBoardSlot(51, playerX.mark());
//    diaTest.coverBoardSlot(61, playerX.mark());
//    diaTest.coverBoardSlot(71, playerX.mark());
//    diaTest.coverBoardSlot(81, playerX.mark());
//    diaTest.coverBoardSlot(91, playerX.mark());
//    diaTest.coverBoardSlot(101, playerX.mark());
//    diaTest.setDiagonalWin(playerX.mark(), true);
//    diaTest.setDiagonalWin(1, playerX.mark());//not working
    diaTest.display(playerX.mark(), playerO.mark());
    if(diaTest.isDiagonalWin(playerX.mark()))
    {
        std::cout << "Dia Win!\n";
    }

    //Tie test
    Board tieTest{};
    tieTest.setBoard(row, colum);
    tieTest.setTie(playerX.mark());
    tieTest.display(playerX.mark(), playerO.mark());
    if(tieTest.isTie(playerX.mark(), playerO.mark()))
    {
        std::cout << "Tie game!\n";
    }
    std::cout << "END BOARD TEST!\n";

    displayStats(playerX, playerO);
    TicTacToe test{};
    std::cout << "END TICTACTOE TEST!\n";

    Table table{makeTable(3, 3)};
    displayTable(table);
    changeTable(table, 1, 'x');
    std::cout << "VEC CHANGE\n";
    displayTable(table, 'x');
    std::cout << "END STD VEC!\n";

    int matrix[3][3]
    {
         {1, 2, 3},
         {4, 5, 6},
         {7, 8, 9},
    };
    int outter{1};
    int inner{0};
    while(outter <= 5)
    {
        inner = 5;
        while(inner >= 1)
        {
            if(inner <= outter)
            {
                std::cout << inner << " ";
            }
            else
            {
                std::cout << "  ";
            }
            inner--;
        }
        std::cout << '\n';
        outter++;
    }
//    displayTable(matrix);
//    changeTable(matrix, 1, 'x');
    std::cout << "CHANGE\n";
//    displayTable(matrix, 'x');


    return 0;
}
#endif // TICTACTOETEST_H
