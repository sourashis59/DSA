#include<bits/stdc++.h>

using namespace std;
class Solution {
public:

    class Point {
    public:
        int x, y;
        Point(int x, int y): x(x), y(y) {}
        Point(const vector<int> &arr): x(arr[0]), y(arr[1]) {}

        bool operator == (const Point &that) const {
            return this->x == that.x && this->y == that.y;
        }
    };


    //check if vector <cd> takes counter clockwise turn from vector <ab>
    //i.e., check if cross product  ab X cd is positive or not
    //if positive, returns +1
    //if negative, returns -1
    //if zero, returns 0
    static int ccw(const Point &a, const Point &b, const Point &c, const Point &d) {
        // ab X bc = determinant(...)
        int area = (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
        if (area < 0) return -1; //counter clockwise
        if (area > 0) return 1; //clockwise
        return 0; 
    }


    class comp {
    public:
        Point minYPoint;

        comp(const Point &minYPoint): minYPoint(minYPoint) {}
        bool operator()(const Point &a, const Point &b) {
            //if any point is the min Y point, keep it in beninging
            if (a == minYPoint) return true;
            if (b == minYPoint) return false;

            //return smaller angle (or smaller slope) point
            int ccwRes = ccw(minYPoint, a, a, b);
            if (ccwRes != 0) return ccwRes > 0;

            //for equality:
            //choose the closest point first
            int dist1 = (minYPoint.x - a.x) * (minYPoint.x - a.x) + (minYPoint.y - a.y) * (minYPoint.y - a.y);
            int dist2 = (minYPoint.x - b.x) * (minYPoint.x - b.x) + (minYPoint.y - b.y) * (minYPoint.y - b.y);
            return dist1 < dist2;
        }
    };

    //Graham's scan algorithm
    vector<vector<int>> outerTrees(vector<vector<int>>& _points) {
        vector<Point> points(_points.begin(), _points.end());
        int n = points.size();

        //edge case
        if (n <= 3) return _points;
        
        //point with min y coordinate
        Point minYpoint(-1, INT_MAX);
        for (const auto p: points) {
            if (p.y < minYpoint.y) minYpoint = p;
        } 
        //sort according to increasing order of slopes of all points making with minYpoint
        sort(points.begin(), points.end(), comp(minYpoint));

        //for the last slope consider points from furthest to closest
        //if slope of first line is not same as last line
        if (ccw(points[0], points[1], points[n - 2], points[n - 1]) != 0)
        {
            int i = n - 2;
            while (i >= 0 && ccw(points[n - 1], points[0], points[i], points[i + 1]) == 0)
                --i;
            
            reverse(points.begin() + i + 1, points.end());
        }

        stack<Point> s;
        s.push(points[0]);
        s.push(points[1]);
        for (int i = 2; i < points.size(); ++i) {
            Point currPoint = points[i];
            Point top = s.top();
            s.pop();
            //discard points that would create clockwise turn
            while (ccw(s.top(), top, top, currPoint) < 0) {
                top = s.top();
                s.pop();
            }
            s.push(top);
            s.push(currPoint);
        }
        vector<vector<int>> res;
        while (s.size()) {
            res.push_back({s.top().x, s.top().y});
            s.pop();
        }

        return res;
    }

/*
[[1,1],[2,2],[2,0],[2,4],[3,3],[4,2]]
[[1,2],[2,2],[4,2]]
[[0,0],[0,1],[0,2],[1,2],[2,2],[3,2],[3,1],[3,0],[2,0]]
[[0,0],[1,1],[2,2],[1,2],[2,4]]
*/
};



int main() {
    // vector<vector<int>> points = {{0,2},{0,4},{0,5},{0,9},{2,1},{2,2},{2,3},{2,5},{3,1},{3,2},{3,6},{3,9},{4,2},{4,5},{5,8},{5,9},{6,3},{7,9},{8,1},{8,2},{8,5},{8,7},{9,0},{9,1},{9,6}};
    vector<vector<int>> points = {{0,2},{0,1},{0,0},{1,0},{2,0},{1,1}};
    Solution ob;
    ob.outerTrees(points);
}