import java.util.ArrayList;
import java.util.List;

public class Board {
    private static final int [][]DXY = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    private final int [][]board;
    private final int n;

    // create a board from an n-by-n array of tiles,
    // where tiles[row][col] = tile at (row, col)
    public Board(int[][] tiles) {
        if (tiles == null) throw new IllegalArgumentException("arg is empty in Board()");
        n = tiles.length;
        board = new int[n][n];
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                board[i][j] = tiles[i][j];
            }
        }

    }


    // copy ctr
    private Board(Board that) {
        this.n = that.n;
        this.board = new int[n][n];
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                this.board[i][j] = that.board[i][j];
    }

    // string representation of this board
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(n);
        res.append('\n');
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j)
                res.append(" ").append(board[i][j]);

            res.append('\n');
        }
        return res.toString();
    }

    // board dimension n
    public int dimension() {
        return n;
    }

    // number of tiles out of place
    public int hamming() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int goalVal = i * n + (j + 1);
                if (!(i == n - 1 && j == n - 1) && goalVal != board[i][j])
                    ++res;
            }
        }
        return res;
    }

    private int abs(int x) {
        if (x < 0) x *= -1;
        return x;
    }

    // sum of Manhattan distances between tiles and goal
    public int manhattan() {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 0)
                    continue;

                int val = board[i][j];
                int targetI = (val - 1) / n;
                int targetJ = (val - 1) % n;
                res += abs(targetI - i) + abs(targetJ - j);
            }
        }
        return res;
    }

    // is this board the goal board?
    public boolean isGoal() {
        return hamming() == 0;
    }

    @Override
    public boolean equals(Object newObj) {
        if (newObj == null || !newObj.getClass().equals(this.getClass())) return false;
        if (newObj == this) return true;
        Board that = (Board) newObj;
        if (this.n != that.n) return false;
        if (this.board == that.board) return true;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                if (that.board[i] == null
                        || that.board.length != n
                        || this.board[i][j] != that.board[i][j])
                    return false;
        return true;
    }

    private boolean isSafe(int i, int j) {
        return i >= 0 && j >= 0 && i < n && j < n;
    }

    // all neighboring boards
    public Iterable<Board> neighbors() {
        List<Board> res = new ArrayList<>();
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != 0) continue;
                for (int[] dir : DXY) {
                    int x = i + dir[0];
                    int y = j + dir[1];
                    if (!isSafe(x, y)) continue;
                    Board newBoard = new Board(board);
                    swap(newBoard.board, x, y, i, j);
                    res.add(newBoard);
                }
                return res;
            }
        }
        return res;
    }


    private void swap(int [][]a, int i1, int j1, int i2, int j2) {
        int temp = a[i1][j1];
        a[i1][j1] = a[i2][j2];
        a[i2][j2] = temp;
    }

    // a board that is obtained by exchanging any pair of tiles
    public Board twin() {
        Board newBoard = new Board(this);
        // given 2 <= n <= 128
        if (newBoard.board[0][0] != 0 && newBoard.board[0][1] != 0) swap(newBoard.board, 0, 0, 0, 1);
        else swap(newBoard.board, 1, 0, 1, 1);
        return newBoard;
    }

    // unit testing (not graded)
    public static void main(String[] args) {
        System.out.println("hello");
    }

}
