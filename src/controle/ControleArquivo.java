/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;


import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import modelo.config;


import org.json.JSONException;
import org.json.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

/**
 *
 * @author Vitor
 */
public class ControleArquivo {

    public boolean salvaPorta(String porta) throws IOException, JSONException, FileNotFoundException, ParseException {

        JSONObject json = new JSONObject();

        json.put("porta", porta);

        try (FileWriter config_json = new FileWriter(System.getProperty("user.dir") + "/config.json")) {
            config_json.write(json.toString());
        }

        json = capturaJson();
        
        // testando checlout

        return true;
    }

    @SuppressWarnings("null")
    public JSONObject capturaJson() throws FileNotFoundException, IOException, ParseException {
       
         JSONObject jsonObject;
         JSONParser parser = new JSONParser();

         jsonObject = (JSONObject) parser.parse(new FileReader(
                    "config.json"));
         
         return jsonObject;
    }
    
    public config configuracao() throws FileNotFoundException, IOException, ParseException, JSONException{
        config c = new config();
        /*JSONObject config = null;
        JSONParser parser = new JSONParser();
        try {
            //Salva no objeto JSONObject o que o parse tratou do arquivo
            config = (JSONObject) parser.parse(new FileReader("config.json"));
               
             
        } 
        //Trata as exceptions que podem ser lançadas no decorrer do processo
        catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (ParseException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
        
        */
        c.porta = "COM5";
        
        return c;
    }

}
