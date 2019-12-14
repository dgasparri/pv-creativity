import java.io.FileWriter;
import java.io.IOException;   
import java.io.PrintWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.Writer;


public class WriteToFileCsv
 {
   //FileWriter fw = new FileWriter("C:/Users/alexf/Desktop/Fisica/triangles.csv");
  public static void main(String[] args) throws IOException{

System.out.println("Starting....");
        File file = new File("C:/Users/alexf/Desktop/Fisica/triangles.csv");
        try {
            FileWriter output = new FileWriter(file);
            CSVWriter write = new CSVWriter(output);

            // Header column value
            String[] header = { "ID", "Name", "Address", "Phone Number" };
            write.writeNext(header);
            // Value
            String[] data1 = { "1", "First Name", "Address1", "12345" };
            write.writeNext(data1);
            String[] data2 = { "2", "Second Name", "Address2", "123456" };
            write.writeNext(data2);
            String[] data3 = { "3", "Third Name", "Address3", "1234567" };
            write.writeNext(data3);
            write.close();
        } catch (Exception e) {
            // TODO: handle exception
            e.printStackTrace();

        }

        System.out.println("End.");







}



}