import edu.princeton.cs.algs4.In;
import edu.princeton.cs.algs4.MinPQ;
import edu.princeton.cs.algs4.StdOut;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Solver {
    private final Board b1;
    private final Board b2;
    private final MinPQ<SearchNode> q1;
    private final MinPQ<SearchNode> q2;

    private SearchNode solnNode;
    private List<Board> solnPath;


    // find a solution to the initial board (using the A* algorithm)
    public Solver(Board initial) {
        if (initial == null) throw new IllegalArgumentException("arg is empty in Solver()");
        q1 = new MinPQ<>((a, b) -> Integer.compare(a.dist + a.approxDistFromGoal(), b.dist + b.approxDistFromGoal()));
        q2 = new MinPQ<>((a, b) -> Integer.compare(a.dist + a.approxDistFromGoal(), b.dist + b.approxDistFromGoal()));
        b1 = initial;
        b2 = b1.twin();
        solnNode = null;

        solve();
    }

    private void solve() {
        q1.insert(new SearchNode(b1, 0, null));
        q2.insert(new SearchNode(b2, 0, null));

        while (true) {
            SearchNode u1 = q1.delMin();
            SearchNode u2 = q2.delMin();

            if (u1.isGoal()) {
                solnNode = u1;
                break;
            }
            if (u2.isGoal()) {
                solnNode = null;
                break;
            }

            for (Board v1: u1.board.neighbors()) {
                if (u1.prevNode != null && v1.equals(u1.prevNode.board)) continue;
                q1.insert(new SearchNode(v1, u1.dist + 1, u1));
            }
            for (Board v2: u2.board.neighbors()) {
                if (u2.prevNode != null && v2.equals(u2.prevNode.board)) continue;
                q2.insert(new SearchNode(v2, u2.dist + 1, u2));
            }
        }

        // find path
        solnPath = new ArrayList<>();
        if (solnNode != null) {
            SearchNode currNode = solnNode;
            while (currNode != null) {
                solnPath.add(currNode.board);
                currNode = currNode.prevNode;
            }
            Collections.reverse(solnPath);
        }
    }


    // is the initial board solvable? (see below)
    public boolean isSolvable() {
        return solnNode != null;
    }

    // min number of moves to solve initial board; -1 if unsolvable
    public int moves() {
        return isSolvable() ? solnNode.dist : -1;
    }

    // sequence of boards in a shortest solution; null if unsolvable
    public Iterable<Board> solution() {
        return isSolvable() ? solnPath : null;
    }


    private class SearchNode {
        private final Board board;
        private final int dist; // dist from start
        private final SearchNode prevNode;
        private final int memoApproxDistFromGoal;

        public SearchNode(Board board, int dist, SearchNode prevNode) {
            this.board = board;
            this.dist = dist;
            this.prevNode = prevNode;
            this.memoApproxDistFromGoal = manhattanDist();
        }

        public int approxDistFromGoal() {
            return memoApproxDistFromGoal;
        }

//        private int hammingDist() {
//            return this.board.hamming();
//        }

        private int manhattanDist() {
            return this.board.manhattan();
        }

        public boolean isGoal() {
            return this.board.isGoal();
        }
    }


    // test client (see below)
    public static void main(String[] args) {

        // create initial board from file
        In in = new In(args[0]);
//        In in = new In("puzzle3x3-unsolvable.txt");
//        In in = new In("puzzle04.txt");
//        In in = new In("myPuzzle.txt");

        int n = in.readInt();
        int[][] tiles = new int[n][n];
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                tiles[i][j] = in.readInt();
        Board initial = new Board(tiles);
//        int mandist = initial.manhattan();

        // solve the puzzle
        Solver solver = new Solver(initial);

        // print solution to standard output
        if (!solver.isSolvable())
            StdOut.println("No solution possible");
        else {
            StdOut.println("Minimum number of moves = " + solver.moves());
            for (Board board : solver.solution())
                StdOut.println(board);
        }
    }

}
