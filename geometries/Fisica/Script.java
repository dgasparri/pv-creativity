import java.io.FileWriter;
import java.util.Arrays;

public class Script {

    public static void main(String[] args) throws Exception {

        String csvFile = "C:/Users/alexf/Desktop/Fisica/triangles.csv";
        FileWriter writer = new FileWriter(csvFile);

        Sinu(1, 1, 0, 5, 5);


       // CSVUtils.writeLine(writer, Arrays.asList(vertexx, vertexy, vertexz));

      //  CSVUtils.writeLine(writer, Arrays.asList("a", "b", "c", "d"));

        //custom separator + quote
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bb,b", "cc,c"), ',', '"');

        //custom separator + quote
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bbb", "cc,c"), '|', '\'');

        //double-quotes
      //  CSVUtils.writeLine(writer, Arrays.asList("aaa", "bbb", "cc\"c"));
    

        writer.flush();
        writer.close();


    }

    public static void Sinu(double A, double Omega, double Y1, double Y2, int X)
        {
            try {
                
           
            String csvFile = "C:/Users/alexf/Desktop/Fisica/triangles.csv";
            FileWriter writer = new FileWriter(csvFile);

            Vertex v1, v2, v3, v4;
            for(int i = 0; i < X; i++)
            {
                System.out.println("CICLO");
                int x1    = i;
                double y1 = Y1;
                double z1 = A*Math.sin(Omega*x1);

                v1 = new Vertex(Double.valueOf(x1), y1, z1);


                int x2    = x1;
                double y2 = Y2;
                double z2 = A*Math.sin(Omega*x2);

                v2 = new Vertex(Double.valueOf(x2), y2, z2);

                int x3 = x2 + 1;
                double y3 = y1;
                double z3 = A*Math.sin(Omega*x3);

                v3 = new Vertex(Double.valueOf(x3), y3, z3);

                int x4 = x3;
                double y4 = y2;
                double z4 = A*Math.sin(Omega*x4);
                v4 = new Vertex(Double.valueOf(x4), y4, z4);

                //vertex a
                String vertexAx = String.valueOf(v1.getPointX());
                String vertexAy = String.valueOf(v1.getPointY());
                String vertexAz = String.valueOf(v1.getPointZ());
                String vertexAxyz = vertexAx +" " + vertexAy +" " +vertexAz;
                System.out.println(vertexAxyz);

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
}