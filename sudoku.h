#pragma once
#include <vector>

class Sudoku
{
public:
    Sudoku();
    ~Sudoku() = default;

    void SetBoard(const std::vector<std::vector<int>>& setup);
    bool TryMove(int x, int y, int val);
    void Solve();
    void Print();

private:
    static const int COLS = 9;
    static const int ROWS = 9;
    static const int EMPTY_VALUE = 0;
    static const int MIN_VALUE = 1;
    static const int MAX_VALUE = 9;

    std::vector<std::vector<int>> board;
    std::vector<std::vector<int>> board_copy;
    std::vector<std::vector<std::vector<int>>> solutions;
    int recursive_count{ 0 };

    bool SolveNext(int x, int y);
    bool IsValid(int x, int y, int val) const;
    bool TestRow(int y, int val) const;
    bool TestCol(int x, int val) const;
    bool TestBlock(int x, int y, int val) const;
    void Clear();
    void CopyBoard(const std::vector<std::vector<int>>& src, std::vector<std::vector<int>>& dest);

    inline bool IsEmpty(int x, int y) const { return board[y][x] <= EMPTY_VALUE; }
    inline int Get(int x, int y) const { return board[y][x]; }
    inline void SetEmpty(int x, int y) { board[y][x] = EMPTY_VALUE; }
    inline void Set(int x, int y, int val) { board[y][x] = val; }
};
