#include <cstdio>
#include <cstring>
#include "shapes.h"

bool sphere::Hits( const ray& R, hit_info& Info ) const
{
    vec3 oc = R.Origin - C;
    double a = R.Dir.length2();
    double b = 2 * dot(oc, R.Dir);
    double c = oc.length2() - Radius * Radius;
    double discr = b * b - 4 * a * c;
    if (discr >= 0)
    {
        Info.t = (-b - sqrt(discr)) / (2 * a);
        Info.p = R.at(Info.t);
        Info.mtl = Mtl;
        vec3 n = mth::unit_vector(Info.p - C);
        Info.set_face_normal(R, n);
        return true;
    }
    return false;
}

bool triangle::Hits( const ray& R, hit_info& Info ) const
{
    vec3 N = mth::unit_vector(cross(p0 - p1, p0 - p2));  // plane normal
    double D = -dot(N, p0);  // D coeff from Ax + By + Cz + D = 0 plane equation
    if (fabs(dot(N, R.Dir)) <= THR)
        return false;
    double t = -(dot(N, R.Origin) + D) / dot(N, R.Dir);
    if (t <= THR)
        return false;
    point3 p = R.at(t); // intersection with triangle plane

    vec3
        edge0 = p1 - p0,
        edge1 = p2 - p1,
        edge2 = p0 - p2;
    vec3
        c0 = p - p0,
        c1 = p - p1,
        c2 = p - p2;
    if (dot(N, cross(edge0, c0)) > THR &&
        dot(N, cross(edge1, c1)) > THR &&
        dot(N, cross(edge2, c2)) > THR)
    {
        Info.set_face_normal(R, N);
        Info.mtl = Mtl;
        Info.p = p;
        Info.t = t;
        return true;
    }
    return false;
}

model::model( const std::string& fn, std::shared_ptr<material> mtl ) : Mtl(mtl)
{
    FILE* f = fopen(fn.c_str(), "r");
    if (f == nullptr)
    {
        LOG(Severity::ERROR) << "Can't open " << fn << " file";
        return;
    }

    uint32_t nv = 0, ni = 0;
    static char Buf[10000];

    while (fgets(Buf, sizeof(Buf) - 1, f) != nullptr)
    {
        if (Buf[0] == 'v' && Buf[1] == ' ')
            nv++;
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
            char* s = Buf + 2;
            char oldc = ' ';
            uint32_t cnt = 0;
            while (*s != 0)
                cnt += isspace(static_cast<uint8_t>(oldc)) && !isspace(static_cast<uint8_t>(*s)), oldc = *s++;
            ni += cnt - 2;
        }
    }

    std::vector<point3> Vertices(nv);
    std::vector<uint32_t> Indices(ni * 3);
    rewind(f);
    nv = ni = 0;
    while (fgets(Buf, sizeof(Buf) - 1, f) != nullptr)
    {
        if (Buf[0] == 'v' && Buf[1] == ' ')
        {
            double x, y, z;
            sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
            Vertices[nv++] = vec3(x, y, z);
        }
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
            char* s = Buf + 2, oldc = ' ';
            uint32_t n = 0, n0 = 0, n1 = 0, nc;
            while (*s != 0)
            {
                if (isspace(static_cast<uint8_t>(oldc)) && !isspace(static_cast<uint8_t>(*s)))
                {
                    sscanf(s, "%d", &nc);
                    if (nc > 0)
                        nc--;
                    else
                        nc += nv;
                    if (n == 0)
                        n0 = nc;
                    else if (n == 1)
                        n1 = nc;
                    else
                    {
                        Indices[ni++] = n0;
                        Indices[ni++] = n1;
                        Indices[ni++] = nc;
                        n1 = nc;
                    }
                    n++;
                }
                oldc = *s++;
            }
        }
    }
    for (uint32_t i = 0; i < ni; i += 3)
        Triangles.push_back(std::make_shared<triangle>(Vertices[Indices[i]], Vertices[Indices[i + 1]], Vertices[Indices[i + 2]], Mtl));
    LOG(Severity::DEBUG) << "Loaded " << Triangles.size() << " triangles for " << fn << " model to scene";
    fclose(f);
}

bool model::Hits( const ray& R, hit_info& Info ) const
{
    hit_info temp {{}, {}, 1e9};
    bool hits = false;
    for (auto t : Triangles)
    {
        if(t->Hits(R, temp) && temp.t < Info.t && temp.t > THR)
            Info = temp, hits = true;
    }
    return hits;
}