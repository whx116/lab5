#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
using namespace std;
const int N = 1e5 + 10;
const double eps = 1e-8, INF = 1e20;
int sgn(double x) {
    if (fabs(x) < eps)
        return 0;
    else
        return x < 0 ? -1 : 1;
}
struct Point {  // 点结构体
    double x, y;
    Point() {}
    Point(double x, double y) : x(x), y(y) {}
    Point operator+(Point B) { return Point(x + B.x, y + B.y); }
    Point operator-(Point B) { return Point(x - B.x, y - B.y); }
    bool operator==(Point B) { return x == B.x && y == B.y; }
};
typedef Point Vector;
// 比较函数1
bool cmpxy(Point A, Point B) {
    return sgn(A.x - B.x) < 0 || (sgn(A.x - B.x) == 0 && sgn(A.y - B.y) < 0);
}
// 比较函数2
bool cmpy(Point A, Point B) {
    return sgn(A.y - B.y) < 0;
}
double Cross(Vector A, Vector B) {  // 求叉积
    return A.x * B.y - A.y * B.x;
}
double Dist(Point A, Point B) {  // 求两点间距离
    return hypot(A.x - B.x, A.y - B.y);
}
void init() {}
int n;
Point p[N], tmp_p[N];
double Closest_Pair(int left, int right) {  // 分治法求最近点对
    double dis = INF;
    if (left == right)
        return dis;
    if (left + 1 == right)
        return Dist(p[left], p[right]);
    int mid = (left + right) >> 1;
    double d1 = Closest_Pair(left, mid);
    double d2 = Closest_Pair(mid + 1, right);
    dis = min(d1, d2);
    int k = 0;
    for (int i = left; i <= right; ++i)
        if (fabs(p[mid].x - p[i].x) <= dis)
            tmp_p[++k] = p[i];
    sort(tmp_p + 1, tmp_p + k + 1, cmpy);
    for (int i = 1; i <= k; ++i)
        for (int j = i + 1; j <= k; ++j) {
            if (tmp_p[j].y - tmp_p[i].y >= dis)
                break;
            dis = min(dis, Dist(tmp_p[j], tmp_p[i]));
        }
    return dis;
}
void solve() {
    for (int i = 1; i <= n; ++i)  // 输入点
        scanf("%lf %lf", &p[i].x, &p[i].y);
    sort(p + 1, p + 1 + n, cmpxy);
    printf("%.2f\n", Closest_Pair(1, n) / 2);  // 输出最近点对
}
int main() {
    while (scanf("%d", &n) && n)  // n表示有n个点，输入0则结束程序
        solve();
    return 0;
}