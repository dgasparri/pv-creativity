#include <iostream>
#include <cmath>
#include "discpp.h"

double zmat[50][50], xray[50], yray[50], zlev[20];

int main ()
{ 
    int n = 50 ,i, j, nlev = 20;
    double fpi = 3.1415927 / 180.0, step, x, y;
    const char *ctit1 = "Shaded Surface / Contour Plot",
                *ctit2 = "F(X,Y) = 2*SIN(X)*SIN(Y)";
    Dislin g;

    step = 360.0 / (n - 1);
    for (i = 0; i < n; i++)
    { x = i * step;
    xray[i] = x;
    for (j = 0; j < n; j++)
    { y = j * step;
        yray[j] = y;
        zmat[i][j] = 2 * sin (x * fpi) * sin (y * fpi);
    }
    }

    g.scrmod ("revers");
    g.setpag ("da4p");
    g.metafl ("cons");
    g.disini ();
    g.pagera ();
    g.hwfont ();
    g.axspos (200, 2600);
    g.axslen (1800, 1800);

    g.name   ("X-axis", "x");
    g.name   ("Y-axis", "y");
    g.name   ("Z-axis", "z");

    g.titlin (ctit1, 2);
    g.titlin (ctit2, 4);

    g.graf3d (0.0, 360.0, 0.0, 90.0, 0.0, 360.0, 0.0, 90.0,
            -2.0, 2.0, -2.0, 1.0);
    g.height (50);
    g.title  ();

    g.grfini (-1.0, -1.0, -1.0, 1.0, -1.0, -1.0, 1.0, 1.0, -1.0);
    g.nograf ();
    g.graf   (0.0, 360.0, 0.0, 90.0, 0.0, 360.0, 0.0, 90.0);
    step = 4.0 / nlev;
    for (i = 0; i < nlev; i++)
    zlev[i] = -2.0 + i * step; 

    g.conshd (xray, n, yray, n, (double *) zmat, zlev, nlev);
    g.box2d  ();
    g.reset  ("nograf");
    g.grffin ();

    g.shdmod ("smooth", "surface"); 
    g.surshd (xray, n, yray, n, (double *) zmat);
    g.disfin ();
    return 0;
}