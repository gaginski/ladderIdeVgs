/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modelo;

import org.json.JSONObject;

/**
 *
 * @author Vitor
 */
public class Programacao {

    public JSONObject status;
    public JSONObject parametros;
    public String[] pacotes;
    public String progNewFormat;
     
    public Programacao(JSONObject status, JSONObject parametros, String[] pacotes, String progNewFormat) {
        this.status = status;
        this.parametros = parametros;
        this.pacotes = pacotes;
        this.progNewFormat = progNewFormat;

    }

    public Programacao() {
        this.status = null;
        this.parametros = null;
        this.pacotes = null;
        progNewFormat = null;

    }

    public void setPacotes(String[] pacotes) {
        this.pacotes = pacotes;
    }

    public String[] getPacotes() {
        return pacotes;
    }

    public JSONObject getStatus() {
        return status;
    }

    public JSONObject getParametros() {
        return parametros;
    }

    public void setStatus(JSONObject status) {
        this.status = status;
    }

    public void setParametros(JSONObject parametros) {
        this.parametros = parametros;
    }
    public String getProgNewFormat() {
        return progNewFormat;
    }    
    public void setProgNewFormat(String progNewFormat) {
       this.progNewFormat = progNewFormat;
    }    
}
