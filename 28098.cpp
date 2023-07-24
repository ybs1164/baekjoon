#include <stdio.h>
#include <algorithm>
#include <math.h>

using namespace std;

int n;

struct P {
    double x;
    double y;
    bool operator < (const P &a) {
        return (y == a.y) ? (x<a.x) : (y<a.y);
    }
} p[500001], q[500001];

double ccw(P a, P b, P c) {
    return a.x*b.y+b.x*c.y+c.x*a.y-b.x*a.y-c.x*b.y-a.x*c.y;
}

bool comp(P a, P b) {
    return atan2(a.y, a.x) > atan2(b.y, b.x);
}

double get_distance(P a, P b) {
    double xx = a.x - b.x;
    double yy = a.y - b.y;
    return sqrt(xx*xx + yy*yy);
}

P get_nearest_point(P p, P q) {
    if (p.x == q.x) {
        return P{x:p.x, y:0};
    } else {
        double a1 = (p.y - q.y)/(p.x - q.x);
        double b1 = p.y - a1*p.x;
        double a2 = -1 / a1;
        double b2 = 0;
        return P{
            x: -(b1-b2) / (a1-a2),
            y: a1*(-(b1-b2)/(a1-a2)) + b1
        };
    }
}

int main() {
    scanf("%d", &n);

    for (int i=0;i<n;i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        p[i].x = (double)x;
        p[i].y = (double)y;
    }

    sort(p, p+n, comp);

    for (int i=0;i<n;i++) {
        P point = get_nearest_point(p[i], p[(i+1)%n]);
        double dis = min(get_distance(p[i], point), get_distance(point, p[(i+1)%n]));
        double dis_to_point = get_distance(P{x:0, y:0}, point);

        printf("%lf %lf\n", point.x, point.y);
        printf("%lf %lf\n", dis, dis_to_point);
        if (dis > dis_to_point) {
            printf("Yes");
            return 0;
        }
    }

    printf("No");
    return 0;
}