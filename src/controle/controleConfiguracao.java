/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package controle;

import com.google.gson.Gson;
import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import modelo.Configuracoes;
import org.json.JSONException;
import org.json.simple.JSONObject;
import org.json.simple.parser.ParseException;

/**
 *
 * @author Vitor
 */
public class controleConfiguracao {
     public boolean salvaPorta(String porta) throws IOException, JSONException, FileNotFoundException, ParseException {

        JSONObject json = new JSONObject();
         
        // verificar, necessário criar leitura e alteração do config
        json.put("porta", porta);

        try (FileWriter config_json = new FileWriter(System.getProperty("user.dir") + "/config.json")) {
            config_json.write(json.toString());
        }
        return true;
    }
     
     // reutilizar metodo de leitura
         public Configuracoes configuracao() throws FileNotFoundException, IOException, ParseException, JSONException {
        Configuracoes c = new Configuracoes();
        Gson gson = new Gson();

        try {
            
            BufferedReader br = new BufferedReader(new FileReader("config.json"));
            
            c = gson.fromJson(br, Configuracoes.class);
        } catch (IOException e) {
        }

        return c;
    }
     
    public void lerConfiguracao(){
         // verificar, necessário criar leitura para alteração do config
    }
}
