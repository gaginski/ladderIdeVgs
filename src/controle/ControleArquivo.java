/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import modelo.Programacao;
import modelo.config;
import org.json.JSONException;
import org.json.simple.JSONObject;
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
        return true;
    }

    @SuppressWarnings("null")

    public config configuracao() throws FileNotFoundException, IOException, ParseException, JSONException {
        config c = new config();
        Gson gson = new Gson();

        try {
            
            BufferedReader br = new BufferedReader(new FileReader("config.json"));
            
            c = gson.fromJson(br, config.class);
        } catch (IOException e) {
        }

        return c;
    }
    public boolean salvaProg(JSONObject prog, File diretorio, String nomeProjeto) throws IOException, JSONException, FileNotFoundException, ParseException {
          try (FileWriter prog_json = new FileWriter(diretorio +"/"+nomeProjeto+".json")) {
            prog_json.write(prog.toString());
        }
        
        System.out.println("Programação salva com sucesso!");
        return true;
    }

}
