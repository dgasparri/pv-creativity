import java.io.FileWriter;
import java.util.Arrays;

public class Script {

    public static void main(String[] args) throws Exception {
        //String csvFile = "C:/Users/alexf/Desktop/Fisica/triangles.csv";
        //FileWriter writer = new FileWriter(csvFile);
        Sinu(1, 1, 0, 5, 5,0,0);
        Retta(1, 0, 5, 5,0,0);
        Para(1, 1, 0, 5, 5,0,0);
        Circ(4, 0, 5, 179,0,0);
        cono(4, 0, 179, 0, 0, 4,4, 5);
        sfera(4, 0, 179, 0, 0, 4, 4, 4, 4, 4, -4);

       // CSVUtils.writeLine(writer, Arrays.asList(vertexx, vertexy, vertexz));

      //  CSVUtils.writeLine(writer, Arrays.asList("a", "b", "c", "d"));

        //custom separator + quote
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bb,b", "cc,c"), ',', '"');

        //custom separator + quote
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bbb", "cc,c"), '|', '\'');

        //double-quotes
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bbb", "cc\"c"));
    

      //  writer.flush();
       // writer.close();
    }
    //ondulato
    // angolo è l'inclinazione rispetto al suolo
    // angolo 2 Z_S
    public static void Sinu(double A, double Omega, double Y1, double Y2, int X, double angolo, double angolo2 )
        {
            try {
                
           
            String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesSinu.csv";
            FileWriter writer = new FileWriter(csvFile);

            Vertex v1, v2, v3, v4;

            for(int i = 0; i < X; i++)
            {
                int x1    = i;
                double y1 = Y1;
                double z1 = A*Math.sin(Omega*x1);
                //angolo
                double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo)) ;
                double yr1 = y1;
                double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));

                double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
                double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
                double zr11 = zr1;
                


                //first vertex
                v1 = new Vertex(xr11, yr11, zr11);


                int x2    = x1;
                double y2 = Y2;
                double z2 = A*Math.sin(Omega*x2);
                //angolo
                double xr2 = (Double.valueOf(x2) * Math.cos(angolo)) - (z2 * Math.sin(angolo));
                double yr2 = y2;
                double zr2 = (x2*Math.sin(angolo)) + (z2 * Math.cos(angolo));

                double xr22 = (Double.valueOf(xr2) * Math.cos(angolo2)) - (yr2 * Math.sin(angolo2));
                double yr22 = (xr2*Math.sin(angolo2)) + (yr2 * Math.cos(angolo2));
                double zr22 = zr2;

                //secondo Vertex
                v2 = new Vertex(xr22, yr22, zr22);

                int x3 = x2 + 1;
                double y3 = y1;
                double z3 = A*Math.sin(Omega*x3);
                //angolo
                double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
                double yr3 = y3;
                double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

                double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
                double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
                double zr33 = zr3;


                //third verdex
                v3 = new Vertex(xr33, yr33, zr33);

                int x4 = x3;
                double y4 = y2;
                double z4 = A*Math.sin(Omega*x4);
                //angolo
                double xr4 = (Double.valueOf(x4) * Math.cos(angolo)) - (z4 * Math.sin(angolo));
                double yr4 = y4;
                double zr4 = (x4*Math.sin(angolo)) + (z4 * Math.cos(angolo));

                double xr44 = (Double.valueOf(xr4) * Math.cos(angolo2)) - (yr4 * Math.sin(angolo2));
                double yr44 = (xr4*Math.sin(angolo2)) + (yr4 * Math.cos(angolo2));
                double zr44 = zr4;

                v4 = new Vertex(xr44, yr44, zr44);

               
                //vertex a
                String vertexAx = String.valueOf(v1.getPointX());
                String vertexAy = String.valueOf(v1.getPointY());
                String vertexAz = String.valueOf(v1.getPointZ());
                String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;
              

                //vertex b 
                String vertexBx = String.valueOf(v2.getPointX());
                String vertexBy = String.valueOf(v2.getPointY());
                String vertexBz = String.valueOf(v2.getPointZ());
                String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

                //vertex c
                String vertexCx = String.valueOf(v3.getPointX());
                String vertexCy = String.valueOf(v3.getPointY());
                String vertexCz = String.valueOf(v3.getPointZ());
                String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;

                //vertex d
                String vertexDx = String.valueOf(v4.getPointX());
                String vertexDy = String.valueOf(v4.getPointY());
                String vertexDz = String.valueOf(v4.getPointZ());
                String vertexDxyz = vertexDx +" " + vertexDy +" " +vertexDz;
                
                //first triangle
                CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));
                //secondo triangle
                CSVUtils.writeLine(writer, Arrays.asList(vertexBxyz, vertexCxyz, vertexDxyz));


            } // end for
            writer.flush();
                writer.close();

            } catch (Exception e) {
            System.out.println(e);
            }


        }

    public static void Retta(double A, double Y1, double Y2, int X, double angolo, double angolo2){
      try {
                
           
        String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesRetta.csv";
        FileWriter writer = new FileWriter(csvFile);

        Vertex v1, v2, v3, v4;
        for(int i = 0; i < X; i++)
        {
            int x1    = i;
            double y1 = Y1;
            double z1 = A*x1;
            //angolo
            double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo));
            double yr1 = y1;
            double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));

            double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
            double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
            double zr11 = zr1;

            v1 = new Vertex(xr11,yr11,zr11);


            int x2    = x1;
            double y2 = Y2;
            double z2 =  A*x2;
            //angolo
            double xr2 = (Double.valueOf(x2) * Math.cos(angolo)) - (z2 * Math.sin(angolo));
            double yr2 = y2;
            double zr2 = (x2*Math.sin(angolo)) + (z2 * Math.cos(angolo));

            double xr22 = (Double.valueOf(xr2) * Math.cos(angolo2)) - (yr2 * Math.sin(angolo2));
            double yr22 = (xr2*Math.sin(angolo2)) + (yr2 * Math.cos(angolo2));
            double zr22 = zr2;


            v2 = new Vertex(xr22,yr22,zr22);

            int x3 = x2 + 1;
            double y3 = y1;
            double z3 =  A*x3;
            //angolo
            double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
            double yr3 = y3;
            double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

            double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
                double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
                double zr33 = zr3;

            v3 = new Vertex(xr33, yr33, zr33);

            int x4 = x3;
            double y4 = y2;
            double z4 =  A*x4;
            //angolo
            double xr4 = (Double.valueOf(x4) * Math.cos(angolo)) - (z4 * Math.sin(angolo));
            double yr4 = y4;
            double zr4 = (x4*Math.sin(angolo)) + (z4 * Math.cos(angolo));

            double xr44 = (Double.valueOf(xr4) * Math.cos(angolo2)) - (yr4 * Math.sin(angolo2));
                double yr44 = (xr4*Math.sin(angolo2)) + (yr4 * Math.cos(angolo2));
                double zr44 = zr4;

            v4 = new Vertex(xr44, yr44, zr44);

            //vertex a
            String vertexAx = String.valueOf(v1.getPointX());
            String vertexAy = String.valueOf(v1.getPointY());
            String vertexAz = String.valueOf(v1.getPointZ());
            String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;
            

            //vertex b 
            String vertexBx = String.valueOf(v2.getPointX());
            String vertexBy = String.valueOf(v2.getPointY());
            String vertexBz = String.valueOf(v2.getPointZ());
            String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

            //vertex c
            String vertexCx = String.valueOf(v3.getPointX());
            String vertexCy = String.valueOf(v3.getPointY());
            String vertexCz = String.valueOf(v3.getPointZ());
            String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;

            //vertex d
            String vertexDx = String.valueOf(v4.getPointX());
            String vertexDy = String.valueOf(v4.getPointY());
            String vertexDz = String.valueOf(v4.getPointZ());
            String vertexDxyz = vertexDx +" " + vertexDy +" " +vertexDz;
            
            //first triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));
            //secondo triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexBxyz, vertexCxyz, vertexDxyz));

            
        

        } // end for
        writer.flush();
            writer.close();

        } catch (Exception e) {
        System.out.println(e);
        }


    }

    public static void Para(double A, double B, double Y1, double Y2, int X, double angolo, double angolo2){
      try {
                
           
        String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesPara.csv";
        FileWriter writer = new FileWriter(csvFile);

        Vertex v1, v2, v3, v4;
        for(int i = 0; i < X; i++)
        {
          
            int x1    = i;
            double y1 = Y1;
            double z1 = A*Math.pow(x1, 2) + B*x1;

            //angolo
            double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo));
            double yr1 = y1;
            double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));

            double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
            double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
            double zr11 = zr1;

            v1 = new Vertex(xr11,yr11,zr11);


            int x2    = x1;
            double y2 = Y2;
            double z2 =  A*Math.pow(x2, 2) + B*x2;
            //angolo
            double xr2 = (Double.valueOf(x2) * Math.cos(angolo)) - (z2 * Math.sin(angolo));
            double yr2 = y2;
            double zr2 = (x2*Math.sin(angolo)) + (z2 * Math.cos(angolo));

            double xr22 = (Double.valueOf(xr2) * Math.cos(angolo2)) - (yr2 * Math.sin(angolo2));
            double yr22 = (xr2*Math.sin(angolo2)) + (yr2 * Math.cos(angolo2));
            double zr22 = zr2;


            v2 = new Vertex(xr22,yr22,zr22);

            int x3 = x2 + 1;
            double y3 = y1;
            double z3 = A*Math.pow(x3, 2) + B*x3;
            //angolo
            double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
            double yr3 = y3;
            double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

            double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
                double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
                double zr33 = zr3;


            v3 = new Vertex(xr33, yr33, zr33);

            int x4 = x3;
            double y4 = y2;
            double z4 =  A*Math.pow(x4, 2) + B*x4;
            //angolo
            double xr4 = (Double.valueOf(x4) * Math.cos(angolo)) - (z4 * Math.sin(angolo));
            double yr4 = y4;
            double zr4 = (x4*Math.sin(angolo)) + (z4 * Math.cos(angolo));

            double xr44 = (Double.valueOf(xr4) * Math.cos(angolo2)) - (yr4 * Math.sin(angolo2));
                double yr44 = (xr4*Math.sin(angolo2)) + (yr4 * Math.cos(angolo2));
                double zr44 = zr4;

            v4 = new Vertex(xr44, yr44, zr44);

            //vertex a
            String vertexAx = String.valueOf(v1.getPointX());
            String vertexAy = String.valueOf(v1.getPointY());
            String vertexAz = String.valueOf(v1.getPointZ());
            String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;
            

            //vertex b 
            String vertexBx = String.valueOf(v2.getPointX());
            String vertexBy = String.valueOf(v2.getPointY());
            String vertexBz = String.valueOf(v2.getPointZ());
            String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

            //vertex c
            String vertexCx = String.valueOf(v3.getPointX());
            String vertexCy = String.valueOf(v3.getPointY());
            String vertexCz = String.valueOf(v3.getPointZ());
            String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;

            //vertex d
            String vertexDx = String.valueOf(v4.getPointX());
            String vertexDy = String.valueOf(v4.getPointY());
            String vertexDz = String.valueOf(v4.getPointZ());
            String vertexDxyz = vertexDx +" " + vertexDy +" " +vertexDz;
            
            //first triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));
            //secondo triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexBxyz, vertexCxyz, vertexDxyz));

            
        

        } // end for
        writer.flush();
            writer.close();

        } catch (Exception e) {
        System.out.println(e);
        }

    }

    public static void Circ(double R, double Y1, double Y2, int X, double angolo, double angolo2){
      try {
                
           
        String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesCirc.csv";
        FileWriter writer = new FileWriter(csvFile);

        Vertex v1, v2, v3, v4;
        for(int i = 0; i < X; i++)
        {
          
            double x1    = R * Math.cos(Math.toRadians((double)(i)));
            double y1 = Y1;
            double z1 = R * Math.sin(Math.toRadians((double)(i))) ;
            //angolo
            double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo));
            double yr1 = y1;
            double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));


            double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
            double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
            double zr11 = zr1;

            v1 = new Vertex(xr11,yr11,zr11);


            double x2    = x1;
            double y2 = Y2;
            double z2 =  z1;
            //angolo
            double xr2 = (Double.valueOf(x2) * Math.cos(angolo)) - (z2 * Math.sin(angolo));
            double yr2 = y2;
            double zr2 = (x2*Math.sin(angolo)) + (z2 * Math.cos(angolo));

            double xr22 = (Double.valueOf(xr2) * Math.cos(angolo2)) - (yr2 * Math.sin(angolo2));
            double yr22 = (xr2*Math.sin(angolo2)) + (yr2 * Math.cos(angolo2));
            double zr22 = zr2;


            v2 = new Vertex(xr22,yr22,zr22);

            double x3 = R * Math.cos(Math.toRadians((double)(i + 1)));
            double y3 = y1;
            double z3 = R * Math.sin(Math.toRadians((double)(i + 1)));
            //angolo
            double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
            double yr3 = y3;
            double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

            double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
                double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
                double zr33 = zr3;

            v3 = new Vertex(xr33, yr33, zr33);

            double x4 = x3;
            double y4 = y2;
            double z4 =  z3;
            //angolo
            double xr4 = (Double.valueOf(x4) * Math.cos(angolo)) - (z4 * Math.sin(angolo));
            double yr4 = y4;
            double zr4 = (x4*Math.sin(angolo)) + (z4 * Math.cos(angolo));

            double xr44 = (Double.valueOf(xr4) * Math.cos(angolo2)) - (yr4 * Math.sin(angolo2));
                double yr44 = (xr4*Math.sin(angolo2)) + (yr4 * Math.cos(angolo2));
                double zr44 = zr4;

            v4 = new Vertex(xr44, yr44, zr44);

            //vertex a
            String vertexAx = String.valueOf(v1.getPointX());
            String vertexAy = String.valueOf(v1.getPointY());
            String vertexAz = String.valueOf(v1.getPointZ());
            String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;
            

            //vertex b 
            String vertexBx = String.valueOf(v2.getPointX());
            String vertexBy = String.valueOf(v2.getPointY());
            String vertexBz = String.valueOf(v2.getPointZ());
            String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

            //vertex c
            String vertexCx = String.valueOf(v3.getPointX());
            String vertexCy = String.valueOf(v3.getPointY());
            String vertexCz = String.valueOf(v3.getPointZ());
            String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;

            //vertex d
            String vertexDx = String.valueOf(v4.getPointX());
            String vertexDy = String.valueOf(v4.getPointY());
            String vertexDz = String.valueOf(v4.getPointZ());
            String vertexDxyz = vertexDx +" " + vertexDy +" " +vertexDz;
            
            //first triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));
            //secondo triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexBxyz, vertexCxyz, vertexDxyz));

            
        

        } // end for
        writer.flush();
            writer.close();

        } catch (Exception e) {
        System.out.println(e);
        }

    }



    public static void cono(double R, double zCirc, int X, double angolo, double angolo2, double vVerticex, double vVerticey, double vVerticez){
      try {

        String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesCono.csv";
        FileWriter writer = new FileWriter(csvFile);

        Vertex v1, v2, v3;

        for (int i = 0; i < X; i++) {

          double x1    = R * Math.cos(Math.toRadians((double)(i)));
            double y1 = R * Math.sin(Math.toRadians((double)(i)));
            double z1 =  zCirc;
            //angolo
            double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo));
            double yr1 = y1;
            double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));


            double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
            double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
            double zr11 = zr1;

            v1 = new Vertex(xr11,yr11,zr11);


           //vertice 2

           double x3 = R * Math.cos(Math.toRadians((double)(i + 1)));
            double y3 =  R * Math.sin(Math.toRadians((double)(i + 1)));
            double z3 = zCirc;
            //angolo
            double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
            double yr3 = y3;
            double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

            double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
            double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
            double zr33 = zr3;

            v2 = new Vertex(xr33, yr33, zr33);


            //angolo
            double Xxr3 = ( vVerticex * Math.cos(angolo)) - (vVerticez * Math.sin(angolo));
            double Xyr3 = vVerticey;
            double Xzr3 = (vVerticex*Math.sin(angolo)) + (vVerticez * Math.cos(angolo));

            double Xxr33 = (Double.valueOf(Xxr3) * Math.cos(angolo2)) - (Xyr3 * Math.sin(angolo2));
            double Xyr33 = (Xxr3*Math.sin(angolo2)) + (Xyr3 * Math.cos(angolo2));
            double Xzr33 = Xzr3;
            
            v3 = new Vertex(Xxr33, Xyr33, Xzr33);


            //vertex a
            String vertexAx = String.valueOf(v1.getPointX());
            String vertexAy = String.valueOf(v1.getPointY());
            String vertexAz = String.valueOf(v1.getPointZ());
            String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;

            //vertex b 
            String vertexBx = String.valueOf(v2.getPointX());
            String vertexBy = String.valueOf(v2.getPointY());
            String vertexBz = String.valueOf(v2.getPointZ());
            String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

            //vertex c
            String vertexCx = String.valueOf(v3.getPointX());
            String vertexCy = String.valueOf(v3.getPointY());
            String vertexCz = String.valueOf(v3.getPointZ());
            String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;


            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));


        }//end for

        writer.flush();
        writer.close();

      } catch (Exception e) {
        System.out.println(e);
      }
    }//end cono



    public static void sfera(double R, double zCirc, int X, double angolo, double angolo2, double vVerticex, double vVerticey, double vVerticez, double v2Verticex, double v2Verticey, double v2Verticez){
      try {

        String csvFile = "C:/Users/alexf/Desktop/FisicaConAngolo/trianglesSfera.csv";
        FileWriter writer = new FileWriter(csvFile);

        Vertex v1, v2, v3, v4;

        for (int i = 0; i < X; i++) {

           double x1    = R * Math.cos(Math.toRadians((double)(i)));
            double y1 = R * Math.sin(Math.toRadians((double)(i)));
            double z1 =  zCirc;
            //angolo
            double xr1 = (Double.valueOf(x1) * Math.cos(angolo)) - (z1 * Math.sin(angolo));
            double yr1 = y1;
            double zr1 = (x1*Math.sin(angolo)) + (z1 * Math.cos(angolo));


            double xr11 = (Double.valueOf(xr1) * Math.cos(angolo2)) - (yr1 * Math.sin(angolo2));
            double yr11 = (xr1*Math.sin(angolo2)) + (yr1 * Math.cos(angolo2));
            double zr11 = zr1;

            v1 = new Vertex(xr11,yr11,zr11);


           //vertice 2

           double x3 = R * Math.cos(Math.toRadians((double)(i + 1)));
            double y3 =  R * Math.sin(Math.toRadians((double)(i + 1)));
            double z3 = zCirc;
            //angolo
            double xr3 = (Double.valueOf(x3) * Math.cos(angolo)) - (z3 * Math.sin(angolo));
            double yr3 = y3;
            double zr3 = (x3*Math.sin(angolo)) + (z3 * Math.cos(angolo));

            double xr33 = (Double.valueOf(xr3) * Math.cos(angolo2)) - (yr3 * Math.sin(angolo2));
            double yr33 = (xr3*Math.sin(angolo2)) + (yr3 * Math.cos(angolo2));
            double zr33 = zr3;

            v2 = new Vertex(xr33, yr33, zr33);


            //angolo
            double Xxr3 = ( vVerticex * Math.cos(angolo)) - (vVerticez * Math.sin(angolo));
            double Xyr3 = vVerticey;
            double Xzr3 = (vVerticex*Math.sin(angolo)) + (vVerticez * Math.cos(angolo));

            double Xxr33 = (Double.valueOf(Xxr3) * Math.cos(angolo2)) - (Xyr3 * Math.sin(angolo2));
            double Xyr33 = (Xxr3*Math.sin(angolo2)) + (Xyr3 * Math.cos(angolo2));
            double Xzr33 = Xzr3;
            
            v3 = new Vertex(Xxr33, Xyr33, Xzr33);

            //angolo
            double X2xr3 = ( v2Verticex * Math.cos(angolo)) - (v2Verticez * Math.sin(angolo));
            double X2yr3 = v2Verticey;
            double X2zr3 = (v2Verticex*Math.sin(angolo)) + (v2Verticez * Math.cos(angolo));

            double X2xr33 = (Double.valueOf(X2xr3) * Math.cos(angolo2)) - (X2yr3 * Math.sin(angolo2));
            double X2yr33 = (X2xr3*Math.sin(angolo2)) + (X2yr3 * Math.cos(angolo2));
            double X2zr33 = X2zr3;
            
            v4 = new Vertex(X2xr33, X2yr33, X2zr33);


            //vertex a
            String vertexAx = String.valueOf(v1.getPointX());
            String vertexAy = String.valueOf(v1.getPointY());
            String vertexAz = String.valueOf(v1.getPointZ());
            String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;

            //vertex b 
            String vertexBx = String.valueOf(v2.getPointX());
            String vertexBy = String.valueOf(v2.getPointY());
            String vertexBz = String.valueOf(v2.getPointZ());
            String vertexBxyz = vertexBx +" " + vertexBy +" " +vertexBz;

            //vertex c
            String vertexCx = String.valueOf(v3.getPointX());
            String vertexCy = String.valueOf(v3.getPointY());
            String vertexCz = String.valueOf(v3.getPointZ());
            String vertexCxyz = vertexCx +" " + vertexCy +" " +vertexCz;

             //vertex d
             String vertexDx = String.valueOf(v4.getPointX());
             String vertexDy = String.valueOf(v4.getPointY());
             String vertexDz = String.valueOf(v4.getPointZ());
             String vertexDxyz = vertexDx +" " + vertexDy +" " +vertexDz;


            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexCxyz));
            //secondo triangle
            CSVUtils.writeLine(writer, Arrays.asList(vertexAxyz, vertexBxyz, vertexDxyz));


        }//end for

        writer.flush();
        writer.close();

      } catch (Exception e) {
        System.out.println(e);
      }


    }










      }