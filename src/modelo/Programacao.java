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
     
    public Programacao(JSONObject status, JSONObject parametros, String[] pacotes) {
        this.status = status;
        this.parametros = parametros;
        this.pacotes = pacotes;

    }

    public Programacao() {
        this.status = null;
        this.parametros = null;
        this.pacotes = null;

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
}
