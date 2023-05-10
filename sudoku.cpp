// Sudoku solver, just for fun.
// (C) Werner

#include "sudoku.h"
#include <iostream>
#include <cassert>

Sudoku::Sudoku() : board(10, std::vector<int>(10, 0))
{
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

const std::vector<std::vector<std::vector<int>>>& Sudoku::Solve()
{
    solutions.clear();
    SolveNext(0, 0);
    return solutions;
}

void Sudoku::Print(const std::vector<std::vector<int>>& board) const
{
    printf(" --- --- --- \n");
    for (int y = 0; y < ROWS; y++)
    {
        printf("|");
        for (int x = 0; x < COLS; x++)        
        {
            if (IsEmpty(board, x, y))
                printf(".");
            else
                printf("%d", Get(board, x,y));
            if (x % 3 == 2)
                printf("|");
        }
        printf("\n");
        if (y % 3 == 2)
            printf(" --- --- --- \n");
    }
    printf("\n");
}

void Sudoku::SolveNext(int x, int y)
{
    if (solutions.size() >= max_solutions)
        return;

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
        solutions.push_back(board);
        return;
    }

    // Solve this field, if ok then continue with the next free field
    for (int value = MIN_VALUE; value <= MAX_VALUE; value++)
    {
        if (TryMove(x, y, value))
        {
            SolveNext(x, y);
            SetEmpty(x, y);
        }
    }
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

void Sudoku::CopyBoard(const std::vector<std::vector<int>>& src, std::vector<std::vector<int>>& dest)
{
    dest = src;
}


void Solve(const std::vector<std::vector<int>>& game)
{
    auto sudoku = Sudoku();
    sudoku.SetBoard(game);

    printf("Solve game:\n");
    sudoku.Print(game);
    auto solutions = sudoku.Solve();

    printf("%d solutions found:\n", solutions.size());
    if (solutions.size() > 10)
        return;
    for (auto const& solution : solutions)
        sudoku.Print(solution);
}

int main()
{
    std::vector<std::vector<int>> solved_game = {
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
        {0,8,0,1,0,0,0,0,0},    // set a few more fields to 0
        {2,0,0,0,0,0,0,0,5},
        {0,0,0,0,2,0,0,0,0},
        {5,0,0,0,3,0,0,0,1},
        {1,0,0,2,0,8,0,0,6},
        {0,2,6,0,0,0,3,5,0},
        {0,7,3,0,0,0,4,1,0},
        {0,0,0,0,1,0,0,0,0},
        {4,0,8,0,0,0,5,0,7}
    };

    std::vector<std::vector<int>> game3 = {
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0},
        {1,0,0,2,0,8,0,0,6},
        {0,2,6,0,0,0,3,5,0},
        {0,7,3,0,0,0,4,1,0},
        {0,0,0,0,1,0,0,0,0},
        {4,0,8,0,0,0,5,0,7}
    };


    Solve(game1);
    Solve(game2);
    Solve(game3);

    return 0;
}
