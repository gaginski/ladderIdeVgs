/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modelo;

/**
 *
 * @author Vitor
 */
public class config {
    public String porta;

    public config(String porta) {
        this.porta = porta;
    }
    
    public config() {
        this.porta = null;
    }
    
    public String getPorta() {
        return porta;
    }

    public void setPorta(String porta) {
        this.porta = porta;
    }
    
}
