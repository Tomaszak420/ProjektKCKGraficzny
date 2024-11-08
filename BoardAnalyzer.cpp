#include "BoardAnalyzer.h"

BoardAnalyzer::BoardAnalyzer(string board[RZEDY][KOLUMNY], string dictionary_file_path) : dictionary(dictionary_file_path)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            this->board[i][j] = board[i][j];
        }
    }
}

void BoardAnalyzer::fillNeighborList() {

    for (int i = 0; i < RZEDY * KOLUMNY; i++)
    {
        vector<int> i_neighbor_list;

        int rows = i / RZEDY;
        int cols = i % KOLUMNY;

        vector<int> possible_rows;
        vector<int> possible_cols;

        possible_rows.push_back(rows);
        if (rows != 0)
            possible_rows.push_back(rows - 1);
        if (rows != (RZEDY - 1))
            possible_rows.push_back(rows + 1);

        possible_cols.push_back(cols);
        if (cols != 0)
            possible_cols.push_back(cols - 1);
        if (cols != (KOLUMNY - 1))
            possible_cols.push_back(cols + 1);

        for (int j = 0; j < possible_rows.size(); j++)
        {
            for (int k = 0; k < possible_cols.size(); k++)
            {
                if (!(possible_rows[j] == rows && possible_cols[k] == cols))
                {
                    i_neighbor_list.push_back(possible_rows[j] * RZEDY + possible_cols[k]);
                }
            }
        }

        neighbor_list.push_back(i_neighbor_list);
    }

}