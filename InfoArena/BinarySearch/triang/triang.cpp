#include<iostream>
#include<fstream>
#include<vector>
#include<cmath>
#include<algorithm>

#define M_PI 3.14159265358979323846
#define precision 10e-5

double sin_60 = sin( (60 * M_PI) / 180);
double cos_60 = cos( (60 * M_PI) / 180);

/*
    Rotational matrix = ( cos(α) -sin(α) 
                          sin(α)  cos(α) )
    Particular case for 60 degress:
        = (0.5          -sqrt(3)/2
           sqrt(3)/2    0.5         )
    
    new_x = old_x * cos(teta) + old_y * sin(teta)
    new_y = -old_x * sin(teta) + old_y * cos(teta)
*/

struct point {
    double x, y;
};

point rotate(point a, bool clock_wise) {
    point tmp;
    if(clock_wise) {
        tmp.x = a.x * cos_60 + a.y * sin_60;
        tmp.y = -a.x * sin_60 + a.y * cos_60;
    }
    else {
        tmp.x = a.x * cos_60 - a.y * sin_60;
        tmp.y = a.x * sin_60 + a.y * cos_60;
    }
    return tmp;
}

bool compare_points(point a, point b) {

    if(fabs(a.x - b.x) < precision && fabs(a.y - b.y) < precision)
        return true;
    return false;
}


long long _binary_search(long long left, long long right, const std::vector<point>& points, point a) {
  
    // std::cout << "\n\n";
    while(left <= right) {
        long long mid = left + (right - left) / 2;

        if(compare_points(points[mid], a)) {
            // std::cout << "Eu sunt a.x: " << a.x << "Eu sunt a.y: " << a.y << "\n";
            // std::cout << "Eu sunt points[mid].x: " << points[mid].x << " Eu sunt points[mid].y: " << points[mid].y << "\n";
            return true;
        }

        if(points[mid].x < a.x || ( fabs(points[mid].x - a.x) < precision && points[mid].y < a.y)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    return false;
}

long long count_eq_triangles(const std::vector<point>& points) {
    long long counter = 0;

    for(size_t i = 0; i < points.size() - 1; ++i) {
        for(size_t j = i + 1; j < points.size(); ++j) {
            
            point a_cw = rotate(points[j], true);
            // std::cout << "Eu sunt rotit: " << points[j].x << " " << points[j].y << "\n";
            // std::cout << "a_cw.x : " << a_cw.x << " a_cw.y: " << a_cw.y << "\n";
            counter += _binary_search(j + 1, points.size(), points, a_cw);
            

            point a_ccw = rotate(points[j], false);
            // std::cout << "Eu sunt rotit: " << points[j].x << " " << points[j].y << "\n";
            // std::cout << "a_ccw.x : " << a_ccw.x << " a_ccw.y: " << a_ccw.y << "\n";
            counter += _binary_search(j + 1, points.size(), points, a_ccw);
        }
    }
    return counter;
}

bool cmp(const point &a, const point &b)
{
    if(fabs(a.x - b.x) > precision) {
        return a.x < b.x;
    }

    if(fabs(a.y - b.y) > precision) {
        return a.y < b.y;
    }

    return true;    
}

int main() {

    long long n;
    std::vector<point> points;

    std::ifstream in("triang.in");
    std::ofstream out("triang.out");

    in >> n;
    while(n--) {
        point tmp;
        in >> tmp.x >> tmp.y;
        points.push_back(tmp);
    }

    std::sort(points.begin(), points.end(), cmp);

    // for(const auto& x: points)
    //     std::cout << x.x  << " " <<  x.y << "\n";
    // std::cout << "\n";

    
    // for(auto const& x: all_pairs) {
    //     std::cout << x.first.x << " " << x.first.y << " ";
    //     std::cout << x.second.x << " " << x.second.y << " ";
    // } 
    // std::cout << "\n";

    // std::cout << count_eq_triangles(points);
    out << count_eq_triangles(points) << "\n";

    in.close();
    out.close();

    return 0;
}