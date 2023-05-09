// Sudoku solver, just for fun.
// (C) Werner

#include "sudoku.h"
#include <iostream>
#include <cassert>

Sudoku::Sudoku() : board(10, std::vector<int>(10, 0))
{
    Clear();
}

void Sudoku::SetBoard(const std::vector<std::vector<int>>& setup)
{
    CopyBoard(setup, board);
}

bool Sudoku::TryMove(int x, int y, int val)
{
    if (IsValid(x, y, val)) 
    {
        Set(x, y, val);
        return true;
    }
        
    return false;
}

void Sudoku::Solve()
{
    CopyBoard(board, board_copy);
    recursive_count = 0;
    SolveNext(0, 0);
}

void Sudoku::Print()
{
    printf(" --- --- --- \n");
    for (int y = 0; y < ROWS; y++)
    {
        printf("|");
        for (int x = 0; x < COLS; x++)        
        {
            if (IsEmpty(x, y))
                printf(".");
            else
                printf("%d", Get(x,y));
            if (x % 3 == 2)
                printf("|");
        }
        printf("\n");
        if (y % 3 == 2)
            printf(" --- --- --- \n");
    }
    printf("\n");
}

bool Sudoku::SolveNext(int x, int y)
{
    recursive_count++;

    // Advance to next empty place from here
    while (y < ROWS && x < COLS && !IsEmpty(x, y))
    {
        x++;
        if (x >= COLS)
        {
            x = 0;
            y++;
        }
    }
    if (y == COLS)
    {
        Print();
        return true;
    }

    // Solve this field, if ok then continue with the next free field
    for (int value = MIN_VALUE; value <= MAX_VALUE; value++)
    {
        if (TryMove(x, y, value))
        {
            if (SolveNext(x, y))
            {
                recursive_count--;
                SetEmpty(x, y);
                if (recursive_count > 1)
                {
                    return true;
                }
                else
                {
                    CopyBoard(board_copy, board);   // restart
                }
            }
            SetEmpty(x, y);  // No solution after this one, so must set empty
        }
    }
    recursive_count--;
    return false;
}

// Test move, assign to board if valid
bool Sudoku::IsValid(int x, int y, int val) const
{
    return TestRow(y, val) && TestCol(x, val) && TestBlock(x, y, val);
}

bool Sudoku::TestRow(int y, int val) const
{
    for (int x = 0; x < COLS; x++)
        if (Get(x, y) == val)
            return false;
    return true;
}

bool Sudoku::TestCol(int x, int val) const
{
    for (int y = 0; y < ROWS; y++)
        if (Get(x, y) == val)
            return false;
    return true;
}

bool Sudoku::TestBlock(int x, int y, int val) const
{
    int block_left = 3 * (x / 3);
    int block_top = 3 * (y / 3);
    for (int block_x = block_left; block_x < block_left + 3; block_x++)
        for (int block_y = block_top; block_y < block_top + 3; block_y++)
            if (Get(block_x, block_y) == val)
                return false;
    return true;
}

void Sudoku::Clear()
{
    for (int x = 0; x < COLS; x++)
        for (int y = 0; y < ROWS; y++)
            SetEmpty(x, y);
}

void Sudoku::CopyBoard(const std::vector<std::vector<int>>& src, std::vector<std::vector<int>>& dest)
{
    dest = src;
}

int main()
{
    auto sudoku = Sudoku();
    printf("%d\n", sudoku.TryMove(0, 0, 0));
    printf("%d\n", sudoku.TryMove(1, 0, 1));
    printf("%d\n", sudoku.TryMove(2, 0, 2));
    printf("%d\n", sudoku.TryMove(3, 0, 2));

    std::vector<std::vector<int>> setup = {
        {4, 3, 1, 6, 7, 9, 5, 2, 8},
        {9, 6, 7, 2, 5, 8, 3, 4, 1},
        {5, 8, 2, 1, 4, 3, 9, 6, 7},
        {6, 5, 9, 8, 1, 7, 2, 3, 4},
        {3, 2, 8, 5, 6, 4, 1, 7, 9},
        {7, 1, 4, 9, 3, 2, 8, 5, 6},
        {8, 7, 3, 4, 2, 1, 6, 9, 5},
        {1, 4, 5, 3, 9, 6, 7, 8, 2},
        {2, 9, 6, 7, 8, 5, 4, 1, 3}
    };
    //setup[0][0] = -1;
    //setup[0][1] = -1;
    //setup[4][0] = -1;
    //setup[3][3] = -1;
    //setup[6][6] = -1;
    //sudoku.SetBoard(setup);
    //sudoku.Solve();

    std::vector<std::vector<int>> game1 = {
        {0,8,0,1,0,4,0,9,0},
        {2,0,0,0,0,0,0,0,5},
        {0,0,0,0,2,0,0,0,0},
        {5,0,0,0,3,0,0,0,1},
        {1,0,0,2,0,8,0,0,6},
        {0,2,6,0,0,0,3,5,0},
        {0,7,3,0,0,0,4,1,0},
        {0,0,0,0,1,0,0,0,0},
        {4,0,8,0,0,0,5,0,7}
    };

    std::vector<std::vector<int>> game2 = {
        {0,0,0,0,0,0,0,0,0},
        {2,0,0,0,0,0,0,0,5},
        {0,0,0,0,2,0,0,0,0},
        {5,0,0,0,3,0,0,0,1},
        {1,0,0,2,0,8,0,0,6},
        {0,2,6,0,0,0,3,5,0},
        {0,7,3,0,0,0,4,1,0},
        {0,0,0,0,1,0,0,0,0},
        {4,0,8,0,0,0,5,0,7}
    };

    //sudoku.SetBoard(game1);
    //sudoku.Print();
    //sudoku.Solve();

    sudoku.SetBoard(game2);
    sudoku.Print();
    sudoku.Solve();

    return 0;
}
