/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package modelo;

import javax.swing.JLabel;

/**
 *
 * @author Vitor
 */
public class Comando extends JLabel{
    public String comando;
    public int porta;
    public int linha;
    public int coluna;
    public double delay; 

    public Comando(String comando, int porta, int linha, int coluna, double delay) {
        this.comando = comando;
        this.porta = porta;
        this.linha = linha;
        this.coluna = coluna;
        this.delay = delay;
    }

    public String getComando() {
        return comando;
    }

    public int getPorta() {
        return porta;
    }

    public int getLinha() {
        return linha;
    }

    public int getColuna() {
        return coluna;
    }

    public double getDelay() {
        return delay;
    }

    public void setComando(String comando) {
        this.comando = comando;
    }

    public void setPorta(int porta) {
        this.porta = porta;
    }

    public void setLinha(int linha) {
        this.linha = linha;
    }

    public void setColuna(int coluna) {
        this.coluna = coluna;
    }

    public void setDelay(double delay) {
        this.delay = delay;
    }
    
}
