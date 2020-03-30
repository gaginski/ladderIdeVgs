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
     
    public Programacao(JSONObject status, JSONObject parametros) {
        this.status = status;
        this.parametros = parametros;

    }

    public Programacao() {
        this.status = null;
        this.parametros = null;

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
